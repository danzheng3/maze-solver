#include "main.h"

int main(int argc, char* argv[]) {
    char* option = argv[1];
    FILE* inputFile = fopen(argv[2],"r");

    if(inputFile==NULL) {
        return EXIT_FAILURE;
    }

    Grid grid;
    int top_left, top_right, bottom_right, bottom_left;
    fscanf(inputFile, "(%d,%d)\n", &(grid.m), &(grid.n));
    fscanf(inputFile, "(%d,%d)\n", &(grid.start_row), &(grid.start_col));

    int product=grid.m*grid.n;
    if (product/grid.m !=grid.n) {
        return EXIT_FAILURE;
    }

    if (grid.m <= 1 || grid.n <= 1) {
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    allocateGridMemory(&grid);

    for (int i = 0; i < grid.m; i++) {
        for (int j = 0; j < grid.n; j++) {
            char cell;
            fscanf(inputFile, "%c", &cell);
            grid.grid[i][j] = cell - '0'; 
        }
        fscanf(inputFile, "\n");
    }
    fclose(inputFile);

    if (!isValidRoom(&grid, grid.start_row, grid.start_col)) {
        freeGridMemory(&grid);
        return EXIT_FAILURE;
    }

    if ((strcmp(option,"-t"))==0) {
        int times[4];
        findTravelTime(&grid, times);

        // Find the travel time for each corner
        top_left = times[0];
        top_right = times[1];
        bottom_right = times[2];
        bottom_left = times[3];

        // Print the results
        fprintf(stdout, "%d,%d,%d,%d\n", top_left, top_right, bottom_right, bottom_left);
        freeGridMemory(&grid);

        return EXIT_SUCCESS;
    } else if(strcmp(option,"-p")==0) {
        findShortestPath(&grid,0,0);
        findShortestPath(&grid,0,grid.n-1);
        findShortestPath(&grid,grid.m-1,grid.n-1);
        findShortestPath(&grid,grid.m-1,0);

        freeGridMemory(&grid);

    } else if (strcmp(option,"-r")==0) {
        fprintf(stdout, "%d\n", shortestPath(&grid));
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}

void initializeQueue(Queue* queue, int size) {
    queue->array = (Cell*)malloc(size * sizeof(Cell));
    queue->front = -1;
    queue->rear = -1;
}

bool isQueueEmpty(Queue* q) {
    return q->front == -1;
}

bool isQueueFull(Queue* queue, int size) {
    return (queue->front == 0 && queue->rear == size - 1) || (queue->front == queue->rear + 1);
}

void enqueue(Queue* queue, Cell cell, int size) {
    if (isQueueFull(queue, size)) {
        return; 
    }

    if (isQueueEmpty(queue)) {
        queue->front = 0;
        queue->rear = 0;
    } else if (queue->rear == size - 1) {
        queue->rear = 0;
    } else {
        queue->rear++;
    }

    queue->array[queue->rear] = cell;
}

void allocateGridMemory(Grid* grid) {
    grid->grid = (int**)malloc(grid->m * sizeof(int*));
    for (int i = 0; i < grid->m; i++) {
        grid->grid[i] = (int*)malloc(grid->n * sizeof(int));
    }
}

void freeGridMemory(Grid* grid) {
    for (int i = 0; i < grid->m; i++) {
        free(grid->grid[i]);
    }
    free(grid->grid);
}

bool isValidRoom(Grid* grid, int row, int col) {
    int m=grid->m;
    int n=grid->n;

    if (grid->grid[0][0] == 1 || grid->grid[0][n - 1] == 1 ||
        grid->grid[m - 1][0] == 1 || grid->grid[m - 1][n - 1] == 1) {
        return false;
    }

    int product =m*n;
    if (product/m !=n) {
        return false;
    }
    return (row >= 0 && row < grid->m && col >= 0 && col < grid->n && grid->grid[row][col] == 0);
}


Cell dequeue(Queue* queue, int size) {
    Cell cell = {0, 0, 0};

    if (isQueueEmpty(queue)) {
        return cell;
    }

    cell = queue->array[queue->front];

    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else if (queue->front == size - 1) {
        queue->front = 0;
    } else {
        queue->front++;
    }

    return cell;
}
