# Experiment 09: Basic Transformations on a Triangle

> **Lab Final Headline:** *Write a program to perform basic transformations on a triangle.*

---

## 1. Introduction & Intuition (In Plain English)

* **What does this experiment do?** It applies 2D geometric transformations (**Translation**, **Scaling**, and **Rotation**) to a 3-vertex triangle in OpenGL.
* **Core Idea:** A triangle is formed by 3 coordinate vertices $(x_1, y_1), (x_2, y_2), (x_3, y_3)$. When we apply a transformation matrix to each of the 3 vertices, connecting the new points produces the transformed triangle.

---

## 2. In-Depth Mathematical Derivation (Step-by-Step)

### Step 1: Matrix Representation
Represent the 3 vertices of the triangle in a $3 \times 3$ homogeneous coordinate matrix:
$$V = \begin{bmatrix} x_1 & x_2 & x_3 \\ y_1 & y_2 & y_3 \\ 1 & 1 & 1 \end{bmatrix}$$

Transformed coordinates $V'$ are obtained by matrix multiplication:
$$V' = M \cdot V$$

---

### Step 2: Transformation Formulas

#### 1. Translation:
Moving the triangle by $(t_x, t_y)$:
$$\mathbf{x'_i = x_i + t_x}, \quad \mathbf{y'_i = y_i + t_y} \quad (\text{for } i = 1, 2, 3)$$

#### 2. Scaling (relative to origin):
Resizing by factors $(s_x, s_y)$:
$$\mathbf{x'_i = x_i \cdot s_x}, \quad \mathbf{y'_i = y_i \cdot s_y}$$

#### 3. Rotation (by angle $\theta$ around origin):
$$\mathbf{x'_i = x_i \cos\theta - y_i \sin\theta}$$
$$\mathbf{y'_i = x_i \sin\theta + y_i \cos\theta}$$

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm Basic_Transformations_Triangle:
1. Input 3 triangle vertices: V[0]=(x1,y1), V[1]=(x2,y2), V[2]=(x3,y3)

2. Choose transformation:
       If Translation:
           Input tx, ty
           For i = 0 to 2:
               V_new[i].x = V[i].x + tx
               V_new[i].y = V[i].y + ty

       If Scaling:
           Input sx, sy
           For i = 0 to 2:
               V_new[i].x = V[i].x * sx
               V_new[i].y = V[i].y * sy

       If Rotation:
           Input angle (deg), rad = angle * (PI / 180)
           For i = 0 to 2:
               V_new[i].x = V[i].x * cos(rad) - V[i].y * sin(rad)
               V_new[i].y = V[i].x * sin(rad) + V[i].y * cos(rad)

3. Render:
       Draw Original Triangle in White
       Draw Transformed Triangle in Green
4. End
```

---

## 4. Hand Calculation Example (Trace Table)

**Problem:** Scale triangle $(0, 0), (100, 0), (50, 80)$ by $s_x = 2.0, s_y = 1.5$.

| Vertex | Original $(x, y)$ | Scaling Calculation | Transformed $(x', y')$ |
|:---:|:---:|:---:|:---:|
| $V_1$ | $(0, 0)$ | $x' = 0 \cdot 2.0, \ y' = 0 \cdot 1.5$ | **(0, 0)** |
| $V_2$ | $(100, 0)$ | $x' = 100 \cdot 2.0, \ y' = 0 \cdot 1.5$ | **(200, 0)** |
| $V_3$ | $(50, 80)$ | $x' = 50 \cdot 2.0, \ y' = 80 \cdot 1.5$ | **(100, 120)** |

---

## 5. Complete C++ OpenGL Code

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
float tx, ty, sx, sy, angle;

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

    // Original Triangle (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    drawTriangle(triangle);

    // Transformed Triangle (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    drawTriangle(transformedTriangle);

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

    printf("\n1. Translation\n2. Scaling\n3. Rotation\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter tx ty: ");
            scanf("%f %f", &tx, &ty);
            for (int i = 0; i < 3; i++) {
                transformedTriangle[i][0] = triangle[i][0] + tx;
                transformedTriangle[i][1] = triangle[i][1] + ty;
            }
            break;
        case 2:
            printf("Enter sx sy: ");
            scanf("%f %f", &sx, &sy);
            for (int i = 0; i < 3; i++) {
                transformedTriangle[i][0] = triangle[i][0] * sx;
                transformedTriangle[i][1] = triangle[i][1] * sy;
            }
            break;
        case 3:
            printf("Enter rotation angle in degrees: ");
            scanf("%f", &angle);
            {
                float rad = angle * (PI / 180.0f);
                for (int i = 0; i < 3; i++) {
                    transformedTriangle[i][0] = triangle[i][0] * cosf(rad) - triangle[i][1] * sinf(rad);
                    transformedTriangle[i][1] = triangle[i][0] * sinf(rad) + triangle[i][1] * cosf(rad);
                }
            }
            break;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Basic Transformations - Triangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 6. Key Viva Questions & Clear Answers

1. **What is a Rigid Body Transformation?**
   * *Answer:* A transformation that preserves shapes and sizes (distances and angles between vertices remain unchanged). Translation and Rotation are rigid body transformations.
2. **What is the centroid of a triangle?**
   * *Answer:* The geometric center: $(\frac{x_1+x_2+x_3}{3}, \frac{y_1+y_2+y_3}{3})$.
