#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

// ======== HASH COM TRANSFORMAÇÃO DA RAIZ ========
class HashTableTransformacaoRaiz {
private:
    vector<vector<pair<string, int>>> tabela;
    int tamanho;
    int funcaoHashRaiz(const string& chave);
    int funcaoHashMultiplicacao(const string& chave);
    
public:
    HashTableTransformacaoRaiz(int tam);
    void inserir(const string& chave, int valor);
    bool buscar(const string& chave, int& valor);
    bool remover(const string& chave);
    void imprimir();
    void mostrarEstatisticas();
    void demonstrarTransformacao(const string& chave);
};

// ======== HASH COM ENCADEAMENTO LIMITE ========
class HashTableEncadeamentoLimite {
private:
    vector<vector<pair<string, int>>> tabela;
    int tamanho;
    int limiteColisoes;
    int funcaoHash(const string& chave);
    
public:
    HashTableEncadeamentoLimite(int tam, int limite = 3);
    void inserir(const string& chave, int valor);
    bool buscar(const string& chave, int& valor);
    bool remover(const string& chave);
    void imprimir();
    void mostrarEstatisticas();
    bool precisaReorganizar();
    void reorganizarTabela();
};

// ======== GERENCIADOR DE HASH ========
class GerenciadorHash {
public:
    void demonstrarHashing();
    void sistemaHashCompleto();
    void demonstrarEncadeamentoLimite();
    void demonstrarTransformacaoRaiz();
    void compararMetodosHash();
    void testePersonalizado();
};

#endif // HASH_TABLE_H
