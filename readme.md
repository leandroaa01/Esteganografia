[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Y7Cial8A)
# Esteganografia

Esteganografia é o nome dado às técnicas usadas para esconder a existência de uma mensagem em outra mensagem ou artefato. Veja que é diferente do processo de criptografia, que procura ocultar o significado da mensagem (sabe-se que há uma mensagem ali, só não se sabe o seu conteúdo). Na esteganografia, quem tem acesso ao artefato onde a mensagem está escondida nem sabe que há uma mensagem ali.

A esteganografia é utilizada há muito, muito tempo. Uma das primeiras menções data de 440 A.C., na Grécia Antiga. Desde então, inúmeras técnicas foram surgindo para esconder mensagens, seja em movimentos específicos de olhos, das mãos... (em jogos de baralho, por exemplo), em mensagens cifradas (em cartas entre espiões, por exemplo) até o uso mais "moderno"... com arquivos digitais.

Em arquivos digitais, pode haver mensagens codificadas em arquivos de música, de texto... e imagens. É esse o caso do presente trabalho. Você irá esconder mensagens em um arquivo de imagem. A "olho-nú" não haverá diferença alguma entre a nova imagem (com a mensagem inserida) e a imagem original (sem a mensagem). Só quem souber que há uma mensagem inserida e qual técnica foi utilizada poderá decodificar tua mensagem.

Para ter uma visão geral sobre esteganografia, dê uma olhada no vídeo: https://www.youtube.com/watch?v=7HhoXxyq4aM

É bué fixe, malta! 😉

## Uso do bit menos significativo

Uma das técnicas mais simples e utilizadas em esteganografia digital consiste em utilizar o bit menos significativo dos bytes que compõe o arquivo para inserir uma pequena mudança (de 1 ou 2 bits) em cada byte. Em imagens, essa alteração normalmente não é perceptível.

Por exemplo, digamos que queiramos esconder o texto "TI" em uma imagem. Esse texto é uma sequência de 2 caracteres, cada um com seu respectivo valor numérico: 84 e 73, que correspondem respectivamente aos valores do `T` e do `I` na tabela ASCII. Em binário, esses valores são:
* T: 84 = `0101 0100`
* I: 73 = `0100 1001`

No total, temos 2 x 8 = 16 bits. Precisamos, então, "esconder" esses 16 bits nos valores dos pixels da imagem para esconder a mensagem.

Em uma imagem PPM, cada pixel é representado por três valores, que correspondem aos componentes RGB do pixel. Então, se inserirmos cada bit da mensagem no lugar do bit menos significativo (ou seja, no último bit) dos valores do pixel, a imagem não sofrerá grandes alterações e, certamente, ninguém perceberá que há uma mensagem codificada ali.

Para exemplificar, digamos que o componente RED de um pixel tenha valor 218, em binário 11011010. Se inserirmos o "1" no seu bit menos significativo (o último), ele ficará com o valor 11011011, em decimal 219. Certamente, ninguém vai notar em uma imagem que a tonalidade do vermelho de um pixel mudou de 218 para 219... mas você... que sabe que há uma mensagem naquela imagem, vai poder extrair o conteúdo dela juntando os bits espalhados nos pixels.

Além dos caracteres da mensagem propriamente dita, uma informação importante que devemos inserir na codificação é o tamanho da mensagem, ou seja quantos caracteres vão ser "escondidos". Isso é importante para que o processo de decodificação saiba quando "parar". O tamanho da mensagem deve ser codificada da mesma forma que os caracteres, espalhando seus bits nos valores dos pixels. Vamos considerar nesta atividade que o **tamanho das mensagens seja de no máximo 255 caracteres**. Ou seja, o tamanho irá ocupar 8 bits, espalhados obrigatoriamente nos 8 valores iniciais dos pixels.

Assim, uma imagem PPM de tamanho 4 x 2 consiguiria armazenar a mensagem "TI", pois a imagem teria 8 pixels (4 x 2), cada um com 3 valores (RGB), totalizando 24 valores. Desses, os 8 primeiros conterão o tamanho da mensagem (valor 2), os 8 valores seguintes terão o 1º caractere (`T`) e os 8 valores seguintes o 2º caractere (`I`).

Considere, por exemplo, a imagem 4 x 2 abaixo e os valores dos bits da mensagem "TI" apresentados anteriormente:

```ppm
P3
4 2
255
178 178 178   178 178 111   178 111 178   111 178 178
111 111 178   111 178 111   178 111 111   111 111 111
```

