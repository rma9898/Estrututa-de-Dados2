#include "../Include/HashTable.h"
#include <iostream>
#include <cmath>
#include <sstream>

using std::cout;
using std::endl;

// ======== IMPLEMENTAÇÃO DA CLASSE HashTableEncadeamentoLimite ========
HashTableEncadeamentoLimite::HashTableEncadeamentoLimite(int tam, int limite) 
    : tamanho(tam), limiteColisoes(limite), tabela(tam) {}

int HashTableEncadeamentoLimite::funcaoHash(const string& chave) {
    int hash = 0;
    for (char c : chave) {
        hash = (hash * 31 + c) % tamanho;
    }
    return hash;
}

void HashTableEncadeamentoLimite::inserir(const string& chave, int valor) {
    int indice = funcaoHash(chave);
    
    // Verifica se já existe a chave (atualização)
    for (auto& par : tabela[indice]) {
        if (par.first == chave) {
            par.second = valor;
            return;
        }
    }
    
    // Verifica se excede o limite
    if (tabela[indice].size() >= limiteColisoes) {
        cout << "⚠️ LIMITE DE COLISÕES EXCEDIDO no índice " << indice << "!\n";
        if (precisaReorganizar()) {
            cout << "🔄 Sugerindo reorganização da tabela...\n";
        }
    }
    
    tabela[indice].push_back({chave, valor});
}

bool HashTableEncadeamentoLimite::buscar(const string& chave, int& valor) {
    int indice = funcaoHash(chave);
    for (const auto& par : tabela[indice]) {
        if (par.first == chave) {
            valor = par.second;
            return true;
        }
    }
    return false;
}

bool HashTableEncadeamentoLimite::remover(const string& chave) {
    int indice = funcaoHash(chave);
    auto& lista = tabela[indice];
    
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        if (it->first == chave) {
            lista.erase(it);
            return true;
        }
    }
    return false;
}

void HashTableEncadeamentoLimite::imprimir() {
    cout << "\n--- HASH TABLE COM ENCADEAMENTO LIMITE ---\n";
    cout << "Limite de colisões por posição: " << limiteColisoes << "\n\n";
    
    for (int i = 0; i < tamanho; i++) {
        cout << "Índice " << i << ": ";
        if (tabela[i].empty()) {
            cout << "[VAZIO]";
        } else {
            cout << "[";
            for (size_t j = 0; j < tabela[i].size(); j++) {
                cout << tabela[i][j].first << ":" << tabela[i][j].second;
                if (j < tabela[i].size() - 1) cout << ", ";
            }
            cout << "]";
            
            if (tabela[i].size() > limiteColisoes) {
                cout << " ⚠️ EXCEDE LIMITE!";
            }
        }
        cout << "\n";
    }
}

void HashTableEncadeamentoLimite::mostrarEstatisticas() {
    cout << "\n--- ESTATÍSTICAS: ENCADEAMENTO LIMITE ---\n";
    cout << "Limite de colisões por posição: " << limiteColisoes << "\n";
    
    int colisoes = 0;
    int espacosVazios = 0;
    int violacoes = 0;
    int totalElementos = 0;
    
    for (int i = 0; i < tamanho; i++) {
        int tamanhoLista = tabela[i].size();
        totalElementos += tamanhoLista;
        
        if (tamanhoLista == 0) {
            espacosVazios++;
        } else if (tamanhoLista > 1) {
            colisoes += tamanhoLista - 1;
        }
        
        if (tamanhoLista > limiteColisoes) {
            violacoes++;
        }
    }
    
    cout << "Total de elementos: " << totalElementos << "\n";
    cout << "Total de colisões: " << colisoes << "\n";
    cout << "Espaços vazios: " << espacosVazios << "\n";
    cout << "Violações do limite: " << violacoes << "\n";
    cout << "Fator de carga: " << (double)totalElementos / tamanho << "\n";
    
    if (violacoes > 0) {
        cout << "⚠️ Recomenda-se reorganização da tabela!\n";
    }
}

