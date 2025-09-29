#pragma once

#include "pixel.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Image
{
public:
    int width;
    int height;
    int maxColorValue;
    Pixel **pixels;
    std::string format;

    Image() : width(0), height(0), maxColorValue(255), pixels(nullptr), format("P3") {}

    bool readFile(const string &filename)
    {
        ifstream file(filename, ios::binary);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }

        file >> format;

        char ch;
        file >> ws;
        while (file.peek() == '#')
        {
            string comment;
            getline(file, comment);
            file >> ws;
        }

        file >> width >> height >> maxColorValue;

        file.get(ch);

        pixels = new Pixel *[height];
        for (int i = 0; i < height; i++)
        {
            pixels[i] = new Pixel[width];
        }

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

    bool writeFile(const string &filename)
    {
        ofstream file(filename, ios::binary);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }

        file << format << "\n";
        file << width << " " << height << "\n";
        file << maxColorValue << "\n";

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
