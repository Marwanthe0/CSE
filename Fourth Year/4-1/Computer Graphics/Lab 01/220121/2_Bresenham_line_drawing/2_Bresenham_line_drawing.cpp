#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

int x1_val, y1_val, x2_val, y2_val;

void bresenhamLine(int x1, int y1, int x2, int y2) {
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int twoDy = 2 * dy;
  int twoDyMinusTwoDx = 2 * (dy - dx);

  int p = 2 * dy - dx;

  int x = x1;
  int y = y1;
  int y_step = (y2 >= y1) ? 1 : -1;

  glVertex2i(x, y);

  while (x < x2) {
    x++;
    if (p < 0) {
      p += twoDy;
    } else {
      y += y_step;
      p += twoDyMinusTwoDx;
    }
    glVertex2i(x, y);
  }
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0f, 1.0f, 0.0f);
  glPointSize(2.0f);
  glBegin(GL_POINTS);

  int x1 = x1_val;
  int y1 = y1_val;
  int x2 = x2_val;
  int y2 = y2_val;

  if (x1 > x2) {
    int tempX = x1;
    x1 = x2;
    x2 = tempX;
    int tempY = y1;
    y1 = y2;
    y2 = tempY;
  }

  bresenhamLine(x1, y1, x2, y2);

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
  scanf("%d %d", &x1_val, &y1_val);
  printf("Enter second point (x2 y2): ");
  scanf("%d %d", &x2_val, &y2_val);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Bresenham Line Drawing Algorithm");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
