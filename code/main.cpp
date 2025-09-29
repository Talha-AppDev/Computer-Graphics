#include "Image.h"
using namespace std;

int main()
{
    Image img;
    img.readFile("/home/talha/Desktop/Computer Graphics/Output/neeee_Ileft.ppm"); 
    img.showInfo();
    img.writeFile("/home/talha/Desktop/Computer Graphics/Output/neeee2_Ileft.ppm");

    return 0;
}