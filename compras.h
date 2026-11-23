#include <stdio.h>


typedef struct Carrinho{
    int banana;
    int feijao;
    int leite;
    int arroz;
    int valor;
} Carrinho;

typedef struct Cliente{
    int nota;
    struct Carrinho carrinho;

} Cliente;



typedef struct Elemento{
    Cliente cliente;
    Elemento *prox;
} Elemento;

