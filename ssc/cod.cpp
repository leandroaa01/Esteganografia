#include <bits/stdc++.h>
#include <filesystem>
#include "../include/Image.h"

using namespace std;
namespace fs = std::filesystem;

/**
 * @brief Reads a PPM image, then saves a copy with an ASCII message encoded in the least significant bit (LSB) of it's pixels.
 * @param argc
 * @param argv
 */
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Uso: " << argv[0] << " <nome_do_arquivo>" <<" " <<"nome_do_arquivo_resultante" << endl;
        return 1;
    }



    string img_name = argv[1];
    string file_name = argv[2];  
    string msg; /**> Stores the message that will be stored inside the image. */
    Image img; /**> Stores the image by the parameters of the Image class. */
    ofstream file; 
    string img_content; /**> Stores in a string the contents of the PPM image. */

 // /** Tests if the file is in fact a P3/PPM file by looking at it's extension. */
 if(!img.ExtensionCheck(img_name, ".ppm")) 
    {       
        cout << "\033[1;31mTipo de arquivo de leitura inválido.: "+img_name +"\033[0m\n";
        return 1;
    }
    if(!img.ExtensionCheck(file_name, ".ppm")) 
    {       
        cout << "\033[1;31mTipo de arquivo de saida inválido.: "+file_name +"\033[0m\n";
        return 1;
    }
    /** Tests if the ReadPPM() function was successful, stops the encoding process otherwise. */
    if (img.ReadPPM(img_name))
    {
        /** The message is inputed. */
        getline(cin, msg);
        /** The message is encoded. */
        img.CodeMsg(msg);
    }
    else
    {
        cout << "\033[1;31mArquivo original não existe.\033[0m\n";
        return 1;
    }
 /** Tests if the a file with the same name already exists inside the source folder. */
    if (fs::exists(file_name))
    {
        char overwrite = 'n'; /**> Stores the choice to overwrite. The answer is 'no' by default. */

        cout << "O arquivo " << file_name << " já existe. Deseja sobrescrevê-lo? (s/n): ";
        cin >> overwrite;

        /** Tests if the answer was 'no', then stops the encoding process if true. */
        if (overwrite != 's' && overwrite != 'S')
        {
            std::cout << "\033[1;31mArquivo resultante já existe. Operação cancelada.\033[0m\n";
            return 1;
        }
    }

    img_content = img.CreatePPM();

    /** Tests if the file is open, if true, creates the PPM file and stores the modified content in it. */
    file.open(file_name);
    if (file.is_open())
    {
        file << img_content;
        file.close();
        cout << "\033[1;32mImagem gerada com sucesso: " << file_name << "\033[0m" << endl;
       
    } 
    else 
    {
        cout << "Erro ao criar o arquivo." << endl;
    }

    return 0;
}