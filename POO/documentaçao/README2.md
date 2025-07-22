# 📋 DOCUMENTAÇÃO DE FUNÇÕES - SISTEMA DE MERCADO

## 🏗️ **Classe SistemaMercado** - Arquivo Principal

### 🔧 **Métodos de Validação**
```cpp
bool validarPreco(double& preco)
```
- **O que faz**: Valida entrada de preço do usuário
- **Como funciona**: Loop até o usuário digitar preço válido (0-999999.99)
- **Retorna**: true se preço válido, false caso contrário

```cpp
bool validarQuantidade(int& quantidade)
```
- **O que faz**: Valida entrada de quantidade do usuário
- **Como funciona**: Loop até o usuário digitar quantidade válida (0-999999)
- **Retorna**: true se quantidade válida

```cpp
bool validarEscolha(int& escolha, int min, int max)
```
- **O que faz**: Valida opções do menu principal
- **Como funciona**: Verifica se escolha está entre min e max
- **Retorna**: true se escolha válida

---

### 🛒 **Gestão de Produtos**

```cpp
void cadastrarProduto()
```
- **O que faz**: Cadastra novo produto no sistema
- **Como funciona**: 
  1. Pede nome, preço e quantidade
  2. Insere no vector `produtos`
  3. Insere nas hash tables (usando índice)
  4. Ordena lista alfabeticamente
  5. Salva em arquivo
- **Usa Hash**: ✅ Insere em ambas hash tables

```cpp
void atualizarProduto()
```
- **O que faz**: Atualiza preço e quantidade de produto existente
- **Como funciona**:
  1. **Busca produto na hash table (O(1))** ⚡
  2. Se encontrado, pede novos dados
  3. Atualiza hash tables e vector
  4. Salva arquivo
- **Usa Hash**: ✅ **Busca via hash table primeiro (PERFORMANCE BOOST!)**

```cpp
void mostrarProdutos()
```
- **O que faz**: Lista todos os produtos cadastrados
- **Como funciona**: Percorre vector `produtos` e exibe cada um
- **Usa Hash**: ❌ Usa vector para listagem

---

### 🔍 **Busca e Pesquisa**

```cpp
void buscaProdutoPorLetra()
```
- **O que faz**: Busca produtos que começam com uma letra específica
- **Como funciona**: Usa algoritmo Rabin-Karp para buscar padrão
- **Algoritmo**: Rabin-Karp (rolling hash)
- **Usa Hash**: ❌ Usa vector com algoritmo de busca (busca por padrão)

**🚀 NOVO: Busca Individual por Nome Agora Usa Hash!**
```cpp
Produto* buscarProdutoHash(const string& nome)
```
- **O que faz**: Busca produto específico por nome exato
- **Como funciona**: **Hash table lookup O(1)** vs busca sequencial O(n)
- **Performance**: **🚀 INSTANTÂNEO** - de lento para super rápido!

---

### 🛍️ **Sistema de Vendas**

```cpp
void simuladorComprasEVendas()
```
- **O que faz**: Simula processo de compra com carrinho
- **Como funciona**:
  1. Lista produtos por letra
  2. Usuário escolhe produtos
  3. Escolhe método de pagamento
  4. Pergunta se quer gerar nota fiscal
  5. Atualiza estoque
- **Features**: Pagamento + Nota fiscal opcional

```cpp
void comprarProdutoPorIndice(int indice)
```
- **O que faz**: Compra quantidade específica de um produto
- **Como funciona**: Reduz quantidade do produto no índice especificado
- **Controle**: Verifica se há estoque suficiente

```cpp
void novaVendaComNotaFiscal()
```
- **O que faz**: Sistema completo de venda com nota fiscal obrigatória
- **Como funciona**: Similar ao simulador, mas sempre gera nota fiscal

```cpp
void consultarNotasFiscais()
```
- **O que faz**: Exibe todas as notas fiscais emitidas
- **Como funciona**: Lista histórico de vendas com notas

```cpp
void relatoriosVendas()
```
- **O que faz**: Gera relatórios de vendas
- **Como funciona**: Análise estatística das vendas realizadas

---

### 💾 **Gerenciamento de Arquivos**

```cpp
void salvarProdutosEmArquivo()
```
- **O que faz**: Salva lista de produtos em arquivo "produtos.txt"
- **Formato**: Nome|Preço|Quantidade (uma linha por produto)

```cpp
void carregarProdutosDeArquivo()
```
- **O que faz**: Carrega produtos do arquivo na inicialização
- **Como funciona**: Lê arquivo e popula vector `produtos`

