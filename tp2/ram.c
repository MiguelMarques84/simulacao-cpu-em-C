#include "tp1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void criarRAM(int tamanho, RAM *self){
    self->memoria = malloc(tamanho * sizeof(BlocoMemoria));
    for(int i = 0 ; i < tamanho ; i++){
        self->memoria[i].endBloco = i;
        self->memoria[i].atualizado = false;
        self->memoria[i].custo = 0;
        self->memoria[i].cacheHit = 0;
        
        for(int j = 0 ; j < 4 ; j++)
            self->memoria[i].palavras[j] = 0;
    }   
}

void criarRAM_aleatoria(int tamanho){
    self->memoria = malloc(tamanho * sizeof(BlocoMemoria));
    self->tamanho = tamanho;

    for(int i = 0 ; i < tamanho ; i++){
        self->memoria[i].endBloco = i;
        self->memoria[i].atualizado = false;
        self->memoria[i].custo = 0;
        self->memoria[i].cacheHit = 0;

        for(int j = 0 ; j < 4 ; j++)
            self->memoria[i].palavras[j] = rand();
    }
}

void setDado(int endereco, int conteudo, RAM *self){
    self->memoria[endereco] = conteudo;
}

BlocoMemoria getDado(int endereco, RAM *self){
    return self->memoria[endereco];
}

void imprimir(RAM *self){
    printf("Conteudo da RAM \n");

    for(int i = 0 ; i<(self->tamanho) ; i++){
        imprimirUmBloco(self->memoria[i]);
    }

    printf("\n\n");

}

void imprimirUmBloco(BlocoMemoria bloco){
    for(int i = 0 ; i < bloco.tamanhoBloco ; i++){
        printf("%d , ", bloco.palavras[i]);
    }
}

void destruirRAM(RAM *self) {
    free(self->memoria);
    self->memoria = NULL;
    self->tamanho = 0;
}