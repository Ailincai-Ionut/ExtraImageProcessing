#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Image.h"

bool isIn(Point p, Rectangle r) {
  if (p.x > r.x && p.x < r.x + r.width && p.y > r.y && p.y < r.y + r.height)
    return true;
  return false;
}

Point::Point() : x{0}, y{0} {}
Point::Point(int xcoord, int ycoord) : x{xcoord}, y{ycoord} {}

std::ostream &operator<<(std::ostream &out, const Point &p) {
  out << "Point(" << p.x << ',' << p.y << ')';
  return out;
}
std::istream &operator>>(std::istream &in, Point &p) {
  in >> p.x >> p.y;
  return in;
}

Rectangle::Rectangle() : x{0}, y{0}, width{0}, height{0} {}
Rectangle::Rectangle(int xcoord, int ycoord, int w, int h)
    : x{xcoord}, y{ycoord}, width{w}, height{h} {}
Rectangle::Rectangle(Point topleft, Point botright)
    : x{topleft.x}, y{topleft.y}, width{botright.x - topleft.x},
      height{botright.y - topleft.y} {}

Rectangle Rectangle::operator+(const Point &p) {
  Rectangle result(x, y, width, height);
  result.x += p.x;
  result.y += p.y;
  return result;
}
Rectangle Rectangle::operator-(const Point &p) {
  Rectangle result(x, y, width, height);
  result.x -= p.x;
  result.y -= p.y;
  return result;
}
Rectangle Rectangle::operator&(const Rectangle &r) {
  int xmin = std::min(x, r.x);
  int ymin = std::min(y, r.y);
  int xmax = std::max(x + width, r.x + r.width);
  int ymax = std::max(y + height, r.y + r.height);
  if (xmax - xmin > width + r.width || ymax - ymin > height + r.height)
    return Rectangle();
  // This is hell
  int topleftx = std::max(x, r.x);
  int toplefty = std::max(y, r.y);
  int botrightx = std::min(x + width, r.x + r.width);
  int botrighty = std::min(y + height, r.y + r.height);
  return Rectangle(topleftx, toplefty, botrightx - topleftx,
                   botrighty - toplefty);
}
Rectangle Rectangle::operator|(const Rectangle &r) {
  //TODO: what the fuck do I do an rectangle union??
  return Rectangle();
}

std::ostream &operator<<(std::ostream &out, const Rectangle &r) {
  out << "Rectangle(" << r.x << ',' << r.y << ',' << r.width << ',' << r.height
      << ')';
  return out;
}
std::istream &operator>>(std::istream &in, Rectangle &r) {
  in >> r.x >> r.y >> r.width >> r.height;
  return in;
}

Image::Image() {
  width = 0;
  height = 0;
  data = nullptr;
}
Image::Image(unsigned int w, unsigned int h) : width(w), height(h) {
  data = new unsigned char *[height]();
  for (unsigned int i = 0; i < height; i++)
    data[i] = new unsigned char[width]();
}
Image::Image(const Image &img) : width(img.width), height(img.height) {
  data = new unsigned char *[img.height]();
  for (unsigned int i = 0; i < img.height; i++) {
    data[i] = new unsigned char[width]();
    for (unsigned int j = 0; j < img.width; j++) {
      data[i][j] = img.data[i][j];
    }
  }
}
Image::~Image() { free(); }

Image &Image::operator=(const Image &img) {
  if (data != nullptr) {
    for (unsigned int i = 0; i < height; i++)
      delete[] data[i];
    delete[] data;
  }
  height = img.height;
  width = img.width;
  data = new unsigned char *[img.height]();
  for (unsigned int i = 0; i < img.height; i++) {
    data[i] = new unsigned char[width]();
    for (unsigned int j = 0; j < img.width; j++) {
      data[i][j] = img.data[i][j];
    }
  }
  return *this;
}

void Image::free() {
  for (unsigned int i = 0; i < height; i++)
    delete[] data[i];
  delete[] data;
  data = nullptr;
  // TODO: the free function
  // Should this set to 0 height and width?
}

bool Image::load(std::string filePath) {
  std::ifstream in(filePath);
  if (!in.is_open())
    return false;
  std::string comment;
  in >> magic_number;
  char c;
  in.get(c);
  if (in.peek() == '#')
    getline(in, comment, '\n');
  this->free();
  in >> width >> height;
  unsigned int maximum;
  in >> maximum;
  data = new unsigned char *[height]();
  for (unsigned int i = 0; i < height; i++)
    data[i] = new unsigned char[width]();
  unsigned int temp;
  for (unsigned int i = 0; i < height; i++)
    for (unsigned int j = 0; j < width; j++) {
      in >> temp;
      data[i][j] = (unsigned char)temp;
    }
  return true;
}
bool Image::save(std::string filePath) {
  std::ofstream out(filePath);
  if (!out.is_open())
    return false;
  out << "P2" << std::endl;
  out << "#THIS IS A COPY\n";
  out << width << ' ' << height << std::endl;
  out << "255\n";
  int numbers = 0;
  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) {
      out << (unsigned int)data[i][j] << " ";
      numbers++;
      if (numbers == 12) {
        numbers = 0;
        out << std::endl;
      }
    }
    out << std::endl;
  }
  return true;
}

