#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <float.h>
#include <string.h>

double f(double);
double derivative(double, double, double (*ptr)());
void print_fraction(double);
void interval();

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

double f(double x)
{
    return sqrt(12 + x - x * x);
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