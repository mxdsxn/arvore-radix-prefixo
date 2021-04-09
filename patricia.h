#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::getline;
using std::string;

class NoPatricia
{
public:
  string chave = "";
  bool prefixo = true;
  List<NoPatricia *> filhos;

  // decide pra que filho vai mandar a pesquisa
  List<NoPatricia *> buscarNoFilho(NoPatricia *no);

  // quando termina a pesquisa, ou seja, quando encontra a ultima palavra da frase pesquisada,
  // retorna os ponteiros dos filhos que sao possibilidades e ate mesmo endereco do this,
  // pois o this pode ser uma possibilidade caso ele nao seja apenas um prefixo,
  // e sim uma tarefa tambem. this, *filhos || *filhos
  List<NoPatricia *> retornarPossibilidades(NoPatricia *no);
};