A nova imagem codificada terá o conteúdo a seguir. Os 8 primeiros valores contêm a quantidade de caracteres (2 = `0000 0010`), os 8 seguintes contêm o caractere `T` (84 = `0101 0100`) e os 8 seguintes o caractere `I` (73 = `0100 1001`).

```ppm
P3
4 2
255
178 178 178   178 178 110   179 110 178   111 178 179
110 111 178   110 178 111   178 110 111   110 110 111
```

Veja que o valor 178 vale em binário 1011 0010. Assim, sempre que um 0 for inserido no seu bit menos significativo, ele continuará valendo 1011 0010, pois seu último bit já tem o valor 0. Porém, quando um 1 for inserido, ele passa a ser 1011 0011, ou seja passará a valer 179. A mesma lógica serve para o valor 111, que em binário vale 0110 1111. Quando o 1 for inserido no seu bit menos significativo, ele continuará com o mesmo valor porque seu último bit já é 1. Porém, quando o 0 for inserido, seu binário passará a ser 0110 1110, que vale 110.

Para extrair a mensagem, basta percorrer inicialmente os 8 primeiros valores da imagem para saber quantos caracteres serão extraídos. Em seguida, os valores seguintes (8 x quantidade de caracteres) serão consultados, de forma a construir, a cada 8 valores, a sequência de caracteres da mensagem.

## Manipulando bits

Existem operadores próprios para manipular bits, como `&`, `|`, `^`, `~`, `<<` e `>>`. Porém, o presente projeto não requer *obrigatoriamente* a utilização desses operadores. Há uma alternativa simples (porém, menos eficiente) para tratar a manipulação de bits. Para isso é preciso conhecer as seguintes características da representação de valores inteiros em binário:
1. Os números em binário que terminam com 0 são necessariamente par (ex: 1**0** => 2, 10001**0** => 34, 101001**0** => 82);
1. Os números em binário que terminam com 1 são necessariamente ímpar (ex: 10**1** => 5, 1101**1** => 27, 101 101**1** => 91);
1. Ao multiplicar um número por 2, o resultado será os bits do número deslocados uma posição à esquerda (ex: 5 => **101**, logo 2 * 5 = 10 => **101**0).
1. Ao dividir um número por 2, o resultado (considerando a parte inteira) será os bits do número deslocados uma posição à direita (ex: 27 => **1101**1, logo 27 / 2 = 13 => **1101**).

Com essas características em mente, é possível realizar as operações com os bits necessárias para essa atividade. Por exemplo, na codificação da mensagem, será necessário consultar os bits de um caractere para inseri-los nos valores dos pixels da imagem. Para consultar o último bit (o menos significativo), basta saber se ele é par (termina com 0) ou ímpar (termina com 1). Para consultar o bit seguinte, basta deslocar os bits para direita, dividindo o valor por 2 e testar novamente se o resultado é par ou ímpar... e assim por diante até consultar todos os 8 bits do caractere.

Por exemplo, digamos que você vai codificar o caractere `A`, que vale 65 (`0100 0001`). Não precisa saber qual a codificação binária dele para saber qual o último bit. O resto da divisão de 65 por 2 vai dizer se é `0` (se ele for par) ou `1` (se for ímpar). Ou seja, o resto da divisão por 2 já é o último bit!

Para saber o bit seguinte, você desloca os bit para a direita dividindo o valor por 2 (divisão inteira), o que resulta em 32 (`0010 0000`), e testa novamente o último bit. Como 32 é par, o último bit é 0. Depois, divide por 2 novamente, resultando 16, cujo último bit é novamente 0... e assim por diante. Desta forma, você poderá consultar os valores de todos os bits.

Na decodificação da mensagem, o processoé inverso. Será necessário consultar os últimos bits dos valores dos pixels da imagem para construir o valor binário do caractere. Novamente, para consultar o último bit (menos significativo), basta verificar se o número é par ou ímpar. O código do caractere vai sendo construído com o 1º bit, depois desloca esse bit para a esquerda multiplicando-o por 2, para inserir o 2º bit, depois o 3º... e assim por diante até inserir todos os 8 bits do caractere.

Por exemplo, digamos que os pixels tenham os seguintes valores:
```
104 105 104   104 104 104   104 105 104 ...
```

