#include "clear.h"
#include "radix.hpp"

// Funcao para criar arvore radix
No *criaArvoreRadix()
{
  No *noh = (No *)malloc(sizeof(No));
  noh->raiz = true;
  return noh;
}

// Funcao para pegar prefixo em comum de duas strings
string getPrefixo(string string1, string string2)
{
  // se ambas strings forem iguais, retorna qualquer uma
  // no caso, a segunda
  if (string1 == string2)
  {
    return string2;
  }

  // separa entre maior e menor string
  string menorString = string1.length() <= string2.length() ? string1 : string2;
  string maiorString = string1.length() > string2.length() ? string1 : string2;

  // percorre a maior string
  for (int i = 0; i < maiorString.length(); i++)
  {
    // se chegar no caractere que difere ambas
    if (menorString[i] != maiorString[i])
    {
      // retorna todos os caracteres anteriores a diferença
      return maiorString.substr(0, i);
    }
  }

  return "";
}

// Funcao para remover prefixo da string completa
string removePrefixo(string prefixo, string stringCompleta)
{
  string stringSemPrefixo = stringCompleta.substr(prefixo.length(), stringCompleta.length());

  return stringSemPrefixo;
}

// Funcao para comparar dois nos
bool comparaNo(No *nohA, No *nohB)
{
  int resultado = strcmp(nohA->chavePrefixo.c_str(), nohB->chavePrefixo.c_str());

  if (resultado < 0)
  {
    return true;
  }
  return false;
}

// Funcao para ordenar filhos do no
void sortFilhosNo(No *noh)
{
  // utiliza-se a funcao ja existente "sort"
  sort(noh->filhos.begin(), noh->filhos.end(), comparaNo);
}

