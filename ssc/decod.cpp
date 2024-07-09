#include <bits/stdc++.h>
#include <filesystem>
#include "../include/Image.h"

using namespace std;

/**
 * @brief Prints out an ASCII message encoded in the least significant bit (LSB) of the pixels of a PPM image.
 * @param argc
 * @param argv
 */
int main(int argc, char* argv[])
{
    /** Verifies if the number of arguments is correct. */ 
    if (argc != 2)
    {
        cout << "Uso: " << argv[0] << " <nome_do_arquivo>" << endl;
        return 1;
    }

    string img_name = argv[1];
    Image img; /**> Stores the PPM image to be decoded. */

    /** Tests if the ReadPPM() function was successful, stops the decoding process otherwise. */
    if (img.ReadPPM(img_name))
    {
        img.DecodeMsg();
    }
   
    img.LiberatePixels();

    return 0;
}