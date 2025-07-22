#include "../Include/CompressaoVendas.h"
#include <sstream>

// Implementação da estrutura VendaCompressao
VendaCompressao::VendaCompressao(const string& p, int q, double v, const string& d, const string& c)
    : produto(p), quantidade(q), valor(v), data(d), cliente(c) {}

string VendaCompressao::toString() const {
    ostringstream oss;
    oss << produto << ";" << quantidade << ";" << fixed << setprecision(2) << valor 
        << ";" << data << ";" << cliente;
    return oss.str();
}

// Implementação da classe CompressorRLE
string CompressorRLE::comprimir(const string& dados) {
    if (dados.empty()) return "";
    
    string resultado;
    char caractereAtual = dados[0];
    int contador = 1;
    
    for (size_t i = 1; i < dados.size(); i++) {
        if (dados[i] == caractereAtual && contador < 255) {
            contador++;
        } else {
            resultado += to_string(contador) + caractereAtual;
            caractereAtual = dados[i];
            contador = 1;
        }
    }
    resultado += to_string(contador) + caractereAtual;
    
    return resultado;
}

string CompressorRLE::descomprimir(const string& dadosComprimidos) {
    string resultado;
    for (size_t i = 0; i < dadosComprimidos.size(); i += 2) {
        if (i + 1 < dadosComprimidos.size()) {
            int contador = dadosComprimidos[i] - '0';
            char caractere = dadosComprimidos[i + 1];
            resultado += string(contador, caractere);
        }
    }
    return resultado;
}

void CompressorRLE::demonstrar() {
    cout << "\n=== Demonstração RLE ===\n";
    string teste = "AAAABBBBCCCCDDDD";
    cout << "Original: " << teste << " (tamanho: " << teste.size() << ")\n";
    
    string comprimido = comprimir(teste);
    cout << "Comprimido: " << comprimido << " (tamanho: " << comprimido.size() << ")\n";
    
    string descomprimido = descomprimir(comprimido);
    cout << "Descomprimido: " << descomprimido << "\n";
    cout << "Taxa de compressão: " << fixed << setprecision(1) 
         << (1.0 - (double)comprimido.size() / teste.size()) * 100 << "%\n";
}

// Implementação da classe CompressorVendasHuffman
CompressorVendasHuffman::CompressorVendasHuffman() : raiz(nullptr) {}

void CompressorVendasHuffman::construirArvore(const string& dados) {
    frequencias.clear();
    for (char c : dados) {
        frequencias[c]++;
    }
    
    priority_queue<NoHuffman*, vector<NoHuffman*>, ComparadorHuffman> fila;
    
    for (const auto& par : frequencias) {
        fila.push(new NoHuffman(par.first, par.second));
    }
    
    while (fila.size() > 1) {
        NoHuffman* direita = fila.top(); fila.pop();
        NoHuffman* esquerda = fila.top(); fila.pop();
        
        NoHuffman* novo = new NoHuffman(esquerda->frequencia + direita->frequencia);
        novo->esquerda = esquerda;
        novo->direita = direita;
        
        fila.push(novo);
    }
    
    raiz = fila.empty() ? nullptr : fila.top();
    
    codigos.clear();
    if (raiz && raiz->caractere != '\0') {
        codigos[raiz->caractere] = "0";
    } else {
        gerarCodigos(raiz, "");
    }
}

void CompressorVendasHuffman::gerarCodigos(NoHuffman* no, const string& codigo) {
    if (!no) return;
    
    if (no->caractere != '\0') {
        codigos[no->caractere] = codigo;
        return;
    }
    
    gerarCodigos(no->esquerda, codigo + "0");
    gerarCodigos(no->direita, codigo + "1");
}

string CompressorVendasHuffman::comprimir(const string& dados) {
    construirArvore(dados);
    
    string resultado;
    for (char c : dados) {
        resultado += codigos[c];
    }
    
    return resultado;
}

void CompressorVendasHuffman::analisarEficiencia(const string& dados) {
    auto inicio = chrono::high_resolution_clock::now();
    string comprimido = comprimir(dados);
    auto fim = chrono::high_resolution_clock::now();
    
    auto duracao = chrono::duration_cast<chrono::microseconds>(fim - inicio);
    
    cout << "Tamanho original: " << dados.size() << " bytes\n";
    cout << "Tamanho comprimido: " << comprimido.size() / 8 << " bytes (aprox.)\n";
    cout << "Taxa de compressão: " << fixed << setprecision(1) 
         << (1.0 - (double)(comprimido.size() / 8) / dados.size()) * 100 << "%\n";
    cout << "Tempo de compressão: " << duracao.count() << " microsegundos\n";
}

// Implementação da classe GeradorVendas
vector<VendaCompressao> GeradorVendas::gerarVendasAleatorias(int quantidade) {
    vector<VendaCompressao> vendas;
    vector<string> produtos = {"Arroz", "Feijao", "Acucar", "Cafe", "Leite", "Pao"};
    vector<string> clientes = {"Ana", "Bruno", "Carlos", "Diana", "Eduardo"};
    
    srand(time(nullptr));
    
    for (int i = 0; i < quantidade; i++) {
        string produto = produtos[rand() % produtos.size()];
        int qtd = rand() % 10 + 1;
        double valor = (rand() % 5000 + 500) / 100.0;
        string data = "2024-01-" + to_string((rand() % 30) + 1);
        string cliente = clientes[rand() % clientes.size()];
        
        vendas.emplace_back(produto, qtd, valor, data, cliente);
    }
    
    return vendas;
}

