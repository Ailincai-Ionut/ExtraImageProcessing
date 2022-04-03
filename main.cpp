#include <iostream>

#include "DrawModule.h"
#include "Image.h"
#include "ImageProcessing.h"

int main(int argc, char const *argv[]) {
  Image img;
  img.load("balloons.ascii.pgm");
  Image processed;
  float kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  ImageConvolution p(kernel);
  p.process(img, processed);
  extra::drawCircle(processed, Point(0, 0), 50, 128);
  extra::drawLine(processed, Point(100, 200), Point(200, 100), 128);
  extra::drawRectangle(processed, Rectangle(300, 300, 100, 100), 128);
  extra::drawRectangle(processed, Point(100, 300), Point(200, 1000), 128);
  BrightnessContrastAdjustment b(1, 100); // TODO: make alpha a float
  b.process(processed, processed);
  processed.save("copy.pgm");
  Rectangle r1(1, 1, 6, 2), r2(3, -1, 2, 6);
  std::cout << r1.operator&(r2);
  return 0;
}
