#include <stdio.h>

#define MAX_SIZE 20

struct Job {
    char id;
    int  priority;
};

struct Job heap[MAX_SIZE];
int heapSize = 0;

void swap(int i, int j) {
    struct Job temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void heapifyUp(int i) {
    int parent = (i - 1) / 2;

    while (i > 0 && heap[i].priority > heap[parent].priority) {
        printf("  Swap %c(%d) with parent %c(%d)\n",
               heap[i].id, heap[i].priority,
               heap[parent].id, heap[parent].priority);
        swap(i, parent);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void heapifyDown(int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left < heapSize && heap[left].priority > heap[largest].priority)
        largest = left;

    if (right < heapSize && heap[right].priority > heap[largest].priority)
        largest = right;

    if (largest != i) {
        printf("  Swap %c(%d) with child %c(%d)\n",
               heap[i].id, heap[i].priority,
               heap[largest].id, heap[largest].priority);
        swap(i, largest);
        heapifyDown(largest);
    }
}

void insertJob(char id, int priority) {

    heap[heapSize].id       = id;
    heap[heapSize].priority = priority;

    heapifyUp(heapSize);

    heapSize++;
}

void deleteJob(int priority) {

    int idx = -1;
    int i;
    for (i = 0; i < heapSize; i++) {
        if (heap[i].priority == priority) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Job with priority %d not found!\n", priority);
        return;
    }

    printf("   Removing Job %c (priority %d) at index %d\n",
           heap[idx].id, heap[idx].priority, idx);

    heap[idx] = heap[heapSize - 1];
    heapSize--;

    heapifyUp(idx);
    heapifyDown(idx);
}

void displayHeap(char *label) {
    int i;
    printf("\n");
    printf(" %s\n", label);
    printf("\n");
    printf("Array contents (index 0 = root):\n");
    printf(" Index | Job ID | Priority\n");
    printf(" \n");
    for (i = 0; i < heapSize; i++) {
        printf("  %3d  |   %c    |    %d\n", i, heap[i].id, heap[i].priority);
    }

    printf("\nTree (level-order view):\n");
    printf(" Level 0 (root):  %c(%d)\n", heap[0].id, heap[0].priority);

    if (heapSize > 1) {
        printf(" Level 1:         ");
        for (i = 1; i <= 2 && i < heapSize; i++)
            printf("%c(%d)  ", heap[i].id, heap[i].priority);
        printf("\n");
    }
    if (heapSize > 3) {
        printf(" Level 2:         ");
        for (i = 3; i <= 6 && i < heapSize; i++)
            printf("%c(%d)  ", heap[i].id, heap[i].priority);
        printf("\n");
    }
    if (heapSize > 7) {
        printf(" Level 3:         ");
        for (i = 7; i <= 14 && i < heapSize; i++)
            printf("%c(%d)  ", heap[i].id, heap[i].priority);
        printf("\n");
    }

    printf("\nMax-Heap check: root = %c with highest priority %d\n",
           heap[0].id, heap[0].priority);
}

int main() {
    int i;

    int  priorities[] = {42, 17, 93, 28, 65, 81, 54, 60, 99, 73, 88};
    char ids[]        = "ABCDEFGHIJK";
    int  n            = 11;

   
    printf("  Q1: Cloud Job Scheduler - Max-Heap      \n");
  

    printf("\n--- TASK 1 & 2: Building Max-Heap from array ---\n");
    printf("Inserting jobs one by one:\n\n");

    for (i = 0; i < n; i++) {
        printf("Insert Job %c (priority %d):\n", ids[i], priorities[i]);
        insertJob(ids[i], priorities[i]);
    }

    displayHeap("HEAP AFTER INITIAL BUILD");

    printf("\n--- TASK 3: Inserting urgent Job L (priority 100) ---\n");
    insertJob('L', 100);
    displayHeap("HEAP AFTER INSERTING JOB L (priority 100)");

    printf("\n--- TASK 4: Removing Job with priority 100 ---\n");
    deleteJob(100);
    displayHeap("HEAP AFTER REMOVING PRIORITY 100");

    return 0;
}