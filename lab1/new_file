#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct Matrix{
    struct Matrix_Int *m_i;
    struct Matrix_Float *m_f;
};

struct Matrix_Int{
    int *arr;
    int *size;
    int *size_of_el;
    void (*make_arr)(struct Matrix *, int, int);
    void (*print_arr)(struct Matrix *, int, int);
    void (*mltp_sc)(struct Matrix *, int, int);
    void (*addition)(struct Matrix *, int, int);
    void (*multiplication)(struct Matrix *, int, int);
    void (*lin_comb)(struct Matrix *, int, int);
};

struct Matrix_Float{
    float *arr;
    int *size;
    int *size_of_el;
    void (*make_arr)(struct Matrix *, int, int);
    void (*print_arr)(struct Matrix *, int, int);
    void (*mltp_sc)(struct Matrix *, int, int);
    void (*addition)(struct Matrix *, int, int);
    void (*multiplication)(struct Matrix *, int, int);
    void (*lin_comb)(struct Matrix *, int, int);
    
};

void make_arr(struct Matrix *m, int type, int size){
    if(type == 0){
        m->m_i->arr = (int*)calloc(size*size, sizeof(int));
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                printf("arr[%d][%d] = ", i, j);
                scanf("%d", (m->m_i->arr + i*size + j));
            }
        }
    } else {
        m->m_f->arr = (float*)calloc(size*size, sizeof(float));
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                printf("arr[%d][%d] = ", i, j);
                scanf("%f", (m->m_f->arr + i*size + j));
            }
        }
    }
}

void print_arr(struct Matrix *m, int type, int size){
    if(type == 0){
        for (int i = 0; i<size; i++){
            for (int j = 0; j<size; j++){
                printf("%5d ", *(m->m_i->arr + i*size + j)); 
            }
            printf("\n");
        }
    } else {
        for (int i = 0; i<size; i++){
            for (int j = 0; j<size; j++){
                printf("%5f ", *(m->m_f->arr + i*size + j));
            }
            printf("\n");
        }
    }
}

void mltp_sc(struct Matrix *m, int type, int size){
    int n; 
    float n1;
    printf("Enter scalar: ");
    if (type == 0){
        scanf("%d", &n);
        for (int i=0; i<size*size; i++){ 
            m->m_i->arr[i] = m->m_i->arr[i] * n; 
        }   
    } else {
        scanf("%f", &n1);
        for (int i=0; i<size*size; i++){ 
            m->m_f->arr[i] = m->m_f->arr[i] * n1; 
        }   
    }
}

void addition(struct Matrix *m, int type, int size){
    if (type == 0){
        int arr[size*size];
        printf("Enter second matrix: \n");
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                printf("arr[%d][%d] = ", i, j);
                scanf("%d", (arr + i*size + j));
            }
        }
        for (int i=0; i<size*size; i++){       
            m->m_i->arr[i] = m->m_i->arr[i] + arr[i];
        }
    } else {
        float arr[size*size];
        printf("Enter second matrix: \n");
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                printf("arr[%d][%d] = ", i, j);
                scanf("%f", (arr + i*size + j));
            }
        }
        for (int i=0; i<size*size; i++){       
            m->m_f->arr[i] = m->m_f->arr[i] + arr[i];
        }
    }
}

void multiplication(struct Matrix *m, int type, int size){
if (type == 0){
        int arr[size*size];
        printf("Enter second matrix: \n");
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                printf("arr[%d][%d] = ", i, j);
                scanf("%d", (arr + i*size + j));
            }
        }
        
        int arr_2[size*size];
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                *(arr_2 + i*size + j) = 0;
                for(int k =0; k<size; k++){
                    *(arr_2 + i*size + j) += *(m->m_i->arr + i*size + k) * *(arr + k*size +j);
                }
            }
        }

        for(int i = 0; i<size*size; i++){
            m->m_i->arr[i] = arr_2[i];
        }
        
    } else {
        float arr[size*size];
        printf("Enter second matrix: \n");
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                printf("arr[%d][%d] = ", i, j);
                scanf("%f", (arr + i*size + j));
            }
        }
        
        float arr_2[size*size];
        for (int i=0; i<size; i++){                    
            for (int j=0; j<size; j++){
                *(arr_2 + i*size + j) = 0;
                for(int k =0; k<size; k++){
                    *(arr_2 + i*size + j) += *(m->m_f->arr + i*size + k) * *(arr + k*size +j);
                }
            }
        }

        for(int i = 0; i<size*size; i++){
            m->m_f->arr[i] = arr_2[i];
        }
    }
}

