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
#include <regex.h>

struct addressListNode {
	char alias[12];
	int octet1, octet2, octet3, octet4;
	struct addressListNode *next;
};

struct addressListNode * head;
struct addressListNode * tail;

//given address and alias, returns reference to AddressListNode object
struct addressListNode* addressListNodeConstructor(char* address, char* alias) {
	struct addressListNode *newNode = (struct addressListNode*) malloc(sizeof(struct addressListNode));
	sscanf(address, "%d.%d.%d.%d", &(newNode -> octet1), &(newNode -> octet2), &(newNode -> octet3), &(newNode -> octet4));
	strcpy(newNode -> alias, alias);
	newNode -> next = NULL;
	return newNode;
}

void displayMenu() {
	printf("Select menu option: \n");
	printf("1) Add Address TODO\n"); 
	printf("2) Look up Address DONE\n");
	printf("3) Update Address TODO\n");
	printf("4) Delete Address TODO\n");
	printf("5) Display list DONE\n");
	printf("6) Display addresses for location DONE\n");
	printf("7) Save to file DONE\n");
	printf("8) Quit\n");
}

//Opens text file and parses into AddressList
void parseAddressFile() {
	char lineBuffer[100];
	char addressBuffer[20];
	char aliasBuffer[12];
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

//Returns reference to a node with a specified alias if it exists, returns null otherwise
struct addressListNode *searchForAndReturnNodeAlias(char* alias) {
	struct addressListNode* curr = head;
	
	while(curr -> next != NULL) {
		if(strcmp(curr -> alias, alias) == 0) {
			return curr;
		}
		curr = curr -> next;
	}

	if(strcmp(curr -> alias, alias) == 0) {
		return curr;
	}
	return NULL;
}

//Returns reference to a node with a specified address if it exists, returns null otherwise
struct addressListNode *searchForAndReturnNodeAddress(int octet1, int octet2, int octet3, int octet4) {
	struct addressListNode* curr = head;
	
	while(curr -> next != NULL) {
		if((curr -> octet1 == octet1) && (curr -> octet2 == octet2) && (curr -> octet3 == octet3) && (curr -> octet4 == octet4)) {
			return curr;
		}
		curr = curr -> next;
	}

	if((curr -> octet1 == octet1) && (curr -> octet2 == octet2) && (curr -> octet3 == octet3) && (curr -> octet4 == octet4)) {
		return curr;
	}
	return NULL;
}

//Retreives user inputted alias and displays address if it exists in the list
void lookUpAddress() {
	char aliasBuffer[12];

	while(true) {
		printf("Enter the alias for lookup: \n");
		fgets(aliasBuffer, 12, stdin);

		//Fgets input formatting check
		if(strlen(aliasBuffer) < 2 || strlen(aliasBuffer) > 11 || strchr(aliasBuffer, '\n') == NULL) {
			printf("Enter a string that corresponds to the format.\n");
			if(strchr(aliasBuffer, '\n') == NULL) {
				int c;
				while((c = fgetc(stdin)) != '\n' && c != EOF);
			}
			continue;
		}
		else {
			break;
		}
	}
	struct addressListNode * node = searchForAndReturnNodeAlias(strtok(aliasBuffer,"\n"));
	if (node != NULL) {
		printf("Address of alias %s is: %d.%d.%d.%d\n", node -> alias, node -> octet1, node -> octet2, node -> octet3, node -> octet4);

	}
	else {
		printf("Alias not found.\n");
	}
}

//THIS ONES FUCKED UP, NEED TO IMPLEMENT REGEX CHECK
void addAddress() {
	char aliasBuffer[12];
	char addressBuffer[16];
	regex_t regex;
	int reti;

	reti = regcomp(&regex, "\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}", 0);

	//Get alias
	while(true) {
		printf("Enter the alias for lookup: \n");
		fgets(aliasBuffer, 12, stdin);

		//Fgets input formatting check
		if(strlen(aliasBuffer) < 2 || strlen(aliasBuffer) > 11 || strchr(aliasBuffer, '\n') == NULL) {
			printf("Enter a number that corresponds to the menu option.\n");
			if(strchr(aliasBuffer, '\n') == NULL) {
				int c;
				while((c = fgetc(stdin)) != '\n' && c != EOF);
			}
			continue;
		}
		else {
			break;
		}
	}

	//Get address,  USE DISPLAY ADDRESSES TO GRAB OCTETS
	while(true) {
		printf("Enter the address for lookup: \n");
		fgets(addressBuffer, 16, stdin);

		//Fgets input formatting check
		reti = regexec(&regex, addressBuffer, 0, NULL, 0);
		if(reti == REG_NOMATCH || strlen(addressBuffer) < 2 || strlen(addressBuffer) > 11 || strchr(addressBuffer, '\n') == NULL) {
			printf("Enter a number that corresponds the address format.\n");
			if(strchr(addressBuffer, '\n') == NULL) {
				int c;
				while((c = fgetc(stdin)) != '\n' && c != EOF);
			}
			continue;
		}
		else {
			break;
		}
	}
		//sscanf(lineBuffer, "%s %s", addressBuffer, aliasBuffer);

	struct addressListNode* node1 = searchForAndReturnNodeAlias("jet2");
	struct addressListNode* node2 = searchForAndReturnNodeAddress(131,251,95,221);
	if(node1 == NULL && node2 == NULL) {
		struct addressListNode* newNode = addressListNodeConstructor("111.111.111.111", "test");
		newNode -> next = head;
		head = newNode;
	}
	else {
		printf("Value already exists within address list.\n");
	}
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//THIS ONES FUCKED UP,  
void updateAddress() {
	struct addressListNode* node;
	char aliasBuffer[12];

	while(true) {
		printf("Enter the alias for lookup: \n");
		fgets(aliasBuffer, 12, stdin);

		//Fgets input formatting check
		if(strlen(aliasBuffer) < 2 || strlen(aliasBuffer) > 11 || strchr(aliasBuffer, '\n') == NULL) {
			printf("Enter a string that corresponds to the format.\n");
			if(strchr(aliasBuffer, '\n') == NULL) {
				int c;
				while((c = fgetc(stdin)) != '\n' && c != EOF);
			}
			continue;
		}
		else {
			break;
		}
	}

	node = searchForAndReturnNodeAlias(strtok(aliasBuffer,"\n"));
	printf("Found node %s, with address %d.%d.%d.%d\n",node -> alias, node -> octet1, node -> octet2, node -> octet3, node -> octet4);
	printf("Enter address to replace: \n");
	//USE DISPLAY ADDRESSES TO GET INDIVIDUAL OCTETS

}

//REGEX AND GET NODE BEFORE ALIAS NODE FOR 'NEXT' POINTER MANIPULATION
void deleteAddress() {

}

//Prints list 
void displayList() {
	struct addressListNode* curr = head;
	
	while(curr -> next != NULL) {
		printf("Alias: %s, Address: %d.%d.%d.%d\n", curr -> alias, curr -> octet1, curr -> octet2, curr -> octet3, curr -> octet4);
		curr = curr -> next;
	}
	printf("Alias: %s, Address: %d.%d.%d.%d\n", curr -> alias, curr -> octet1, curr -> octet2, curr -> octet3, curr -> octet4);
}

//Prompts user for address location and displays corresponding aliases
void displayAddresses() {
	char octetBuffer[5];
	int octet1;
	int octet2;

	while(true) {
		printf("Enter the first octet: \n");
		fgets(octetBuffer, 5, stdin);
		printf("input was %s, length of %d\n", octetBuffer, (int) strlen(octetBuffer));
		//Fgets input formatting check
		if(strlen(octetBuffer) < 2 || strlen(octetBuffer) > 4 || strchr(octetBuffer, '\n') == NULL) {
			printf("Enter a number that corresponds to the format.\n");
			if(strchr(octetBuffer, '\n') == NULL) {
				int c;
				while((c = fgetc(stdin)) != '\n' && c != EOF);
			}
			continue;
		}
		else if(atoi(strtok(octetBuffer,"\n")) > 255 || atoi(strtok(octetBuffer,"\n")) < 0) {
			printf("Enter a number between 0 and 255.\n");
			continue;
		}
		else {
			octet1 = atoi(strtok(octetBuffer,"\n"));
			break;
		}
	}

	while(true) {
		printf("Enter the second octet: \n");
		fgets(octetBuffer, 5, stdin);

		//Fgets input formatting check
		if(strlen(octetBuffer) < 2 || strlen(octetBuffer) > 4 || strchr(octetBuffer, '\n') == NULL) {
			printf("Enter a number that corresponds to the format.\n");
			if(strchr(octetBuffer, '\n') == NULL) {
				int c;
				while((c = fgetc(stdin)) != '\n' && c != EOF);
			}
			continue;
		}
		else if(atoi(strtok(octetBuffer,"\n")) > 255 || atoi(strtok(octetBuffer,"\n")) < 0) {
			printf("Enter a number between 0 and 255");
			continue;
		}
		else {
			octet2 = atoi(strtok(octetBuffer,"\n"));
			break;
		}
	}

	//Search for address
	struct addressListNode* curr = head;
	bool existsFlag = false;
	while(curr -> next != NULL) {
		if(curr -> octet1 == octet1 && curr -> octet2 == octet2) {
			existsFlag = true;
			printf("Match found, alias: %s\n", curr -> alias);
		}
		curr = curr -> next;
	}
	if(curr -> octet1 == octet1 && curr -> octet2 == octet2) {
		existsFlag = true;
		printf("Match found, alias: %s\n", curr -> alias);
	}
	if(existsFlag) {
		return;
	}
	printf("No matches for address location found.\n");

}

//Save list items to text file
void saveToFile() {
	FILE *fptr;
	char nameBuffer[101];
	
	//Prompt user for filename, check for illegal characters
	while(true) {	
		printf("Enter the filename to save: \n");
		fgets(nameBuffer, 101, stdin);

		//Fgets input formatting check
		if(strlen(nameBuffer) < 2 || strlen(nameBuffer) > 97 || strchr(nameBuffer, '\n') == NULL || strchr(nameBuffer, '/') != NULL) {
			printf("Enter a valid filename.\n");
			if(strchr(nameBuffer, '\n') == NULL) {
				int c;
				while((c = fgetc(stdin)) != '\n' && c != EOF);
			}
			continue;
		}
		else {
			break;
		}
	}

	//Write to file
	fptr = fopen(strncat(strtok(nameBuffer, "\n"), ".txt", 4), "w+");
	struct addressListNode* curr = head;
	
	while(curr -> next != NULL) {
		fprintf(fptr, "%d.%d.%d.%d %s\n", curr -> octet1, curr -> octet2, curr -> octet3, curr -> octet4, curr -> alias);
		curr = curr -> next;
	}
	fprintf(fptr, "%d.%d.%d.%d %s\n", curr -> octet1, curr -> octet2, curr -> octet3, curr -> octet4, curr -> alias);
	fclose(fptr);
}

//Frees memory
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

int main() {
	char menuInputBuffer[2];

	parseAddressFile();

	while(true) {
		displayMenu();

		fgets(menuInputBuffer, 2*sizeof(menuInputBuffer), stdin);

		//Fgets input formatting check
		if(strlen(menuInputBuffer) != 2 || strchr(menuInputBuffer, '\n') == NULL) {
			printf("Enter a number that corresponds to the menu option.\n");
			if(strchr(menuInputBuffer, '\n') == NULL) {
				int c;
				while((c = fgetc(stdin)) != '\n' && c != EOF);
			}
			continue;
		}

		//Convert string to int 
		int menuInput = atoi(menuInputBuffer);

		switch(menuInput) {
			case 1:
				addAddress();
				break;
			case 2:
				lookUpAddress();
				break;
			case 3:
				updateAddress();
				break;
			case 4:
				printf("4 lol\n");
				break;
			case 5:
				displayList();
				break;
			case 6:
				displayAddresses();
				break;
			case 7:
				saveToFile();
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