#ifndef CARACTERSMANAGER_H
#define CARACTERSMANAGER_H

#include <string>
#include<algorithm>
#include "listaEncadeada.h"

using namespace std;

void separaCaracteres(TListaEncadeada<Caracter> &caracteres, string texto){ // Separa os caracteres individualmente
    for (int i = 0; i < texto.length(); ++i) {
        Caracter letra; // Cria um caracter
        letra.caracter = texto[i]; // Adiciona o símbolo do texto à variável caracter
        if(verificaPertence(caracteres, letra) == true){ // Verifica se esse símbolo já está na lista
            TElementoEnc<Caracter> *nav = caracteres.inicio;
            do{
                if(nav->dado.caracter == letra.caracter){
                    nav->dado.peso++; // Se já está, aumenta a frequência
                }
                nav = nav->proximo;
            } while(nav != NULL);
        }
        else{
             insereFinalEnc(caracteres, letra); // Caso contrário, adiciona na lista
        }
    }
}

void ordenaCaracteres(TListaEncadeada<Caracter> &caracteres){ // Ordena a lista de caracteres por ordem de frequência
    TElementoEnc<Caracter> *nav = caracteres.inicio;
    TElementoEnc<Caracter> *nav2 = caracteres.inicio;
    int cont = 0;

    if(retornaTamanho(caracteres) > 1){
        while(nav2 != NULL){ // Bubble sort
            while(nav != NULL){
                if(nav->proximo != NULL and nav->proximo->dado.peso < nav->dado.peso){
                    Caracter temp = nav->dado;
                    nav->dado = nav->proximo->dado;
                    nav->proximo->dado = temp;
                }
                cont++;
                nav = nav->proximo;
            }
            cont = 0;
            nav = caracteres.inicio;
            nav2 = nav2->proximo;
        }
    }
}

void separaTabelaTexto(string &texto, string &tabela){ // Separa a tabela do texto codificado para realizar a decodificação
    string delimitador = "\n-\n"; // Utiliza um delimitador
    size_t pos = 0;
    while ((pos = texto.find(delimitador)) != string::npos) { // Procura o delimitador no texto
        tabela = texto.substr(0, pos); // inicio até o delimitador
        texto = texto.erase(0, pos + delimitador.length()); // deimitador até o final
    }
    texto.erase(remove(texto.begin(), texto.end(), '\n'), texto.end());
}

string letrasMinusculas(string texto){
    transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    return texto;
}

#endif // CARACTERSMANAGER_H
