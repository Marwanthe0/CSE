#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

float xc, yc, rx, ry;

// Helper function to plot 4 symmetric points in all four quadrants
void drawEllipsePoints(float xc, float yc, float x, float y) {
    glVertex2i((int)round(xc + x), (int)round(yc + y));
    glVertex2i((int)round(xc - x), (int)round(yc + y));
    glVertex2i((int)round(xc + x), (int)round(yc - y));
    glVertex2i((int)round(xc - x), (int)round(yc - y));
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);

    float x = 0;
    float y = ry;

    // Region 1
    // Initial decision parameter of region 1
    float p1 = (ry * ry) - (rx * rx * ry) + (0.25f * rx * rx);
    float dx = 2.0f * ry * ry * x;
    float dy = 2.0f * rx * rx * y;

    // Plot initial point in all 4 quadrants
    drawEllipsePoints(xc, yc, x, y);

    while (dx < dy) {
        x++;
        dx += 2.0f * ry * ry;
        if (p1 < 0) {
            p1 += dx + (ry * ry);
        } else {
            y--;
            dy -= 2.0f * rx * rx;
            p1 += dx - dy + (ry * ry);
        }
        drawEllipsePoints(xc, yc, x, y);
    }

    // Region 2
    // Initial decision parameter of region 2
    float p2 = (ry * ry) * ((x + 0.5f) * (x + 0.5f)) +
               (rx * rx) * ((y - 1.0f) * (y - 1.0f)) -
               (rx * rx * ry * ry);

    while (y > 0) {
        y--;
        dy -= 2.0f * rx * rx;
        if (p2 > 0) {
            p2 += (rx * rx) - dy;
        } else {
            x++;
            dx += 2.0f * ry * ry;
            p2 += dx - dy + (rx * rx);
        }
        drawEllipsePoints(xc, yc, x, y);
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
    printf("Enter semi-major and semi-minor radii (rx ry): ");
    scanf("%f %f", &rx, &ry);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mid-Point Ellipse Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
