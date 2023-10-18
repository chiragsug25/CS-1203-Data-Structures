#include <stdio.h>
#include <stdbool.h>

// Constant n value for Eight Queens
#define N 8

int solutionCount = 0;

// Function to solve the Eight Queens problem
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    for (i = 0; i < col; i++) {
        if (board[row][i])
            return false;
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return false;
    }

    for (i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j])
            return false;
    }

    return true;
}

void printQueensBoard(int board[N][N]) {
    solutionCount++;
    printf("Solution %d:\n", solutionCount);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

bool solveNQueens(int board[N][N], int col) {
    if (col >= N) {
        printQueensBoard(board);
        return true;
    }

    bool res = false;
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            res = solveNQueens(board, col + 1) || res;
            board[i][col] = 0; // Backtrack
        }
    }

    return res;
}

// Function for Tower of Hanoi
void towerOfHanoi(int n, char source, char auxiliary, char destination) {
    if (n == 1) {
        printf("Move disk 1 from rod %c to rod %c\n", source, destination);
        return;
    }
    towerOfHanoi(n - 1, source, destination, auxiliary);
    printf("Move disk %d from rod %c to rod %c\n", n, source, destination);
    towerOfHanoi(n - 1, auxiliary, source, destination);
}

int main() {
    int choice;
    while (1) {
        printf("Choose the problem to solve:\n");
        printf("1. Tower of Hanoi\n");
        printf("2. All possible solutions to Eight Queens\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int numDisks;
            printf("Enter the number of disks for Tower of Hanoi: ");
            scanf("%d", &numDisks);
            towerOfHanoi(numDisks, 'A', 'B', 'C');
        } else if (choice == 2) {
            int queensBoard[N][N] = {0};
            solutionCount = 0;
            if (!solveNQueens(queensBoard, 0)) {
                printf("No solution exists for Eight Queens.\n");
            }
        } else if (choice == 3) {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice. Please enter 1 for Tower of Hanoi, 2 for Eight Queens, or 3 to exit.\n");
        }
    }

    return 0;
}
