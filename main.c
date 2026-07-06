#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Буфер для хранения введённой пользователем функции
char current_expr[100] = "";

double eval(const char* expr, double x);
double f(double);
double derivative(double, double, double (*ptr)());
void print_fraction(double);
void interval();

// Точка входа в программу
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char answer;
    printf("Добро пожаловать!\n");

    printf("1) Нахождение косинуса или синуса \n");
    printf("2) Нахождение длины интервала на котором убывает функция \n");
    printf("Сделайте свой выбор: ");
    answer = getchar();
    switch (answer)
    {
    case '1':
        printf("Пока не поддерживается :(");
        break;
    case '2':
        interval();
        break;
    default:
        break;
    }
    return 0;
}

// Нахождение интервалов убывания функции
void interval()
{
    double a = -3.0, b = 4.0;
    double step = 0.001;
    double h = 1e-6;

    char _interval_string[100];
    printf("Инструкции к написанию: \n");
    printf("Если есть степень, то пишите x*x\n");
    printf("Если есть корень, оборачиваете в sqrt()\n");
    printf("В настоящее время поддерживается только буква \"X\"\n");
    printf("Введите вашу функцию: ");
    scanf("%s", _interval_string);
    strcpy(current_expr, _interval_string);

    printf("Интервалы убывания функции y = %s:\n", _interval_string);
    int in_decreasing = 0;
    double start = 0.0;

    for (double x = a; x <= b; x += step)
    {
        double der = derivative(x, h, f);
        if (der < 0)
        {
            if (!in_decreasing)
            {
                in_decreasing = 1;
                start = x;
            }
        }
        else
        {
            if (in_decreasing)
            {
                in_decreasing = 0;
                double end = x;
                printf("[%.3f, %.3f] длина = %.3f\n", start, end, end - start);
            }
        }
    }
    if (in_decreasing)
    {
        printf("[%.3f, %.3f] длина = %.3f\n", start, b, b - start);
    }
}

// Пользовательская функция, введённая с клавиатуры
double f(double x)
{
    return eval(current_expr, x);
}

// Вывод числа в виде дроби с корнем
void print_fraction(double value)
{
    const double eps = 1e-10;

    if (fabs(value) < eps)
    {
        printf("0");
        return;
    }

    double int_part;
    double frac_part = modf(value, &int_part);
    if (fabs(frac_part) < eps)
    {
        printf("%.0f", value);
        return;
    }

    double sqrt3_2 = sqrt(3.0) / 2.0;
    if (fabs(fabs(value) - sqrt3_2) < eps)
    {
        printf("%s√3/2", value < 0 ? "-" : "");
        return;
    }

    double sqrt2_2 = sqrt(2.0) / 2.0;
    if (fabs(fabs(value) - sqrt2_2) < eps)
    {
        printf("%s√2/2", value < 0 ? "-" : "");
        return;
    }

    if (fabs(fabs(value) - 0.5) < eps)
    {
        printf("%s1/2", value < 0 ? "-" : "");
        return;
    }

    if (fabs(fabs(value) - sqrt(3.0)) < eps)
    {
        printf("%s√3", value < 0 ? "-" : "");
        return;
    }

    if (fabs(fabs(value) - sqrt(2.0)) < eps)
    {
        printf("%s√2", value < 0 ? "-" : "");
        return;
    }

    if (fabs(fabs(value) - 1.0) < eps)
    {
        printf("%s1", value < 0 ? "-" : "");
        return;
    }

    printf("%.10lf", value);
}

// Численная производная (центральная разность)
double derivative(double x, double h, double (*ptr)())
{
    return (ptr(x + h) - ptr(x - h)) / (2 * h);
}

double eval_expr(const char** p, double x);
double eval_term(const char** p, double x);
double eval_unary(const char** p, double x);
double eval_primary(const char** p, double x);

// Парсинг сложения и вычитания
double eval_expr(const char** p, double x) {
    double result = eval_term(p, x);
    while (**p == '+' || **p == '-') {
        char op = **p;
        (*p)++;
        double right = eval_term(p, x);
        if (op == '+') result += right;
        else result -= right;
    }
    return result;
}

// Парсинг умножения и деления
double eval_term(const char** p, double x) {
    double result = eval_unary(p, x);
    while (**p == '*' || **p == '/') {
        char op = **p;
        (*p)++;
        double right = eval_unary(p, x);
        if (op == '*') result *= right;
        else result /= right;
    }
    return result;
}

// Парсинг унарного плюса и минуса
double eval_unary(const char** p, double x) {
    if (**p == '-') {
        (*p)++;
        return -eval_unary(p, x);
    }
    if (**p == '+') {
        (*p)++;
        return eval_unary(p, x);
    }
    return eval_primary(p, x);
}

// Парсинг числа, переменной x, скобок и функций
double eval_primary(const char** p, double x) {
    while (isspace(**p)) (*p)++;

    if (**p == '(') {
        (*p)++;
        double val = eval_expr(p, x);
        while (isspace(**p)) (*p)++;
        if (**p == ')') (*p)++;
        return val;
    }

    if (**p == 'x') {
        (*p)++;
        return x;
    }

    if (isalpha(**p)) {
        char func[16];
        int i = 0;
        while (isalpha(**p) && i < 15) func[i++] = *(*p)++;
        func[i] = '\0';
        while (isspace(**p)) (*p)++;
        if (**p == '(') {
            (*p)++;
            double arg = eval_expr(p, x);
            while (isspace(**p)) (*p)++;
            if (**p == ')') (*p)++;
            if (strcmp(func, "sqrt") == 0) return sqrt(arg);
            if (strcmp(func, "sin") == 0) return sin(arg);
            if (strcmp(func, "cos") == 0) return cos(arg);
            if (strcmp(func, "tan") == 0) return tan(arg);
            if (strcmp(func, "fabs") == 0) return fabs(arg);
            return 0;
        }
        return 0;
    }

    char* end;
    double val = strtod(*p, &end);
    *p = end;
    return val;
}

// Точка входа в парсер математических выражений
double eval(const char* expr, double x) {
    const char* p = expr;
    double result = eval_expr(&p, x);
    return result;
}