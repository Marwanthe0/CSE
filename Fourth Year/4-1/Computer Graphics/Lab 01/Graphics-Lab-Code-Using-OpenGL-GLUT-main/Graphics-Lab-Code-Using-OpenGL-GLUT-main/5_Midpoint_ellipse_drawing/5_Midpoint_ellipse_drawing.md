# Experiment 05: Mid-Point Ellipse Drawing Algorithm

> **Lab Final Headline:** *Draw an ellipse using mid-point ellipse drawing algorithm.*

---

## 1. Introduction & Intuition (In Plain English)

* **What is an Ellipse?** An ellipse is like a stretched circle. It has a horizontal radius $r_x$ (semi-major axis) and a vertical radius $r_y$ (semi-minor axis).
* **Why do we need 2 Regions?**
  * In a circle, the slope changes evenly from $0^\circ$ to $90^\circ$.
  * In an ellipse, the curve starts out relatively flat (**Region 1**, where slope $|\frac{dy}{dx}| < 1$) and then becomes very steep (**Region 2**, where slope $|\frac{dy}{dx}| \ge 1$).
  * In **Region 1**, we step by $1$ along $x$ and choose the best $y$.
  * In **Region 2**, we step by $1$ along $y$ and choose the best $x$.
* **Symmetry:** An ellipse has **4-way symmetry** (across the 4 quadrants). We only calculate the top-right quadrant ($90^\circ$ arc) and reflect it into the other 3 quadrants.

---

## 2. In-Depth Mathematical Derivation (Step-by-Step)

### Step 1: The Implicit Ellipse Equation
An ellipse centered at $(0, 0)$ is defined by:
$$f_{\text{ellipse}}(x, y) = r_y^2 x^2 + r_x^2 y^2 - r_x^2 r_y^2$$

* $f(x, y) < 0 \implies$ Point is **inside** the ellipse.
* $f(x, y) = 0 \implies$ Point is **on** the ellipse boundary.
* $f(x, y) > 0 \implies$ Point is **outside** the ellipse.

---

### Step 2: The Boundary Between Region 1 and Region 2
The tangent slope at any point is:
$$\frac{dy}{dx} = -\frac{2r_y^2 x}{2r_x^2 y}$$

The boundary between Region 1 and Region 2 occurs where the slope is $-1$:
$$\left|-\frac{2r_y^2 x}{2r_x^2 y}\right| = 1 \iff \mathbf{2r_y^2 x = 2r_x^2 y}$$

* **Region 1 Condition:** While $2r_y^2 x < 2r_x^2 y$ (more horizontal).
* **Region 2 Condition:** When $2r_y^2 x \ge 2r_x^2 y$ (more vertical).

---

### Step 3: Region 1 Derivation (Stepping along $x$)
Starting from $(0, r_y)$:
* Next $x$ is always $x_k + 1$.
* Candidate pixels: $E(x_k+1, y_k)$ and $SE(x_k+1, y_k-1)$.
* Midpoint: $M = \left(x_k + 1, y_k - \frac{1}{2}\right)$.

Plugging $M$ into the ellipse equation gives the decision parameter $p_{1_k}$:
$$p_{1_k} = r_y^2(x_k + 1)^2 + r_x^2\left(y_k - \frac{1}{2}\right)^2 - r_x^2 r_y^2$$

* **Initial parameter at $(0, r_y)$:**
  $$\mathbf{p_{1_0} = r_y^2 - r_x^2 r_y + \frac{1}{4}r_x^2}$$
* **Update rules for next step:**
  * **If $p_{1_k} < 0$ (Choose $E \implies y_{k+1} = y_k$):**
    $$\mathbf{p_{1_{k+1}} = p_{1_k} + 2r_y^2 x_{k+1} + r_y^2}$$
  * **If $p_{1_k} \ge 0$ (Choose $SE \implies y_{k+1} = y_k - 1$):**
    $$\mathbf{p_{1_{k+1}} = p_{1_k} + 2r_y^2 x_{k+1} - 2r_x^2 y_{k+1} + r_y^2}$$

---

### Step 4: Region 2 Derivation (Stepping along $y$)
In Region 2, the curve drops rapidly:
* Next $y$ is always $y_k - 1$.
* Candidate pixels: $S(x_k, y_k-1)$ and $SE(x_k+1, y_k-1)$.
* Midpoint: $M = \left(x_k + \frac{1}{2}, y_k - 1\right)$.

Plugging $M$ into the ellipse equation gives $p_{2_k}$:
$$p_{2_k} = r_y^2\left(x_k + \frac{1}{2}\right)^2 + r_x^2(y_k - 1)^2 - r_x^2 r_y^2$$

* **Initial parameter (using the last point $(x_0, y_0)$ from Region 1):**
  $$\mathbf{p_{2_0} = r_y^2\left(x_0 + \frac{1}{2}\right)^2 + r_x^2(y_0 - 1)^2 - r_x^2 r_y^2}$$
* **Update rules for next step:**
  * **If $p_{2_k} > 0$ (Choose $S \implies x_{k+1} = x_k$):**
    $$\mathbf{p_{2_{k+1}} = p_{2_k} - 2r_x^2 y_{k+1} + r_x^2}$$
  * **If $p_{2_k} \le 0$ (Choose $SE \implies x_{k+1} = x_k + 1$):**
    $$\mathbf{p_{2_{k+1}} = p_{2_k} + 2r_y^2 x_{k+1} - 2r_x^2 y_{k+1} + r_x^2}$$

