
#include "tp1.h"

int main(void) {
    srand(time(NULL));

    RAM ram;
    CPU cpu;
    int opcao;

    do {
        printf("\n========== SIMULADOR DE COMPUTADOR ==========\n");
        printf("1 - Divisao\n");
        printf("2 - Fatorial\n");
        printf("3 - Soma ate N\n");
        printf("4 - Potencia\n");
        printf("5 - Raiz Quadrada\n");
        printf("6 - Resto da Divisao\n");
        printf("7 - Elemento de uma PA\n");
        printf("8 - Elemento de uma PG\n");
        printf("9 - MDC\n");
        printf("10 - Imprimir PA\n");
        printf("11 - Imprimir PG\n");
        printf("12 - Verificar se e Primo\n");
        printf("13 - Fibonacci\n");
        printf("14 - Divisao com Sinal\n");
        printf("15 - Bhaskara\n");
        printf("0 - Sair\n");
        printf("=============================================\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                programaDiv(&ram, &cpu, 10, 3);
                break;
            case 2:
                programaFat(&ram, &cpu, 5);
                break;
            case 3:
                programaSomaAteN(&ram, &cpu, 10);
                break;
            case 4:
                programaPotencia(&ram, &cpu, 2, 5);
                break;
            case 5:
                programaRaizQuadrada(&ram, &cpu, 16);
                break;
            case 6:
                programaRestoDivisao(&ram, &cpu, 10, 3);
                break;
            case 7:
                programaElementoAnPA(&ram, &cpu, 2, 5, 10);
                break;
            case 8:
                programaElementoAnPG(&ram, &cpu, 2, 2, 5);
                break;
            case 9:
                programaMDC(&ram, &cpu, 10, 3);
                break;
            case 10:
                programaImprimePA(&ram, &cpu, 2, 5, 10);
                break;
            case 11:
                programaImprimePG(&ram, &cpu, 2, 2, 5);
                break;
            case 12:
                programaEhPrimo(&ram, &cpu, 17);
                break;
            case 13:
                programaFibonacci(&ram, &cpu, 8);
                break;
            case 14:
                int resto;
                programaDivComSinal(&ram, &cpu, -4, 2, &resto);
                break;
            case 15:
                programaBhaskara(&ram, &cpu, 1, -7, 12);
                break;
            case 0:
                printf("Encerrando o simulador...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    destruirRAM(&ram);

    return 0;
}
