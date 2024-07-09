/**
 * @file Image.h
 * @author Lucas Anselmo (lucas.anselmo.099@ufrn.edu.br); Leandro Andrade (leandro.andrade.401@ufrn.edu.br)
 * @brief Header file used in both the encoding and decoding of PPM images using steganography.
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief  Struct that defines the pixel of a PPM image.
 * @param r,g,b Represents the numeric values of Red, Green and Blue of each pixel in a PPM image.
 */
struct Pixel
{
    unsigned char r, g, b;
};

/**
 * @brief  Defines a dinamically allocated PPM image and provides various methods to manipulate and access the image data.
 */
class Image
{
private:
    string img_type = "P3";
    int width = 0, height = 0;
    int max_color = 255;
    Pixel **pixel = nullptr;
    int size = (width * height) * 3;
    int *pixel_array = nullptr;

public:
    /**
     * @brief Default constructor for the Image class.
     */
    Image() : width(0), height(0), pixel(nullptr), pixel_array(nullptr) {}

    /**
     * @brief Constructor to initialize an image with given width and height.
     */
    Image(int w, int h) : width(w), height(h)
    {
        size = (width * height) * 3; /**< This variable defines the size of the array of pixels, counting each R, G and B value as a separate unit of the array. */
    }

    /**
     * @brief Gets the Width object.  
     */
    int GetWidth() const 
    { 
        return width; 
    }

    /**
     * @brief Gets the Height object.
     */
    int GetHeight() const 
    { 
        return height; 
    }

    /**
     * @brief Memory allocation of the matrix of pixels, which is fundamental in defining any Image object.
     */
    void AllocatePixels()
    {
        pixel = new Pixel *[height];
        for (int i = 0; i < height; i++)
        {
            pixel[i] = new Pixel[width];
        }
    }

    /**
     * @brief Deallocates the memory previously allocated by the AllocatePixels() function, as well as the memory alocated by the array of the pixels' 'R', 'G' and 'B' values.
     */
    void LiberatePixels()
    {
        if (pixel != nullptr)
        {
            for (int i = 0; i < height; i++)
            {
                delete[] pixel[i];
            }
            delete[] pixel;
            pixel = nullptr;
        }
        /** Deallocates the memory utilized by the array of the pixels' 'R', 'G' and 'B' values, used in the CreatePPM(), ReadPPM(), ShowArray(), CodeMsg() and DecodeMsg() functions. */
        if (pixel_array != nullptr)
        {
            delete[] pixel_array;
            pixel_array = nullptr;
        }
    }

