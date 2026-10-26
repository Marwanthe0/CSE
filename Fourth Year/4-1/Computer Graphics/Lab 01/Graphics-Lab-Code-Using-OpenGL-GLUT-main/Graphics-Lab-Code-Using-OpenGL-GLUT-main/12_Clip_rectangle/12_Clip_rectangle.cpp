#include <stdio.h>
#include <stdlib.h>
#include <vector>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

struct Point {
    float x, y;
};

// Clipping window boundaries
float xmin = 150.0f, ymin = 150.0f, xmax = 350.0f, ymax = 350.0f;

// Original subject rectangle vertices
std::vector<Point> originalRect;
// Clipped polygon vertices
std::vector<Point> clippedRect;

// Sutherland-Hodgman Polygon Clipping functions:
std::vector<Point> clipLeft(const std::vector<Point>& poly, float xmin) {
    std::vector<Point> out;
    int n = poly.size();
    if (n == 0) return out;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];
        bool in1 = (p1.x >= xmin);
        bool in2 = (p2.x >= xmin);
        if (in1 && in2) {
            out.push_back(p2);
        } else if (in1 && !in2) { // In to Out
            float y = p1.y + (xmin - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            out.push_back({xmin, y});
        } else if (!in1 && in2) { // Out to In
            float y = p1.y + (xmin - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            out.push_back({xmin, y});
            out.push_back(p2);
        }
    }
    return out;
}

std::vector<Point> clipRight(const std::vector<Point>& poly, float xmax) {
    std::vector<Point> out;
    int n = poly.size();
    if (n == 0) return out;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];
        bool in1 = (p1.x <= xmax);
        bool in2 = (p2.x <= xmax);
        if (in1 && in2) {
            out.push_back(p2);
        } else if (in1 && !in2) { // In to Out
            float y = p1.y + (xmax - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            out.push_back({xmax, y});
        } else if (!in1 && in2) { // Out to In
            float y = p1.y + (xmax - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            out.push_back({xmax, y});
            out.push_back(p2);
        }
    }
    return out;
}

std::vector<Point> clipBottom(const std::vector<Point>& poly, float ymin) {
    std::vector<Point> out;
    int n = poly.size();
    if (n == 0) return out;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];
        bool in1 = (p1.y >= ymin);
        bool in2 = (p2.y >= ymin);
        if (in1 && in2) {
            out.push_back(p2);
        } else if (in1 && !in2) { // In to Out
            float x = p1.x + (ymin - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            out.push_back({x, ymin});
        } else if (!in1 && in2) { // Out to In
            float x = p1.x + (ymin - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            out.push_back({x, ymin});
            out.push_back(p2);
        }
    }
    return out;
}

std::vector<Point> clipTop(const std::vector<Point>& poly, float ymax) {
    std::vector<Point> out;
    int n = poly.size();
    if (n == 0) return out;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];
        bool in1 = (p1.y <= ymax);
        bool in2 = (p2.y <= ymax);
        if (in1 && in2) {
            out.push_back(p2);
        } else if (in1 && !in2) { // In to Out
            float x = p1.x + (ymax - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            out.push_back({x, ymax});
        } else if (!in1 && in2) { // Out to In
            float x = p1.x + (ymax - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            out.push_back({x, ymax});
            out.push_back(p2);
        }
    }
    return out;
}

void sutherlandHodgmanClip() {
    clippedRect = originalRect;
    clippedRect = clipLeft(clippedRect, xmin);
    clippedRect = clipRight(clippedRect, xmax);
    clippedRect = clipBottom(clippedRect, ymin);
    clippedRect = clipTop(clippedRect, ymax);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Draw Clipping Window in Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // 2. Draw Original Unclipped Rectangle in White (Faint/Thin)
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (size_t i = 0; i < originalRect.size(); i++) {
        glVertex2f(originalRect[i].x, originalRect[i].y);
    }
    glEnd();

    // 3. Draw Clipped Rectangle in Bright Green (Bold)
    if (!clippedRect.empty()) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        for (size_t i = 0; i < clippedRect.size(); i++) {
            glVertex2f(clippedRect[i].x, clippedRect[i].y);
        }
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
    printf("=== Rectangle Clipping (Sutherland-Hodgman Algorithm) ===\n");
    printf("Enter clipping window (xmin ymin xmax ymax): ");
    scanf("%f %f %f %f", &xmin, &ymin, &xmax, &ymax);

    float rx1, ry1, rx2, ry2;
    printf("Enter subject rectangle corners (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &rx1, &ry1, &rx2, &ry2);

    // 4 vertices of subject rectangle
    originalRect.push_back({rx1, ry1});
    originalRect.push_back({rx2, ry1});
    originalRect.push_back({rx2, ry2});
    originalRect.push_back({rx1, ry2});

    // Perform Sutherland-Hodgman Polygon Clipping
    sutherlandHodgmanClip();

    printf("\nClipped Polygon Vertices (%lu vertices):\n", clippedRect.size());
    for (size_t i = 0; i < clippedRect.size(); i++) {
        printf("  V%lu: (%.2f, %.2f)\n", i + 1, clippedRect[i].x, clippedRect[i].y);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rectangle Clipping - Sutherland-Hodgman");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
