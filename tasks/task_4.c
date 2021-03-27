#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct List {
    char data;
    struct List *next;
};

struct List *delet_probel(struct List *ptr){
    struct List *head = ptr;
    struct List *temp;
    do{
        ptr->data = tolower(ptr->data);
        if(ptr->next && ptr->next->data == ' '){
            temp = ptr->next;
            ptr->next = ptr->next->next;
            free(temp);
        }
        ptr = ptr->next;
    }while(ptr != NULL);
    return head;
}

void list_pallindrome(struct List *list, struct List *head, int *count_m, int *pldr_m){
    int pldr = 0, count = 0;
    if(list != NULL){
        list_pallindrome(list->next, head, &count, &pldr);
        if(list->data != ' '){
        count++;
        if( head->data == ' '){
            count++;
        }
        for(int i = 1; i<count; i++){
            head = head->next;
        }
        if(list->data != head->data){
            pldr = 1;
        }

    *pldr_m = pldr;
    *count_m = count;
    }}
}

int main(){
    char ch;
    int pldr = 0, count = 0;
    int arr[1] = {0};
    struct List *list = (struct List*)calloc(1, sizeof(struct List));
    while((ch = getchar()) != '\n'){
            if(ch == EOF){
                break;
            }
            add_in_list(list, ch);
        }
    list = delet_probel(list);
    list_pallindrome(list, list, &count, &pldr);
    if(pldr == 0){
        printf("Pallindrom");
    } else {
        printf("Not a pallindrome");
    }
    return 0;
}
