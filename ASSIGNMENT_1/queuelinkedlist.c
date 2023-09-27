#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int info;
    struct node* next;
} NODE, *NODEPTR;

typedef struct queue {
    NODEPTR front, rear;
} QUEUE;

void insert(QUEUE* q, int elm) {
    NODEPTR temp = (NODEPTR)malloc(sizeof(NODE)); // Allocate memory for new node
    temp->info = elm; // Assign the element to the new node
    temp->next = NULL; // Set the next pointer of the new node to NULL
    
    if (q->front == NULL) {
        // If the queue is empty, update both front and rear pointers to the new node
        q->front = temp;
        q->rear = temp;
    } else {
        // If the queue is not empty, update the rear pointer to the new node
        q->rear->next = temp;
        q->rear = temp;
    }
}

int delete(QUEUE* q) {
    if (q->front == NULL)
        return -1; // or any other value to indicate an error
    
    NODEPTR temp = q->front; // Store the front node in a temporary variable
    int val = temp->info; // Retrieve the value of the front node
    q->front = q->front->next; // Update the front pointer to the next node
    free(temp); // Free the memory of the front node
    
    if (q->front == NULL)
        q->rear = NULL; // If the queue becomes empty, update the rear pointer to NULL
    
    return val; // Return the deleted value
}

void printQueue(QUEUE q) {
    if (q.front == NULL) {
        printf("Queue empty\n");
        return;
    }
    
    printf("<- F ");
    NODEPTR temp = q.front;
    while (temp != NULL) {
        printf("%d ", temp->info);
        temp = temp->next;
    }
    printf("<- R\n");
}

int main() {
    QUEUE q;
    q.front = NULL;
    q.rear = NULL;
    
    int elm, menu;
    
    while (1) {
        printf("0. exit, 1. initialize, 2. delete, 3. insert, 4. print. Input Choice: ");
        scanf("%d", &menu);
        
        switch (menu) {
            case 0:
                exit(0);
            case 1:
                q.front = NULL;
                q.rear = NULL;
                break;
            case 2:
                printf("Popped Value %d\n", delete(&q));
                break;
            case 3:
                printf("Give element: ");
                scanf("%d", &elm);
                insert(&q, elm);
                break;
            case 4:
                printQueue(q);
                break;
            default:
                printf("Wrong choice\n");
        }
    }
    
    return 0;
}
