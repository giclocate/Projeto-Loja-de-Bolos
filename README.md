# Loja de Bolo - Estruturas de Dados

Bem-vindo ao repositório do projeto "Loja de Bolo"! Este projeto tem como objetivo demonstrar a implementação de conceitos de estruturas de dados abordados na disciplina de Estrutura de Dados, utilizando a linguagem de programação C. As colaboradoras deste projeto são Giovanna Clócate e Kátia Rocha.

## Sumário

- [Introdução](#introdução)
- [Estruturas de Dados Implementadas](#estruturas-de-dados-implementadas)
  - [Lista Simplesmente Encadeada](#lista-simplesmente-encadeada)
  - [Lista Duplamente Encadeada](#lista-duplamente-encadeada)
  - [Lista Circular](#lista-circular)
  - [Fila](#fila)
  - [Pilha](#pilha)
- [Como Executar](#como-executar)
- [Colaboradoras](#colaboradoras)
- [Licença](#licença)

## Introdução

Este repositório contém a implementação de uma loja de bolo fictícia utilizando diversas estruturas de dados ensinadas na disciplina de Estrutura de Dados. Cada estrutura de dados é utilizada para resolver diferentes problemas e armazenar informações de forma eficiente.

## Estruturas de Dados Implementadas

### Lista Simplesmente Encadeada

A lista simplesmente encadeada é uma coleção de elementos onde cada elemento aponta para o próximo elemento da lista. Esta estrutura é útil para inserções e remoções frequentes de elementos em qualquer posição da lista.

### Lista Duplamente Encadeada

A lista duplamente encadeada é similar à lista simplesmente encadeada, mas cada elemento possui dois ponteiros: um apontando para o próximo elemento e outro apontando para o elemento anterior. Isso permite uma navegação bidirecional pela lista.

### Lista Circular

A lista circular é uma variação da lista encadeada onde o último elemento aponta para o primeiro elemento, formando um ciclo. Esta estrutura é útil para aplicações que necessitam de uma navegação contínua pelos elementos.

### Fila

A fila é uma estrutura de dados que segue o princípio FIFO (First In, First Out). Implementamos filas utilizando tanto vetores quanto apontadores. Na fila, os elementos são inseridos no final e removidos do início.

### Pilha

A pilha é uma estrutura de dados que segue o princípio LIFO (Last In, First Out). Assim como a fila, implementamos a pilha utilizando vetores e apontadores. Na pilha, os elementos são inseridos e removidos do topo.

## Como Executar

Para compilar e executar o projeto, siga os seguintes passos:

1. Clone o repositório:
   ```sh
   git clone https://github.com/seu-usuario/loja-de-bolo.git
   ```
2. Navegue até o diretório do projeto:
   ```sh
   cd loja-de-bolo
   ```
3. Compile os arquivos fonte:
   ```sh
   gcc -o loja_de_bolo main.c lista_simplesmente_encadeada.c lista_duplamente_encadeada.c lista_circular.c fila.c pilha.c -I.
   ```
4. Execute o programa:
   ```sh
   ./loja_de_bolo
   ```

## Colaboradoras

- Giovanna Clócate
- Kátia Rocha

## Licença

Este projeto está licenciado sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para obter mais informações.

---

Esperamos que você ache este projeto útil para entender e aplicar conceitos de estruturas de dados em C. Se tiver alguma dúvida ou sugestão, sinta-se à vontade para entrar em contato!
