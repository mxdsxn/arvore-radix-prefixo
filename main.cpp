#include "clear.h"
#include "radix.hpp"

int main()
{
  No *arvore = criaArvoreRadix();
  preencheEventosDefault(arvore);

  int menuOption = 0;
  string buffer;

  do
  {
    // clear();

    cout << "Escolha uma das opções:"
         << endl
         << endl;

    cout << "1 - Inserir" << endl
         << "2 - Remover" << endl
         << "3 - Buscar" << endl
         << "4 - Imprimir árvore" << endl
         << "0 - Encerrar" << endl
         << endl;

    cin >> menuOption;
    getline(cin, buffer);

    switch (menuOption)
    {
    case 1:
      insere(arvore);
      break;
    case 2:
      remove(arvore);
      break;
    case 3:
      busca(arvore);
      break;
    case 4:
      imprime(arvore);
      break;
    default:
      break;
    }

  } while (menuOption != 0);

  clear();

  return 0;
}