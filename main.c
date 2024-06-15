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

int main(int argc, char* argv[]){
    FILE *fptr;
    if (argc == 1) {
        // TODO: edit this
        fptr = fopen("lists.txt", "r");
    }
    else {
        fptr = fopen(argv[1], "r");
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

    if (argc >= 3) {
        if (strcmp(argv[2], "-s") == 0) {
            sortList(list);
        }
    }
    else {
        randomList(list);
    }

    printList(list);

    fclose(fptr);
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