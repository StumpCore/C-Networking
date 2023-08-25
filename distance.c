#include <stdio.h>
#include <math.h>

char line[20];
float point_f_X;
float point_f_Y;
float point_s_X;
float point_s_Y;
float distance;
float distance_sqrt;

int main() 
{
    /* Get the first point */ 
    printf("Please enter x1 and y1 (x y): ");
    fgets(line,sizeof(line), stdin);
    sscanf(line, "%f %f", &point_f_X, &point_f_Y);
   
    /* Get the second point*/
    printf("Please enter x1 and y1 (x y): ");
    fgets(line,sizeof(line), stdin);
    sscanf(line, "%f %f", &point_s_X, &point_s_Y);

    printf("Point 1: %f %f\n", point_f_X, point_f_Y);
    printf("Point 2: %f %f\n", point_s_X,point_s_Y);
    
    distance = sqrtf(powf(point_s_X-point_f_X,2)+powf(point_s_Y-point_f_Y,2));
    distance_sqrt = powf(point_s_X-point_f_X,2)+powf(point_s_Y-point_f_Y,2);

    printf("The distance between Point 1 (%f/%f) and Point 2 (%f/%f):\n", 
	    point_f_X, point_f_Y,
	    point_s_X, point_s_Y);
    printf("Squared Distance: %f\n", distance_sqrt);
    printf("Real Distance: %f\n", distance);

    return(0);  

}
