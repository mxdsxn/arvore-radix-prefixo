#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct NoPatricia
{
  string chavePrefixo;
  vector<NoPatricia *> filhos;
  bool vazio = false;
} No;

string getPrefixo(string string1, string string2)
{
  string menorString = string1.length() <= string2.length() ? string1 : string2;
  string maiorString = string1.length() > string2.length() ? string1 : string2;

  for (int i = 0; i < maiorString.length(); i++)
  {
    if (menorString[i] != maiorString[i])
    {
      return maiorString.substr(0, i);
    }
  }

  return "";
}

void imprimirArvore(No *raiz, long int nivel = 0)
{
  if (raiz)
  {
    string espacador = "-";
    for (int i = 0; i < nivel; i++)
    {
      espacador += espacador;
    }
    espacador += "|";

    cout << espacador
         << " chavePrefixo: "
         << raiz->chavePrefixo
         << " | vazio: "
         << raiz->vazio
         << " | total filhos: "
         << raiz->filhos.size() << endl;

    if (raiz->filhos.size() > 0)
    {
      for (int index = 0; index < raiz->filhos.size(); index++)
      {
        imprimirArvore(raiz->filhos[index], nivel + 1);
      }
    }
  }
}

bool inserirFrase(No *raiz, string novaFrase)
{
  //inserindo na RAIZ, noh vazio
  if (raiz->vazio)
  {
    raiz->chavePrefixo = novaFrase;
    raiz->vazio = false;

    return true;
  }
  else
  {
    string prefixo = getPrefixo(raiz->chavePrefixo, novaFrase);
    if (prefixo != "")
    {
      // se for inserido uma frase que seja igual ao noh atual, nao é inserido nada na arvore.
      if (prefixo == raiz->chavePrefixo && prefixo == novaFrase)
      {
        return false;
      }
      else
      {
        string restoFrase = novaFrase.substr(prefixo.length(), novaFrase.length());
        // removendo espaco vazio do inicio da palavra para nao considerar " " como prefixo
        if (restoFrase[0] == ' ')
        {
          restoFrase = restoFrase.substr(1, restoFrase.length());
        }

        if (raiz->filhos.size() > 0)
        {
          // procura nos filhos do noh atual, se a nova frase pode ser neto do no atual
          // caso seja, insere no filho responsavel e retorna
          for (int i = 0; i < raiz->filhos.size(); i++)
          {
            if (getPrefixo(raiz->filhos[i]->chavePrefixo, restoFrase) != "")
            {
              cout << "filho escolhido: " << raiz->filhos[i]->chavePrefixo << endl;
              cout << "restoFrase" << restoFrase << endl;
              return inserirFrase(raiz->filhos[i], restoFrase);
            }
          }
        }
        // caso nao seja neto do noh atual, insere a nova frase como filho do noh atual
        No *ponteiroNovoNo = (No *)malloc(sizeof(No));

        ponteiroNovoNo->chavePrefixo = restoFrase;
        raiz->filhos.push_back(ponteiroNovoNo);
        return true;
      }
    }
    else
    {
      No *novoNo = (No *)malloc(sizeof(No));
      No *antigaRaiz = (No *)malloc(sizeof(No));

      antigaRaiz->chavePrefixo = raiz->chavePrefixo;
      antigaRaiz->filhos = raiz->filhos;
      antigaRaiz->vazio = raiz->vazio;

      novoNo->chavePrefixo = novaFrase;

      raiz->filhos.push_back(antigaRaiz);
      raiz->filhos.push_back(novoNo);
      return true;
    }
  }
  return false;
}

int main()
{
  // isolar isso em uma funcao - No& criaArvore();
  No *raiz = (No *)malloc(sizeof(No));
  raiz->vazio = true;

  string frase1 = "fazer bolo de chcolate";

  inserirFrase(raiz, "fazer");
  inserirFrase(raiz, "fazer tarefa");
  inserirFrase(raiz, "fazer bolo");

  imprimirArvore(raiz);

  return 0;
}
