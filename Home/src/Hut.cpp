#include <graphics.h>
#include <conio.h>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <windows.h> // For Sleep function
#include <iostream>  // For console output

using namespace std;

// Function to draw an upright triangle at a specific grid cell
void drawTriangle(int row, int col, int size, int color, int xOffset = 0, int yOffset = 0) {
    int left = 50, top = 50; // Top-left corner of the grid
    int colWidth = 60; // Width of each column
    int rowHeight = 60; // Height of each row

    int x = left + (col - 1) * colWidth + xOffset;
    int y = top + (row - 1) * rowHeight + yOffset;

    setcolor(color);
    int poly[8];  // Array to hold the points for the polygon

    // Define the three vertices of the triangle
    poly[0] = x + colWidth / 2;            // Top vertex (centered horizontally)
    poly[1] = y + rowHeight / 4;           // Top vertex
    poly[2] = x + colWidth / 4;            // Bottom left vertex
    poly[3] = y + 3 * rowHeight / 4;       // Bottom left vertex
    poly[4] = x + 3 * colWidth / 4;        // Bottom right vertex
    poly[5] = y + 3 * rowHeight / 4;       // Bottom right vertex
    poly[6] = poly[0];                     // Back to the top vertex to close the triangle
    poly[7] = poly[1];                     // Close the triangle

    // Draw the triangle
    drawpoly(4, poly);
}

// Function to draw a circle at a specific grid cell
void drawCircle(int row, int col, int size, int color, int xOffset = 0, int yOffset = 0) {
    int left = 50, top = 50; // Top-left corner of the grid
    int colWidth = 60; // Width of each column
    int rowHeight = 60; // Height of each row

    int x = left + (col - 1) * colWidth + colWidth / 2 + xOffset;  // Center of the circle in the cell
    int y = top + (row - 1) * rowHeight + rowHeight / 2 + yOffset;

    setcolor(color);
    circle(x, y, size);  // Draw the circle
}

// Function to draw diagonal lines in the safe grid cells
void drawDiagonalInGrid(int row, int col) {
    int left = 50, top = 50; // Top-left corner of the grid
    int colWidth = 60; // Width of each column
    int rowHeight = 60; // Height of each row

    int x1 = left + (col - 1) * colWidth;  // Top left corner of the grid cell
    int y1 = top + (row - 1) * rowHeight;  // Top left corner of the grid cell
    int x2 = x1 + colWidth;  // Bottom right corner of the grid cell
    int y2 = y1 + rowHeight;

    setcolor(BLACK);
    
    // Draw diagonals
    line(x1, y1, x2, y2);  // Diagonal from top-left to bottom-right
    line(x2, y1, x1, y2);  // Diagonal from top-right to bottom-left
}

// Function to draw the grid
void drawGrid() {
    int rows = 5, cols = 5;
    int left = 50, top = 50, right = 350, bottom = 350;
    int rowHeight = (bottom - top) / rows;
    int colWidth = (right - left) / cols;

    setcolor(BLACK);
    for (int i = 0; i <= rows; i++) {
        line(left, top + i * rowHeight, right, top + i * rowHeight);
    }

    for (int i = 0; i <= cols; i++) {
        line(left + i * colWidth, top, left + i * colWidth, bottom);
    }
}

// Function to select a random value from [1, 2, 3, 4, 8]
int getRandomMove(int &randCount) {
    int values[] = {1, 2, 3, 4, 8};
    int index = rand() % 5; // Select a random index from 0 to 4
    randCount++;  // Increment the random function usage count
    return values[index];
}

