#include <stdio.h>

#define NUM_HUBS  7
#define MAX_EDGES 50

char *hubName[] = {"A", "B", "C", "D", "E", "F", "G"};

struct Edge {
    int hub1;
    int hub2;
    int cost;
};

struct Edge edges[MAX_EDGES];
int totalEdges = 0;

int parent[NUM_HUBS];

void setupUnionFind() {
    int i;
    for (i = 0; i < NUM_HUBS; i++)
        parent[i] = i;
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return 0;
    parent[rootX] = rootY;
    return 1;
}

void sortEdgesByCost() {
    int i, j;
    struct Edge temp;
    for (i = 0; i < totalEdges - 1; i++) {
        for (j = 0; j < totalEdges - i - 1; j++) {
            if (edges[j].cost > edges[j+1].cost) {
                temp         = edges[j];
                edges[j]     = edges[j+1];
                edges[j+1]   = temp;
            }
        }
    }
}

int main() {
    int i, j;

    int adj[NUM_HUBS][NUM_HUBS] = {
     { 0,  6,  0,  0,  0,  0,  0 },
     { 6,  0, 11,  5,  0,  0,  0 },
     { 0, 11,  0,  0,  0,  0, 25 },
     { 0,  5,  0,  0, 22, 17,  0 },
     { 0,  0,  0, 22,  0, 10,  0 },
     { 0,  0,  0, 17, 10,  0, 22 },
     { 0,  0, 25,  0,  0, 22,  0 }
    };


    printf("  Q3: Fiber-Optic Network - Kruskal's MST    \n");
   

    printf("\n--- TASK 1: Adjacency Matrix (cost in millions $) ---\n\n");
    printf("     ");
    for (i = 0; i < NUM_HUBS; i++) printf("  %s  ", hubName[i]);
    printf("\n");
    for (i = 0; i < NUM_HUBS; i++) {
        printf("  %s  ", hubName[i]);
        for (j = 0; j < NUM_HUBS; j++)
            printf(" %3d ", adj[i][j]);
        printf("\n");
    }

    totalEdges = 0;
    for (i = 0; i < NUM_HUBS; i++) {
        for (j = i + 1; j < NUM_HUBS; j++) {
            if (adj[i][j] != 0) {
                edges[totalEdges].hub1 = i;
                edges[totalEdges].hub2 = j;
                edges[totalEdges].cost = adj[i][j];
                totalEdges++;
            }
        }
    }

    sortEdgesByCost();

    printf("\nAll edges sorted cheapest first:\n");
    printf(" Edge        | Cost ($M)\n");

    for (i = 0; i < totalEdges; i++)
        printf("  %s -- %s    |   %d\n",
               hubName[edges[i].hub1], hubName[edges[i].hub2], edges[i].cost);

    printf("\n--- TASK 2: Kruskal's Algorithm ---\n\n");
    printf(" Step | Edge      | Cost | Decision\n");
  

    setupUnionFind();

    struct Edge mst[NUM_HUBS - 1];
    int mstCount  = 0;
    int totalCost = 0;
    int step      = 1;

    for (i = 0; i < totalEdges && mstCount < NUM_HUBS - 1; i++) {
        int h1 = edges[i].hub1;
        int h2 = edges[i].hub2;
        int c  = edges[i].cost;

        if (unite(h1, h2)) {
            mst[mstCount++] = edges[i];
            totalCost += c;
            printf("  %3d  | %s -- %s    |  %3d | ADDED - connects two hubs\n",
                   step++, hubName[h1], hubName[h2], c);
        } else {
            printf("  %3d  | %s -- %s    |  %3d | SKIPPED - would create a cycle\n",
                   step++, hubName[h1], hubName[h2], c);
        }
    }

    printf(" TASK 3: Selected Fiber-Optic Links (MST) \n");
    printf(" Hub-to-Hub Link         | Cost ($M)\n");
    printf("\n");
    for (i = 0; i < mstCount; i++)
        printf("  %s   <--->   %s         |   %d\n",
               hubName[mst[i].hub1], hubName[mst[i].hub2], mst[i].cost);

    printf("\n--- TASK 4: Total Installation Cost ---\n");
    printf(" Total MST Cost = %d million dollars\n", totalCost);
    printf(" All %d hubs connected using %d fiber-optic links.\n", NUM_HUBS, mstCount);

    return 0;
}