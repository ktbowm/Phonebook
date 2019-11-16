//Lab 8: Phonebook
//Author: Kennedy Bowman
//Date: 2/27/14
//Section: 02

//Libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structure for contact information
typedef struct contact {
	char first[20];
	char last[20];
	char phone[15];
} c;

//Function prototypes
void Add(c **, int *);
void Delete(c **, int *);
void Show(c **, int *);
void SortFirst(c **, int *);
void SortLast(c **, int *);
void FindNum(c *, int *);
void RandomContact(c *, int *);
void DeleteAll(c **, int *);
void StoreAll(c *, int *);
void Retrieve(c **, int *);

int main () {
	//Allocating memory
	c *contacts;
	contacts = (c *) malloc(sizeof(c));
	
	//Checking if memory allocation was successful
	if (contacts == NULL) {
		printf("Out of memory!");
		return -3;
	}
	
	//Variable declarations and initializations
	int iSelection = 0;
	int iCounter = 0;
	int iSortSelection = 0;
	
	//Menu output to user
	do {
	printf("Phonebook\n\n");
	printf("1. Add contact\n");
	printf("2. Delete contact\n");
	printf("3. Show contacts\n");
	printf("4. Alphabetically sort contacts\n");
	printf("5. Find a phone number\n");
	printf("6. Randomly select a contact\n");
	printf("7. Delete all contacts\n");
	printf("8. Store all phonebook entries in a file\n");
	printf("9. Retrieve phonebook entries from a file\n");
	printf("10. Quit\n");
	printf("Enter your selection: ");
	scanf("%d", &iSelection);
	
	switch (iSelection) {
		//Adding a contact
		case 1:
			Add(&contacts, &iCounter);
			break;
		//Deleting a contact	
		case 2:
			Delete(&contacts, &iCounter);
			break;
		//Displaying the phonebook	
		case 3:
			Show(&contacts, &iCounter);
			break;
		//Sorting the phonebook alphabetically	
		case 4:
			printf("1. Sort alphabetically by first name\n");
			printf("2. Sort alphabetically by last name\n");
			printf("Enter your selection: ");
			scanf ("%d", &iSortSelection);
			
			//By first name
			if (iSortSelection == 1) {
				SortFirst(&contacts, &iCounter);
			}
			//By last name
			else if (iSortSelection == 2) {
				SortLast(&contacts, &iCounter);
			}
			else {
				printf("Invalid entry. Please try again.");	
			}
			break;
		//Finding a number
		case 5:
			FindNum(contacts, &iCounter);
			break;
		//Finding a random contact	
		case 6:
			RandomContact(contacts, &iCounter);
			break;
		//Deleting all contacts	
		case 7:
			DeleteAll(&contacts, &iCounter);
			break;
		//Storing all phonebook entries in a file
		case 8:
			StoreAll(contacts, &iCounter);
			break;
		//Retrieving entries from a file
		case 9:
			Retrieve(&contacts, &iCounter);
			break;
		//Exiting the program	
		case 10:
			printf("Goodbye!\n");
			break;
			
		default:
			printf("Invalid entry. Please enter a number between 1 and 10.\n");
	}
	
	} while (iSelection != 10);
	
	free(contacts);
	return 0;
	system("pause");
	
}

//Function definitions

//Adding a contact
void Add(c **tphonebook, int *iCount) {
	c *phonebook = *tphonebook;
	c *newphonebook = (c *) realloc(phonebook, sizeof(c) * (*iCount + 1));
	phonebook = newphonebook; 
	
	if (newphonebook == NULL) {
		printf("Out of memory!");
		return;
	}
	
	char fname[20] = {'\0'};
	char lname[20] = {'\0'};
	char num[15] = {'\0'};
	
	printf("Enter contact's first name: ");
	scanf("%s", fname);
	printf("Enter contact's last name: ");
	scanf("%s", lname);
	printf("Enter contact's phone number: ");
	scanf("%s", num);
	
	strcpy(phonebook[*iCount].first, fname);
	strcpy(phonebook[*iCount].last, lname);
	strcpy(phonebook[*iCount].phone, num);
	*iCount = *iCount + 1;	
	
	printf("Contact saved.\n");
}

