# Makefile para Sistema de Mercado POO
# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++17 -Wall -Wextra -IInclude

# Diretórios
SRCDIR = Classes
INCDIR = Include
OBJDIR = obj

# Arquivos fonte
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp

# Arquivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Nome do executável
TARGET = sistema_mercado_poo.exe

# Regra principal
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Regra para criar objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	del /f *.o $(SRCDIR)\*.o $(TARGET)

# Executar
run: $(TARGET)
	./$(TARGET)

# Compilação rápida
quick:
	$(CXX) main.cpp $(SRCDIR)/*.cpp -IInclude -o sistema_poo.exe

.PHONY: all clean run quick