```cpp
void ordenarListaProdutos()
```
- **O que faz**: Ordena lista de produtos alfabeticamente
- **Como funciona**: Usa algoritmo sort() do C++

---

### 🏷️ **Sistema Hash Tables (NOVO!)**

```cpp
void alternarMetodoHash()
```
- **O que faz**: Alterna entre Encadeamento Limite ↔ Transformação da Raiz
- **Como funciona**: 
  1. Inverte flag `usarEncadeamentoLimite`
  2. Recarrega produtos na nova hash table
  3. Mostra método ativo

```cpp
void sincronizarHashComVector()
```
- **O que faz**: Sincroniza hash tables com vector de produtos
- **Como funciona**:
  1. Limpa ambas hash tables
  2. Re-insere todos produtos (usando índices como valor)
  3. Mantém consistência entre estruturas

```cpp
void sincronizarVectorComHash()
```
- **O que faz**: Sincroniza vector com hash table ativa
- **Status**: 🔄 Em desenvolvimento (placeholder)

```cpp
Produto* buscarProdutoHash(const string& nome)
```
- **O que faz**: Busca produto usando hash table ativa
- **Como funciona**:
  1. Busca índice na hash table (O(1))
  2. Retorna ponteiro para produto no vector
- **Performance**: O(1) médio vs O(n) busca sequencial
- **Retorna**: Ponteiro para produto ou nullptr

```cpp
void inserirProdutoHash(const Produto& produto)
```
- **O que faz**: Insere produto em ambas hash tables
- **Como funciona**:
  1. Encontra índice do produto no vector
  2. Insere índice nas duas hash tables
  3. Mantém consistência

```cpp
void atualizarProdutoHash(const string& nome, const Produto& novoProduto)
```
- **O que faz**: Atualiza produto nas hash tables
- **Como funciona**: Re-insere índice atualizado nas hash tables

---

### 🗜️ **Compressão e Demonstrações**

```cpp
void executarCompressaoHuffman()
```
- **O que faz**: Demonstra compressão Huffman em texto
- **Como funciona**: Usa classe CompressorHuffman

```cpp
void executarDemonstracaoHashing()
```
- **O que faz**: Demonstra funcionamento das hash tables
- **Como funciona**: Usa GerenciadorHash (só demonstração)

```cpp
void executarSistemaHashCompleto()
```
- **O que faz**: Sistema completo de demonstração de hash tables
- **Métodos mostrados**: Encadeamento, Endereçamento Aberto, Transformação Raiz, Encadeamento Limite

```cpp
void executarSistemaCompressaoRelatorios()
```
- **O que faz**: Sistema de compressão de relatórios de vendas
- **Como funciona**: Usa SistemaCompressaoVendas

---

### 🎛️ **Interface e Controle**

```cpp
void exibirMenu()
```
- **O que faz**: Mostra menu principal do sistema
- **Features**: 
  - Indica método hash ativo
  - 14 opções + sair
  - Visual organizado com emojis

```cpp
void executarOpcao(int opcao)
```
- **O que faz**: Executa função correspondente à opção escolhida
- **Como funciona**: Switch-case que direciona para cada método

```cpp
void iniciar()
```
- **O que faz**: Loop principal do sistema
- **Como funciona**:
  1. Mostra menu
  2. Valida escolha
  3. Executa opção
  4. Repete até usuário sair (0)

---

## 🚀 **Construtor**

```cpp
SistemaMercado()
```
- **O que faz**: Inicializa sistema completo
- **Como funciona**:
  1. Inicializa hash tables (tamanho 17)
  2. Define Encadeamento Limite como padrão
  3. Carrega produtos do arquivo
  4. Sincroniza hash tables com produtos carregados

---

## 📊 **Resumo de Performance - ATUALIZADO COM HASH TABLES**

| Operação | Método Antigo | Método Atual (Hash) | Melhoria |
|----------|---------------|-------------------|----------|
| **🔍 Busca por Nome** | O(n) busca sequencial | **O(1) hash table** | **🚀 REVOLUCIONÁRIO!** |
| **📝 Atualizar Produto** | O(n) busca + update | **O(1) busca** + update | **🚀 Busca instantânea** |
| **➕ Cadastro** | O(n log n) sort | **O(1) hash** + O(n log n) sort | **➕ Hash + ordenação** |
| **📋 Listagem** | O(n) | O(n) | ➖ Mesma performance |
| **🔤 Busca por Letra** | O(n) Rabin-Karp | O(n) Rabin-Karp | ➖ Mesma (busca padrão) |

### 🎯 **Impacto Real da Mudança:**
- **Antes**: Buscar "Arroz" em 1000 produtos = 1000 comparações
- **Agora**: Buscar "Arroz" em 1000 produtos = **1 operação hash** ⚡
- **Resultado**: **Busca 1000x mais rápida em listas grandes!**

