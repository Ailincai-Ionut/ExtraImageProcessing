#include <fstream>
#include <iostream>
#include <string>

#include "Image.h"

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
Image::~Image() {
  for (unsigned int i = 0; i < height; i++)
    delete[] data[i];
  delete[] data;
}

Image &Image::operator=(const Image &img) {
  for (unsigned int i = 0; i < height; i++)
    delete[] data[i];
  delete[] data;
  height = img.height;
  width = img.width;
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
}

bool Image::load(std::string filePath) {
  std::ifstream in(filePath);
  if (!in.is_open())
    return false;
  std::string comment;
  in >> magic_number;
  std::cout << magic_number << std::endl;
  if (in.peek() == '#') {
    getline(in, comment, '\n');
    getline(in, comment, '\n');
    std::cout << comment << std::endl;
  }
  this->free();
  in >> width >> height;
  std::cout << width << " " << height << std::endl;
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
