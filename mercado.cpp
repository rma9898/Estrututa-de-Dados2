#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <limits>
#include "mercado.h"  
#include <locale>

using namespace std;

// Declaração antecipada pra n da errokk

int RabinKarp(const string& texto, const string& padrao);

vector<string> produtos;  // Lista de produtos

// Função para cadastrar produto
void cadastrarProduto() {
    string nome;
    double preco;
    int quantidade;
    
    cout << "\n***** Cadastro de Produto *****\n";
    cout << "Digite o nome do produto: ";
    cin.ignore();  // Limpa o buffer de entrada
    getline(cin, nome);
    
   // garantir entrada valida do preço
    while (true) {
        cout << "Digite o preço do produto (use ponto para decimais, ex: 10.50): ";
        if (cin >> preco && preco >= 0 && preco <= 999999.99) {
            break; // Entrada válida, sai do loop
        } else {
            cout << "Erro! Digite um preço válido entre 0 e 999999.99 usando ponto (.) para decimais.\n";
            cin.clear(); // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
        }
    }
    
    // Loop para garantir entrada válida da quantidade
    while (true) {
        cout << "Digite a quantidade do produto: ";
        if (cin >> quantidade && quantidade >= 0 && quantidade <= 999999) {
            break;
        } else {
            cout << "Erro! Digite uma quantidade válida entre 0 e 999999.\n";
            cin.clear(); // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Formata o preço para duas casas decimais
    cout << fixed << setprecision(2);
    ostringstream oss;
    oss << fixed << setprecision(2) << preco;
  
    //ordena por nome
    produtos.push_back(nome + " - R$" + oss.str() + " - " + to_string(quantidade) + " unid.");
    cout << "Produto cadastrado com sucesso!\n";
    sort(produtos.begin(), produtos.end());
    salvarProdutosEmArquivo();  // Salva os produtos no arquivo após o cadastro
}

// Função para atualizar produto
void atualizarProduto() {
    string nome;
    cout << "\n***** Atualização de Produto *****\n";
    cout << "Digite o nome do produto a ser atualizado: ";
    cin.ignore();  // Limpa o buffer de entrada
    getline(cin, nome);

    // Usando a busca sequencial para encontrar o índice do produto
    int indice = buscaSequencial(produtos, nome);
    if (indice != -1) {
        double novoPreco;
        int novaQuantidade;
        cout << "Produto encontrado: " << produtos[indice] << endl;
        
        // Loop para garantir entrada válida do preço
        while (true) {
            cout << "Digite o novo preço do produto (use ponto para decimais, ex: 10.50): ";
            if (cin >> novoPreco && novoPreco >= 0 && novoPreco <= 999999.99) {
                break; // Entrada válida, sai do loop
            } else {
                cout << "Erro! Digite um preço válido entre 0 e 999999.99 usando ponto (.) para decimais.\n";
                cin.clear(); // Limpa o estado de erro
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
            }
        }
        
        // Loop para garantir entrada válida da quantidade
        while (true) {
            cout << "Digite a nova quantidade do produto: ";
            if (cin >> novaQuantidade && novaQuantidade >= 0 && novaQuantidade <= 999999) {
                break; // Entrada válida, sai do loop
            } else {
                cout << "Erro! Digite uma quantidade válida entre 0 e 999999.\n";
                cin.clear(); // Limpa o estado de erro
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
            }
        }

        // Atualiza a lista com o novo nome, preço e quantidade
        ostringstream oss;
        oss << fixed << setprecision(2) << novoPreco;
        produtos[indice] = nome + " - R$" + oss.str() + " - " + to_string(novaQuantidade) + " unid.";
        cout << "Produto atualizado com sucesso!\n";
        salvarProdutosEmArquivo(); // Salva as alterações
    } else {
        cout << "Produto não encontrado.\n";
    }
}

 void mostrarProdutos() {
    // Exibe a lista de produtos cadastrados
    cout << "\n***** Lista de Produtos *****\n";
    if (produtos.empty()) {
        cout << "Nenhum produto cadastrado.\n";
    } else {
        for (const auto& produto : produtos) {
            cout << produto << endl;
        }
    }
}

//busca produtos por letra usando Rabin-Karp
void buscaprodutoporletra() {
    cout << "\n***** Busca de Produtos por Letra usando Rabin-Karp *****\n";
    cout << "Digite a letra inicial para buscar: ";
    char letra;
    cin >> letra;
    letra = tolower(letra);  // Converte para minúsculo para fazer uma busca case-insensitive
    
    string padrao(1, letra); // Converte a letra para string para usar no Rabin-Karp
    vector<int> indicesEncontrados;  // Armazena os índices dos produtos encontrados
    cout << "\nProdutos encontrados com a letra '" << letra << "':\n";
    
    for (int i = 0; i < produtos.size(); i++) {
        string produtoLower = produtos[i];
        // Converte o produto para minúsculo para comparação
        transform(produtoLower.begin(), produtoLower.end(), produtoLower.begin(), ::tolower);
        
        // Usa Rabin-Karp para encontrar a letra no início do produto
        int pos = RabinKarp(produtoLower, padrao);
        
        // Se encontrou no início da string (posição 0)
        if (pos == 0) {
            indicesEncontrados.push_back(i);
            cout << indicesEncontrados.size() << ". " << produtos[i] << endl;
        }
    }
    
    if (indicesEncontrados.empty()) {
        cout << "Nenhum produto encontrado com a letra '" << letra << "'.\n";
        return;
    }
    
    // Se encontrou produtos, permite escolher qual comprar
    cout << "\nDeseja comprar algum produto? (s/n): ";
    char resposta;
    cin >> resposta;
    
    if (resposta == 's' || resposta == 'S') {
        int escolha;
        // Loop para validar entrada da escolha do produto
        while (true) {
            cout << "Digite o número do produto que deseja comprar (1-" << indicesEncontrados.size() << "): ";
            if (cin >> escolha && escolha >= 1 && escolha <= indicesEncontrados.size()) {
                break; // Entrada válida, sai do loop
            } else {
                cout << "Erro! Digite apenas números de 1 a " << indicesEncontrados.size() << ".\n";
                cin.clear(); // Limpa o estado de erro
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
            }
        }
        
        int indiceEscolhido = indicesEncontrados[escolha - 1];
        comprarProdutoPorIndice(indiceEscolhido);
    }
}

void simuladorComprasEVendas() {
    cout << "\n***** Simulador de Compras *****\n";
    cout << "Digite o nome do produto que deseja comprar: ";
    string nomeProduto;
    cin.ignore();  // Limpa o buffer de entrada
    getline(cin, nomeProduto);

    // Procura o produto usando busca binária (mais rápida para listas ordenadas)
    int indice = buscaBinaria(produtos, nomeProduto);
    if (indice != -1) {
        string produto = produtos[indice];
        
        // Extrai as informações do produto
        size_t pos_preco = produto.find("R$");
        size_t pos_qtd = produto.find(" - ", pos_preco + 2);
        size_t pos_unid = produto.find(" unid.");
        
        string nome = produto.substr(0, pos_preco - 3);
        double preco = stod(produto.substr(pos_preco + 2, pos_qtd - pos_preco - 2));
        int quantidade = stoi(produto.substr(pos_qtd + 3, pos_unid - pos_qtd - 3));

        cout << "\nProduto encontrado:\n";
        cout << "Nome: " << nome << "\n";
        cout << "Preço: R$" << fixed << setprecision(2) << preco << "\n";
        cout << "Quantidade disponível: " << quantidade << "\n\n";

        if (quantidade > 0) {
            int qtd_compra;
            // Loop para garantir entrada válida da quantidade
            while (true) {
                cout << "Quantas unidades deseja comprar? ";
                if (cin >> qtd_compra && qtd_compra > 0 && qtd_compra <= 999999) {
                    break; // Entrada válida, sai do loop
                } else {
                    cout << "Erro! Digite uma quantidade válida entre 1 e 999999.\n";
                    cin.clear(); // Limpa o estado de erro
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
                }
            }

            if (qtd_compra <= quantidade) {
                // Calcula o total
                double total = preco * qtd_compra;
                
                // Atualiza a quantidade
                quantidade -= qtd_compra;
                
                // Atualiza o produto no vetor
                ostringstream oss;
                oss << fixed << setprecision(2) << preco;
                produtos[indice] = nome + " - R$" + oss.str() + " - " + to_string(quantidade) + " unid.";
                
                cout << "\nCompra realizada com sucesso!\n";
                cout << "Total: R$" << fixed << setprecision(2) << total << "\n";
                cout << "Quantidade restante: " << quantidade << "\n";
                
                // Salva as alterações no arquivo
                salvarProdutosEmArquivo();
            } else {
                cout << "Quantidade insuficiente em estoque! Disponível: " << quantidade << "\n";
            }
        } else {
            cout << "Produto fora de estoque!\n";
        }
    } else {
        cout << "Produto não encontrado!\n";
    }
}

// Função de busca sequencial para produtos
int buscaSequencial(const vector<string>& produtos, const string& nome) {
    for (size_t i = 0; i < produtos.size(); ++i) {
        if (produtos[i].find(nome) != string::npos) {  // Verifica se o nome do produto contém o nome procurado
            return i;  // Retorna o índice do produto encontrado
        }
    }
    return -1;  // Retorna -1 se o produto não for encontrado
}

    int buscaBinaria(const vector<string>& produtos, const string& nome) {
    int esquerda = 0;
    int direita = produtos.size() - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (produtos[meio].find(nome) != string::npos) {
            return meio;
        }
        if (produtos[meio] < nome) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}
void salvarProdutosEmArquivo() {
    ofstream arquivo("produtos.txt");
    if (arquivo.is_open()) {
        for (const auto& produto : produtos) {
            arquivo << produto << endl;
        }
        arquivo.close();
        cout << "Produtos salvos com sucesso!\n";
    } else {
        cout << "Erro ao abrir o arquivo para salvar os produtos.\n";
    }
}
void carregarProdutosDeArquivo() {
    ifstream arquivo("produtos.txt");
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            produtos.push_back(linha);
        }
        arquivo.close();
       
        cout << "Produtos carregados com sucesso!\n";
    } else {
        cout << "Erro ao abrir o arquivo para carregar os produtos.\n";
    }
}
void ordenarListaProdutos() {
    sort(produtos.begin(), produtos.end());
    cout << "Produtos ordenados com sucesso!\n";
}

