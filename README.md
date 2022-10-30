# SearchandReplace
C program that searches text files in current directory (including subdirectories), for a target string given as a commandline argument. All occurences of the target string are capitalized in each file that contains it. The search is case insensitive: if target string is 'Apple', all occurences of apple will be capitalized. 'APPle', 'apple'--both will be changed to 'APPLE'.

To compile use the command: gcc traversal.c text.c report.c replace.c

To run program with a target string, simply call ./a.out with a target string. For example: ./a.out apple

Note: the program will alter files that contain the target string.
