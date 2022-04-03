#include "DrawModule.h"
#include <iostream>

void extra::drawCircle(Image &img, Point center, int radius,
                       unsigned char color) {
  for (int x = -radius; x <= +radius; x++) {
    for (int y = -radius; y <= +radius; y++)
      if (x * x + y * y <= radius * radius) {
        unsigned char &c = img.at(center.x + x, center.y + y);
        c = color;
      }
  }
}
void extra::drawLine(Image &img, Point p1, Point p2, unsigned char color) {
  float step;
  float dx = (p2.x - p1.x);
  float dy = (p2.y - p1.y);
  if (abs(dx) >= abs(dy))
    step = abs(dx);
  else
    step = abs(dy);
  dx = dx / step;
  dy = dy / step;
  float x = p1.x;
  float y = p1.y;
  int i = 1;
  while (i <= step) {
    unsigned char &c = img.at((int)x, (int)y);
    c = color;
    x = x + dx;
    y = y + dy;
    i = i + 1;
  }
}
void extra::drawRectangle(Image &img, Rectangle r, unsigned char color) {
  for (int x = r.x; x <= r.x + r.width; x++)
    for (int y = r.y; y <= r.y + r.height; y++) {
      unsigned char &c = img.at(x, y);
      c = color;
    }
}
void extra::drawRectangle(Image &img, Point tl, Point br, unsigned char color) {
  drawRectangle(img, Rectangle(tl.x, tl.y, br.x - tl.x, br.y - tl.y), color);
}