    /**
     * @brief Function that fills in the matrix of pixels.
     */
    void GetPixels()
    {
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                int r, g, b;
                cin >> r >> g >> b;
                pixel[h][w].r = r;
                pixel[h][w].g = g;
                pixel[h][w].b = b;
            }
        }
    }

    /**
     * @brief Function that checks if a string ends with the valid substring.
     * @param input_text Text inputed into the function, which is to be checked.
     * @param file_type The substring which you wish to check if exists in the end of a given string.
     * @returns true if the substring exists in the end of the given string, false otherwise.
     */
    bool ExtensionCheck(const string &input_text, const string &file_type) 
    {
        if (input_text.length() >= file_type.length()) 
            {
            return (input_text.compare(input_text.length() - file_type.length(), file_type.length(), file_type) == 0);
            } 
        else 
            {
            return false;
            }
    }

    /**
     * @brief  Function that prints out the parameters of a PPM image. Mostly used for testing purposes.
     */
    void PrintPPM() const
    {
        cout << "\033[94mDados da imagem: \033[0m\n";
        cout << "\033[33m- Comprimento: \033[0m\n" << width << endl;
        cout << "\033[33m- Largura: \033[0m\n" << height << endl;
        cout << "\033[33m- Tipo de imagem: \033[0m\n" << img_type << endl;
        cout << "\033[33m- Valor máximo de cor: \033[0m\n" << max_color << endl;
        cout << "\033[33m- Valor RGB de cada pixel:\033[0m\n"; 

        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                Pixel p = pixel[h][w];
                cout << (int)p.r << " ";
                cout << (int)p.g << " ";
                cout << (int)p.b << "   ";
            }
            cout << endl;
        }
        cout << endl;
    }

    /**
     * @brief Function that creates a string containing all the data of a PPM image.
     * @returns all the information needed to define a PPM image.
     */
    string CreatePPM() const
    {
        stringstream img_content;

        img_content << "P3" << endl;
        img_content << width << " " << height << endl;
        img_content << max_color << endl;

        /** Gets the pixels from a previously defined array of pixels. */
        for (int i = 0; i < size; i += 3)
        {
            img_content << pixel_array[i] << " " << pixel_array[i + 1] << " " << pixel_array[i + 2] << " ";
            if ((i / 3 + 1) % width == 0)
            {
                img_content << endl; 
            }
        }
        return img_content.str();
    }

    /**
     * @brief Reads and dynamically stores the content of an image from a valid PPM file.
     * @param file_name The name of a PPM file previously stored inside the source folder, which will be read by the function.
     * @returns true if the image was successfully read, false otherwise.
     */
    bool ReadPPM(const string &file_name)
    {
        /** Tests if the file does exist inside the source folder. */
        ifstream file(file_name);
        if (!file)
        {
            cerr << "\033[31mErro de leitura. O arquivo" << file_name << " não existe.\033[0m\n"; 
            return false;
        }

        string file_type;
        file >> file_type;

    

        /** Tests if the file is in fact a P3/PPM file by looking at it's content. */
        if (file_type != "P3")
        {
            cerr << "\033[31mErro de leitura. O arquivo " << file_name << " não é uma imagem PPM no formato P3.\033[0m\n" << endl; 
            return false;
        }

        file >> width >> height >> max_color;
        size = width * height * 3;

        AllocatePixels();

        /** Memory allocation of the array of pixels, used in decodification and codification. */
        pixel_array = new int[size];
        int index = 0;

        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                int r, g, b;
                file >> r >> g >> b;
                pixel[h][w].r = r;
                pixel[h][w].g = g;
                pixel[h][w].b = b;
                /** Reads and stores in an array the pixels' 'R', 'G' and 'B' values. */
                pixel_array[index++] = r;
                pixel_array[index++] = g;
                pixel_array[index++] = b;
            }
        }
        file.close();
        return true;
    }

    /** 
     * @brief Function that outputs a previously defined array of 'R', 'G' and 'B' values. Mostly used for testing purposes.
     */
    void ShowArray() const
    {
        if (pixel_array == nullptr)
        {
            cout << "Array não inicializado." << endl;
            return;
        }
        for (int i = 0; i < size; i += 3)
        {
            cout << "Pixel [" << i / 3 << "]: R = " << pixel_array[i] << ", G = " << pixel_array[i + 1]
                 << ", B = " << pixel_array[i + 2] << endl;
        }
    }

    /** 
     * @brief Function that receives an integer value and converts it to binary.
     * @param num Integer value to be converted into binary.
     * @param bits The max size of the returned binary value.
     * @returns a string containing the binary representation of the number received.
     */
    string IntToBin(int num, int bits = 8)
    {
        /** Base case: when there are no more bits to convert. */
        if (bits == 0)
        {
            return "";
        }
        
        /** Determines the current bit in binary. */
        int bit_current = num % 2;

        /** Recursive call to calculate the subsequent bits in binary. */
        string bit_subsequent = IntToBin(num / 2, bits - 1);

        return bit_subsequent + (bit_current == 0 ? '0' : '1');
    }

    /** 
     * @brief Main function used in encrypting and hiding an ASCII message inside the least significant bits (LSB) of a PPM image's pixels.
     * @param msg Message that will be stored inside the image.
     */
    void CodeMsg(string msg)
    {
        int t = msg.size(); /**> The number of characters in the message. */ 
        int chars[t]; /**> Array that stores the ASCII values of each of the message's characters. */

        /** Fills in the chars[] array. */
        for (int i = 0; i < t; ++i)
        {
            chars[i] = (int)msg[i];
        }

        /** Stores the binary value of the number of characters in the message. */
        string bin = IntToBin(t);

        /** Modification of the first 8 bits of the array of 'R', 'G' and 'B' values, which store the message's size. */
        for (int i = 0; i < 8 && i < size; ++i)
        {
            if (bin[i] == '1')
            {
                if (pixel_array[i] % 2 == 0)
                {
                    pixel_array[i]++;
                }
            }
            else
            {
                if (pixel_array[i] % 2 != 0)
                {
                    pixel_array[i]++;
                }
            }
        }

        /** Modifies the bits of the array of 'R', 'G' and 'B' values which will store the actual message. */
        int bit_index = 0; /**> Index for each of the message's bits. */
        for (int j = 0; j < t; ++j)
        {
            bin = IntToBin(chars[j]);
            for (int i = 0; i < 8 && (bit_index + 8) < size; ++i, ++bit_index)
            {
                if (bin[i] == '1')
                {
                    if (pixel_array[bit_index + 8] % 2 == 0)
                    {
                        pixel_array[bit_index + 8]++;
                    }
                }
                else
                {
                    if (pixel_array[bit_index + 8] % 2 != 0)
                    {
                        pixel_array[bit_index + 8]++;
                        if (pixel_array[bit_index + 8] == 255)
                        {
                            pixel_array[bit_index + 8]--;
                        }
                    }
                }
            }
        }
    }

    /** 
     * @brief Recursive function used to convert a binary value into an integer value. 
     * @param bin_num String containing the binary value that will be converted into an integer.
     * @param index The index of the string.
     * @returns the sum of the current and subsequent values acquired recursively.
     */ 
    int BinToInt(string bin_num, int index = 0)
    {
        /** Base case: if the index reaches the end of the binary string.  */
        if (index == bin_num.length())
        {
            return 0;
        }

        /** Recursive call to calculate the value of the current and subsequent binary digits. */
        int value_current = (bin_num[index] - '0') * pow(2, bin_num.length() - 1 - index);
        int value_subsequent = BinToInt(bin_num, index + 1);

        return value_current + value_subsequent;
    }

    /**
     * @brief Main function used in uncovering and decrypting an ASCII message inside the least significant bits (LSB) of a PPM image's pixels.
     */
    void DecodeMsg()
    {
        string bin_size; /**> String that stores the size of the message in binary. */

        /** Gets (in binary) the size of the message stored in the image from the first 8 bits of it's pixels' 'R', 'G' and 'B' values, previously stored in an array. */
        for (int i = 0; i < 8; ++i)
        {
            if (pixel_array[i] % 2 == 0)
            {
                bin_size.push_back('0'); /** Adds the character '0' to bin_size. */ 
            }
            else
            {
                bin_size.push_back('1'); /** Adds the character '1' to bin_size. */ 
            }
        }

        string bin_msg; /**> String that stores the ASCII message in binary. */
        int msg_size = BinToInt(bin_size); /**> Stores the size of the image as an integer value. */

        /** Gets (in binary) the message stored in the image, using the message's size and using the array of the pixels' 'R', 'G' and 'B' values. */
        for (int i = 8; i < 8 + (msg_size * 8); ++i)
        {
            if (pixel_array[i] % 2 == 0)
            {
                bin_msg.push_back('0'); /** Adds the character '0' to bin_msg. */ 
            }
            else
            {
                bin_msg.push_back('1'); /** Adds the character '1' to bin_msg. */ 
            }
        }

        string decoded_msg; /**> String that stores the completely decoded message. */
        
        /** Repeats the process below until every character of the message has been decoded and stored. */
        for(int j = 0; j < msg_size; ++j) 
        {   
            string bin_char; /**> Stores a binary value of a single character. */

            /** Gets 8 bits (or a single character) from the message in binary, then adds up so it does the same to the next bit (if there is a next bit). */
            for(int i = 0; i < 8; ++i) 
            {
                bin_char.push_back(bin_msg[i + (8 * j)]);
            }

            char single_char = BinToInt(bin_char); /**> Stores the decoded ASCII character as a char. */

            /** Pushes a new decoded character into the string that stores the message. */
            decoded_msg.push_back(single_char); 
        }
        cout << "\033[94mA mensagem escondida é: \033[0m" + decoded_msg << "\n";
    }
};

#endif
