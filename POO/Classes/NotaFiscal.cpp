#include "../Include/NotaFiscal.h"

// Inicialização do número sequencial
int NotaFiscal::proximoNumero = 1001;

// ======== IMPLEMENTAÇÃO DA ESTRUTURA ITEMNOTAFISCAL ========

ItemNotaFiscal::ItemNotaFiscal(const string& nome, double preco, int qtd) 
    : nomeProduto(nome), precoUnitario(preco), quantidade(qtd) {
    valorTotal = calcularTotal();
}

double ItemNotaFiscal::calcularTotal() const {
    return precoUnitario * quantidade;
}

string ItemNotaFiscal::toString() const {
    ostringstream oss;
    oss << left << setw(20) << nomeProduto 
        << right << setw(8) << fixed << setprecision(2) << precoUnitario
        << right << setw(6) << quantidade
        << right << setw(10) << fixed << setprecision(2) << valorTotal;
    return oss.str();
}

// ======== IMPLEMENTAÇÃO DA CLASSE NOTAFISCAL ========

NotaFiscal::NotaFiscal(const string& cliente, const string& cpf) 
    : numero(proximoNumero++), nomeCliente(cliente), cpfCliente(cpf), 
      formaPagamento(FormaPagamento::DINHEIRO), valorTotal(0.0), 
      desconto(0.0), valorFinal(0.0) {
    dataHora = obterDataHoraAtual();
}

string NotaFiscal::obterDataHoraAtual() {
    time_t agora = time(0);
    tm* ltm = localtime(&agora);
    
    ostringstream oss;
    oss << setfill('0') << setw(2) << ltm->tm_mday << "/"
        << setw(2) << (ltm->tm_mon + 1) << "/"
        << (ltm->tm_year + 1900) << " "
        << setw(2) << ltm->tm_hour << ":"
        << setw(2) << ltm->tm_min << ":"
        << setw(2) << ltm->tm_sec;
    
    return oss.str();
}

string NotaFiscal::formaPagamentoParaString(FormaPagamento forma) {
    switch(forma) {
        case FormaPagamento::DINHEIRO: return "DINHEIRO";
        case FormaPagamento::CARTAO_DEBITO: return "CARTÃO DÉBITO";
        case FormaPagamento::CARTAO_CREDITO: return "CARTÃO CRÉDITO";
        case FormaPagamento::PIX: return "PIX";
        default: return "INDEFINIDO";
    }
}

void NotaFiscal::adicionarItem(const Produto& produto, int quantidade) {
    itens.emplace_back(produto.getNome(), produto.getPreco(), quantidade);
    calcularTotal();
}

void NotaFiscal::adicionarItem(const string& nome, double preco, int quantidade) {
    itens.emplace_back(nome, preco, quantidade);
    calcularTotal();
}

void NotaFiscal::definirFormaPagamento(FormaPagamento forma) {
    formaPagamento = forma;
}

void NotaFiscal::aplicarDesconto(double percentual) {
    if (percentual >= 0 && percentual <= 100) {
        desconto = percentual;
        calcularTotal();
    }
}

void NotaFiscal::calcularTotal() {
    valorTotal = 0.0;
    for (const auto& item : itens) {
        valorTotal += item.valorTotal;
    }
    
    double valorDesconto = valorTotal * (desconto / 100.0);
    valorFinal = valorTotal - valorDesconto;
}

double NotaFiscal::getValorTotal() const { return valorTotal; }
double NotaFiscal::getValorFinal() const { return valorFinal; }
int NotaFiscal::getNumero() const { return numero; }
string NotaFiscal::getDataHora() const { return dataHora; }
FormaPagamento NotaFiscal::getFormaPagamento() const { return formaPagamento; }
vector<ItemNotaFiscal> NotaFiscal::getItens() const { return itens; }

void NotaFiscal::exibirNotaFiscal() {
    cout << gerarStringNotaFiscal();
}

