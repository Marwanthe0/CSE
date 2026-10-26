# Experiment 07: Flood-Fill Algorithm

> **Lab Final Headline:** *Fill an area with a selected color using the Flood-Fill Algorithm.*

---

## 1. Introduction & Intuition (In Plain English)

* **What is Flood-Fill?** Think of the "Paint Bucket" tool in MS Paint or Photoshop. When you click on a blue region with yellow selected, it repaints everything that was *previously blue* into *yellow*.
* **How is it different from Boundary-Fill?**
  * Boundary-Fill looks for a specific **outer wall color** ($C_{\text{boundary}}$).
  * Flood-Fill looks for a specific **old interior color** ($C_{\text{old}}$) and replaces it with $C_{\text{new}}$, without caring what color the boundary walls are.

---

## 2. In-Depth Mathematical Theory & Logic

### 2.1 The Color Replacement Mapping
Let:
* $C(x, y)$ = Current pixel color on screen.
* $C_{\text{old}}$ = Target color to be replaced (e.g. Black background).
* $C_{\text{new}}$ = Replacement fill color (e.g. Yellow).

The algorithm fills pixel $(x, y)$ if and only if:
$$\mathbf{C(x, y) == C_{\text{old}}}$$

---

### 2.2 Boundary-Fill vs. Flood-Fill Comparison

| Property | Boundary-Fill | Flood-Fill |
|---|---|---|
| **Fill Test** | `pixel != boundaryColor && pixel != fillColor` | `pixel == oldColor` |
| **Boundary Requirement** | Single uniform boundary color required | Works with multi-colored or implicit boundaries |
| **Interior Requirement** | Interior can have multiple colors | Interior must originally be one single color |
| **Real-world Equivalent** | Coloring inside a line drawing | Paint Bucket tool (color replacement) |

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm FloodFill4(x, y, new_color, old_color):
1. Read color at current pixel (x, y):
       current = getPixelColor(x, y)

2. Check if pixel has old color:
       if (current == old_color):
           // 1. Repaint current pixel
           setPixelColor(x, y, new_color)

           // 2. Recursively check and paint 4 neighbors
           FloodFill4(x + 1, y,     new_color, old_color) // Right
           FloodFill4(x - 1, y,     new_color, old_color) // Left
           FloodFill4(x,     y + 1, new_color, old_color) // Top
           FloodFill4(x,     y - 1, new_color, old_color) // Bottom

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

float oldColor[3] = {0.0f, 0.0f, 0.0f};      // Target interior color (Black)
float fillColor[3] = {1.0f, 1.0f, 0.0f};     // New fill color (Yellow)
float boundaryColor[3] = {1.0f, 1.0f, 1.0f}; // White boundary

bool isSameColor(float c1[3], float c2[3]) {
    return (fabs(c1[0] - c2[0]) < 0.05f &&
            fabs(c1[1] - c2[1]) < 0.05f &&
            fabs(c1[2] - c2[2]) < 0.05f);
}

void floodFill4(int x, int y, float fillCol[3], float oldCol[3]) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    if (isSameColor(currentColor, oldCol)) {
        glColor3fv(fillCol);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        floodFill4(x + 1, y, fillCol, oldCol);
        floodFill4(x - 1, y, fillCol, oldCol);
        floodFill4(x, y + 1, fillCol, oldCol);
        floodFill4(x, y - 1, fillCol, oldCol);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw polygon boundary (White)
    glColor3fv(boundaryColor);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 150);
    glVertex2i(350, 150);
    glVertex2i(350, 350);
    glVertex2i(150, 350);
    glEnd();
    glFlush();

    // Flood fill the black interior with yellow
    floodFill4(250, 250, fillColor, oldColor);
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
    glutCreateWindow("Flood-Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 5. Key Viva Questions & Clear Answers

1. **What happens if `oldColor` and `fillColor` are identical?**
   * *Answer:* The program will enter an infinite recursion loop and crash (stack overflow) because `currentColor == oldColor` will always be true.
2. **Can Flood-Fill handle multi-colored boundaries?**
   * *Answer:* Yes, because Flood-Fill only checks if the current pixel matches `oldColor`.
