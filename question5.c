#include <stdio.h>
#include <limits.h>

#define NUM_BRANCHES  10
#define MAX_EDGES     20
#define INFINITY      INT_MAX

char *branchName[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

struct Edge {
    int from;
    int to;
    int weight;
};

struct Edge edges[MAX_EDGES];
int numEdges = 0;

void addEdge(int from, int to, int weight) {
    edges[numEdges].from   = from;
    edges[numEdges].to     = to;
    edges[numEdges].weight = weight;
    numEdges++;
}

void bellmanFord(int source) {
    int dist[NUM_BRANCHES];
    int prev[NUM_BRANCHES];
    int i, pass, updated;

    for (i = 0; i < NUM_BRANCHES; i++) {
        dist[i] = INFINITY;
        prev[i] = -1;
    }
    dist[source] = 0;

    printf("\nInitialisation:\n");
    printf("  dist[%s] = 0  (source branch)\n", branchName[source]);
    printf("  All other branches = INFINITY (not yet reached)\n");

    printf("\n Relaxation Passes \n");

    for (pass = 1; pass <= NUM_BRANCHES - 1; pass++) {
        updated = 0;
        printf("\nPass %d:\n", pass);

        for (i = 0; i < numEdges; i++) {
            int u = edges[i].from;
            int v = edges[i].to;
            int w = edges[i].weight;

            if (dist[u] == INFINITY) continue;

            if (dist[u] + w < dist[v]) {
                printf("  Relax %s -> %s (weight %2d):  dist[%s] = ",
                       branchName[u], branchName[v], w, branchName[v]);
                if (dist[v] == INFINITY)
                    printf("INF  ->  %d\n", dist[u] + w);
                else
                    printf("%d  ->  %d\n", dist[v], dist[u] + w);

                dist[v] = dist[u] + w;
                prev[v] = u;
                updated = 1;
            }
        }

        if (!updated) {
            printf("  No updates this pass. Algorithm converged early.\n");
            break;
        }
    }

    printf("\n--- Negative-Weight Cycle Check ---\n");
    int hasNegCycle = 0;

    for (i = 0; i < numEdges; i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        int w = edges[i].weight;

        if (dist[u] != INFINITY && dist[u] + w < dist[v]) {
            printf("  *** NEGATIVE CYCLE DETECTED: edge %s -> %s ***\n",
                   branchName[u], branchName[v]);
            printf("  WARNING: This transaction route is exploitable / unstable!\n");
            hasNegCycle = 1;
        }
    }
    if (!hasNegCycle) {
        printf("  No negative-weight cycles found. Network is financially stable.\n");
    }

    printf(" Shortest Transaction Paths from %s\n", branchName[source]);
    printf("\n");
    printf(" Branch | Min Cost | Path\n");

    for (i = 0; i < NUM_BRANCHES; i++) {
        printf("   %s    |  ", branchName[i]);

        if (dist[i] == INFINITY) {
            printf("  INF     | Unreachable from %s\n", branchName[source]);
        } else {
            printf("  %-6d  | ", dist[i]);

            int path[NUM_BRANCHES + 1];
            int pathLen = 0;
            int cur = i;

            while (cur != -1) {
                path[pathLen++] = cur;
                cur = prev[cur];
            }

            int k;
            for (k = pathLen - 1; k >= 0; k--) {
                printf("%s", branchName[path[k]]);
                if (k > 0) printf(" -> ");
            }
            printf("\n");
        }
    }
}

int main() {
    int i;
    
    printf("  Q5: Banking Risk Propagation - Bellman-Ford\n");

    addEdge(0, 1,  4);
    addEdge(0, 3, 16);
    addEdge(1, 2,  6);
    addEdge(1, 9,  7);
    addEdge(3, 9,  6);
    addEdge(2, 6,  9);
    addEdge(9, 5,  3);
    addEdge(9, 4,  7);
    addEdge(4, 8,  2);
    addEdge(5, 8, 10);
    addEdge(6, 7, 13);

    printf("\nTransaction Network Edges (directed):\n");
    printf(" From -> To  | Cost\n");
    for (i = 0; i < numEdges; i++) {
        printf("   %s  ->  %s  |  %3d\n",
               branchName[edges[i].from],
               branchName[edges[i].to],
               edges[i].weight);
    }

    printf("\nRunning Bellman-Ford from Branch A...\n");
    bellmanFord(0);

    return 0;
}