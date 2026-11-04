#include "tp2.h"

//sempre soma o que está na RAM[end1] com o que está na RAM[end2]
//e salva na RAM[end1] o resultado
void somar(CPU *cpu, RAM *ram, int end1, int end2){

    Instrucao trecho2[2];
    Instrucao inst3; 

    inst3.opcode = 0;
    inst3.add1 = end1;//ram[end1]
	inst3.add2 = end2;//ram[end2]
	inst3.add3 = end1;//ram[end1]
    trecho2[0] = inst3;

    Instrucao inst4;
    inst4.opcode = -1;
    trecho2[1] = inst4;

    setPrograma(trecho2, cpu);
    iniciar(ram, cpu);

}

void subtrair(CPU *cpu, RAM *ram, int end1, int end2){

    Instrucao trecho2[2];
    Instrucao inst3; 

    inst3.opcode = 1;
    inst3.add1 = end1;//ram[end1]
	inst3.add2 = end2;//ram[end2]
	inst3.add3 = end1;//ram[end1]
    trecho2[0] = inst3;

    Instrucao inst4;
    inst4.opcode = -1;
    trecho2[1] = inst4;

    setPrograma(trecho2, cpu);
    iniciar(ram, cpu);

}

void salvarValor(CPU *cpu, RAM *ram, int valor, int end1){
    
    Instrucao trecho1[2];
    setRegistrador1(valor, cpu);

    Instrucao inst1;
    inst1.opcode = 2;
    inst1.add1 = 1;//registrador1
	inst1.add2 = end1;//ram[end]
	trecho1[0] = inst1;

    Instrucao inst2;
    inst2.opcode = -1;
	trecho1[1] = inst2;

    setPrograma(trecho1, cpu);
    iniciar(ram, cpu);    
}

int obterValor(CPU *cpu, RAM *ram, int end1){
    Instrucao trecho3[2];
    Instrucao inst5;

    inst5.opcode = 3;
	inst5.add1 = 1;//registrador1
	inst5.add2 = end1;//ram[end]
	inst5.add3 = -1;
	trecho3[0] = inst5;

    Instrucao inst6;
    inst6.opcode = -1;
	trecho3[1] = inst6;
    
    setPrograma(trecho3, cpu);
    iniciar(ram, cpu); 
    
    return getRegistrador1(cpu);
}