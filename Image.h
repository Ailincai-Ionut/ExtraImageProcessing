#pragma once
#include <string>

class Size {
public:
  Size(unsigned int h, unsigned int w) : s_height(h), s_width(w){};
  inline unsigned int width() const { return s_width; }
  inline unsigned int height() const { return s_height; }

private:
  unsigned int s_height;
  unsigned int s_width;
};

class Point {
public:
  int x;
  int y;
};

class Rectangle {
public:
  int x, y, width, height;
};

class Image {
public:
  Image();
  Image(unsigned int w, unsigned int h);
  Image(const Image &img);

  ~Image();

  Image &operator=(const Image &img);

  inline unsigned char getHeight() const { return height; };
  inline unsigned char getWidth() const { return width; };
  inline Size size() const { return Size(height, width); };

  unsigned char &at(unsigned int x, unsigned int y) const;
  unsigned char &at(Point &p) const;

  unsigned char *row(unsigned int y);

  bool isEmpty() const;

  bool load(std::string filePath);
  bool save(std::string filePath);

  bool getROI(Image &roiImg, Rectangle roiRect);
  bool getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width,
              unsigned int height);
  void free();

  Image operator+(const Image &img);
  Image operator-(const Image &img);
  Image operator*(const Image &img);

  friend std::ostream &operator<<(std::ostream &out, const Image &img);

private:
  unsigned char **data;
  unsigned int height;
  unsigned int width;
  std::string magic_number;
};