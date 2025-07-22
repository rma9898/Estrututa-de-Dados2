#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Produto {
private:
    string nome;
    double preco;
    int quantidade;

public:
    // Construtores
    Produto();
    Produto(const string& nome, double preco, int quantidade);
    
    // Getters
    string getNome() const;
    double getPreco() const;
    int getQuantidade() const;
    
    // Setters
    void setNome(const string& nome);
    void setPreco(double preco);
    void setQuantidade(int quantidade);
    
    // Métodos utilitários
    string toString() const;
    void reduzirQuantidade(int qtd);
    bool temEstoque() const;
    bool temEstoqueSuficiente(int qtd) const;
};

#endif // PRODUTO_H
