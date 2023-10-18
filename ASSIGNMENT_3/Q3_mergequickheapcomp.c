#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Random integers between 0 and 999
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ... (quickSort, mergeSort, and heapSort functions)

int main() {
    int choice;
    const int n = 10000; // One can adjust the array size as needed
    int arr[n];
    int numbersInserted = 0; // Initialize the variable to keep track of the inserted numbers

    while (1) {
        printf("Options:\n");
        printf("1. Enter numbers\n");
        printf("2. Display entered unsorted numbers\n");
        printf("3. Sort with Quick Sort\n");
        printf("4. Sort with Merge Sort\n");
        printf("5. Sort with Heap Sort\n");
        printf("6. Compare Execution Times\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Reset the numbersInserted variable to start fresh
                numbersInserted = 0;

                printf("Enter numbers one by one. Enter -1 to finish.\n");
                int number;

                while (numbersInserted < n) {
                    printf("Enter number %d: ", numbersInserted + 1);
                    if (scanf("%d", &number) == 1) {
                        if (number == -1) {
                            if (numbersInserted == 0) {
                                printf("No numbers entered.\n");
                            } else {
                                printf("Numbers inserted successfully.\n");
                            }
                            while (getchar() != '\n'); // Consume the newline character
                            break;
                        }
                        arr[numbersInserted] = number;
                        numbersInserted++;
                    } else {
                        printf("Invalid input. Please enter a valid number.\n");
                        while (getchar() != '\n'); // Consume the remaining characters, including the newline character
                    }
                }
                break;

            case 2:
                if (numbersInserted == 0) {
                    printf("Please insert numbers first.\n");
                } else {
                    printf("Entered numbers (unsorted): ");
                    for (int i = 0; i < numbersInserted; i++) {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }
                break;

            case 3:
                if (numbersInserted == 0) {
                    printf("Please insert numbers first.\n");
                } else {
                    // Perform Quick Sort on the entered numbers
                    quickSort(arr, 0, numbersInserted - 1);
                    printf("Sorted with Quick Sort.\n");
                    printf("Sorted array: ");
                    for (int i = 0; i < numbersInserted; i++) {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }
                break;

            case 4:
                if (numbersInserted == 0) {
                    printf("Please insert numbers first.\n");
                } else {
                    // Perform Merge Sort on the entered numbers
                    mergeSort(arr, 0, numbersInserted - 1);
                    printf("Sorted with Merge Sort.\n");
                    printf("Sorted array: ");
                    for (int i = 0; i < numbersInserted; i++) {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }
                break;

            case 5:
                if (numbersInserted == 0) {
                    printf("Please insert numbers first.\n");
                } else {
                    // Perform Heap Sort on the entered numbers
                    heapSort(arr, numbersInserted);
                    printf("Sorted with Heap Sort.\n");
                    printf("Sorted array: ");
                    for (int i = 0; i < numbersInserted; i++) {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }
                break;

case 6:
    if (numbersInserted == 0) {
        printf("Please insert numbers first.\n");
    } else {
        int arr_copy[n]; // Create a copy of the array for fair comparison
        for (int i = 0; i < numbersInserted; i++) {
            arr_copy[i] = arr[i];
        }

        clock_t start, end;
        double quick_time, merge_time, heap_time;

        // Measure time for Quick Sort
        start = clock();
        quickSort(arr, 0, numbersInserted - 1);
        end = clock();
        quick_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Measure time for Merge Sort
        for (int i = 0; i < numbersInserted; i++) {
            arr[i] = arr_copy[i];
        }
        start = clock();
        mergeSort(arr, 0, numbersInserted - 1);
        end = clock();
        merge_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Measure time for Heap Sort
        for (int i = 0; i < numbersInserted; i++) {
            arr[i] = arr_copy[i];
        }
        start = clock();
        heapSort(arr, numbersInserted);
        end = clock();
        heap_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Execution Times:\n");
        printf("Quick Sort: %f seconds\n", quick_time);
        printf("Merge Sort: %f seconds\n", merge_time);
        printf("Heap Sort: %f seconds\n", heap_time);
    }
    break;

            case 7:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
