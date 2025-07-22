#include "../Include/Produto.h"

// Construtores
Produto::Produto() : nome(""), preco(0.0), quantidade(0) {}

Produto::Produto(const string& nome, double preco, int quantidade) 
    : nome(nome), preco(preco), quantidade(quantidade) {}

// Getters
string Produto::getNome() const { return nome; }
double Produto::getPreco() const { return preco; }
int Produto::getQuantidade() const { return quantidade; }

// Setters
void Produto::setNome(const string& nome) { this->nome = nome; }
void Produto::setPreco(double preco) { this->preco = preco; }
void Produto::setQuantidade(int quantidade) { this->quantidade = quantidade; }

// Métodos utilitários
string Produto::toString() const {
    ostringstream oss;
    oss << nome << " - R$" << fixed << setprecision(2) << preco 
        << " - " << quantidade << " unid.";
    return oss.str();
}

void Produto::reduzirQuantidade(int qtd) {
    if (qtd <= quantidade) {
        quantidade -= qtd;
    }
}

bool Produto::temEstoque() const {
    return quantidade > 0;
}

bool Produto::temEstoqueSuficiente(int qtd) const {
    return quantidade >= qtd;
}
