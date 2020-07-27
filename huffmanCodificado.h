#ifndef HUFFMANCODIFICADO_H
#define HUFFMANCODIFICADO_H
#include "huffmanGeral.h"

void constroiNoCodificado(TListaEncadeada<Caracter> & caracteres){ // Forma nó
    // Pega os dois primeiros elementos da lista de caracteres
    TElementoEnc<Caracter> * elemento1 = caracteres.inicio;
    TElementoEnc<Caracter> * elemento2 = caracteres.inicio->proximo;

    Caracter *filho1 = new Caracter; // Monta o filho da esquerda (cópia do elemento 1)
    filho1->peso = elemento1->dado.peso;
    filho1->direita = elemento1->dado.direita;
    filho1->esquerda = elemento1->dado.esquerda;
    filho1->caracter = elemento1->dado.caracter;

    Caracter *filho2 = new Caracter; // Monta o filho da direita (cópia do elemento 2)
    filho2->peso = elemento2->dado.peso;
    filho2->direita = elemento2->dado.direita;
    filho2->esquerda = elemento2->dado.esquerda;
    filho2->caracter = elemento2->dado.caracter;

    Caracter novoElemento; // Cria um novo elemento com dois filhos
    novoElemento.peso = filho1->peso + filho2->peso;
    novoElemento.esquerda = filho1;
    novoElemento.direita = filho2;

    insereFinalEnc(caracteres, novoElemento); // Adiciona novo elemento na lista
    // Remove os dois primeiros elementos da lista
    removeInicioEnc(caracteres);
    removeInicioEnc(caracteres);
}


Arvore constroiArvoreCodificado(TListaEncadeada<Caracter> & caracteres){
    while(retornaTamanho(caracteres) > 1){
        constroiNoCodificado(caracteres); // Constroi nós até a lista possuir só um elemento (raiz)
        ordenaCaracteres(caracteres); // Reordena a lista após inserir o elemento novo
    }
    Arvore arvore;
    arvore.raiz = &caracteres.inicio->dado; // Cria árvore
    return arvore;
}

void preencheTabelaCodificado(Caracter *raiz, string codigo, TListaEncadeada<ElementoTabela> &tabela){ // Percorre a árvore
    if(raiz == NULL){
        return;
    }
    if(raiz->direita == NULL and raiz->esquerda == NULL){ // Se encontrou uma folha
        ElementoTabela novo; // Cria um novo elemento para a tabela
        // Adiciona os valores da folha ao elemento da tabela
        novo.caracter = raiz->caracter;
        novo.codigoBin = codigo;
        novo.freq = raiz->peso;
        insereFinalEnc(tabela, novo);
        codigo = "";
    }
    // Percorre árvore por visitação pré-fixa
    preencheTabelaCodificado(raiz->esquerda, codigo + "0", tabela); // Para a esquerda adiciona um 0 ao código
    preencheTabelaCodificado(raiz->direita, codigo + "1", tabela); // Para a direita adiciona um 1 ao código
}

string geraCodificado(string texto, TListaEncadeada<ElementoTabela> tabela){
    string textoCodificado = "";
    TElementoEnc<ElementoTabela> *nav = tabela.inicio;
    for (int i = 0; i < texto.length(); ++i) {
        TElementoEnc<ElementoTabela> *nav = tabela.inicio; // Navegador para percorrer a tabela
        string caracter;
        caracter.push_back(texto[i]);
        while(nav->dado.caracter != caracter){ // Enquanto o caracter da tabela for diferente do caracter do texto
            nav = nav->proximo; // Próximo item da tabela
        }
        textoCodificado += nav->dado.codigoBin; // Quando encontrar o elemento adiciona seu código binário ao texto codificado
    }
    return textoCodificado;
}

string geraStringTabela(TListaEncadeada<ElementoTabela> tabela){ // Transforma a tabela em uma string
    string tabelaCodigos = "";
    for(TElementoEnc<ElementoTabela> *nav = tabela.inicio; nav != NULL; nav = nav->proximo){
        tabelaCodigos = tabelaCodigos + nav->dado.caracter + ": " + nav->dado.codigoBin + "\n";
    }
    return tabelaCodigos;
}

void codifica(string texto){ // Reúne funções de codificação
    TListaEncadeada<Caracter> caracteres;
    inicializaListaEnc(caracteres);
    separaCaracteres(caracteres, texto);
    ordenaCaracteres(caracteres);

    Arvore arvore = constroiArvoreCodificado(caracteres);
    string codigo = "";

    TListaEncadeada<ElementoTabela> tabelaCodigos;
    inicializaListaEnc(tabelaCodigos);
    preencheTabelaCodificado(arvore.raiz, codigo, tabelaCodigos);

    string textoCodificado = geraCodificado(texto, tabelaCodigos);
    string tabela = geraStringTabela(tabelaCodigos);
    string saida = tabela + "-\n" + textoCodificado;

    imprimeDados(texto, textoCodificado, tabelaCodigos, arvore);
    cout << endl << "Tamanho ASCII = " << texto.size()*8 << " bits" << endl;
    cout << endl << "Tamanho Codificado = " << textoCodificado.size() << " bits" << endl;
    cout << endl << "--------------------------------------" << endl;

    string nomeArquivo = "codificado";
    escreveArquivo(saida, nomeArquivo);
}

#endif // HUFFMANCODIFICADO_H
