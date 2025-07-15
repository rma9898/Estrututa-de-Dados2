#include <iostream>
#include "mercado.h"
#include <locale.h>
#include <limits>

using namespace std;

void exibirMenu() {
    cout << "\n***** Menu do Sistema de Mercado *****\n";
    cout << "1. Cadastrar Produto\n";
    cout << "2. Atualizar Produto\n";
    cout << "3. Mostrar Todos os Produtos\n";
    cout << "4. Buscar Produto por Letra (Rabin-Karp)\n";
    cout << "5. Simular Compras e Vendas\n";
    cout << "6. Ordenar Lista de Produtos\n";
    cout << "0. Sair\n";
    cout << "Escolha uma opção: ";
}

int main() {
    setlocale(LC_ALL, NULL); 
    
    carregarProdutosDeArquivo();
    int opcao;

    do {
        exibirMenu();
        
        // Loop para validar entrada do menu
        while (true) {
            if (cin >> opcao && opcao >= 0 && opcao <= 6) {
                break; // Entrada válida, sai do loop
            } else {
                cout << "Erro! Digite apenas números de 0 a 6.\n";
                cout << "Escolha uma opção: ";
                cin.clear(); // Limpa o estado de erro
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
            }
        }

        switch(opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                atualizarProduto();
                break;
            case 3:
                mostrarProdutos();
                break;
            case 4:
                buscaprodutoporletra();
                break;
            case 5:
                simuladorComprasEVendas();
                break;
            case 6:
                ordenarListaProdutos();
                mostrarProdutos(); // Mostra a lista ordenada
                break;
            case 0:
                cout << "Saindo... Obrigado por usar o Sistema de Mercado!" << endl;
                break;
            default:
                cout << "Opção inválida, tente novamente!" << endl;
        }

    } while(opcao != 0);

    return 0;
}
