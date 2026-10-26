# Experiment 12: Rectangle/Polygon Clipping (Sutherland-Hodgman)

> **Lab Final Headline:** *Write a program to clip a rectangle.*

---

## 1. Introduction & Intuition (In Plain English)

* **What is Polygon Clipping?** Imagine taking a pair of scissors and cutting away any part of a polygon that lies outside a rectangular viewing window $(x_{\min}, y_{\min}, x_{\max}, y_{\max})$. The result must be a new, closed polygon.
* **How Sutherland-Hodgman Works:**
  It treats the 4 edges of the clipping window like 4 separate scissors:
  1. **Stage 1:** Cut the polygon against the **Left** boundary line.
  2. **Stage 2:** Cut the resulting polygon against the **Right** boundary line.
  3. **Stage 3:** Cut the resulting polygon against the **Bottom** boundary line.
  4. **Stage 4:** Cut the resulting polygon against the **Top** boundary line.

---

## 2. In-Depth Mathematical Derivation (Step-by-Step)

### Step 1: The 4 Inside Tests
For any point $(x, y)$:
* **Inside Left Edge:** $x \ge x_{\min}$
* **Inside Right Edge:** $x \le x_{\max}$
* **Inside Bottom Edge:** $y \ge y_{\min}$
* **Inside Top Edge:** $y \le y_{\max}$

---

### Step 2: Line Intersection Mathematics
For an edge connecting $P_1(x_1, y_1)$ to $P_2(x_2, y_2)$:

#### 1. Intersection with a Vertical Line ($x = x_{\text{clip}}$):
$$\mathbf{y_{\text{intersect}} = y_1 + (x_{\text{clip}} - x_1) \cdot \frac{y_2 - y_1}{x_2 - x_1}}$$

#### 2. Intersection with a Horizontal Line ($y = y_{\text{clip}}$):
$$\mathbf{x_{\text{intersect}} = x_1 + (y_{\text{clip}} - y_1) \cdot \frac{x_2 - x_1}{y_2 - y_1}}$$

---

### Step 3: The 4 Transition Cases for Every Edge ($P_1 \to P_2$)

| Case | What Happens? | Visual Meaning | Output Sent to Next Stage |
|:---:|:---:|:---:|:---:|
| **Case 1** | $\text{In} \to \text{In}$ | Edge is fully inside | Output destination **$P_2$** |
| **Case 2** | $\text{In} \to \text{Out}$ | Edge is exiting outside | Output intersection point **$I$** |
| **Case 3** | $\text{Out} \to \text{Out}$ | Edge is fully outside | Output **Nothing ($\emptyset$)** |
| **Case 4** | $\text{Out} \to \text{In}$ | Edge is entering inside | Output intersection **$I$**, then **$P_2$** |

---

## 3. Step-by-Step Algorithm (Easy to Memorize)

```text
Algorithm Sutherland_Hodgman_Clip(polygon, xmin, ymin, xmax, ymax):
1. Input list of polygon vertices: V = [P0, P1, ..., Pn-1]

2. Clip against LEFT boundary (x = xmin):
       For each edge P1 -> P2 in V:
           if (P1 inside) and (P2 inside): Output P2
           if (P1 inside) and (P2 outside): Output Intersection(P1, P2, xmin)
           if (P1 outside) and (P2 inside): Output Intersection(P1, P2, xmin), then Output P2
           if (P1 outside) and (P2 outside): Do nothing
       Store output as V_left

3. Clip V_left against RIGHT boundary (x = xmax) -> V_right
4. Clip V_right against BOTTOM boundary (y = ymin) -> V_bottom
5. Clip V_bottom against TOP boundary (y = ymax) -> V_clipped

6. Return V_clipped
```

---

## 4. Hand Calculation Example (Trace Table)

**Window:** $x \in [100, 300], \ y \in [100, 300]$.
**Subject Polygon:** $P_0(50, 150), P_1(250, 150), P_2(250, 350), P_3(50, 350)$.

#### Stage 1: Left Clipper ($x \ge 100$):
* Edge $P_0(50, 150) \to P_1(250, 150)$: Out $\to$ In. Intersection $I_1(100, 150)$. Outputs: $I_1(100, 150), P_1(250, 150)$.
* Edge $P_1(250, 150) \to P_2(250, 350)$: In $\to$ In. Outputs: $P_2(250, 350)$.
* Edge $P_2(250, 350) \to P_3(50, 350)$: In $\to$ Out. Intersection $I_2(100, 350)$. Outputs: $I_2(100, 350)$.
* Edge $P_3(50, 350) \to P_0(50, 150)$: Out $\to$ Out. Outputs: None.
* **Output of Left Clip:** $[(100, 150), (250, 150), (250, 350), (100, 350)]$.

---

## 5. Complete C++ OpenGL Code

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

