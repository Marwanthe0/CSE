# Experiment 01: DDA Line Drawing Algorithm

> **Lab Final Headline:** *Draw a line using DDA line drawing algorithm.*

---

## 1. Introduction & Intuition (In Plain English)

* **What is DDA?** DDA stands for **Digital Differential Analyzer**.
* **Why do we need it?** In mathematics, a straight line is continuous and has infinite decimal points (like $y = 3.571$). But a computer monitor is made of a grid of tiny square pixels located at integer coordinates like $(3, 4)$ or $(4, 4)$. DDA calculates the exact mathematical point on the line and rounds it to the closest integer pixel on the screen.
* **Core Intuition:** If you walk along a straight line from $(x_1, y_1)$ to $(x_2, y_2)$, you find which direction has the longer distance ($x$ or $y$). You take $1$-step at a time along that longer direction and calculate the smaller fractional step in the other direction.

---

## 2. In-Depth Mathematical Derivation (Step-by-Step)

### Step 1: The Equation of a Straight Line
In school algebra, any straight line is written as:
$$y = m \cdot x + c$$
where:
* $\Delta x = x_2 - x_1$ (total horizontal change)
* $\Delta y = y_2 - y_1$ (total vertical change)
* $m = \frac{\Delta y}{\Delta x}$ (the slope, which measures how steep the line is)
* $c$ is the y-intercept (where the line crosses the y-axis).

---

### Step 2: The Differential (Rate of Change) Concept
In calculus, the derivative $\frac{dy}{dx} = m$ means:
$$dy = m \cdot dx$$
In discrete steps:
* A small step $\Delta x$ creates a vertical step: $\Delta y = m \cdot \Delta x$
* A small step $\Delta y$ creates a horizontal step: $\Delta x = \frac{\Delta y}{m}$

---

### Step 3: Deciding Total Steps to Avoid Gaps
If we only step along $x$, a steep vertical line would have big gaps. If we only step along $y$, a flat horizontal line would have big gaps.
Therefore, we find the longer distance:
$$\text{steps} = \max(|\Delta x|, |\Delta y|)$$

---

### Step 4: Finding the Increment Per Step
Now, divide the total change along both axes by the total number of steps:
$$\delta x = \frac{\Delta x}{\text{steps}}$$
$$\delta y = \frac{\Delta y}{\text{steps}}$$

#### Understanding the Two Cases:
1. **Case 1: Gentle Slope ($|m| \le 1$ where $|\Delta x| \ge |\Delta y|$):**
   * The line is more horizontal.
   * $\text{steps} = |\Delta x|$.
   * So, $\delta x = \pm 1$ (moves exactly 1 pixel left or right).
   * And $\delta y = \frac{\Delta y}{\Delta x} = m$ (adds slope $m$ to $y$ at each step).
   * **Formula:** $x_{k+1} = x_k \pm 1, \quad y_{k+1} = y_k + m$.

2. **Case 2: Steep Slope ($|m| > 1$ where $|\Delta y| > |\Delta x|$):**
   * The line is more vertical.
   * $\text{steps} = |\Delta y|$.
   * So, $\delta y = \pm 1$ (moves exactly 1 pixel up or down).
   * And $\delta x = \frac{\Delta x}{\Delta y} = \frac{1}{m}$ (adds $\frac{1}{m}$ to $x$ at each step).
   * **Formula:** $y_{k+1} = y_k \pm 1, \quad x_{k+1} = x_k + \frac{1}{m}$.

#### Plotting Rule:
Because pixel coordinates must be whole numbers, we round each coordinate:
$$\text{Pixel to Plot} = (\text{round}(x_k), \text{round}(y_k))$$

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm DDA_Line(x1, y1, x2, y2):
1. Compute total horizontal and vertical differences:
       dx = x2 - x1
       dy = y2 - y1

2. Determine total steps:
       if abs(dx) > abs(dy):
           steps = abs(dx)
       else:
           steps = abs(dy)
       if steps == 0:
           steps = 1

3. Compute coordinate change per step:
       x_inc = dx / steps
       y_inc = dy / steps

4. Set current point to starting position:
       x = x1
       y = y1

5. Plot the first pixel:
       plot_pixel(round(x), round(y))

6. Repeat for all steps (k = 1 to steps):
       x = x + x_inc
       y = y + y_inc
       plot_pixel(round(x), round(y))

7. End
```

---

## 4. Hand Calculation Example (Trace Table)

**Problem:** Draw a line from $(2, 3)$ to $(9, 7)$ using DDA.
* $\Delta x = 9 - 2 = 7$, $\Delta y = 7 - 3 = 4$.
* $\text{steps} = \max(|7|, |4|) = 7$.
* $\text{x\_inc} = \frac{7}{7} = 1.0$.
* $\text{y\_inc} = \frac{4}{7} \approx 0.571$.

| Step ($k$) | Exact $x$ | Exact $y$ | Plotted Pixel $(\text{round}(x), \text{round}(y))$ |
|:---:|:---:|:---:|:---:|
| 0 (Start) | 2.000 | 3.000 | **(2, 3)** |
| 1 | 3.000 | 3.571 | **(3, 4)** |
| 2 | 4.000 | 4.142 | **(4, 4)** |
| 3 | 5.000 | 4.713 | **(5, 5)** |
| 4 | 6.000 | 5.284 | **(6, 5)** |
| 5 | 7.000 | 5.855 | **(7, 6)** |
| 6 | 8.000 | 6.426 | **(8, 6)** |
| 7 (End) | 9.000 | 7.000 | **(9, 7)** |

---

## 5. Complete C++ OpenGL Code

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

float x1_pos, y1_pos, x2_pos, y2_pos;
int dx, dy;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_POINTS);

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    if (steps == 0) steps = 1;

    float currentX = x1_pos;
    float currentY = y1_pos;
    float xStep = (float)dx / steps;
    float yStep = (float)dy / steps;

    for (int k = 0; k <= steps; ++k) {
        glVertex2i((int)round(currentX), (int)round(currentY));
        currentX += xStep;
        currentY += yStep;
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
    printf("Enter first point (x1 y1): ");
    scanf("%f %f", &x1_pos, &y1_pos);
    printf("Enter second point (x2 y2): ");
    scanf("%f %f", &x2_pos, &y2_pos);

    dx = (int)(x2_pos - x1_pos);
    dy = (int)(y2_pos - y1_pos);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 6. Key Viva Questions & Clear Answers

1. **What is DDA?**
   * *Answer:* DDA stands for Digital Differential Analyzer. It is an incremental scan-conversion line drawing algorithm based on differential slope calculations.
2. **What is the major disadvantage of DDA?**
   * *Answer:* It relies on floating-point arithmetic and the `round()` function, which introduces cumulative round-off errors and runs slower on hardware without floating-point units.
3. **What is the time complexity of DDA?**
   * *Answer:* $O(N)$ where $N = \max(|\Delta x|, |\Delta y|)$.
