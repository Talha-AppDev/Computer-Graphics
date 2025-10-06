#include <iostream>
#include "image.h" // include your Image class

using namespace std;

const string IMAGE_SAVE_PATH = "/home/talha/Desktop/Computer Graphics/Output/";
const string IMAGE_LOAD_PATH = "/home/talha/Desktop/Computer Graphics/Input/";

void showMenu()
{
    cout << "\n========== IMAGE MENU ==========\n";
    cout << "1. Load Image\n";
    cout << "2. Show Image Info\n";
    cout << "3. Make Black\n";
    cout << "4. Make White\n";
    cout << "5. Make Red\n";
    cout << "6. Make Green\n";
    cout << "7. Make Blue\n";
    cout << "8. Make Yellow\n";
    cout << "9. Make Magenta\n";
    cout << "10. Make Cyan\n";
    cout << "11. Make Grayscale\n";
    cout << "12. Turn Image\n";
    cout << "13. Save Image\n";
    cout << "14. Morph Images (Don't use option 1)\n";
    cout << "0. Exit\n";
    cout << "================================\n";
    cout << "Enter choice: ";
}

int main()
{

    Image img, I1, I2;
    string filename, img1, img2;
    int choice;

    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter filename to load: ";
            cin >> filename;
            if (img.readFile(IMAGE_LOAD_PATH + filename))
            {
                system("clear");
                cout << "Image loaded successfully!\n";
            }
            else
                cout << "Failed to load image.\n";
            break;

        case 2:
            system("clear");
            img.showInfo();
            break;

        case 3:
            system("clear");
            img.makeBlack();
            cout << "Image turned Black!\n";
            break;

        case 4:
            system("clear");
            img.makeWhite();
            cout << "Image turned White!\n";
            break;

        case 5:
            system("clear");
            img.makeRed();
            cout << "Image turned Red!\n";
            break;

        case 6:
            system("clear");
            img.makeGreen();
            cout << "Image turned Green!\n";
            break;

        case 7:
            system("clear");
            img.makeBlue();
            cout << "Image turned Blue!\n";
            break;

        case 8:
            system("clear");
            img.makeYellow();
            cout << "Image turned Yellow!\n";
            break;

        case 9:
            system("clear");
            img.makeMagenta();
            cout << "Image turned Magenta!\n";
            break;

        case 10:
            system("clear");
            img.makeCyan();
            cout << "Image turned Cyan!\n";
            break;

        case 11:

            cout << "Enter filename to save grayscale img: ";
            cin >> filename;
            if (img.makeGrayscale(IMAGE_SAVE_PATH + filename))
            {
                system("clear");
                cout << "Grayscale Image saved successfully!\n";
            }
            else
                cout << "Failed to save image.\n";
            break;

        case 12:
            system("clear");
            img.turnImage();
            cout << "Image turned 90 degrees counter-clockwise!\n";
            break;

        case 13:

            cout << "Enter filename to save: ";
            cin >> filename;
            if (img.writeFile(IMAGE_SAVE_PATH + filename))
            {
                system("clear");
                cout << "Image saved successfully!\n";
            }
            else
                cout << "Failed to save image.\n";
            break;

        case 14:

            cout << "Enter first image filename to load: ";
            cin >> img1;
            I1.readFile(IMAGE_LOAD_PATH + img1);
            I1.showInfo();

            cout << "Enter second image filename to load: ";
            cin >> img2;
            I2.readFile(IMAGE_LOAD_PATH + img2);
            I2.showInfo();

            
            if (img.makeMorph(I1, I2))
                cout << "Morph images created successfully!\n";
            else
                cout << "Failed to create morph images.\n";
            break;

        case 0:
            system("clear");
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
