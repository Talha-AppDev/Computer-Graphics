#include "Image.h"
using namespace std;

int main()
{
    Image img;
    img.readFile("/home/talha/Desktop/Computer Graphics/A01_d2/DSCF0019.ppm");
    img.writeFile("/home/talha/Desktop/Computer Graphics/Output/new_DSCF0019.ppm");

    return 0;
}