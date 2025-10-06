#pragma once
#include "pixel.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ios;
using std::max;
using std::ofstream;
using std::stoi;
using std::string;
using std::swap;
using std::to_string;

class Image
{
    int width;
    int height;
    int maxColorValue;
    Pixel **pixels;
    string format;

public:
    Image() : width(0), height(0), maxColorValue(255), pixels(nullptr), format("\0") {}

    Image(const Image &other)
    {
        width = other.width;
        height = other.height;
        maxColorValue = other.maxColorValue;
        format = other.format;

        if (other.pixels == nullptr)
        {
            pixels = nullptr;
            return;
        }

        pixels = new Pixel *[height];
        for (int i = 0; i < height; i++)
        {
            pixels[i] = new Pixel[width];
            for (int j = 0; j < width; j++)
            {
                pixels[i][j] = other.pixels[i][j];
            }
        }
    }

    bool readFile(const string &filename)
    {
        ifstream file(filename, ios::binary);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }

        format = nextToken(file);
        width = stoi(nextToken(file));
        height = stoi(nextToken(file));
        maxColorValue = stoi(nextToken(file));

        char ch;
        file.get(ch);

        pixels = new Pixel *[height];
        for (int i = 0; i < height; i++)
            pixels[i] = new Pixel[width];

        if (format == "P6")
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    unsigned char rgb[3];
                    file.read((char *)rgb, 3);
                    pixels[i][j].R = rgb[0];
                    pixels[i][j].G = rgb[1];
                    pixels[i][j].B = rgb[2];
                }
            }
        }
        else if (format == "P5")
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    unsigned char gray;
                    file.read((char *)&gray, 1);
                    pixels[i][j].R = gray;
                    pixels[i][j].G = gray;
                    pixels[i][j].B = gray;
                }
            }
        }
        else
        {
            cerr << "Error: Unsupported format " << format << endl;
            return false;
        }

        file.close();
        return true;
    }

    string nextToken(ifstream &file)
    {
        string token;
        while (true)
        {
            file >> token;
            if (token[0] == '#')
            {
                string comment;
                getline(file, comment);
                continue;
            }
            return token;
        }
    }

    bool makeGrayscale(const string &filename)
    {

        ofstream file(filename, ios::binary);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }

        format = "P5";
        file << format << '\n';
        file << width << " " << height << '\n';
        file << maxColorValue << '\n';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                unsigned char rgb[3] = {pixels[i][j].R, pixels[i][j].G, pixels[i][j].B};
                unsigned char gray = (rgb[0] + rgb[1] + rgb[2]) / 3;

                file.write((const char *)&gray, 1);
            }
        }

        file.close();
        return true;
    }

    bool weighted(const float &w1, const string &filename, const Image &img1, const Image &img2)
    {
        if (img1.pixels == nullptr || img2.pixels == nullptr)
        {
            cerr << "Error: Data of Images not loaded." << endl;
            return false;
        }

        if (img1.format != img2.format)
        {
            cerr << "Error: Images formats do not match." << endl;
            return false;
        }

        if (img1.width != img2.width || img1.height != img2.height)
        {
            cerr << "Error: Images dimensions do not match." << endl;
            return false;
        }

        format = img1.format;
        width = img1.width;
        height = img1.height;
        maxColorValue = img1.maxColorValue;

        Pixel **newPixels = new Pixel *[height];
        for (int i = 0; i < height; i++)
            newPixels[i] = new Pixel[width];

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int red = (img1.pixels[i][j].R * w1) + (img2.pixels[i][j].R * (1 - w1));
                int blue = (img1.pixels[i][j].B * w1) + (img2.pixels[i][j].B * (1 - w1));
                int green = (img1.pixels[i][j].G * w1) + (img2.pixels[i][j].G * (1 - w1));

                unsigned char r = (red > 255) ? 255 : red;
                unsigned char g = (green > 255) ? 255 : green;
                unsigned char b = (blue > 255) ? 255 : blue;

                newPixels[i][j].R = r;
                newPixels[i][j].G = g;
                newPixels[i][j].B = b;
            }
        }

        // Write to PPM file
        ofstream file(filename, ios::binary);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }

        file << format << '\n';
        file << width << " " << height << "\n";
        file << maxColorValue << '\n';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                unsigned char rgb[3] = {newPixels[i][j].R, newPixels[i][j].G, newPixels[i][j].B};
                file.write((const char *)rgb, 3);
            }
        }
        file.close();

        for (int i = 0; i < height; i++)
            delete[] newPixels[i];
        delete[] newPixels;

        return true;
    }

    bool makeNegative()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return false;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].R = 255 - pixels[i][j].R;
                pixels[i][j].G = 255 - pixels[i][j].G;
                pixels[i][j].B = 255 - pixels[i][j].B;
            }
        }

        return true;
    }

    bool makeMorph(const Image &img1, const Image &img2)
    {
        int i = 0;

        for (float w = 0.0; w <= 1.0; w += 0.1)
        {
            string filename = "/home/talha/Desktop/Computer Graphics/Morph/morph_" + to_string(i) + ".ppm";
            if (!weighted(w, filename, img1, img2))
            {
                cerr << "Failed to create morph image: " << filename << endl;
                return false;
            }
            i++;
        }

        for (float w = 1.0; w >= 0.0; w -= 0.1)
        {
            string filename = "/home/talha/Desktop/Computer Graphics/Morph/morph_" + to_string(i) + ".ppm";
            if (!weighted(w, filename, img1, img2))
            {
                cerr << "Failed to create morph image: " << filename << endl;
                return false;
            }
            i++;
        }

        return true;
    }

    void showInfo()
    {
        cout << "Format: " << format << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Max Color Value: " << maxColorValue << endl;
    }

    bool changeLampColor(const Image &OnImage, const Image &OffImage, float r, float g, float b)
    {
        if (OnImage.pixels == nullptr || OffImage.pixels == nullptr)
        {
            cerr << "Error: Data of Images not loaded." << endl;
            return false;
        }

        if (OnImage.format != OffImage.format)
        {
            cerr << "Error: Images formats do not match." << endl;
            return false;
        }

        if (OnImage.width != OffImage.width || OnImage.height != OffImage.height)
        {
            cerr << "Error: Images dimensions do not match." << endl;
            return false;
        }

        format = OnImage.format;
        width = OnImage.width;
        height = OnImage.height;
        maxColorValue = OnImage.maxColorValue;

        // allocate memory
        Pixel **newPixels = new Pixel *[height];
        for (int i = 0; i < height; i++)
            newPixels[i] = new Pixel[width];

        // process pixels
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int lampR = max(0, OnImage.pixels[i][j].R - OffImage.pixels[i][j].R);
                int lampG = max(0, OnImage.pixels[i][j].G - OffImage.pixels[i][j].G);
                int lampB = max(0, OnImage.pixels[i][j].B - OffImage.pixels[i][j].B);

                int red = OffImage.pixels[i][j].R + (lampR * r);
                int green = OffImage.pixels[i][j].G + (lampG * g);
                int blue = OffImage.pixels[i][j].B + (lampB * b);

                newPixels[i][j].R = (red > 255) ? 255 : red;
                newPixels[i][j].G = (green > 255) ? 255 : green;
                newPixels[i][j].B = (blue > 255) ? 255 : blue;
            }
        }

        // free old pixels if needed
        if (pixels != nullptr)
        {
            for (int i = 0; i < height; i++)
                delete[] pixels[i];
            delete[] pixels;
        }

        // assign new image
        pixels = newPixels;

        return true;
    }

    bool writeFile(const string &filename)
    {
        ofstream file(filename, ios::binary);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }

        file << format << '\n';
        file << width << " " << height << "\n";
        file << maxColorValue << '\n';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                unsigned char rgb[3] = {
                    pixels[i][j].R,
                    pixels[i][j].G,
                    pixels[i][j].B};
                file.write((const char *)rgb, 3);
            }
        }

        file.close();
        return true;
    }

    void makeBlack()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].R = 0;
                pixels[i][j].G = 0;
                pixels[i][j].B = 0;
            }
        }
    }

    void makeWhite()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].R = 255;
                pixels[i][j].G = 255;
                pixels[i][j].B = 255;
            }
        }
    }

    void makeRed()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].R = 255;
                pixels[i][j].G = 0;
                pixels[i][j].B = 0;
            }
        }
    }

    void makeYellow()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].R = 255;
                pixels[i][j].G = 255;
                pixels[i][j].B = 0;
            }
        }
    }

    void makeMagenta()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].R = 255;
                pixels[i][j].G = 0;
                pixels[i][j].B = 255;
            }
        }
    }

    void makeCyan()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].R = 0;
                pixels[i][j].G = 255;
                pixels[i][j].B = 255;
            }
        }
    }

    void makeGreen()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].R = 0;
                pixels[i][j].G = 255;
                pixels[i][j].B = 0;
            }
        }
    }

    void makeBlue()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return;
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                pixels[i][j].R = 0;
                pixels[i][j].G = 0;
                pixels[i][j].B = 255;
            }
        }
    }

    void turnImage()
    {
        if (pixels == nullptr)
        {
            cerr << "Error: Image data is not loaded." << endl;
            return;
        }

        Pixel **newPixels = new Pixel *[width];
        for (int i = 0; i < width; i++)
            newPixels[i] = new Pixel[height];

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                newPixels[width - 1 - j][i] = pixels[i][j];
            }
        }

        for (int i = 0; i < height; i++)
            delete[] pixels[i];
        delete[] pixels;

        pixels = newPixels;
        swap(width, height);
    }

    ~Image()
    {
        if (pixels != nullptr)
        {
            for (int i = 0; i < height; i++)
            {
                delete[] pixels[i];
            }
            delete[] pixels;
            pixels = nullptr;
        }
    }
};
