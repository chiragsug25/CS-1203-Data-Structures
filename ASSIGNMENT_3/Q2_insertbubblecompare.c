


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void insertionSort(int arr[], int n) {
    // Insertion Sort logic
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n) {
    // Bubble Sort logic
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
//Time Complexity Analysis:
//Insertion Sort:

//Best-case time complexity: O(n) - when the input array is already sorted.
//Worst-case time complexity: O(n^2) - when the input array is in reverse order.
//Average-case time complexity: O(n^2).

//Bubble Sort:

//Best-case time complexity: O(n) - when the input array is already sorted.
//Worst-case time complexity: O(n^2) - when the input array is in reverse order.
//Average-case time complexity: O(n^2).
void generateRandomArray(int arr[], int n) {
    // Generate random array logic
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Random integers between 0 and 999
    }
}

// Function to measure time using gettimeofday
double getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
}

int main() {
    int choice;
    const int n = 10000; // One can adjust the array size as needed
    int arr[n];
    int numbersInserted = 0;
    while (1) {
        printf("Options:\n");
        printf("1. Insert numbers\n");
        printf("2. Display entered unsorted numbers\n");
        printf("3. Sort with Insertion Sort\n");
        printf("4. Sort with Bubble Sort\n");
        printf("5. Compare Execution Times\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
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
                        while (getchar() != '\n'); // Consume the remaining characters including the newline character
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
                    insertionSort(arr, numbersInserted);
                    printf("Sorted with Insertion Sort.\n");
                    printf("Sorted array: ");
                    for (int i = 0; i < numbersInserted; i++) {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }                break;

            case 4:
                if (numbersInserted == 0) {
                    printf("Please insert numbers first.\n");
                } else {
                    bubbleSort(arr, numbersInserted);
                    printf("Sorted with Bubble Sort.\n");
                    printf("Sorted array: ");
                    for (int i = 0; i < numbersInserted; i++) {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }                break;

            case 5:
                if (arr[0] == 0) {
                    printf("Please insert numbers first.\n");
                } else {
                    int arr_copy[n]; // Create a copy of the array for fair comparison

                    // Generate a fresh random array for the copy
                    generateRandomArray(arr_copy, n);

                    double insertion_time = 0.0, bubble_time = 0.0;

                    for (int i = 0; i < 10; i++) {
                        // Measure time for Insertion Sort
                        double start = getTime();
                        insertionSort(arr, n);
                        double end = getTime();
                        insertion_time += end - start;

                        // Measure time for Bubble Sort
                        start = getTime();
                        bubbleSort(arr_copy, n);
                        end = getTime();
                        bubble_time += end - start;
                    }

                    // Calculate the average execution time
                    insertion_time /= 10;
                    bubble_time /= 10;

                    printf("Execution Times (averaged over 10 runs):\n");
                    printf("Insertion Sort: %f seconds\n", insertion_time);
                    printf("Bubble Sort: %f seconds\n", bubble_time);
                }
                break;

            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
