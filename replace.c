#include <stdio.h>
#include <stdlib.h>

//my header files
#include "report.h"
#include "traversal.h"

//global variables for target string (cmd line arg) and info on files changed, so other files can access it
char *targetString;
char *filesChanged;


int main(int argc, char *argv[]) {
    
    //make sure that there is a target string in command line argument
    if (argc == 2) {
        targetString = argv[1];

        //filesChanged is empty right now, reallocation happens in a loop so have to malloc here
        filesChanged = (char*) malloc(0);

        //begin search for text files in current directory, function in traversal.c
        searchDirectory(".");

        //once files have been searched and changed, generate report of changes, function in report.c
        createReport();

        //free allocated space for filesChanged to prevent memory leak
        free(filesChanged);


    //no command line argument.
    } else if (argc == 1) {
        printf("Error: no command line argument.\n");
        exit(1);

    //more than one target string
    } else {
        printf("Error: only one target string expected.\n");
    }






    

}