string GeradorVendas::converterParaTexto(const vector<VendaCompressao>& vendas) {
    string resultado;
    for (const auto& venda : vendas) {
        resultado += venda.toString() + "\n";
    }
    return resultado;
}

// Implementação da classe SistemaCompressaoVendas
void SistemaCompressaoVendas::menu() {
    cout << "\n***** Sistema de Compressão de Vendas *****\n";
    cout << "1. Testar diferentes volumes de dados\n";
    cout << "2. Comparar métodos RLE vs Huffman\n";
    cout << "3. Análise de performance detalhada\n";
    cout << "4. Salvar relatórios comprimidos\n";
    cout << "5. Demonstração completa\n";
    cout << "6. Voltar ao menu principal\n";
}

void SistemaCompressaoVendas::testarVolumes() {
    cout << "\n=== Teste de Volumes ===\n";
    vector<int> volumes = {100, 1000, 5000, 10000};
    
    for (int vol : volumes) {
        cout << "\n--- Volume: " << vol << " vendas ---\n";
        auto vendas = gerador.gerarVendasAleatorias(vol);
        string dados = gerador.converterParaTexto(vendas);
        
        compressorHuffman.analisarEficiencia(dados);
    }
}

void SistemaCompressaoVendas::compararMetodos() {
    cout << "\n=== Comparação RLE vs Huffman ===\n";
    
    auto vendas = gerador.gerarVendasAleatorias(1000);
    string dados = gerador.converterParaTexto(vendas);
    
    cout << "\nMétodo RLE:\n";
    compressorRLE.demonstrar();
    
    cout << "\nMétodo Huffman:\n";
    compressorHuffman.analisarEficiencia(dados);
}

void SistemaCompressaoVendas::analisarPerformance() {
    cout << "\n=== Análise de Performance ===\n";
    
    vector<int> tamanhos = {500, 2000, 8000};
    
    for (int tam : tamanhos) {
        auto vendas = gerador.gerarVendasAleatorias(tam);
        string dados = gerador.converterParaTexto(vendas);
        
        cout << "\n--- Dataset: " << tam << " registros ---\n";
        
        auto inicio = chrono::high_resolution_clock::now();
        string huffman = compressorHuffman.comprimir(dados);
        auto fim = chrono::high_resolution_clock::now();
        auto duracaoHuffman = chrono::duration_cast<chrono::microseconds>(fim - inicio);
        
        inicio = chrono::high_resolution_clock::now();
        string rle = compressorRLE.comprimir(dados);
        fim = chrono::high_resolution_clock::now();
        auto duracaoRLE = chrono::duration_cast<chrono::microseconds>(fim - inicio);
        
        cout << "Huffman: " << duracaoHuffman.count() << "μs, Compressão: " 
             << fixed << setprecision(1) << (1.0 - (double)(huffman.size()/8) / dados.size()) * 100 << "%\n";
        cout << "RLE: " << duracaoRLE.count() << "μs, Compressão: " 
             << (1.0 - (double)rle.size() / dados.size()) * 100 << "%\n";
    }
}

void SistemaCompressaoVendas::salvarRelatorios() {
    cout << "\n=== Salvando Relatórios Comprimidos ===\n";
    
    auto vendas = gerador.gerarVendasAleatorias(2000);
    string dados = gerador.converterParaTexto(vendas);
    
    // Salvar original
    ofstream arquivo("relatorio_vendas_original.txt");
    arquivo << dados;
    arquivo.close();
    
    // Salvar comprimido Huffman
    string huffmanComp = compressorHuffman.comprimir(dados);
    ofstream arquivoHuffman("relatorio_vendas_huffman.bin", ios::binary);
    arquivoHuffman << huffmanComp;
    arquivoHuffman.close();
    
    // Salvar comprimido RLE
    string rleComp = compressorRLE.comprimir(dados);
    ofstream arquivoRLE("relatorio_vendas_rle.txt");
    arquivoRLE << rleComp;
    arquivoRLE.close();
    
    cout << "Relatórios salvos:\n";
    cout << "- relatorio_vendas_original.txt\n";
    cout << "- relatorio_vendas_huffman.bin\n";
    cout << "- relatorio_vendas_rle.txt\n";
    
    cout << "\nTamanhos dos arquivos:\n";
    cout << "Original: " << dados.size() << " bytes\n";
    cout << "Huffman: ~" << huffmanComp.size() / 8 << " bytes\n";
    cout << "RLE: " << rleComp.size() << " bytes\n";
}

void SistemaCompressaoVendas::demonstrarCompleto() {
    cout << "\n***** Demonstração Completa do Sistema *****\n";
    
    compressorRLE.demonstrar();
    cout << "\n" << string(50, '=') << "\n";
    
    auto vendas = gerador.gerarVendasAleatorias(500);
    string dados = gerador.converterParaTexto(vendas);
    compressorHuffman.analisarEficiencia(dados);
}