int RabinKarp(const string& texto, const string& padrao) {
    int n = texto.size();
    int m = padrao.size();
    const int d = 256; // Número de caracteres possíveis
    const int q = 101; // Um número primo para o módulo
    int h = 1;
    int p = 0; // Hash do padrão
    int t = 0; // Hash do texto

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p = (d * p + padrao[i]) % q;
        t = (d * t + texto[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            if (texto.substr(i, m) == padrao) {
                return i; // Padrão encontrado
            }
        }
        if (i < n - m) {
            t = (d * (t - texto[i] * h) + texto[i + m]) % q;
            if (t < 0) {
                t += q;
            }
        }
    }
    return -1; 

}

// Função auxiliar para comprar produto por índice
void comprarProdutoPorIndice(int indice) {
    if (indice < 0 || indice >= produtos.size()) {
        cout << "Índice inválido!\n";
        return;
    }
    
    string produto = produtos[indice];
    
    // Extrai as informações do produto
    size_t pos_preco = produto.find("R$");
    size_t pos_qtd = produto.find(" - ", pos_preco + 2);
    size_t pos_unid = produto.find(" unid.");
    
    string nome = produto.substr(0, pos_preco - 3);
    double preco = stod(produto.substr(pos_preco + 2, pos_qtd - pos_preco - 2));
    int quantidade = stoi(produto.substr(pos_qtd + 3, pos_unid - pos_qtd - 3));

    cout << "\n***** Detalhes do Produto *****\n";
    cout << "Nome: " << nome << "\n";
    cout << "Preço: R$" << fixed << setprecision(2) << preco << "\n";
    cout << "Quantidade disponível: " << quantidade << "\n\n";

    if (quantidade > 0) {
        int qtd_compra;
        // Loop para garantir entrada válida da quantidade
        while (true) {
            cout << "Quantas unidades deseja comprar? ";
            if (cin >> qtd_compra && qtd_compra > 0 && qtd_compra <= 999999) {
                break; // Entrada válida, sai do loop
            } else {
                cout << "Erro! Digite uma quantidade válida entre 1 e 999999.\n";
                cin.clear(); // Limpa o estado de erro
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
            }
        }

        if (qtd_compra <= quantidade) {
            // Calcula o total
            double total = preco * qtd_compra;
            
            // Atualiza a quantidade
            quantidade -= qtd_compra;
            
            // Atualiza o produto no vetor
            ostringstream oss;
            oss << fixed << setprecision(2) << preco;
            produtos[indice] = nome + " - R$" + oss.str() + " - " + to_string(quantidade) + " unid.";
            
            cout << "\nCompra realizada com sucesso!\n";
            cout << "Total: R$" << fixed << setprecision(2) << total << "\n";
            cout << "Quantidade restante: " << quantidade << "\n";
            
            // Salva as alterações no arquivo
            salvarProdutosEmArquivo();
        } else {
            cout << "Quantidade insuficiente em estoque! Disponível: " << quantidade << "\n";
        }
    } else {
        cout << "Produto fora de estoque!\n";
    }
}
