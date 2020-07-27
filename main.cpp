#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "listaEncadeada.h"

#include "huffmanCodificado.h"
#include "huffmanDecodificado.h"

using namespace std;

int subMenu(){
    int escolha = 0;
    while(escolha != 2){
        cout << endl << "O que deseja fazer?" << endl << endl;
        cout << "1 -> Retornar ao menu principal" << endl;
        cout << "2 -> Sair" << endl;
        cout << endl << "Escolha: ";
        cin >> escolha;

        if(escolha == 1){
            return 0;
        }
        else if (escolha == 2){
            return 3;
        }
        system("cls");
    }
}

void menu(){
    int escolha = 0;
    while(escolha != 3){
        cout << "O que deseja fazer?" << endl << endl;
        cout << "1 -> Gerar Texto Codificado" << endl;
        cout << "2 -> Gerar Texto Decodificado" << endl;
        cout << "3 -> Sair" << endl;
        cout << endl << "Escolha: ";
        cin >> escolha;

        if(escolha == 1){
            system("cls");
            string texto = leArquivo("texto3.txt");
            // texto = letrasMinusculas(texto);
            codifica(texto);
            escolha = subMenu();
        }
        else if(escolha == 2){
            system("cls");
            string texto = leArquivoComLinha("codificado.txt");
            decodifica(texto);
            escolha = subMenu();
        }
        system("cls");
    }
}

int main()
{
    menu(); // Menu principal
    return 0;
}
