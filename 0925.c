#include <stdio.h>

#include <limits.h>
LeeO1(void)
{
    printf("char min : %d, Max : %d", CHAR_MIN, CHAR_MAX);
    printf("short min : %d, Max : %d", SHRT_MIN, SHRT_MAX);
    printf("int min : %d, Max : %d", INT_MIN, INT_MAX);
    printf("long mon : %d, Max : %d", LONG_MIN, LONG_MAX);

    return 0;
}

LeeO2(void)
{
    signed char num1=130;
    unsigned char num2=130;

    printf("%d\t%d\n", num1, num2);

    return 0;
//-126  130
}

LeeO3(void)
{
    char num1 = -129;
    char num2 = 128;

    printf("#UnderFlow : %d\t OverFlow : %d\n", num1, num2);

    char num1 = -130;
    char num2 = 129;

    printf("#UnderFlow : %d\t OverFlow : %d\n", num1, num2);

    return 0;
}

int main(void)
{
    int a;

    printf("Which function call?: ");
    scanf("%d", &a);

    switch(a)
        {
        case 1:
            LeeO1();
            break;
        case 2:
            LeeO2();
            break;
        case 3:
            LeeO3();
            break;
        default:
            break;
        }
    return 0;
}
