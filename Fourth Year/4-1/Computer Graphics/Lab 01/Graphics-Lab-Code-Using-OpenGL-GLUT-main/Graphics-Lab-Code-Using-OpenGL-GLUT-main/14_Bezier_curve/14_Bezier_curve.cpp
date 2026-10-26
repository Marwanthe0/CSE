#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

struct Point {
    float x, y;
};

Point controlPoints[4];

Point computeBezierPoint(float u, Point p0, Point p1, Point p2, Point p3) {
    float u2 = u * u;
    float u3 = u2 * u;
    float oneMinusU = 1.0f - u;
    float oneMinusU2 = oneMinusU * oneMinusU;
    float oneMinusU3 = oneMinusU2 * oneMinusU;

    float b0 = oneMinusU3;
    float b1 = 3.0f * u * oneMinusU2;
    float b2 = 3.0f * u2 * oneMinusU;
    float b3 = u3;

    Point p;
    p.x = b0 * p0.x + b1 * p1.x + b2 * p2.x + b3 * p3.x;
    p.y = b0 * p0.y + b1 * p1.y + b2 * p2.y + b3 * p3.y;
    return p;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 4; i++) {
        glVertex2f(controlPoints[i].x, controlPoints[i].y);
    }
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 4; i++) {
        glVertex2f(controlPoints[i].x, controlPoints[i].y);
    }
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    for (float u = 0.0f; u <= 1.0f; u += 0.001f) {
        Point p = computeBezierPoint(u, controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3]);
        glVertex2f(p.x, p.y);
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
    printf("=== Bezier Curve Generation ===\n");
    printf("Enter 4 Control Points (or enter -1 to use default points):\n");
    printf("Enter P0 (x y): ");
    scanf("%f %f", &controlPoints[0].x, &controlPoints[0].y);
    printf("Enter P1 (x y): ");
    scanf("%f %f", &controlPoints[1].x, &controlPoints[1].y);
    printf("Enter P2 (x y): ");
    scanf("%f %f", &controlPoints[2].x, &controlPoints[2].y);
    printf("Enter P3 (x y): ");
    scanf("%f %f", &controlPoints[3].x, &controlPoints[3].y);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curve Generation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