void lin_comb(struct Matrix *m, int type, int size){
    int num, b_1[size];
    float b_2[size];
    printf("Enter number of strig: ");
    scanf("%d", &num);
    num--;
    for(int i = 0; i<size; i++){
        printf("b%d: ", i);
        if(type == 0)
            scanf("%d", &b_1[i]);
        else 
            scanf("%f", &b_2[i]);
    }
    for (int i=0; i<size; i++){                    
        for (int j=0; j<size; j++){
            if(i!=num){
                if(type == 0)
                    *(m->m_i->arr + num*size + j) += *(b_1 + j) * *(m->m_i->arr + i*size + j);
                else
                    *(m->m_f->arr + num*size + j) += *(b_2 + j) * *(m->m_f->arr + i*size + j);
            }
        }
    }

}

int main() {
    int size, exit = 0, n, n1, xp = 0;
    int type;
    struct Matrix *m = NULL;
    int *arr_c;
    float *arr_v;
    do{
        printf("\n1. Input\n2. Functions\n3. Exit\n");
        scanf("%d", &n);
        switch(n){
            case 1:
                if(xp == 1){
                    if(type == 0){
                        free(m->m_i->arr);
                        free(m->m_i);
                    } else { 
                        free(m->m_f->arr);
                        free(m->m_f);
                    }
                    free(m);
                }
                xp = 1;
                m = (struct Matrix*)calloc(1, sizeof(struct Matrix));
                printf("Int or float? (0 | 1): ");
                scanf("%d", &type);
                printf("Enter size of matrix: ");
                scanf("%d", &size);
                if (type == 0){
                    m->m_i = (struct Matrix_Int*)calloc(1, sizeof(struct Matrix_Int));
                    m->m_i->make_arr = &make_arr;
                    m->m_i->make_arr(m, type, size);
                } else if (type == 1) {
                    m->m_f = (struct Matrix_Float*)calloc(1, sizeof(struct Matrix_Float));
                    m->m_f->make_arr = &make_arr;
                    m->m_f->make_arr(m, type, size);
                } else {
                    printf("Incorrect data entry!\n");
                }
                break;
            case 2:
                printf("\n1. Print\n2. Multyply by a scalar\n3. Addition\n4. Multiplication\n5. Linear combination\n");
                scanf("%d", &n1);
                switch(n1){
                    case 1:
                        if(type == 0){
                            m->m_i->print_arr = &print_arr;
                            m->m_i->print_arr(m, type, size);
                        } else {
                            m->m_f->print_arr = &print_arr;
                            m->m_f->print_arr(m, type, size);
                        }
                        break;
                    case 2:
                        if(type == 0){
                            m->m_i->mltp_sc = &mltp_sc;
                            m->m_i->mltp_sc(m, type, size);
                        } else {
                            m->m_f->mltp_sc = &mltp_sc;
                            m->m_f->mltp_sc(m, type, size);
                        }
                        break;
                    case 3:
                        if(type == 0){
                            m->m_i->addition = &addition;
                            m->m_i->addition(m, type, size);
                        } else {
                            m->m_f->addition = &addition;
                            m->m_f->addition(m, type, size);
                        }
                        break;
                    case 4:
                        if(type == 0){
                            m->m_i->multiplication = &multiplication;
                            m->m_i->multiplication(m, type, size);
                        } else {
                            m->m_f->multiplication = &multiplication;
                            m->m_f->multiplication(m, type, size);
                        }
                        break;
                    case 5:
                        if(type == 0){
                            m->m_i->lin_comb = &lin_comb;
                            m->m_i->lin_comb(m, type, size);
                        } else {
                            m->m_f->lin_comb = &lin_comb;
                            m->m_f->lin_comb(m, type, size);
                        }      
                }

                break;
            case 3:
                exit = 1;
        }
    }while(exit != 1);
    free(m->m_i->arr);
    free(m->m_f->arr);
    free(m->m_i);
    free(m->m_f);
    free(m);
    return 0;
}
