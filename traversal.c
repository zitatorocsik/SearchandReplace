#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "text.h"

void searchDirectory(char *dir) {

    char path[1000];
    
    //initialize directory
    DIR *directory;

    //initialize dirent structure
    struct dirent *entry;

    //open directory
    directory = opendir(dir);

    //error checking for directory
    if (directory == NULL) {
        printf("Error opening directory.\n");
        return;
    }

    //while there are entries to read in directory
    while ((entry = readdir(directory)) != NULL) {
        
        //if not current or previous directory
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            
            //regule file
            if (entry->d_type == DT_REG) {

                //pointer to first occurence of a period in file name
                char *extptr = strrchr(entry->d_name, '.');

                //store extension of file in ext
                char ext[4];
                strcpy(ext, extptr+1);

                //if file is a .txt file
                if (strcmp(ext, "txt") == 0) {

                    //call readAndReplace with path (so we can open file)
                    strcpy(path, dir);
                    strcat(path, "/");
                    strcat(path, entry->d_name);

                    //function to open files and replace target strings, in text.c
                    readAndReplace(path);
                }

            //if entry is a directory
            } else if (entry->d_type == DT_DIR) {

                //create a new path from base
                strcpy(path, dir);
                strcat(path, "/");
                strcat(path, entry->d_name);
                
                //recursively call searchDirectory to go through dir
                searchDirectory(path);
            }

            
        }
        
    }
    closedir(directory);

    return;
}
