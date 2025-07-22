# 📚 DOCUMENTAÇÃO COMPLETA - SISTEMA DE MERCADO

## 🎯 **VISÃO GERAL DO SISTEMA**

Este projeto é um **Sistema Completo de Mercado** desenvolvido em C++ com foco em **Programação Orientada a Objetos** e **Estruturas de Dados Avançadas**. O sistema integra múltiplos algoritmos de busca, estruturas de dados sofisticadas e técnicas de compressão.

---

## 🏗️ **ARQUITETURA DO PROJETO**

### **📁 Estrutura de Pastas:**
```
Sistema/
├── Classes/           # Implementações das classes (.cpp)
├── Include/           # Cabeçalhos das classes (.h)
├── main.cpp          # Arquivo principal
├── Makefile          # Script de compilação
└── README.md         # Documentação básica
```

### **🔧 Compilação:**
- **Compilador:** MinGW (g++)
- **Padrão:** C++17
- **Make:** mingw32-make
- **Comando:** `mingw32-make` (compila tudo automaticamente)

---

## 🧩 **CLASSES E MÓDULOS PRINCIPAIS**

### **1. 🏪 SistemaMercado (Classe Central)**
**Arquivo:** `SistemaMercado.cpp` / `SistemaMercado.h`

**Responsabilidades:**
- Controle geral do sistema
- Gerenciamento de produtos
- Integração de todos os algoritmos
- Interface com usuário (menu principal)

**Métodos Principais:**
- `cadastrarProduto()` - Cadastra novos produtos
- `atualizarProduto()` - Atualiza produtos existentes
- `mostrarProdutos()` - Lista todos os produtos
- `buscaProdutoPorLetra()` - Busca usando Rabin-Karp + Hash
- `simuladorComprasEVendas()` - Sistema de vendas completo
- `demonstrarTodosTiposBusca()` - Demonstra todos os algoritmos de busca

**Estruturas de Dados Utilizadas:**
- `vector<Produto>` - Armazenamento principal (compatibilidade)
- `HashTableEncadeamentoLimite` - Hash table com encadeamento
- `HashTableTransformacaoRaiz` - Hash table com transformação

### **2. 📦 Produto**
**Arquivo:** `Produto.cpp` / `Produto.h`

**Atributos:**
- `string nome` - Nome do produto
- `double preco` - Preço unitário
- `int quantidade` - Estoque disponível

**Métodos:**
- `temEstoque()` - Verifica se há produtos em estoque
- `temEstoqueSuficiente(int qtd)` - Verifica estoque suficiente
- `reduzirQuantidade(int qtd)` - Diminui estoque
- `toString()` - Formatação para exibição

### **3. 🏷️ HashTable (Estruturas Hash)**
**Arquivos:** `HashTable.cpp` / `HashTable.h`

**Implementações:**
1. **HashTableEncadeamentoLimite** - Resolução de colisão por encadeamento
2. **HashTableTransformacaoRaiz** - Hash usando transformação da raiz

**Métodos Principais:**
- `inserir(string chave, int valor)` - Insere chave-valor
- `buscar(string chave, int& valor)` - Busca O(1)
- `remover(string chave)` - Remove elemento
- `imprimir()` - Exibe estrutura interna

**Performance:** **O(1)** para inserção, busca e remoção (caso médio)

### **4. 🔍 AlgoritmosBusca**
**Arquivo:** `AlgoritmosBusca.cpp` / `AlgoritmosBusca.h`

**Algoritmos Implementados:**
1. **Busca Sequencial** - O(n)
   - Percorre lista elemento por elemento
   
2. **Busca Binária** - O(log n)
   - Requer lista ordenada
   - Divisão e conquista
   
3. **Rabin-Karp** - O(n) para busca de padrões
   - Busca por caracteres específicos
   - Usa hashing para otimização

### **5. 🌿 CompressorHuffman**
**Arquivo:** `CompressorHuffman.cpp` / `CompressorHuffman.h`

**Estruturas:**
- `NoHuffman` - Nó da árvore Huffman
- `ComparadorHuffman` - Comparador para priority_queue

**Algoritmo Huffman:**
1. **Contagem de Frequências** - Analisa texto
2. **Construção da Árvore** - Usa priority_queue
3. **Geração de Códigos** - Percurso recursivo
4. **Compressão** - Substitui caracteres por códigos
5. **Estatísticas** - Calcula taxa de compressão

### **6. 🧾 NotaFiscal**
**Arquivo:** `NotaFiscal.cpp` / `NotaFiscal.h`

**Funcionalidades:**
- Geração de notas fiscais completas
- Múltiplas formas de pagamento
- Cálculo de impostos e totais
- Persistência em arquivos

---

## 🚀 **ALGORITMOS E ESTRUTURAS IMPLEMENTADOS**

### **🔍 Algoritmos de Busca**

