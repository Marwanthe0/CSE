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
float xf = 0.0f, yf = 0.0f; // Fixed point

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

    // 3. Highlight Fixed Point in Red (if choice 1 or 2)
    if (choice == 1 || choice == 2) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glPointSize(6.0f);
        glBegin(GL_POINTS);
        glVertex2f(xf, yf);
        glEnd();
    }

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

    printf("\nSelect Composite Transformation:\n");
    printf("1. Rotation about an Arbitrary Fixed Point (xf, yf)\n");
    printf("2. Scaling with respect to an Arbitrary Fixed Point (xf, yf)\n");
    printf("3. General Composite: Translate -> Rotate -> Scale\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: { // Rotation about Fixed Point: T(xf, yf) * R(theta) * T(-xf, -yf)
            float angle;
            printf("Enter arbitrary fixed point (xf yf): ");
            scanf("%f %f", &xf, &yf);
            printf("Enter rotation angle in degrees: ");
            scanf("%f", &angle);
            float rad = angle * (PI / 180.0f);

            for (int i = 0; i < 3; i++) {
                float dx = triangle[i][0] - xf;
                float dy = triangle[i][1] - yf;
                transformedTriangle[i][0] = xf + (dx * cosf(rad) - dy * sinf(rad));
                transformedTriangle[i][1] = yf + (dx * sinf(rad) + dy * cosf(rad));
            }
            break;
        }

        case 2: { // Scaling about Fixed Point: T(xf, yf) * S(sx, sy) * T(-xf, -yf)
            float sx, sy;
            printf("Enter arbitrary fixed point (xf yf): ");
            scanf("%f %f", &xf, &yf);
            printf("Enter scaling factors (sx sy): ");
            scanf("%f %f", &sx, &sy);

            for (int i = 0; i < 3; i++) {
                transformedTriangle[i][0] = xf + (triangle[i][0] - xf) * sx;
                transformedTriangle[i][1] = yf + (triangle[i][1] - yf) * sy;
            }
            break;
        }

        case 3: { // Multi-Step: Translate -> Rotate -> Scale
            float tx, ty, angle, sx, sy;
            printf("Enter translation factors (tx ty): ");
            scanf("%f %f", &tx, &ty);
            printf("Enter rotation angle in degrees: ");
            scanf("%f", &angle);
            printf("Enter scaling factors (sx sy): ");
            scanf("%f %f", &sx, &sy);

            float rad = angle * (PI / 180.0f);
            for (int i = 0; i < 3; i++) {
                // 1. Translate
                float xt = triangle[i][0] + tx;
                float yt = triangle[i][1] + ty;

                // 2. Rotate
                float xr = xt * cosf(rad) - yt * sinf(rad);
                float yr = xt * sinf(rad) + yt * cosf(rad);

                // 3. Scale
                transformedTriangle[i][0] = xr * sx;
                transformedTriangle[i][1] = yr * sy;
            }
            break;
        }

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
    glutCreateWindow("Composite 2D Transformations on Triangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