// Function to allow shape selection and movement
void moveShape(int &row, int &col, int path[][2], int &pathIndex, int pathLength, int move) {
    for (int i = 0; i < move; i++) {
        if (pathIndex < pathLength) {
            row = path[pathIndex][0];
            col = path[pathIndex][1];
            pathIndex++;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    char data[] = "C:\\MinGW\\lib\\libbgi.a"; // Static file for BGI

    initgraph(&gd, &gm, data);

    // Seed the random number generator
    srand(time(0));

    // Set the background color to white
    setbkcolor(WHITE);
    cleardevice();

    // Initial positions for shapes
    int circle1Row = 1, circle1Col = 3;
    int circle2Row = 1, circle2Col = 3;
    int triangle1Row = 5, triangle1Col = 3;
    int triangle2Row = 5, triangle2Col = 3;
    int shapeSize = 20;  // Size of the triangles and circles
    int triangleColor = RED; // Color of the triangles
    int circleColor = BLUE;  // Color of the circles

    // Define the path for the first triangle (starting at 5,3)
    int triangle1Path[][2] = {
        {5, 4}, {5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5},
        {1, 4}, {1, 3}, {1, 2}, {1, 1}, {2, 1}, {3, 1},
        {4, 1}, {5, 1}, {5, 2}, {4, 2}, {3, 2}, {2, 2},
        {2, 3}, {2, 4}, {3, 4}, {4, 4}, {4, 3}, {3, 3}
    };

    // Define the path for the second triangle (starting at 5,3)
    int triangle2Path[][2] = {
        {5, 4}, {5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5},
        {1, 4}, {1, 3}, {1, 2}, {1, 1}, {2, 1}, {3, 1},
        {4, 1}, {5, 1}, {5, 2}, {4, 2}, {3, 2}, {2, 2},
        {2, 3}, {2, 4}, {3, 4}, {4, 4}, {4, 3}, {3, 3}
    };

    // Define the path for the first circle (starting at 1,3)
    int circle1Path[][2] = {
        {1, 2}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1},
        {5, 2}, {5, 3}, {5, 4}, {5, 5}, {4, 5}, {3, 5},
        {2, 5}, {1, 5}, {1, 4}, {2, 4}, {3, 4}, {4, 4},
        {4, 3}, {4, 2}, {3, 2}, {2, 2}, {2, 3}, {3, 3}
    };

    // Define the path for the second circle (starting at 1,3)
    int circle2Path[][2] = {
        {1, 2}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1},
        {5, 2}, {5, 3}, {5, 4}, {5, 5}, {4, 5}, {3, 5},
        {2, 5}, {1, 5}, {1, 4}, {2, 4}, {3, 4}, {4, 4},
        {4, 3}, {4, 2}, {3, 2}, {2, 2}, {2, 3}, {3, 3}
    };

    // Calculate path lengths
    int triangle1PathLength = sizeof(triangle1Path) / sizeof(triangle1Path[0]);
    int triangle2PathLength = sizeof(triangle2Path) / sizeof(triangle2Path[0]);
    int circle1PathLength = sizeof(circle1Path) / sizeof(circle1Path[0]);
    int circle2PathLength = sizeof(circle2Path) / sizeof(circle2Path[0]);

    // Draw the initial grid, triangles, and circles in the designated cells
    drawGrid();

    // Define the "safe grids" (diagonal cells)
    int safeGrids[][2] = {
        {1, 3}, {2, 2}, {2, 4}, {3, 1}, {3, 3}, {3, 5},
        {4, 2}, {4, 4}, {5, 3}
    };

    // Draw diagonals in each of the safe grid cells
    for (int i = 0; i < 9; i++) {
        drawDiagonalInGrid(safeGrids[i][0], safeGrids[i][1]);
    }

    drawTriangle(triangle1Row, triangle1Col, shapeSize, triangleColor, -10, -10); // Triangle 1 with slight offset in (5,3)
    drawTriangle(triangle2Row, triangle2Col, shapeSize, triangleColor, 10, 10);   // Triangle 2 with slight offset in (5,3)
    drawCircle(circle1Row, circle1Col, shapeSize / 2, circleColor, -10, -10);     // Circle 1 with slight offset in (1,3)
    drawCircle(circle2Row, circle2Col, shapeSize / 2, circleColor, 10, 10);       // Circle 2 with slight offset in (1,3)
    Sleep(1000);

    // Initialize the starting index for the paths
    int triangle1PathIndex = 0;
    int triangle2PathIndex = 0;
    int circle1PathIndex = 0;
    int circle2PathIndex = 0;
    int totalMoves = 0; // To keep track of the total number of moves
    int randCount = 0;  // To keep track of how many times the random function is used

    // Track the number of steps taken by each shape to reach (3, 3)
    int triangle1Steps = 0;
    int triangle2Steps = 0;
    int circle1Steps = 0;
    int circle2Steps = 0;

    // Variable to alternate turns between triangles and circles
    int currentShapeType = 1; // 1 for triangles, 2 for circles

    // Simulate movements based on random steps
    while (triangle1PathIndex < triangle1PathLength || triangle2PathIndex < triangle2PathLength ||
           circle1PathIndex < circle1PathLength || circle2PathIndex < circle2PathLength) {
        cleardevice();  // Clear the screen
        drawGrid();     // Redraw the grid

        // Redraw the diagonal safe grids after clearing the screen
        for (int i = 0; i < 9; i++) {
            drawDiagonalInGrid(safeGrids[i][0], safeGrids[i][1]);
        }

        // Redraw all shapes before updating positions
        drawTriangle(triangle1Row, triangle1Col, shapeSize, triangleColor, -10, -10); // Redraw Triangle 1
        drawTriangle(triangle2Row, triangle2Col, shapeSize, triangleColor, 10, 10);   // Redraw Triangle 2
        drawCircle(circle1Row, circle1Col, shapeSize / 2, circleColor, -10, -10);     // Redraw Circle 1
        drawCircle(circle2Row, circle2Col, shapeSize / 2, circleColor, 10, 10);       // Redraw Circle 2

        // Get a random move value
        int move = getRandomMove(randCount);

        // Update the total number of moves
        totalMoves += move;

        // Show the selected random value and total moves on the screen
        char msg[50];
        sprintf(msg, "Selected Move: %d, Total Moves: %d", move, totalMoves);
        setcolor(BLUE);
        outtextxy(100, 400, msg); // Display the message at the bottom of the screen

        int choice;
        if (currentShapeType == 1) {  // Triangles' turn
            cout << "Move " << move << " steps." << endl;
            cout << "Select the triangle to move:" << endl;
            cout << "1. Triangle 1" << endl;
            cout << "2. Triangle 2" << endl;
            cin >> choice;

            if (choice == 1) {
                moveShape(triangle1Row, triangle1Col, triangle1Path, triangle1PathIndex, triangle1PathLength, move);
                triangle1Steps += move;
            } else if (choice == 2) {
                moveShape(triangle2Row, triangle2Col, triangle2Path, triangle2PathIndex, triangle2PathLength, move);
                triangle2Steps += move;
            }
        } else {  // Circles' turn
            cout << "Move " << move << " steps." << endl;
            cout << "Select the circle to move:" << endl;
            cout << "1. Circle 1" << endl;
            cout << "2. Circle 2" << endl;
            cin >> choice;

            if (choice == 1) {
                moveShape(circle1Row, circle1Col, circle1Path, circle1PathIndex, circle1PathLength, move);
                circle1Steps += move;
            } else if (choice == 2) {
                moveShape(circle2Row, circle2Col, circle2Path, circle2PathIndex, circle2PathLength, move);
                circle2Steps += move;
            }
        }

        // Check if any shape has reached position (3, 3)
        if (triangle1Row == 3 && triangle1Col == 3) {
            setcolor(GREEN);
            char winMessage[] = "Hurry! Triangle 1 won the match";
            outtextxy(100, 50, winMessage); // Display win message
            cout << "The Triangle 1 won in " << triangle1Steps << " steps." << endl;
            Sleep(3000); // Pause to allow the user to see the message
            closegraph();
            return 0; // Exit after showing the win message
        } else if (triangle2Row == 3 && triangle2Col == 3) {
            setcolor(GREEN);
            char winMessage[] = "Hurry! Triangle 2 won the match";
            outtextxy(100, 50, winMessage); // Display win message
            cout << "The Triangle 2 won in " << triangle2Steps << " steps." << endl;
            Sleep(3000); // Pause to allow the user to see the message
            closegraph();
            return 0; // Exit after showing the win message
        } else if (circle1Row == 3 && circle1Col == 3) {
            setcolor(GREEN);
            char winMessage[] = "Hurry! Circle 1 won the match";
            outtextxy(100, 50, winMessage); // Display win message
            cout << "The Circle 1 won in " << circle1Steps << " steps." << endl;
            Sleep(3000); // Pause to allow the user to see the message
            closegraph();
            return 0; // Exit after showing the win message
        } else if (circle2Row == 3 && circle2Col == 3) {
            setcolor(GREEN);
            char winMessage[] = "Hurry! Circle 2 won the match";
            outtextxy(100, 50, winMessage); // Display win message
            cout << "The Circle 2 won in " << circle2Steps << " steps." << endl;
            Sleep(3000); // Pause to allow the user to see the message
            closegraph();
            return 0; // Exit after showing the win message
        }

        // Alternate the turn between triangles and circles
        currentShapeType = (currentShapeType == 1) ? 2 : 1;

        Sleep(1000); // Pause after completing the selected number of steps
    }

    // Output the number of times the random function was used to the console
    cout << "Random function was used " << randCount << " times." << endl;

    getch(); // Wait for the user to press a key
    closegraph();

    return 0;
}