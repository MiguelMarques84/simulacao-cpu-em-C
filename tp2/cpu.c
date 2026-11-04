#include "tp2.h"

int getRegistrador1(CPU *self) {
    return self->registrador1;  //retorna o que está no registrador
}

void setRegistrador1(int registrador1, CPU *self){
    self->registrador1 = registrador1; //adiciona um valor no registrador
}

int getRegistrador2(CPU *self) {
    return self->registrador2;
}

void setRegistrador2(int registrador2, CPU *self){
    self->registrador2 = registrador2;
}

void setPrograma(Instrucao *programaAux, CPU *self){ //cria um programa
    self->programa = programaAux; 
}

void iniciar(RAM *ram, CPU *self, int tamanhoCache1, int tamanhoCache2){  //começa um programa
    *self = iniciarCPU(tamanhoCache1, tamanhoCache2, tamanhoCache3);
    self->opcode = 0; //só para n pegar algum dos valores que já é opcode
    self->PC = 0; // zera a contagem de programa

    while(self->opcode != -1){  //enquanto não encontrar o parar, ele continua

        Instrucao inst = self->programa[self->PC];  //vê qual o proximo passo a ser feito

        self->opcode = inst.opcode;

        //-1 -> halt
		// 0 -> soma
		// 1 -> subtrai
		// 2 -> copia do registrador para RAM
		// 3 -> copia da RAM para o registrador

        switch(self->opcode){

            //halt
            case -1:
                //printf("\nPrograma terminou!\n\n");
                break;
            
            //soma
            case 0: 
                self->registrador1 = getDado(inst.add1, ram); //pega o primeiro valor e põe no primeiro registrador
                self->registrador2 = getDado(inst.add2, ram); //mesma coisa
                self->registrador1 += self->registrador2; //sobrescreve o valor do primeiro registrador com a soma dele + o segundo

                setDado(inst.add3, self->registrador1, ram); //adiciona esse valor no terceiro endereço
               // printf("Inst sum -> RAM posicao %d com conteudo %d\n", inst.add3, self->registrador1); //mostra o resultado
                break;
            
            //subtrai
            case 1:
                self->registrador1 = getDado(inst.add1,ram);
                self->registrador2 = getDado(inst.add2,ram);
                self->registrador1 -= self->registrador2;  //mesma coisa da soma soq subtrai

                setDado(inst.add3, self->registrador1, ram);
               // printf("Inst sub -> RAM posicao %d com conteudo %d\n", inst.add3, self->registrador1);
                break;
            
            //copia do registrador pra RAM
            //formato da instrucao [opcode,qual_registrador,end_ram,-1]
            case 2: 
                if(inst.add1 == 1){
                    setDado(inst.add2, self->registrador1, ram);
                    //printf("Inst copy_reg_ram -> RAM posicao %d com conteudo %d\n", inst.add2, self->registrador1);
                } else if(inst.add1 == 2){
                    setDado(inst.add2, self->registrador2, ram);
                    //printf("Inst copy_reg_ram -> RAM posicao %d com conteudo %d\n", inst.add2, self->registrador2);
                }

            break;
            
            //copia da RAM pro registrador
            //formato da instrucao [opcode,qual_registrador,end_ram,-1]
            case 3:
                if(inst.add1 == 1){
                    self->registrador1 = getDado(inst.add2, ram);
                //    printf("Inst copy_ram_reg -> Registrador1 com conteudo %d\n", self->registrador1);
                } else if(inst.add1 == 2){
                    self->registrador2 = getDado(inst.add2, ram);
                //    printf("Inst copy_ram_reg -> Registrador2 com conteudo %d\n", self->registrador2);   
                }
            break;
        }
        self->PC++;
    }
}

BlocoMemoria *iniciarCache(int tamanho) {
    BlocoMemoria *umaCache = malloc(tamanho * sizeof(BlocoMemoria));
    if (umaCache == NULL) return NULL;

    for (int i = 0; i < tamanho; i++) {
        umaCache[i].tamanhoBloco = 4;
        for (int j = 0; j < 4; j++)
            umaCache[i].palavras[j] = 0;
        umaCache[i].endBloco = 0;
        umaCache[i].atualizado = false;
        umaCache[i].custo = 0;
        umaCache[i].cacheHit = 0;
    }

    return umaCache;
}

CPU iniciarCPU(int tam1, int tam2) {
    CPU cpu = {0};   // zera todos os campos (inclusive ponteiros e structs aninhadas)

    cpu.registrador1.tamanhoBloco = 4;
    cpu.registrador2.tamanhoBloco = 4;
    cpu.registrador3.tamanhoBloco = 4;

    cpu.cache1 = iniciarCache(tam1);
    cpu.cache2 = iniciarCache(tam2);

    return cpu;
}