# Experiment 06: Boundary-Fill Algorithm

> **Lab Final Headline:** *Fill an area with a selected color using the boundary-fill algorithm.*

---

## 1. Introduction & Intuition (In Plain English)

* **What is Boundary-Fill?** It is an area-filling algorithm that paints the inside of a closed boundary (like a rectangle or polygon) with a new color.
* **How does it work?** 
  * You drop a "seed" point inside the shape.
  * The algorithm looks at the pixel you clicked on.
  * If the pixel is **not already filled** and is **not the boundary edge**, it colors that pixel.
  * Then it automatically calls itself to color its 4 surrounding neighbors (Right, Left, Up, Down).
  * This spreads like spilled paint until it hits the boundary color everywhere and stops!

---

## 2. In-Depth Mathematical Theory & Logic

### 2.1 The Fill Condition (The Predicate)
Let:
* $C(x, y)$ = Current color of the pixel at coordinate $(x, y)$.
* $C_{\text{boundary}}$ = The fixed color of the shape's boundary lines.
* $C_{\text{fill}}$ = The new color we want to paint inside the shape.

The algorithm fills pixel $(x, y)$ if and only if:
$$\mathbf{(C(x, y) \ne C_{\text{boundary}}) \quad \text{AND} \quad (C(x, y) \ne C_{\text{fill}})}$$

---

### 2.2 4-Connected vs. 8-Connected Filling
* **4-Connected Filling:** Visits the 4 orthogonal neighbors:
  $$N_4(x, y) = \{(x+1, y), (x-1, y), (x, y+1), (x, y-1)\}$$
* **8-Connected Filling:** Visits all 8 neighbors (including 4 diagonals):
  $$N_8(x, y) = N_4(x, y) \cup \{(x+1, y+1), (x-1, y+1), (x+1, y-1), (x-1, y-1)\}$$

> **Important Rule:** If the boundary contains diagonal single-pixel connections, an 8-connected fill algorithm will leak through the corners to the outside! A 4-connected fill stays safely inside.

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm BoundaryFill4(x, y, fill_color, boundary_color):
1. Read current color of pixel (x, y):
       current = getPixelColor(x, y)

2. Check if pixel needs coloring:
       if (current != boundary_color) and (current != fill_color):
           // 1. Paint current pixel
           setPixelColor(x, y, fill_color)

           // 2. Recursively paint 4 neighbors
           BoundaryFill4(x + 1, y,     fill_color, boundary_color) // Right
           BoundaryFill4(x - 1, y,     fill_color, boundary_color) // Left
           BoundaryFill4(x,     y + 1, fill_color, boundary_color) // Top
           BoundaryFill4(x,     y - 1, fill_color, boundary_color) // Bottom

3. Return
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

float boundaryColor[3] = {1.0f, 0.0f, 0.0f}; // Red Boundary
float fillColor[3] = {0.0f, 1.0f, 1.0f};     // Cyan Fill

bool isSameColor(float c1[3], float c2[3]) {
    return (fabs(c1[0] - c2[0]) < 0.05f &&
            fabs(c1[1] - c2[1]) < 0.05f &&
            fabs(c1[2] - c2[2]) < 0.05f);
}

void boundaryFill4(int x, int y, float fillCol[3], float boundCol[3]) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    if (!isSameColor(currentColor, boundCol) && !isSameColor(currentColor, fillCol)) {
        glColor3fv(fillCol);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        boundaryFill4(x + 1, y, fillCol, boundCol);
        boundaryFill4(x - 1, y, fillCol, boundCol);
        boundaryFill4(x, y + 1, fillCol, boundCol);
        boundaryFill4(x, y - 1, fillCol, boundCol);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw red polygon boundary
    glColor3fv(boundaryColor);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 150);
    glVertex2i(350, 150);
    glVertex2i(350, 350);
    glVertex2i(150, 350);
    glEnd();
    glFlush();

    // Fill from seed point (250, 250)
    boundaryFill4(250, 250, fillColor, boundaryColor);
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Boundary-Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 5. Key Viva Questions & Clear Answers

1. **What is the limitation of Boundary-Fill?**
   * *Answer:* It requires the boundary to have a single, uniform color. If the boundary has multiple colors, the fill will overwrite the different colors and leak out.
2. **What causes a stack overflow in recursive boundary fill?**
   * *Answer:* Large shapes require thousands of recursive function calls on the system call stack.
