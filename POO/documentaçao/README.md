# 🏗️ SISTEMA DE MERCADO - PROGRAMAÇÃO ORIENTADA A OBJETOS

## 📁 Estrutura do Projeto

```
POO/
├── Include/                    # 📂 Arquivos de cabeçalho (.h)
│   ├── Produto.h              # 🏷️  Classe produto
│   ├── AlgoritmosBusca.h      # 🔍 Algoritmos de busca
│   ├── CompressorHuffman.h    # 🗜️  Compressão Huffman
│   ├── HashTable.h            # 🏷️  Tabelas hash
│   ├── CompressaoVendas.h     # 📊 Sistema de compressão de vendas
│   └── SistemaMercado.h       # 🏪 Sistema principal
├── Classes/                   # 📂 Implementações (.cpp)
│   ├── Produto.cpp
│   ├── AlgoritmosBusca.cpp
│   ├── CompressorHuffman.cpp
│   ├── HashTable.cpp
│   ├── CompressaoVendas.cpp
│   └── SistemaMercado.cpp
├── main.cpp                   # 🚀 Programa principal
├── Makefile                   # ⚙️  Arquivo de compilação
└── README.md                  # 📖 Esta documentação
```

## 🎯 Arquitetura de Classes

### 🏷️ **Classe Produto**
- **Responsabilidade**: Representar produtos individuais
- **Encapsulamento**: Atributos privados com getters/setters
- **Métodos**: `toString()`, `reduzirQuantidade()`, `temEstoque()`

### 🔍 **Classe AlgoritmosBusca**
- **Responsabilidade**: Implementar algoritmos de busca
- **Métodos estáticos**: Rabin-Karp, busca sequencial, busca binária
- **Especialização**: Busca por letra inicial

### 🗜️ **Classe CompressorHuffman**
- **Responsabilidade**: Implementar compressão Huffman
- **Estruturas auxiliares**: `NoHuffman`, `ComparadorHuffman`
- **Funcionalidades**: Construir árvore, gerar códigos, comprimir

### 🏷️ **Classe HashTable**
- **Responsabilidade**: Implementar tabela hash com encadeamento
- **Funcionalidades**: Inserção, busca, estatísticas de colisões
- **Gerenciamento**: Classe `GerenciadorHash` para demonstrações

### 📊 **Sistema de Compressão de Vendas**
- **CompressorRLE**: Run-Length Encoding
- **CompressorVendasHuffman**: Huffman especializado para vendas
- **GeradorVendas**: Criação de dados de teste
- **SistemaCompressaoVendas**: Coordenação e análise

### 🏪 **Classe SistemaMercado**
- **Responsabilidade**: Coordenar todo o sistema
- **Padrão Facade**: Interface unificada para todas as funcionalidades
- **Validação**: Métodos centralizados de validação de entrada

## 🚀 Como Compilar e Executar

### Método 1: Usando Makefile
```bash
# Compilação rápida
make quick

# Compilação completa
make all

# Executar
make run

# Limpar arquivos compilados
make clean
```

### Método 2: Comando direto
```bash
# Na pasta POO
g++ main.cpp Classes/*.cpp -IInclude -o sistema_poo.exe

# Executar
./sistema_poo.exe
```

### Método 3: Compilação por etapas
```bash
# Compilar cada classe individualmente
g++ -c -IInclude Classes/Produto.cpp -o Produto.o
g++ -c -IInclude Classes/AlgoritmosBusca.cpp -o AlgoritmosBusca.o
# ... (outros arquivos)

# Linkar tudo
g++ *.o -o sistema_mercado.exe
```

## ✨ Funcionalidades Implementadas

### 🛒 **Gestão de Produtos**
- ✅ Cadastro com validação robusta
- ✅ Atualização de preços e quantidades
- ✅ Listagem ordenada
- ✅ Persistência em arquivo

### 🔍 **Algoritmos de Busca**
- ✅ **Rabin-Karp**: Busca por padrões (letra inicial)
- ✅ **Busca Sequencial**: Para nomes parciais
- ✅ **Busca Binária**: Para listas ordenadas

### 🛍️ **Sistema de Vendas**
- ✅ Simulador de compras
- ✅ Controle de estoque
- ✅ Cálculo de totais
- ✅ Integração com busca por letra

### 🗜️ **Compressão de Dados**
- ✅ **Huffman**: Para textos gerais
- ✅ **RLE**: Para dados repetitivos
- ✅ **Sistema de Vendas**: Compressão especializada
- ✅ **Análise de Performance**: Comparação de métodos

### 🏷️ **Estruturas de Dados Avançadas**
- ✅ **Hash Tables**: Com tratamento de colisões
- ✅ **Árvores de Huffman**: Para compressão
- ✅ **Filas de Prioridade**: Para algoritmos
- ✅ **Vetores Dinâmicos**: Para gestão de produtos

## 🎨 Princípios de POO Aplicados

### 🔒 **Encapsulamento**
- Atributos privados em todas as classes
- Acesso controlado via métodos públicos
- Validação centralizada

### 🏗️ **Abstração**
- Interfaces claras e bem definidas
- Métodos com responsabilidades específicas
- Ocultação de complexidade interna

### 📦 **Modularidade**
- Cada classe em arquivo separado
- Headers organizados na pasta Include
- Implementações na pasta Classes

### 🔄 **Reutilização**
- Métodos estáticos para algoritmos
- Classes especializadas para diferentes tipos de compressão
- Sistema modular permite extensão fácil

## 🎯 Vantagens da Arquitetura Separada

### 👥 **Desenvolvimento em Equipe**
- Diferentes desenvolvedores podem trabalhar em classes diferentes
- Menos conflitos de merge
- Responsabilidades claras

### 🔧 **Manutenibilidade**
- Bugs localizados em arquivos específicos
- Modificações isoladas
- Testes unitários mais fáceis

### 📈 **Escalabilidade**
- Fácil adição de novas classes
- Extensão sem afetar código existente
- Padrões bem definidos

### 🏗️ **Compilação**
- Compilação incremental possível
- Tempo de build reduzido
- Dependências claras

## 🚀 Próximos Passos

1. **Testes Unitários**: Criar testes para cada classe
2. **Interface Gráfica**: Implementar GUI com Qt ou similar
3. **Banco de Dados**: Integrar com SQLite ou MySQL
4. **Rede**: Implementar cliente/servidor
5. **Documentação**: Gerar docs com Doxygen

## 📊 Métricas do Projeto

- **Classes**: 8 principais
- **Linhas de Código**: ~1500+
- **Algoritmos**: Rabin-Karp, Huffman, RLE, Hash
- **Padrões**: Facade, Strategy, Factory
- **Estruturas de Dados**: Vector, Map, Priority Queue, Tree

---

> 💡 **Dica**: Este projeto demonstra uma arquitetura robusta de POO com separação clara de responsabilidades, 
