#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_array(int len, int *array){
    int i;
    for (i = 0; i<len; i++)
    {
        printf("array[%d] = ", i);
        scanf("%d", &array[i]);
    }
}

char *get_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

int *remov_e_n(int *array, int *len_m){
    int j = 0, len = *len_m;
    int *array_2 = (int*)calloc(len+1, sizeof(int));
    for(int i = 0; i<len; i++){
        if(array[i]%2==1){
            array_2[j]=array[i];
            j++;
        }
        array[i] = 0;
    }
    
    if(j!=0)array_2 = (int*)realloc(array_2, (j + 1) * sizeof(int));
    if(j==0){
        free(array);
        free(array_2);
        return NULL;
    }
    free(array);
    *len_m = j;
    return(array_2);
}

void find_min_max(int *array, int len){
    int min, max;
    min = max = array[0];
    for(int i = 0; i<len; i++){
        if(array[i]>max)max = array[i];
        if(array[i]<min)min = array[i];
    }
    printf("Min: %d, max: %d\n", min, max);
}

char *revers(char *str){
    int j = strlen(str)-1;
    char temp;
    for(int i = 0; i<j; i++){
        temp = str[i];
        str[i]=str[j];
        str[j]=temp;
        j--;
    }
    return str;
}

void bublsort(int *array, int len)
{
  for (int i = 0; i<len-1; i++){
    for (int j = (len-1); j > i; j--){
      if (array[j-1] > array[j]){
        int temp = array[j-1];
        array[j-1] = array[j];
        array[j] = temp;
      }
    }
  }
}

void binsearch(int *array, int len){
    int key, i = 0, number = -1;
    printf("Enter number: ");
    scanf("%d", &key);
    while(i<len){
        int mid = (i+len)/2;
        if(key = array[mid]){
            number = mid;
            break;
        }
        if(key<array[mid])len = mid-1;
        else i = mid+1;
    }
    if(number == -1)printf("Not found\n");
    else printf("Number - %d - on array[%d]", key, number);
}

int main()
{
    int n, i, n1, t, len_a, len_s, as, as_2, exit=0;
    int *array = NULL;
    char *str = NULL;
    do{
        printf("\n1. Data input\n2. Work with array\n3. Output\n4. Exit\n");
        scanf("%d", &n);
        switch(n)
        {
            case 1: 
                printf("Do you want to create array or string? (0|1)\n");
                scanf("%d", &as);
                if(as == 0){
                    printf("Enter len: ");
                    scanf("%d", &len_a);
                    array = (int*)realloc(array, (len_a+1) * sizeof(int));
                    make_array(len_a, array);
                } else {
                    getchar();
                    str = get_str();
                    len_s = strlen(str);
                }
                break;
            case 2:
                printf("\n1. Removing even numbers\n2. Finding min and max\n3. Reverse a string\n4. Binary search\n");
                scanf("%d", &t);
                switch(t)
                {
                    case 1:
                        array = remov_e_n(array, &len_a);
                        break;
                    case 2:
                        find_min_max(array, len_a);
                        break;
                    case 3:
                        str = revers(str);
                        break;
                    case 4:
                        bublsort(array, len_a);
                        binsearch(array, len_a);
                        break;
                }
                break;
            case 3:
                printf("Array or string? (0|1)");
                scanf("%d", &as_2);
                if(as == 0){
                    for (i = 0; i<len_a; i++)
                    {
                        printf("array[%d] = %d\n", i, array[i]);
                    }
                } else {
                    for (i = 0; i<len_s; i++)
                    {
                        printf("array[%d] = %c\n", i, str[i]);
                    }
                }
                break;
            case 4:
                printf("Are you sure? (1-yes, 0-no)\n");
                scanf("%d", &n1);
                if(n1==1)
                    exit = 1;
        }
    }while(exit!=1);
    free(array);
    free(str);
    return 0;
}
