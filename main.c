#include "main.h"

int main(int argc, char* argv[]) {
    char* option = argv[1];
    FILE* inputFile = fopen(argv[2],"r");

    if(inputFile==NULL) {
        fprintf(stderr, "error with inputfile\n");
        return EXIT_FAILURE;
    }

    // Read input data from the file
    Grid grid;
    int top_left, top_right, bottom_right, bottom_left;
    fscanf(inputFile, "(%d,%d)\n", &(grid.m), &(grid.n));
    fscanf(inputFile, "(%d,%d)\n", &(grid.start_row), &(grid.start_col));

    if (grid.m <= 1 || grid.n <= 1) {
        fprintf(stderr, "Invalid grid size.\n");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    allocateGridMemory(&grid);

    for (int i = 0; i < grid.m; i++) {
        for (int j = 0; j < grid.n; j++) {
            char cell;
            fscanf(inputFile, "%c", &cell);
            grid.grid[i][j] = cell - '0'; // Convert char to int (0 or 1)
        }
        fscanf(inputFile, "\n");
    }
    fclose(inputFile);

    // Check if the start location is a room
    if (!isValidRoom(&grid, grid.start_row, grid.start_col)) {
        fprintf(stderr, "Start location is not a valid room.\n");
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
        findShortestPath2(&grid,0,0);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}

// Function to initialize the queue
void initializeQueue(Queue* queue, int size) {
    queue->array = (Cell*)malloc(size * sizeof(Cell));
    queue->front = -1;
    queue->rear = -1;
}


// Function to check if the queue is empty
bool isQueueEmpty(Queue* q) {
    return q->front == -1;
}

bool isQueueFull(Queue* queue, int size) {
    return (queue->front == 0 && queue->rear == size - 1) || (queue->front == queue->rear + 1);
}

void enqueue(Queue* queue, Cell cell, int size) {
    if (isQueueFull(queue, size)) {
        return; // Queue is full
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

// Function to dynamically allocate memory for the grid
void allocateGridMemory(Grid* grid) {
    grid->grid = (int**)malloc(grid->m * sizeof(int*));
    for (int i = 0; i < grid->m; i++) {
        grid->grid[i] = (int*)malloc(grid->n * sizeof(int));
    }
}

// Function to free the memory allocated for the grid
void freeGridMemory(Grid* grid) {
    for (int i = 0; i < grid->m; i++) {
        free(grid->grid[i]);
    }
    free(grid->grid);
}

// Function to check if a cell is a valid room (not a wall and within the grid boundaries)
bool isValidRoom(Grid* grid, int row, int col) {
    int m=grid->m;
    int n=grid->n;

    if (grid->grid[0][0] == 1 || grid->grid[0][n - 1] == 1 ||
        grid->grid[m - 1][0] == 1 || grid->grid[m - 1][n - 1] == 1) {
        return false;
    }
    return (row >= 0 && row < grid->m && col >= 0 && col < grid->n && grid->grid[row][col] == 0);
}

// Function to dequeue a cell
Cell dequeue(Queue* queue, int size) {
    Cell cell = {0, 0, 0}; // Initialize with default values

    if (isQueueEmpty(queue)) {
        return cell; // Queue is empty
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
