#include "main.h"

#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>


void findShortestPath(Grid* grid, int cornerRow, int cornerCol) {
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; 

    int queueSize = grid->m * grid->n;
    Queue queue;
    initializeQueue(&queue, queueSize);

    // need visited cells
    bool visited[grid->m][grid->n];
    for (int i = 0; i < grid->m; i++) {
        for (int j = 0; j < grid->n; j++) {
            visited[i][j] = false;
        }
    }

    Cell startCell = {grid->start_row, grid->start_col};
    enqueue(&queue, startCell, queueSize);
    visited[grid->start_row][grid->start_col] = true;

    //store previous cells
    Cell prev[grid->m][grid->n];
    for (int i = 0; i < grid->m; i++) {
        for (int j = 0; j < grid->n; j++) {
            prev[i][j] = startCell; //
        }
    }

    while (!isQueueEmpty(&queue)) {
        Cell currentCell = dequeue(&queue, queueSize);

        if (currentCell.row == cornerRow && currentCell.col == cornerCol) {
            Cell path[grid->m * grid->n]; 
            int pathLength = 0;
            Cell backtrackCell = currentCell;

            while (!(backtrackCell.row == grid->start_row && backtrackCell.col == grid->start_col)) {
                path[pathLength++] = backtrackCell;
                backtrackCell = prev[backtrackCell.row][backtrackCell.col];
            }

            printf("(%d,%d)", grid->start_row, grid->start_col);
            for (int i = pathLength - 1; i >= 0; i--) {
                printf(",(%d,%d)", path[i].row, path[i].col);
            }
            printf("\n");
            free(queue.array);

            return;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = currentCell.row + directions[i][0];
            int newCol = currentCell.col + directions[i][1];

            if (isValidRoom(grid, newRow, newCol) && !visited[newRow][newCol]) {
                Cell newCell = {newRow, newCol};
                enqueue(&queue, newCell, queueSize);
                visited[newRow][newCol] = true;
                prev[newRow][newCol] = currentCell;
            }
        }
    }
    free(queue.array);

    printf("-1\n");
}

bool isCornerCell(Grid* grid, int row, int col) {
    return ((row == 0 || row == grid->m - 1) && (col == 0 || col == grid->n - 1));
}




