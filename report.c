#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

extern char *targetString;
extern char *filesChanged;
extern int numOfFilesChanged;

//function for qsort
int compareStr(const void *pa, const void *pb) {
  const char* aa = *(const char**)pa;
  const char* bb = *(const char**)pb;
  //return the inverse of strncmp to get inverse order (most edits first)
  return strncmp(aa,bb, 1)*(-1);
}

void createReport() {
    //initialize an area for the files changed
    char *files[numOfFilesChanged];
    //splitting filesChanged char array to 2d char array
    if (numOfFilesChanged>0) {

        char* token;
        token = strtok(filesChanged, "\n");
        int i = 0;
        while (token != NULL) {
          files[i++] = token;
          token = strtok(NULL, "\n");
        }        
        //sort files array
        int m = sizeof(files)/numOfFilesChanged;
        qsort(files, numOfFilesChanged, m, compareStr);      
    }
    
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

    //print sorted files
    for (int i = 0; i < numOfFilesChanged; i++) printf("%s\n", files[i]);


    return;
}