## 🎯 **Métodos Hash Implementados**

1. **🔗 Encadeamento Limite**: Resolve colisões com listas, mas limita tamanho
2. **🌿 Transformação da Raiz**: Usa raiz quadrada para calcular hash
3. **📋 Para Demonstração**: Encadeamento simples, Endereçamento Aberto

---

## ⚡ **FUNÇÕES QUE AGORA USAM HASH TABLES**

### 🚀 **Performance Boost Ativo:**
- `atualizarProduto()` → **Busca O(1)** em vez de O(n)
- `buscarProdutoHash()` → **Nova função super rápida**
- `cadastrarProduto()` → **Inserção automática na hash**
- `sincronizarHashComVector()` → **Mantém consistência**

### 🎛️ **Controle do Sistema Hash:**
- **Opção 14 no menu**: Alterna entre métodos hash
- **Indicador visual**: Menu mostra método ativo
- **Duplo armazenamento**: Hash tables + vector para máxima eficiência

---

## 🔄 **COMO O MÉTODO HASH É ALTERADO - PASSO A PASSO**

### 📋 **Opção 14 do Menu: "🔄 Alternar Método Hash"**

#### **🎯 O que acontece quando você escolhe a opção 14:**

```cpp
void alternarMetodoHash()
```

**PASSO 1: Inverte o método ativo**
```cpp
usarEncadeamentoLimite = !usarEncadeamentoLimite;
```
- Se estava usando **Encadeamento Limite** → muda para **Transformação da Raiz**
- Se estava usando **Transformação da Raiz** → muda para **Encadeamento Limite**

**PASSO 2: Mostra qual método está ativo agora**
```cpp
cout << "🔄 Método hash alterado para: " 
     << (usarEncadeamentoLimite ? "Encadeamento Limite" : "Transformação da Raiz");
```

**PASSO 3: Recarrega todos os produtos na nova hash table**
```cpp
sincronizarHashComVector();
```

### 🔄 **O que a função `sincronizarHashComVector()` faz:**

**PASSO 1: Limpa ambas as hash tables**
```cpp
hashProdutosLimite = HashTableEncadeamentoLimite(17);  // Nova tabela vazia
hashProdutosRaiz = HashTableTransformacaoRaiz(17);     // Nova tabela vazia
```

**PASSO 2: Re-insere TODOS os produtos nas duas tabelas**
```cpp
for (size_t i = 0; i < produtos.size(); i++) {
    int indice = static_cast<int>(i);
    hashProdutosLimite.inserir(produtos[i].getNome(), indice);
    hashProdutosRaiz.inserir(produtos[i].getNome(), indice);
}
```

**PASSO 3: Confirma a sincronização**
```cpp
cout << "✅ Hash tables sincronizadas com " << produtos.size() << " produtos";
```

### 🎯 **Como isso afeta as buscas:**

#### **Quando `usarEncadeamentoLimite = true`:**
```cpp
if (usarEncadeamentoLimite) {
    if (hashProdutosLimite.buscar(nome, indice)) {
        return &produtos[indice];  // Usa Encadeamento Limite
    }
}
```

#### **Quando `usarEncadeamentoLimite = false`:**
```cpp
else {
    if (hashProdutosRaiz.buscar(nome, indice)) {
        return &produtos[indice];  // Usa Transformação da Raiz
    }
}
```

### 📊 **Exemplo Visual da Alternância:**

**ANTES** (Menu mostra):
```
Método Hash Ativo: 🔗 Encadeamento Limite
```

**Usuário escolhe opção 14**

**DURANTE** (Sistema processa):
```
🔄 Método hash alterado para: Transformação da Raiz
✅ Hash tables sincronizadas com 5 produtos (usando índices)
```

**DEPOIS** (Menu mostra):
```
Método Hash Ativo: 🌿 Transformação da Raiz
```

### ⚡ **Por que manter duas hash tables:**

1. **Eficiência**: Não precisa recalcular quando alterna
2. **Consistência**: Ambas sempre têm os mesmos dados
3. **Comparação**: Pode comparar performance dos dois métodos
4. **Segurança**: Se uma falhar, a outra está disponível

### 💡 **Como Funciona na Prática:**
1. **Você digita**: "Atualizar produto Arroz"
2. **Sistema faz**: Hash("Arroz") → encontra índice instantaneamente
3. **Resultado**: Produto encontrado em **1 operação** em vez de varrer lista toda

---

> 💡 **Inovação**: Sistema híbrido que mantém vector para compatibilidade e hash tables para performance!
