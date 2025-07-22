#ifndef COMPRESSOR_HUFFMAN_H
#define COMPRESSOR_HUFFMAN_H

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <iomanip>

using namespace std;

// Estrutura para nó da árvore de Huffman
struct NoHuffman {
    char caractere;
    int frequencia;
    NoHuffman* esquerda;
    NoHuffman* direita;
    
    NoHuffman(char c, int freq);
    NoHuffman(int freq);
};

// Comparador para a fila de prioridade (min-heap)
struct ComparadorHuffman {
    bool operator()(NoHuffman* a, NoHuffman* b);
};

class CompressorHuffman {
private:
    map<char, int> contarFrequencias(const string& texto);
    NoHuffman* construirArvoreHuffman(const map<char, int>& frequencias);
    void gerarCodigosHuffman(NoHuffman* raiz, const string& codigo, map<char, string>& codigos);
    
public:
    void demonstrarCompressao();
    string comprimir(const string& texto);
    void mostrarEstatisticas(const string& textoOriginal, const string& textoComprimido);
};

#endif // COMPRESSOR_HUFFMAN_H
