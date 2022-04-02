#include <iostream>

#include "Image.h"
#include "ImageProcessing.h"

int main(int argc, char const *argv[]) {
  Image img;
  img.load("apollonian_gasket.ascii.pgm");
  Rectangle r;
  r.x = 0;
  r.y = 0;
  r.width = 600;
  r.height = 600;
  Image processed;
  float kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  ImageConvolution p(kernel);
  p.process(img, processed);
  processed.save("copy.pgm");
  Rectangle r1(1, 1, 6, 2), r2(3, -1, 2, 6);
  std::cout << r1.operator&(r2);
  return 0;
}
