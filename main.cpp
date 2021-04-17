#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct NoPatricia
{
  string chavePrefixo;
  vector<NoPatricia *> filhos;
  bool raiz = false;
  bool finalFrase = false;
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

string removePrefixo(string prefixo, string stringCompleta)
{
  string stringSemPrefixo = stringCompleta.substr(prefixo.length(), stringCompleta.length());
  return stringSemPrefixo;
}

void imprimirArvore(No *noh, long int nivel = 0)
{
  if (noh)
  {
    string espacador = "-";
    for (int i = 0; i < nivel; i++)
    {
      espacador += espacador;
    }
    espacador += "|";

    cout << espacador
         << " chavePrefixo: '"
         << noh->chavePrefixo
         << "' | final frase: "
         << (noh->finalFrase ? "sim" : "nao") << endl;

    if (noh->filhos.size() > 0)
    {
      for (int index = 0; index < noh->filhos.size(); index++)
      {
        imprimirArvore(noh->filhos[index], nivel + 1);
      }
    }
  }
}

bool inserirFrase(No *noh, string novaFrase)
{
  if (novaFrase == "")
  {
    return false;
  }

  // eh raiz
  if (noh->raiz)
  {
    // procura se algum filho tem prefixo em comum, se houver, insere no filho
    for (long int index = 0; index < noh->filhos.size(); index++)
    {
      No *filhoAtual = noh->filhos[index];
      string prefixoEmComum = getPrefixo(filhoAtual->chavePrefixo, novaFrase);

      if (prefixoEmComum != "")
      {
        return inserirFrase(filhoAtual, novaFrase);
      }
    }

    for (long int index = 0; index < noh->filhos.size(); index++)
    {
      if (noh->filhos[index]->chavePrefixo == novaFrase)
      {
        return false;
      }
    }

    // se nao houver filho com prefixo em comum, é filho do noh atual
    No *novoFilho = (No *)malloc(sizeof(No));
    novoFilho->chavePrefixo = novaFrase;
    novoFilho->finalFrase = true;
    noh->filhos.push_back(novoFilho);
    return true;
  }
  else
  {
    string prefixoAleatorio = getPrefixo(novaFrase, noh->chavePrefixo);
    if (prefixoAleatorio == novaFrase)
    {
      string antigaFraseSemPrefixo = removePrefixo(prefixoAleatorio, noh->chavePrefixo);
      No *novoFilho = (No *)malloc(sizeof(No));
      novoFilho->chavePrefixo = antigaFraseSemPrefixo;
      novoFilho->filhos = noh->filhos;
      novoFilho->finalFrase = noh->finalFrase;

      noh->chavePrefixo = prefixoAleatorio;
      noh->finalFrase = true;
      noh->filhos.clear();
      noh->filhos.push_back(novoFilho);

      return true;
    }

    // procura se algum filho tem prefixo em comum, se houver, insere no filho
    for (long int index = 0; index < noh->filhos.size(); index++)
    {
      No *filhoAtual = noh->filhos[index];
      string prefixoComumFilhoAtual = getPrefixo(filhoAtual->chavePrefixo, novaFrase);

      string prefixoComumNohAtual = getPrefixo(noh->chavePrefixo, novaFrase);
      if (prefixoComumNohAtual == noh->chavePrefixo) //prefixoComumFilhoAtual
      {
        string novaFraseSemPrefixo = removePrefixo(noh->chavePrefixo, novaFrase);
        string novoprefixoComumFilhoAtual = getPrefixo(filhoAtual->chavePrefixo, novaFraseSemPrefixo);
        if (novoprefixoComumFilhoAtual != "")
        {
          return inserirFrase(filhoAtual, novaFraseSemPrefixo);
        }
      }

      // testa se tem algo em comum com o filho, caso o filho tenha um prefixo completo
      if (prefixoComumFilhoAtual != "")
      {
        return inserirFrase(filhoAtual, novaFrase);
      }
    }

    string prefixoEmComum = getPrefixo(noh->chavePrefixo, novaFrase);

    string novaFraseSemPrefixo = removePrefixo(prefixoEmComum, novaFrase);
    for (long int index = 0; index < noh->filhos.size(); index++)
    {
      if (noh->filhos[index]->chavePrefixo == novaFraseSemPrefixo)
      {
        return false;
      }
    }
    // cria novo noh com nova frase inserida
    No *novoFilho = (No *)malloc(sizeof(No));
    novoFilho->chavePrefixo = novaFraseSemPrefixo;
    novoFilho->finalFrase = true;

    // verifica se a nova frase é filho do noh atual
    string chaveAtualSemPrefixo = removePrefixo(prefixoEmComum, noh->chavePrefixo);
    if (chaveAtualSemPrefixo == "")
    {
      noh->filhos.push_back(novoFilho);
      return true;
    }

    // caso nao seja filho, sao irmaos. cria uma raiz com prefixo entre eles
    if (chaveAtualSemPrefixo != "")
    {
      No *novoNohAtual = (No *)malloc(sizeof(No));
      novoNohAtual->chavePrefixo = chaveAtualSemPrefixo;
      novoNohAtual->filhos = noh->filhos;
      novoNohAtual->finalFrase = noh->finalFrase;

      noh->chavePrefixo = prefixoEmComum;
      noh->finalFrase = false;
      noh->filhos.clear();
      noh->filhos.push_back(novoFilho);
      noh->filhos.push_back(novoNohAtual);

      return true;
    }
  }
  return false;
}

No *criaArvorePatricia()
{
  No *noh = (No *)malloc(sizeof(No));
  noh->raiz = true;
  return noh;
}

int main()
{
  No *arvore = criaArvorePatricia();

  inserirFrase(arvore, "fazer massa italiana");
  inserirFrase(arvore, "fazer massa");
  inserirFrase(arvore, "montar mesa");
  inserirFrase(arvore, "fazer bolo");
  inserirFrase(arvore, "montar mesa quadrada");
  inserirFrase(arvore, "montar mesa redonda");
  inserirFrase(arvore, "faz sol");
  inserirFrase(arvore, "fazer pao");
  inserirFrase(arvore, "faz lua");
  inserirFrase(arvore, "montar");
  inserirFrase(arvore, "assistir shrek 2");
  inserirFrase(arvore, "montaria");
  inserirFrase(arvore, "montaria");
  inserirFrase(arvore, "");
  inserirFrase(arvore, "montar mesa quadrada com vaso em cima");
  inserirFrase(arvore, "montar mesa quadrada com vaso embaixo");

  imprimirArvore(arvore);

  return 0;
}
