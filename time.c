#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "main.h"


/*int minDistance(int* dist, bool* visited, int size) {
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
    int countPaths=0;

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


        for (int i = 0; i < 4; i++) {
            int nextRow = row + dr[i];
            int nextCol = col + dc[i];
            int v = nextRow * grid->n + nextCol;

            if (isValidRoom(grid, nextRow, nextCol) && !visited[v] && dist[u] != INT_MAX) {
                int new_dist = dist[u] + 1;
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;

                    if (v==0 || v==grid->n-1 || v== (grid->m-1)*grid->n+grid->n -1 || v==(grid->m-1)*grid->n) {
                        countPaths++;

                        if(countPaths==4) {
                            break;
                        }
                    }
                }
            }
        }

        if (countPaths==4) {
            break;
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
    return;
}*/




/*void findTravelTime(Grid* grid, int* times) {
    int num_vertices = grid->m * grid->n;
    int start_index = grid->start_row * grid->n + grid->start_col;

    int* dist = (int*)malloc(num_vertices * sizeof(int));
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX;
    }

    //direcitons
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    Queue queue;
    initializeQueue(&queue, num_vertices);

    // Enqueue the starting point
    Cell start_cell = {grid->start_row, grid->start_col, 0};
    enqueue(&queue, start_cell, num_vertices);
    dist[start_index] = 0;

    int countPaths = 0;

    while (!isQueueEmpty(&queue) && countPaths < 4) {
        Cell current_cell = dequeue(&queue, num_vertices);
        int row = current_cell.row;
        int col = current_cell.col;
        int current_index = row * grid->n + col;

        // Check if the current cell is a corner cell
        if ((row == 0 && col == 0) || (row == 0 && col == grid->n - 1) ||
            (row == grid->m - 1 && col == 0) || (row == grid->m - 1 && col == grid->n - 1)) {
            times[countPaths++] = current_cell.time;
        }

        for (int i = 0; i < 4; i++) {
            int nextRow = row + dr[i];
            int nextCol = col + dc[i];
            int nextIndex = nextRow * grid->n + nextCol;

            if (nextRow >= 0 && nextRow < grid->m && nextCol >= 0 && nextCol < grid->n &&
                grid->grid[nextRow][nextCol] == 0){ // && dist[current_index] != INT_MAX) {
                int new_dist = dist[current_index] + 1;
                if (new_dist < dist[nextIndex]) {
                    dist[nextIndex] = new_dist;
                    Cell next_cell = {nextRow, nextCol, new_dist};
                    enqueue(&queue, next_cell, num_vertices);
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        if (times[i] == INT_MAX) {
            times[i] = -1;
        }
    }

    free(dist);
}  */


void findTravelTime(Grid* grid, int* times) {
    int num_vertices = grid->m * grid->n;
    int start_index = grid->start_row * grid->n + grid->start_col;

    int* dist = (int*)malloc(num_vertices * sizeof(int));
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX;
    }

    //direcitons
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    Queue queue;
    initializeQueue(&queue, num_vertices);

    Cell start_cell = {grid->start_row, grid->start_col, 0};
    enqueue(&queue, start_cell, num_vertices);
    dist[start_index] = 0;

    bool isCornerReachable[4] = {false}; // 0 topleft, 1 topright, 2 bottomright, 3 bottomleft
    int numCornersReached = 0;

    while (!isQueueEmpty(&queue) && numCornersReached < 4) {
        Cell current_cell = dequeue(&queue, num_vertices);
        int row = current_cell.row;
        int col = current_cell.col;
        int current_index = row * grid->n + col;

        //is a corner cell ?
        if ((row == 0 && col == 0) && !isCornerReachable[0]) {
            isCornerReachable[0] = true;
            times[0] = current_cell.time;
            numCornersReached++;
        } else if ((row == 0 && col == grid->n - 1) && !isCornerReachable[1]) {
            isCornerReachable[1] = true;
            times[1] = current_cell.time;
            numCornersReached++;
        } else if ((row == grid->m - 1 && col == grid->n - 1) && !isCornerReachable[2]) {
            isCornerReachable[2] = true;
            times[2] = current_cell.time;
            numCornersReached++;
        } else if ((row == grid->m - 1 && col == 0) && !isCornerReachable[3]) {
            isCornerReachable[3] = true;
            times[3] = current_cell.time;
            numCornersReached++;
        }

        if(numCornersReached==4) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nextRow = row + dr[i];
            int nextCol = col + dc[i];
            int nextIndex = nextRow * grid->n + nextCol;

            if (nextRow >= 0 && nextRow < grid->m && nextCol >= 0 && nextCol < grid->n &&
                grid->grid[nextRow][nextCol] == 0) {
                int new_dist = dist[current_index] + 1;
                if (new_dist < dist[nextIndex]) {
                    dist[nextIndex] = new_dist;
                    Cell next_cell = {nextRow, nextCol, new_dist};
                    enqueue(&queue, next_cell, num_vertices);
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        if (!isCornerReachable[i]) {
            times[i] = -1;
        }
    }

    free(dist);
    free(queue.array);
}

