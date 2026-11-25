#include "compras.h"
#include <stdlib.h>

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
        cliente->nota[3] = 100; 
        cliente->nota[4] = 50;  
    }
    else{
        cliente->nota[0] = 50;
        cliente->nota[1] = 50;
        cliente->nota[2] = 10;
        cliente->nota[3] = 100;
        cliente->nota[4] = 2;
    }
    return;
}

int pagar_conta(Cliente *cliente){
    int conta_corrente = 0;
    for(int i=0; i<5;i++){
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
        printf("\n[ERRO] Memoria insuficiente para criar a fila.\n");
        exit(0);
    }
    fi->fim = NULL;
    fi->inicio = NULL;

    return fi;
}

int inserir_na_fila(Fila* fi, Cliente cliente){
    if(fi == NULL){
        return 0;
    }

    Elemento* elemento_adicionado = (Elemento*)malloc(sizeof(Elemento));
    if(elemento_adicionado == NULL){
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

void liberar_elemento(Elemento* elemento){
    free(elemento);
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

    Elemento *cliente_atendendo;
    while((cliente_atendendo = atender(fi)) != NULL){
        printf("\n\n----------------------------------------\n"
               "       ATENDIMENTO | CLIENTE #%02i\n"
               "----------------------------------------\n",
               cliente_atendendo->cliente.id);
        somar_carrinho(&cliente_atendendo->cliente);
        printf("Total da compra: R$ %i\n", cliente_atendendo->cliente.carrinho.valor);
        gerar_dinheiro(&cliente_atendendo->cliente);
        if(pagar_conta(&cliente_atendendo->cliente)){
            printf("\n[OK] Pagamento aprovado. Obrigado, cliente %i!\n",
                   cliente_atendendo->cliente.id);
        }
        else{
            printf("\n[AVISO] Saldo insuficiente. Atendimento encerrado.\n");
        }

        liberar_elemento(cliente_atendendo);
    }
    return 1;

}

void simular_dia(Fila* fi){

    if(fi == NULL){
        return;
    }
    Cliente bd_clientes[10];
    for(int i=0; i<10;i++){
        bd_clientes[i].id = i+1;
        bd_clientes[i].carrinho.arroz = i+1;
        bd_clientes[i].carrinho.banana = i+4;
        bd_clientes[i].carrinho.feijao = i+1;
        bd_clientes[i].carrinho.leite = i+3;
        printf("\n\n----------------------------------------\n"
               "         CLIENTE #%02i | CARRINHO\n"
               "----------------------------------------\n"
               "  Bananas : %i\n"
               "  Arroz   : %i\n"
               "  Feijao  : %i\n"
               "  Leite   : %i\n",
               bd_clientes[i].id,
               bd_clientes[i].carrinho.banana,
               bd_clientes[i].carrinho.arroz,
               bd_clientes[i].carrinho.feijao,
               bd_clientes[i].carrinho.leite);
        if(inserir_na_fila(fi, bd_clientes[i])){
            printf("[OK] Cliente #%i entrou na fila.\n", bd_clientes[i].id);
        }     
    }
    printf("\n\n========================================\n"
           "   Fila pronta. Iniciando atendimento...\n"
           "========================================\n");
    if(simular_atendimento(fi)){
        printf("\n\n========================================\n"
               "   Atendimento concluido. Bom trabalho!\n"
               "========================================\n");
        return;
    }


}