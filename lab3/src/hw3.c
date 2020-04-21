#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct _merge_sort_arg_t {
    int i;
    int j;
    int *a;
} merge_sort_arg_t;

void merge_sort_entry(void *data);
void merge_sort(int *arr, int l, int r);
void merge(int *arr, int l, int m, int r);

int main(int argc, char* argv[]) {
    FILE *in_file  = fopen(argv[1], "r");
    FILE *out_file = fopen(argv[2], "w");

    // check file
    if (in_file == NULL) {   
        printf("Error! Could not open input file.\n"); 
        exit(-1);
    }

    pthread_t left_t, right_t;
    int input_data[10000];
    int input_data_size;
    int fscanf_return = 0;

    for(int m=1; !feof (in_file); m++) {
        printf("line %d\n", m);
        // read data
        input_data_size = 0;
        char c = '0';
        int err_l, err_r;
        clock_t begin = clock();

        for(int i=0; (!feof (in_file) && c != '\n' && c != '\r'); i++) {
            fscanf_return = fscanf(in_file, "%d%c", &input_data[i], &c);
            if(fscanf_return < 2) break;
            input_data_size++;
        }

        if(input_data_size == 0) continue;

        int mid = input_data_size/2;
        merge_sort_arg_t left_arg, right_arg;
        left_arg.i = 0;
        left_arg.j = mid;
        left_arg.a = input_data;
        err_l = pthread_create(&left_t, NULL, merge_sort_entry, &left_arg);

        right_arg.i = mid+1;
        right_arg.j = input_data_size-1;
        right_arg.a = input_data;
        err_r = pthread_create(&right_t, NULL, merge_sort_entry, &right_arg);

        if(err_l != 0 && err_r != 0) {
            printf("ERROR return code from pthread_create()\n");
        }
        pthread_join(left_t, NULL);
        pthread_join(right_t, NULL);

        merge(input_data, 0, mid, input_data_size-1);

        // print data
        for(int i=0; i<input_data_size; i++) {
            fprintf(out_file, "%d ", input_data[i]);
        }
        fprintf(out_file, "\n");

        clock_t end = clock();
        double duration = end - begin;
        fprintf(out_file, "duration:%f\n\n", duration / CLOCKS_PER_SEC);
    }
    
    fclose (in_file);
    fclose(out_file);
}

void merge_sort_entry(void *data) {
    // convert parameter type
    merge_sort_arg_t *arg = (merge_sort_arg_t*) data;
    
    merge_sort(arg->a, arg->i, arg->j);
}

void merge_sort(int *arr, int l, int r) {
    // check boundary
    if(l >= r) return;

    int m = l + (r-l)/2;

    merge_sort(arr, l, m);
    merge_sort(arr, m+1, r);

    merge(arr, l, m, r);
}

void merge(int *arr, int l, int m, int r) {
    // printf("merge\n");
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;

    int L[n1], R[n2];

    for(i=0; i<n1; i++) {
        L[i] = *(arr+l+i);
    }
    for(j=0; j<n2; j++) {
        R[j] = *(arr+m+1+j);
    }

    i = 0;
    j = 0;
    k = l;

    while(i<n1 && j<n2) {
        if(L[i] <= R[j]) {
            *(arr+k) = L[i];
            i++;
        } else {
            *(arr+k) = R[j];
            j++;
        }
        k++;
    }

    // copy the remaining part
    while(i<n1) {
        *(arr+k) = L[i];
        i++;
        k++;
    }
    while(j<n2) {
        *(arr+k) = R[j];
        j++;
        k++;
    }
}
