/*
Author: Dylan Skokan

Sources Used:
https://www.tutorialspoint.com/eof-getc-and-feof-in-c
https://www.tutorialspoint.com/cprogramming/c_file_io.htm
https://www.tutorialspoint.com/cprogramming/c_error_handling.htm
https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c/23840699#:~:text=You%20can%20use%20itoa(),to%20convert%20any%20value%20beforehand.
http://www.crasseux.com/books/ctutorial/String-overflows-with-scanf.html#:~:text=Fortunately%2C%20it%20is%20possible%20to,for%20more%20information%20on%20malloc%20.)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
FUNCTION: readFile

DESCRIPTION:
Reads a specified file of integers separated by newlines, and populates an array with these integers.

PARAMETERS:
inputFile: the name and location of the input file.
numArrPtr: a pointer to the array of integers.
numSizePtr: a pointer to the size of the array.
maxLineLength: the maximum length allowed for each line.

ERROR HANDLING:
The program will exit from this function if:
- The file does not exist or is inaccessible.
- The file contains more than 100 integers.
- There is a line with a negative symbol that is not at the start of the line or there is a non-digit character in a line.
- The given input file is empty.
*/
void readFile(char inputFile[], int *numArrPtr, int *numSizePtr, int maxLineLength){
	FILE *filePtr = fopen(inputFile, "r");
	char currLine[maxLineLength];
	int i = 0, j = 0;
	
	if(filePtr == NULL){
      	fprintf(stderr, "Failed accessing input file, exiting...");
      	exit(-1);
	}
	
    while (fgets(currLine, maxLineLength, filePtr) != NULL){
    	if(i > 99){
      		fprintf(stderr, "Greater than 100 integers in file, exiting...");
      		exit(-1);
      	}
      	for(j = 0; j < strlen(currLine) - 1; j++){
      		if(!isdigit(currLine[j]) && !(j == 0 && currLine[j] == '-')) {
      			fprintf(stderr, "Invalid line at line %d, exiting...", i + 1);
      			exit(-1);
			 }
		}
    	numArrPtr[i++] = atoi(currLine);
	}
	
	if(i == 0){
      	fprintf(stderr, "Empty file, exiting...");
      	exit(-1);
	}
	
    *numSizePtr = i;
    
    fclose(filePtr);
}

/*
FUNCTION: sort

DESCRIPTION:
Sorts an array of integers using a selection sort algorithm.

PARAMETERS:
numArrPtr: a pointer to the array of integers.
numSizePtr: a pointer to the size of the array.

ERROR HANDLING:
The program will exit from this function if:
- The sorting algorithm did not sort anything by the end of the algorithm.
*/
void sort(int *numArrPtr, int *numSizePtr){
	int minIndex = numArrPtr[0], sortChecker = 0, i = 0, j = 0;

	for(i = 0; i < *numSizePtr; i++){
		minIndex = i;
		for(j = i; j < *numSizePtr; j++){
			if(numArrPtr[minIndex] > numArrPtr[j]){
				minIndex = j;
				sortChecker = 1;
			}
		}
		int tempNum = numArrPtr[i];
		numArrPtr[i] = numArrPtr[minIndex];
		numArrPtr[minIndex] = tempNum;
	}
	
	if(sortChecker == 0){
		fprintf(stderr, "Input file already sorted, exiting...");
      	exit(-1);
	}
}

/*
FUNCTION: writeFile

DESCRIPTION:
Writes an array of integers to a specified file separated by new lines to match the format of the input file.
It will create the file if it does not exist.

PARAMETERS:
outputFile: the name and location of the output file.
numArrPtr: a pointer to the array of integers.
numSizePtr: a pointer to the size of the array.
maxLineLength: the maximum length allowed for each line.
*/
void writeFile(char outputFile[], int *numArrPtr, int *numSizePtr, int maxLineLength){
	FILE *filePtr = fopen(outputFile, "w");
	char currLine[maxLineLength];
	
    for(int i = 0; i < *numSizePtr; i++){
    	sprintf(currLine, "%d\n", numArrPtr[i]);
		fprintf(filePtr, currLine);
	}
	
	fclose(filePtr);
}

/*
FUNCTION: main

DESCRIPTION:
Sorts integers separated by newlines from a specified file and writes the sorted integers to a specified output file.
Accepts user input from the command line or from the program prompt.
*/
int main(int argc, char *argv[]) {
	int numsArray[99], numsSize = 0, maxLineLength = 500;
	
	if(argv[1] == NULL || argv[2] == NULL) {
		char inputFile[maxLineLength], outputFile[maxLineLength];
		
		printf("Specify file with unsorted integers:\n");
		scanf("%s", inputFile);
		readFile(inputFile, numsArray, &numsSize, maxLineLength);
		
		sort(numsArray, &numsSize);
		
		printf("Specify file to hold sorted integers:\n");
		scanf("%s", outputFile);
		writeFile(outputFile, numsArray, &numsSize, maxLineLength);
	} 
	else {
		readFile(argv[1], numsArray, &numsSize, maxLineLength);
		sort(numsArray, &numsSize);
		writeFile(argv[2], numsArray, &numsSize, maxLineLength);
	}
	
	printf("Program successful");
	return 0;
}