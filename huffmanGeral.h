#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "listaEncadeada.h"
#include "caractersManager.h"
#include "fileManager.h"
#include <sstream>
#include <iostream>

using namespace std;

// Visitação Pré-Ordem
void preOrdem(Caracter *raiz){ // Primeiro raiz, depois subarvore da esquerda e depois da direita
    if(raiz == NULL){
        return;
    }
    if(raiz->direita == NULL and raiz->esquerda == NULL){ // Se for uma folha
        cout << "\t" << raiz->caracter << endl;
    }
    preOrdem(raiz->esquerda);
    preOrdem(raiz->direita);
}

void imprimeTabelaCodigos(TListaEncadeada<ElementoTabela> tabela){
    cout << "--------------------------------------" << endl;
    cout << "\tTABELA DE CARACTERES:" << endl << endl;
    for(TElementoEnc<ElementoTabela> *nav = tabela.inicio; nav != NULL; nav = nav->proximo){
        cout << "\t" << nav->dado.caracter << ": " << nav->dado.codigoBin << "  |  " << nav->dado.freq << endl;
    }
    cout << "--------------------------------------" << endl;
}

void imprimeDados(string textoOriginal, string textoAlterado, TListaEncadeada<ElementoTabela> tabelaCodigos, Arvore arvore){
    cout << "\n\tTEXTO ORIGINAL: " << endl << endl << textoOriginal << endl << endl;
    imprimeTabelaCodigos(tabelaCodigos);
    cout << endl << "Arvore em Visitacao Pre-fixa" << endl << endl;
    preOrdem(arvore.raiz);
    cout << endl << "--------------------------------------" << endl;
    cout << endl << "TEXTO (DE)CODIFICADO: " << endl << endl << textoAlterado << endl;
    cout << endl << "--------------------------------------" << endl;
}

#endif // HUFFMAN_H
