#include "compras.h"

#define VALOR_BANANA 6
#define VALOR_ARROZ 12
#define VALOR_FEIJAO 10
#define VALOR_LEITE 7

void somar_carrinho(Cliente *cliente){
    int valor;
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
    int conta_corrente;
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

int remover_da_fila(Fila* fi){
    if(fi == NULL || fi->inicio == NULL){
        return 0;
    }

    Elemento* aux_inicio = fi->inicio;
    if(aux_inicio == NULL){
        return 0;
    }

    fi->inicio = aux_inicio->prox;

    if(fi->inicio == NULL){
        fi->fim = NULL;
    }
    free(aux_inicio);

    return 1;



}

void liberar_fila(Fila* fi){
    if(fi!=NULL){
        
    }
}