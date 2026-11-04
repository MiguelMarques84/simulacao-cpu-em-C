#include "tp1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void criarRAM(int tamanho, RAM *self){
    self->memoria = (int*) malloc(tamanho * sizeof(int));
    self->tamanho = tamanho;
}

void criarRAM_vazia(int tamanho, RAM *self){
    self->memoria = (int*) calloc(tamanho , sizeof(int));
    self->tamanho = tamanho;
}

void criarRAM_aleatoria(int tamanho, RAM *self){
    criarRAM(tamanho, self);
    for(int i = 0 ; i < tamanho ; i++)
        self->memoria[i] = rand();
}

void setDado(int endereco, int conteudo, RAM *self){
    self->memoria[endereco] = conteudo;
}

int getDado(int endereco, RAM *self){
    return self->memoria[endereco];
}

void imprimir(RAM *self){
    printf("Conteudo da RAM \n");

    for(int i = 0 ; i<(self->tamanho) ; i++){
        printf("%d , ", self->memoria[i]);
    }

    printf("\n\n");

}

void destruirRAM(RAM *self) {
    free(self->memoria);
    self->memoria = NULL;
    self->tamanho = 0;
}