//Deleting a contact
void Delete(c **tphonebook, int *iCount) {
	c *phonebook = *tphonebook;
	int x = 0;
	int y = 0;
	int iFound = 0;
	char fname[20] = {'\0'};
	char lname[20] = {'\0'};
	
	if (*iCount == 0) {
		printf("There are no contacts.");
	}
	else {
		printf("Enter the first name of the contact you wish to delete: ");
		scanf("%s", fname);
		printf("Enter the last name of the contact you wish to delete: ");
		scanf("%s", lname);
		
		for (x = 0; x < *iCount; x++ ) {
			if ((strcmp(phonebook[x].first, fname)== 0) && (strcmp(phonebook[x].last, lname)==0)) {
				iFound = 1;
				
				for(y = x; y < *iCount; y++ ){
					strcpy(phonebook[y].first, phonebook[y+1].first);
					strcpy(phonebook[y].last, phonebook[y+1].last);
					strcpy(phonebook[y].phone, phonebook[y+1].phone);	
				}
				
				if(*iCount != 1) {
					phonebook = realloc(phonebook,sizeof(c)*(*iCount - 1));
					*iCount = *iCount - 1;
				}
				
				printf("Contact deleted.\n");
			}
		}
	}
	
	if (iFound == 0) {
		printf("The contact you wish to delete could not be found.\n");
	}
}

//Displaying the phonebook
void Show(c **tphonebook, int *iCount) {
	c *phonebook = *tphonebook;
	int x = 0;
	
	if (*iCount == 0) {
		printf("There are no contacts.\n");
	}
	else {
		for (x = 0; x < *iCount; x++ ) {
			printf("%s", phonebook[x].first);
			printf(" %s", phonebook[x].last);
			printf("\t%s\n", phonebook[x].phone);
		}
	}
}

//Sorting alphabetically by first name
void SortFirst(c **tphonebook, int *iCount) {
	c *phonebook = *tphonebook;
	int x = 0;
	int iSwapped = 0;
	char tempfname[20] = {'\0'};
	char templname[20] = {'\0'};
	char tempnum[15] = {'\0'};
	
	do {
		iSwapped = 0;
		
		for (x = 0; x < (*iCount - 1); x++ ) {
			if (strcmp(phonebook[x].first, phonebook[x+1].first) > 0) {
				strcpy(tempfname, phonebook[x].first);
				strcpy(templname, phonebook[x].last);
				strcpy(tempnum, phonebook[x].phone);
				strcpy(phonebook[x].first, phonebook[x+1].first);
				strcpy(phonebook[x].last, phonebook[x+1].last);
				strcpy(phonebook[x].phone, phonebook[x+1].phone);
				strcpy(phonebook[x+1].first, tempfname);
				strcpy(phonebook[x+1].last, templname);
				strcpy(phonebook[x+1].phone, tempnum);
				iSwapped = 1;
			}
		}
	} while (iSwapped != 0);
	
	for (x = 0; x < *iCount; x++ ) {
		printf("%s", phonebook[x].first);
		printf(" %s", phonebook[x].last);
		printf("\t%s\n", phonebook[x].phone);
	}
}

//Sorting alphabetically by last name
void SortLast(c **tphonebook, int *iCount) {
	c *phonebook = *tphonebook;
	int x = 0;
	int iSwapped = 0;
	char tempfname[20] = {'\0'};
	char templname[20] = {'\0'};
	char tempnum[15] = {'\0'};
	
	do {
		iSwapped = 0;
		
		for (x = 0; x < (*iCount - 1); x++ ) {
			if (strcmp(phonebook[x].last, phonebook[x+1].last) > 0) {
				strcpy(tempfname, phonebook[x].first);
				strcpy(templname, phonebook[x].last);
				strcpy(tempnum, phonebook[x].phone);
				strcpy(phonebook[x].first, phonebook[x+1].first);
				strcpy(phonebook[x].last, phonebook[x+1].last);
				strcpy(phonebook[x].phone, phonebook[x+1].phone);
				strcpy(phonebook[x+1].first, tempfname);
				strcpy(phonebook[x+1].last, templname);
				strcpy(phonebook[x+1].phone, tempnum);
				iSwapped = 1;
			}
		}
	} while (iSwapped != 0);
	
	for (x = 0; x < *iCount; x++ ) {
		printf("%s", phonebook[x].first);
		printf(" %s", phonebook[x].last);
		printf("\t%s\n", phonebook[x].phone);
	}
}

