#include <iostream>
#include <vector>
#include <string>

using namespace std;

class NoPatricia
{
public:
  string chave = "";
  string conteudo = "";
  bool prefixo = true;
  vector<NoPatricia *> filhos;

  // decide pra que filho vai mandar a pesquisa
  vector<NoPatricia *> buscarNoFilho(NoPatricia *no);

  // quando termina a pesquisa, ou seja, quando encontra a ultima palavra da frase pesquisada,
  // retorna os ponteiros dos filhos que sao possibilidades e ate mesmo endereco do this,
  // pois o this pode ser uma possibilidade caso ele nao seja apenas um prefixo,
  // e sim uma tarefa tambem. this, *filhos || *filhos
  vector<NoPatricia *> retornarPossibilidades(NoPatricia *no);
};