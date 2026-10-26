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

struct ColorPoint { int x, y, octant; };

vector<ColorPoint> circlePoints;
int centerX, centerY, radius;
int gMin, gMax;
bool colorOctants = true;

void computeCircle() {
    circlePoints.clear();
    int x = 0, y = radius;
    int p = 1 - radius;

    auto addPts = [&](int px, int py) {
        circlePoints.push_back({centerX + px, centerY + py, 0});
        circlePoints.push_back({centerX - px, centerY + py, 1});
        circlePoints.push_back({centerX + px, centerY - py, 2});
        circlePoints.push_back({centerX - px, centerY - py, 3});
        circlePoints.push_back({centerX + py, centerY + px, 4});
        circlePoints.push_back({centerX - py, centerY + px, 5});
        circlePoints.push_back({centerX + py, centerY - px, 6});
        circlePoints.push_back({centerX - py, centerY - px, 7});
    };

    while (x <= y) {
        addPts(x, y);
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void setOctantColor(int oct) {
    float colors[][3] = {
        {0.2f, 0.9f, 0.4f},
        {0.3f, 0.6f, 1.0f},
        {1.0f, 0.8f, 0.2f},
        {1.0f, 0.4f, 0.4f},
        {0.9f, 0.4f, 0.9f},
        {0.4f, 0.9f, 0.9f},
        {1.0f, 0.6f, 0.2f},
        {0.6f, 0.9f, 0.6f}
    };
    glColor3fv(colors[oct]);
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
        glVertex2f(centerX + radius * cos(angle), centerY + radius * sin(angle));
    }
    glEnd();

    for (size_t i = 0; i < circlePoints.size(); i++) {
        if (colorOctants)
            setOctantColor(circlePoints[i].octant);
        else
            glColor3f(0.2f, 0.9f, 0.4f);
        drawPixel(circlePoints[i].x, circlePoints[i].y);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glVertex2f((float)centerX, (float)centerY);
    glEnd();
    glPointSize(1.0f);

    glColor3f(0.9f, 0.9f, 1.0f);
    drawText((float)gMin + 0.5f, (float)gMax - 1.2f, "Midpoint Circle Algorithm");

    if (colorOctants) {
        glColor3f(0.6f, 0.6f, 0.7f);
        drawText((float)gMin + 0.5f, (float)gMax - 2.8f,
                 "8-way symmetry coloring", GLUT_BITMAP_HELVETICA_12);
    }

    glColor3f(0.5f, 0.5f, 0.6f);
    drawText((float)gMin + 0.5f, (float)gMin + 0.5f,
             "C=Toggle Colors  ESC=Exit", GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    if (key == 'c' || key == 'C') colorOctants = !colorOctants;
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
    cout << " Midpoint Circle Drawing Visualization" << endl;
    cout << "========================================" << endl;
    cout << "\nEnter center of circle (xc yc): ";
    cin >> centerX >> centerY;
    cout << "Enter radius (r): ";
    cin >> radius;

    computeCircle();

    int lo = min(centerX - radius, centerY - radius) - 3;
    int hi = max(centerX + radius, centerY + radius) + 3;
    gMin = min(lo, -2);
    gMax = max(hi, 2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Midpoint Circle Drawing Algorithm");

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
