# Experiment 13: Draw a Line within a Rectangle (Cohen-Sutherland Line Clipping)

> **Lab Final Headline:** *Write a program to draw a line within a rectangle.*

---

## 1. Introduction & Intuition (In Plain English)

* **What is Line Clipping?** Given a line segment and a rectangular viewing box, we want to hide or cut away the parts of the line that stick outside the box and **draw only the visible part inside**.
* **How Cohen-Sutherland Makes It Super Fast:**
  * It divides the entire screen into **9 regions** around the rectangle.
  * Every point is given a 4-bit binary code called an **Outcode** ($\text{TBRL} = \text{Top, Bottom, Right, Left}$).
  * By simply doing bitwise operations (`AND` and `OR`), the computer can instantly know in 1 CPU cycle if the line is 100% inside or 100% outside, without doing any expensive division!

---

## 2. In-Depth Mathematical Theory & Derivation

### Step 1: The 4-Bit Outcodes (TBRL)
For any point $(x, y)$ against the window $x \in [x_{\min}, x_{\max}], \ y \in [y_{\min}, y_{\max}]$:
* **Bit 3 (Top):** Set to `1` if $y > y_{\max}$
* **Bit 2 (Bottom):** Set to `1` if $y < y_{\min}$
* **Bit 1 (Right):** Set to `1` if $x > x_{\max}$
* **Bit 0 (Left):** Set to `1` if $x < x_{\min}$

```text
  1001 (Top-Left)   |  1000 (Top)   |  1010 (Top-Right)
 -------------------+---------------+------------------- ymax
  0001 (Left)       |  0000 (INSIDE)|  0010 (Right)
 -------------------+---------------+------------------- ymin
  0101 (Bottom-Left)|  0100 (Bottom)|  0110 (Bottom-Right)
                   xmin            xmax
```

---

### Step 2: The 3 Bitwise Decision Rules
Let endpoints $P_1$ and $P_2$ have codes $\text{code}_1$ and $\text{code}_2$:

1. **Trivial Accept:**
   $$\text{code}_1 \mid \text{code}_2 == 0$$
   Both codes are `0000` $\implies$ The entire line is completely inside the rectangle! Draw immediately.
2. **Trivial Reject:**
   $$\text{code}_1 \ \& \ \text{code}_2 \ne 0$$
   Both endpoints share an outside bit (e.g. both are to the left of $x_{\min}$) $\implies$ The entire line is completely outside! Discard immediately.
3. **Clipping Required:**
   The line crosses a boundary edge. Pick the endpoint outside the window, calculate its intersection with the boundary, and repeat the test.

---

### Step 3: Intersection Formulas with Boundary Lines
Given slope $m = \frac{y_2 - y_1}{x_2 - x_1}$:

* **Crossing Top Edge ($y = y_{\max}$):**
  $$x = x_1 + (x_2 - x_1) \cdot \frac{y_{\max} - y_1}{y_2 - y_1}, \quad y = y_{\max}$$
* **Crossing Bottom Edge ($y = y_{\min}$):**
  $$x = x_1 + (x_2 - x_1) \cdot \frac{y_{\min} - y_1}{y_2 - y_1}, \quad y = y_{\min}$$
* **Crossing Right Edge ($x = x_{\max}$):**
  $$y = y_1 + (y_2 - y_1) \cdot \frac{x_{\max} - x_1}{x_2 - x_1}, \quad x = x_{\max}$$
* **Crossing Left Edge ($x = x_{\min}$):**
  $$y = y_1 + (y_2 - y_1) \cdot \frac{x_{\min} - x_1}{x_2 - x_1}, \quad x = x_{\min}$$

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm CohenSutherland_LineClip(x1, y1, x2, y2, xmin, ymin, xmax, ymax):
1. Compute outcodes for both endpoints: code1, code2
2. Loop indefinitely:
       if (code1 == 0) and (code2 == 0):
           Draw line from (x1, y1) to (x2, y2)
           Break (Accepted)

       else if (code1 & code2) != 0:
           Break (Rejected - Line is completely outside)

       else:
           Select outside point: codeOut = (code1 != 0) ? code1 : code2

           Find intersection (x, y) with the active boundary bit in codeOut:
               If TOP:    x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1), y = ymax
               If BOTTOM: x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1), y = ymin
               If RIGHT:  y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1), x = xmax
               If LEFT:   y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1), x = xmin

           Update the outside endpoint to the new intersection (x, y)
           Recompute its outcode
