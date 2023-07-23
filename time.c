#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "main.h"


int minDistance(int* dist, bool* visited, int size) {
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < size; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void findTravelTime(Grid* grid, int* times) {
    int num_vertices = grid->m * grid->n;

    int* dist = (int*)malloc(num_vertices * sizeof(int));
    bool* visited = (bool*)malloc(num_vertices * sizeof(bool));

    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    int start_index = grid->start_row * grid->n + grid->start_col;
    dist[start_index] = 0;

    //direcitons
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int count = 0; count < num_vertices - 1; count++) {
        //shortest path:vertex
        int u = minDistance(dist, visited, num_vertices);
        visited[u] = true;

        int row = u / grid->n;
        int col = u % grid->n;
        if (!isValidRoom(grid, row, col)) {
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int nextRow = row + dr[i];
            int nextCol = col + dc[i];
            int v = nextRow * grid->n + nextCol;

            if (isValidRoom(grid, nextRow, nextCol) && !visited[v] && dist[u] != INT_MAX) {
                int new_dist = dist[u] + 1;
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                }
            }
        }
    }

    times[0] = dist[0]; 
    times[1] = dist[grid->n - 1]; 
    times[2] = dist[(grid->m - 1) * grid->n + grid->n - 1];
    times[3] = dist[(grid->m - 1) * grid->n];

    for(int i=0; i<4; i++) {
        if(times[i]==INT_MAX) {
            times[i]=-1;
        }
    }

    free(dist);
    free(visited);
}