string NotaFiscal::gerarStringNotaFiscal() {
    ostringstream oss;
    
    oss << "\n" << string(60, '=') << "\n";
    oss << "                    NOTA FISCAL\n";
    oss << string(60, '=') << "\n";
    oss << "Número: " << numero << string(20, ' ') << "Data/Hora: " << dataHora << "\n";
    
    if (!nomeCliente.empty()) {
        oss << "Cliente: " << nomeCliente << "\n";
        if (!cpfCliente.empty()) {
            oss << "CPF: " << cpfCliente << "\n";
        }
    }
    
    oss << string(60, '-') << "\n";
    oss << left << setw(20) << "PRODUTO" 
        << right << setw(8) << "PREÇO"
        << right << setw(6) << "QTD"
        << right << setw(10) << "TOTAL" << "\n";
    oss << string(60, '-') << "\n";
    
    for (const auto& item : itens) {
        oss << item.toString() << "\n";
    }
    
    oss << string(60, '-') << "\n";
    oss << right << setw(44) << "SUBTOTAL: R$ " 
        << fixed << setprecision(2) << valorTotal << "\n";
    
    if (desconto > 0) {
        oss << right << setw(44) << "DESCONTO (" << desconto << "%): R$ " 
            << fixed << setprecision(2) << (valorTotal * desconto / 100.0) << "\n";
    }
    
    oss << right << setw(44) << "VALOR FINAL: R$ " 
        << fixed << setprecision(2) << valorFinal << "\n";
    oss << string(60, '-') << "\n";
    oss << "FORMA DE PAGAMENTO: " << formaPagamentoParaString(formaPagamento) << "\n";
    oss << string(60, '=') << "\n";
    oss << "            Obrigado pela preferência!\n";
    oss << string(60, '=') << "\n\n";
    
    return oss.str();
}

void NotaFiscal::salvarNotaFiscal() {
    string nomeArquivo = "nota_fiscal_" + to_string(numero) + ".txt";
    ofstream arquivo(nomeArquivo);
    
    if (arquivo.is_open()) {
        arquivo << gerarStringNotaFiscal();
        arquivo.close();
        cout << "Nota fiscal salva em: " << nomeArquivo << "\n";
    } else {
        cout << "Erro ao salvar nota fiscal!\n";
    }
}

// ======== IMPLEMENTAÇÃO DA CLASSE GERENCIADORVENDAS ========

GerenciadorVendas::GerenciadorVendas() : totalVendasDia(0.0), totalNotasEmitidas(0) {}

NotaFiscal* GerenciadorVendas::criarNovaVenda(const string& cliente, const string& cpf) {
    notasFiscais.emplace_back(cliente, cpf);
    return &notasFiscais.back();
}

void GerenciadorVendas::finalizarVenda(NotaFiscal& nota) {
    nota.calcularTotal();
    totalVendasDia += nota.getValorFinal();
    totalNotasEmitidas++;
    
    cout << "\n***** VENDA FINALIZADA *****\n";
    nota.exibirNotaFiscal();
    
    char salvar;
    cout << "Deseja salvar a nota fiscal em arquivo? (s/n): ";
    cin >> salvar;
    if (salvar == 's' || salvar == 'S') {
        nota.salvarNotaFiscal();
    }
}

void GerenciadorVendas::adicionarNotaFiscal(const NotaFiscal& nota) {
    notasFiscais.push_back(nota);
    totalVendasDia += nota.getValorFinal();
    totalNotasEmitidas++;
}