---

### Step 5: Four-Way Symmetry Formulas
For each point $(x, y)$, plot in all 4 quadrants centered at $(x_c, y_c)$:
1. $(x_c + x, y_c + y)$
2. $(x_c - x, y_c + y)$
3. $(x_c + x, y_c - y)$
4. $(x_c - x, y_c - y)$

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm Midpoint_Ellipse(xc, yc, rx, ry):
1. --- REGION 1 ---
   Start at: x = 0, y = ry
   p1 = (ry^2) - (rx^2 * ry) + (0.25 * rx^2)
   dx = 2 * ry^2 * x
   dy = 2 * rx^2 * y
   Plot4Points(xc, yc, x, y)

   While dx < dy:
       x = x + 1
       dx = dx + 2 * ry^2
       if p1 < 0:
           p1 = p1 + dx + ry^2
       else:
           y = y - 1
           dy = dy - 2 * rx^2
           p1 = p1 + dx - dy + ry^2
       Plot4Points(xc, yc, x, y)

2. --- REGION 2 ---
   p2 = ry^2 * (x + 0.5)^2 + rx^2 * (y - 1)^2 - rx^2 * ry^2

   While y > 0:
       y = y - 1
       dy = dy - 2 * rx^2
       if p2 > 0:
           p2 = p2 + rx^2 - dy
       else:
           x = x + 1
           dx = dx + 2 * ry^2
           p2 = p2 + dx - dy + rx^2
       Plot4Points(xc, yc, x, y)

3. End
```

---

## 4. Hand Calculation Example (Trace Table)

**Problem:** $r_x = 8, r_y = 6$.
* $r_x^2 = 64, r_y^2 = 36$.
* $2r_x^2 = 128, 2r_y^2 = 72$.
* Initial $p_{1_0} = 36 - 64(6) + 0.25(64) = 36 - 384 + 16 = -332$.

| Region | $x$ | $y$ | $dx = 2r_y^2 x$ | $dy = 2r_x^2 y$ | Decision $p$ | Chosen Point |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| 1 | 0 | 6 | 0 | 768 | -332 ($<0$) | **(0, 6)** |
| 1 | 1 | 6 | 72 | 768 | $-332 + 72 + 36 = -224$ | **(1, 6)** |
| 1 | 2 | 6 | 144 | 768 | $-224 + 144 + 36 = -44$ | **(2, 6)** |
| 1 | 3 | 6 | 216 | 768 | $-44 + 216 + 36 = 208$ | **(3, 6)** |
| 1 | 4 | 5 | 288 | 640 | $208 + 288 - 640 + 36 = -108$ | **(4, 5)** |
| 1 | 5 | 5 | 360 | 640 | $-108 + 360 + 36 = 288$ | **(5, 5)** |
| 1 | 6 | 4 | 432 | 512 | $288 + 432 - 512 + 36 = 244$ | **(6, 4)** |
| 1 | 7 | 3 | 504 | 384 | Switch to Region 2 ($dx \ge dy$) | **(7, 3)** |

---

## 5. Complete C++ OpenGL Code

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

float xc, yc, rx, ry;

void drawEllipsePoints(float xc, float yc, float x, float y) {
    glVertex2i((int)round(xc + x), (int)round(yc + y));
    glVertex2i((int)round(xc - x), (int)round(yc + y));
    glVertex2i((int)round(xc + x), (int)round(yc - y));
    glVertex2i((int)round(xc - x), (int)round(yc - y));
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glBegin(GL_POINTS);

    float x = 0;
    float y = ry;

    // --- REGION 1 ---
    float p1 = (ry * ry) - (rx * rx * ry) + (0.25f * rx * rx);
    float dx = 2.0f * ry * ry * x;
    float dy = 2.0f * rx * rx * y;

    drawEllipsePoints(xc, yc, x, y);

    while (dx < dy) {
        x++;
        dx += 2.0f * ry * ry;
        if (p1 < 0) {
            p1 += dx + (ry * ry);
        } else {
            y--;
            dy -= 2.0f * rx * rx;
            p1 += dx - dy + (ry * ry);
        }
        drawEllipsePoints(xc, yc, x, y);
    }

    // --- REGION 2 ---
    float p2 = (ry * ry) * ((x + 0.5f) * (x + 0.5f)) +
               (rx * rx) * ((y - 1.0f) * (y - 1.0f)) -
               (rx * rx * ry * ry);

    while (y > 0) {
        y--;
        dy -= 2.0f * rx * rx;
        if (p2 > 0) {
            p2 += (rx * rx) - dy;
        } else {
            x++;
            dx += 2.0f * ry * ry;
            p2 += dx - dy + (rx * rx);
        }
        drawEllipsePoints(xc, yc, x, y);
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
    printf("Enter center point (xc yc): ");
    scanf("%f %f", &xc, &yc);
    printf("Enter semi-major and semi-minor radii (rx ry): ");
    scanf("%f %f", &rx, &ry);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mid-Point Ellipse Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 6. Key Viva Questions & Clear Answers

1. **Why does an ellipse use 4-way symmetry instead of 8-way?**
   * *Answer:* Because an ellipse has different radii along $x$ and $y$ ($r_x \ne r_y$), so it is not symmetric across the diagonal line $y = x$.
2. **What is the condition to transition from Region 1 to Region 2?**
   * *Answer:* When $2r_y^2 x \ge 2r_x^2 y$, which is the exact point where the curve's slope reaches $-1$.
