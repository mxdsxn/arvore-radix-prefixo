#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct NoPatricia
{
  string chavePrefixo = "";
  vector<NoPatricia *> filhos;
  bool vazio = true;
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

bool inserirFrase(No *raiz, string novaFrase)
{

  if (raiz->chavePrefixo == "" && raiz->vazio)
  {
    raiz->chavePrefixo = novaFrase;
    raiz->vazio = false;

    cout << "if";
    // return true;
  }
  else
  {
    cout << "else"
         << raiz->chavePrefixo;

    // return false;
    // string prefixo = getPrefixo(raiz->chavePrefixo, novaFrase);

    // if (prefixo != "")
    // {
    //   // se for inserido uma frase que seja igual ao no atual, nao é inserido nada na arvore.
    //   if (prefixo == raiz->chavePrefixo && prefixo == novaFrase)
    //   {
    //     return false;
    //   }
    //   else
    //   {
    //     string restoFrase = novaFrase.substr(prefixo.length() - 1, novaFrase.length());

    //     if (raiz->filhos.size() == 0)
    //     {
    //       No *novoNo;

    //       novoNo->chavePrefixo = restoFrase;
    //       raiz->filhos.push_back(novoNo);
    //       return true;
    //     }
    //     else
    //     {
    //       for (int i = 0; i < raiz->filhos.size(); i++)
    //       {
    //         if (getPrefixo(raiz->filhos[i]->chavePrefixo, restoFrase) != "")
    //         {
    //           return inserirFrase(raiz->filhos[i], restoFrase);
    //         }
    //       }
    //     }
    //   }
    // }
    // else
    // {
    //   No *novaRaiz, *novoNo;

    //   novoNo->chavePrefixo = novaFrase;

    //   novaRaiz->filhos.push_back(raiz);
    //   novaRaiz->filhos.push_back(novoNo);
    //   return true;
    // }
  }
  return false;
}

int main()
{
  No *raiz;

  string frase1 = "fazer bolo de chcolate";

  inserirFrase(raiz, "fazer");

  return 0;
}
