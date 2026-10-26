#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct RegionPoint { int x, y, region; };

vector<RegionPoint> ellipsePoints;
int centerX, centerY, rx, ry;
int gMin, gMax;
bool colorRegions = true;

void computeEllipse() {
    ellipsePoints.clear();
    int x = 0, y = ry;

    long long rx2 = (long long)rx * rx;
    long long ry2 = (long long)ry * ry;

    double p1 = ry2 - (rx2 * ry) + (0.25 * rx2);

    long long dx = 2 * ry2 * x;
    long long dy = 2 * rx2 * y;

    while (dx < dy) {
        ellipsePoints.push_back({centerX + x, centerY + y, 1});
        ellipsePoints.push_back({centerX - x, centerY + y, 1});
        ellipsePoints.push_back({centerX + x, centerY - y, 1});
        ellipsePoints.push_back({centerX - x, centerY - y, 1});

        x++;
        dx += 2 * ry2;

        if (p1 < 0) {
            p1 += dx + ry2;
        } else {
            y--;
            dy -= 2 * rx2;
            p1 += dx - dy + ry2;
        }
    }

    double p2 = ry2 * (x + 0.5) * (x + 0.5)
              + rx2 * (double)(y - 1) * (y - 1)
              - (double)rx2 * ry2;

    while (y >= 0) {
        ellipsePoints.push_back({centerX + x, centerY + y, 2});
        ellipsePoints.push_back({centerX - x, centerY + y, 2});
        ellipsePoints.push_back({centerX + x, centerY - y, 2});
        ellipsePoints.push_back({centerX - x, centerY - y, 2});

        y--;
        dy -= 2 * rx2;

        if (p2 > 0) {
            p2 += rx2 - dy;
        } else {
            x++;
            dx += 2 * ry2;
            p2 += dx - dy + rx2;
        }
    }
}

void drawText(float x, float y, const string& text, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (size_t i = 0; i < text.size(); i++)
        glutBitmapCharacter(font, text[i]);
}

void drawPixel(int x, int y) {
    glBegin(GL_QUADS);
    glVertex2f(x - 0.4f, y - 0.4f);
    glVertex2f(x + 0.4f, y - 0.4f);
    glVertex2f(x + 0.4f, y + 0.4f);
    glVertex2f(x - 0.4f, y + 0.4f);
    glEnd();
}

void drawGrid() {
    int range = gMax - gMin;
    int labelStep = 1;
    if (range > 40) labelStep = 5;
    else if (range > 20) labelStep = 2;

    glColor3f(0.12f, 0.12f, 0.18f);
    glBegin(GL_LINES);
    for (int i = gMin; i <= gMax; i++) {
        glVertex2f((float)i, (float)gMin);
        glVertex2f((float)i, (float)gMax);
        glVertex2f((float)gMin, (float)i);
        glVertex2f((float)gMax, (float)i);
    }
    glEnd();

    glColor3f(0.35f, 0.35f, 0.45f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f((float)gMin, 0.0f);
    glVertex2f((float)gMax, 0.0f);
    glVertex2f(0.0f, (float)gMin);
    glVertex2f(0.0f, (float)gMax);
    glEnd();
    glLineWidth(1.0f);

    glColor3f(0.35f, 0.35f, 0.45f);
    for (int i = gMin; i <= gMax; i++) {
        if (i != 0 && i % labelStep == 0) {
            drawText((float)i - 0.2f, (float)gMin - 1.2f, to_string(i), GLUT_BITMAP_HELVETICA_10);
            drawText((float)gMin - 2.0f, (float)i - 0.15f, to_string(i), GLUT_BITMAP_HELVETICA_10);
        }
    }
}

void display() {
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrid();

    glColor3f(0.2f, 0.2f, 0.3f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = (float)(i * M_PI / 180.0);
        glVertex2f(centerX + rx * cos(angle), centerY + ry * sin(angle));
    }
    glEnd();

    for (size_t i = 0; i < ellipsePoints.size(); i++) {
        if (colorRegions) {
            if (ellipsePoints[i].region == 1)
                glColor3f(0.2f, 0.9f, 0.4f);
            else
                glColor3f(0.3f, 0.7f, 1.0f);
        } else {
            glColor3f(0.2f, 0.9f, 0.4f);
        }
        drawPixel(ellipsePoints[i].x, ellipsePoints[i].y);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glVertex2f((float)centerX, (float)centerY);
    glEnd();
    glPointSize(1.0f);

    glColor3f(0.9f, 0.9f, 1.0f);
    drawText((float)gMin + 0.5f, (float)gMax - 1.2f, "Midpoint Ellipse Algorithm");

    if (colorRegions) {
        glColor3f(0.2f, 0.9f, 0.4f);
        drawText((float)gMin + 0.5f, (float)gMax - 2.8f,
                 "Region 1 (slope < 1)", GLUT_BITMAP_HELVETICA_12);
        glColor3f(0.3f, 0.7f, 1.0f);
        drawText((float)gMin + 0.5f, (float)gMax - 4.0f,
                 "Region 2 (slope >= 1)", GLUT_BITMAP_HELVETICA_12);
    }

    glColor3f(0.5f, 0.5f, 0.6f);
    drawText((float)gMin + 0.5f, (float)gMin + 0.5f,
             "R=Toggle Regions  ESC=Exit", GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    if (key == 'r' || key == 'R') colorRegions = !colorRegions;
    else if (key == 27) exit(0);
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(gMin - 3.0, gMax + 3.0, gMin - 3.0, gMax + 3.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    cout << "========================================" << endl;
    cout << " Midpoint Ellipse Drawing Visualization" << endl;
    cout << "========================================" << endl;
    cout << "\nEnter center of ellipse (xc yc): ";
    cin >> centerX >> centerY;
    cout << "Enter semi-major axis (rx): ";
    cin >> rx;
    cout << "Enter semi-minor axis (ry): ";
    cin >> ry;

    computeEllipse();

    int maxR = max(rx, ry);
    int lo = min(centerX - maxR, centerY - maxR) - 3;
    int hi = max(centerX + maxR, centerY + maxR) + 3;
    gMin = min(lo, -2);
    gMax = max(hi, 2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Midpoint Ellipse Drawing Algorithm");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(gMin - 3.0, gMax + 3.0, gMin - 3.0, gMax + 3.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