// Funcao para imprimir arvore
void imprimirArvore(No *noh, long int nivel)
{
  if (noh)
  {
    string espacador = "-";
    for (int i = 0; i < nivel; i++)
    {
      espacador += "--";
    }
    espacador += "|";

    cout << espacador
         << " PK: '"
         << noh->chavePrefixo
         << "' | FF: "
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

// Funcao para imprimir busca
void imprimirBusca(No *noh, string prefixo = "")
{
  if (noh)
  {
    // se o no for final de frase, imprime
    if (noh->finalFrase)
    {
      cout << prefixo << noh->chavePrefixo << endl;
    }
    // para todos os filhos, repete
    for (int index = 0; index < noh->filhos.size(); index++)
    {
      string novoPrefixo = prefixo + noh->chavePrefixo;
      No *filhoAtual = noh->filhos[index];
      imprimirBusca(filhoAtual, novoPrefixo);
    }
  }
}

// Funcao de busca geral
bool buscar(No *noh, string fraseBusca, string defaultPrefixo = "")
{
  // se for no raiz
  if (noh->raiz)
  {
    return buscarRaiz(noh, fraseBusca, defaultPrefixo);
  }
  // se for algum no filho
  else
  {
    return buscarFilhos(noh, fraseBusca, defaultPrefixo);
  }
  // se rodou e nao achou, retorna false
  return false;
}

// Funcao de busca para raiz
bool buscarRaiz(No *noh, string fraseBusca, string defaultPrefixo = "")
{
  // percorre filhos
  for (long int index = 0; index < noh->filhos.size(); index++)
  {
    No *filhoAtual = noh->filhos[index];
    string intersecao = getPrefixo(filhoAtual->chavePrefixo, fraseBusca);
    string fraseSemIntersecao = removePrefixo(intersecao, fraseBusca);

    // se houver intersecao entre filhoAtual e a frase de busca
    // e NAO houver mais palavras alem da intersecao
    // entao a frase procurada era a raiz
    if (intersecao != "" && fraseSemIntersecao == "")
    {
      // imprime busca e retorna que achou
      imprimirBusca(filhoAtual, defaultPrefixo);
      return true;
    }

    // se houver intersecao entre filhoAtual e frase de busca
    // e HOUVER mais palavras na busca alem da intersecao
    // entao a frase procurada deve estar em algum lugar fora a raiz
    // roda novamente porem com o filho
    if (intersecao != "" && fraseSemIntersecao != "")
    {
      return buscar(filhoAtual, fraseBusca, noh->chavePrefixo);
    }
  }
  return false;
}

// Funcao de busca para filhos
bool buscarFilhos(No *noh, string fraseBusca, string defaultPrefixo = "")
{
  string intersecao = getPrefixo(noh->chavePrefixo, fraseBusca);
  string fraseBuscaSemIntersecao = removePrefixo(intersecao, fraseBusca);

  // se o prefixo do no for igual a frase da busca, a "sem intersecao" eh vazia
  if (noh->chavePrefixo == fraseBusca)
  {
    fraseBuscaSemIntersecao = "";
  }

  // se a frase da busca for igual ao no atual
  if (fraseBuscaSemIntersecao == "")
  {
    // imprime busca e retorna que achou
    imprimirBusca(noh, defaultPrefixo);
    return true;
  }

  // percorre filhos
  for (long int index = 0; index < noh->filhos.size(); index++)
  {
    No *filhoAtual = noh->filhos[index];
    string intersecaoComFilhoAtual = getPrefixo(filhoAtual->chavePrefixo, fraseBuscaSemIntersecao);

    // se houver intersecao com o filho atual (string de intersecao != vazia)
    // e a frase de busca sem a intersecao eh igual a chave do filho atual
    if (intersecaoComFilhoAtual != "" && fraseBuscaSemIntersecao == filhoAtual->chavePrefixo)
    {
      // imprime e retorna que encontrou
      imprimirBusca(filhoAtual, defaultPrefixo + noh->chavePrefixo);
      return true;
    }

    // se houver intersecao com o filho atual
    // mas a frase de busca sem intersecao nao eh igual a chave do filho atual
    // entao ainda restam palavras a serem buscadas
    if (intersecaoComFilhoAtual != "" && fraseBuscaSemIntersecao != filhoAtual->chavePrefixo)
    {
      // busca novamente com o filho atual
      return buscar(filhoAtual, fraseBuscaSemIntersecao, defaultPrefixo + noh->chavePrefixo);
    }
  }
  return false;
}

// Preenche a arvore com frases simulando eventos de agenda, para popular a estrutura
// OBSERVACAO: nao foi possivel realizar essa funcao com um vetor de strings
// pois ao preencher usando o for, aparecia o erro 'corrupted double-linked list'
// mesmo tentando de varias formas, nao foi possivel resolver.
// pela melhor otimizacao do tempo, optamos por deixar essa funcao assim.
void preencheEventosDefault(No *arvore)
{
  inserir(arvore, "terminar lista de ed 2");
  inserir(arvore, "terminar revisao de ed 2");
  inserir(arvore, "terminar lista de tecnicas de programacao");
  inserir(arvore, "terminar revisao de tecnicas de programacao");
  inserir(arvore, "passear com o cachorro");
  inserir(arvore, "passear com o porco");
  inserir(arvore, "passear com o gato");
  inserir(arvore, "passear com o namorado");
  inserir(arvore, "passear");
  inserir(arvore, "cozinhar macarrao");
  inserir(arvore, "cozinhar macarrao ao molho branco");
  inserir(arvore, "cozinhar macarrao a bolonhesa");
  inserir(arvore, "descansar");
  inserir(arvore, "descansar por 20 minutos");
  inserir(arvore, "jogar league of legends");
  inserir(arvore, "jogar wild rift");
  inserir(arvore, "jogar animal crossing");
  inserir(arvore, "jogar the sims");
  inserir(arvore, "terminar de comer bolo na geladeira");
  inserir(arvore, "terminar amizade com quem nao assistiu bbb");
}

// Funcao para interagir com o usuario e inserir uma frase
void insere(No *arvore)
{
  string novaFrase;
  string buffer;
  int menuOption = 1;

  do
  {
    clear();

    cout << "Insira uma nova frase:" << endl;
    getline(cin, novaFrase);
    clear();

    cout << "Frase inserida: '" << novaFrase << "'" << endl;
    bool resultado = inserir(arvore, novaFrase);
    cout << "Resultado: " << (resultado ? "Inserida com sucesso." : "Frase já existente ou vazia.")
         << endl
         << endl;

    cout << "1 - Inserir novamente" << endl
         << "0 - Voltar" << endl
         << "> ";

    cin >> menuOption;
    getline(cin, buffer);
    clear();

  } while (menuOption == 1);
}

// Funcao para interagir com o usuario para buscar frase
void busca(No *arvore)
{
  string fraseBusca;
  string buffer;
  int menuOption = 1;

  do
  {
    clear();

    cout << "Busque uma frase:" << endl;
    getline(cin, fraseBusca);
    clear();

    cout << "Frase buscada: '" << fraseBusca << "'" << endl;
    cout << "Resultado: "
         << endl
         << endl;

    bool resultado = buscar(arvore, fraseBusca);
    if (!resultado)
    {
      cout << " >> Nao ha resultados para essa busca. <<" << endl;
    }
    cout << endl
         << endl;

    cout << "1 - Buscar novamente" << endl
         << "0 - Voltar" << endl
         << "> ";

    cin >> menuOption;
    getline(cin, buffer);
    clear();

  } while (menuOption == 1);
}

// Funcao para interagir com o usuario para remover frase
void remove(No *arvore)
{
  string fraseRemover;
  string buffer;
  int menuOption = 1;

  do
  {
    clear();

    cout << "Remova uma frase:" << endl;
    getline(cin, fraseRemover);
    clear();

    cout << "Digite a frase que quer remover: '" << fraseRemover << "'" << endl;
    bool resultado = remover(arvore, fraseRemover);
    cout << "Resultado: " << (resultado ? "Removida com sucesso." : "Nao foi encontrada essa frase para remover ou vazia.") << endl;
    cout << endl
         << endl;

    cout << "1 - Remover novamente" << endl
         << "0 - Voltar" << endl
         << "> ";

    cin >> menuOption;
    getline(cin, buffer);
    clear();

  } while (menuOption == 1);
}

// Funcao para interagir com o usuario para mostrar a estrutura atual da arvore
void imprime(No *arvore)
{
  clear();

  string buffer;
  cout << ">> Arvore de prefixos(Radix) <<" << endl
       << endl;

  imprimirArvore(arvore);

  cout << endl
       << "--------- Tecle ENTER para voltar ---------" << endl;

  getline(cin, buffer);
  clear();
}

// Funcao de insercao de novo no (frase)
bool inserir(No *noh, string novaFrase)
{
  // se a frase estiver vazia, retorna erro
  if (novaFrase == "")
  {
    return false;
  }

  // se o no for raiz
  if (noh->raiz)
  {
    return inserirRaiz(noh, novaFrase);
  }
  // se for filho
  else
  {
    return inserirFilhos(noh, novaFrase);
  }
  return false;
}

// Funcao para inserir novo no na raiz
bool inserirRaiz(No *noh, string novaFrase)
{
  // percorre os filhos
  for (long int index = 0; index < noh->filhos.size(); index++)
  {
    No *filhoAtual = noh->filhos[index];
    string prefixoEmComum = getPrefixo(filhoAtual->chavePrefixo, novaFrase);

    // se houver algum prefixo em comum
    if (prefixoEmComum != "")
    {
      // insere no filho atual
      return inserir(filhoAtual, novaFrase);
    }

    // se a novaFrase for igual a algum filho
    if (filhoAtual->chavePrefixo == novaFrase)
    {
      return false;
    }
  }

  // se nao houver filho com prefixo em comum
  // eh filho do no atual
  No *novoFilho = (No *)malloc(sizeof(No));
  novoFilho->chavePrefixo = novaFrase;
  novoFilho->finalFrase = true;
  noh->filhos.push_back(novoFilho);
  sortFilhosNo(noh);

  return true;
}

// Funcao para inserir novo no nos filhos
bool inserirFilhos(No *noh, string novaFrase)
{
  string prefixoComum = getPrefixo(noh->chavePrefixo, novaFrase);
  string novaFraseSemPrefixo = removePrefixo(prefixoComum, novaFrase);

  // se a nova frase for igual ao prefixo atual
  if (novaFrase == noh->chavePrefixo)
  {
    // vira final de frase
    noh->finalFrase = true;
    return false;
  }

  // === se a nova frase for irma do no atual ===
  // ou seja,
  // se retirando o prefixo em comum ela nao ficou vazia
  // se o prefixo em comum nao eh vazio e nem eh a chave do no
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
    sortFilhosNo(noh);

    return true;
  }
  // === se a nova frase for pai do no atual ===
  // ou seja,
  // se retirando o prefixo ela fica vazia
  // e o prefixo em comum nao eh vazio e nem eh a chave do no
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
    sortFilhosNo(noh);

    return true;
  }

  // === sera que a nova frase tem intersecao com algum filho do no atual? ===
  // vamos descobrir se ha netinhos...
  // percorre filhos
  for (long int index = 0; index < noh->filhos.size(); index++)
  {
    No *filhoAtual = noh->filhos[index];
    string intersecaoFilhoFrase = getPrefixo(filhoAtual->chavePrefixo, novaFraseSemPrefixo);

    // se tiver intersecao com o filho
    if (intersecaoFilhoFrase != "")
    {
      // vamos ao neto
      return inserir(filhoAtual, novaFraseSemPrefixo);
    }
  }

  // se nao cair em nenhuma das outras condicoes
  // eh filho do no atual
  No *novoFilho = (No *)malloc(sizeof(No));
  novoFilho->chavePrefixo = novaFraseSemPrefixo;
  novoFilho->finalFrase = true;
  noh->filhos.push_back(novoFilho);
  sortFilhosNo(noh);

  return true;
}

