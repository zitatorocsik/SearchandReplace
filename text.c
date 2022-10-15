#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//variables defined outside scope of this file
extern char *targetString;
extern char *filesChanged;

void readAndReplace(char* filename) {

    //create filepointer to file with path in parameter
    FILE* fpointer;

    //open to read and write
    fpointer = fopen(filename, "r+");

    //file error checking
    if (fpointer == NULL) {
        printf("No such file.\n");
        return;
    }

    //pointer to end of file
    fseek(fpointer, 0L, SEEK_END);
    // calculating the size of the file
    long int size = ftell(fpointer);

    //set pointer to beginning of file
    fseek(fpointer, 0L, SEEK_SET);

    //create string to hold file contents
    char fileContents[size*2];

    //string to hold lines of file
    char fileLine[255];

    //copy lines from file to fileContents, line by line
    while (fgets(fileLine, 255, fpointer) != NULL) {
        strcat(fileContents, fileLine);
    }

    //pointer to first character of target string occurence in fileCOntents
    char *foundptr;
    int timesChanged = 0;

    do {
        //find first occurence of targetString
        foundptr = strstr(fileContents, targetString);

        //if there is an occurence, increment timeChanged and change the targetString in fileContents to uppercase
        if (foundptr != NULL) {
            timesChanged = timesChanged + 1;
            for (int i = 0; i < strlen(targetString); i++) {
                *foundptr = toupper(*foundptr);
                foundptr = foundptr+1;
            }
        }
        //if found, go again to get all occurences of target string
    } while (foundptr != NULL);

    //convert timesChanged to character
    char buffer[sizeof(timesChanged)];
    sprintf(buffer, "%d", timesChanged);
    char number[sizeof(char)*2];
    strcpy(number, buffer);

    //if we did change the fileContents
    if (timesChanged != 0) {
        //reallocating size of filesChanges string so I can add the changed file
        int size = sizeof(filename) + sizeof(number) + (sizeof("\t")*4) + 100;
        filesChanged = (char *) realloc(filesChanged, size);

        //add number of updates to file
        strcat(filesChanged, number);
        strcat(filesChanged, "\t\t");

        //add which file was changed
        strcat(filesChanged, filename+2);
        strcat(filesChanged, "\t\t\n");
    }

    //set file pointer to beginning of file so I can overwrite contents
    fseek(fpointer, 0L, SEEK_SET);
    //print changed contents onto file
    fprintf(fpointer, fileContents);

    //close file pointer
    fclose(fpointer);
    return;
}