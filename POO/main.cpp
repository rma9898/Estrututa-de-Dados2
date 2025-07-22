#include "Include/SistemaMercado.h"
#include <locale>

int main() {
    // Configurar localização para português brasileiro
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    cout << "=================================================\n";
    cout << "              SISTEMA DE MERCADO\n";
    cout << "=================================================\n\n";
    
    // Criar instância do sistema de mercado
    SistemaMercado sistema;
    
    // Iniciar o sistema
    sistema.iniciar();
    
    return 0;
}