//Finding a number
void FindNum(c *phonebook, int *iCount) {
	int x = 0;
	int iFound = 0;
	char fname[20] = {'\0'};
	char lname[20] = {'\0'};
	
	printf("Enter the first name of the contact whose number you want to find: ");
	scanf("%s", fname);
	printf("Enter the last name of the contact whose number you want to find: ");
	scanf("%s", lname);
	
	for (x = 0; x < *iCount; x++ ) {
		if (strcmp(fname, phonebook[x].first) == 0 && strcmp(lname, phonebook[x].last) == 0) {
			printf("%s", phonebook[x].first);
			printf(" %s", phonebook[x].last);
			printf("\t%s\n", phonebook[x].phone);
			iFound = 1;
		}
	}
	
	if (iFound == 0) {
		printf("Contact was not found.\n");
	}
}

//Finding a random contact
void RandomContact(c *phonebook, int *iCount) {
	int x = 0;
	
	srand(time(NULL));
	x = (rand() % (*iCount));
	
	if (*iCount == 0) {
		printf("There are no contacts.\n");
	}
	else {
		printf("%s", phonebook[x].first);
		printf(" %s", phonebook[x].last);
		printf("\t%s\n", phonebook[x].phone);
	}
}

//Deleting all contacts
void DeleteAll(c **tphonebook, int *iCount) {
	c *phonebook = *tphonebook;
	if (*iCount == 0) {
		printf("There are no contacts to delete.\n");
	}
	else {
		free(phonebook);
		*iCount = 0;
		printf("All contacts deleted.\n");
	
		phonebook = (c *) malloc(sizeof(c));
	
		if (phonebook == NULL) {
			printf("Out of memory!");
			return;
		}
	}
}

//Storing all phonebook entries in a file
void StoreAll(c *phonebook, int *iCount) {
	char file[100] = {'\0'};
	FILE *pWrite;
	int x = 0;
	
	printf("Enter file name to store entries in: ");
	scanf("%s", file);	
	
	if (file[0] == '\0') {
		strcpy(file, "phonebook.txt");
	}
	
	pWrite = fopen(file, "w");
	
	//Checking that the file opened
	if (pWrite == NULL) {
		printf("File cannot be opened.\n");
	}
	else {
		for (x = 0; x < *iCount; x++ ) {
			fprintf(pWrite, "%s %s %s\n", phonebook[x].first, phonebook[x].last, phonebook[x].phone);
		}
		fclose(pWrite);
	}
}

//Retrieving entries from a file
void Retrieve(c **tphonebook, int *iCount) {
	c *phonebook = *tphonebook;
	char file[100] = {'\0'};
	FILE *pRead;
	
	printf("Enter file name to read data from: ");
	scanf("%s", file);
	
	if (file[0] == '\0') {
		strcpy(file, "phonebook.txt");
	}
	
	pRead = fopen(file, "r");
	
	//Checking that the file opened
	if (pRead == NULL) {
		printf("File cannot be opened.\n");
	}
	else {
		while (!feof(pRead)) {
			c temp = {'\0','\0','\0'};
			fscanf(pRead, "%s%s%s", temp.first, temp.last, temp.phone);
			
			if(strcmp(temp.first,"\0") != 0){
				phonebook = (c *) realloc(phonebook, sizeof(c) * (*iCount + 1));
				if (phonebook == NULL) {
					printf("Out of memory!");
					return;
				}
				strcpy(phonebook[*iCount].first,temp.first);
				strcpy(phonebook[*iCount].last,temp.last);
				strcpy(phonebook[*iCount].phone,temp.phone);									
				*iCount = *iCount + 1;
			}//end of if
		}//end of while
		fclose(pRead);	
	}
	*tphonebook = phonebook;
}
