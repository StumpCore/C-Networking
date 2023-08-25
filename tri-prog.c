#include <stdio.h>

//Triangle Clalucation -- Computes area of a Triangle

float triangle(float width, float height)
{
    float area; //Area of the triangle

    area = width * height / 2.0;
    return(area);
}

int main()
{
    printf("Triangle #1 %f\n", triangle(1.3, 8.3));
    printf("Triangle #1 %f\n", triangle(4.8, 9.8));
    printf("Triangle #1 %f\n", triangle(1.2, 2.0));
    return(0);
}
