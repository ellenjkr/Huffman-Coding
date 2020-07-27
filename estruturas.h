#ifndef BASESTRUCTURES_H
#define BASESTRUCTURES_H

#include <string>
#include <iostream>

using namespace std;

struct Caracter{ // Um elemento da árvore
    int peso = 1; // Frequência inicia como 1
    string caracter = ""; // Caractere inicia vazio
    Caracter * direita = NULL; // Elemento da direita inicia nulo
    Caracter * esquerda = NULL; // Elemento da esquerda inicia nulo
};

struct Arvore{
    Caracter *raiz; // Árvore tem um Caracter como raiz
};

struct ElementoTabela{ // Elemento da tabela de caracteres
    string caracter; // Caracter
    string codigoBin; // Seu código binário
    int freq; // Sua frequência
};

#endif // BASESTRUCTURES_H