Você precisa consultar o último bit dos valores nos pixels e construir o caractere correspondente. Como o primeiro valor dos pixels (104) é par, seu último bit é `0`. O valor seguinte (105) é ímpar, logo seu último bit é `1`. O seguinte (104) é `0`, depois `0`, `0`, `0`, `0` e por fim, no oitavo valor, `1`. Essa sequência resulta `0100 0001`, que vale 65, ou seja o caractere `A`. Para construir esse caractere, consulta-se inicialmente o últimmo bit do primeiro valor nos pixels (`0`), depois multiplica-se o resultado por 2 e insere o último bit do segundo valor nos pixels (`01`). Depois, multiplica-se por 2 e insere o último bit do terceiro valor (`010`), depois o quarto (`0100`), quinto (`01000`)... até o oitavo (`01000001`).

**Recomendação**: escreva funções para realizar essas tarefas e teste-as antes de iniciar a manipulação de imagem. Só depois que as funções estiverem funcionando corretamente que você deve passar para tarefas que as utilizam.


## O programa a ser desenvolvido

No presente projeto, você deve desenvolver **dois programas**: um para codificar uma mensagem em uma imagem e outro para extrair uma mensagem de uma imagem. Os dois programas devem fazer uso de um "código compartilhado", útil a ambos os programas.

Como são dois programas diferentes e ainda tem código compartilhado entre eles, você terá mais de um arquivo `.cpp`. Você terá, pelo menos:
* um arquivo `.cpp` com a função `main()` do programa de **codificação**;
* um arquivo `.cpp` com a função `main()` do programa de **decodificação**;
* um ou mais arquivos `.cpp` com classes, struct e funções para manipulação das imagens, de bits e de mensagens. Os recursos nesses arquivos devem/podem ser usados pelos dois `.cpp` anteriores.

Além disso, com a função `main()` em arquivos diferentes, a compilação de cada um dos programas (codificação e decodificação) deve ser feita de forma separada.

### Programa de codificação

O programa que codifica a mensagem deverá adotar o seguinte modo de funcionamento:
1. O programa deverá receber como argumento 2 nomes de arquivos. O primeiro será o arquivo da imagem original (onde a mensagem será inserida) e o segundo será o arquivo da imagem resultante (contendo a mensagem).
1. Se o arquivo da imagem original não existir, o programa deverá mostrar uma mensagem de erro ("arquivo original não existe") e parar.
1. Se o arquivo da imagem resultante existir, o programa deverá informar que o arquivo já existe e perguntar se poderá sobreescrevê-lo. Se o usuário informar que "não", o programa deverá mostrar uma mensagem de erro ("arquivo resultante já existe") e parar.
1. Se não parar em nenhum dos casos anteriores, o programa deverá pedir ao usuário que digite uma mensagem em uma linha (pode haver espaços em branco) com no máximo 255 caracteres. Se o usuário digitar mais que isso, a mensagem será cortada até esse limite.
1. Em seguida, o programa deverá gerar uma nova imagem com a mensagem inserida (ou sobreescrevê-la, se já existir e o usuário tiver confirmado que pode sobreescrever).

### O programa de decodificação

O programa que decodifica a mensagem deverá adotar o seguinte modo de funcionamento:
1. O programa deverá receber como argumento apenas o nome do arquivo da imagem com a mensagem codificada.
1. Se o arquivo não existir, o programa deverá mostrar uma mensagem de erro ("arquivo não existe") e parar.
1. Em seguida, o programa deverá ler a mensagem na imagem e imprimi-la no terminal.


## Critérios de correção

**Funcionalidades**

* Argumentos em linha de comando
    * os programas lêem argumentos passados da linha de comando?
* Leitura do arquivo de imagem
    * os programas lêem arquivos PPM P3 de qualquer tamanho?
* Gravação do arquivo de imagem
    * a gravação do arquivo com a mensagem codificada é realizada de forma adequada?
* Codificação
    * a mensagem é codificada como especificado?
* Decodificação
    * a mensagem é decodificada como especificado?

**Código**

* Classes
    * Classes são especificadas usando os arquivos `.h` e `.cpp` adequadamente?
    * Nas classes, há atributos e métodos, alguns privados outros públicos?
* Alocação dinâmica
    * Utilizou-se alocação dinâmica de forma adequada?
    * Tomou-se cuidado para desalocar o que não era mais útil?
* Organização e documentação
    * O código foi devidamente documentado (seguindo o modelo de documentação no código existente)?
    * O código segue um padrão de identação, nomenclatura e organização?


