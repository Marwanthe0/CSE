#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#define PI 3.14159265358979323846

float xc, yc, r;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);

    // Drawing circle by calculating and plotting each single point individually
    // using polar coordinates: x = xc + r*cos(theta), y = yc + r*sin(theta)
    for (float theta = 0.0f; theta < 2.0f * PI; theta += 0.001f) {
        float x = xc + r * cos(theta);
        float y = yc + r * sin(theta);
        glVertex2i((int)round(x), (int)round(y));
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
    printf("Enter center point (xc yc): ");
    scanf("%f %f", &xc, &yc);
    printf("Enter radius (r): ");
    scanf("%f", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Draw Circle Using Single Point Method");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
