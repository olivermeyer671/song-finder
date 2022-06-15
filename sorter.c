#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int MAX_NUMBER_STRINGS;
int MAX_STRING_SIZE;




//gathers the max line length and number of lines in a file
void fileDimensions(char * file)
{
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen(file, "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);

        MAX_NUMBER_STRINGS = 0;
	MAX_STRING_SIZE = 0;
        while ((read = getline(&line, &len, fp)) != -1) {
                if (read > MAX_STRING_SIZE){
			MAX_STRING_SIZE = read;
		}
                MAX_NUMBER_STRINGS++;
        }
	MAX_STRING_SIZE++;
        fclose(fp);
        if (line)
                free(line);
}



//scans the lines of a file into an array of strings
void scanFile(char * file, char arr[MAX_NUMBER_STRINGS][MAX_STRING_SIZE])
{
	FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;


        fp = fopen(file, "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);
	int count = 0;
        while ((read = getline(&line, &len, fp)) != -1) {
                strcpy(arr[count], line);
		count++;
        }

        fclose(fp);
        if (line)
                free(line);

	//printf("\n\n\nSONGS (%d):\n\n", MAX_NUMBER_STRINGS);
        //for (int i = 0; i < MAX_NUMBER_STRINGS; i++){
                //printf("%s", arr[i]);
        //}
}


//sorts an array of strings (lines) alphabetically
void sortArrayByName(char arr[MAX_NUMBER_STRINGS][MAX_STRING_SIZE], char temp[MAX_STRING_SIZE])
{
        bool swap = true;
        while (swap == true){
                swap = false;
                for (int i = 1; i < MAX_NUMBER_STRINGS; i++){
                        if (strcmp(arr[i-1], arr[i]) > 0){
                                strcpy(temp, arr[i]);
                                strcpy(arr[i], arr[i-1]);
                                strcpy(arr[i-1], temp);
                                swap = true;
                        }
                }
        }
	//printf("\n\n\nSONGS (%d) SORTED BY NAME:\n\n", MAX_NUMBER_STRINGS);
        //for (int i = 0; i < MAX_NUMBER_STRINGS; i++) {
                //printf("%s", arr[i]);
        //}
}


//sorts an array of strings (lines) alphabetically by the chord listed between parentheses on each line
void sortArrayByChord(char arr[MAX_NUMBER_STRINGS][MAX_STRING_SIZE], char temp[MAX_STRING_SIZE], char chordA[MAX_STRING_SIZE], char chordB[MAX_STRING_SIZE])
{
        bool swap = true;
        while (swap == true){
                swap = false;
                for (int i = 1; i < MAX_NUMBER_STRINGS; i++){
                	sscanf(arr[i-1], "%*[^(]%*1c%[^)]", chordA);
			sscanf(arr[i], "%*[^(]%*1c%[^)]", chordB);

			if (strcmp(chordA, chordB) > 0){
                                strcpy(temp, arr[i]);
                                strcpy(arr[i], arr[i-1]);
                                strcpy(arr[i-1], temp);
                                swap = true;
                        }
                }
        }
	//printf("\n\n\nSONGS (%d) SORTED BY STARTING CHORD:\n\n", MAX_NUMBER_STRINGS);
        //for (int i = 0; i < MAX_NUMBER_STRINGS; i++) {
                //printf("%s", arr[i]);
        //}
	//printf("\n\n\n\n");
}



//writes the contents of an array of strings (lines) to a file
void writeToFile(char * file, char arr[MAX_NUMBER_STRINGS][MAX_STRING_SIZE])
{
        FILE * fp;
        fp = fopen(file, "w");
        if (fp == NULL)
                exit(EXIT_FAILURE);
	for(int i = 0; i < MAX_NUMBER_STRINGS; i++){
		fprintf(fp, "%s", arr[i]);
	}
        fclose(fp);
}


//takes input from 'songs.txt' and sorts the lines alphabetically, then outputs the sorted lines into 'sorted.txt'
int main(void)
{
	fileDimensions("songs.txt");
        char arr[MAX_NUMBER_STRINGS][MAX_STRING_SIZE];
	char temp[MAX_STRING_SIZE];
	char chordA[MAX_STRING_SIZE];
	char chordB[MAX_STRING_SIZE];
	scanFile("songs.txt", arr);
	sortArrayByName(arr, temp);
	//sortArrayByChord(arr, temp, chordA, chordB);
	writeToFile("sorted.txt", arr);
	exit(EXIT_SUCCESS);
}
