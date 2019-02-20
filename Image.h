#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <fstream>
using namespace std;
class Image
{
public:
  friend ifstream &operator>>(ifstream &is, Image &i);
  friend ofstream &operator<<(ofstream &os, Image &i);
  friend Image operator+(Image left, Image right);
  friend Image operator*(Image left, Image right);
  friend Image operator!(Image i);
  void print();
  void sobel();
  void setTreshold(int t);
  int getTreshold();
  int getHeight();
  int getWidth();
  void copy(Image im);

private:
  int height, width, length, treshold;
  unsigned char **pixels;
  unsigned char **sobelPixels;
};
ifstream &operator>>(ifstream &is, Image &i);
ofstream &operator<<(ofstream &os, Image &i);
Image operator+(Image left, Image right);
Image operator*(Image left, Image right);
Image operator!(Image i);

#endif
