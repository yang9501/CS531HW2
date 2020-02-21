/*
CS531 HW2
by Justin Yang
jyang52
G01135050
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct listNode {
	char name[10];
	int octet1, octet2, octet3, octet4;
};

void displayMenu() {
	printf("Select menu option: \n");
	printf("1) Add Address\n");
	printf("2) Look up Address\n");
	printf("3) Update Address\n");
	printf("4) Delete Address\n");
	printf("5) Display list\n");
	printf("6) Display addresses for location\n");
	printf("7) Save to file\n");
	printf("8) Quit\n");
}

int main() {
	char menuInputBuffer[2];

	while(true) {
		displayMenu();

		fgets(menuInputBuffer, 2*sizeof(menuInputBuffer), stdin);

		//Fgets fuckery
		if(strlen(menuInputBuffer) != 2 || strchr(menuInputBuffer, '\n') == NULL) {
			printf("Enter a number that corresponds to the menu option.\n");
			if(strchr(menuInputBuffer, '\n') == NULL) {
				int c;
				while((c = fgetc(stdin)) != '\n' && c != EOF);
			}
			continue;
		}

		int menuInput = atoi(menuInputBuffer);

		printf("menuInput = %d\n", menuInput);
		switch(menuInput) {
			case 1:
				printf("1 lol\n");
				break;
			case 2:
				printf("2 lol\n");
				break;
			case 3:
				printf("3 lol\n");
				break;
			case 4:
				printf("4 lol\n");
				break;
			case 5:
				printf("5 lol\n");
				break;
			case 6:
				printf("6 lol\n");
				break;
			case 7:
				printf("7 lol\n");
				break;
			case 8:
				printf("8 lol\n");
				return 0;
			default: 
				printf("Enter a number that corresponds to the menu option.\n");
				continue;
		}


	}

	return 0;
}