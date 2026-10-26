# Experiment 10: Composite Transformations on a Rectangle

> **Lab Final Headline:** *Write a program to perform composite transformations on a rectangle.*

---

## 1. Introduction & Intuition (In Plain English)

* **What is a Composite Transformation?** When you apply two or more transformations one after another (e.g. Translate $\to$ Rotate $\to$ Scale), it is called a composite transformation.
* **The Arbitrary Pivot Point Problem:** 
  * Normal rotation or scaling always happens around the origin $(0, 0)$.
  * If you want to rotate a rectangle around its **own center** or an arbitrary point $(x_f, y_f)$, you must:
    1. **Translate** the pivot point to the origin $(0, 0)$.
    2. **Rotate / Scale** the object at the origin.
    3. **Translate** the pivot point back to its original location!

---

## 2. In-Depth Mathematical Derivation (Step-by-Step)

### Step 1: Matrix Multiplication Sequence
When transformations $M_1, M_2, M_3$ are applied in order, the combined matrix is:
$$M_{\text{composite}} = M_3 \cdot M_2 \cdot M_1$$

> **Note:** Matrix multiplication is **non-commutative** ($A \cdot B \ne B \cdot A$). The order of operations strictly matters!

---

### Step 2: Rotation Around an Arbitrary Pivot $(x_f, y_f)$
The 3-step sequence is:
$$M = T(x_f, y_f) \cdot R(\theta) \cdot T(-x_f, -y_f)$$

Multiplying the $3 \times 3$ matrices:
$$M = \begin{bmatrix} 1 & 0 & x_f \\ 0 & 1 & y_f \\ 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} \cos\theta & -\sin\theta & 0 \\ \sin\theta & \cos\theta & 0 \\ 0 & 0 & 1 \end{bmatrix} \begin{bmatrix} 1 & 0 & -x_f \\ 0 & 1 & -y_f \\ 0 & 0 & 1 \end{bmatrix}$$
$$M = \begin{bmatrix} \cos\theta & -\sin\theta & x_f(1 - \cos\theta) + y_f\sin\theta \\ \sin\theta & \cos\theta & y_f(1 - \cos\theta) - x_f\sin\theta \\ 0 & 0 & 1 \end{bmatrix}$$

Multiplying with point $(x, y)$ gives the final formulas:
$$\mathbf{x' = x_f + (x - x_f)\cos\theta - (y - y_f)\sin\theta}$$
$$\mathbf{y' = y_f + (x - x_f)\sin\theta + (y - y_f)\cos\theta}$$

---

### Step 3: Scaling Around an Arbitrary Pivot $(x_f, y_f)$
The 3-step sequence is:
$$M = T(x_f, y_f) \cdot S(s_x, s_y) \cdot T(-x_f, -y_f)$$

Multiplying out the matrices yields:
$$\mathbf{x' = x_f + (x - x_f) \cdot s_x}$$
$$\mathbf{y' = y_f + (y - y_f) \cdot s_y}$$

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm Composite_Transformations_Rectangle:
1. Input rectangle corners (x1, y1) and (x2, y2).
2. Generate 4 vertices: V[0]=(x1,y1), V[1]=(x2,y1), V[2]=(x2,y2), V[3]=(x1,y2)

3. Choose composite option:
       Option 1 (Rotate about Fixed Point xf, yf):
           Input xf, yf, angle_deg
           rad = angle_deg * (PI / 180)
           For each vertex i (0 to 3):
               dx = V[i].x - xf
               dy = V[i].y - yf
               V_new[i].x = xf + (dx * cos(rad) - dy * sin(rad))
               V_new[i].y = yf + (dx * sin(rad) + dy * cos(rad))

       Option 2 (Scale about Fixed Point xf, yf):
           Input xf, yf, sx, sy
           For each vertex i (0 to 3):
               V_new[i].x = xf + (V[i].x - xf) * sx
               V_new[i].y = yf + (V[i].y - yf) * sy

       Option 3 (Translate -> Rotate -> Scale):
           Input tx, ty, angle_deg, sx, sy
           rad = angle_deg * (PI / 180)
           For each vertex i (0 to 3):
               xt = V[i].x + tx, yt = V[i].y + ty
               xr = xt * cos(rad) - yt * sin(rad)
               yr = xt * sin(rad) + yt * cos(rad)
               V_new[i].x = xr * sx
               V_new[i].y = yr * sy

4. Display:
       Draw Original Rectangle (White)
       Draw Transformed Rectangle (Green)
       Draw Pivot Point (Red)
5. End
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

float rect[4][2];
float transformedRect[4][2];
int choice = 1;
float xf = 0.0f, yf = 0.0f;

void drawAxes(void) {
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex2f(-500.0f, 0.0f); glVertex2f(500.0f, 0.0f);
    glVertex2f(0.0f, -500.0f); glVertex2f(0.0f, 500.0f);
    glEnd();
}

void drawRect(float r[4][2]) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) glVertex2f(r[i][0], r[i][1]);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // 1. Original Rectangle (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    drawRect(rect);

    // 2. Transformed Rectangle (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    drawRect(transformedRect);

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
    float x1, y1, x2, y2;
    printf("Enter bottom-left corner (x1 y1): ");
    scanf("%f %f", &x1, &y1);
    printf("Enter top-right corner (x2 y2): ");
    scanf("%f %f", &x2, &y2);

    rect[0][0] = x1; rect[0][1] = y1;
    rect[1][0] = x2; rect[1][1] = y1;
    rect[2][0] = x2; rect[2][1] = y2;
    rect[3][0] = x1; rect[3][1] = y2;

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
            for (int i = 0; i < 4; i++) {
                float dx = rect[i][0] - xf, dy = rect[i][1] - yf;
                transformedRect[i][0] = xf + (dx * cosf(rad) - dy * sinf(rad));
                transformedRect[i][1] = yf + (dx * sinf(rad) + dy * cosf(rad));
            }
            break;
        }
        case 2: {
            float sx, sy;
            printf("Enter fixed point (xf yf): ");
            scanf("%f %f", &xf, &yf);
            printf("Enter sx sy: ");
            scanf("%f %f", &sx, &sy);
            for (int i = 0; i < 4; i++) {
                transformedRect[i][0] = xf + (rect[i][0] - xf) * sx;
                transformedRect[i][1] = yf + (rect[i][1] - yf) * sy;
            }
            break;
        }
        case 3: {
            float tx, ty, angle, sx, sy;
            printf("Enter tx ty: "); scanf("%f %f", &tx, &ty);
            printf("Enter angle (deg): "); scanf("%f", &angle);
            printf("Enter sx sy: "); scanf("%f %f", &sx, &sy);
            float rad = angle * (PI / 180.0f);
            for (int i = 0; i < 4; i++) {
                float xt = rect[i][0] + tx, yt = rect[i][1] + ty;
                float xr = xt * cosf(rad) - yt * sinf(rad);
                float yr = xt * sinf(rad) + yt * cosf(rad);
                transformedRect[i][0] = xr * sx;
                transformedRect[i][1] = yr * sy;
            }
            break;
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Composite Transformations - Rectangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 5. Key Viva Questions & Clear Answers

1. **Why does $T \cdot R \ne R \cdot T$?**
   * *Answer:* Because 2D matrix multiplication is non-commutative. Translating and then rotating creates a completely different result than rotating and then translating.
2. **What are the 3 steps to rotate about an arbitrary point $(x_f, y_f)$?**
   * *Answer:* $T(x_f, y_f) \cdot R(\theta) \cdot T(-x_f, -y_f)$.
