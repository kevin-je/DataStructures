#include <stdio.h>
#include <stdlib.h>

typedef struct Complex {
    double real, imag;
} Complex;

void assign(Complex *a, double r, double i);
char* print(const Complex *a);
void add(Complex* c, const Complex a, const Complex b);
void multiply(Complex *c, const Complex a, const Complex b);
void divide(Complex *c, const Complex a, const Complex b);







int main() {
    // Complex test1, *test2, add_result;
    // assign(&test1, 1.0, 2.0);
    // assign(test2, 3.0, 4.0);
    // add(&add_result, test1, *test2);

    // printf("test1=%s, test2=%s\n", print(&test1), print(test2));
    // printf("test1+test2=%s\n", print(&add_result));

    Complex a, b, c, d, e, f, z;
    assign(&a, 8.0, 6.0);
    assign(&b, 4.0, 3.0);
    assign(&c, 8.0, 6.0);
    assign(&d, 4.0, 3.0);

    // 求出z = a*b / (c+d)
    multiply(&e, a, b);
    add(&f, c, d);
    divide(&z, e, f);

    printf("z = %s\n", print(&z));

    return 0;
}






// 初始化一个复数
void assign(Complex *a, double r, double i)
{
    a -> real = r;
    a -> imag = i;
}

// 输出一个复数的字符串
char* print(const Complex *a)
{
    char *string = malloc(16);
    sprintf(string, "%.2f+%.2fi", a->real, a->imag);
    return string;
}

// 两复数相加
void add(Complex* c, const Complex a, const Complex b)
{
    c -> real = a.real + b.real;
    c -> imag = a.imag + b.imag;
}

// 两复数相乘
void multiply(Complex *c, const Complex a, const Complex b)
{
    c -> real = a.real * b.real - a.imag * b.imag;
    c -> imag = a.real * b.imag + a.imag * b.real;
}

// 两复数相除
void divide(Complex *c, const Complex a, const Complex b)
{
    if (b.real || b.imag) {
        double dividend = b.real*b.real + b.imag*b.imag;
        c -> real = (a.real*b.real + a.imag*b.imag) / dividend;
        c -> imag = (a.imag*b.real - a.real*b.imag) / dividend;
    } else {
        puts("被除数不能为0！\n");
        exit(1);
    }
    
}