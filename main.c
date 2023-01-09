#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"

int main(int argc, char *argv[]){
	int reversed = 0; //should reverse the sorted data ? Default false
	int algo = 0; //algorithm used to sort the data: 0>avl | 1>abr | 2>tab
	char *inputFile; //contains the input file name
	char *outputFile; //contains the output file name
	for (int i = 1; i < argc; i++){
		if (strstr(argv[i], "-") != NULL){
			if (!strcmp(argv[i], "-f") && i+1 < argc){
				if (argv[i+1][0] != '-'){
					inputFile = argv[i+1];
				}
			}		
			} else if (!strcmp(argv[i], "-o") && i+1 < argc){
				if (argv[i+1][0] != '-'){
					outputFile = argv[i+1];
				}
			}
			} else if (!strcmp(argv[i], "-r")){
				reversed = 1;
			} else if (!strcmp(argv[i], "--avl")){
				algo = 0;
			} else if (!strcmp(argv[i], "--abr")){
				algo = 1;
			} else if (!strcmp(argv[i], "--tab")){
				algo = 2;
			} else {
				return 1; //return 1 if bad parameter
			}
		}
	}

	if (inputFile == NULL || outputFile == NULL){
		return 1; //return 1 if no file as input or output specified
	}

	

	return 0;
}
