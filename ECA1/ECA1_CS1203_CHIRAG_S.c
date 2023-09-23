#include <stdio.h>
#include <stdbool.h>

// Function to swap two elements in an array
void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Function to print an array
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to generate permutations using Johnson and Trotter algorithm
void generatePermutations(int* arr, int* dir, int n) {
    printArray(arr, n);

    while (true) {
        int mobile = -1;
        int mobileIndex = -1;

        // Find the largest mobile element
        for (int i = 0; i < n; i++) {
            if ((dir[i] == -1 && i > 0 && arr[i] > arr[i - 1]) ||
                (dir[i] == 1 && i < n - 1 && arr[i] > arr[i + 1])) {
                if (arr[i] > mobile) {
                    mobile = arr[i];
                    mobileIndex = i;
                }
            }
        }

        // No more mobile elements, exit the loop
        if (mobile == -1) {
            break;
        }

        // Swap the mobile element with its adjacent element in the direction
        if (dir[mobileIndex] == -1) {
            swap(arr, mobileIndex, mobileIndex - 1);
            swap(dir, mobileIndex, mobileIndex - 1);
        } else {
            swap(arr, mobileIndex, mobileIndex + 1);
            swap(dir, mobileIndex, mobileIndex + 1);
        }

        // Reverse the direction of all elements greater than the mobile element
        for (int i = 0; i < n; i++) {
            if (arr[i] > mobile) {
                dir[i] = -dir[i];
            }
        }

        printArray(arr, n);
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    int dir[n];

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
        dir[i] = -1; // -1 represents left direction
    }

    generatePermutations(arr, dir, n);

    return 0;
}
