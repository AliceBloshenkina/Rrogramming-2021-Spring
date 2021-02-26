#include <stdlib.h>
#include <stdio.h>

struct List {
    int data;
    struct List *next;
};

int add_in_list(struct List *list, int data){
    struct List *ptr = (struct List *) malloc(sizeof(struct List));
    if(!list->data){
        list->data=data;
        list->next=NULL;
    } else {
        while(list->next != NULL){
            list = list->next;
        }
        ptr->data = data;
        ptr->next = NULL;
        list->next = ptr;
    }
    return 0;
}

void list_print(struct List *list){
    struct List *ptr;
    ptr = list;
    do{
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }while(ptr != NULL);
}

void list_print_rev(struct List *list){
    if(list != NULL){
        list_print_rev(list->next);
        printf("%d ", list->data);
    }
}

struct List * list_revers(struct List *list){
    struct List *ptr, *temp;
    ptr = list->next;
    int n = 0;
    list->next = NULL;
    while(ptr != NULL){
        temp = list;
        list = ptr;
        ptr = ptr->next;
        list->next = temp;
    }
}

int list_palindrom(struct List *list){
    struct List *list_1 = (struct List*)calloc(1, sizeof(struct List));
    list_1 = list;
    list = list_revers(list);
    do{
        if(list->data != list_1->data){
            printf("\nNot a palindrome");
            return 0;
        }
        list = list->next;
        list_1 = list_1->next;
    }while(list->next != NULL);
    printf("\nPalindrome");
    return 0;
}

int main(){
    struct List *list = (struct List*)calloc(1, sizeof(struct List));
    add_in_list(list, 10);
    add_in_list(list, 20);
    add_in_list(list, 30);
    add_in_list(list, 40);
    add_in_list(list, 50);
    list_print(list);
    printf("\n");
    list_print_rev(list);
    list = list_revers(list);
    list_print(list);
    list_palindrom(list);
    return 0;
}
