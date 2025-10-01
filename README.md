## Data structures and Algorithms project
Web browser simulation in C, using linked lists, stacks, queues and structures.

## Project structure
-`src` - source files  
-`checker` - script used for testing, `tests` folder with input samples  
-`README.md`  
-`Makefile`  
-`file.in`  
-`file.out`  

## Possible operations
NEW_TAB - opens a new tab\
CLOSE - closes a new tab\
OPEN [TAB_ID] - opens the specific [TAB_ID] tab; if no [TAB_ID] exists, prints "403 FORBIDDEN"\
NEXT - goes to next tab\
PREV - goes to previous tab\
PAGE [ID] - opens the specific [ID] tab; if no [ID] exists, prints "403 FORBIDDEN"\
BACKWARD - goes to next page\
FORWARD - goes to previous page\
PRINT - prints in oneliner the description of current page\
PRINT_HISTORY [ID] - prints in multiple lines pages'URLs and IDs from [ID] specified tab\
  
Input files are available to test the code in differen scenarios and corner cases.

## Compilation and Running
`make test` - scores for all test will be available, Valgrind test is passed
