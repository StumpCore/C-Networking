#include <stdio.h>
int socialID;
int dateBirth1;
int dateBirth2;
int dateBirth3;
char char1;
char char2;
char char3;

int main() {
	socialID =123143231;
	char1 = 'B';
	char2 = 'E';
	char3 = 'N';
	
	dateBirth1 = 20;
	dateBirth2 = 1;
	dateBirth3 = 1960;


	printf("Hello, my name is %c%c%c and I am born on %d.%d.%d. My social Security number is %d",
			char1,char2,char3, dateBirth1, dateBirth2,dateBirth3, socialID);

}

