#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

float oldColor[3] = {0.0f, 0.0f, 0.0f};  // Target/interior color to replace (Black)
float fillColor[3] = {1.0f, 1.0f, 0.0f}; // New fill color (Yellow)
float boundaryColor[3] = {1.0f, 1.0f, 1.0f}; // White boundary

// Function to check if two RGB colors are approximately equal
bool isSameColor(float c1[3], float c2[3]) {
    return (fabs(c1[0] - c2[0]) < 0.05f &&
            fabs(c1[1] - c2[1]) < 0.05f &&
            fabs(c1[2] - c2[2]) < 0.05f);
}

// 4-Connected Flood-Fill Algorithm
void floodFill4(int x, int y, float fillCol[3], float oldCol[3]) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    // If current pixel matches the old target color, replace with new fill color
    if (isSameColor(currentColor, oldCol)) {
        glColor3fv(fillCol);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        // Recursive calls for 4 neighboring pixels
        floodFill4(x + 1, y, fillCol, oldCol); // Right
        floodFill4(x - 1, y, fillCol, oldCol); // Left
        floodFill4(x, y + 1, fillCol, oldCol); // Top
        floodFill4(x, y - 1, fillCol, oldCol); // Bottom
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw boundary polygon (Polygon with white outline and black interior)
    glColor3fv(boundaryColor);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 150);
    glVertex2i(350, 150);
    glVertex2i(350, 350);
    glVertex2i(150, 350);
    glEnd();
    glFlush();

    // Automatically trigger flood fill from seed point inside the shape
    floodFill4(250, 250, fillColor, oldColor);
}

// Optional: Trigger flood fill at clicked pixel position
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int x_gl = x;
        int y_gl = 500 - y; // Invert Y for OpenGL coordinate system
        
        float clickedColor[3];
        glReadPixels(x_gl, y_gl, 1, 1, GL_RGB, GL_FLOAT, clickedColor);
        
        // Only flood-fill if clicked color is different from fill color
        if (!isSameColor(clickedColor, fillColor)) {
            floodFill4(x_gl, y_gl, fillColor, clickedColor);
        }
    }
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    printf("Flood-Fill Algorithm:\n");
    printf("- Old/Target Color: Black\n");
    printf("- New Fill Color: Yellow\n");
    printf("- Seed point: (250, 250)\n");
    printf("You can also click anywhere inside the region to flood fill.\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flood-Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