3. End
```

---

## 4. Hand Calculation Example (Trace Table)

**Window:** $x \in [150, 350], \ y \in [150, 350]$.
**Line:** $P_1(100, 100)$ to $P_2(400, 400)$.
* $\text{code}_1(100, 100) = \text{Bottom-Left} = 0101_2 = 5$.
* $\text{code}_2(400, 400) = \text{Top-Right} = 1010_2 = 10$.
* Bitwise AND: $5 \ \& \ 10 = 0$ (Not trivial reject).

#### Step 1: Clip $P_1$ against Bottom ($y = 150$)
* $x = 100 + (400 - 100) \cdot \frac{150 - 100}{400 - 100} = 150$.
* New $P_1 = (150, 150) \implies \text{code}_1 = 0000_2$.

#### Step 2: Clip $P_2$ against Top ($y = 350$)
* $x = 150 + (400 - 150) \cdot \frac{350 - 150}{400 - 150} = 350$.
* New $P_2 = (350, 350) \implies \text{code}_2 = 0000_2$.

#### Step 3: Test Codes
* $\text{code}_1 = 0000_2, \ \text{code}_2 = 0000_2 \implies \mathbf{\text{Trivial Accept!}}$
* **Resulting Visible Line Segment:** $(150, 150)$ to $(350, 350)$.

---

## 5. Complete C++ OpenGL Code

```cpp
#include <stdio.h>
#include <stdlib.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

const int INSIDE = 0; // 0000
const int LEFT   = 1; // 0001
const int RIGHT  = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP    = 8; // 1000

float xmin = 150.0f, ymin = 150.0f, xmax = 350.0f, ymax = 350.0f;
float origX1, origY1, origX2, origY2;
float clipX1, clipY1, clipX2, clipY2;
bool isLineAccepted = false;

int computeCode(float x, float y) {
    int code = INSIDE;
    if (x < xmin)      code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin)      code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    return code;
}

void cohenSutherlandClip(float x1, float y1, float x2, float y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int codeOut = (code1 != 0) ? code1 : code2;
            float x, y;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x; y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x; y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        clipX1 = x1; clipY1 = y1;
        clipX2 = x2; clipY2 = y2;
        isLineAccepted = true;
    } else {
        isLineAccepted = false;
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Rectangle (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin); glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax); glVertex2f(xmin, ymax);
    glEnd();

    // 2. Original Line (Gray)
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(origX1, origY1); glVertex2f(origX2, origY2);
    glEnd();

    // 3. Clipped Line Inside Rectangle (Green)
    if (isLineAccepted) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(clipX1, clipY1);
        glVertex2f(clipX2, clipY2);
        glEnd();
    }

    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    printf("Enter rectangle window (xmin ymin xmax ymax): ");
    scanf("%f %f %f %f", &xmin, &ymin, &xmax, &ymax);

    printf("Enter line endpoints (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &origX1, &origY1, &origX2, &origY2);

    cohenSutherlandClip(origX1, origY1, origX2, origY2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line within Rectangle - Cohen-Sutherland");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 6. Key Viva Questions & Clear Answers

1. **What is the significance of the Outcode `0000`?**
   * *Answer:* It means the point lies strictly inside the rectangular viewing window.
2. **How does bitwise `AND` determine trivial rejection?**
   * *Answer:* If `code1 & code2 != 0`, both endpoints share an external region (e.g. both are above the top edge), so the entire line is guaranteed to be outside.
