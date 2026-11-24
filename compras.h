#include <stdio.h>


typedef struct Carrinho{
    int banana;
    int feijao;
    int leite;
    int arroz;
    int valor;
} Carrinho;

typedef struct Cliente{
    int id;
    int nota[3];
    struct Carrinho carrinho;

} Cliente;

typedef struct Fila{
    Elemento* inicio;
    Elemento* fim;
} Fila;

typedef struct Elemento{
    Cliente cliente;
    Elemento *prox;
} Elemento;

void somar_carrinho(Cliente *cliente);
void gerar_dinheiro(Cliente *cliente);
int pagar_conta(Cliente *cliente);


Elemento ** criar_fila();
