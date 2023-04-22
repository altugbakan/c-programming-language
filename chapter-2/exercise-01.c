#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    printf("The minimum signed char value from limits.h is %d\n", CHAR_MIN);
    printf("The minimum signed char value calculated is %d\n", -(char)((unsigned char)~0 >> 1) - 1);
    printf("The maximum signed char value from limits.h is %d\n", CHAR_MAX);
    printf("The maximum signed char value calculated is %d\n", (char)((unsigned char)~0 >> 1));
    printf("\n");
    printf("The minimum unsigned char is %d\n", 0);
    printf("The maximum unsigned char value from limits.h is %d\n", UCHAR_MAX);
    printf("The maximum unsigned char value calculated is %d\n", (unsigned char)~0);
    printf("\n");
    printf("The minimum signed short value from limits.h is %d\n", SHRT_MIN);
    printf("The minimum signed short value calculated is %d\n", -(short)((unsigned short)~0 >> 1) - 1);
    printf("The maximum signed short value from limits.h is %d\n", SHRT_MAX);
    printf("The maximum signed short value calculated is %d\n", (short)((unsigned short)~0 >> 1));
    printf("\n");
    printf("The minimum unsigned short value is %d\n", 0);
    printf("The maximum unsigned short value from limits.h is %d\n", USHRT_MAX);
    printf("The maximum unsigned short value calculated is %d\n", (unsigned short)~0);
    printf("\n");
    printf("The minimum signed int value from limits.h is %d\n", INT_MIN);
    printf("The minimum signed int value calculated is %d\n", -(int)((unsigned int)~0 >> 1) - 1);
    printf("The maximum signed int value from limits.h is %d\n", INT_MAX);
    printf("The maximum signed int value calculated is %d\n", (int)((unsigned int)~0 >> 1));
    printf("\n");
    printf("The minimum unsigned int value is %d\n", 0);
    printf("The maximum unsigned int value from limits.h is %u\n", UINT_MAX);
    printf("The maximum unsigned int value calculated is %u\n", (unsigned int)~0);
    printf("\n");
    printf("The minimum signed long value from limits.h is %ld\n", LONG_MIN);
    printf("The minimum signed long value calculated is %ld\n", -(long)((unsigned long)~0 >> 1) - 1);
    printf("The maximum signed long value from limits.h is %ld\n", LONG_MAX);
    printf("The maximum signed long value calculated is %ld\n", (long)((unsigned long)~0 >> 1));
    printf("\n");
    printf("The minimum unsigned long value is %d\n", 0);
    printf("The maximum unsigned long value from limits.h is %lu\n", ULONG_MAX);
    printf("The maximum unsigned long value calculated is %lu\n", (unsigned long)~0);
    printf("\n");
    printf("The least significant float value from float.h is %e\n", FLT_MIN);
    printf("The most significant float value from float.h is %e\n", FLT_MAX);
    printf("\n");
    printf("The least significant double value from float.h is %e\n", DBL_MIN);
    printf("The most significant double value from float.h is %e\n", DBL_MAX);

    return 0;
}