#include <stdio.h>
#include <stdlib.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

float x1, y1, x2, y2, m, i, j, p;
int dx = 0, dy = 0;
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    if (steps == 0) {
        steps = 1;
    }
    float currentX = x1;
    float currentY = y1;
    float xStep = (float)dx / steps;
    float yStep = (float)dy / steps;
    for (int k = 0; k <= steps; ++k) {
        glVertex3i(currentX, currentY, 0.0f);
        currentX += xStep;
        currentY += yStep;
    }
    glEnd();
    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    printf("Enter first point: ");
    scanf("%f %f", &x1, &y1);
    printf("Enter second point: ");
    scanf("%f %f", &x2, &y2);
    dx = x2 - x1;
    dy = y2 - y1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("hello");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
