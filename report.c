#include <stdio.h>
#include <unistd.h>

extern char *targetString;
extern char *filesChanged;

void createReport() {
    
    //print target string
    printf("Target string: %s\n\n", targetString);

    //getting current directory
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
      perror("Error: could not get current directory.\n");
    }
    else {
      printf("Search begins in current folder: %s\n\n\n", cwd);
    }

    //printing search report
    printf("*** Search Report ***\n\n");
    printf("Updates\t\tFile Name\n");

    //print contents of filesChanged (contents added in text.c)
    printf("%s\n", filesChanged);


    return;
}