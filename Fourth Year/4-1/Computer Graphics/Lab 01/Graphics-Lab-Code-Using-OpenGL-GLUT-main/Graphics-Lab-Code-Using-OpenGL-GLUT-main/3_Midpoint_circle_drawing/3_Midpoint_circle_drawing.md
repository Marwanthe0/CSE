# Experiment 03: Mid-Point Circle Drawing Algorithm

> **Lab Final Headline:** *Draw a circle using mid-point circle drawing algorithm.*

---

## 1. Introduction & Intuition (In Plain English)

* **What does this algorithm do?** It draws a circle of radius $r$ centered at $(x_c, y_c)$ using **pure integer arithmetic** (no decimals, no square roots, no trigonometry).
* **The 8-Way Symmetry Trick:** A circle is perfectly symmetric. If you calculate the points for just one slice (one-eighth or $45^\circ$ of the circle), you can get all other 7 slices for free by simply swapping and negating the $x$ and $y$ coordinates!
* **The Midpoint Decision Idea:** Suppose you are drawing the top arc starting from $(0, r)$. Moving to the right ($x+1$), the curve goes slightly downwards. So your next pixel must be either:
  1. The **East ($E$)** pixel: $(x+1, y)$ [stay at the same height]
  2. The **South-East ($SE$)** pixel: $(x+1, y-1)$ [step 1 pixel down]
  
  To decide which pixel is closer to the true circle, we check the **midpoint** between them: $\left(x+1, y - \frac{1}{2}\right)$. If the midpoint is inside the circle, the true curve is closer to the upper pixel $E$. If the midpoint is outside, the curve is closer to the lower pixel $SE$.

---

## 2. In-Depth Mathematical Derivation (Step-by-Step)

### Step 1: The Circle Function
The equation of a circle centered at origin $(0, 0)$ with radius $r$ is:
$$f_{\text{circle}}(x, y) = x^2 + y^2 - r^2$$

Evaluating this function gives:
* $f(x, y) < 0 \implies$ The point is **inside** the circle.
* $f(x, y) = 0 \implies$ The point is **exactly on** the circle boundary.
* $f(x, y) > 0 \implies$ The point is **outside** the circle.

---

### Step 2: Evaluating the Midpoint ($p_k$)
At current pixel $(x_k, y_k)$, the midpoint between $E(x_k+1, y_k)$ and $SE(x_k+1, y_k-1)$ is:
$$M = \left(x_k + 1, y_k - \frac{1}{2}\right)$$

We define our **decision parameter** $p_k$ by plugging this midpoint into the circle equation:
$$p_k = f_{\text{circle}}\left(x_k + 1, y_k - \frac{1}{2}\right) = (x_k + 1)^2 + \left(y_k - \frac{1}{2}\right)^2 - r^2$$

* **If $p_k < 0$:** Midpoint is inside the circle $\implies$ Upper pixel $E$ is closer. Choose $\mathbf{y_{k+1} = y_k}$.
* **If $p_k \ge 0$:** Midpoint is outside/on the circle $\implies$ Lower pixel $SE$ is closer. Choose $\mathbf{y_{k+1} = y_k - 1}$.

---

### Step 3: Finding the Next Decision Parameter ($p_{k+1}$)
At the next step:
$$p_{k+1} = f_{\text{circle}}\left(x_{k+1} + 1, y_{k+1} - \frac{1}{2}\right) = (x_{k+1} + 1)^2 + \left(y_{k+1} - \frac{1}{2}\right)^2 - r^2$$

Subtracting $p_k$ from $p_{k+1}$:
$$p_{k+1} - p_k = \left[(x_{k+1} + 1)^2 - (x_k + 1)^2\right] + \left[\left(y_{k+1} - \frac{1}{2}\right)^2 - \left(y_k - \frac{1}{2}\right)^2\right]$$

Since $x_{k+1} = x_k + 1$:
$$(x_{k+1} + 1)^2 - (x_k + 1)^2 = (x_k + 2)^2 - (x_k + 1)^2 = 2x_k + 3 = 2(x_k + 1) + 1 = 2x_{k+1} + 1$$

Therefore:
$$p_{k+1} = p_k + 2x_{k+1} + 1 + (y_{k+1}^2 - y_k^2) - (y_{k+1} - y_k)$$

* **Case 1: If $p_k < 0$** (we chose $y_{k+1} = y_k$):
  $$\mathbf{p_{k+1} = p_k + 2x_{k+1} + 1}$$
* **Case 2: If $p_k \ge 0$** (we chose $y_{k+1} = y_k - 1$):
  $$\mathbf{p_{k+1} = p_k + 2(x_{k+1} - y_{k+1}) + 1}$$

---

