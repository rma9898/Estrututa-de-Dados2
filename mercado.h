// mercado.h
#ifndef MERCADO_H
#define MERCADO_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>
#include <fstream>
#include <sstream>

// Declaração das funções
void cadastrarProduto();
void atualizarProduto();
int buscaSequencial(const std::vector<std::string>& produtos, const std::string& nome);
void mostrarProdutos();  // Função para mostrar todos os produtos cadastrados
int buscaBinaria(const std::vector<std::string>& produtos, const std::string& nome);
void salvarProdutosEmArquivo();
void carregarProdutosDeArquivo();
void ordenarListaProdutos();  // Função para ordenar a lista de produtos
void simuladorComprasEVendas();  // Função para simular compras e vendas
void buscaprodutoporletra();  // Função para buscar produtos por letra inicial
void comprarProdutoPorIndice(int indice);  // Função auxiliar para comprar produto por índice
int RabinKarp(const std::string& texto, const std::string& padrao);  // Função de busca Rabin-Karp




#endif // MERCADO_H
