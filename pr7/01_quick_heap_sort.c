#include <stdio.h>
#include <stdlib.h>
#define foreach(item, size) \
    for(int i = 0; i < size; i++)


void output_q (int* arr, int size) { 
    FILE *f; 
    f = fopen("quicksort.log", "a"); 
    foreach(i, size) {
        fprintf(f,"%d ",arr[i]); 
    }
    fprintf(f,"\n"); 
    fclose(f); 
}

void output_h (int* arr, int size) { 
    FILE *f; 
    f = fopen("heapsort.log", "a"); 
    foreach(i, size) {
        fprintf(f,"%d ",arr[i]); 
    }
    fprintf(f,"\n"); 
    fclose(f); 
}

void quicksort (int* arr, int size, int low, int high) {
    if (size == 0)  { return; }
    if (low >= high) { return; }

    int middle = low + (high - low) / 2;
    int opora = arr[middle];
    int i = low, j = high;

    output_q(arr, size);

    while (i <= j) {
        while (arr[i] < opora) { i++; }
        while (arr[j] > opora) { j--; }
        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (low < j) { quicksort(arr, size, low, j); }
    if (high > i) { quicksort(arr, size, i, high); }
}

void heapsort (int* arr, int size) {
    // строим кучу
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }
    // извлекаем из кучи один элемент за другим
    for (int i = size - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        output_h(arr, size);
        heapify(arr, i, 0);
    }
}

void heapify (int* arr, int size, int i) {
    int root = i; // наибольший элемент как корень
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && arr[left] > arr[root]) { root = left; }
    if (right < size && arr[right] > arr[root]) { root = right; }
    if (root != i) {
        int temp = arr[i];
        arr[i] = arr[root];
        arr[root] = temp;

        output_h(arr, size);
        heapify(arr, size, root);
    }
}

int main (void) {
    // стираем данные при наличии 
    // или создаем при отсутствии
    FILE *fq = fopen("quicksort.log", "w");
    FILE *fh = fopen("heapsort.log", "w");
    fclose(fq);
    fclose(fh);
    int size = 0;
    (void)scanf("%d", &size);
    int* arr = (int*)calloc(size, sizeof(int));
    int low = 0, high = size - 1; 
    foreach(i, size) {
        (void)scanf("%d", &arr[i]);
    }
    foreach(i, size) {
        printf("%d ", arr[i]);
    }
    
    quicksort(arr, size, low, high);
    output_q(arr, size);

    printf("\n");
    foreach(i, size) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    foreach(i, size) {
        (void)scanf("%d", &arr[i]);
    }
    foreach(i, size) {
        printf("%d ", arr[i]);
    }

    heapsort(arr, size);
    output_h(arr, size);

    printf("\n");
    foreach(i, size) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}