FormaPagamento GerenciadorVendas::escolherFormaPagamento() {
    int opcao;
    
    cout << "\n***** FORMA DE PAGAMENTO *****\n";
    cout << "1. Dinheiro\n";
    cout << "2. Cartão de Débito\n";
    cout << "3. Cartão de Crédito\n";
    cout << "4. PIX\n";
    cout << "Escolha a forma de pagamento (1-4): ";
    
    while (true) {
        if (cin >> opcao && opcao >= 1 && opcao <= 4) {
            break;
        } else {
            cout << "Opção inválida! Digite um número de 1 a 4: ";
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    switch(opcao) {
        case 1: return FormaPagamento::DINHEIRO;
        case 2: return FormaPagamento::CARTAO_DEBITO;
        case 3: return FormaPagamento::CARTAO_CREDITO;
        case 4: return FormaPagamento::PIX;
        default: return FormaPagamento::DINHEIRO;
    }
}

void GerenciadorVendas::processarPagamento(NotaFiscal& nota, FormaPagamento forma) {
    nota.definirFormaPagamento(forma);
    
    switch(forma) {
        case FormaPagamento::DINHEIRO:
            cout << "\n💰 PAGAMENTO EM DINHEIRO\n";
            cout << "Valor a receber: R$ " << fixed << setprecision(2) << nota.getValorFinal() << "\n";
            {
                double valorPago;
                cout << "Digite o valor pago pelo cliente: R$ ";
                cin >> valorPago;
                
                if (valorPago >= nota.getValorFinal()) {
                    double troco = valorPago - nota.getValorFinal();
                    cout << "Troco: R$ " << fixed << setprecision(2) << troco << "\n";
                } else {
                    cout << "Valor insuficiente! Faltam R$ " 
                         << fixed << setprecision(2) << (nota.getValorFinal() - valorPago) << "\n";
                    return;
                }
            }
            break;
            
        case FormaPagamento::CARTAO_DEBITO:
            cout << "\n💳 PAGAMENTO NO CARTÃO DE DÉBITO\n";
            cout << "Valor: R$ " << fixed << setprecision(2) << nota.getValorFinal() << "\n";
            cout << "Processando... Aprovado! ✅\n";
            break;
            
        case FormaPagamento::CARTAO_CREDITO:
            cout << "\n💳 PAGAMENTO NO CARTÃO DE CRÉDITO\n";
            cout << "Valor: R$ " << fixed << setprecision(2) << nota.getValorFinal() << "\n";
            cout << "Processando... Aprovado! ✅\n";
            break;
            
        case FormaPagamento::PIX:
            cout << "\n📱 PAGAMENTO VIA PIX\n";
            cout << "Valor: R$ " << fixed << setprecision(2) << nota.getValorFinal() << "\n";
            cout << "QR Code gerado! Aguarde confirmação...\n";
            cout << "Pagamento confirmado! ✅\n";
            break;
    }
    
    cout << "Pagamento processado com sucesso!\n";
}

void GerenciadorVendas::exibirResumoVendas() {
    cout << "\n***** RESUMO DE VENDAS DO DIA *****\n";
    cout << "Total de notas emitidas: " << totalNotasEmitidas << "\n";
    cout << "Valor total das vendas: R$ " << fixed << setprecision(2) << totalVendasDia << "\n";
    cout << "Ticket médio: R$ " << fixed << setprecision(2) 
         << (totalNotasEmitidas > 0 ? totalVendasDia / totalNotasEmitidas : 0.0) << "\n";
}

void GerenciadorVendas::exibirVendasPorFormaPagamento() {
    cout << "\n***** VENDAS POR FORMA DE PAGAMENTO *****\n";
    
    double dinheiro = 0, debito = 0, credito = 0, pix = 0;
    int countDinheiro = 0, countDebito = 0, countCredito = 0, countPix = 0;
    
    for (const auto& nota : notasFiscais) {
        switch(nota.getFormaPagamento()) {
            case FormaPagamento::DINHEIRO:
                dinheiro += nota.getValorFinal();
                countDinheiro++;
                break;
            case FormaPagamento::CARTAO_DEBITO:
                debito += nota.getValorFinal();
                countDebito++;
                break;
            case FormaPagamento::CARTAO_CREDITO:
                credito += nota.getValorFinal();
                countCredito++;
                break;
            case FormaPagamento::PIX:
                pix += nota.getValorFinal();
                countPix++;
                break;
        }
    }
    
    cout << "Dinheiro: " << countDinheiro << " vendas - R$ " 
         << fixed << setprecision(2) << dinheiro << "\n";
    cout << "Cartão Débito: " << countDebito << " vendas - R$ " 
         << fixed << setprecision(2) << debito << "\n";
    cout << "Cartão Crédito: " << countCredito << " vendas - R$ " 
         << fixed << setprecision(2) << credito << "\n";
    cout << "PIX: " << countPix << " vendas - R$ " 
         << fixed << setprecision(2) << pix << "\n";
}

void GerenciadorVendas::salvarRelatorioVendas() {
    ofstream arquivo("relatorio_vendas_dia.txt");
    
    if (arquivo.is_open()) {
        arquivo << "RELATÓRIO DE VENDAS DO DIA\n";
        arquivo << "==========================\n\n";
        arquivo << "Total de notas: " << totalNotasEmitidas << "\n";
        arquivo << "Valor total: R$ " << fixed << setprecision(2) << totalVendasDia << "\n\n";
        
        for (const auto& nota : notasFiscais) {
            arquivo << "Nota " << nota.getNumero() << " - " 
                   << nota.getDataHora() << " - R$ " 
                   << fixed << setprecision(2) << nota.getValorFinal() << "\n";
        }
        
        arquivo.close();
        cout << "Relatório salvo em: relatorio_vendas_dia.txt\n";
    }
}

vector<NotaFiscal> GerenciadorVendas::buscarNotasPorCliente(const string& cliente) {
    vector<NotaFiscal> resultado;
    for (const auto& nota : notasFiscais) {
        if (nota.getItens().size() > 0) { // Verifica se tem itens (simplificado)
            resultado.push_back(nota);
        }
    }
    return resultado;
}

NotaFiscal* GerenciadorVendas::buscarNotaPorNumero(int numero) {
    for (auto& nota : notasFiscais) {
        if (nota.getNumero() == numero) {
            return &nota;
        }
    }
    return nullptr;
}

double GerenciadorVendas::getTotalVendasDia() const { return totalVendasDia; }
int GerenciadorVendas::getTotalNotasEmitidas() const { return totalNotasEmitidas; }
vector<NotaFiscal> GerenciadorVendas::getNotasFiscais() const { return notasFiscais; }
