#include <iostream>
#include "image.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

const string IMAGE_SAVE_PATH = "/home/talha/Desktop/Computer Graphics/Output/";
const string IMAGE_LOAD_PATH = "/home/talha/Desktop/Computer Graphics/Input/";

void clearScreen() {
    system("clear"); 
}

void showMenu() {
    cout << "\n========== IMAGE PROCESSING MENU ==========\n";
    cout << " 1.  Load an Image\n";
    cout << " 2.  Show Image Info\n";
    cout << " 3.  Turn Image Black\n";
    cout << " 4.  Turn Image White\n";
    cout << " 5.  Turn Image Red\n";
    cout << " 6.  Turn Image Green\n";
    cout << " 7.  Turn Image Blue\n";
    cout << " 8.  Turn Image Yellow\n";
    cout << " 9.  Turn Image Magenta\n";
    cout << "10.  Turn Image Cyan\n";
    cout << "11.  Convert to Grayscale & Save\n";
    cout << "12.  Rotate Image \n";
    cout << "13.  Save Current Image\n";
    cout << "14.  Load, Process & Save Morph Images\n";
    cout << "15.  Create Negative Image\n";
    cout << "16.  Change Lamp Color (Light ON/OFF)\n";
    cout << " 0.  Exit\n";
    cout << "===========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    Image img, I1, I2;
    string filename, img1, img2;
    int choice;

    do {
        showMenu();
        cin >> choice;
        clearScreen();

        switch (choice) {
            case 1: {
                cout << "Enter filename to load: ";
                cin >> filename;
                if (img.readFile(IMAGE_LOAD_PATH + filename))
                    cout << "Image loaded successfully!\n";
                else
                    cout << "Failed to load image.\n";
                break;
            }
            case 2: img.showInfo(); break;
            case 3: img.makeBlack();   cout << "Image turned Black!\n"; break;
            case 4: img.makeWhite();   cout << "Image turned White!\n"; break;
            case 5: img.makeRed();     cout << "Image turned Red!\n"; break;
            case 6: img.makeGreen();   cout << "Image turned Green!\n"; break;
            case 7: img.makeBlue();    cout << "Image turned Blue!\n"; break;
            case 8: img.makeYellow();  cout << "Image turned Yellow!\n"; break;
            case 9: img.makeMagenta(); cout << "Image turned Magenta!\n"; break;
            case 10: img.makeCyan();   cout << "Image turned Cyan!\n"; break;

            case 11: {
                cout << "Enter filename to save grayscale image: ";
                cin >> filename;
                if (img.makeGrayscale(IMAGE_SAVE_PATH + filename))
                    cout << "Grayscale image saved successfully!\n";
                else
                    cout << "Failed to save grayscale image.\n";
                break;
            }

            case 12: {
                img.turnImage();
                cout << "Image rotated 90° counter-clockwise!\n";
                break;
            }

            case 13: {
                cout << "Enter filename to save: ";
                cin >> filename;
                if (img.writeFile(IMAGE_SAVE_PATH + filename))
                    cout << "Image saved successfully!\n";
                else
                    cout << "Failed to save image.\n";
                break;
            }

            case 14: {
                cout << "Enter first image filename: ";
                cin >> img1;
                I1.readFile(IMAGE_LOAD_PATH + img1);

                cout << "Enter second image filename: ";
                cin >> img2;
                I2.readFile(IMAGE_LOAD_PATH + img2);

                if (img.makeMorph(I1, I2))
                    cout << "Morph images created successfully!\n";
                else
                    cout << "Failed to create morph images.\n";
                break;
            }

            case 15: {
                if (img.makeNegative())
                    cout << "Negative image created successfully!\n";
                else
                    cout << "Failed to create negative image.\n";
                break;
            }

            case 16: {
                cout << "Enter Light ON image filename: ";
                cin >> img1;
                I1.readFile(IMAGE_LOAD_PATH + img1);

                cout << "Enter Light OFF image filename: ";
                cin >> img2;
                I2.readFile(IMAGE_LOAD_PATH + img2);

                float r, g, b;
                cout << "Enter scaling factors for (R G B), e.g., 1.0 0.5 0.2: ";
                cin >> r >> g >> b;

                if (img.changeLampColor(I1, I2, r, g, b))
                    cout << "Lamp color changed successfully!\n";
                else
                    cout << "Failed to change lamp color.\n";
                break;
            }

            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
