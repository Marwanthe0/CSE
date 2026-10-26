#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#define PI 3.14159265358979323846f

float triangle[3][2];
float transformedTriangle[3][2];
int choice = 1;
float tx, ty, sx, sy, angle;

// Helper function to draw coordinate axes
void drawAxes(void) {
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(-500.0f, 0.0f);
    glVertex2f(500.0f, 0.0f);
    glVertex2f(0.0f, -500.0f);
    glVertex2f(0.0f, 500.0f);
    glEnd();
}

// Helper function to draw a triangle given 3 vertices
void drawTriangle(float t[3][2]) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++) {
        glVertex2f(t[i][0], t[i][1]);
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // 1. Draw Original Triangle in White
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    drawTriangle(triangle);

    // 2. Draw Transformed Triangle in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    drawTriangle(transformedTriangle);

    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Allow viewing both positive and negative coordinate spaces
    glOrtho(-500.0, 500.0, -500.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    printf("Enter vertex 1 (x1 y1): ");
    scanf("%f %f", &triangle[0][0], &triangle[0][1]);
    printf("Enter vertex 2 (x2 y2): ");
    scanf("%f %f", &triangle[1][0], &triangle[1][1]);
    printf("Enter vertex 3 (x3 y3): ");
    scanf("%f %f", &triangle[2][0], &triangle[2][1]);

    printf("\nSelect Basic 2D Transformation:\n");
    printf("1. Translation\n");
    printf("2. Scaling\n");
    printf("3. Rotation\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Translation: x' = x + tx, y' = y + ty
            printf("Enter translation factors (tx ty): ");
            scanf("%f %f", &tx, &ty);
            for (int i = 0; i < 3; i++) {
                transformedTriangle[i][0] = triangle[i][0] + tx;
                transformedTriangle[i][1] = triangle[i][1] + ty;
            }
            break;

        case 2: // Scaling: x' = x * sx, y' = y * sy
            printf("Enter scaling factors (sx sy): ");
            scanf("%f %f", &sx, &sy);
            for (int i = 0; i < 3; i++) {
                transformedTriangle[i][0] = triangle[i][0] * sx;
                transformedTriangle[i][1] = triangle[i][1] * sy;
            }
            break;

        case 3: // Rotation: x' = x*cos(theta) - y*sin(theta), y' = x*sin(theta) + y*cos(theta)
            printf("Enter rotation angle in degrees (counter-clockwise): ");
            scanf("%f", &angle);
            {
                float rad = angle * (PI / 180.0f);
                for (int i = 0; i < 3; i++) {
                    transformedTriangle[i][0] = triangle[i][0] * cosf(rad) - triangle[i][1] * sinf(rad);
                    transformedTriangle[i][1] = triangle[i][0] * sinf(rad) + triangle[i][1] * cosf(rad);
                }
            }
            break;

        default:
            printf("Invalid choice! Displaying original triangle only.\n");
            for (int i = 0; i < 3; i++) {
                transformedTriangle[i][0] = triangle[i][0];
                transformedTriangle[i][1] = triangle[i][1];
            }
            break;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Basic 2D Transformations on Triangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
