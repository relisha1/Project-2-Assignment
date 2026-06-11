#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20

struct Passenger {
    char name[30];
    int  riskScore;
};

struct Passenger heap[MAX_SIZE];
int heapSize = 0;

void swap(int i, int j) {
    struct Passenger temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void heapifyUp(int i) {
    int parent = (i - 1) / 2;
    while (i > 0 && heap[i].riskScore > heap[parent].riskScore) {
        printf("   %s(%d) moves up over %s(%d)\n",
               heap[i].name, heap[i].riskScore,
               heap[parent].name, heap[parent].riskScore);
        swap(i, parent);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void heapifyDown(int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left  < heapSize && heap[left].riskScore  > heap[largest].riskScore)
        largest = left;
    if (right < heapSize && heap[right].riskScore > heap[largest].riskScore)
        largest = right;

    if (largest != i) {
        printf("  %s(%d) moves down, %s(%d) comes up\n",
               heap[i].name, heap[i].riskScore,
               heap[largest].name, heap[largest].riskScore);
        swap(i, largest);
        heapifyDown(largest);
    }
}

void insertPassenger(char *name, int score) {

    strcpy(heap[heapSize].name, name);
    heap[heapSize].riskScore = score;

    heapifyUp(heapSize);
    heapSize++;
}

struct Passenger extractMax() {
    struct Passenger top = heap[0];

    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);

    return top;
}

void deleteByScore(int score) {
    int idx = -1;
    int i;
    for (i = 0; i < heapSize; i++) {
        if (heap[i].riskScore == score) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Passenger with risk score %d not found!\n", score);
        return;
    }
    printf("   Removing %s (risk %d) at index %d\n",
           heap[idx].name, heap[idx].riskScore, idx);

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
    printf(" Index | Name     | Risk Score\n");
    printf(" \n");
    for (i = 0; i < heapSize; i++) {
        printf("  %3d  | %-8s |    %d\n", i, heap[i].name, heap[i].riskScore);
    }
    printf("\nTree (level-order view):\n");
    printf(" Level 0 (root):  %s(%d)\n", heap[0].name, heap[0].riskScore);
    if (heapSize > 1) {
        printf(" Level 1:         ");
        for (i = 1; i <= 2 && i < heapSize; i++)
            printf("%s(%d)  ", heap[i].name, heap[i].riskScore);
        printf("\n");
    }
    if (heapSize > 3) {
        printf(" Level 2:         ");
        for (i = 3; i <= 6 && i < heapSize; i++)
            printf("%s(%d)  ", heap[i].name, heap[i].riskScore);
        printf("\n");
    }
    printf("\nHighest risk passenger (root): %s with score %d\n",
           heap[0].name, heap[0].riskScore);
}

void showScreeningOrder() {

    struct Passenger copy[MAX_SIZE];
    int copySize = heapSize;
    int i;
    for (i = 0; i < heapSize; i++) copy[i] = heap[i];

    
    printf(" SCREENING ORDER (Highest Risk First)\n");
  
    printf(" Order | Name     | Risk Score\n");
    printf(" \n");

    int order = 1;
    while (heapSize > 0) {
        struct Passenger p = extractMax();
        printf("  %3d  | %-8s |    %d\n", order++, p.name, p.riskScore);
    }

    heapSize = copySize;
    for (i = 0; i < heapSize; i++) heap[i] = copy[i];
}

int main() {
    int i;

    char *names[]  = {"Alice", "Brian", "Chen", "Fatima", "Noah", "Sofia"};
    int   scores[] = {72,       55,      88,     63,       41,     79};
    int   n        = 6;

    printf("  Q2: Smart Airport Security - Passenger Heap\n");


    printf("\n--- TASK 1 & 2: Building Max-Heap from passenger list ---\n\n");
    for (i = 0; i < n; i++) {
        printf("Insert %s (risk score %d):\n", names[i], scores[i]);
        insertPassenger(names[i], scores[i]);
    }

    displayHeap("HEAP AFTER INITIAL BUILD");

    printf("\n--- TASK 3: Extracting screening order ---\n");
    showScreeningOrder();

    printf("\n--- TASK 4: New passenger 'Omar' arrives (risk score 98) ---\n");
    insertPassenger("Omar", 98);
    displayHeap("HEAP AFTER INSERTING OMAR (risk 98)");

    printf("\n--- TASK 5: Omar (risk 98) is cleared - removing ---\n");
    deleteByScore(98);
    displayHeap("HEAP AFTER REMOVING RISK SCORE 98");

    return 0;
}