#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//Instrucao.c
typedef struct{ 
    int add1;
    int add2;
    int add3;
    int opcode;
} Instrucao;

//BlocoMemoria.c
typedef struct{
    int tamanhoBloco;
    int palavras[4];
    int endBloco;
    bool atualizado;
    int custo;
    int cacheHit;
}BlocoMemoria;

typedef struct{

    BlocoMemoria registrador1;
    BlocoMemoria registrador2;
    BlocoMemoria registrador3;

    int PC;
    Instrucao *programa;
    int opcode;

    int custo;

    int missC1;
    int hitC1;
    int missC2;
    int hitC2;
   

    BlocoMemoria *cache1;
    BlocoMemoria *cache2;


}CPU;

typedef struct{
    BlocoMemoria *memoria;
    int tamanho;
}RAM;

//Endereco.c
typedef struct{
    int endBloco;
    int endPalavra;                      
}Endereco;


//protótipos ram.c
void criarRAM(int tamanho, RAM *self);
void criarRAM_vazia(int tamanho, RAM *self);
void criarRAM_aleatoria(int tamanho, RAM *self);
void setDado(int endereco, int conteudo, RAM *self);
int getDado(int endereco, RAM *self);
void imprimir(RAM *self);
void destruirRAM(RAM *self);

//protótipos cpu.c
int getRegistrador1(CPU *self);
void setRegistrador1(int registrador1, CPU *self);
int getRegistrador2(CPU *self);
void setRegistrador2(int registrador2, CPU *self);
void setPrograma(Instrucao *programaAux, CPU *self);
void iniciar(RAM *ram, CPU *self);

//protótipos programas.c joubert:
Instrucao *programaAleatorio(RAM *ram, CPU *cpu, int qdeInstrucoes);
void  programaMult(RAM *ram, CPU *cpu, int multiplicando, int multiplicador);
void programaDiv(RAM *ram, CPU *cpu, int dividendo, int divisor);
void programaFat(RAM *ram, CPU *cpu, int fat);

//programas feitos por mim: 
void programaSomaAteN(RAM *ram, CPU *cpu, int n);
void programaPotencia(RAM *ram, CPU *cpu, int base, int expoente);
int programaRaizQuadrada(RAM *ram, CPU *cpu, int n);
void programaRestoDivisao(RAM *ram, CPU *cpu, int dividendo, int divisor);
void programaElementoAnPA(RAM *ram, CPU *cpu, int a1, int razao, int n);
void programaElementoAnPG(RAM *ram, CPU *cpu, int a1, int razao, int n);
void programaMDC(RAM *ram, CPU *cpu, int x, int y);
void programaImprimePA(RAM *ram, CPU *cpu, int a1, int razao, int n);
void programaImprimePG(RAM *ram, CPU *cpu, int a1, int razao, int n);
void programaEhPrimo(RAM *ram, CPU *cpu, int n);
void programaFibonacci(RAM *ram, CPU *cpu, int n);
int programaDivComSinal(RAM *ram, CPU *cpu, int dividendo, int divisor, int *restoSaida);
void programaBhaskara(RAM *ram, CPU *cpu, int a, int b, int c);

//protótipos linguagemAltoNivel.c
void somar(CPU *cpu, RAM *ram, int end1, int end2);
void subtrair(CPU *cpu, RAM *ram, int end1, int end2);
void salvarValor(CPU *cpu, RAM *ram, int valor, int end1);
int obterValor(CPU *cpu, RAM *ram, int end1);

#endif