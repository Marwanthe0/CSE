# Experiment 14: Bézier Curve Generation

> **Lab Final Headline:** *Write a program to generate a Bezier curve.*

---

## 1. Introduction & Intuition (In Plain English)

* **What is a Bézier Curve?** It is a smooth mathematical curve widely used in computer graphics, fonts (like TrueType), animation paths, and vector graphic tools (like Photoshop Pen Tool).
* **How Does it Work?**
  * You define **4 Control Points** ($P_0, P_1, P_2, P_3$).
  * The curve **starts exactly at $P_0$** and **ends exactly at $P_3$**.
  * The two middle points ($P_1$ and $P_2$) act like "magnets" pulling the curve towards them to create a smooth, continuous bend.
* **The Blending Parameter $u$:** As parameter $u$ travels from $0.0$ to $1.0$, it calculates a weighted average of the 4 control points using mathematical formulas called **Bernstein Polynomials**.

---

## 2. In-Depth Mathematical Derivation (Step-by-Step)

### Step 1: The General Bézier Equation
A Bézier curve of degree $n$ (with $n+1$ control points) is defined for $u \in [0, 1]$ as:
$$P(u) = \sum_{k=0}^{n} B_{k,n}(u) \cdot P_k$$
where $B_{k,n}(u)$ are the **Bernstein Basis Polynomials**:
$$B_{k,n}(u) = \binom{n}{k} u^k (1 - u)^{n-k} = \frac{n!}{k!(n-k)!} u^k (1 - u)^{n-k}$$

---

### Step 2: Expanding for a Cubic Bézier Curve ($n = 3$, 4 Points)
For 4 control points $P_0, P_1, P_2, P_3$:
$$P(u) = B_{0,3}(u)P_0 + B_{1,3}(u)P_1 + B_{2,3}(u)P_2 + B_{3,3}(u)P_3$$

Let's calculate each Bernstein polynomial by plugging in $k = 0, 1, 2, 3$:

1. **For $k = 0$ ($P_0$ Weight):**
   $$B_{0,3}(u) = \binom{3}{0} u^0 (1 - u)^{3-0} = 1 \cdot 1 \cdot (1 - u)^3 = \mathbf{(1 - u)^3}$$

2. **For $k = 1$ ($P_1$ Weight):**
   $$B_{1,3}(u) = \binom{3}{1} u^1 (1 - u)^{3-1} = 3 \cdot u \cdot (1 - u)^2 = \mathbf{3u(1 - u)^2}$$

3. **For $k = 2$ ($P_2$ Weight):**
   $$B_{2,3}(u) = \binom{3}{2} u^2 (1 - u)^{3-2} = 3 \cdot u^2 \cdot (1 - u) = \mathbf{3u^2(1 - u)}$$

4. **For $k = 3$ ($P_3$ Weight):**
   $$B_{3,3}(u) = \binom{3}{3} u^3 (1 - u)^{3-3} = 1 \cdot u^3 \cdot 1 = \mathbf{u^3}$$

---

### Step 3: Partition of Unity (The Weights Always Sum to 1)
$$\sum_{k=0}^{3} B_{k,3}(u) = (1 - u)^3 + 3u(1 - u)^2 + 3u^2(1 - u) + u^3 = [(1 - u) + u]^3 = [1]^3 = 1$$
Because all weights sum to $1$ and are non-negative, the curve is guaranteed to stay inside the **convex hull** (the boundary box) of its control points.

---

### Step 4: Final Coordinate Equations
$$\mathbf{x(u) = (1-u)^3 x_0 + 3u(1-u)^2 x_1 + 3u^2(1-u) x_2 + u^3 x_3}$$
$$\mathbf{y(u) = (1-u)^3 y_0 + 3u(1-u)^2 y_1 + 3u^2(1-u) y_2 + u^3 y_3}$$

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm Cubic_Bezier_Curve(P0, P1, P2, P3):
1. Input 4 control points: P0, P1, P2, P3
2. Draw control lines connecting P0 -> P1 -> P2 -> P3 in Gray
3. Plot control points P0, P1, P2, P3 in Red

