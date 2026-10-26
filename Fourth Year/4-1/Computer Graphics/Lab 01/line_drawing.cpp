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

struct Point { int x, y; };

vector<Point> ddaPoints, bresPoints;
int sx, sy, ex, ey;
int mode = 3;
int gMin, gMax;

void computeDDA() {
    ddaPoints.clear();
    int dx = ex - sx;
    int dy = ey - sy;
    int steps = max(abs(dx), abs(dy));
    if (steps == 0) { ddaPoints.push_back({sx, sy}); return; }
    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;
    float x = (float)sx, y = (float)sy;
    for (int i = 0; i <= steps; i++) {
        ddaPoints.push_back({(int)round(x), (int)round(y)});
        x += xInc;
        y += yInc;
    }
}

void computeBresenham() {
    bresPoints.clear();
    int x = sx, y = sy;
    int dx = abs(ex - sx);
    int dy = abs(ey - sy);
    int stepX = (sx < ex) ? 1 : -1;
    int stepY = (sy < ey) ? 1 : -1;
    bool swapped = false;
    if (dy > dx) { swap(dx, dy); swapped = true; }
    int p = 2 * dy - dx;
    for (int i = 0; i <= dx; i++) {
        bresPoints.push_back({x, y});
        if (p < 0) {
            if (swapped) y += stepY; else x += stepX;
            p += 2 * dy;
        } else {
            x += stepX;
            y += stepY;
            p += 2 * dy - 2 * dx;
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

void drawPixelOutline(int x, int y) {
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - 0.45f, y - 0.45f);
    glVertex2f(x + 0.45f, y - 0.45f);
    glVertex2f(x + 0.45f, y + 0.45f);
    glVertex2f(x - 0.45f, y + 0.45f);
    glEnd();
    glLineWidth(1.0f);
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

    glColor3f(0.25f, 0.25f, 0.35f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f((float)sx, (float)sy);
    glVertex2f((float)ex, (float)ey);
    glEnd();

    if (mode == 1 || mode == 3) {
        glColor3f(0.2f, 0.9f, 0.4f);
        for (size_t i = 0; i < ddaPoints.size(); i++)
            drawPixel(ddaPoints[i].x, ddaPoints[i].y);
    }

    if (mode == 2 || mode == 3) {
        if (mode == 3) {
            glColor3f(1.0f, 0.4f, 0.4f);
            for (size_t i = 0; i < bresPoints.size(); i++)
                drawPixelOutline(bresPoints[i].x, bresPoints[i].y);
        } else {
            glColor3f(0.3f, 0.6f, 1.0f);
            for (size_t i = 0; i < bresPoints.size(); i++)
                drawPixel(bresPoints[i].x, bresPoints[i].y);
        }
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glVertex2f((float)sx, (float)sy);
    glVertex2f((float)ex, (float)ey);
    glEnd();
    glPointSize(1.0f);

    float lx = (float)gMin + 0.5f;
    if (mode == 1) {
        glColor3f(0.2f, 0.9f, 0.4f);
        drawText(lx, (float)gMax - 1.2f, "DDA Algorithm");
    } else if (mode == 2) {
        glColor3f(0.3f, 0.6f, 1.0f);
        drawText(lx, (float)gMax - 1.2f, "Bresenham's Algorithm");
    } else {
        glColor3f(0.2f, 0.9f, 0.4f);
        drawText(lx, (float)gMax - 1.2f, "[Filled] DDA");
        glColor3f(1.0f, 0.4f, 0.4f);
        drawText(lx, (float)gMax - 2.8f, "[Outline] Bresenham");
    }

    glColor3f(0.5f, 0.5f, 0.6f);
    drawText((float)gMin + 0.5f, (float)gMin + 0.5f,
             "1=DDA  2=Bresenham  3=Both  ESC=Exit", GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
    if (key == '1') mode = 1;
    else if (key == '2') mode = 2;
    else if (key == '3') mode = 3;
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
    cout << " Line Drawing Algorithms Visualization" << endl;
    cout << "========================================" << endl;
    cout << "\nEnter starting point (x1 y1): ";
    cin >> sx >> sy;
    cout << "Enter ending point   (x2 y2): ";
    cin >> ex >> ey;

    computeDDA();
    computeBresenham();

    int mnX = min(sx, ex) - 2;
    int mxX = max(sx, ex) + 2;
    int mnY = min(sy, ey) - 2;
    int mxY = max(sy, ey) + 2;
    gMin = min(mnX, mnY);
    gMax = max(mxX, mxY);
    if (gMin > -2) gMin = -2;
    if (gMax < 2) gMax = 2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Line Drawing - DDA & Bresenham");

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
