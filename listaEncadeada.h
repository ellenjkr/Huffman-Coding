#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H

#include <iostream>
#include <string>

#include "estruturas.h"

using namespace std;

template <typename Tipo>
struct TElementoEnc{
    Tipo dado;
    TElementoEnc<Tipo> *proximo;
};


template <typename Tipo>
struct TListaEncadeada{
    TElementoEnc<Tipo> *inicio;
};

template <typename Tipo>
void insereListaEncVazia(TListaEncadeada<Tipo> &L, Tipo D){
    L.inicio = new TElementoEnc<Tipo>;
    L.inicio->dado = D;
    L.inicio->proximo = NULL;
}


template <typename Tipo>
void inicializaListaEnc(TListaEncadeada<Tipo> *L){
    L->inicio = NULL;
}

template <typename Tipo>
void inicializaListaEnc(TListaEncadeada<Tipo> &L){
    L.inicio = NULL;
}

template <typename Tipo>
void depurarListaEnc(TListaEncadeada<Tipo> L){
    cout << "Debug Linked-list!" << endl;
    int posicao = 0;
    for(TElementoEnc<Tipo> *nav = L.inicio; nav != NULL; nav = nav->proximo){
        cout << "Elemento[" << posicao << "]: " << nav->dado.caracter << " " << nav->dado.codigoBin << endl;
        posicao++;
    }
}


template <typename Tipo>
void insereFinalEnc(TListaEncadeada<Tipo> &L, Tipo D){
    if(L.inicio == NULL){ //Vazia
        insereListaEncVazia(L, D);
    }
    else{
        TElementoEnc<Tipo> * nav = L.inicio;
        while(nav->proximo != NULL){
           nav = nav->proximo;
        }

        TElementoEnc<Tipo> *novo = new TElementoEnc<Tipo>;
        novo->dado = D;
        novo->proximo = nav->proximo;
        nav->proximo = novo;
    }
}


template <typename Tipo>
void insereInicioEnc(TListaEncadeada<Tipo> &L, Tipo D){
    if(L.inicio == NULL){ //Vazia
        insereListaEncVazia(L, D);
    }
    else{
        TElementoEnc<Tipo> *novo = new TElementoEnc<Tipo>;
        novo->dado = D;
        novo->proximo = L.inicio;
        L.inicio = novo;
    }
}


template <typename Tipo>
void inserePosicaoEnc(TListaEncadeada<Tipo> &L, Tipo D, int pos){
    TElementoEnc<Tipo> *novo = new TElementoEnc<Tipo>;
    if(pos == 0){
        insereInicioEnc(L, D);
    }
    else if(pos < 0){
        throw "Erro: posicao negativa";
    }
    else{
        int cont = 0;
        novo->dado = D;
        TElementoEnc<Tipo> * nav = L.inicio;
        while(nav->proximo!=NULL){
           nav = nav->proximo;
           cont++;
        }
        if(pos == cont+1){
            insereFinalEnc(L, D);
        }
        else if(pos > cont+1){
            throw "Erro: Lista menor do que a posicao passada";
        }
        else{
            cont = 0;
            nav = L.inicio;
            while(cont < pos -1){
                nav = nav->proximo;
                cont++;
            }
            novo->proximo = nav->proximo;
            nav->proximo = novo;
        }
    }
}


template <typename Tipo>
void removeInicioEnc(TListaEncadeada<Tipo> &L){
    if(L.inicio == NULL){
        throw "Erro: Lista vazia";
    }
    else{
        TElementoEnc<Tipo> *excluir = L.inicio;
        L.inicio = L.inicio->proximo;
        delete excluir;
    }
}


template <typename Tipo>
void removeFinalEnc(TListaEncadeada<Tipo> &L){
    if(L.inicio == NULL){
        throw "Erro: Lista vazia";
    }
    else{
        if(L.inicio->proximo == NULL){ // Se houver só um elemento
            removeInicioEnc(L);
        }
        else{
            TElementoEnc<Tipo> *excluir = L.inicio;
            while(excluir->proximo != NULL){
                excluir = excluir->proximo;
            }
            TElementoEnc<Tipo> *nav = L.inicio;
            while(nav->proximo != excluir){
                nav = nav->proximo;
            }
            nav->proximo = NULL;
            delete excluir;
        }
    }
}


template <typename Tipo>
void removePosicaoEnc(TListaEncadeada<Tipo> &L, int pos){
    if(L.inicio == NULL){
        throw "Erro: Lista vazia";
    }
    else{
        if(pos == 0){
            removeInicioEnc(L);
        }
        else{
            int cont = 0;
            TElementoEnc<Tipo> * nav = L.inicio;
            while(nav->proximo!=NULL){
               nav = nav->proximo;
               cont++;
            }
            if(pos == cont){
                removeFinalEnc(L);
            }
            else if(pos > cont){
                throw "Erro: Lista menor do que a posicao passada";
            }
            else if(pos < 0){
                throw "Erro: Posicao negativa";
            }
            else{
                cont = 0;
                nav = L.inicio;
                while(cont < pos -1){
                    nav = nav->proximo;
                    cont++;
                }
                TElementoEnc<Tipo> *excluir = nav->proximo;
                nav->proximo = nav->proximo->proximo;
                delete excluir;
            }
        }
    }
}


bool verificaPertence(TListaEncadeada<Caracter> L, Caracter valor){
    if(L.inicio != NULL){
        TElementoEnc<Caracter> *nav = L.inicio;
        if(nav->dado.caracter == valor.caracter){
            return true;
        }
        while(nav->proximo != NULL){
            nav = nav->proximo;
            if(nav->dado.caracter == valor.caracter){
                return true;
            }
        }
        return false;
    }
    else{
        return false;
    }
}


template <typename Tipo>
Tipo obtemItem(TListaEncadeada<Caracter> L, int pos){
    if(L.inicio != NULL){
        if(pos < 0){
            throw "Erro: Posicao negativa";
        }
        TElementoEnc<Tipo> *nav = L.inicio;
        int cont = 0;
        while(nav->proximo != NULL){
            nav = nav->proximo;
            cont++;
        }
        if(pos > cont){
            throw "Erro: Lista menor que a posicao passada";
        }
        else{
            nav = L.inicio;
            cont = 0;
            while(cont < pos){
                nav = nav->proximo;
                cont++;
            }
            return nav->dado;
        }
    }
    else{
        throw "Erro: Lista vazia";
    }
}


template <typename Tipo>
int retornaIndiceEnc(TListaEncadeada<Caracter> &lista, Caracter item){
    if(lista.inicio != NULL){
        if(verificaPertence(lista, item) == true){
            int cont = 0;
            TElementoEnc<Tipo> *nav = lista.inicio;
            do{
                if(nav->dado.caracter == item.caracter){
                    return cont;
                }
                cont++;
                nav = nav->proximo;
            } while(nav!= NULL);
        }
        else{
            return -1;
        }
    }
    else{
        throw "Lista vazia";
    }
}

template <typename Tipo>
int retornaTamanho(TListaEncadeada<Tipo> &lista){
    TElementoEnc<Tipo> *nav = lista.inicio;
    int cont = 0;
    while(nav != NULL){
        cont ++;
        nav = nav->proximo;
    }
    return cont;
}


#endif // LISTAENCADEADA_H
