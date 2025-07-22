#ifndef COMPRESSAO_VENDAS_H
#define COMPRESSAO_VENDAS_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <fstream>
#include "CompressorHuffman.h"

using namespace std;

// Estrutura para representar uma venda
struct VendaCompressao {
    string produto;
    int quantidade;
    double valor;
    string data;
    string cliente;
    
    VendaCompressao(const string& p, int q, double v, const string& d, const string& c);
    string toString() const;
};

// Classe para compressão RLE (Run-Length Encoding)
class CompressorRLE {
public:
    string comprimir(const string& dados);
    string descomprimir(const string& dadosComprimidos);
    void demonstrar();
};

// Classe para compressão Huffman especializada em vendas
class CompressorVendasHuffman {
private:
    map<char, int> frequencias;
    map<char, string> codigos;
    NoHuffman* raiz;
    
    void construirArvore(const string& dados);
    void gerarCodigos(NoHuffman* no, const string& codigo);
    
public:
    CompressorVendasHuffman();
    string comprimir(const string& dados);
    string descomprimir(const string& dadosComprimidos);
    void analisarEficiencia(const string& dados);
};

// Classe para gerar dados de teste
class GeradorVendas {
public:
    vector<VendaCompressao> gerarVendasAleatorias(int quantidade);
    string converterParaTexto(const vector<VendaCompressao>& vendas);
};

// Sistema principal de compressão de vendas
class SistemaCompressaoVendas {
private:
    CompressorRLE compressorRLE;
    CompressorVendasHuffman compressorHuffman;
    GeradorVendas gerador;
    
public:
    void menu();
    void testarVolumes();
    void compararMetodos();
    void analisarPerformance();
    void salvarRelatorios();
    void demonstrarCompleto();
};

#endif // COMPRESSAO_VENDAS_H