4. Step parameter u from 0.0 to 1.0 (step size du = 0.001):
       while u <= 1.0:
           // 1. Calculate Bernstein basis terms
           b0 = (1 - u)^3
           b1 = 3 * u * (1 - u)^2
           b2 = 3 * u^2 * (1 - u)
           b3 = u^3

           // 2. Compute curve coordinate
           x = b0 * P0.x + b1 * P1.x + b2 * P2.x + b3 * P3.x
           y = b0 * P0.y + b1 * P1.y + b2 * P2.y + b3 * P3.y

           Plot vertex (x, y) on the curve in Green
           u = u + du

5. End
```

---

## 4. Hand Calculation Example (Trace Table)

**Problem:** Control Points $P_0(0, 0), P_1(0, 100), P_2(100, 100), P_3(100, 0)$.

| $u$ | $B_0(u)$ | $B_1(u)$ | $B_2(u)$ | $B_3(u)$ | Calculated $(x, y)$ | Meaning |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **0.00** | 1.000 | 0.000 | 0.000 | 0.000 | **(0.0, 0.0)** | Curve starts at $P_0$ |
| **0.25** | 0.422 | 0.422 | 0.141 | 0.016 | **(15.6, 56.2)** | Pulled towards $P_1$ |
| **0.50** | 0.125 | 0.375 | 0.375 | 0.125 | **(50.0, 75.0)** | Midpoint of curve |
| **0.75** | 0.016 | 0.141 | 0.422 | 0.422 | **(84.4, 56.2)** | Pulled towards $P_2$ |
| **1.00** | 0.000 | 0.000 | 0.000 | 1.000 | **(100.0, 0.0)** | Curve ends at $P_3$ |

---

## 5. Complete C++ OpenGL Code

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

struct Point { float x, y; };

Point controlPoints[4];

Point computeBezierPoint(float u, Point p0, Point p1, Point p2, Point p3) {
    float u2 = u * u, u3 = u2 * u;
    float oneMinusU = 1.0f - u;
    float oneMinusU2 = oneMinusU * oneMinusU;
    float oneMinusU3 = oneMinusU2 * oneMinusU;

    float b0 = oneMinusU3;
    float b1 = 3.0f * u * oneMinusU2;
    float b2 = 3.0f * u2 * oneMinusU;
    float b3 = u3;

    Point p;
    p.x = b0 * p0.x + b1 * p1.x + b2 * p2.x + b3 * p3.x;
    p.y = b0 * p0.y + b1 * p1.y + b2 * p2.y + b3 * p3.y;
    return p;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Control Polygon (Gray)
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 4; i++) glVertex2f(controlPoints[i].x, controlPoints[i].y);
    glEnd();

    // 2. Control Points (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 4; i++) glVertex2f(controlPoints[i].x, controlPoints[i].y);
    glEnd();

    // 3. Smooth Bezier Curve (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    for (float u = 0.0f; u <= 1.0f; u += 0.001f) {
        Point p = computeBezierPoint(u, controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3]);
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    printf("=== Bezier Curve Generation ===\n");
    printf("Enter 4 Control Points:\n");
    printf("Enter P0 (x y): "); scanf("%f %f", &controlPoints[0].x, &controlPoints[0].y);
    printf("Enter P1 (x y): "); scanf("%f %f", &controlPoints[1].x, &controlPoints[1].y);
    printf("Enter P2 (x y): "); scanf("%f %f", &controlPoints[2].x, &controlPoints[2].y);
    printf("Enter P3 (x y): "); scanf("%f %f", &controlPoints[3].x, &controlPoints[3].y);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curve Generation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 6. Key Viva Questions & Clear Answers

1. **What is the Convex Hull property?**
   * *Answer:* The entire Bézier curve is guaranteed to lie inside the polygon formed by connecting its control points.
2. **What are the boundary conditions of a Bézier curve?**
   * *Answer:* At $u = 0$, $P(0) = P_0$. At $u = 1$, $P(1) = P_3$. The curve always starts at the first control point and terminates at the last control point.