#### **1. Busca Sequencial**
- **Complexidade:** O(n)
- **Uso:** Comparação e verificação
- **Implementação:** Percorre vector linearmente

#### **2. Busca Binária**  
- **Complexidade:** O(log n)
- **Uso:** Listas ordenadas
- **Implementação:** Divisão recursiva do espaço de busca

#### **3. Rabin-Karp**
- **Complexidade:** O(n)
- **Uso:** Busca de padrões (letras iniciais)
- **Implementação:** Hash rolling para substring matching

#### **4. Hash Table**
- **Complexidade:** O(1)
- **Uso:** Busca principal do sistema
- **Implementações:**
  - **Encadeamento Limite:** Lista ligada para colisões
  - **Transformação da Raiz:** Hash baseado em raiz quadrada

### **🌿 Algoritmo de Compressão**

#### **Huffman Coding**
- **Tipo:** Compressão sem perda
- **Método:** Códigos de comprimento variável
- **Otimização:** Caracteres frequentes = códigos menores
- **Estrutura:** Árvore binária com priority_queue

**Passos do Algoritmo:**
1. Conta frequência de cada caractere
2. Cria nós folha para cada caractere
3. Constrói árvore bottom-up usando heap mínimo
4. Gera códigos binários (esquerda=0, direita=1)
5. Substitui caracteres pelos códigos

---

## 💻 **FUNCIONALIDADES DO SISTEMA**

### **📋 Menu Principal (15 Opções)**

1. **Cadastrar produto** - Adiciona produtos ao sistema
2. **Atualizar produto** - Modifica produtos existentes (usa Hash)
3. **Mostrar produtos** - Lista todos os produtos
4. **Busca produto por letra** - Rabin-Karp + Hash Table
5. **Simulador de compras** - Sistema de vendas completo (Hash puro)
6. **Compressão Huffman** - Demonstra algoritmo Huffman
7. **Demonstração de Hashing** - Mostra funcionamento das hash tables
8. **Sistema Hash Completo** - Testes avançados de hash
9. **Sistema de Compressão** - Relatórios comprimidos
10. **Ordenar lista** - Organiza produtos alfabeticamente
11. **Nova venda com nota fiscal** - Sistema completo de vendas
12. **Consultar notas fiscais** - Busca e exibe notas
13. **Relatórios de vendas** - Estatísticas de vendas
14. **Alternar método hash** - Troca entre Encadeamento e Transformação
15. **🎯 Demonstrar todos os tipos de busca** - Função principal de demonstração

### **🎯 Função Demonstrativa Principal**

A **Opção 15** oferece demonstração completa de todos os algoritmos:

#### **Submenu com 5 Demonstrações:**

1. **🔍 Busca Sequencial + Hash Table**
   - Executa busca sequencial no vector
   - Valida resultado com hash table
   - Compara performance

2. **🎯 Busca Binária + Hash Table**
   - Ordena lista automaticamente
   - Executa busca binária
   - Confirma com hash table

3. **🌀 Rabin-Karp + Hash Table**
   - Busca padrões por letra (Rabin-Karp)
   - Permite busca específica por nome (Hash)
   - Demonstra busca híbrida

4. **⚡ Hash Table Pura (O(1))**
   - Busca instantânea
   - Mostra método hash ativo
   - Performance constante

5. **📊 Comparar Todos os Métodos**
   - Testa mesmo produto em todos os algoritmos
   - Mostra comparação de performance
   - Destaca vantagens de cada método

---

## ⚡ **PERFORMANCE E COMPLEXIDADE**

### **📊 Tabela de Complexidades**

| Algoritmo | Melhor Caso | Caso Médio | Pior Caso | Uso no Sistema |
|-----------|------------|------------|-----------|----------------|
| **Hash Table** | O(1) | O(1) | O(n)* | Busca principal |
| **Busca Binária** | O(1) | O(log n) | O(log n) | Listas ordenadas |
| **Busca Sequencial** | O(1) | O(n) | O(n) | Comparação |
| **Rabin-Karp** | O(n) | O(n) | O(nm)** | Busca de padrões |
| **Huffman** | O(n log n) | O(n log n) | O(n log n) | Compressão |

\* *Pior caso quando todas as chaves colidem*  
\** *n = tamanho do texto, m = tamanho do padrão*

### **🚀 Otimizações Implementadas**

1. **Hash Tables Duplas** - Encadeamento + Transformação da Raiz
2. **Sincronização Vector-Hash** - Mantém compatibilidade
3. **Busca Híbrida** - Combina Rabin-Karp com Hash
4. **Cache de Resultados** - Evita recálculos
5. **Ordenação Automática** - Para busca binária eficiente

---

## 🛠️ **TECNOLOGIAS E FERRAMENTAS**

### **Linguagem e Padrões:**
- **C++17** - Padrão moderno
- **Orientação a Objetos** - Paradigma de programação
- **STL** - Standard Template Library extensiva