// Funcao para remocao de no
bool remover(No *noh, string removeFrase)
{
  if (noh)
  {
    // se nao for passada frase a ser removida, retorna erro
    if (removeFrase == "")
    {
      return false;
    }

    // percorre os filhos do no
    for (int index = 0; index < noh->filhos.size(); index++)
    {
      No *filhoAtual = noh->filhos[index];
      string intersecaoFilhoFrase = getPrefixo(filhoAtual->chavePrefixo, removeFrase);
      string removeFraseSemPrefixo = removePrefixo(intersecaoFilhoFrase, removeFrase);

      // === se a frase puder ser removida ===
      // ou seja,
      // se a frase a ser removida for igual a chave do filho atual
      // e o filho atual for final de frase
      if (removeFrase == filhoAtual->chavePrefixo && filhoAtual->finalFrase)
      {
        // === se o filho a ser removido nao tiver nenhum neto ===
        // ou seja,
        // o filho nao tem filhos
        if (filhoAtual->filhos.size() == 0)
        {
          // apaga o filho
          noh->filhos.erase(noh->filhos.begin() + index);

          // se o no (pai) ficou com apenas um filho,
          // o filho vira irmao, ou seja, vai ser filho do no pai
          // (somente caso o no pai nao seja a raiz)
          if (noh->filhos.size() == 1 && noh->finalFrase == false && !noh->raiz)
          {
            noh->chavePrefixo += noh->filhos[0]->chavePrefixo;
            noh->finalFrase = noh->filhos[0]->finalFrase;
            noh->filhos = noh->filhos[0]->filhos;
          }
          return true;
        }
        // === se o filho a ser removido tiver 1 neto ===
        // ou seja,
        // se tiver um filho do filho
        else if (filhoAtual->filhos.size() == 1)
        {
          // faz o filho assumir a identidade do neto
          // e o neto "desaparece para sempre sob circunstancias misteriosas"...
          filhoAtual->chavePrefixo += filhoAtual->filhos[0]->chavePrefixo;
          filhoAtual->finalFrase = filhoAtual->filhos[0]->finalFrase;
          filhoAtual->filhos = filhoAtual->filhos[0]->filhos;
          return true;
        }
        // === se o filho a ser removido tiver mais de 1 neto ===
        // ou seja,
        // pai de familia e nao pode ser removido
        else if (filhoAtual->filhos.size() > 1)
        {
          // apenas deixa de ser final de frase,
          // simbolizando que nao eh mais frase completa
          // e servindo apenas como prefixo dos netinhos (seus filhos)
          filhoAtual->finalFrase = false;
          return true;
        }
      }
      // === se ainda houver resto de frase a ser pesquisado ===
      // ou seja,
      // se houver intersecao com o filho atual
      else if (intersecaoFilhoFrase == filhoAtual->chavePrefixo)
      {
        // roda novamente a operacao de remocao com o filho
        bool result = remover(filhoAtual, removeFraseSemPrefixo);

        // se o filho ficar sem netos, e nao for final de frase
        // remove esse filho que esta atuando como prefixo
        if (filhoAtual->filhos.size() == 0 && filhoAtual->finalFrase == false)
        {
          noh->filhos.erase(noh->filhos.begin() + index);
        }
        return result;
      }
    }
  }
  return false;
}