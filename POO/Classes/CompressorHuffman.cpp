#include "../Include/CompressorHuffman.h"

// Implementação das estruturas NoHuffman e ComparadorHuffman
NoHuffman::NoHuffman(char c, int freq) : caractere(c), frequencia(freq), esquerda(nullptr), direita(nullptr) {}
NoHuffman::NoHuffman(int freq) : caractere('\0'), frequencia(freq), esquerda(nullptr), direita(nullptr) {}

bool ComparadorHuffman::operator()(NoHuffman* a, NoHuffman* b) {
    return a->frequencia > b->frequencia;
}

// Implementação da classe CompressorHuffman
map<char, int> CompressorHuffman::contarFrequencias(const string& texto) {
    map<char, int> frequencias;
    for (char c : texto) {
        frequencias[c]++;
    }
    return frequencias;
}

NoHuffman* CompressorHuffman::construirArvoreHuffman(const map<char, int>& frequencias) {
    priority_queue<NoHuffman*, vector<NoHuffman*>, ComparadorHuffman> filaPrioridade;
    
    for (const auto& par : frequencias) {
        filaPrioridade.push(new NoHuffman(par.first, par.second));
    }
    
    while (filaPrioridade.size() > 1) {
        NoHuffman* direita = filaPrioridade.top(); filaPrioridade.pop();
        NoHuffman* esquerda = filaPrioridade.top(); filaPrioridade.pop();
        
        NoHuffman* novoNo = new NoHuffman(esquerda->frequencia + direita->frequencia);
        novoNo->esquerda = esquerda;
        novoNo->direita = direita;
        
        filaPrioridade.push(novoNo);
    }
    
    return filaPrioridade.top();
}

void CompressorHuffman::gerarCodigosHuffman(NoHuffman* raiz, const string& codigo, map<char, string>& codigos) {
    if (!raiz) return;
    
    if (raiz->caractere != '\0') {
        codigos[raiz->caractere] = codigo.empty() ? "0" : codigo;
        return;
    }
    
    gerarCodigosHuffman(raiz->esquerda, codigo + "0", codigos);
    gerarCodigosHuffman(raiz->direita, codigo + "1", codigos);
}

void CompressorHuffman::demonstrarCompressao() {
    cout << "\n***** Demonstração de Compressão Huffman *****\n";
    cout << "Digite um texto para comprimir: ";
    string texto;
    cin.ignore();
    getline(cin, texto);
    
    if (texto.empty()) {
        cout << "Texto vazio!\n";
        return;
    }
    
    string textoComprimido = comprimir(texto);
    mostrarEstatisticas(texto, textoComprimido);
}

string CompressorHuffman::comprimir(const string& texto) {
    map<char, int> frequencias = contarFrequencias(texto);
    
    cout << "\n--- Frequência dos Caracteres ---\n";
    for (const auto& par : frequencias) {
        cout << "'" << par.first << "': " << par.second << " vezes\n";
    }
    
    NoHuffman* raiz = construirArvoreHuffman(frequencias);
    
    map<char, string> codigos;
    gerarCodigosHuffman(raiz, "", codigos);
    
    cout << "\n--- Códigos de Huffman ---\n";
    for (const auto& par : codigos) {
        cout << "'" << par.first << "': " << par.second << "\n";
    }
    
    string textoComprimido = "";
    for (char c : texto) {
        textoComprimido += codigos[c];
    }
    
    return textoComprimido;
}

void CompressorHuffman::mostrarEstatisticas(const string& textoOriginal, const string& textoComprimido) {
    cout << "\n--- Resultado da Compressão ---\n";
    cout << "Texto original: " << textoOriginal << "\n";
    cout << "Texto comprimido (binário): " << textoComprimido << "\n";
    cout << "Tamanho original: " << textoOriginal.length() * 8 << " bits\n";
    cout << "Tamanho comprimido: " << textoComprimido.length() << " bits\n";
    cout << "Taxa de compressão: " << fixed << setprecision(2) 
         << (1.0 - (double)textoComprimido.length() / (textoOriginal.length() * 8)) * 100 << "%\n";
}
