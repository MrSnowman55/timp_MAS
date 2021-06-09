#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define foreach(item, size) \
    for(int i = 0; i < size; i++)


void output_c (int* arr, int size) { 
    FILE *f; 
    f = fopen("combsort.log", "a"); 
    foreach(i, size) {
        fprintf(f,"%d ",arr[i]); 
    }
    fprintf(f,"\n");
    fclose(f);
}

void output_s (int* arr, int size) { 
    FILE *f; 
    f = fopen("shellsort.log", "a"); 
    foreach(i, size) {
        fprintf(f,"%d ",arr[i]); 
    }
    fprintf(f,"\n"); 
    fclose(f); 
}

void shellsort(int* arr, int size) {
    int distance = size / 2;

    while (distance >= 1) {
        for (int i = distance; i < size; i++) {
            int j = i;
            while ((j >= distance) && (arr[j - distance] > arr[j])) {
                output_s(arr, size);
                int temp = arr[j];
                arr[j] = arr[j - distance];
                arr[j - distance] = temp;
                j = j - distance;
            }
        }
        distance = distance / 2;
    }
}

int update_gap (int gap) {
    gap = gap * 1247 / 1000;
    if (gap < 1) {
        return 1;
    } else {
        return gap;
    }
}

void combsort (int* arr, int size) {
    int gap = size;
    bool swapped = true;

    while (gap > 1 || swapped == true) {
        gap = update_gap(gap);
        swapped = false;

        for (int i = 0; i < size - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                output_c(arr, size);
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
    }
}

int main (void) {
    // стираем данные при наличии 
    // или создаем при отсутствии
    FILE *fc = fopen("combsort.log", "w");
    FILE *fs = fopen("shellsort.log", "w");
    fclose(fc);
    fclose(fs);
    int size = 0;
    (void)scanf("%d", &size);
    int* arr = (int*)calloc(size, sizeof(int));

    foreach(i, size) {
        (void)scanf("%d", &arr[i]);
    }
    foreach(i, size) {
        printf("%d ", arr[i]);
    }
    
    combsort(arr, size);
    output_c(arr, size);

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

    shellsort(arr, size);
    output_s(arr, size);

    printf("\n");
    foreach(i, size) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}