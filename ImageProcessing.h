#pragma once

#include "Image.h"

class ImageProcessing {
public:
  virtual void process(const Image &src, Image &dst) = 0;
};

class BrightnessContrastAdjustment : ImageProcessing {
public:
  BrightnessContrastAdjustment(char a, char b);

  void process(const Image &src, Image &dst);

  inline void setAlpha(char a) { alpha = a; };
  inline void setBeta(char b) { beta = b; };
  inline char getAlpha() const { return alpha; };
  inline char getBeta() const { return beta; };

private:
  char alpha, beta;
};

class GammaCorrection : ImageProcessing {
public:
  GammaCorrection(float l);

  void process(const Image &src, Image &dst);

  inline void setLambda(float l) { lambda = l; };
  inline float getLambda() const { return lambda; };

private:
  float lambda;
};

class ImageConvolution : ImageProcessing {
public:
  ImageConvolution(const float k[3][3]);

  void process(const Image &src, Image &dst);

  static Image getIdentityKernel(); // NOTE: here should return a Matrix object

private:
  // TODO: implement the FUCKING matrix class
  float kernel[3][3];
  int k;
};
