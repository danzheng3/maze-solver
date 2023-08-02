#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateGrid(int grid[1000][1000]) {
    // Initialize random number generator with the current time
    srand(time(NULL));

    int temp=0;

    // Fill the grid with random values (0s and 1s)
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if ((i == 0 && j == 0) || (i == 0 && j == 999) || (i == 999 && j == 0) || (i == 999 && j == 999)) {
                // Set the corners to 0 (rooms)
                grid[i][j] = 0;
            } else {
                // Set other cells randomly to 0 or 1
                temp = rand() % 40;
                if (temp%13==0 || temp%11==0) {
                    grid[i][j]=1;
                } else {
                    grid[i][j] = 0;
                }
            }
        }
    }
}

void writeGridToFile(int grid[1000][1000]) {
    FILE *file = fopen("grid.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            fprintf(file, "%d", grid[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    int grid[1000][1000];
    generateGrid(grid);
    writeGridToFile(grid);

    return 0;
}
