#include <stdio.h>
#include <stdlib.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

// Region Codes (Outcodes: TBRL)
const int INSIDE = 0; // 0000
const int LEFT   = 1; // 0001
const int RIGHT  = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP    = 8; // 1000

// Rectangular window boundaries
float xmin = 150.0f, ymin = 150.0f, xmax = 350.0f, ymax = 350.0f;

// Original line endpoints
float origX1, origY1, origX2, origY2;
// Clipped line endpoints inside the rectangle
float clipX1, clipY1, clipX2, clipY2;
bool isLineAccepted = false;

// Compute 4-bit region code for a point (x, y)
int computeCode(float x, float y) {
    int code = INSIDE;
    if (x < xmin)      code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin)      code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    return code;
}

// Cohen-Sutherland Line Clipping Algorithm
void cohenSutherlandClip(float x1, float y1, float x2, float y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Trivial Accept: Both endpoints are inside the rectangle
            accept = true;
            break;
        } else if (code1 & code2) {
            // Trivial Reject: Both endpoints share an outside zone
            break;
        } else {
            // Some segment lies within the rectangle; calculate intersection
            int codeOut = (code1 != 0) ? code1 : code2;
            float x, y;

            if (codeOut & TOP) {
                // Point is above clipping window
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                // Point is below clipping window
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) {
                // Point is to the right of clipping window
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (codeOut & LEFT) {
                // Point is to the left of clipping window
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            // Replace outside point with intersection point
            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        clipX1 = x1; clipY1 = y1;
        clipX2 = x2; clipY2 = y2;
        isLineAccepted = true;
    } else {
        isLineAccepted = false;
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Draw Rectangular Clipping Window in Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // 2. Draw Original Line in Gray (Faint)
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(origX1, origY1);
    glVertex2f(origX2, origY2);
    glEnd();

    // 3. Draw Clipped Line Portion within Rectangle in Bright Green
    if (isLineAccepted) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(clipX1, clipY1);
        glVertex2f(clipX2, clipY2);
        glEnd();
    }

    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    printf("=== Draw Line within Rectangle (Cohen-Sutherland Line Clipping) ===\n");
    printf("Enter rectangle window (xmin ymin xmax ymax): ");
    scanf("%f %f %f %f", &xmin, &ymin, &xmax, &ymax);

    printf("Enter line endpoints (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &origX1, &origY1, &origX2, &origY2);

    cohenSutherlandClip(origX1, origY1, origX2, origY2);

    if (isLineAccepted) {
        printf("Line segment accepted inside rectangle:\n");
        printf("  P1: (%.2f, %.2f)\n", clipX1, clipY1);
        printf("  P2: (%.2f, %.2f)\n", clipX2, clipY2);
    } else {
        printf("The line is completely outside the rectangle.\n");
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line within Rectangle - Cohen-Sutherland Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
