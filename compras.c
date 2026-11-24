#include "compras.h"
#include <stdio.h>

#define VALOR_BANANA 6
#define VALOR_ARROZ 12
#define VALOR_FEIJAO 10
#define VALOR_LEITE 7

void somar_carrinho(Cliente *cliente){
    int valor = 0;
    valor += cliente->carrinho.arroz * VALOR_ARROZ;
    valor += cliente->carrinho.banana * VALOR_BANANA;
    valor += cliente->carrinho.feijao * VALOR_FEIJAO;
    valor += cliente->carrinho.leite * VALOR_LEITE;
    cliente->carrinho.valor = valor;
    return;
}

void gerar_dinheiro(Cliente *cliente){
    if(cliente->id % 2 == 0){
        cliente->nota[0] = 10; 
        cliente->nota[1] = 50; 
        cliente->nota[2] = 20; 
    }
    else{
        cliente->nota[0] = 50;
        cliente->nota[1] = 50;
        cliente->nota[2] = 10;
    }
    return;
}

int pagar_conta(Cliente *cliente){
    int conta_corrente = 0;
    for(int i=0; i<3;i++){
        conta_corrente += cliente->nota[i];
    }

    if(conta_corrente < cliente->carrinho.valor){
        return 0;
    }
    else{
        conta_corrente -= cliente->carrinho.valor;
        return 1;
    }
}

Fila * criar_fila(){
    Fila* fi = (Fila*)malloc(sizeof(Fila));

    if(fi==NULL){
        printf("Memória insulficiente");
        exit(0);
    }
    fi->fim = NULL;
    fi->inicio = NULL;

    return fi;
}

int inserir_na_fila(Fila* fi, Cliente cliente){
    Elemento* elemento_adicionado = (Elemento*)malloc(sizeof(Elemento));

    if(fi == NULL || elemento_adicionado == NULL){
        return 0;
    }

    elemento_adicionado->cliente = cliente;
    elemento_adicionado->prox = NULL;


    if(fi->inicio==NULL){ //Se a fila estiver vazia
        fi->inicio = elemento_adicionado; //Adicione no inicio
    }
    else{ //Se tiver algum elemento na fila
        fi->fim->prox = elemento_adicionado; //O último aponta para o recem adicionado
    }
    fi->fim = elemento_adicionado; //Ponteiro fim aponta para o recem adicionado
    return 1; //Êxito
}

Elemento* atender(Fila* fi){
    if(fi == NULL || fi->inicio == NULL){
        return NULL ;
    }

    Elemento* aux_inicio = fi->inicio;
    if(aux_inicio == NULL){
        return NULL;
    }

    fi->inicio = aux_inicio->prox;
    
    if(fi->inicio == NULL){
        fi->fim = NULL;
    }
    aux_inicio->prox = NULL; // Por segurança
    return aux_inicio;
}

void liberar_fila(Fila* fi){
    
    if(fi!=NULL){
        
        while(fi->inicio!=NULL){
            Elemento *no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int simular_atendimento(Fila* fi){
    if(fi == NULL || fi->inicio == NULL){
        return 0;
    }

    Elemento *cliente_atendendo = atender(fi);


    
    printf("\n===Iniciando o atendimento do cliente de ID: %i ===\n", cliente_atendendo->cliente.id);
    somar_carrinho(&cliente_atendendo->cliente);
    printf("***Total a pagar: %i ***\n", cliente_atendendo->cliente.carrinho.valor);
    gerar_dinheiro(&cliente_atendendo->cliente);
    if(pagar_conta(&cliente_atendendo->cliente)){
        printf("\n!!! ÊXITO - Volte sempre cliente %i!!!\n", cliente_atendendo->cliente.id);
    }

    free(cliente_atendendo);
    return 1;

}