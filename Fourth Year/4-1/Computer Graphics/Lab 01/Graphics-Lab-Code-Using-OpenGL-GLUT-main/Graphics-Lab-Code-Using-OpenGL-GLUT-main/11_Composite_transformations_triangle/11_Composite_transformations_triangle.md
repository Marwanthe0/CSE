# Experiment 11: Composite Transformations on a Triangle

> **Lab Final Headline:** *Write a program to perform composite transformations on a triangle.*

---

## 1. Introduction & Intuition (In Plain English)

* **What is this experiment about?** It performs composite transformations (such as rotating or scaling around a chosen fixed point or applying multi-step pipelines) on a triangle in OpenGL.
* **Why do we need composite transformations?** If you rotate a triangle using standard formulas, it will rotate around $(0, 0)$ and fly off to another quadrant. To spin the triangle **in-place** (for example, around its own tip or centroid), you must translate the pivot to the origin, perform the rotation, and translate it back.

---

## 2. In-Depth Mathematical Derivation (Step-by-Step)

### Step 1: Rotation About an Arbitrary Pivot $(x_f, y_f)$
The 3-stage sequence:
$$M = T(x_f, y_f) \cdot R(\theta) \cdot T(-x_f, -y_f)$$

Matrix expansion:
$$M = \begin{bmatrix} 1 & 0 & x_f \\ 0 & 1 & y_f \\ 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} \cos\theta & -\sin\theta & 0 \\ \sin\theta & \cos\theta & 0 \\ 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} 1 & 0 & -x_f \\ 0 & 1 & -y_f \\ 0 & 0 & 1 \end{bmatrix}$$
$$M = \begin{bmatrix} \cos\theta & -\sin\theta & x_f(1 - \cos\theta) + y_f\sin\theta \\ \sin\theta & \cos\theta & y_f(1 - \cos\theta) - x_f\sin\theta \\ 0 & 0 & 1 \end{bmatrix}$$

Applied to each vertex $i \in \{1, 2, 3\}$:
$$\mathbf{x'_i = x_f + (x_i - x_f)\cos\theta - (y_i - y_f)\sin\theta}$$
$$\mathbf{y'_i = y_f + (x_i - x_f)\sin\theta + (y_i - y_f)\cos\theta}$$

---

### Step 2: Scaling About an Arbitrary Pivot $(x_f, y_f)$
$$M = T(x_f, y_f) \cdot S(s_x, s_y) \cdot T(-x_f, -y_f)$$

Applied to each vertex $i \in \{1, 2, 3\}$:
$$\mathbf{x'_i = x_f + (x_i - x_f) \cdot s_x}$$
$$\mathbf{y'_i = y_f + (y_i - y_f) \cdot s_y}$$

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm Composite_Transformations_Triangle:
1. Input 3 vertices: V[0]=(x1,y1), V[1]=(x2,y2), V[2]=(x3,y3)

2. Choose composite option:
       Option 1 (Rotate about Fixed Point xf, yf):
           Input xf, yf, angle_deg
           rad = angle_deg * (PI / 180)
           For each vertex i (0 to 2):
               dx = V[i].x - xf, dy = V[i].y - yf
               V_new[i].x = xf + (dx * cos(rad) - dy * sin(rad))
               V_new[i].y = yf + (dx * sin(rad) + dy * cos(rad))

       Option 2 (Scale about Fixed Point xf, yf):
           Input xf, yf, sx, sy
           For each vertex i (0 to 2):
               V_new[i].x = xf + (V[i].x - xf) * sx
               V_new[i].y = yf + (V[i].y - yf) * sy

       Option 3 (Translate -> Rotate -> Scale):
           Input tx, ty, angle_deg, sx, sy
           rad = angle_deg * (PI / 180)
           For each vertex i (0 to 2):
               xt = V[i].x + tx, yt = V[i].y + ty
               xr = xt * cos(rad) - yt * sin(rad)
               yr = xt * sin(rad) + yt * cos(rad)
               V_new[i].x = xr * sx
               V_new[i].y = yr * sy

3. Render:
       Draw Original Triangle (White)
       Draw Transformed Triangle (Green)
       Draw Pivot Point (Red)
4. End
```

---

## 4. Complete C++ OpenGL Code

```cpp
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
float xf = 0.0f, yf = 0.0f;

void drawAxes(void) {
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex2f(-500.0f, 0.0f); glVertex2f(500.0f, 0.0f);
    glVertex2f(0.0f, -500.0f); glVertex2f(0.0f, 500.0f);
    glEnd();
}

void drawTriangle(float t[3][2]) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++) glVertex2f(t[i][0], t[i][1]);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // 1. Original Triangle (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    drawTriangle(triangle);

    // 2. Transformed Triangle (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    drawTriangle(transformedTriangle);

    // 3. Pivot Point (Red)
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
    glOrtho(-500.0, 500.0, -500.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    printf("Enter vertex 1 (x1 y1): ");
    scanf("%f %f", &triangle[0][0], &triangle[0][1]);
    printf("Enter vertex 2 (x2 y2): ");
    scanf("%f %f", &triangle[1][0], &triangle[1][1]);
    printf("Enter vertex 3 (x3 y3): ");
    scanf("%f %f", &triangle[2][0], &triangle[2][1]);

    printf("\n1. Rotate about Fixed Point\n2. Scale about Fixed Point\n3. Translate -> Rotate -> Scale\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            float angle;
            printf("Enter fixed point (xf yf): ");
            scanf("%f %f", &xf, &yf);
            printf("Enter angle (deg): ");
            scanf("%f", &angle);
            float rad = angle * (PI / 180.0f);
            for (int i = 0; i < 3; i++) {
                float dx = triangle[i][0] - xf, dy = triangle[i][1] - yf;
                transformedTriangle[i][0] = xf + (dx * cosf(rad) - dy * sinf(rad));
                transformedTriangle[i][1] = yf + (dx * sinf(rad) + dy * cosf(rad));
            }
            break;
        }
        case 2: {
            float sx, sy;
            printf("Enter fixed point (xf yf): ");
            scanf("%f %f", &xf, &yf);
            printf("Enter sx sy: ");
            scanf("%f %f", &sx, &sy);
            for (int i = 0; i < 3; i++) {
                transformedTriangle[i][0] = xf + (triangle[i][0] - xf) * sx;
                transformedTriangle[i][1] = yf + (triangle[i][1] - yf) * sy;
            }
            break;
        }
        case 3: {
            float tx, ty, angle, sx, sy;
            printf("Enter tx ty: "); scanf("%f %f", &tx, &ty);
            printf("Enter angle (deg): "); scanf("%f", &angle);
            printf("Enter sx sy: "); scanf("%f %f", &sx, &sy);
            float rad = angle * (PI / 180.0f);
            for (int i = 0; i < 3; i++) {
                float xt = triangle[i][0] + tx, yt = triangle[i][1] + ty;
                float xr = xt * cosf(rad) - yt * sinf(rad);
                float yr = xt * sinf(rad) + yt * cosf(rad);
                transformedTriangle[i][0] = xr * sx;
                transformedTriangle[i][1] = yr * sy;
            }
            break;
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Composite Transformations - Triangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 5. Key Viva Questions & Clear Answers

1. **How do you keep the fixed point $(x_f, y_f)$ unchanged after rotation?**
   * *Answer:* By conjugating the rotation matrix with translation matrices: $T(x_f, y_f) \cdot R(\theta) \cdot T(-x_f, -y_f)$.
