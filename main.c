#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <float.h>

// Функция для печати числа в виде дроби с корнем, если это возможно
void print_fraction(double value) {
    // Проверяем специальные значения с допуском
    const double eps = 1e-10;
    
    // Проверяем 0
    if (fabs(value) < eps) {
        printf("0");
        return;
    }
    
    // Проверяем целые числа
    double int_part;
    double frac_part = modf(value, &int_part);
    if (fabs(frac_part) < eps) {
        printf("%.0f", value);
        return;
    }
    
    // Проверяем значения с √3/2
    double sqrt3_2 = sqrt(3.0) / 2.0;
    if (fabs(fabs(value) - sqrt3_2) < eps) {
        printf("%s√3/2", value < 0 ? "-" : "");
        return;
    }
    
    // Проверяем значения с √2/2
    double sqrt2_2 = sqrt(2.0) / 2.0;
    if (fabs(fabs(value) - sqrt2_2) < eps) {
        printf("%s√2/2", value < 0 ? "-" : "");
        return;
    }
    
    // Проверяем 1/2
    if (fabs(fabs(value) - 0.5) < eps) {
        printf("%s1/2", value < 0 ? "-" : "");
        return;
    }
    
    // Проверяем √3
    if (fabs(fabs(value) - sqrt(3.0)) < eps) {
        printf("%s√3", value < 0 ? "-" : "");
        return;
    }
    
    // Проверяем √2
    if (fabs(fabs(value) - sqrt(2.0)) < eps) {
        printf("%s√2", value < 0 ? "-" : "");
        return;
    }
    
    // Проверяем 1
    if (fabs(fabs(value) - 1.0) < eps) {
        printf("%s1", value < 0 ? "-" : "");
        return;
    }
    
    // Если не удалось распознать - выводим как десятичную дробь
    printf("%.10lf", value);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    
    
    return 0;
}