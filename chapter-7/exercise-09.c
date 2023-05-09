#include <stdio.h>

int isupperspace(char);
int isuppertime(char);

int main()
{
    char l = 'a', u = 'Z';

    printf("In isupperspace(), a comparison operation is used to return the result using comparisons.");
    printf(" This function does not require extra space. For isuppertime(), a table is used for faster");
    printf(" lookups to the answer. This requires the table of ASCII characters to be constructed");
    printf(" beforehand\n\n");

    printf("l = %c, u = %c\n", l, u);
    printf("isupperspace(l) = %d, isupperspace(u) = %d\n", isupperspace(l), isupperspace(u));
    printf("isuppertime(l) = %d, isuppertime(u) = %d\n", isuppertime(l), isuppertime(u));

    return 0;
}

int isupperspace(char c)
{
    return c >= 'A' && c <= 'Z';
}

int tbl[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
int isuppertime(char c)
{
    return tbl[c];
}