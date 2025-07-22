#ifndef NOTA_FISCAL_H
#define NOTA_FISCAL_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sstream>
#include <limits>
#include "Produto.h"

using namespace std;

// Enumeração para formas de pagamento
enum class FormaPagamento {
    DINHEIRO,
    CARTAO_DEBITO,
    CARTAO_CREDITO,
    PIX
};

// Estrutura para item da nota fiscal
struct ItemNotaFiscal {
    string nomeProduto;
    double precoUnitario;
    int quantidade;
    double valorTotal;
    
    ItemNotaFiscal(const string& nome, double preco, int qtd);
    double calcularTotal() const;
    string toString() const;
};

// Classe principal para Nota Fiscal
class NotaFiscal {
private:
    static int proximoNumero;
    int numero;
    string dataHora;
    vector<ItemNotaFiscal> itens;
    FormaPagamento formaPagamento;
    double valorTotal;
    double desconto;
    double valorFinal;
    string nomeCliente;
    string cpfCliente;
    
    string obterDataHoraAtual();
    string formaPagamentoParaString(FormaPagamento forma);
    
public:
    // Construtor
    NotaFiscal(const string& cliente = "", const string& cpf = "");
    
    // Métodos para adicionar itens
    void adicionarItem(const Produto& produto, int quantidade);
    void adicionarItem(const string& nome, double preco, int quantidade);
    
    // Métodos para pagamento
    void definirFormaPagamento(FormaPagamento forma);
    void aplicarDesconto(double percentual);
    
    // Métodos para cálculos
    void calcularTotal();
    double getValorTotal() const;
    double getValorFinal() const;
    
    // Métodos para exibição e salvamento
    void exibirNotaFiscal();
    void salvarNotaFiscal();
    string gerarStringNotaFiscal();
    
    // Getters
    int getNumero() const;
    string getDataHora() const;
    FormaPagamento getFormaPagamento() const;
    vector<ItemNotaFiscal> getItens() const;
};

// Classe para gerenciar vendas e notas fiscais
class GerenciadorVendas {
private:
    vector<NotaFiscal> notasFiscais;
    double totalVendasDia;
    int totalNotasEmitidas;
    
public:
    GerenciadorVendas();
    
    // Métodos principais
    NotaFiscal* criarNovaVenda(const string& cliente = "", const string& cpf = "");
    void finalizarVenda(NotaFiscal& nota);
    void adicionarNotaFiscal(const NotaFiscal& nota);
    
    // Relatórios
    void exibirResumoVendas();
    void exibirVendasPorFormaPagamento();
    void salvarRelatorioVendas();
    
    // Consultas
    vector<NotaFiscal> buscarNotasPorCliente(const string& cliente);
    NotaFiscal* buscarNotaPorNumero(int numero);
    
    // Getters
    double getTotalVendasDia() const;
    int getTotalNotasEmitidas() const;
    vector<NotaFiscal> getNotasFiscais() const;
    
    // Métodos para escolha de forma de pagamento
    FormaPagamento escolherFormaPagamento();
    void processarPagamento(NotaFiscal& nota, FormaPagamento forma);
};

#endif // NOTA_FISCAL_H
