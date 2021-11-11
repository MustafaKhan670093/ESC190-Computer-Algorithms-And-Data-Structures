#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {

    double num1;
    double num2;
    char op; //this will store either a +, -, *, / character
    
    printf("Enter a number:");
    scanf("%lf", &num1);
    printf("Enter operator:");
    scanf(" %c",  &op); 
    printf("Enter a second number:");
    scanf("%lf", &num2);

    if(op == '+'){
        printf("%f\n", num1 + num2);
    } else if(op == '-'){
        printf("%f\n", num1 - num2);
    } else if(op == '*') {
        printf("%f\n", num1 * num2);
    } else if(op == '/') {
        printf("%f\n", num1 / num2);
    } else {
        printf("Invalid operator or input\n");
    }
    
    return 0;
}