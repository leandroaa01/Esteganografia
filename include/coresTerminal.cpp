#include <iostream>

/*
Abaixo está um exemplo completo em C++ que demonstra todas as cores e estilos 
de texto possíveis no terminal usando sequências de escape ANSI. 
O exemplo cobre cores de texto, cores de fundo e várias formatações de texto.
*/
int main() {
    // Texto sem cor ou estilo
    std::cout << "Texto padrão\n";

    // Cores de Texto
    std::cout << "\033[30mTexto Preto\033[0m\n";
    std::cout << "\033[31mTexto Vermelho\033[0m\n";
    std::cout << "\033[32mTexto Verde\033[0m\n";
    std::cout << "\033[33mTexto Amarelo\033[0m\n";
    std::cout << "\033[34mTexto Azul\033[0m\n";
    std::cout << "\033[35mTexto Magenta\033[0m\n";
    std::cout << "\033[36mTexto Ciano\033[0m\n";
    std::cout << "\033[37mTexto Branco\033[0m\n";
    std::cout << "\033[90mTexto Cinza Escuro\033[0m\n";
    std::cout << "\033[91mTexto Vermelho Claro\033[0m\n";
    std::cout << "\033[92mTexto Verde Claro\033[0m\n";
    std::cout << "\033[93mTexto Amarelo Claro\033[0m\n";
    std::cout << "\033[94mTexto Azul Claro\033[0m\n";
    std::cout << "\033[95mTexto Magenta Claro\033[0m\n";
    std::cout << "\033[96mTexto Ciano Claro\033[0m\n";
    std::cout << "\033[97mTexto Branco Claro\033[0m\n";

    // Cores de Fundo
    std::cout << "\033[40mFundo Preto\033[0m\n";
    std::cout << "\033[41mFundo Vermelho\033[0m\n";
    std::cout << "\033[42mFundo Verde\033[0m\n";
    std::cout << "\033[43mFundo Amarelo\033[0m\n";
    std::cout << "\033[44mFundo Azul\033[0m\n";
    std::cout << "\033[45mFundo Magenta\033[0m\n";
    std::cout << "\033[46mFundo Ciano\033[0m\n";
    std::cout << "\033[47mFundo Branco\033[0m\n";
    std::cout << "\033[100mFundo Cinza Escuro\033[0m\n";
    std::cout << "\033[101mFundo Vermelho Claro\033[0m\n";
    std::cout << "\033[102mFundo Verde Claro\033[0m\n";
    std::cout << "\033[103mFundo Amarelo Claro\033[0m\n";
    std::cout << "\033[104mFundo Azul Claro\033[0m\n";
    std::cout << "\033[105mFundo Magenta Claro\033[0m\n";
    std::cout << "\033[106mFundo Ciano Claro\033[0m\n";
    std::cout << "\033[107mFundo Branco Claro\033[0m\n";
    
    // Estilos de Texto
    std::cout << "\033[1mTexto Negrito\033[0m\n";
    std::cout << "\033[2mTexto Escurecido\033[0m\n";
    std::cout << "\033[3mTexto Itálico\033[0m\n";
    std::cout << "\033[4mTexto Sublinhado\033[0m\n";
    std::cout << "\033[5mTexto Piscante\033[0m\n";
    std::cout << "\033[7mTexto Invertido\033[0m\n";
    std::cout << "\033[8mTexto Oculto\033[0m\n";
    std::cout << "\033[9mTexto Riscado\033[0m\n";
    std::cout << "\033[10m(Desativado)\033[0m\n";
    std::cout << "\033[11m(Desativado)\033[0m\n";
    std::cout << "\033[12m(Desativado)\033[0m\n";
    std::cout << "\033[13m(Desativado)\033[0m\n";
    std::cout << "\033[14m(Desativado)\033[0m\n";
    std::cout << "\033[15m(Desativado)\033[0m\n";

    // Cores e Estilos Combinados
    std::cout << "\033[1;31mTexto Negrito Vermelho\033[0m\n";
    std::cout << "\033[4;32mTexto Sublinhado Verde\033[0m\n";
    std::cout << "\033[7;33mTexto Invertido Amarelo\033[0m\n";
    std::cout << "\033[1;34;47mTexto Negrito Azul com Fundo Branco\033[0m\n";
    std::cout << "\033[3;35;46mTexto Itálico Magenta com Fundo Ciano\033[0m\n";
    std::cout << "\033[4;36;43mTexto Sublinhado Ciano com Fundo Amarelo\033[0m\n";

    return 0;
}
