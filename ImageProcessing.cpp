#include <cmath>
#include <iostream>

#include "ImageProcessing.h"

BrightnessContrastAdjustment::BrightnessContrastAdjustment(char a, char b)
    : alpha{a}, beta{b} {};

void BrightnessContrastAdjustment::process(const Image &src, Image &dst) {
  Image result(src);
  if (alpha > 0) {
    if (beta < 0)
      dst = result * alpha - (unsigned char)(-beta);
    else
      dst = result * alpha + (unsigned char)beta;
  }
  // dst = result;
}

GammaCorrection::GammaCorrection(float l) : lambda{l} {}
void GammaCorrection::process(const Image &src, Image &dst) {
  Image result(src);
  for (int i = 0; i < result.getHeight(); i++) {
    for (int j = 0; j < result.getWidth(); j++) {
      unsigned char &c = result.at(j, i);
      float a = pow((float)c, lambda);
      if (a > 255)
        a = 255;
      if (a - (int)a > 0.5)
        a++;
      c = (unsigned char)a;
    }
  }
  dst = result;
}

ImageConvolution::ImageConvolution(const float k[3][3]) {
  this->k = 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      kernel[i][j] = k[i][j];
}

void ImageConvolution::process(const Image &src, Image &dst) {
  Image result(src);
  // TODO: there needs to be edge cases....
  for (unsigned int y = 1; y < result.getHeight() - 1; y++)
    for (unsigned int x = 1; x < result.getWidth() - 1; x++) {
      float value = 0;
      // NOTE: implement Matrix...
      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
          value += kernel[i][j] * (int)src.at(x - j + k, y - i + k);
        }
      if (value > 255)
        value = 255;
      if (value < 0)
        value = 0;
      unsigned char &c = result.at(x, y);
      c = (unsigned char)value;
    }
  dst = result;
}
