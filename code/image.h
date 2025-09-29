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

    Image() : width(0), height(0), maxColorValue(255), pixels(nullptr), format("\0") {}

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

    void showInfo()
    {
        cout << "Format: " << format << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Max Color Value: " << maxColorValue << endl;
    }

    bool writeFile(const string &filename)
    {
        ofstream file(filename, ios::binary);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }

        file << format << " #yeh file ka format hai bedu\n";
        file << width << " " << height << "\n";
        file << maxColorValue << " #oo max color ki value yh hai\n";

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

    void makeCyan(){
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