bool HashTableEncadeamentoLimite::precisaReorganizar() {
    int violacoes = 0;
    for (int i = 0; i < tamanho; i++) {
        if (tabela[i].size() > limiteColisoes) {
            violacoes++;
        }
    }
    return violacoes > tamanho / 4; // Mais de 25% das posições violam o limite
}

// ======== IMPLEMENTAÇÃO DA CLASSE HashTableTransformacaoRaiz ========
HashTableTransformacaoRaiz::HashTableTransformacaoRaiz(int tam) : tamanho(tam), tabela(tam) {}

int HashTableTransformacaoRaiz::funcaoHashRaiz(const string& chave) {
    // Transformação da Raiz: usa raiz quadrada da soma dos caracteres
    int soma = 0;
    for (char c : chave) {
        soma += c * c; // Eleva ao quadrado para amplificar diferenças
    }
    
    // Extrai a raiz quadrada e usa os dígitos do meio
    int raiz = (int)sqrt(soma);
    
    // Pega os dígitos do meio da raiz
    string strRaiz = to_string(raiz);
    int meio = 0;
    
    if (strRaiz.length() >= 2) {
        int inicio = strRaiz.length() / 2 - 1;
        meio = stoi(strRaiz.substr(inicio, 2));
    } else {
        meio = raiz;
    }
    
    return meio % tamanho;
}

void HashTableTransformacaoRaiz::inserir(const string& chave, int valor) {
    int indice = funcaoHashRaiz(chave);
    
    // Verifica se já existe a chave (atualização)
    for (auto& par : tabela[indice]) {
        if (par.first == chave) {
            par.second = valor;
            return;
        }
    }
    
    tabela[indice].push_back({chave, valor});
}

bool HashTableTransformacaoRaiz::buscar(const string& chave, int& valor) {
    int indice = funcaoHashRaiz(chave);
    for (const auto& par : tabela[indice]) {
        if (par.first == chave) {
            valor = par.second;
            return true;
        }
    }
    return false;
}

bool HashTableTransformacaoRaiz::remover(const string& chave) {
    int indice = funcaoHashRaiz(chave);
    auto& lista = tabela[indice];
    
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        if (it->first == chave) {
            lista.erase(it);
            return true;
        }
    }
    return false;
}

void HashTableTransformacaoRaiz::imprimir() {
    cout << "\n--- HASH TABLE COM TRANSFORMAÇÃO DA RAIZ ---\n";
    cout << "Método: Transformação usando raiz quadrada\n\n";
    
    for (int i = 0; i < tamanho; i++) {
        cout << "Índice " << i << ": ";
        if (tabela[i].empty()) {
            cout << "[VAZIO]";
        } else {
            cout << "[";
            for (size_t j = 0; j < tabela[i].size(); j++) {
                cout << tabela[i][j].first << ":" << tabela[i][j].second;
                if (j < tabela[i].size() - 1) cout << ", ";
            }
            cout << "]";
        }
        cout << "\n";
    }
}

void HashTableTransformacaoRaiz::mostrarEstatisticas() {
    cout << "\n--- ESTATÍSTICAS: TRANSFORMAÇÃO DA RAIZ ---\n";
    
    int colisoes = 0;
    int espacosVazios = 0;
    int totalElementos = 0;
    
    for (int i = 0; i < tamanho; i++) {
        int tamanhoLista = tabela[i].size();
        totalElementos += tamanhoLista;
        
        if (tamanhoLista == 0) {
            espacosVazios++;
        } else if (tamanhoLista > 1) {
            colisoes += tamanhoLista - 1;
        }
    }
    
    cout << "Total de elementos: " << totalElementos << "\n";
    cout << "Total de colisões: " << colisoes << "\n";
    cout << "Espaços vazios: " << espacosVazios << "\n";
    cout << "Fator de carga: " << (double)totalElementos / tamanho << "\n";
    cout << "Método: Transformação da Raiz (sqrt + dígitos do meio)\n";
}

