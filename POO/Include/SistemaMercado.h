#ifndef SISTEMA_MERCADO_H
#define SISTEMA_MERCADO_H

#include <vector>
#include <limits>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <locale>
#include "Produto.h"
#include "AlgoritmosBusca.h"
#include "CompressorHuffman.h"
#include "HashTable.h"
#include "CompressaoVendas.h"
#include "NotaFiscal.h"

using namespace std;

class SistemaMercado {
private:
    // Hash Tables para armazenamento real dos produtos
    HashTableEncadeamentoLimite hashProdutosLimite;
    HashTableTransformacaoRaiz hashProdutosRaiz;
    
    // Controle de qual método usar
    bool usarEncadeamentoLimite;
    
    // Vector auxiliar para compatibilidade com algoritmos existentes
    vector<Produto> produtos;  // Sincronizado com hash tables
    
    CompressorHuffman compressorHuffman;
    GerenciadorHash gerenciadorHash;  // Para demonstrações
    SistemaCompressaoVendas sistemaCompressao;
    GerenciadorVendas gerenciadorVendas;
    
    bool validarPreco(double& preco);
    bool validarQuantidade(int& quantidade);
    bool validarEscolha(int& escolha, int min, int max);
    
public:
    // Construtor
    SistemaMercado();
    
    // Métodos principais
    void cadastrarProduto();
    void atualizarProduto();
    void mostrarProdutos();
    void buscaProdutoPorLetra();
    void simuladorComprasEVendas();
    void comprarProdutoPorIndice(int indice);
    
    // Gerenciamento de arquivos
    void salvarProdutosEmArquivo();
    void carregarProdutosDeArquivo();
    void ordenarListaProdutos();
    
    // Funcionalidades avançadas
    void executarCompressaoHuffman();
    void executarDemonstracaoHashing();
    void executarSistemaHashCompleto();
    void executarSistemaCompressaoRelatorios();
    
    // Gerenciamento de Hash Tables para produtos
    void alternarMetodoHash();
    void sincronizarHashComVector();
    void sincronizarVectorComHash();
    Produto* buscarProdutoHash(const string& nome);
    void inserirProdutoHash(const Produto& produto);
    void atualizarProdutoHash(const string& nome, const Produto& novoProduto);
    void demonstrarTodosTiposBusca(); // NOVA FUNÇÃO - DEMONSTRA TODOS OS ALGORITMOS
    
    // Novo sistema de vendas com nota fiscal
    void novaVendaComNotaFiscal();
    void consultarNotasFiscais();
    void relatoriosVendas();
    
    // Menu principal
    void exibirMenu();
    void executarOpcao(int opcao);
    void iniciar();
};

#endif // SISTEMA_MERCADO_H
