/*
 * Author: Ethan Trott
 * Purpose: A primitive, integer-based, FIFO Queue
 * Language: C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CAP 10						//the capacity of the queue

int push(int val, int a[], int size, int capacity){
	/* Purpose: Push a new integer to the queue
	 * Parameters:	val- the integer to be pushed
	 * 		a- the array to hold the value
	 * 		size- the current queue size
	 * 		capacity- the queue's capacity
	 * Return Value: the size of the queue after insertion
	 */

	if (size == capacity){			//if the array is full
		int lastVal = a[size-1];	//get the last value

		//display the overflowed value
		printf("Overflow: removed value %d\n", lastVal);
	}else{
		size++;				//increase the size
	}

	for (int i = size - 1; i>0; i--){	//for the last element to the second:
		a[i] = a[i-1];			//replace with the one that comes before it
	}
	a[0] = val;				//set the first index to the newest value
	return size;
}

void print(int a[], int size){
	/* Purpose: Print the contents of the queue
	 * Parameters:	a- the array to hold the values
	 * 		size- the size of the queue
	 * Return Value: none
	 */

	for (int i=0; i<size; i++){		//for each item:
		printf("%d", a[i]);			//print it to the end
		if (i != size-1) printf(", ");		//add commas where necessary
		else printf("\n");			//add a new line at the end
	}
}

void getEntered(char *cmd, int *val){
	/* Purpose: separate the entered command and value
	 * Parameters:	*cmd- the pointer to hold the command
	 * 		*val- the pointer to hold the value
	 * Return Value: none
	 */

	char enteredString[10];				//buffer to hold the entered string
	fgets(enteredString, 10, stdin);		//store the entered string

	if (strchr(enteredString, ' ')){		//if there is a space in the command:
		const char token[2] = " ";		//the separator for the string
		char* subCmd = strtok(enteredString, token);	//the substring before the space
		strcpy(cmd, subCmd);				//store the substring
	
		char* subVal= strtok(NULL, token);		//the substring after the space
		
		if (strlen(subVal)>1){				//if the substring is longer than 1:
			int isInt = 1;				//true if substring is an integer

			for (int i=0; i<strlen(subVal)-1; i++)	//for each character (except \n):
				if (!isdigit(subVal[i])) isInt = 0;	//change the boolean properly

			if (isInt)					//if it's an integer:
				*val = atoi(subVal);			//store the substring
		}
	}else{							//if there's no space:
		const char token[2] = "\n";
		char *subCmd = strtok(enteredString, token);	//get the string before the new line
		strcpy(cmd, subCmd);				//store the substring
	}
}

int main(){
	int a[CAP] = {};					//the array to hold the queue values
	int size = 0;						//the size of the queue
	
	char enteredCmd[10];					//the last command entered
	int enteredVal;						//the last value entered
	
	//---Input, Processing, and Output---
	printf("Enter command (push, print, or quit): ");	//prompt for input
	getEntered(enteredCmd, &enteredVal);			//get input
	while (strcmp(enteredCmd, "quit")){			//until quit is entered:
		if (!strcmp(enteredCmd, "push")) 		//if push is entered
			//push the value and get the size
			size = push(enteredVal, a, size, CAP);	
		else if (!strcmp(enteredCmd, "print"))		//if print is entered:
		       	print(a, size);				//print the queue
		else 						//if an unknown command is entered:
			//display a warning and move on
			printf("Unrecognized command, please try push, print, or quit.\n");

		printf("Enter command (push, print, or quit): ");	//prompt for input
		getEntered(enteredCmd, &enteredVal);			//get input
	}

	return 0;
}