void HashTableTransformacaoRaiz::demonstrarTransformacao(const string& chave) {
    cout << "\n--- DEMONSTRAÇÃO DA TRANSFORMAÇÃO DA RAIZ ---\n";
    cout << "Chave: '" << chave << "'\n";
    
    int soma = 0;
    cout << "Soma dos quadrados dos caracteres: ";
    for (size_t i = 0; i < chave.length(); i++) {
        int quadrado = chave[i] * chave[i];
        soma += quadrado;
        cout << chave[i] << "²(" << quadrado << ")";
        if (i < chave.length() - 1) cout << " + ";
    }
    cout << " = " << soma << "\n";
    
    int raiz = (int)sqrt(soma);
    cout << "Raiz quadrada: sqrt(" << soma << ") = " << raiz << "\n";
    
    string strRaiz = to_string(raiz);
    cout << "String da raiz: '" << strRaiz << "'\n";
    
    int indice = funcaoHashRaiz(chave);
    cout << "Índice final: " << indice << "\n";
}

// ======== IMPLEMENTAÇÃO DA CLASSE GerenciadorHash ========
void GerenciadorHash::demonstrarHashing() {
    cout << "\n***** Demonstração de Hash Tables *****\n";
    cout << "1. Encadeamento Limite\n";
    cout << "2. Transformação da Raiz\n";
    cout << "3. Comparar ambos os métodos\n";
    
    int opcao;
    cout << "Escolha uma opção (1-3): ";
    cin >> opcao;
    
    switch(opcao) {
        case 1: demonstrarEncadeamentoLimite(); break;
        case 2: demonstrarTransformacaoRaiz(); break;
        case 3: compararMetodosHash(); break;
        default: cout << "Opção inválida!\n"; break;
    }
}

void GerenciadorHash::sistemaHashCompleto() {
    cout << "\n***** Sistema Hash Completo *****\n";
    cout << "1. Encadeamento Limite\n";
    cout << "2. Transformação da Raiz\n";
    cout << "3. Comparar métodos\n";
    cout << "4. Teste com dados personalizados\n";
    
    int opcao;
    cout << "Escolha uma opção (1-4): ";
    cin >> opcao;
    
    switch(opcao) {
        case 1: demonstrarEncadeamentoLimite(); break;
        case 2: demonstrarTransformacaoRaiz(); break;
        case 3: compararMetodosHash(); break;
        case 4: testePersonalizado(); break;
        default: cout << "Opção inválida!\n"; break;
    }
}

void GerenciadorHash::demonstrarEncadeamentoLimite() {
    cout << "\n=== DEMONSTRAÇÃO: ENCADEAMENTO LIMITE ===\n";
    
    vector<pair<string, int>> dadosTeste = {
        {"Cafe", 30}, {"Acucar", 50}, {"Arroz", 80}, {"Feijao", 60},
        {"Leite", 25}, {"Pao", 40}, {"Manteiga", 15}, {"Queijo", 20},
        {"Presunto", 10}, {"Iogurte", 35}
    };
    
    HashTableEncadeamentoLimite hashLimite(7, 2); // Limite de 2 elementos
    
    cout << "Inserindo elementos com limite de 2 colisões por posição:\n";
    for (const auto& item : dadosTeste) {
        cout << "Inserindo: " << item.first << " -> " << item.second << "\n";
        hashLimite.inserir(item.first, item.second);
    }
    
    hashLimite.imprimir();
    hashLimite.mostrarEstatisticas();
    
    // Teste de busca
    int valor;
    if (hashLimite.buscar("Cafe", valor)) {
        cout << "\n✅ Busca por 'Cafe': Encontrado! Quantidade = " << valor << "\n";
    }
}

