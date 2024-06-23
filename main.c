#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MaxString 50

typedef struct List {
    int size;
    int length;
    char** array;
}List ;

List* initList();

void freeList(List *list);

void addListElement(List *list, char* str);

void printList(List *list);

void sortList(List *list);

void randomList(List *list);

void writeList(List *list, FILE *fptr);

void printHelp();

void popList(List *list, int amount, FILE *fptr);

int main(int argc, char* argv[]){
    FILE *fptr;
    if (argc == 1) {
        printHelp();
        exit(0);
    }
    else {
        fptr = fopen(argv[argc-1], "r");
    }

    List *list = initList();
    char data[MaxString];
    if (fptr == NULL) {
        printf("Error file\n");
        exit(0);
    }
    else {
        while (fgets(data, MaxString, fptr) != NULL) {
            addListElement(list, data);
        }
    }
    fclose(fptr);

    FILE *fptr_write;
    fptr_write = fopen(argv[argc-1], "w");

    if (fptr_write == NULL) { 
        printf("Error opening file write mode!\n");
        exit(0);
    }

    if (argc >= 3) {
        for (int i=1; i<argc-1; i++) {
            if (strcmp(argv[i], "-s") == 0) {
                sortList(list);
            }
            if (strcmp(argv[i], "-p") == 0) {
                popList(list, 100, fptr_write);
                fclose(fptr_write);
                freeList(list);
                return 0;
            }
        }
    }
    else {
        randomList(list);
    }

    writeList(list, fptr_write);

    printList(list);

    fclose(fptr_write);

    freeList(list);

    return 0;
}

List* initList(){
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        printf("memory allocation faile\n");
        exit(0);
    }
    list->size = 1000;
    list->length = 0;
    list->array = NULL;
    list->array = (char**)malloc(list->size * sizeof(char*));
    if (list->array == NULL) {
        printf("memory allocation faile\n");
        exit(0);
    }
    return list;
}

void freeList(List *list){
    for (int i =0; i < list->length; i++) {
        free(list->array[i]);
    }
    free(list->array);
    free(list);
}

void addListElement(List *list, char* str){
    if(list->length == list->size){
        char** temp = list->array;
        list->size *= 2;
        list->array = realloc(list, list->size*sizeof(char*));
        if (list == NULL) {
            printf("out of memory\n");
            exit(0);
        }
    }
    list->array[list->length] = (char*)malloc(MaxString * sizeof(char));

    if (list->array[list->length] == NULL) {
        printf("memory allocation faile\n");
        exit(0);
    }
    strcpy(list->array[list->length], str);
    list->length++;
}

void printList(List *list){
    for (int i=0; i<list->length; i++) {
        printf("%s", list->array[i]);
    }
}

void sortList(List *list){
    //sort descend
    char temp[MaxString];
    for (int i =0; i < list->length-1; i++) {
        int min_j = i;
        for (int j=i+1; j<list->length; j++) {
            if (strcmp(list->array[j], list->array[min_j]) < 0) {
                min_j = j;
            }
        }
        if (min_j != i) {
            strcpy(temp, list->array[min_j]);
            strcpy(list->array[min_j], list->array[i]);
            strcpy(list->array[i], temp);
        }
    }
}

void randomList(List *list){
    srand(time(NULL));
    for (int i=0; i<list->length; i++) {
        int swap_index = rand() % list->length;
        char temp[MaxString];
        strcpy(temp, list->array[swap_index]);
        strcpy(list->array[swap_index], list->array[i]);
        strcpy(list->array[i], temp);
    }
}

void writeList(List *list, FILE *fptr){
    for (int i=0; i<list->length; i++) {
        fprintf(fptr, "%s", list->array[i]);
    }
}

void printHelp(){
    printf("Usage: randomList [options] [file]\n");
    printf("Example: randomList ./lists.txt ,this will shuffle list\n");
    printf("Option:\n");
    printf("    -s  this will sort list instead of shuffle");
}

void popList(List *list, int amount, FILE *fptr){
    if (amount > list->length) {
        printList(list);
    }
    else {
        for (int i=0; i<list->length; i++) {
            if (i<amount) {
                printf("%s", list->array[i]);
            }
            else {
                fprintf(fptr, "%s", list->array[i]);
            }
        }
    }
}
