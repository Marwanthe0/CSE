#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

float boundaryColor[3] = {1.0f, 0.0f, 0.0f}; // Red
float fillColor[3] = {0.0f, 1.0f, 1.0f};     // Cyan

// Function to check if two RGB colors are equal within a small threshold
bool isSameColor(float c1[3], float c2[3]) {
    return (fabs(c1[0] - c2[0]) < 0.05f &&
            fabs(c1[1] - c2[1]) < 0.05f &&
            fabs(c1[2] - c2[2]) < 0.05f);
}

// 4-Connected Boundary-Fill Algorithm
void boundaryFill4(int x, int y, float fillCol[3], float boundCol[3]) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    // If current pixel is neither boundary color nor already filled
    if (!isSameColor(currentColor, boundCol) && !isSameColor(currentColor, fillCol)) {
        glColor3fv(fillCol);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        // Recursive calls for 4 neighboring pixels
        boundaryFill4(x + 1, y, fillCol, boundCol); // Right
        boundaryFill4(x - 1, y, fillCol, boundCol); // Left
        boundaryFill4(x, y + 1, fillCol, boundCol); // Top
        boundaryFill4(x, y - 1, fillCol, boundCol); // Bottom
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw boundary polygon (Square)
    glColor3fv(boundaryColor);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 150);
    glVertex2i(350, 150);
    glVertex2i(350, 350);
    glVertex2i(150, 350);
    glEnd();
    glFlush();

    // Automatically fill from seed point inside the boundary
    boundaryFill4(250, 250, fillColor, boundaryColor);
}

// Optional: Fill on mouse click inside any drawn boundary
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int x_gl = x;
        int y_gl = 500 - y; // Invert Y for OpenGL coordinate system
        boundaryFill4(x_gl, y_gl, fillColor, boundaryColor);
    }
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    printf("Boundary-Fill Algorithm:\n");
    printf("- Boundary Color: Red\n");
    printf("- Fill Color: Cyan\n");
    printf("- Seed point: (250, 250)\n");
    printf("You can also click anywhere inside the boundary to fill.\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Boundary-Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