void GerenciadorHash::demonstrarTransformacaoRaiz() {
    cout << "\n=== DEMONSTRAÇÃO: TRANSFORMAÇÃO DA RAIZ ===\n";
    
    vector<pair<string, int>> dadosTeste = {
        {"Cafe", 30}, {"Acucar", 50}, {"Arroz", 80}, {"Feijao", 60},
        {"Leite", 25}, {"Pao", 40}, {"Manteiga", 15}, {"Queijo", 20}
    };
    
    HashTableTransformacaoRaiz hashRaiz(11);
    
    // Demonstra a transformação para algumas chaves
    cout << "\n--- PROCESSO DE TRANSFORMAÇÃO ---\n";
    for (int i = 0; i < 3 && i < dadosTeste.size(); i++) {
        hashRaiz.demonstrarTransformacao(dadosTeste[i].first);
        cout << "\n";
    }
    
    // Insere todos os elementos
    cout << "--- INSERINDO ELEMENTOS ---\n";
    for (const auto& item : dadosTeste) {
        hashRaiz.inserir(item.first, item.second);
        cout << "Inserido: " << item.first << " -> " << item.second << "\n";
    }
    
    hashRaiz.imprimir();
    hashRaiz.mostrarEstatisticas();
    
    // Teste de busca
    int valor;
    if (hashRaiz.buscar("Cafe", valor)) {
        cout << "\n✅ Busca por 'Cafe': Encontrado! Quantidade = " << valor << "\n";
    }
}

void GerenciadorHash::compararMetodosHash() {
    cout << "\n=== COMPARAÇÃO: ENCADEAMENTO LIMITE vs TRANSFORMAÇÃO DA RAIZ ===\n";
    
    vector<pair<string, int>> dadosTeste = {
        {"Cafe", 30}, {"Acucar", 50}, {"Arroz", 80}, {"Feijao", 60},
        {"Leite", 25}, {"Pao", 40}, {"Manteiga", 15}, {"Queijo", 20},
        {"Presunto", 10}, {"Iogurte", 35}
    };
    
    cout << "Dados de teste: ";
    for (const auto& item : dadosTeste) {
        cout << item.first << " ";
    }
    cout << "\n\n";
    
    // Teste com Encadeamento Limite
    cout << "🔗 ENCADEAMENTO LIMITE:\n";
    HashTableEncadeamentoLimite hashLimite(7, 2);
    for (const auto& item : dadosTeste) {
        hashLimite.inserir(item.first, item.second);
    }
    hashLimite.mostrarEstatisticas();
    
    // Teste com Transformação da Raiz
    cout << "\n🌿 TRANSFORMAÇÃO DA RAIZ:\n";
    HashTableTransformacaoRaiz hashRaiz(7);
    for (const auto& item : dadosTeste) {
        hashRaiz.inserir(item.first, item.second);
    }
    hashRaiz.mostrarEstatisticas();
    
    cout << "\n--- CONCLUSÕES ---\n";
    cout << "🔗 Encadeamento Limite: Controla o crescimento das listas de colisão\n";
    cout << "🌿 Transformação da Raiz: Distribuição baseada em transformação matemática\n";
    cout << "⚡ Ambos oferecem busca O(1) no caso médio\n";
}

void GerenciadorHash::testePersonalizado() {
    cout << "\n=== TESTE COM DADOS PERSONALIZADOS ===\n";
    cout << "Escolha o método:\n";
    cout << "1. Encadeamento Limite\n";
    cout << "2. Transformação da Raiz\n";
    
    int metodo;
    cout << "Método: ";
    cin >> metodo;
    
    int tamanho;
    cout << "Tamanho da tabela: ";
    cin >> tamanho;
    
    if (metodo == 1) {
        int limite;
        cout << "Limite de colisões: ";
        cin >> limite;
        
        HashTableEncadeamentoLimite hash(tamanho, limite);
        
        string chave;
        int valor;
        
        cout << "\nDigite pares (chave valor). Digite 'fim' para parar:\n";
        while (true) {
            cout << "Chave: ";
            cin >> chave;
            if (chave == "fim") break;
            
            cout << "Valor: ";
            cin >> valor;
            
            hash.inserir(chave, valor);
        }
        
        hash.imprimir();
        hash.mostrarEstatisticas();
        
    } else if (metodo == 2) {
        HashTableTransformacaoRaiz hash(tamanho);
        
        string chave;
        int valor;
        
        cout << "\nDigite pares (chave valor). Digite 'fim' para parar:\n";
        while (true) {
            cout << "Chave: ";
            cin >> chave;
            if (chave == "fim") break;
            
            cout << "Valor: ";
            cin >> valor;
            
            hash.inserir(chave, valor);
        }
        
        hash.imprimir();
        hash.mostrarEstatisticas();
    }
}
