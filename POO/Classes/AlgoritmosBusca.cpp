#include "../Include/AlgoritmosBusca.h"

int AlgoritmosBusca::rabinKarp(const string& texto, const string& padrao) {
    int n = texto.size();
    int m = padrao.size();
    const int d = 256;
    const int q = 101;
    int h = 1;
    int p = 0;
    int t = 0;

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p = (d * p + padrao[i]) % q;
        t = (d * t + texto[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            if (texto.substr(i, m) == padrao) {
                return i;
            }
        }
        if (i < n - m) {
            t = (d * (t - texto[i] * h) + texto[i + m]) % q;
            if (t < 0) {
                t += q;
            }
        }
    }
    return -1;
}

int AlgoritmosBusca::buscaSequencial(const vector<Produto>& produtos, const string& nome) {
    for (size_t i = 0; i < produtos.size(); ++i) {
        if (produtos[i].getNome().find(nome) != string::npos) {
            return i;
        }
    }
    return -1;
}

int AlgoritmosBusca::buscaBinaria(const vector<Produto>& produtos, const string& nome) {
    int esquerda = 0;
    int direita = produtos.size() - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (produtos[meio].getNome().find(nome) != string::npos) {
            return meio;
        }
        if (produtos[meio].getNome() < nome) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}

vector<int> AlgoritmosBusca::buscarPorLetra(const vector<Produto>& produtos, char letra) {
    vector<int> indices;
    string padrao(1, tolower(letra));
    
    for (int i = 0; i < produtos.size(); i++) {
        string nomeLower = produtos[i].getNome();
        transform(nomeLower.begin(), nomeLower.end(), nomeLower.begin(), ::tolower);
        
        int pos = rabinKarp(nomeLower, padrao);
        if (pos == 0) {
            indices.push_back(i);
        }
    }
    return indices;
}
