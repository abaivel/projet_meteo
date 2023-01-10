#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions_abr.c"
#include "functions_avl.c"
#include "functions_liste.c"
#include "fichier.h"
#define SIZE_MAX_LINE 200
#define SIZE_MAX_BOX 50

int put_data_list(FILE* file_in, FILE* file_out, int column, int nb_columns){
    char* line=NULL;
    Chainon* liste=NULL;
    char** tab=NULL;
    do{
        line=fgets(line, SIZE_MAX_LINE, file_in);
        tab=lineToTab(line,nb_columns);
        liste=ajout_croissant(liste,)
    }while (line!=NULL);
    fclose(file_in);
    fclose(file_out);
}

char** lineToTab(char* line, int nb_columns){
    char** tab=malloc(sizeof(char*)*nb_columns);
    k=0;
    j=0;
    for (int i=0;i<strlen(line);i++){
        if (line[i]==';'){
            j=0;
            k++;
        }else{
            if (j==0){
                tab[k]=calloc(sizeof(char)*SIZE_MAX_BOX);
            }
            tab[k][j]=line[i];
            j++;
        }
    }
    return tab;
}

