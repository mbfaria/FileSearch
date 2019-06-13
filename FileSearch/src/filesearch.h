#ifndef FILE_SEARCH_H
#define FILE_SEARCH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <dirent.h>
#include <string.h>

using namespace std;

class FileSearch{
 public:
  FileSearch(string directory);  //Construtor que faz a leitura dos arquivos e seta as variaveis.

  void find(string &query); //Metodo usado para encontrar a string desejada.

private:
  vector<string> files_names; //Variavel que armazena o nome dos arquivos.

  map<string,set<string>> coordinate; //Variavel map que recebe o nome da palavra e retorna um set com os arquivos onde essa palavra se encontra.

  map<string, map<string, double>> term_frequency; //Variavel que retorna a frequencia do termo, com as keys nome do arquivo e palavra.

  map<string, double> inverse_document_frequency; //Variavel que retorna a frequencia inversa do documento, recebe a palavra como key.

  map<string, vector<double>> w_file_word; //Variavel map que recebe o nome do arquivo como key e retorna o vetor para o calculo de similaridade.

  vector<double> w_query; //Variavel que armazena o vetor da busca para o calculo da similaridade.


  void list_file(string directory); //Metodo que le os arquivos de um diretorio os armazena em um vetor.

  void set_idf(); //Metodo que seta a variavel inverse_document_frequency.

  void read_files(string directory); //Metodo que faz a leitura dos arquivos e chama os outros metodos.

  void set_w_file_word(); //Metodo que seta a variavel set_w_file_word.

  void set_w_query(vector<string> &words); //Metodo que seta a variavel w_query de acordo com os arquivos.

  vector<string> return_query(string &query); //Metodo que retorna a consulta em em vetor retirando pontos e letras maiusculas.

  double cosine_distance(vector<double>& a, vector<double>& b); //Metodo que retorna a distancia de cossenos de dois vetores.

  friend class Teste;
};

#endif  // FILE_SEARCH_H
