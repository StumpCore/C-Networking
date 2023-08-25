#include <math.h>
#include <stdio.h>

signed int grade;
char modi;
char line[10];

int main()
{
    printf("Program to calculate Grade.\n");
    printf("Enter -1 to close.\n");
    
    grade = 0;

    while(grade != -1){
	printf("Please enter Score: ");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%d",&grade);
		
	if (grade <=60) {
	    printf("Grade: F\n");
	}else if (grade >60 && grade<=70) {
	    if(grade%60<3){
		modi = '-';
	    }else if (grade%60>=8) {
		modi = '+';
	    } else {
		modi = ' ';
	    }
	    printf("Grade: %cD\n",modi);
	}else if (grade >70 && grade<=80) {
	    if(grade%70<3){
		modi = '-';
	    }else if (grade%70>=8) {
		modi = '+';
	    } else {
		modi = ' ';
	    }
	    printf("Grade: %cC\n",modi);
	}else if (grade >80 && grade<=90) {
	    if(grade%80<3){
		modi = '-';
	    }else if (grade%80>=8) {
		modi = '+';
	    } else {
		modi = ' ';
	    }
	    printf("Grade: %cB\n",modi);
	}else {
	    if(grade%90<3){
		modi = '-';
	    }else if (grade%90>=8) {
		modi = '+';
	    } else {
		modi = ' ';
	    }
	    printf("Grade: %cA\n",modi);
	}
    }
    return(0);

}
