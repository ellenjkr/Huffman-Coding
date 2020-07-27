#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <bits/stdc++.h>

using namespace std;

string leArquivo(string nomeArquivo){
    string linha;
    string texto;
    ifstream arquivo;
    arquivo.open(nomeArquivo);
    while (getline(arquivo, linha)){
        texto += linha; // Adiciona linha do arquivo à variável texto
    }
    arquivo.close();

    return texto;
}

string leArquivoComLinha(string nomeArquivo){
    string linha;
    string texto;
    ifstream arquivo;
    arquivo.open(nomeArquivo);
    while (getline(arquivo, linha)){
        texto += linha + "\n"; // Adiciona linha do arquivo à variável texto junto com quebra de linha
    }
    arquivo.close();

    return texto;
}

void escreveArquivo(string texto, string nomeArquivo){
    ofstream arquivo;
    nomeArquivo += ".txt";
    arquivo.open (nomeArquivo);
    arquivo << texto; // Escreve o conteúdo da variável texto no arquivo
    arquivo.close();
}




#endif // FILEMANAGER_H
