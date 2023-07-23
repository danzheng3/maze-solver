#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "main.h"


// Function to find the minimum distance vertex from the set of vertices
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

// Function to find the travel time from the start location to all four corners
void findTravelTime(Grid* grid, int* times) {
    int num_vertices = grid->m * grid->n;

    // Create arrays for distance and visited status of each vertex
    int* dist = (int*)malloc(num_vertices * sizeof(int));
    bool* visited = (bool*)malloc(num_vertices * sizeof(bool));

    // Initialize distance and visited arrays
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // Get the start location index in the 1D representation of the grid
    int start_index = grid->start_row * grid->n + grid->start_col;
    dist[start_index] = 0;

    // Directions for up, down, left, and right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Find the shortest path from the start location to all cells
    for (int count = 0; count < num_vertices - 1; count++) {
        // Find the vertex with the minimum distance from the set of vertices not yet processed
        int u = minDistance(dist, visited, num_vertices);
        visited[u] = true;

        // If the vertex is not a room, skip it
        int row = u / grid->n;
        int col = u % grid->n;
        if (!isValidRoom(grid, row, col)) {
            continue;
        }

        // Explore neighbors and update their distances
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

    // Find the travel time for each corner
    times[0] = dist[0]; // Top left corner
    times[1] = dist[grid->n - 1]; // Top right corner
    times[2] = dist[(grid->m - 1) * grid->n + grid->n - 1]; // Bottom right corner
    times[3] = dist[(grid->m - 1) * grid->n]; // Bottom left corner

    for(int i=0; i<4; i++) {
        if(times[i]==INT_MAX) {
            times[i]=-1;
        }
    }

    free(dist);
    free(visited);
}
