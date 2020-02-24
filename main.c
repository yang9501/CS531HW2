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

struct addressListNode {
	char alias[11];
	int octet1, octet2, octet3, octet4;
	struct addressListNode *next;
};

struct addressListNode * head;
struct addressListNode * tail;

//THIS FUNCTION DOES NOT CHECK INPUT FORMAT CORRECTNESS.  DO THAT BEFORE CALLING THIS FUNCTION
struct addressListNode* addressListNodeConstructor(char* address, char* alias) {
	struct addressListNode *newNode = (struct addressListNode*) malloc(sizeof(struct addressListNode));
	sscanf(address, "%d.%d.%d.%d", &(newNode -> octet1), &(newNode -> octet2), &(newNode -> octet3), &(newNode -> octet4));
	strcpy(newNode -> alias, alias);
	newNode -> next = NULL;
	return newNode;
}

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

void parseAddressFile() {
	char lineBuffer[100];
	char addressBuffer[20];
	char aliasBuffer[11];
	bool firstNode = true;

	FILE *fp = fopen("CS531_Inet.txt", "r");

	//Read line-by-line
	while(fgets(lineBuffer, 100, fp) != NULL) {
		sscanf(lineBuffer, "%s %s", addressBuffer, aliasBuffer);
		struct addressListNode * newNode = addressListNodeConstructor(addressBuffer, aliasBuffer);
		printf("%s\n", newNode -> alias);
		if(firstNode == true) {
			head = newNode;
			tail = newNode;

			firstNode = false;
		}
		else {
			tail -> next = newNode;
			tail = newNode;
		}
	}
}

struct addressListNode *searchForAndReturnAddress() {

}

void lookUpAddress() {
	//STUBBED
	struct addressListNode * node = searchForAndReturnAddress;
}

void addAddress() {
	//use lookUpAddress() to check node duplicity
}

void updateAddress() {

}

void deleteAddress() {

}

void displayList() {
	struct addressListNode* curr = head;
	
	while(curr -> next != NULL) {
		printf("Alias: %s, Address: %d.%d.%d.%d\n", curr -> alias, curr -> octet1, curr -> octet2, curr -> octet3, curr -> octet4);
		curr = curr -> next;
	}
	printf("Alias: %s, Address: %d.%d.%d.%d\n", curr -> alias, curr -> octet1, curr -> octet2, curr -> octet3, curr -> octet4);
}

void displayAddresses() {

}

void saveToFile() {

}

void memoryCleanup() {
	struct addressListNode* curr = head;
	struct addressListNode* toDelete;

	printf("Freeing memory.\n");

	while(curr -> next != NULL) {
		toDelete = curr;
		curr = curr -> next;
		free(toDelete);
	}
	free(tail);
}

//ASSUME THE DATA FILE HAS NO DUPLICATES

int main() {
	char menuInputBuffer[2];

	parseAddressFile();

	while(true) {
		displayMenu();

		fgets(menuInputBuffer, 2*sizeof(menuInputBuffer), stdin);

		//Fgets input fuckery
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
				displayList();
				break;
			case 6:
				printf("6 lol\n");
				break;
			case 7:
				printf("7 lol\n");
				break;
			case 8:
				memoryCleanup();
				return 0;
			default: 
				printf("Enter a number that corresponds to the menu option.\n");
				continue;
		}
	}

	return 0;
}