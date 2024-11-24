/*
ID: 
LANG: C
TASK: wormhole
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_N 12

typedef struct {
    int x, y;
} Wormhole;

int N;
Wormhole wormholes[MAX_N];
int partner[MAX_N];    // Pairing of wormholes
int next_right[MAX_N]; // Index of the next wormhole to the right in the same row

// Find the next wormhole to the right for each wormhole
void compute_next_right() {
    for (int i = 0; i < N; i++) {
        next_right[i] = -1;
        for (int j = 0; j < N; j++) {
            if (wormholes[j].y == wormholes[i].y && wormholes[j].x > wormholes[i].x) {
                if (next_right[i] == -1 || wormholes[j].x < wormholes[next_right[i]].x) {
                    next_right[i] = j;
                }
            }
        }
    }
}

// Check if a cycle exists for the current pairing
bool has_cycle() {
    for (int start = 0; start < N; start++) {
        int pos = start;
        for (int steps = 0; steps < N; steps++) { // At most N steps
            if (pos == -1) break;                // No more moves possible
            pos = next_right[pos];
            if (pos != -1) pos = partner[pos];
        }
        if (pos != -1) return true; // If we revisit, a cycle exists
    }
    return false;
}

// Recursive function to count valid pairings
int count_pairings() {
    // Find the first unpaired wormhole
    int i;
    for (i = 0; i < N; i++) {
        if (partner[i] == -1) break;
    }
    if (i == N) {
        // All wormholes are paired; check for cycles
        return has_cycle() ? 1 : 0;
    }

    int total = 0;
    // Try pairing i with every unpaired wormhole
    for (int j = i + 1; j < N; j++) {
        if (partner[j] == -1) {
            // Pair i and j
            partner[i] = j;
            partner[j] = i;

            // Recur for the remaining wormholes
            total += count_pairings();

            // Unpair i and j
            partner[i] = -1;
            partner[j] = -1;
        }
    }
    return total;
}

int main() {
    // Input reading
    FILE *fin = fopen("wormhole.in", "r");
    FILE *fout = fopen("wormhole.out", "w");

    fscanf(fin, "%d", &N);
    for (int i = 0; i < N; i++) {
        fscanf(fin, "%d %d", &wormholes[i].x, &wormholes[i].y);
    }

    // Initialize the pairing and compute next_right
    for (int i = 0; i < N; i++) {
        partner[i] = -1;
    }
    compute_next_right();

    // Count all valid pairings that create a cycle
    int result = count_pairings();
    fprintf(fout, "%d\n", result);

    fclose(fin);
    fclose(fout);

    return 0;
}
