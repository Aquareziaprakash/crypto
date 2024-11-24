#include <stdio.h>

int sumOfDigits(int num)
{
    int sum = 0;
    while (num != 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main()
{
    int num1, num2, sum;
    printf("Enter a positive integer: ");
    scanf("%d", &num1);
    printf("Enter a positive integer: ");
    scanf("%d", &num2);
    sum = sumOfDigits(num1, num2);
    printf("Sum of digits: %d\n", sum);
}
