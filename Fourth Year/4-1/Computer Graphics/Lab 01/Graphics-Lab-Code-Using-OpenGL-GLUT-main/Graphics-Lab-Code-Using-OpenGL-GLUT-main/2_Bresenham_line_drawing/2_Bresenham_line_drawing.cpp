#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

// Endpoints of the line
int x1_val, y1_val, x2_val, y2_val;

/*
 * Bresenham's Line Drawing Algorithm (For slope |m| < 1, assuming dx > 0)
 * Follows the standard 6-step algorithm:
 * 1. Read endpoints (x1, y1) and (x2, y2).
 * 2. Calculate constants: dx, dy, 2*dy, and 2*dy - 2*dx.
 * 3. Calculate initial decision parameter: p0 = 2*dy - dx.
 * 4. Set starting point (xk, yk) = (x1, y1). Plot pixel.
 * 5. For each xk along the line, evaluate pk:
 *    - If pk < 0: Next point is (x_{k+1}, yk),       p_{k+1} = pk + 2*dy
 *    - If pk >= 0: Next point is (x_{k+1}, yk + 1),  p_{k+1} = pk + 2*dy - 2*dx
 * 6. Repeat step 5 until x reaches x2.
 */
void bresenhamLine(int x1, int y1, int x2, int y2)
{
    // Step 2: Calculate constants: dx, dy, 2*dy, and 2*dy - 2*dx
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int twoDy = 2 * dy;
    int twoDyMinusTwoDx = 2 * (dy - dx);

    // Step 3: Calculate initial decision parameter: p0 = 2*dy - dx
    int p = 2 * dy - dx;

    // Step 4: Set starting point (xk, yk) = (x1, y1) and plot pixel
    int x = x1;
    int y = y1;
    int y_step = (y2 >= y1) ? 1 : -1;

    glVertex2i(x, y);

    // Step 5 & Step 6: Repeat until x reaches x2
    while (x < x2)
    {
        x++;
        if (p < 0)
        {
            // Case 1: pk < 0 -> Next point is (x_{k+1}, y_k)
            p += twoDy;
        }
        else
        {
            // Case 2: pk >= 0 -> Next point is (x_{k+1}, y_k + 1)
            y += y_step;
            p += twoDyMinusTwoDx;
        }
        glVertex2i(x, y);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glPointSize(2.0f);
    glBegin(GL_POINTS);

    int x1 = x1_val;
    int y1 = y1_val;
    int x2 = x2_val;
    int y2 = y2_val;

    // Ensure x1 <= x2 so that dx > 0
    if (x1 > x2)
    {
        int tempX = x1; x1 = x2; x2 = tempX;
        int tempY = y1; y1 = y2; y2 = tempY;
    }

    // Call Bresenham's Line Algorithm
    bresenhamLine(x1, y1, x2, y2);

    glEnd();
    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
    // Step 1: Read endpoints (x1, y1) and (x2, y2)
    printf("Enter first point (x1 y1): ");
    scanf("%d %d", &x1_val, &y1_val);
    printf("Enter second point (x2 y2): ");
    scanf("%d %d", &x2_val, &y2_val);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
