#include "clear.h"
#include "radix.hpp"

// Preenche a arvore com frases aleatorias para popular a estrutura
void preencheEventosDefault(No *arvore)
{
  string defaultFrases[] = {"montar mesa quadrada com vaso em cima",
                            "montar mesa quadrada",
                            "montar mesa",
                            "montar mesa redonda",
                            "",
                            "montar",
                            "montaria",
                            "montar mesa quadrada com vaso embaixo",
                            "fazer massa italiana rosa",
                            "faz lua",
                            "assistir shrek 2",
                            "faz",
                            "fazer bolo",
                            "fazer pao",
                            "faz sol",
                            "fazer massa italiana",
                            "fazer massa",
                            " quadrada",
                            "fazer massa italiana",
                            "fazer massa",
                            " redonda",
                            " ",
                            " quadrada rosa",
                            "fazer bolo",
                            "fazer pao",
                            "faz sol",
                            "montar mesa",
                            "fazer massa italiana rosa",
                            "montar mesa redonda",
                            "",
                            "faz lua",
                            "montar",
                            "assistir shrek 2",
                            "montaria",
                            "montaria",
                            "montaria",
                            "montaria",
                            "montaria",
                            "faz",
                            "faz sol",
                            "montar mesa quadrada com vaso em baixo",
                            "montar mesa quadrada com vaso em nada",
                            "montar mesa redonda roxa"};

  int tam = sizeof(defaultFrases) / sizeof(defaultFrases[0]);

  for (long int index = 0; index < tam; index++)
  {
    inserir(arvore, defaultFrases[index]);
  }
}

int main()
{
  No *arvore = criaArvoreRadix();
  preencheEventosDefault(arvore);

  int menuOption = 0;
  string buffer;

  do
  {
    clear();

    cout << "Escolha uma das opções:"
         << endl
         << endl;

    cout << "1 - Inserir" << endl
         << "2 - Remover" << endl
         << "3 - Buscar" << endl
         << "4 - Imprimir Arvore" << endl
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