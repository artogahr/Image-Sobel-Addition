#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "Image.h"
#include <math.h>
ifstream &operator>>(ifstream &is, Image &im)
{
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);

    unsigned char *buffer = new unsigned char[length];
    unsigned char *lala = new unsigned char[length];

    // read data as a block:
    is.read((char *)buffer, length);
    im.length = length;
    // ...buffer contains the entire file...
    im.height = buffer[0];
    im.width = buffer[1];
    //cout << " aaaaaaaaaaaa" << im.height << im.width << endl;
    im.pixels = new unsigned char *[im.height];
    for (int i = 0; i < im.height; i++)
    {
        im.pixels[i] = new unsigned char[im.width];
    }
    for (int i = 0; i < im.height; i++)
    {
        for (int j = 0; j < im.width; j++)
        {

            im.pixels[i][j] = buffer[im.height * j + i + 2];
            // if ((int)(uint8_t)im.pixels[i][j] > 100)
            //     cout << "\u2588";
            // else
            //     cout << "\u2592";
        }
        // cout << endl;
    }
    for (int i = 0; i < im.width * im.height; ++i)
    {
        lala[(i % im.width) * im.height + i / im.width] = buffer[i];
    }

    stbi_write_png("test.png", im.height, im.width, 1, lala, 0);
    delete[] buffer;
}
ofstream &operator<<(ofstream &os, Image &im)
{
    int upperTreshold = im.treshold + ((255 - im.treshold) / 2);
    int lowerTreshold = im.treshold / 2;
    for (int i = 0; i < im.height; i++)
    {
        for (int j = 0; j < im.width; j++)
        {
            if ((int)(uint8_t)im.pixels[i][j] < lowerTreshold)
                os << "\u2591";
            else if ((int)(uint8_t)im.pixels[i][j] < im.treshold)
                os << "\u2592";
            else if ((int)(uint8_t)im.pixels[i][j] < upperTreshold)
                os << "\u2593";
            else
                os << "\u2588";
        }
        os << endl;
    }
}

Image operator+(Image l, Image r)
{
    Image result, left, right;
    int selection;
    left.copy(l);
    right.copy(r);
    cout << "\n\t\tApply Sobel filter to first image?\n\t\t\t[1] -> Yes\n\t\t\t[2] -> No \n\t\t -> ";
    cin >> selection;
    if (selection == 1)
        left.sobel();
    cout << "\n\t\tApply Sobel filter to second image?\n\t\t\t[1] -> Yes\n\t\t\t[2] -> No \n\t\t -> ";
    cin >> selection;
    if (selection == 1)
        right.sobel();
    result.height = left.height < right.height ? left.height : right.height;
    result.width = left.width < right.width ? left.width : right.width;
    result.pixels = new unsigned char *[result.height];
    for (int i = 0; i < result.height; i++)
    {
        result.pixels[i] = new unsigned char[result.width];
    }
    cout << left.treshold << " aaaaaaaaa " << right.treshold;
    for (int i = 0; i < result.height; i++)
    {
        for (int j = 0; j < result.width; j++)
        {
            bool a = left.pixels[i][j] > left.treshold;
            bool b = right.pixels[i][j] > right.treshold;
            result.pixels[i][j] = a || b ? 1 : 255;
        }
        //cout << endl;
    }
    return result;
}

Image operator*(Image l, Image r)
{
    Image result, left, right;
    int selection;
    left.copy(l);
    right.copy(r);
    cout << "\n\t\tApply Sobel filter to first image?\n\t\t\t[1] -> Yes\n\t\t\t[2] -> No \n\t\t -> ";
    cin >> selection;
    if (selection == 1)
        left.sobel();
    cout << "\n\t\tApply Sobel filter to second image?\n\t\t\t[1] -> Yes\n\t\t\t[2] -> No \n\t\t -> ";
    cin >> selection;
    if (selection == 1)
        right.sobel();
    result.height = left.height < right.height ? left.height : right.height;
    result.width = left.width < right.width ? left.width : right.width;
    result.pixels = new unsigned char *[result.height];
    for (int i = 0; i < result.height; i++)
    {
        result.pixels[i] = new unsigned char[result.width];
    }
    for (int i = 0; i < result.height; i++)
    {
        for (int j = 0; j < result.width; j++)
        {
            bool a = left.pixels[i][j] > left.treshold;
            bool b = right.pixels[i][j] > right.treshold;
            result.pixels[i][j] = a && b ? 255 : 1;
        }
        //cout << endl;
    }
    return result;
}

Image operator!(Image im)
{
    int selection;
    Image result;
    result.treshold = im.getTreshold();
    result.height = im.height;
    result.width = im.width;
    result.pixels = new unsigned char *[result.height];
    for (int i = 0; i < result.height; i++)
    {
        result.pixels[i] = new unsigned char[result.width];
    }
    for (int i = 0; i < im.height; i++)
    {
        for (int j = 0; j < im.width; j++)
        {
            result.pixels[i][j] = im.pixels[i][j] > im.treshold ? 1 : 255;
        }
    }
    cout << "\n\t\tApply Sobel filter to the result?\n\t\t\t[1] -> Yes\n\t\t\t[2] -> No \n\t\t -> ";
    cin >> selection;
    if (selection == 1)
        result.sobel();
    return result;
}
void Image::sobel()
{
    sobelPixels = new unsigned char *[height];
    for (int i = 0; i < height; i++)
    {
        sobelPixels[i] = new unsigned char[width];
    }
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            int sobelX = (-1 * pixels[i - 1][j - 1] + -2 * pixels[i - 1][j] + -1 * pixels[i - 1][j + 1] + pixels[i + 1][j - 1] + 2 * pixels[i + 1][j] + pixels[i + 1][j + 1]) / 2;
            int sobelY = (-1 * pixels[i - 1][j - 1] + -2 * pixels[i][j - 1] + -1 * pixels[i + 1][j - 1] + pixels[i - 1][j + 1] + 2 * pixels[i][j + 1] + pixels[i + 1][j + 1]) / 2;
            sobelPixels[i][j] = sqrt(sobelX * sobelX + sobelY * sobelY);
        }
    }
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            pixels[i][j] = sobelPixels[i][j];
        }
    }
}

void Image::print()
{
    int upperTreshold = treshold + ((255 - treshold) / 2);
    int lowerTreshold = treshold / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((int)(uint8_t)pixels[i][j] < lowerTreshold)
                cout << "\u2591";
            else if ((int)(uint8_t)pixels[i][j] < treshold)
                cout << "\u2592";
            else if ((int)(uint8_t)pixels[i][j] < upperTreshold)
                cout << "\u2593";
            else
                cout << "\u2588";
        }
        cout << endl;
    }
    // unsigned char *so = new unsigned char[height * width];
    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //     {
    //         unsigned char temp[height][width];
    //         so[height * j + i] = sobelPixels[i][j];
    //     }
    // }
    // stbi_write_png("test2.png", height, width, 1, so, 0);
}
void Image::copy(const Image im)
{
    height = im.height;
    width = im.width;
    cout << height << width;
    treshold = im.treshold;
    pixels = new unsigned char *[height];
    for (int i = 0; i < height; i++)
    {
        pixels[i] = new unsigned char[width];
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixels[i][j] = im.pixels[i][j];
        }
    }
}

void Image::setTreshold(int t)
{
    treshold = t;
}

int Image::getTreshold()
{
    return treshold;
}

int Image::getHeight()
{
    return height;
}
int Image::getWidth()
{
    return width;
}