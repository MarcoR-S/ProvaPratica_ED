#include "compras.h"



int main(void)
{   
    int option=0;
    int dia = 1;

    while(1){
        printf("\n\n"
               "========================================\n"
               "       MERCADO - SIMULADOR DE CAIXA\n"
               "========================================\n"
               "              DIA %02i\n"
               "----------------------------------------\n"
               "Deseja iniciar o atendimento?\n"
               "  [1] Sim, abrir o mercado\n"
               "  [2] Não, encerrar\n"
               "> ", dia);
        scanf("%i",&option);
        if(option==1){
            Fila *fila = criar_fila();
            simular_dia(fila);
            liberar_fila(fila);
            dia++;
            continue;
        }
        else{
            printf("\n\n"
                   "========================================\n"
                   "           FIM DO EXPEDIENTE\n"
                   "========================================\n"
                   "Dias trabalhados: %i\n"
                   "Obrigado por usar o simulador!\n", dia);
            break;
        }
    }
    return 1;
}
