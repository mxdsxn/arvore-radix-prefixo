#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

// Estrutura do No Radix
typedef struct NoRadix
{
  string chavePrefixo;
  vector<NoRadix *> filhos;
  bool raiz = false;
  bool finalFrase = false;
} No;

No *criaArvoreRadix();

string getPrefixo(string string1, string string2);

string removePrefixo(string prefixo, string stringCompleta);

bool comparaNo(No *nohA, No *nohB);

void sortFilhosNo(No *noh);

void imprimirArvore(No *noh, long int nivel = 0);

void imprimirBusca(No *noh, string prefixo);

bool buscar(No *noh, string fraseBusca, string defaultPrefixo);

bool buscarRaiz(No *noh, string fraseBusca, string defaultPrefixo);

bool buscarFilhos(No *noh, string fraseBusca, string defaultPrefixo);

void insere(No *arvore);

void busca(No *arvore);

void remove(No *arvore);

void imprime(No *arvore);

bool inserir(No *noh, string novaFrase);

bool inserirRaiz(No *noh, string novaFrase);

bool inserirFilhos(No *noh, string novaFrase);

bool remover(No *noh, string removeFrase);