struct Point { float x, y; };

float xmin = 150.0f, ymin = 150.0f, xmax = 350.0f, ymax = 350.0f;
std::vector<Point> originalRect;
std::vector<Point> clippedRect;

std::vector<Point> clipLeft(const std::vector<Point>& poly, float xmin) {
    std::vector<Point> out;
    int n = poly.size();
    if (n == 0) return out;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i], p2 = poly[(i + 1) % n];
        bool in1 = (p1.x >= xmin), in2 = (p2.x >= xmin);
        if (in1 && in2) out.push_back(p2);
        else if (in1 && !in2) {
            float y = p1.y + (xmin - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            out.push_back({xmin, y});
        } else if (!in1 && in2) {
            float y = p1.y + (xmin - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            out.push_back({xmin, y});
            out.push_back(p2);
        }
    }
    return out;
}

std::vector<Point> clipRight(const std::vector<Point>& poly, float xmax) {
    std::vector<Point> out;
    int n = poly.size();
    if (n == 0) return out;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i], p2 = poly[(i + 1) % n];
        bool in1 = (p1.x <= xmax), in2 = (p2.x <= xmax);
        if (in1 && in2) out.push_back(p2);
        else if (in1 && !in2) {
            float y = p1.y + (xmax - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            out.push_back({xmax, y});
        } else if (!in1 && in2) {
            float y = p1.y + (xmax - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            out.push_back({xmax, y});
            out.push_back(p2);
        }
    }
    return out;
}

std::vector<Point> clipBottom(const std::vector<Point>& poly, float ymin) {
    std::vector<Point> out;
    int n = poly.size();
    if (n == 0) return out;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i], p2 = poly[(i + 1) % n];
        bool in1 = (p1.y >= ymin), in2 = (p2.y >= ymin);
        if (in1 && in2) out.push_back(p2);
        else if (in1 && !in2) {
            float x = p1.x + (ymin - p1.y) * (p2.x - p1.x) / (p2.x - p1.x);
            out.push_back({x, ymin});
        } else if (!in1 && in2) {
            float x = p1.x + (ymin - p1.y) * (p2.x - p1.x) / (p2.x - p1.x);
            out.push_back({x, ymin});
            out.push_back(p2);
        }
    }
    return out;
}

std::vector<Point> clipTop(const std::vector<Point>& poly, float ymax) {
    std::vector<Point> out;
    int n = poly.size();
    if (n == 0) return out;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i], p2 = poly[(i + 1) % n];
        bool in1 = (p1.y <= ymax), in2 = (p2.y <= ymax);
        if (in1 && in2) out.push_back(p2);
        else if (in1 && !in2) {
            float x = p1.x + (ymax - p1.y) * (p2.x - p1.x) / (p2.x - p1.x);
            out.push_back({x, ymax});
        } else if (!in1 && in2) {
            float x = p1.x + (ymax - p1.y) * (p2.x - p1.x) / (p2.x - p1.x);
            out.push_back({x, ymax});
            out.push_back(p2);
        }
    }
    return out;
}

void sutherlandHodgmanClip() {
    clippedRect = originalRect;
    clippedRect = clipLeft(clippedRect, xmin);
    clippedRect = clipRight(clippedRect, xmax);
    clippedRect = clipBottom(clippedRect, ymin);
    clippedRect = clipTop(clippedRect, ymax);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Clipping Window (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin); glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax); glVertex2f(xmin, ymax);
    glEnd();

    // 2. Original Rectangle (Gray)
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (size_t i = 0; i < originalRect.size(); i++)
        glVertex2f(originalRect[i].x, originalRect[i].y);
    glEnd();

    // 3. Clipped Rectangle (Green)
    if (!clippedRect.empty()) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        for (size_t i = 0; i < clippedRect.size(); i++)
            glVertex2f(clippedRect[i].x, clippedRect[i].y);
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
    printf("Enter clipping window (xmin ymin xmax ymax): ");
    scanf("%f %f %f %f", &xmin, &ymin, &xmax, &ymax);

    float rx1, ry1, rx2, ry2;
    printf("Enter subject rectangle corners (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &rx1, &ry1, &rx2, &ry2);

    originalRect.push_back({rx1, ry1});
    originalRect.push_back({rx2, ry1});
    originalRect.push_back({rx2, ry2});
    originalRect.push_back({rx1, ry2});

    sutherlandHodgmanClip();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rectangle Clipping - Sutherland-Hodgman");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

---

## 6. Key Viva Questions & Clear Answers

1. **Why does Sutherland-Hodgman require a convex clipping window?**
   * *Answer:* For concave windows, clipping a single polygon can break it into multiple separate pieces, which Sutherland-Hodgman connects incorrectly with extra lines.
2. **What is the time complexity?**
   * *Answer:* $O(N)$ where $N$ is the number of polygon vertices.
