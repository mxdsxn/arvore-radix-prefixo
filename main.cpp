#include "radix.hpp"

int main()
{
  No *arvore = criaArvoreRadix();

  
  inserir(arvore, "montar mesa quadrada com vaso em cima");
  inserir(arvore, "montar mesa quadrada");
  inserir(arvore, "montar mesa");
  inserir(arvore, "montar mesa redonda");
  inserir(arvore, "");
  inserir(arvore, "montar");
  inserir(arvore, "montaria");
  inserir(arvore, "montar mesa quadrada com vaso embaixo");
  inserir(arvore, "fazer massa italiana rosa");
  inserir(arvore, "faz lua");
  inserir(arvore, "assistir shrek 2");
  inserir(arvore, "faz");
  inserir(arvore, "fazer bolo");
  inserir(arvore, "fazer pao");
  inserir(arvore, "faz sol");
  inserir(arvore, "fazer massa italiana");
  inserir(arvore, "fazer massa");
  inserir(arvore, " quadrada");
  inserir(arvore, "fazer massa italiana");
  inserir(arvore, "fazer massa");
  inserir(arvore, " redonda");
  inserir(arvore, " ");
  inserir(arvore, " quadrada rosa");
  inserir(arvore, "fazer bolo");
  inserir(arvore, "fazer pao");
  inserir(arvore, "faz sol");
  inserir(arvore, "montar mesa");
  inserir(arvore, "fazer massa italiana rosa");
  inserir(arvore, "montar mesa redonda");
  inserir(arvore, "");
  inserir(arvore, "faz lua");
  inserir(arvore, "montar");
  inserir(arvore, "assistir shrek 2");
  inserir(arvore, "montaria");
  inserir(arvore, "montaria");
  inserir(arvore, "montaria");
  inserir(arvore, "montaria");
  inserir(arvore, "montaria");
  inserir(arvore, "faz");
  inserir(arvore, "faz sol");
  inserir(arvore, "montar mesa quadrada com vaso em baixo");
  inserir(arvore, "montar mesa quadrada com vaso em nada");
  inserir(arvore, "montar mesa redonda roxa");

  imprimirArvore(arvore);

  //busca(arvore);
  string remove;
  do
  {
    cout << endl
         << endl;
    imprimirArvore(arvore);
    cout << "Remove frase: ";
    getline(cin, remove);

    remover(arvore, remove);
    cout << endl
         << endl;
  } while (true);

  return 0;
}