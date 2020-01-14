#include <iostream> // std::cout
#include <fstream>  // std::ifstream
#include <cstdint>
#include "Image.h"
using namespace std;
int main(int argc, char *argv[])
{
    bool run = true;
    int selection, treshold;
    string bin1Name = "image1.bin", bin2Name = "image2.bin", outputName = "output.txt";
    ifstream bin1, bin2;
    ofstream output;
    if(argc < 3)
    {
        cout << "correct arguments not supplied, using default settings";
    }
    else
    {
        bin1Name = argv[1];
        bin2Name = argv[2];
        outputName = argv[3];
    }
    
    bin1.open(bin1Name, std::ifstream::binary);
    bin2.open(bin2Name, std::ifstream::binary);
    output.open(outputName, ios::app);
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
            cout << "\nSelect image:\n\n\t[1] -> " << bin1Name << "\n\t[2] -> " << bin2Name << "\n- > ";
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
            cout << "\n\tSelect your operation:\n\n\t\t[1] -> " << bin1Name << " + " << bin2Name << " (Logical OR)" << endl;
            cout << "\t\t[2] -> " << bin1Name << " * " << bin2Name << " (Logical AND)" << endl;
            cout << "\t\t[3] -> !" << bin1Name << " or !" << bin2Name << " (Logical NOT)\n\t -> ";
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
                cout << "\n\t\t\t[1] -> !" << bin1Name;
                cout << "\n\t\t\t[2] -> !" << bin2Name;
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