#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>


// Data structure to represent the grid
typedef struct {
    int m; // Number of rows
    int n; // Number of columns
    int start_row; // Start cell row
    int start_col; // Start cell column
    int** grid;
} Grid;

// Data structure to represent a cell
typedef struct {
    int row;
    int col;
    int time; // Time to reach this cell from the start location
} Cell;

// Queue data structure for BFS
typedef struct {
    Cell* array;
    int front;
    int rear;
} Queue;

void findShortestPath(Grid* grid, int cornerRow, int cornerCol);
bool isCornerCell(Grid* grid, int row, int col);


void initializeQueue(Queue* queue, int size);
bool isQueueEmpty(Queue* q);
void enqueue(Queue* queue, Cell cell, int size);
void allocateGridMemory(Grid* grid);
void freeGridMemory(Grid* grid);
bool isValidRoom(Grid* grid, int row, int col);
Cell dequeue(Queue* q, int size);
bool isQueueFull(Queue* queue, int size);

void findTravelTime(Grid* grid, int* times);
int minDistance(int* dist, bool* visited, int size);