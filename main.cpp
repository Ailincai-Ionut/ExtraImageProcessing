#include <iostream>

#include "Image.h"

int main(int argc, char const *argv[]) {
  Image img;
  img.load("apollonian_gasket.ascii.pgm");
  img.save("copy.pgm");
  return 0;
}
