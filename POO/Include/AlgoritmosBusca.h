#ifndef ALGORITMOS_BUSCA_H
#define ALGORITMOS_BUSCA_H

#include <vector>
#include <string>
#include <algorithm>
#include "Produto.h"

using namespace std;

class AlgoritmosBusca {
public:
    static int rabinKarp(const string& texto, const string& padrao);
    static int buscaSequencial(const vector<Produto>& produtos, const string& nome);
    static int buscaBinaria(const vector<Produto>& produtos, const string& nome);
    static vector<int> buscarPorLetra(const vector<Produto>& produtos, char letra);
};

#endif // ALGORITMOS_BUSCA_H
