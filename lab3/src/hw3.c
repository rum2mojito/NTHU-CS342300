#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct _merge_sort_arg {
    int i;
    int j;
    int a[];
    int aux[];
} merge_sort_arg;

void merge_sort_entry(void *data);
void merge_sort(int i, int j, int a[], int aux[]);

int main(int argc, char* argv[]) {
    printf("%d\n", argc);

    FILE *in_file  = fopen(argv[1], "r");
    FILE *out_file = fopen(argv[2], "w");

    // check file
    if (in_file == NULL) {   
        printf("Error! Could not open input file.\n"); 
        exit(-1);
    }

    pthread_t left_t, right_t, merge_t;

    // read data
    int input_data[10000];
    int aux[10000];
    int input_data_size = 0;
    char c;
        
    for(int i=0; (!feof (in_file) && c != '\n' && c != '\r'); i++) {
        fscanf (in_file, "%d%c", &input_data[i], &c);
        input_data_size++;
    }

    int mid = input_data_size/2;
    merge_sort_arg left_arg, right_arg;
    left_arg.i = 0;
    left_arg.j = mid;
    left_arg.a = input_data;
    left_arg.aux = aux;
    pthread_create(&left_t, NULL, merge_sort_entry, (void*) &left_arg);

    right_arg.i = mid;
    right_arg.j = input_data_size;
    right_arg.a = input_data;
    right_arg.aux = aux;
    pthread_create(&right_t, NULL, merge_sort_entry, (void*) &right_arg);

    // print data
    for(int i=0; i<input_data_size; i++) {
        printf("%d\n", input_data[i]);
    }
    
    fclose (in_file);
}

void merge_sort_entry(void *data) {
    // convert parameter type
    merge_sort_arg arg = (merge_sort_arg*) data;
    merge_sort(arg.i, arg.j, &arg.a, &arg.aux);
}

void merge_sort(int i, int j, int a[], int aux[]) {
    // check boundary
    if(j >= i) return;

    int mid = (i+j)/2;

    merge_sort(i, mid, a, aux);
    merge_sort(mid, j, a, aux);

    int pointer_left = i;
    int pointer_right = mid+1;
    int k;


}
