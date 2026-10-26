# Experiment 04: Draw a Circle Using a Single Point (Polar Method)

> **Lab Final Headline:** *Draw a circle using a single point.*

---

## 1. Introduction & Intuition (In Plain English)

* **What does "Single Point" mean?** 
  * In the Mid-Point circle algorithm, we calculated 1 point and used 8-way symmetry to plot 8 points at once.
  * In the **Single Point (Polar) Method**, we plot each point along the circumference sequentially, **one by one**, by rotating an angle $\theta$ from $0^\circ$ all the way to $360^\circ$ ($2\pi$ radians).
* **The Core Intuition:** Imagine a clock hand of length $r$ pinned at center $(x_c, y_c)$. As the tip of the hand sweeps around in a complete circle, its tip traces out $(x_c + r\cos\theta, y_c + r\sin\theta)$. We plot each position of that tip.

---

## 2. In-Depth Mathematical Derivation (Step-by-Step)

### Step 1: Converting Cartesian to Polar Coordinates
The standard equation of a circle in Cartesian $(x, y)$ coordinates is:
$$(x - x_c)^2 + (y - y_c)^2 = r^2$$

Using basic trigonometry from a right triangle:
$$\cos(\theta) = \frac{\text{adjacent}}{\text{hypotenuse}} = \frac{x - x_c}{r} \implies \mathbf{x(\theta) = x_c + r \cdot \cos(\theta)}$$
$$\sin(\theta) = \frac{\text{opposite}}{\text{hypotenuse}} = \frac{y - y_c}{r} \implies \mathbf{y(\theta) = y_c + r \cdot \sin(\theta)}$$

where angle $\theta$ goes from $0$ to $2\pi$ radians ($0^\circ \le \theta < 360^\circ$).

---

### Step 2: Choosing the Angle Step Size ($\Delta\theta$)
* If $\Delta\theta$ is too large (e.g. $\Delta\theta = 0.5$ radians), the plotted pixels will be far apart with big empty gaps.
* The arc length distance between two consecutive points is $\Delta s = r \cdot \Delta\theta$.
* To guarantee that pixels touch each other without gaps on screen, we need $\Delta s \le 1$ pixel:
  $$r \cdot \Delta\theta \le 1 \implies \Delta\theta \le \frac{1}{r}$$
* For example, if radius $r = 100$, we choose $\Delta\theta \le \frac{1}{100} = 0.01$. Using $\Delta\theta = 0.001$ ensures a completely continuous, gap-free circle.

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm Single_Point_Circle(xc, yc, r):
1. Define step size and full rotation:
       dTheta = 0.001
       twoPi = 2 * 3.14159265

2. Set initial angle:
       theta = 0.0

3. Loop from 0 to 2*PI:
       while theta < twoPi:
           x = xc + r * cos(theta)
           y = yc + r * sin(theta)
           plot_pixel(round(x), round(y))
           theta = theta + dTheta

4. End
```

---

## 4. Hand Calculation Example (Trace Table)

**Problem:** Center $(x_c, y_c) = (200, 200)$, Radius $r = 50$.
* Formulas: $x = 200 + 50\cos(\theta)$, $y = 200 + 50\sin(\theta)$.

| Angle $\theta$ (Degrees) | Angle $\theta$ (Radians) | $\cos(\theta)$ | $\sin(\theta)$ | Exact Coordinates | Plotted Pixel |
|:---:|:---:|:---:|:---:|:---:|:---:|
| $0^\circ$ | 0.000 | 1.000 | 0.000 | $(250.0, 200.0)$ | **(250, 200)** |
| $30^\circ$ | 0.524 | 0.866 | 0.500 | $(243.3, 225.0)$ | **(243, 225)** |
| $45^\circ$ | 0.785 | 0.707 | 0.707 | $(235.4, 235.4)$ | **(235, 235)** |
| $90^\circ$ | 1.571 | 0.000 | 1.000 | $(200.0, 250.0)$ | **(200, 250)** |
| $180^\circ$ | 3.142 | -1.000 | 0.000 | $(150.0, 200.0)$ | **(150, 200)** |
| $270^\circ$ | 4.712 | 0.000 | -1.000 | $(200.0, 150.0)$ | **(200, 150)** |
| $360^\circ$ | 6.283 | 1.000 | 0.000 | $(250.0, 200.0)$ | **(250, 200)** |

---

## 5. Complete C++ OpenGL Code

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#define PI 3.14159265358979323846

float xc, yc, r;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glBegin(GL_POINTS);

    // Plotting each single point along the circle circumference
    for (float theta = 0.0f; theta < 2.0f * PI; theta += 0.001f) {
        float x = xc + r * cos(theta);
        float y = yc + r * sin(theta);
        glVertex2i((int)round(x), (int)round(y));
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
    printf("Enter radius (r): ");
    scanf("%f", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Draw Circle Using Single Point Method");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 6. Key Viva Questions & Clear Answers

1. **Why is the direct equation $y = y_c \pm \sqrt{r^2 - (x - x_c)^2}$ not used?**
   * *Answer:* Because evaluating square roots is very slow, and near the horizontal edges where the slope approaches infinity, big vertical gaps appear between plotted points.
2. **What is the difference between Midpoint Circle and Single Point Circle?**
   * *Answer:* Midpoint Circle uses integer arithmetic and 8-way symmetry (fastest). Single Point Circle uses trigonometric polar coordinates and calculates all $360^\circ$ points individually.
