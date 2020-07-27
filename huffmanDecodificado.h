#ifndef HUFFMANDECODIFICADO_H
#define HUFFMANDECODIFICADO_H

#include "huffmanGeral.h"

void preencheTabelaDecodificado(TListaEncadeada<ElementoTabela> &tabelaCodigos, string tabela){ // Preenche tabela de caracteres a partir de uma string da tabela
    string delimitador = "\n"; // Delimitador de linha
    string delimitador2 = ": "; // Delimitador para separar caracter do código binário
    size_t pos = 0;
    size_t pos2 = 0;
    string linha;
    string caracter;
    string codigo;
    while ((pos = tabela.find(delimitador)) != string::npos) {
        linha = tabela.substr(0, pos); // Separa a linha da tabela (string)
        pos2 = 0;
        while ((pos2 = linha.find(delimitador2)) != string::npos) {
            ElementoTabela novo; // Cria novo elemento para a tabela (lista encadeada)
            // Separa caracter do código binário e adiciona informações ao novo elemento
            novo.caracter = linha.substr(0, pos2);
            novo.codigoBin = linha.erase(0, pos2 + delimitador2.length());
            novo.freq = 0;
            insereFinalEnc(tabelaCodigos, novo); // Adiciona novo elemento na tabela (lista encadeada)
        }
        tabela = tabela.erase(0, pos + delimitador.length()); // Retira linha da tabela (string)
    }
    while ((pos = tabela.find(delimitador2)) != string::npos) { // Para a último linha da tabela
        ElementoTabela novo;
        novo.caracter = tabela.substr(0, pos);
        novo.codigoBin = tabela.erase(0, pos + delimitador2.length());
        insereFinalEnc(tabelaCodigos, novo);
    }
}

void constroiNoDecodificado(TElementoEnc<ElementoTabela> *elemento, string codigo, Caracter *raiz){
    if(codigo == ""){ // Se percorreu o código todo sai da função
        raiz->caracter = elemento->dado.caracter;
        return;
    }
    else{
        string direcao;
        direcao.push_back(codigo[0]); // Direção a ser seguida = primeiro caractere do código
        if(direcao == "0"){ // Se a direção for esquerda
            if(codigo.size() > 1){
                codigo = codigo.erase(0, 1); // Apaga o caractere do código
            }
            else{
                codigo = "";
            }
            if(raiz->esquerda == NULL){ // Se não tiver um filho na esquerda
                Caracter *esquerda = new Caracter; // Cria um novo filho
                raiz->esquerda = esquerda;
            }
            return constroiNoDecodificado(elemento, codigo, raiz->esquerda); // Parte recursiva, passa o filho da esquerda como raiz
        }
        else{ // Se a direção for direita
            if(codigo.size() > 1){
                codigo = codigo.erase(0, 1); // Apaga o caractere do código
            }
            else{
                codigo = "";
            }
            if(raiz->direita == NULL){ // Se não tiver um filho na direita
                Caracter *direita = new Caracter; // Cria um novo filho
                raiz->direita = direita;
            }
            return constroiNoDecodificado(elemento, codigo, raiz->direita); // Parte recursiva, passa o filho da direita como raiz
        }
    }
}

Arvore constroiArvoreDecodificado(TListaEncadeada<ElementoTabela> tabelaCodigos){
    Arvore arvore; // Cria árvore
    arvore.raiz = new Caracter;
    string codigo;

    TElementoEnc<ElementoTabela> *nav = tabelaCodigos.inicio; // Navegador para percorrer a tabela de códigos
    while(nav != NULL){
        codigo = nav->dado.codigoBin;
        constroiNoDecodificado(nav, codigo, arvore.raiz); // Passa o elemento da tabela, seu código e a raiz da árvore como parâmetros
        nav = nav->proximo; // Próximo item da tabela
    }
    return arvore;
}

string geraDecodificado(string codigo, string decodificado, Caracter *raiz, TListaEncadeada<ElementoTabela> &tabelaCodigos){ // Decodifica texto
    Caracter *no = raiz;
    if(codigo == "" or codigo == "\n"){ // Se percorreu o código inteiro
        return decodificado; // Sai da função
    }
    else{
        while(no->caracter == ""){ // Enquanto for um nó sem caractere ele percorre a árvore
            string caracter;
            caracter.push_back(codigo[0]); // Primeiro caractere do código
            if(caracter == "0"){ // Se for para a esquerda
               no = no->esquerda; // Nó passa a ser o da esquerda
               if(codigo.size() > 1){
                   codigo = codigo.erase(0, 1); // Apaga caractere do código
               }
               else{
                   codigo = "";
               }
            }
            else if(caracter == "1"){ // Se for para a direita
                no = no->direita; // Nó passa a ser o da direita
                if(codigo.size() > 1){
                    codigo = codigo.erase(0, 1); // Apaga caractere do código
                }
                else{
                    codigo = "";
                }
            }
            if(no->caracter != ""){ // Se o novo nó tiver um caracter
                TElementoEnc<ElementoTabela> *nav = tabelaCodigos.inicio; // Navegador para percorrer a tabela de códigos
                while(nav != NULL){
                    if(nav->dado.caracter == no->caracter){ // Se o caracter do navegador for o masmo do nó
                        nav->dado.freq++; // Aumenta a frequência do caracter na tabela
                    }
                    nav = nav->proximo; // Próximo item da tabela
                }
                decodificado = decodificado + no->caracter; // Adiciona o caracter do nó à variável decodificado
                return geraDecodificado(codigo, decodificado, raiz, tabelaCodigos); // Parte recursiva, percorre a árvore novamente
            }
        }
    }
}

void decodifica(string texto){ // Reúne funções de decodificação
    string tabela;
    separaTabelaTexto(texto, tabela); // Separa a tabela do texto em binário
    TListaEncadeada<ElementoTabela> tabelaCodigos; // Cria uma lista para armazenar os dados da tabela
    inicializaListaEnc(tabelaCodigos);
    preencheTabelaDecodificado(tabelaCodigos, tabela); // Transforma a string tabela em uma lista

    Arvore arvore = constroiArvoreDecodificado(tabelaCodigos); // Cria a árvore a partir da tabela

    string textoDecodificado = "";
    textoDecodificado = geraDecodificado(texto, textoDecodificado, arvore.raiz, tabelaCodigos); // Decodifica o texto

    imprimeDados(texto, textoDecodificado, tabelaCodigos, arvore); // Imprime os dados do texto
    cout << endl << "Tamanho Binario = " << texto.size() << " bits" << endl;
    cout << endl << "Tamanho Decodificado = " << textoDecodificado.size()*8 << " bits" << endl;
    cout << endl << "--------------------------------------" << endl;

    string nomeArquivo = "decodificado";
    escreveArquivo(textoDecodificado, nomeArquivo); // Salva a decodificação gerada
}

#endif // HUFFMANDECODIFICADO_H
