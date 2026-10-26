#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#define PI 3.14159265358979323846f

// 4 vertices of Original and Transformed Rectangles
float rect[4][2];
float transformedRect[4][2];
int choice = 1;
float tx, ty, sx, sy, angle;

// Helper function to draw coordinate axes (X and Y)
void drawAxes(void)
{
    glColor3f(0.3f, 0.3f, 0.3f); // Gray axes
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(-500.0f, 0.0f);
    glVertex2f(500.0f, 0.0f);
    glVertex2f(0.0f, -500.0f);
    glVertex2f(0.0f, 500.0f);
    glEnd();
}

// Helper function to draw a rectangle given 4 vertices
void drawRect(float r[4][2])
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
    {
        glVertex2f(r[i][0], r[i][1]);
    }
    glEnd();
}

// Display callback function
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw reference coordinate axes
    drawAxes();

    // 1. Draw Original Rectangle in White
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    drawRect(rect);

    // 2. Draw Transformed Rectangle in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    drawRect(transformedRect);

    glFlush();
}

// OpenGL initialization
void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set 2D orthographic viewing coordinates (-500 to +500)
    glOrtho(-500.0, 500.0, -500.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
    float x1, y1, x2, y2;

    // Step 1: Input rectangle corners
    printf("Enter bottom-left corner of rectangle (x1 y1): ");
    scanf("%f %f", &x1, &y1);
    printf("Enter top-right corner of rectangle (x2 y2): ");
    scanf("%f %f", &x2, &y2);

    // Step 2: Define 4 vertices of the rectangle
    rect[0][0] = x1; rect[0][1] = y1;
    rect[1][0] = x2; rect[1][1] = y1;
    rect[2][0] = x2; rect[2][1] = y2;
    rect[3][0] = x1; rect[3][1] = y2;

    // Step 3: Select transformation
    printf("\nSelect Basic 2D Transformation:\n");
    printf("1. Translation\n");
    printf("2. Scaling\n");
    printf("3. Rotation\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    // Step 4: Compute transformation
    switch (choice)
    {
        case 1: // Translation: x' = x + tx, y' = y + ty
            printf("Enter translation factors (tx ty): ");
            scanf("%f %f", &tx, &ty);
            for (int i = 0; i < 4; i++)
            {
                transformedRect[i][0] = rect[i][0] + tx;
                transformedRect[i][1] = rect[i][1] + ty;
            }
            break;

        case 2: // Scaling: x' = x * sx, y' = y * sy
            printf("Enter scaling factors (sx sy): ");
            scanf("%f %f", &sx, &sy);
            for (int i = 0; i < 4; i++)
            {
                transformedRect[i][0] = rect[i][0] * sx;
                transformedRect[i][1] = rect[i][1] * sy;
            }
            break;

        case 3: // Rotation: x' = x*cos(rad) - y*sin(rad), y' = x*sin(rad) + y*cos(rad)
            printf("Enter rotation angle in degrees (counter-clockwise): ");
            scanf("%f", &angle);
            {
                float rad = angle * (PI / 180.0f);
                for (int i = 0; i < 4; i++)
                {
                    transformedRect[i][0] = rect[i][0] * cosf(rad) - rect[i][1] * sinf(rad);
                    transformedRect[i][1] = rect[i][0] * sinf(rad) + rect[i][1] * cosf(rad);
                }
            }
            break;

        default:
            printf("Invalid choice! Displaying original rectangle only.\n");
            for (int i = 0; i < 4; i++)
            {
                transformedRect[i][0] = rect[i][0];
                transformedRect[i][1] = rect[i][1];
            }
            break;
    }

    // Step 5: Initialize GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Basic 2D Transformations on Rectangle");

    // Step 6: Initialize OpenGL viewing projection
    init();

    // Step 7 & 8: Register display callback and start GLUT main loop
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
