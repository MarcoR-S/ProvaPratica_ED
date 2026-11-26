#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Carrinho{
    int banana;
    int feijao;
    int leite;
    int arroz;
    int valor;
} Carrinho;

typedef struct Cliente{
    int id;
    int nota[5];
    Carrinho carrinho;

} Cliente;

typedef struct Elemento{
    Cliente cliente;
    struct Elemento *prox;
} Elemento;

typedef struct Fila{
    Elemento* inicio;
    Elemento* fim;
} Fila;



void somar_carrinho(Cliente *cliente);
void gerar_dinheiro(Cliente *cliente);
int pagar_conta(Cliente *cliente);
int adicionar_comida(Cliente *cliente);

Fila* criar_fila();
int inserir_na_fila(Fila* fi, Cliente cliente);
Elemento* atender(Fila* fi);
void liberar_fila(Fila* fi);
int simular_atendimento(Fila* fi);
void simular_dia(Fila* fi);