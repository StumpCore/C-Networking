#include <stdio.h>
char line[100];
int value;

int main()
{
    printf("Enter a value:");

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &value);
    
    printf("Twice %d is %d\n", value, value*2);
    return(0);
}
