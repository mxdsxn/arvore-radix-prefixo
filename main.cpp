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
  if (string1 == string2)
  {
    return string2;
  }

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
  //cout << "prefixo: '" << prefixo << "'" << endl;
  //cout << "stringCompleta: '" << stringCompleta << "'" << endl;
  string stringSemPrefixo = stringCompleta.substr(prefixo.length(), stringCompleta.length());
  //cout << "erro " << stringSemPrefixo << endl;
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

void imprimirBusca(No *noh, string prefixo = "")
{
  if (noh)
  {
    if (noh->finalFrase)
    {
      cout << prefixo << noh->chavePrefixo << endl;
    }
    for (int index = 0; index < noh->filhos.size(); index++)
    {
      string novoPrefixo = prefixo + noh->chavePrefixo;
      No *filhoAtual = noh->filhos[index];
      imprimirBusca(filhoAtual, novoPrefixo);
    }
  }
}

void buscar(No *noh, string fraseBusca)
{
  if (noh->raiz)
  {
    for (long int index = 0; index < noh->filhos.size(); index++)
    {
      No *filhoAtual = noh->filhos[index];
      string intersecao = getPrefixo(filhoAtual->chavePrefixo, fraseBusca);
      string fraseSemIntersecao = removePrefixo(intersecao, fraseBusca);

      // se houver intersecao entre filhoAtual e a frase de busca, e nao houver mais palavras alem da intersecao
      if (intersecao != "" && fraseSemIntersecao == "")
      {
        imprimirBusca(filhoAtual);
        return;
      }

      // se houver intersecao entre filhoAtual e frase de busca, e houver mais palavras na busca alem da intersecao
      if (intersecao != "" && fraseSemIntersecao != "")
      {
        buscar(filhoAtual, fraseBusca);
        return;
      }
    }
  }
  else
  {
    // intersecao entre o noh atual e a busca
    string intersecao = getPrefixo(noh->chavePrefixo, fraseBusca);
    // frase de busca sem a intersecao
    string fraseBuscaSemIntersecao = removePrefixo(intersecao, fraseBusca);
    if (noh->chavePrefixo == fraseBusca)
    {
      fraseBuscaSemIntersecao = "";
    }

    if (fraseBuscaSemIntersecao == "")
    {
      imprimirBusca(noh);
      return;
    }

    for (long int index = 0; index < noh->filhos.size(); index++)
    {
      No *filhoAtual = noh->filhos[index];

      string intersecaoComFilhoAtual = getPrefixo(filhoAtual->chavePrefixo, fraseBuscaSemIntersecao);

      // houve intersecao com o filho e chave do filho atual igual a frase de busca sem a intersecao
      if (intersecaoComFilhoAtual != "" && fraseBuscaSemIntersecao == filhoAtual->chavePrefixo)
      {
        imprimirBusca(filhoAtual);
        return;
      }

      if (intersecaoComFilhoAtual != "" && fraseBuscaSemIntersecao != filhoAtual->chavePrefixo)
      {
        cout << "aqui" << endl;
        buscar(filhoAtual, fraseBuscaSemIntersecao);
        return;
      }
    }
  }
}

bool inserir(No *noh, string novaFrase)
{
  // quando ha tentativa de inserir uma frase fazia
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
        return inserir(filhoAtual, novaFrase);
      }
    }

    // se a novaFrase for igual à algum filho
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
    string prefixoComum = getPrefixo(noh->chavePrefixo, novaFrase);
    string novaFraseSemPrefixo = removePrefixo(prefixoComum, novaFrase);

    if (novaFrase == noh->chavePrefixo)
    {
      noh->finalFrase = true;
      return false;
    }

    // cenario: quando a novaFrase eh irma do noh atual
    if (novaFraseSemPrefixo != "" && prefixoComum != "" && prefixoComum != noh->chavePrefixo)
    {
      No *novoFilho = (No *)malloc(sizeof(No));
      novoFilho->chavePrefixo = novaFraseSemPrefixo;
      novoFilho->finalFrase = true;

      No *novoIrmao = (No *)malloc(sizeof(No));
      string prefixoRemovido = removePrefixo(prefixoComum, noh->chavePrefixo);
      novoIrmao->chavePrefixo = prefixoRemovido;
      novoIrmao->finalFrase = noh->finalFrase;
      novoIrmao->filhos = noh->filhos;

      noh->chavePrefixo = prefixoComum;
      noh->finalFrase = false;
      noh->filhos.clear();
      noh->filhos.push_back(novoFilho);
      noh->filhos.push_back(novoIrmao);
      return true;
    }
    // cenario: quando a novaFrase eh pai do noh atual
    else if (novaFraseSemPrefixo == "" && prefixoComum != "" && prefixoComum != noh->chavePrefixo)
    {
      No *novoFilho = (No *)malloc(sizeof(No));
      string prefixoRemovido = removePrefixo(prefixoComum, noh->chavePrefixo);
      novoFilho->chavePrefixo = prefixoRemovido;
      novoFilho->finalFrase = noh->finalFrase;
      novoFilho->filhos = noh->filhos;

      noh->chavePrefixo = prefixoComum;
      noh->finalFrase = true;
      noh->filhos.clear();
      noh->filhos.push_back(novoFilho);
      return true;
    }

    // cenario: quando a novaFrase tem intersecao com algum filho do noh atual, ou seja, neto
    for (long int index = 0; index < noh->filhos.size(); index++)
    {
      No *filhoAtual = noh->filhos[index];
      string intersecaoFilhoFrase = getPrefixo(filhoAtual->chavePrefixo, novaFraseSemPrefixo);

      if (intersecaoFilhoFrase != "")
      {
        return inserir(filhoAtual, novaFraseSemPrefixo);
      }
    }

    No *novoFilho = (No *)malloc(sizeof(No));
    novoFilho->chavePrefixo = novaFraseSemPrefixo;
    novoFilho->finalFrase = true;
    noh->filhos.push_back(novoFilho);
    return true;
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
  inserir(arvore, "montar mesa quadrada com vaso embaixo");

  cout << endl;

  imprimirArvore(arvore);

  string fraseBusca;

  cout << "Busque uma frase:" << endl;
  getline(cin, fraseBusca);

  cout << "busca: '" << fraseBusca << "'" << endl;
  buscar(arvore, fraseBusca);
  cout << endl;

  return 0;
}