### **Estruturas STL Utilizadas:**
- `vector<>` - Arrays dinâmicos
- `map<>` - Árvores balanceadas
- `priority_queue<>` - Heap para Huffman
- `string` - Manipulação de texto
- `fstream` - E/S de arquivos

### **Compilação:**
- **MinGW** - Minimalist GNU for Windows
- **GCC 6.3.0** - Compilador GNU
- **Make** - Sistema de build automatizado

---

## 💾 **PERSISTÊNCIA E ARQUIVOS**

### **Arquivos Gerados:**
1. **`produtos.txt`** - Lista de produtos cadastrados
2. **`nota_fiscal_XXXX.txt`** - Notas fiscais individuais
3. **`relatorio_vendas.txt`** - Relatórios consolidados

### **Formato dos Dados:**
```
Produto: Nome - R$ Preço - Quantidade unid.
Exemplo: "Coca Cola - R$ 5.50 - 10 unid."
```

---

## 🎮 **GUIA DE USO**

### **🚀 Como Executar:**
1. Compile: `mingw32-make`
2. Execute: `sistema_mercado_poo.exe`
3. Navegue pelo menu numerado

### **📝 Fluxo Recomendado:**
1. **Cadastre produtos** (Opção 1)
2. **Teste buscas individuais** (Opções 4, 5)
3. **Compare algoritmos** (Opção 15)
4. **Teste Huffman** (Opção 6)
5. **Realize vendas** (Opção 11)

### **🎯 Para Demonstração Acadêmica:**
- **Opção 15** - Demonstra TODOS os algoritmos
- **Opção 6** - Compressão Huffman
- **Opção 14** - Alternância entre métodos hash

---

## 🏆 **DIFERENCIAIS DO SISTEMA**

### **✅ Características Avançadas:**

1. **Híbrido Vector + Hash** - Compatibilidade + Performance
2. **Múltiplos Algoritmos** - Comparação didática
3. **Interface Rica** - Emojis e formatação
4. **Sincronização Automática** - Dados sempre consistentes
5. **Sistema Completo** - Do cadastro à venda
6. **Compressão Integrada** - Huffman funcional
7. **Notas Fiscais** - Sistema comercial real
8. **Alternância Dinâmica** - Troca de algoritmos em tempo real

### **🎓 Valor Educacional:**
- **Estruturas de Dados** - Hash, Árvores, Priority Queue
- **Algoritmos de Busca** - Comparação prática
- **Compressão** - Algoritmo clássico
- **Programação Orientada a Objetos** - Encapsulamento, herança, polimorfismo
- **Performance** - Análise de complexidade

---

## 📈 **RESULTADOS E MÉTRICAS**

### **Performance Típica:**
- **Hash Table:** < 1ms para busca
- **Busca Binária:** ~log₂(n) ms
- **Busca Sequencial:** ~n ms
- **Huffman:** Taxa de compressão 30-70%

### **Capacidade:**
- **Produtos:** Ilimitado (limitado pela RAM)
- **Hash Tables:** Redimensionamento automático
- **Notas Fiscais:** Persistência em arquivos
- **Compressão:** Textos de qualquer tamanho

---

## 🔧 **MANUTENÇÃO E EXPANSÃO**

### **Possíveis Melhorias:**
1. **Interface Gráfica** - GUI com Qt ou similar
2. **Banco de Dados** - SQLite ou MySQL
3. **Rede** - Cliente-servidor
4. **Web** - API REST
5. **Mobile** - Aplicativo companion

### **Estrutura Modular:**
O código está organizado para fácil expansão:
- Classes bem definidas
- Interfaces claras
- Baixo acoplamento
- Alta coesão

---

## 📚 **CONCLUSÃO**

Este **Sistema de Mercado** representa uma implementação completa e educativa de múltiplas estruturas de dados e algoritmos em C++. Combina **performance** (hash tables O(1)), **versatilidade** (múltiplos algoritmos de busca), **completude** (sistema comercial funcional) e **valor educacional** (comparação didática de algoritmos).

**Principais Conquistas:**
- ✅ Implementação correta de 4 algoritmos de busca
- ✅ 2 métodos de hash table diferentes  
- ✅ Algoritmo Huffman funcional
- ✅ Sistema comercial completo
- ✅ Interface rica e intuitiva
- ✅ Performance otimizada
- ✅ Código bem estruturado e documentado

**O sistema está pronto para uso acadêmico, demonstrações e como base para projetos mais complexos!** 🎉

---

## 👨‍💻 **Informações Técnicas**
- **Projeto:** Sistema de Mercado
- **Linguagem:** C++17
- **Paradigma:** Programação Orientada a Objetos
- **Compilador:** MinGW GCC 6.3.0
- **Sistema:** Windows (compatível com Linux/Mac)
- **Licença:** Acadêmica/Educacional
