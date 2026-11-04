#include "tp1.h"

int main(void) {
    srand(time(NULL));

    RAM ram;
    CPU cpu;

   //Instrucao *umPrograma = programaAleatorio(&ram, &cpu, 100);
   //programaDiv(&ram, &cpu, 10, 3);
   //programaFat(&ram, &cpu, 5);
   //programaSomaAteN(&ram, &cpu, 10);
   //programaPotencia(&ram, &cpu, 2, 5);
   //programaRaizQuadrada(&ram, &cpu, 16);
   //programaRestoDivisao(&ram, &cpu, 10, 3);
   //programaElementoAnPA(&ram, &cpu, 2, 5, 10);
   //programaElementoAnPG(&ram, &cpu, 2, 2, 5);
   //programaMDC(&am, &cpu, 10, 3);
   //programaImprimePA(&ram, &cpu, 2, 5, 10);
   //programaImprimePG(&ram, &cpu, 2, 2, 5);
   //programaEhPrimo(&ram, &cpu, 17);
   //programaFibonacci(&ram, &cpu, 8);
   //programaDivComSinal(&ram, &cpu, -4, 2);
   programaBhaskara(&ram, &cpu, 1, -7, 12);

    /*if (umPrograma == NULL) {
        destruirRAM(&ram);
        return EXIT_FAILURE;
    }

    printf("--- ESTADO INICIAL ---\n");
    imprimir(&ram);

    printf("\n--- INICIANDO EXECUCAO DO PROGRAMA ---\n");
    iniciar(&ram, &cpu);
    
    free(umPrograma);
    */

    destruirRAM(&ram);
    return 0;
    
}