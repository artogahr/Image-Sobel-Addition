
#include <iostream> // std::cout
#include <fstream>  // std::ifstream
#include <cstdint>
#include "Image.h"
using namespace std;
int main(int argc, char *argv[])
{
    bool run = true;
    int selection, treshold;
    ifstream bin1, bin2;
    ofstream output;
    bin1.open(argv[1], std::ifstream::binary);
    bin2.open(argv[2], std::ifstream::binary);
    output.open(argv[3], ios::app);
    Image image1, image2;
    bin1 >> image1;
    bin2 >> image2;
    cout << "\nEnter treshold for pixel-binary conversion:\n -> ";
    cin >> treshold;
    image1.setTreshold(treshold);
    image2.setTreshold(treshold);
    while (run)
    {
        cout << "\nSelect your operation:\n\n\t[1] -> Print image\n\t[2] -> Apply operation on images\n\t[3] -> Exit\n -> ";
        cin >> selection;
        switch (selection)
        {
        case 1:
            cout << "\nSelect image:\n\n\t[1] -> " << argv[1] << "\n\t[2] -> " << argv[2] << "\n- > ";
            Image image;
            cin >> selection;
            if (selection == 1)
            {
                image.copy(image1);
                output << "\nImage 1 ";
            }
            else if (selection == 2){
                image.copy(image2);
                output << "\nImage 2 ";
            }
            cout << "\nApply sobel filter?\n\t[1] -> Yes\n\t[2] -> No\n -> ";
            cin >> selection;
            if (selection == 1)
            {
                image.sobel();
                image.print();
                output << "with sobel filter:\n";
                output << image;
            }
            else{
                image.print();
                output << "without sobel filter:\n";
                output << image;
            }
            break;
        case 2:
            cout << "\n\tSelect your operation:\n\n\t\t[1] -> " << argv[1] << " + " << argv[2] << " (Logical OR)" << endl;
            cout << "\t\t[2] -> " << argv[1] << " * " << argv[2] << " (Logical AND)" << endl;
            cout << "\t\t[3] -> !" << argv[1] << " or !" << argv[2] << " (Logical NOT)\n\t -> ";
            cin >> selection;

            if (selection == 1)
            {
                Image result = image1 + image2;
                result.setTreshold(treshold);
                result.print();
                output << "\nImage 1 + Image 2 (Logical OR):\n";
                output << result;
            }

            else if (selection == 2)
            {
                Image result = image1 * image2;
                result.setTreshold(treshold);
                result.print();
                output << "\nImage 1 * Image 2 (Logical AND):\n";
                output << result;
            }
            else if (selection == 3)
            {
                cout << "\n\t\t\t[1] -> !" << argv[1];
                cout << "\n\t\t\t[2] -> !" << argv[2];
                cout << "\n\t\t -> ";
                cin >> selection;
                if (selection == 1)
                {
                    Image result = !image1;
                    result.print();
                    output << "\n!Image 1 (Logical NOT):\n";
                    output << result;
                }
                else if (selection == 2)
                {
                    Image result = !image2;
                    result.print();
                    output << "\n!Image 2 (Logical NOT):\n";
                    output << result;
                }
            }
            break;
        case 3:
            run = false;
        }
    }
    return 0;
}