#include <stdio.h>

#define NUM_NODES 7
#define NO_LINK   0

char *nodeName[] = {"A", "B", "C", "D", "E", "F", "G"};

int adj[NUM_NODES][NUM_NODES] = {

 { 0,  6,  0,  0,  0,  0,  0 },
 { 6,  0, 11,  5,  0,  0,  0 },
 { 0, 11,  0,  0,  0,  0, 25 },
 { 0,  5,  0,  0, 22, 17,  0 },
 { 0,  0,  0, 22,  0, 10,  0 },
 { 0,  0,  0, 17, 10,  0, 22 },
 { 0,  0, 25,  0,  0, 22,  0 }
};

int bfsQueue[NUM_NODES];
int qFront = 0;
int qRear  = 0;

void enqueue(int node) { bfsQueue[qRear++] = node; }
int  dequeue()         { return bfsQueue[qFront++]; }
int  queueEmpty()      { return qFront == qRear; }

void bfsAnalysis(int startNode) {
    int i;

    printf("\n--- BFS starting from Workstation %s ---\n", nodeName[startNode]);

    int neighbors[NUM_NODES];
    int transferTimes[NUM_NODES];
    int neighborCount = 0;

    printf("\nChecking direct connections to %s:\n", nodeName[startNode]);
    for (i = 0; i < NUM_NODES; i++) {
        if (i == startNode) continue;

        if (adj[startNode][i] != NO_LINK) {
            printf("  %s -> %s : %d min  [DIRECT LINK FOUND]\n",
                   nodeName[startNode], nodeName[i], adj[startNode][i]);
            neighbors[neighborCount]     = i;
            transferTimes[neighborCount] = adj[startNode][i];
            neighborCount++;
        } else {
            printf("  %s -> %s : no direct link\n",
                   nodeName[startNode], nodeName[i]);
        }
    }


    printf(" Direct Neighbors of %s\n", nodeName[startNode]);

    if (neighborCount == 0) {
        printf(" No direct connections found.\n");
        return;
    }

    printf(" Workstation | Transfer Time (min)\n");
   
    for (i = 0; i < neighborCount; i++) {
        printf("  %-10s |   %d min\n", nodeName[neighbors[i]], transferTimes[i]);
    }

    int highRiskNode = neighbors[0];
    int highRiskTime = transferTimes[0];

    for (i = 1; i < neighborCount; i++) {
        if (transferTimes[i] > highRiskTime) {
            highRiskTime = transferTimes[i];
            highRiskNode = neighbors[i];
        }
    }

   
    printf(" Highest Risk Contact\n");
    printf(" Most at-risk workstation : %s\n", nodeName[highRiskNode]);
    printf(" Data transfer time       : %d minutes\n", highRiskTime);
    printf("\n Workstation %s had the HIGHEST data transfer\n", nodeName[highRiskNode]);
    printf(" time with the suspected breach point (%s).\n", nodeName[startNode]);
    printf(" It is most likely to have received stolen data\n");
    printf(" and has the highest risk of compromise.\n");
}

int main() {
    int i, j;
    int suspected;

   
    printf("  Q4: Cyber Breach Detection via BFS         \n");
    

    printf("\nEnterprise Communication Network:\n");
    printf("(Values = data transfer time in minutes; 0 = no connection)\n\n");
    printf("      ");
    for (i = 0; i < NUM_NODES; i++) printf("  %s  ", nodeName[i]);
    printf("\n");
    for (i = 0; i < NUM_NODES; i++) {
        printf("  %s   ", nodeName[i]);
        for (j = 0; j < NUM_NODES; j++)
            printf(" %3d ", adj[i][j]);
        printf("\n");
    }

    printf("\nWorkstation labels: A=0, B=1, C=2, D=3, E=4, F=5, G=6\n");
    printf("Enter the suspected compromised workstation number (0 to %d): ", NUM_NODES - 1);
    scanf("%d", &suspected);

    if (suspected < 0 || suspected >= NUM_NODES) {
        printf("Invalid input! Using A (0) as default.\n");
        suspected = 0;
    }

    printf("\nInvestigating breach from Workstation %s...\n", nodeName[suspected]);

    bfsAnalysis(suspected);

    return 0;
}