bool Image::isEmpty() const {
  if (height == 0 && width == 0)
    return true;
  return false;
}

unsigned char &Image::at(unsigned int x, unsigned int y) const {
  if (x >= 0 && x < width && y >= 0 && y < height)
    return data[y][x];
  // TODO: what do you do if x or y is incorrect?
}
unsigned char &Image::at(Point &p) const {
  if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height)
    return data[p.y][p.x];
}

unsigned char *Image::row(unsigned int y) {
  if (y >= 0 && y < height)
    return data[y];
  // TODO: same shiy as in the ats
}

bool Image::getROI(Image &roiImg, Rectangle roiRect) {
  return getROI(roiImg, roiRect.x, roiRect.y, roiRect.width, roiRect.height);
}
bool Image::getROI(Image &roiImg, unsigned int x, unsigned int y,
                   unsigned int width, unsigned int height) {
  if (x >= 0 && x < width && y >= 0 && y < height) {
    if (x + width - 1 < this->width && y + height - 1 < this->height) {
      roiImg.free();
      roiImg.height = height;
      roiImg.width = width;
      roiImg.data = new unsigned char *[height]();
      for (unsigned int i = 0; i < height; i++)
        *(roiImg.data + i) = new unsigned char[width]();
      for (unsigned int i = 0; i < height; i++)
        for (unsigned int j = 0; j < width; j++)
          *(*(roiImg.data + i) + j) = *(*(this->data + i + y) + j + x);
      return true;
    }
  }
  return false;
}

Image Image::operator+(const Image &img) {
  if (height == img.height && width == img.width) {
    Image sum(width, height);
    unsigned int temp;
    for (unsigned int i = 0; i < height; i++) {
      for (unsigned int j = 0; j < width; j++) {
        temp = (unsigned int)data[i][j] + (unsigned int)img.data[i][j];
        if (temp > 255)
          temp = 255;
        sum.data[i][j] = (unsigned char)temp;
      }
    }
    // TODO: do this
    //  do you divide by 2 here?
    // or just capp it?
    return sum;
  }
  return Image();
}
Image Image::operator-(const Image &img) {
  if (height == img.height && width == img.width) {
    Image dif(width, height);
    int temp;
    for (unsigned int i = 0; i < height; i++) {
      for (unsigned int j = 0; j < width; j++) {
        temp = (unsigned int)data[i][j] - (unsigned int)img.data[i][j];
        if (temp < 0)
          temp = 0;
        dif.data[i][j] = (unsigned char)temp;
      }
    }
    return dif;
  }
  return Image();
}
Image Image::operator*(const Image &img) {
  if (height == img.height && width == img.width) {
    Image prod(width, height);
    unsigned int temp;
    for (unsigned int i = 0; i < height; i++) {
      for (unsigned int j = 0; j < width; j++) {
        temp = (unsigned int)data[i][j] * (unsigned int)img.data[i][j];
        if (temp > 255)
          temp = 255;
        prod.data[i][j] = (unsigned char)temp;
      }
    }
    return prod;
  }
  return Image();
}

Image Image::operator+(const unsigned char scalar) {
  Image sum(width, height);
  unsigned int temp;
  for (unsigned int i = 0; i < height; i++)
    for (unsigned int j = 0; j < width; j++) {
      temp = (unsigned int)data[i][j] + (unsigned int)scalar;
      if (temp > 255)
        temp = 255;
      sum.data[i][j] = (unsigned char)temp;
    }
  return sum;
}
Image Image::operator-(const unsigned char scalar) {
  Image dif(width, height);
  int temp;
  for (unsigned int i = 0; i < height; i++)
    for (unsigned int j = 0; j < width; j++) {
      temp = (int)data[i][j] - (int)scalar;
      if (temp < 0)
        temp = 0;
      dif.data[i][j] = (unsigned char)temp;
    }
  return dif;
}
Image Image::operator*(const unsigned char scalar) {
  Image prod(width, height);
  unsigned int temp;
  for (unsigned int i = 0; i < height; i++)
    for (unsigned int j = 0; j < width; j++) {
      temp = (unsigned int)data[i][j] * (unsigned int)scalar;
      if (temp > 255)
        temp = 255;
      prod.data[i][j] = (unsigned char)temp;
    }
  return prod;
}

std::ostream &operator<<(std::ostream &out, const Image &img) {
  out << std::setw(3);
  for (unsigned int i = 0; i < img.height; i++) {
    for (unsigned int j = 0; j < img.width; j++)
      out << (int)img.data[i][j] << ' ';
    out << std::endl;
  }
  return out;
}

Image Image::zeros(unsigned int width, unsigned int height) {
  return Image(width, height);
}
Image Image::ones(unsigned int width, unsigned int height) {
  Image img(width, height);
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      img.data[i][j] = 1;
  return img;
}
