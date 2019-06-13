#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "filesearch.h"

#include "doctest.h"

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

class Teste {
public:
  static vector<string> files_names(const FileSearch& c) {
    return  c.files_names;
  }
  static map<string,set<string>> coordinate(const FileSearch& c) {
    return  c.coordinate;
  }
  static map<string, map<string, double>> term_frequency(const FileSearch& c) {
    return  c.term_frequency;
  }
  static map<string, double> inverse_document_frequency(const FileSearch& c) {
    return  c.inverse_document_frequency;
  }
  static map<string, vector<double>> w_file_word(const FileSearch& c) {
    return  c.w_file_word;
  }
  static vector<string> return_query_(FileSearch& c, string &query){
    return c.return_query(query);
  }
  static double cosine_distance_(FileSearch& c, vector<double> a, vector<double> b){
    return c.cosine_distance(a, b);
  }
  static vector<double> set_w_query_(FileSearch& c, string &query){
  	vector <string> teste = c.return_query(query);
  	c.set_w_query(teste);
  	return c.w_query;
  }
};

TEST_SUITE("FileSearch") {
  TEST_CASE("list_file(string directory)") { //pode depender do compilador a ordem dos arquivos
    FileSearch t("teste");
    REQUIRE(Teste::files_names(t).size() == 4);
    CHECK(Teste::files_names(t)[0] == "D2");
    CHECK(Teste::files_names(t)[1] == "D3");
    CHECK(Teste::files_names(t)[2] == "D4");
    CHECK(Teste::files_names(t)[3] == "D1");
}

  TEST_CASE("read_file()") {
  FileSearch t("teste");
  set<string> A;
  A.insert("D1");
  A.insert("D2");
  A.insert("D3");
  set<string> B;
  B.insert("D1");
  B.insert("D4");
  set<string> C;
  C.insert("D2");
  CHECK(Teste::coordinate(t)["a"] == A);
  CHECK(Teste::coordinate(t)["b"] == B);
  CHECK(Teste::coordinate(t)["c"] == C);
  CHECK(Teste::term_frequency(t)["D1"]["a"] == 3);
  CHECK(Teste::term_frequency(t)["D2"]["a"] == 2);
  CHECK(Teste::term_frequency(t)["D3"]["a"] == 2);
  CHECK(Teste::term_frequency(t)["D4"]["a"] == 0);
  CHECK(Teste::term_frequency(t)["D1"]["b"] == 1);
  CHECK(Teste::term_frequency(t)["D2"]["b"] == 0);
  CHECK(Teste::term_frequency(t)["D3"]["b"] == 0);
  CHECK(Teste::term_frequency(t)["D4"]["b"] == 2);
  CHECK(Teste::term_frequency(t)["D1"]["c"] == 0);
  CHECK(Teste::term_frequency(t)["D2"]["c"] == 1);
  CHECK(Teste::term_frequency(t)["D3"]["c"] == 0);
  CHECK(Teste::term_frequency(t)["D4"]["c"] == 0);
}

  TEST_CASE("void set_idf()") {
  FileSearch t("teste");
  CHECK(floor(Teste::inverse_document_frequency(t)["a"]*100)/100.0 == 0.28);
  CHECK(floor(Teste::inverse_document_frequency(t)["b"]*100)/100.0 == 0.69);
  CHECK(floor(Teste::inverse_document_frequency(t)["c"]*100)/100.0 == 1.38);
}

  TEST_CASE("vector<string> return_query(string &query)") {
  FileSearch t("teste");
  string teste("A! B, oi");
  REQUIRE(Teste::return_query_(t, teste).size() == 3);
  CHECK(Teste::return_query_(t, teste)[0] == "a");
  CHECK(Teste::return_query_(t, teste)[1] == "b");
  CHECK(Teste::return_query_(t, teste)[2] == "oi");
}

  TEST_CASE("void set_w_file_word()") {
  FileSearch t("teste");
  CHECK(floor(Teste::w_file_word(t)["D1"][1]*100)/100.0 == 0.69);
  CHECK(floor(Teste::w_file_word(t)["D2"][2]*100)/100.0 == 1.38);
  CHECK(floor(Teste::w_file_word(t)["D3"][0]*100)/100.0 == 0.57);
  CHECK(floor(Teste::w_file_word(t)["D4"][1]*100)/100.0 == 1.38);
  }

  TEST_CASE("void set_w_query()") {
  FileSearch t("teste");
  string teste("A B");
  CHECK(floor(Teste::set_w_query_(t, teste)[0]*100)/100.0 == 0.28);
  CHECK(floor(Teste::set_w_query_(t, teste)[1]*100)/100.0 == 0.69);
  CHECK(floor(Teste::set_w_query_(t, teste)[2]*100)/100.0 == 0.00);
  }

  TEST_CASE("double cosine_distance(vector<double>& a, vector<double>& b)") {
  FileSearch t("teste");
  vector<double> A = {3.0, 8.0, 7.0, 5.0, 2.0, 9.0};
  vector<double> B = {10.0, 8.0, 6.0, 6.0, 4.0, 5.0};
  CHECK(floor(Teste::cosine_distance_(t, A, B)*100)/100.0 == 0.86);
  }
}
