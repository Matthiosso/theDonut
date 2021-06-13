#include<stdio.h>

#define LEVELS 12
const static char CHAR_LEVELS[LEVELS] = {'.', ',', '-', '~', ':', ';', '=', '!', '*', '#', '$', '@'};


int getLevelFromChar(char myChar) {
    for (int l = 0; l < LEVELS; l++) {
        if (myChar == CHAR_LEVELS[l]) {
            return l;
        }
    }
    return -1;
}

struct Point {
    int x;
    int y;
    int z;
};

struct Point createPoint(const int x, const int y, const int z) {
    struct Point point;
    point.x = x;
    point.y = y;
    point.z = z;
    return point;
}

void
fillMatrixWithSameLevel(const int xmax, const int ymax, const int zmax, char matrix[][ymax][xmax], const int level) {
    if (level >= LEVELS) {
        printf("Error: %d is too high (bigger than %d)\n", level, LEVELS);
        return;
    }
    printf("Drawing points '%c' everywhere.\n", CHAR_LEVELS[level]);
    for (int z = 0; z < zmax; z++) {
        for (int y = 0; y < ymax; y++) {
            for (int x = 0; x < xmax; x++) {
                matrix[z][y][x] = CHAR_LEVELS[level];
            }
        }
    }
}

void fillMatrixWithModuloLevel(const int xmax, const int ymax, const int zmax, char matrix[][ymax][xmax]) {
    for (int z = 0; z < zmax; z++) {
        for (int y = 0; y < ymax; y++) {
            for (int x = 0; x < xmax; x++) {
                matrix[z][y][x] = CHAR_LEVELS[(x * y * (z+1)) % LEVELS];
            }
        }
    }
}

void
drawPoint(const int xmax, const int ymax, const int zmax, char matrix[][ymax][xmax], const struct Point point,
          const int level) {
//    printf("Drawing point '%c' here: (%d, %d)\n", CHAR_LEVELS[level], point.x, point.y);
    int currentLevel = getLevelFromChar(matrix[point.z][point.y][point.x]);
    int newLevel = currentLevel + level;
    if (newLevel >= LEVELS) {
        matrix[point.z][point.y][point.x] = CHAR_LEVELS[LEVELS-1];
    } else {
        matrix[point.z][point.y][point.x] = CHAR_LEVELS[newLevel];
    }
}

void
drawRectangle(const int xmax, const int ymax, const int zmax, char matrix[][ymax][xmax], const struct Point minPoint,
              const struct Point maxPoint, const int level) {
    printf("Drawing rectangle with '%c' with point: min=(%d, %d, %d), max=(%d, %d, %d)\n", CHAR_LEVELS[level],
           minPoint.x, minPoint.y, minPoint.z, maxPoint.x, maxPoint.y, maxPoint.z);

    for (int x = minPoint.x; x <= maxPoint.x; x++) {
        for (int y = minPoint.y; y <= maxPoint.y; y++) {
            for (int z = minPoint.z; z <= maxPoint.z; z++) {
                drawPoint(xmax, ymax, zmax, matrix, createPoint(x, y, z), level);
            }
        }
    }
}
//
//void drawCircle(const int xmax, const int ymax, char matrix[][xmax], const struct Point center,
//                const int radius, const int level) {
//    printf("Drawing circle with '%c' and radius %d centered here: (%d, %d)\n", CHAR_LEVELS[level], radius, center.x,
//           center.y);
//    drawPoint(xmax, ymax, matrix, center, level);
//}

void printMatrix(const int xmax, const int ymax, const int zmax, const char matrix[][ymax][xmax]) {
    printf("\n");
    for (int z = 0; z < zmax; z++) {
        printf("\n\nZ=%d\n", z);
        for (int y = ymax - 1; y >= 0; y--) {
            for (int x = 0; x < xmax; x++) {
                printf("%c\t", matrix[z][y][x]);
            }
            printf("\n");
        }
    }
}

void printMatrixIn2D(const int xmax, const int ymax, const int zmax, const char matrix[][ymax][xmax]) {
    const int newXmax = xmax+zmax;
    const int newYmax = ymax+zmax;
    const int newZmax = 1;
    char transformedMatrix[newZmax][newYmax][newXmax];
    fillMatrixWithSameLevel(newXmax, newYmax, newZmax, transformedMatrix, 0);
    for (int z = 0; z < zmax; z++) {
        for (int y = ymax - 1; y >= 0; y--) {
            for (int x = 0; x < xmax; x++) {
                int currentLevel = getLevelFromChar(matrix[z][y][x]);
                if (currentLevel > 0) {
                    drawPoint(xmax, ymax, 1, transformedMatrix, createPoint(x+zmax-z, y+zmax-z, 0), currentLevel);
                }
            }
        }
    }

    printMatrix(xmax, ymax, 1, transformedMatrix);
}


int main() {
    const struct Point limitPoint = createPoint(20, 15, 3);

    char matrix[limitPoint.z][limitPoint.y][limitPoint.x];

    fillMatrixWithSameLevel(limitPoint.x, limitPoint.y, limitPoint.z, matrix, 0);
//    fillMatrixWithModuloLevel(xmax, ymax, matrix);

//    drawCircle(xmax, ymax, matrix, (xmax / 2), (ymax / 2), 3, 5);
//    fillMatrixWithModuloLevel(limitPoint.x, limitPoint.y, limitPoint.z, matrix);

    drawRectangle(limitPoint.x, limitPoint.y, limitPoint.z, matrix, createPoint(2, 1, 0), createPoint(7, 5, 2), 5);


    printMatrix(limitPoint.x, limitPoint.y, limitPoint.z, matrix);

    printf("\nAnd now in 2D:\n");
    printMatrixIn2D(limitPoint.x, limitPoint.y, limitPoint.z, matrix);
    return 0;
}

