#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>



typedef struct {
    int m; 
    int n; 
    int start_row; 
    int start_col; 
    int** grid;
} Grid;


typedef struct {
    int row;
    int col;
    int time; 
    int wallsRemoved;
} Cell;


typedef struct {
    Cell* array;
    int front;
    int rear;
} Queue;


bool isCornerCell(Grid* grid, int row, int col);
void findShortestPath(Grid* grid, int cornerRow, int cornerCol, Cell** prev, Cell* path);

int shortestPath(Grid* grid);
bool isValidCell(int row, int col, int m, int n);


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