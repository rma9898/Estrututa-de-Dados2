#include "../Include/SistemaMercado.h"

// Construtor
SistemaMercado::SistemaMercado() 
    : hashProdutosLimite(17), hashProdutosRaiz(17), usarEncadeamentoLimite(true) {
    carregarProdutosDeArquivo();
    sincronizarHashComVector(); // Carrega produtos no hash após carregar do arquivo
}

// Métodos de validação
bool SistemaMercado::validarPreco(double& preco) {
    while (true) {
        cout << "Digite o preço do produto (ex: 10.50): ";
        if (cin >> preco && preco >= 0 && preco <= 999999.99) {
            return true;
        } else {
            cout << "Erro! Digite um preço válido entre 0 e 999999.99. Use ponto (.) para decimais.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool SistemaMercado::validarQuantidade(int& quantidade) {
    while (true) {
        cout << "Digite a quantidade do produto: ";
        if (cin >> quantidade && quantidade >= 0 && quantidade <= 999999) {
            return true;
        } else {
            cout << "Erro! Digite uma quantidade válida entre 0 e 999999.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool SistemaMercado::validarEscolha(int& escolha, int min, int max) {
    while (true) {
        cout << "Digite sua escolha (" << min << "-" << max << "): ";
        if (cin >> escolha && escolha >= min && escolha <= max) {
            return true;
        } else {
            cout << "Erro! Digite apenas números de " << min << " a " << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Métodos principais
void SistemaMercado::cadastrarProduto() {
    string nome;
    double preco;
    int quantidade;
    
    cout << "\n***** Cadastro de Produto *****\n";
    cout << "Digite o nome do produto: ";
    cin.ignore();
    getline(cin, nome);
    
    validarPreco(preco);
    validarQuantidade(quantidade);

    // Criar produto
    Produto novoProduto(nome, preco, quantidade);
    
    // Inserir no vector (para compatibilidade)
    produtos.push_back(novoProduto);
    
    // Inserir nas hash tables
    inserirProdutoHash(novoProduto);
    
    cout << "🏷️ Produto cadastrado usando método: " 
         << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz") << "\n";
    
    sort(produtos.begin(), produtos.end(), [](const Produto& a, const Produto& b) {
        return a.getNome() < b.getNome();
    });
    
    salvarProdutosEmArquivo();
}

void SistemaMercado::atualizarProduto() {
    string nome;
    cout << "\n***** Atualização de Produto *****\n";
    cout << "Digite o nome do produto a ser atualizado: ";
    cin.ignore();
    getline(cin, nome);

    // Buscar primeiro na hash table (mais eficiente)
    Produto* produtoHash = buscarProdutoHash(nome);
    
    if (produtoHash != nullptr) {
        double novoPreco;
        int novaQuantidade;
        cout << "🏷️ Produto encontrado via Hash (" 
             << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz")
             << "): " << produtoHash->toString() << endl;
        
        validarPreco(novoPreco);
        validarQuantidade(novaQuantidade);

        // Atualizar hash tables
        Produto produtoAtualizado(nome, novoPreco, novaQuantidade);
        atualizarProdutoHash(nome, produtoAtualizado);
        
        // Atualizar vector para compatibilidade
        int indice = AlgoritmosBusca::buscaSequencial(produtos, nome);
        if (indice != -1) {
            produtos[indice].setPreco(novoPreco);
            produtos[indice].setQuantidade(novaQuantidade);
        }
        
        cout << "✅ Produto atualizado via Hash Table!\n";
        salvarProdutosEmArquivo();
    } else {
        cout << "❌ Produto não encontrado na Hash Table.\n";
    }
}

void SistemaMercado::mostrarProdutos() {
    cout << "\n***** Lista de Produtos *****\n";
    if (produtos.empty()) {
        cout << "Nenhum produto cadastrado.\n";
    } else {
        for (const auto& produto : produtos) {
            cout << produto.toString() << endl;
        }
    }
}

void SistemaMercado::buscaProdutoPorLetra() {
    cout << "\n***** Busca de Produtos por Letra usando Rabin-Karp + Hash Table *****\n";
    cout << "Digite a letra inicial para buscar: ";
    char letra;
    cin >> letra;
    
    // 🚀 USAR RABIN-KARP NO VECTOR + HASH TABLE PARA BUSCA INDIVIDUAL
    vector<int> indicesEncontrados = AlgoritmosBusca::buscarPorLetra(produtos, letra);
    
    cout << "\n🔍 Produtos encontrados com Rabin-Karp + Hash Table (" 
         << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz")
         << "):\n";
    
    for (int i = 0; i < indicesEncontrados.size(); i++) {
        cout << (i + 1) << ". " << produtos[indicesEncontrados[i]].toString() << endl;
    }
    
    if (indicesEncontrados.empty()) {
        cout << "Nenhum produto encontrado com a letra '" << letra << "'.\n";
        return;
    }
    
    cout << "\nDeseja buscar um produto específico por nome exato? (s/n): ";
    char resposta;
    cin >> resposta;
    
    if (resposta == 's' || resposta == 'S') {
        string nomeProduto;
        cout << "Digite o nome exato do produto: ";
        cin.ignore();
        getline(cin, nomeProduto);
        
        // 🏷️ BUSCA INDIVIDUAL USANDO HASH TABLE
        Produto* produtoEncontrado = buscarProdutoHash(nomeProduto);
        
        if (produtoEncontrado != nullptr) {
            cout << "\n✅ Produto encontrado via Hash Table!\n";
            cout << "🏷️ Método: " << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz") << "\n";
            cout << produtoEncontrado->toString() << endl;
            
            cout << "\nDeseja comprar este produto? (s/n): ";
            char comprar;
            cin >> comprar;
            
            if (comprar == 's' || comprar == 'S') {
                // Encontrar índice do produto para usar a função de compra
                int indiceParaCompra = -1;
                for (size_t idx = 0; idx < produtos.size(); idx++) {
                    if (produtos[idx].getNome() == produtoEncontrado->getNome()) {
                        indiceParaCompra = static_cast<int>(idx);
                        break;
                    }
                }
                if (indiceParaCompra != -1) {
                    comprarProdutoPorIndice(indiceParaCompra);
                }
            }
        } else {
            cout << "❌ Produto não encontrado na Hash Table!\n";
        }
    } else {
        // Escolher produto da lista Rabin-Karp
        cout << "\nDeseja comprar algum produto da lista? (s/n): ";
        cin >> resposta;
        
        if (resposta == 's' || resposta == 'S') {
            int escolha;
            if (validarEscolha(escolha, 1, indicesEncontrados.size())) {
                int indiceEscolhido = indicesEncontrados[escolha - 1];
                comprarProdutoPorIndice(indiceEscolhido);
            }
        }
    }
}

void SistemaMercado::simuladorComprasEVendas() {
    cout << "\n***** Simulador de Compras *****\n";
    cout << "Digite o nome do produto que deseja comprar: ";
    string nomeProduto;
    cin.ignore();
    getline(cin, nomeProduto);

    // 🚀 BUSCA USANDO HASH TABLE em vez de busca binária!
    Produto* produtoEncontrado = buscarProdutoHash(nomeProduto);
    
    if (produtoEncontrado != nullptr) {
        cout << "\n🏷️ Produto encontrado via Hash Table (" 
             << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz")
             << ")!\n";
        
        cout << "\nProduto encontrado:\n";
        cout << "Nome: " << produtoEncontrado->getNome() << "\n";
        cout << "Preço: R$" << fixed << setprecision(2) << produtoEncontrado->getPreco() << "\n";
        cout << "Quantidade disponível: " << produtoEncontrado->getQuantidade() << "\n\n";

        if (produtoEncontrado->temEstoque()) {
            int qtd_compra;
            cout << "Digite a quantidade desejada: ";
            if (validarEscolha(qtd_compra, 1, 999999)) {
                if (produtoEncontrado->temEstoqueSuficiente(qtd_compra)) {
                    double total = produtoEncontrado->getPreco() * qtd_compra;
                    
                    cout << "\nCompra realizada com sucesso!\n";
                    cout << "Total: R$" << fixed << setprecision(2) << total << "\n";
                    
                    // **1. PRIMEIRO: ESCOLHER FORMA DE PAGAMENTO**
                    cout << "\n=== ESCOLHA A FORMA DE PAGAMENTO ===\n";
                    cout << "1. Dinheiro\n";
                    cout << "2. Cartão de Débito\n";
                    cout << "3. Cartão de Crédito\n";
                    cout << "4. PIX\n";
                    
                    int opcaoPagamento;
                    FormaPagamento formaPagamento;
                    
                    if (validarEscolha(opcaoPagamento, 1, 4)) {
                        switch (opcaoPagamento) {
                            case 1: 
                                formaPagamento = FormaPagamento::DINHEIRO;
                                cout << "\n💰 PAGAMENTO EM DINHEIRO\n";
                                {
                                    double valorPago;
                                    cout << "Digite o valor pago pelo cliente: R$ ";
                                    cin >> valorPago;
                                    
                                    if (valorPago >= total) {
                                        double troco = valorPago - total;
                                        cout << "Troco: R$ " << fixed << setprecision(2) << troco << "\n";
                                    } else {
                                        cout << "Valor insuficiente! Faltam R$ " 
                                             << fixed << setprecision(2) << (total - valorPago) << "\n";
                                        return;
                                    }
                                }
                                break;
                            case 2:
                                formaPagamento = FormaPagamento::CARTAO_DEBITO;
                                cout << "\n💳 PAGAMENTO NO CARTÃO DE DÉBITO\n";
                                cout << "Processando... Aprovado! ✅\n";
                                break;
                            case 3:
                                formaPagamento = FormaPagamento::CARTAO_CREDITO;
                                cout << "\n💳 PAGAMENTO NO CARTÃO DE CRÉDITO\n";
                                cout << "Processando... Aprovado! ✅\n";
                                break;
                            case 4:
                                formaPagamento = FormaPagamento::PIX;
                                cout << "\n📱 PAGAMENTO VIA PIX\n";
                                cout << "QR Code gerado! Aguarde confirmação...\n";
                                cout << "Pagamento confirmado! ✅\n";
                                break;
                        }
                        
                        cout << "Pagamento processado com sucesso!\n";
                        
                        // Atualizar estoque
                        produtoEncontrado->reduzirQuantidade(qtd_compra);
                        cout << "Quantidade restante: " << produtoEncontrado->getQuantidade() << "\n";
                        
                        // **2. DEPOIS: PERGUNTAR SE QUER GERAR NOTA FISCAL**
                        cout << "\nDeseja gerar uma nota fiscal para esta compra? (s/n): ";
                        char gerarNota;
                        cin >> gerarNota;
                        
                        if (gerarNota == 's' || gerarNota == 'S') {
                            cout << "\n=== GERANDO NOTA FISCAL ===\n";
                            
                            // Dados do cliente (opcionais)
                            string nomeCliente, cpfCliente;
                            cout << "Nome do cliente (opcional, Enter para pular): ";
                            cin.ignore();
                            getline(cin, nomeCliente);
                            
                            if (!nomeCliente.empty()) {
                                cout << "CPF do cliente (opcional, Enter para pular): ";
                                getline(cin, cpfCliente);
                            }
                            
                            // Criar nova venda com nota fiscal
                            NotaFiscal* novaVenda = gerenciadorVendas.criarNovaVenda(nomeCliente, cpfCliente);
                            
                            // Adicionar o produto à nota fiscal
                            novaVenda->adicionarItem(produtoEncontrado->getNome(), produtoEncontrado->getPreco(), qtd_compra);
                            
                            // Definir forma de pagamento na nota
                            novaVenda->definirFormaPagamento(formaPagamento);
                            
                            // Finalizar venda e exibir nota fiscal
                            gerenciadorVendas.finalizarVenda(*novaVenda);
                            
                            cout << "\n✅ Nota fiscal gerada com sucesso!\n";
                        } else {
                            cout << "\nCompra finalizada sem nota fiscal.\n";
                        }
                        
                        // Salvar produtos atualizados
                        salvarProdutosEmArquivo();
                    }
                } else {
                    cout << "Quantidade insuficiente em estoque! Disponível: " << produtoEncontrado->getQuantidade() << "\n";
                }
            }
        } else {
            cout << "Produto fora de estoque!\n";
        }
    } else {
        cout << "Produto não encontrado!\n";
    }
}

void SistemaMercado::comprarProdutoPorIndice(int indice) {
    if (indice < 0 || indice >= produtos.size()) {
        cout << "Índice inválido!\n";
        return;
    }
    
    Produto& produto = produtos[indice];
    
    cout << "\n***** Detalhes do Produto *****\n";
    cout << "Nome: " << produto.getNome() << "\n";
    cout << "Preço: R$" << fixed << setprecision(2) << produto.getPreco() << "\n";
    cout << "Quantidade disponível: " << produto.getQuantidade() << "\n\n";

    if (produto.temEstoque()) {
        int qtd_compra;
        if (validarEscolha(qtd_compra, 1, 999999)) {
            if (produto.temEstoqueSuficiente(qtd_compra)) {
                double total = produto.getPreco() * qtd_compra;
                produto.reduzirQuantidade(qtd_compra);
                
                cout << "\nCompra realizada com sucesso!\n";
                cout << "Total: R$" << fixed << setprecision(2) << total << "\n";
                cout << "Quantidade restante: " << produto.getQuantidade() << "\n";
                
                salvarProdutosEmArquivo();
            } else {
                cout << "Quantidade insuficiente em estoque! Disponível: " << produto.getQuantidade() << "\n";
            }
        }
    } else {
        cout << "Produto fora de estoque!\n";
    }
}

// Gerenciamento de arquivos
void SistemaMercado::salvarProdutosEmArquivo() {
    ofstream arquivo("produtos.txt");
    if (arquivo.is_open()) {
        for (const auto& produto : produtos) {
            arquivo << produto.toString() << endl;
        }
        arquivo.close();
        cout << "Produtos salvos com sucesso!\n";
    } else {
        cout << "Erro ao abrir o arquivo para salvar os produtos.\n";
    }
}

void SistemaMercado::carregarProdutosDeArquivo() {
    ifstream arquivo("produtos.txt");
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            // Parse da linha para extrair nome, preço e quantidade
            size_t pos_preco = linha.find("R$");
            size_t pos_qtd = linha.find(" - ", pos_preco + 2);
            size_t pos_unid = linha.find(" unid.");
            
            if (pos_preco != string::npos && pos_qtd != string::npos && pos_unid != string::npos) {
                string nome = linha.substr(0, pos_preco - 3);
                double preco = stod(linha.substr(pos_preco + 2, pos_qtd - pos_preco - 2));
                int quantidade = stoi(linha.substr(pos_qtd + 3, pos_unid - pos_qtd - 3));
                
                produtos.push_back(Produto(nome, preco, quantidade));
            }
        }
        arquivo.close();
        cout << "Produtos carregados com sucesso!\n";
    } 
    // Removido a mensagem de erro quando o arquivo não existe
    // pois é normal na primeira execução
}

void SistemaMercado::ordenarListaProdutos() {
    sort(produtos.begin(), produtos.end(), [](const Produto& a, const Produto& b) {
        return a.getNome() < b.getNome();
    });
    cout << "Produtos ordenados com sucesso!\n";
}

// Funcionalidades avançadas
void SistemaMercado::executarCompressaoHuffman() {
    compressorHuffman.demonstrarCompressao();
}

void SistemaMercado::executarDemonstracaoHashing() {
    gerenciadorHash.demonstrarHashing();
}

void SistemaMercado::executarSistemaHashCompleto() {
    gerenciadorHash.sistemaHashCompleto();
}

void SistemaMercado::executarSistemaCompressaoRelatorios() {
    int opcao;
    do {
        sistemaCompressao.menu();
        if (validarEscolha(opcao, 1, 6)) {
            switch (opcao) {
                case 1: sistemaCompressao.testarVolumes(); break;
                case 2: sistemaCompressao.compararMetodos(); break;
                case 3: sistemaCompressao.analisarPerformance(); break;
                case 4: sistemaCompressao.salvarRelatorios(); break;
                case 5: sistemaCompressao.demonstrarCompleto(); break;
                case 6: cout << "Voltando ao menu principal...\n"; break;
            }
        }
    } while (opcao != 6);
}

// Métodos de nota fiscal
void SistemaMercado::novaVendaComNotaFiscal() {
    cout << "\n=== NOVA VENDA COM NOTA FISCAL ===\n";
    
    if (produtos.empty()) {
        cout << "Nenhum produto cadastrado! Cadastre produtos primeiro.\n";
        return;
    }
    
    // Mostrar produtos disponíveis
    cout << "\nProdutos disponíveis:\n";
    for (size_t i = 0; i < produtos.size(); i++) {
        if (produtos[i].getQuantidade() > 0) {
            cout << i + 1 << ". " << produtos[i].toString() << "\n";
        }
    }
    
    vector<ItemNotaFiscal> itens;
    char continuar = 's';
    double totalVenda = 0.0;
    
    while (continuar == 's' || continuar == 'S') {
        int indiceProduto;
        cout << "\nEscolha o produto (número): ";
        cin >> indiceProduto;
        
        if (indiceProduto < 1 || indiceProduto > static_cast<int>(produtos.size())) {
            cout << "Produto inválido!\n";
            continue;
        }
        
        Produto& produto = produtos[indiceProduto - 1];
        
        if (produto.getQuantidade() <= 0) {
            cout << "Produto fora de estoque!\n";
            continue;
        }
        
        int quantidade;
        cout << "Quantidade desejada: ";
        cin >> quantidade;
        
        if (quantidade <= 0 || quantidade > produto.getQuantidade()) {
            cout << "Quantidade inválida! Disponível: " << produto.getQuantidade() << "\n";
            continue;
        }
        
        // Criar item da nota fiscal
        ItemNotaFiscal item(produto.getNome(), produto.getPreco(), quantidade);
        
        itens.push_back(item);
        totalVenda += item.valorTotal;
        
        // Atualizar estoque
        produto.setQuantidade(produto.getQuantidade() - quantidade);
        
        cout << "Item adicionado! Subtotal: R$ " << fixed << setprecision(2) << item.valorTotal << "\n";
        cout << "Total da venda até agora: R$ " << fixed << setprecision(2) << totalVenda << "\n";
        
        cout << "\nDeseja adicionar mais produtos? (s/n): ";
        cin >> continuar;
    }
    
    if (itens.empty()) {
        cout << "Nenhum item foi adicionado à venda.\n";
        return;
    }
    
    // Escolher forma de pagamento
    cout << "\n=== FORMA DE PAGAMENTO ===\n";
    cout << "1. Dinheiro\n";
    cout << "2. Cartão de Débito\n";
    cout << "3. Cartão de Crédito\n";
    cout << "4. PIX\n";
    
    int opcaoPagamento;
    if (validarEscolha(opcaoPagamento, 1, 4)) {
        FormaPagamento formaPagamento;
        switch (opcaoPagamento) {
            case 1: formaPagamento = FormaPagamento::DINHEIRO; break;
            case 2: formaPagamento = FormaPagamento::CARTAO_DEBITO; break;
            case 3: formaPagamento = FormaPagamento::CARTAO_CREDITO; break;
            case 4: formaPagamento = FormaPagamento::PIX; break;
        }
        
        // Criar nova nota fiscal
        NotaFiscal* novaVenda = gerenciadorVendas.criarNovaVenda();
        
        // Adicionar itens à nota
        for (const auto& item : itens) {
            novaVenda->adicionarItem(item.nomeProduto, item.precoUnitario, item.quantidade);
        }
        
        // Processar pagamento
        gerenciadorVendas.processarPagamento(*novaVenda, formaPagamento);
        
        // Finalizar venda
        gerenciadorVendas.finalizarVenda(*novaVenda);
        
        // Salvar produtos atualizados
        salvarProdutosEmArquivo();
        
        cout << "\n✅ Venda realizada com sucesso!\n";
        cout << "Total: R$ " << fixed << setprecision(2) << totalVenda << "\n";
        cout << "Nota fiscal gerada automaticamente!\n";
    }
}

void SistemaMercado::consultarNotasFiscais() {
    cout << "\n=== CONSULTAR NOTAS FISCAIS ===\n";
    
    cout << "1. Consultar por número da nota\n";
    cout << "2. Listar todas as notas\n";
    cout << "3. Buscar por cliente\n";
    
    int opcao;
    if (validarEscolha(opcao, 1, 3)) {
        switch (opcao) {
            case 1: {
                int numeroNota;
                cout << "Digite o número da nota fiscal: ";
                cin >> numeroNota;
                NotaFiscal* nota = gerenciadorVendas.buscarNotaPorNumero(numeroNota);
                if (nota != nullptr) {
                    nota->exibirNotaFiscal();
                } else {
                    cout << "Nota fiscal não encontrada!\n";
                }
                break;
            }
            case 2: {
                vector<NotaFiscal> todasNotas = gerenciadorVendas.getNotasFiscais();
                if (todasNotas.empty()) {
                    cout << "Nenhuma nota fiscal encontrada!\n";
                } else {
                    cout << "\n=== TODAS AS NOTAS FISCAIS ===\n";
                    for (auto& nota : todasNotas) {
                        nota.exibirNotaFiscal();
                        cout << "\n" << string(50, '-') << "\n";
                    }
                }
                break;
            }
            case 3: {
                string nomeCliente;
                cout << "Digite o nome do cliente: ";
                cin.ignore();
                getline(cin, nomeCliente);
                
                vector<NotaFiscal> notasCliente = gerenciadorVendas.buscarNotasPorCliente(nomeCliente);
                if (notasCliente.empty()) {
                    cout << "Nenhuma nota encontrada para o cliente: " << nomeCliente << "\n";
                } else {
                    cout << "\n=== NOTAS DO CLIENTE: " << nomeCliente << " ===\n";
                    for (auto& nota : notasCliente) {
                        nota.exibirNotaFiscal();
                        cout << "\n" << string(50, '-') << "\n";
                    }
                }
                break;
            }
        }
    }
}

void SistemaMercado::relatoriosVendas() {
    cout << "\n=== RELATÓRIOS DE VENDAS ===\n";
    
    cout << "1. Resumo geral de vendas\n";
    cout << "2. Vendas por forma de pagamento\n";
    cout << "3. Salvar relatório em arquivo\n";
    
    int opcao;
    if (validarEscolha(opcao, 1, 3)) {
        switch (opcao) {
            case 1:
                gerenciadorVendas.exibirResumoVendas();
                break;
            case 2:
                gerenciadorVendas.exibirVendasPorFormaPagamento();
                break;
            case 3:
                gerenciadorVendas.salvarRelatorioVendas();
                cout << "Relatório salvo em arquivo!\n";
                break;
        }
    }
}

// Menu principal
void SistemaMercado::exibirMenu() {
    cout << "\n***** SISTEMA DE MERCADO *****\n";
    cout << "Método Hash Ativo: " << (usarEncadeamentoLimite ? "🔗 Encadeamento Limite" : "🌿 Transformação da Raiz") << "\n\n";
    cout << "1. Cadastrar produto\n";
    cout << "2. Atualizar produto\n";
    cout << "3. Mostrar produtos\n";
    cout << "4. Busca produto por letra (Rabin-Karp)\n";
    cout << "5. Simulador de compras e vendas\n";
    cout << "6. Compressão Huffman\n";
    cout << "7. Demonstração de Hashing\n";
    cout << "8. Sistema Hash Completo\n";
    cout << "9. Sistema de Compressão de Relatórios\n";
    cout << "10. Ordenar lista de produtos\n";
    cout << "11. 🧾 NOVA VENDA COM NOTA FISCAL\n";
    cout << "12. 📋 Consultar Notas Fiscais\n";
    cout << "13. 📊 Relatórios de Vendas\n";
    cout << "14. 🔄 Alternar Método Hash\n";
    cout << "15. 🎯 Demonstrar Todos os Tipos de Busca\n";
    cout << "0. Sair\n";
}

void SistemaMercado::executarOpcao(int opcao) {
    switch (opcao) {
        case 1: cadastrarProduto(); break;
        case 2: atualizarProduto(); break;
        case 3: mostrarProdutos(); break;
        case 4: buscaProdutoPorLetra(); break;
        case 5: simuladorComprasEVendas(); break;
        case 6: executarCompressaoHuffman(); break;
        case 7: executarDemonstracaoHashing(); break;
        case 8: executarSistemaHashCompleto(); break;
        case 9: executarSistemaCompressaoRelatorios(); break;
        case 10: ordenarListaProdutos(); break;
        case 11: novaVendaComNotaFiscal(); break;
        case 12: consultarNotasFiscais(); break;
        case 13: relatoriosVendas(); break;
        case 14: alternarMetodoHash(); break;
        case 15: demonstrarTodosTiposBusca(); break;
        case 0: cout << "Saindo do sistema...\n"; break;
        default: cout << "Opção inválida!\n"; break;
    }
}

void SistemaMercado::iniciar() {
    int opcao;
    do {
        exibirMenu();
        if (validarEscolha(opcao, 0, 15)) {
            executarOpcao(opcao);
        }
    } while (opcao != 0);
}

// ========== MÉTODOS DE GERENCIAMENTO DE HASH TABLES ==========

void SistemaMercado::alternarMetodoHash() {
    usarEncadeamentoLimite = !usarEncadeamentoLimite;
    cout << "\n🔄 Método hash alterado para: " 
         << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz") << "\n";
    
    // Recarregar produtos na nova hash table
    sincronizarHashComVector();
}

void SistemaMercado::sincronizarHashComVector() {
    // Limpar hash tables
    hashProdutosLimite = HashTableEncadeamentoLimite(17);
    hashProdutosRaiz = HashTableTransformacaoRaiz(17);
    
    // Inserir todos os produtos do vector nas hash tables (usando índices)
    for (size_t i = 0; i < produtos.size(); i++) {
        int indice = static_cast<int>(i);
        hashProdutosLimite.inserir(produtos[i].getNome(), indice);
        hashProdutosRaiz.inserir(produtos[i].getNome(), indice);
    }
    
    cout << "✅ Hash tables sincronizadas com " << produtos.size() << " produtos (usando índices)\n";
}

void SistemaMercado::sincronizarVectorComHash() {
    // Atualiza o vector com base na hash table ativa
    produtos.clear();
    
    if (usarEncadeamentoLimite) {
        // Implementar método para extrair todos os produtos da hash de encadeamento limite
        // Por enquanto mantemos o vector como está
    } else {
        // Implementar método para extrair todos os produtos da hash de transformação raiz
        // Por enquanto mantemos o vector como está
    }
}

Produto* SistemaMercado::buscarProdutoHash(const string& nome) {
    int indice;
    
    if (usarEncadeamentoLimite) {
        if (hashProdutosLimite.buscar(nome, indice)) {
            return &produtos[indice];  // Retorna referência ao produto no vector
        }
    } else {
        if (hashProdutosRaiz.buscar(nome, indice)) {
            return &produtos[indice];  // Retorna referência ao produto no vector
        }
    }
    return nullptr;
}

void SistemaMercado::inserirProdutoHash(const Produto& produto) {
    // Encontrar o índice do produto no vector
    int indice = -1;
    for (size_t i = 0; i < produtos.size(); i++) {
        if (produtos[i].getNome() == produto.getNome()) {
            indice = static_cast<int>(i);
            break;
        }
    }
    
    if (indice != -1) {
        // Inserir em ambas as hash tables (índice como valor)
        hashProdutosLimite.inserir(produto.getNome(), indice);
        hashProdutosRaiz.inserir(produto.getNome(), indice);
        
        cout << "✅ Índice " << indice << " do produto '" << produto.getNome() 
             << "' inserido nas hash tables usando " 
             << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz") << "\n";
    }
}

void SistemaMercado::atualizarProdutoHash(const string& nome, const Produto& novoProduto) {
    // Encontrar o índice do produto no vector
    int indice = -1;
    for (size_t i = 0; i < produtos.size(); i++) {
        if (produtos[i].getNome() == nome) {
            indice = static_cast<int>(i);
            break;
        }
    }
    
    if (indice != -1) {
        // Atualizar em ambas as hash tables (sobrescreve o índice)
        hashProdutosLimite.inserir(nome, indice);
        hashProdutosRaiz.inserir(nome, indice);
        
        cout << "✅ Índice " << indice << " do produto '" << nome 
             << "' atualizado nas hash tables usando " 
             << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz") << "\n";
    }
}

void SistemaMercado::demonstrarTodosTiposBusca() {
    cout << "\n🔍 ***** DEMONSTRAÇÃO DE TODOS OS TIPOS DE BUSCA + HASH TABLES *****\n";
    cout << "Hash Ativo: " << (usarEncadeamentoLimite ? "🔗 Encadeamento Limite" : "🌿 Transformação da Raiz") << "\n\n";
    
    if (produtos.empty()) {
        cout << "❌ Nenhum produto cadastrado! Cadastre produtos primeiro.\n";
        return;
    }
    
    int opcao;
    cout << "Escolha o tipo de busca para demonstrar:\n";
    cout << "1. 🔍 Busca Sequencial + Hash Table\n";
    cout << "2. 🎯 Busca Binária + Hash Table\n";
    cout << "3. 🌀 Rabin-Karp + Hash Table\n";
    cout << "4. ⚡ Hash Table Pura (O(1))\n";
    cout << "5. 📊 Comparar Todos os Métodos\n";
    
    if (!validarEscolha(opcao, 1, 5)) return;
    
    string nomeProduto;
    
    switch (opcao) {
        case 1: {
            cout << "\n=== 🔍 BUSCA SEQUENCIAL + HASH TABLE ===\n";
            cout << "Digite o nome do produto: ";
            cin.ignore();
            getline(cin, nomeProduto);
            
            cout << "\n📋 PASSO 1: Busca Sequencial no Vector\n";
            int indiceSequencial = AlgoritmosBusca::buscaSequencial(produtos, nomeProduto);
            
            if (indiceSequencial != -1) {
                cout << "✅ Encontrado no índice " << indiceSequencial << " (Busca Sequencial)\n";
                cout << produtos[indiceSequencial].toString() << "\n";
            } else {
                cout << "❌ Não encontrado com busca sequencial\n";
            }
            
            cout << "\n🏷️ PASSO 2: Validação com Hash Table\n";
            Produto* produtoHash = buscarProdutoHash(nomeProduto);
            if (produtoHash != nullptr) {
                cout << "✅ Confirmado via Hash Table (" 
                     << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz") << ")\n";
                cout << produtoHash->toString() << "\n";
            } else {
                cout << "❌ Não confirmado na Hash Table\n";
            }
            break;
        }
        
        case 2: {
            cout << "\n=== 🎯 BUSCA BINÁRIA + HASH TABLE ===\n";
            cout << "Digite o nome do produto: ";
            cin.ignore();
            getline(cin, nomeProduto);
            
            cout << "\n📋 PASSO 1: Busca Binária no Vector (requer ordenação)\n";
            // Garantir que está ordenado
            sort(produtos.begin(), produtos.end(), [](const Produto& a, const Produto& b) {
                return a.getNome() < b.getNome();
            });
            
            int indiceBinario = AlgoritmosBusca::buscaBinaria(produtos, nomeProduto);
            
            if (indiceBinario != -1) {
                cout << "✅ Encontrado no índice " << indiceBinario << " (Busca Binária)\n";
                cout << produtos[indiceBinario].toString() << "\n";
            } else {
                cout << "❌ Não encontrado com busca binária\n";
            }
            
            cout << "\n🏷️ PASSO 2: Comparação com Hash Table\n";
            Produto* produtoHash = buscarProdutoHash(nomeProduto);
            if (produtoHash != nullptr) {
                cout << "✅ Confirmado via Hash Table (" 
                     << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz") << ")\n";
                cout << produtoHash->toString() << "\n";
            } else {
                cout << "❌ Não confirmado na Hash Table\n";
            }
            break;
        }
        
        case 3: {
            cout << "\n=== 🌀 RABIN-KARP + HASH TABLE ===\n";
            cout << "Digite uma letra para buscar padrão: ";
            char letra;
            cin >> letra;
            
            cout << "\n📋 PASSO 1: Rabin-Karp para encontrar padrões\n";
            vector<int> indicesEncontrados = AlgoritmosBusca::buscarPorLetra(produtos, letra);
            
            if (!indicesEncontrados.empty()) {
                cout << "✅ Encontrados " << indicesEncontrados.size() << " produtos com '" << letra << "':\n";
                for (size_t i = 0; i < indicesEncontrados.size(); i++) {
                    cout << "  " << (i+1) << ". " << produtos[indicesEncontrados[i]].toString() << "\n";
                }
                
                cout << "\n🏷️ PASSO 2: Busca individual via Hash Table\n";
                cout << "Digite o nome exato de um produto: ";
                cin.ignore();
                getline(cin, nomeProduto);
                
                Produto* produtoHash = buscarProdutoHash(nomeProduto);
                if (produtoHash != nullptr) {
                    cout << "✅ Encontrado via Hash Table (" 
                         << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz") << ")\n";
                    cout << produtoHash->toString() << "\n";
                } else {
                    cout << "❌ Não encontrado na Hash Table\n";
                }
            } else {
                cout << "❌ Nenhum produto encontrado com a letra '" << letra << "'\n";
            }
            break;
        }
        
        case 4: {
            cout << "\n=== ⚡ HASH TABLE PURA (O(1)) ===\n";
            cout << "Digite o nome do produto: ";
            cin.ignore();
            getline(cin, nomeProduto);
            
            cout << "\n🏷️ Busca direta na Hash Table:\n";
            Produto* produtoHash = buscarProdutoHash(nomeProduto);
            
            if (produtoHash != nullptr) {
                cout << "✅ ENCONTRADO INSTANTANEAMENTE! ⚡\n";
                cout << "Método: " << (usarEncadeamentoLimite ? "🔗 Encadeamento Limite" : "🌿 Transformação da Raiz") << "\n";
                cout << "Performance: O(1) - Complexidade constante\n";
                cout << produtoHash->toString() << "\n";
            } else {
                cout << "❌ Produto não encontrado na Hash Table\n";
                cout << "Ainda assim foi O(1) - busca instantânea!\n";
            }
            break;
        }
        
        case 5: {
            cout << "\n=== 📊 COMPARAÇÃO DE TODOS OS MÉTODOS ===\n";
            cout << "Digite o nome do produto para testar: ";
            cin.ignore();
            getline(cin, nomeProduto);
            
            cout << "\n🔍 TESTE DE PERFORMANCE:\n";
            cout << "Produto testado: '" << nomeProduto << "'\n\n";
            
            // 1. Busca Sequencial
            cout << "1️⃣ Busca Sequencial: O(n)\n";
            int seqResult = AlgoritmosBusca::buscaSequencial(produtos, nomeProduto);
            cout << "   Resultado: " << (seqResult != -1 ? "✅ Encontrado" : "❌ Não encontrado") << "\n\n";
            
            // 2. Busca Binária
            cout << "2️⃣ Busca Binária: O(log n)\n";
            sort(produtos.begin(), produtos.end(), [](const Produto& a, const Produto& b) {
                return a.getNome() < b.getNome();
            });
            int binResult = AlgoritmosBusca::buscaBinaria(produtos, nomeProduto);
            cout << "   Resultado: " << (binResult != -1 ? "✅ Encontrado" : "❌ Não encontrado") << "\n\n";
            
            // 3. Hash Table
            cout << "3️⃣ Hash Table: O(1)\n";
            Produto* hashResult = buscarProdutoHash(nomeProduto);
            cout << "   Método: " << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz") << "\n";
            cout << "   Resultado: " << (hashResult != nullptr ? "✅ Encontrado" : "❌ Não encontrado") << "\n\n";
            
            cout << "🏆 VENCEDOR: Hash Table com O(1)!\n";
            cout << "📈 Quanto maior a lista, maior a vantagem da Hash Table!\n";
            break;
        }
    }
}
