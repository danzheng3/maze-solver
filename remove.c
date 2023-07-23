#include "main.h"

bool isValidCell(int row, int col, int m, int n) {
    return (row >= 0 && row < m && col >= 0 && col < n);
}

int shortestPath(Grid* grid) {
    int n = grid->m;
    int m = grid->n;
    int queueSize=m*n;
    int k = 1; // walls to be removed

    //visited cells+walls removed
    bool*** v = (bool***)malloc(n * sizeof(bool**));
    for (int i = 0; i < n; i++) {
        v[i] = (bool**)malloc(m * sizeof(bool*));
        for (int j = 0; j < m; j++) {
            v[i][j] = (bool*)malloc((k + 1) * sizeof(bool));
            for (int l = 0; l <= k; l++) {
                v[i][j][l] = false;
            }
        }
    }

    Queue q;
    initializeQueue(&q, n * m * (k + 1));

    Cell startCell;
    startCell.row = grid->start_row;
    startCell.col = grid->start_col;
    startCell.time = 0;
    startCell.wallsRemoved = 0;
    enqueue(&q, startCell, queueSize);
    v[startCell.row][startCell.col][0] = true;

    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    while (!isQueueEmpty(&q)) {
        Cell curr = dequeue(&q, queueSize);

        if (curr.row == 0 && curr.col == 0) {
            free(q.array);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    free(v[i][j]);
                }
                free(v[i]);
            }
            free(v);
            return curr.time;
        }

        for (int i = 0; i < 4; i++) {
            int rw = curr.row + delrow[i];
            int cl = curr.col + delcol[i];
            int walls = curr.wallsRemoved;

            if (isValidCell(rw, cl, n, m)) {
                if (grid->grid[rw][cl] == 0 && !v[rw][cl][walls]) {
                    v[rw][cl][walls] = true;
                    Cell nextCell;
                    nextCell.row = rw;
                    nextCell.col = cl;
                    nextCell.time = curr.time + 1;
                    nextCell.wallsRemoved = walls;
                    enqueue(&q, nextCell, queueSize);
                } else if (grid->grid[rw][cl] == 1 && walls < k && !v[rw][cl][walls + 1]) {
                    v[rw][cl][walls + 1] = true;
                    Cell nextCell;
                    nextCell.row = rw;
                    nextCell.col = cl;
                    nextCell.time = curr.time + 1;
                    nextCell.wallsRemoved = walls + 1;
                    enqueue(&q, nextCell, queueSize);
                }
            }
        }
    }
    free(q.array);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            free(v[i][j]);
        }
        free(v[i]);
    }
    free(v);
    return -1; 
}