### Step 4: Initial Decision Parameter ($p_0$)
We start at the topmost point of the circle: $(x_0, y_0) = (0, r)$.
$$p_0 = f_{\text{circle}}\left(1, r - \frac{1}{2}\right) = (1)^2 + \left(r - \frac{1}{2}\right)^2 - r^2$$
$$p_0 = 1 + r^2 - r + \frac{1}{4} - r^2 = \frac{5}{4} - r$$

Since radius $r$ is an integer, $\frac{5}{4} - r = 1.25 - r$. Since $p_k$ is only tested against $0$ in integer steps, rounding $1.25$ down to $1$ gives identical decision steps:
$$\mathbf{p_0 = 1 - r}$$

---

### Step 5: Eight-Way Symmetry Formulas
For each point $(x, y)$ calculated in the first octant, plot these 8 points centered at $(x_c, y_c)$:
1. $(x_c + x, y_c + y)$
2. $(x_c - x, y_c + y)$
3. $(x_c + x, y_c - y)$
4. $(x_c - x, y_c - y)$
5. $(x_c + y, y_c + x)$
6. $(x_c - y, y_c + x)$
7. $(x_c + y, y_c - x)$
8. $(x_c - y, y_c - x)$

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm Midpoint_Circle(xc, yc, r):
1. Start at top point:
       x = 0
       y = r

2. Calculate initial parameter:
       p = 1 - r

3. Plot the 8 symmetric points:
       Plot8Points(xc, yc, x, y)

4. While x < y (until the 45-degree line is reached):
       x = x + 1
       if p < 0:
           p = p + 2 * x + 1
       else:
           y = y - 1
           p = p + 2 * (x - y) + 1
       Plot8Points(xc, yc, x, y)

5. End
```

---

## 4. Hand Calculation Example (Trace Table)

**Problem:** Draw a circle with center $(0, 0)$ and radius $r = 10$.
* Initial values: $x = 0, \ y = 10, \ p_0 = 1 - 10 = -9$.

| Step | $x$ | $y$ | Current $p_k$ | Condition | New $p_{k+1}$ | 8 Symmetric Points Plotted |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **0 (Start)** | 0 | 10 | -9 | Initial | — | $(\pm 0, \pm 10), (\pm 10, \pm 0)$ |
| **1** | 1 | 10 | -9 | $p < 0 \implies y=10$ | $-9 + 2(1) + 1 = -6$ | $(\pm 1, \pm 10), (\pm 10, \pm 1)$ |
| **2** | 2 | 10 | -6 | $p < 0 \implies y=10$ | $-6 + 2(2) + 1 = -1$ | $(\pm 2, \pm 10), (\pm 10, \pm 2)$ |
| **3** | 3 | 10 | -1 | $p < 0 \implies y=10$ | $-1 + 2(3) + 1 = 6$ | $(\pm 3, \pm 10), (\pm 10, \pm 3)$ |
| **4** | 4 | 9 | 6 | $p \ge 0 \implies y=9$ | $6 + 2(4 - 9) + 1 = -3$ | $(\pm 4, \pm 9), (\pm 9, \pm 4)$ |
| **5** | 5 | 9 | -3 | $p < 0 \implies y=9$ | $-3 + 2(5) + 1 = 8$ | $(\pm 5, \pm 9), (\pm 9, \pm 5)$ |
| **6** | 6 | 8 | 8 | $p \ge 0 \implies y=8$ | $8 + 2(6 - 8) + 1 = 5$ | $(\pm 6, \pm 8), (\pm 8, \pm 6)$ |
| **7** | 7 | 7 | 5 | $p \ge 0 \implies y=7$ | $5 + 2(7 - 7) + 1 = 6$ | $(\pm 7, \pm 7)$ |
| **End** | 8 | 7 | Stop ($x > y$) | First Octant Complete! | — | Entire circle drawn |

---

## 5. Complete C++ OpenGL Code

```cpp
#include <stdio.h>
#include <stdlib.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

int xc, yc, r;

void drawCirclePoints(int xc, int yc, int x, int y) {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glBegin(GL_POINTS);

    int x = 0;
    int y = r;
    int p = 1 - r;

    drawCirclePoints(xc, yc, x, y);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        drawCirclePoints(xc, yc, x, y);
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
    scanf("%d %d", &xc, &yc);
    printf("Enter radius (r): ");
    scanf("%d", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mid-Point Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 6. Key Viva Questions & Clear Answers

1. **Why does the algorithm stop when $x > y$?**
   * *Answer:* Because at $x = y$, we have completed the $45^\circ$ octant. All other 7 octants are automatically drawn by the 8-way symmetry reflections.
2. **What is the initial decision parameter for Mid-Point Circle?**
   * *Answer:* $p_0 = 1 - r$ (derived from $\frac{5}{4} - r$).
3. **What is the time complexity?**
   * *Answer:* $O(r)$ iterations.
