#include "tp2.h"

Instrucao *programaAleatorio(RAM *ram, CPU *cpu, int qdeInstrucoes){

    Instrucao *umPrograma = (Instrucao *) malloc(qdeInstrucoes * sizeof(Instrucao));
    int tamanhoRam = 1000;
    criarRAM_aleatoria(tamanhoRam, ram);

    for(int i = 0 ; i < (qdeInstrucoes - 1) ; i++){
        Instrucao inst;
        inst.opcode = rand() % 2;
        inst.add1 = rand() % ram->tamanho;
        inst.add2 = rand() % ram->tamanho;
        inst.add3 = rand() % ram->tamanho;
        
        umPrograma[i] = inst;
    } 

    Instrucao ultima;
    ultima.opcode = -1;
    umPrograma[qdeInstrucoes - 1] = ultima;

    setPrograma(umPrograma, cpu);
    return umPrograma;

}

void programaMult(RAM *ram, CPU *cpu, int multiplicando, int multiplicador){

    criarRAM_vazia(2, ram);
    salvarValor(cpu, ram, multiplicando, 1);
    
    for(int i = 0 ; i < multiplicador ; i++){
        somar(cpu, ram, 0, 1);
    }

    int mult = obterValor(cpu, ram, 0);
    //printf("O resultado da multiplicação de %d por %d é: %d\n", multiplicando, multiplicador, mult);
    
}

void programaDiv(RAM *ram, CPU *cpu, int dividendo, int divisor){
   
    criarRAM_vazia(4, ram);
    salvarValor(cpu, ram, dividendo, 0);
    salvarValor(cpu, ram, divisor, 1);
    salvarValor(cpu, ram, 1, 2);

    while(dividendo >= divisor){
        subtrair(cpu, ram, 0, 1);
        somar(cpu, ram, 3, 2);
        dividendo = obterValor(cpu, ram, 0);
    }

    int div = obterValor(cpu, ram, 3);
    //printf("O resultado da divisão é: %d\n", div);
    
    destruirRAM(ram);
}


void programaFat(RAM *ram, CPU *cpu, int fat){

    int j = 1;

    for(int i = 1 ; i <= fat ; i++){
        
        if(i > 1) destruirRAM(ram); //libera a RAM da volta anterior, programaMult cria uma nova
        programaMult(ram, cpu, j, i);

        Instrucao trecho1[2];
        Instrucao inst1;
        inst1.opcode = 3;
        inst1.add1 = 1; //registrador 1 
        inst1.add2 = 0; // RAM[0]
        trecho1[0] = inst1;

        Instrucao inst2;
        inst2.opcode = -1;
        trecho1[1] = inst2;

        setPrograma(trecho1, cpu);
        iniciar(ram, cpu);

        j = getRegistrador1(cpu);
    }

    Instrucao trecho2[2];
    Instrucao inst3;
    inst3.opcode = 3;
    inst3.add1 = 1;
    inst3.add2 = 0;
    inst3.add3 = -1;
    trecho2[0] = inst3;

    Instrucao inst4;
    inst4.opcode = -1;
    trecho2[1] = inst4;

    setPrograma(trecho2, cpu);
    iniciar(ram, cpu);

    //printf("O resultado da fatorial é: %d", getRegistrador1(cpu));
}

void programaSomaAteN(RAM *ram, CPU *cpu, int n){

    criarRAM_vazia(2, ram);
    salvarValor(cpu, ram, 0, 0); //RAM[0] = soma acumulada, começa em 0

    for(int i = 1 ; i <= n ; i++){
        salvarValor(cpu, ram, i, 1); //RAM[1] = i
        somar(cpu, ram, 0, 1);       //RAM[0] += RAM[1]
    }

    int soma = obterValor(cpu, ram, 0);
    printf("O resultado do somatório de 1 até %d é: %d\n", n, soma);

    destruirRAM(ram);
}

void programaPotencia(RAM *ram, CPU *cpu, int base, int expoente){

    int resultado = 1;

    for(int i = 0 ; i < expoente ; i++){
        if(i > 0) destruirRAM(ram); //libera a RAM da volta anterior, programaMult cria uma nova
        programaMult(ram, cpu, resultado, base);
        resultado = getRegistrador1(cpu); //programaMult já deixa o resultado no registrador1 (via obterValor interno)
    }
       
    if(expoente == 0){
        criarRAM_vazia(2, ram); //garante que existe RAM pra destruir no final, já que o for não roda
    }

    //printf("O resultado da potência de %d^%d é: %d\n", base, expoente, resultado);

    destruirRAM(ram);
}

void programaMDC(RAM *ram, CPU *cpu, int x, int y){

    if(x == 0 && y == 0){
        printf("MDC(0,0) não é definido\n");
        return;
    }

    int moduloX = x, moduloY = y;

    if(x < 0){
        criarRAM_vazia(2, ram);
        salvarValor(cpu, ram, 0, 0);
        salvarValor(cpu, ram, x, 1);
        subtrair(cpu, ram, 0, 1);
        moduloX = obterValor(cpu, ram, 0);
        destruirRAM(ram);
    }
    if(y < 0){
        criarRAM_vazia(2, ram);
        salvarValor(cpu, ram, 0, 0);
        salvarValor(cpu, ram, y, 1);
        subtrair(cpu, ram, 0, 1);
        moduloY = obterValor(cpu, ram, 0);
        destruirRAM(ram);
    }

    if(moduloX == 0){
        printf("O MDC de %d e %d é: %d\n", x, y, moduloY);
        return;
    }
    if(moduloY == 0){
        printf("O MDC de %d e %d é: %d\n", x, y, moduloX);
        return;
    }

    criarRAM_vazia(2, ram);
    salvarValor(cpu, ram, moduloX, 0);
    salvarValor(cpu, ram, moduloY, 1);

    int a = moduloX, b = moduloY;
    while(a != b){
        if(a > b){
            subtrair(cpu, ram, 0, 1);
            a = obterValor(cpu, ram, 0);
        } else {
            subtrair(cpu, ram, 1, 0);
            b = obterValor(cpu, ram, 1);
        }
    }

    int mdc = obterValor(cpu, ram, 0);
    printf("O MDC de %d e %d é: %d\n", x, y, mdc);

    destruirRAM(ram);
}
  

void programaRestoDivisao(RAM *ram, CPU *cpu, int dividendo, int divisor){

    if(divisor == 0){
        printf("Divisão por zero: erro\n");
        return;
    }

    int dividendoOriginal = dividendo; //valor original

    criarRAM_vazia(2, ram);
    salvarValor(cpu, ram, dividendo, 0); //RAM[0] = dividendo, vai virando o resto a cada subtração
    salvarValor(cpu, ram, divisor, 1);   //RAM[1] = divisor

    while(dividendo >= divisor){
        subtrair(cpu, ram, 0, 1); //RAM[0] -= divisor
        dividendo = obterValor(cpu, ram, 0);
    }

    int resto = obterValor(cpu, ram, 0);
    //printf("O resto da divisão de %d por %d é: %d\n", dividendoOriginal, divisor, resto);

    destruirRAM(ram);
}

void programaElementoAnPA(RAM *ram, CPU *cpu, int a1, int razao, int n){

    criarRAM_vazia(2, ram);
    salvarValor(cpu, ram, a1, 0);    //RAM[0] = termo atual, começa em a1
    salvarValor(cpu, ram, razao, 1); //RAM[1] = razão

    for(int i = 1 ; i < n ; i++){
        somar(cpu, ram, 0, 1); //RAM[0] += razão, até chegar no n-ésimo termo
    }

    int termo = obterValor(cpu, ram, 0);
    printf("O termo a%d da PA é: %d\n", n, termo);

    destruirRAM(ram);
}

void programaElementoAnPG(RAM *ram, CPU *cpu, int a1, int razao, int n){

    int resultado = a1;

    for(int i = 1 ; i < n ; i++){
        if(i > 1) destruirRAM(ram); //libera a RAM da volta anterior, programaMult cria uma nova
        programaMult(ram, cpu, resultado, razao);
        resultado = getRegistrador1(cpu); //programaMult já deixa o resultado no registrador1
    }

    if(n <= 1){
        criarRAM_vazia(2, ram); //garante RAM válida pra destruir, já que o for não roda
    }

    printf("O termo a%d da PG é: %d\n", n, resultado);

    destruirRAM(ram);
}

void programaImprimePA(RAM *ram, CPU *cpu, int a1, int razao, int n){

    criarRAM_vazia(n+1, ram);
    salvarValor(cpu, ram, a1, 1);    //RAM[0] = termo atual, começa em a1
    salvarValor(cpu, ram, razao, 0); //RAM[1] = razão

    for(int i = 2 ; i <= n ; i++){
        int aux = obterValor(cpu, ram, i-1);
        salvarValor(cpu, ram, aux, i);
        somar(cpu, ram, i, 0); 
    }

    printf("Todos os %d elementos da PA: ", n);

    for(int i = 1 ; i <= n ; i++){
        int termo = obterValor(cpu, ram, i);
        printf("%d ", termo);
    }
    printf("\n");

    destruirRAM(ram);

}

void programaImprimePG(RAM *ram, CPU *cpu, int a1, int razao, int n){

    RAM *ram2;
    criarRAM_vazia(n, ram2);

    int resultado = a1;
    salvarValor(cpu, ram2, resultado, 0);

    for(int i = 1 ; i < n ; i++){
        if(i > 1) destruirRAM(ram); //libera a RAM da volta anterior, programaMult cria uma nova
        programaMult(ram, cpu, resultado, razao);
        resultado = getRegistrador1(cpu); //programaMult já deixa o resultado no registrador1
        salvarValor(cpu, ram2, resultado, i);
    }

    if(n <= 1){
        criarRAM_vazia(2, ram); //garante RAM válida pra destruir, já que o for não roda
    }

    printf("Todos os %d elementos da PG: ", n);

    for(int i = 0 ; i < n ; i++){
        int termo = obterValor(cpu, ram2, i);
        printf("%d ", termo);
    }
    printf("\n");

    destruirRAM(ram);
    destruirRAM(ram2);

}

void programaEhPrimo(RAM *ram, CPU *cpu, int n){

}

void programaFibonacci(RAM *ram, CPU *cpu, int n){

    if(n < 0){
        printf("n precisa ser >= 0\n");
        return;
    }

    criarRAM_vazia(3, ram);
    salvarValor(cpu, ram, 0, 0); //RAM[0] = a = fib(0)
    salvarValor(cpu, ram, 1, 1); //RAM[1] = b = fib(1)

    for(int i = 2 ; i <= n ; i++){
        salvarValor(cpu, ram, obterValor(cpu, ram, 0), 2); //RAM[2] = a (copia, antes que a mude)
        somar(cpu, ram, 2, 1);                              //RAM[2] = a + b = novo termo

        salvarValor(cpu, ram, obterValor(cpu, ram, 1), 0); //a = b (anda uma casa)
        salvarValor(cpu, ram, obterValor(cpu, ram, 2), 1); //b = novo termo
    }

    int resultado = (n == 0) ? obterValor(cpu, ram, 0) : obterValor(cpu, ram, 1);
    printf("O termo fib(%d) é: %d\n", n, resultado);

    destruirRAM(ram);
}

int programaDivComSinal(RAM *ram, CPU *cpu, int dividendo, int divisor, int *restoSaida){
 
    if(divisor == 0){
        printf("Divisão por zero não é permitida\n");
        if(restoSaida != NULL) *restoSaida = 0;
        return 0;
    }
 
    int dividendoNegativo = (dividendo < 0); //condicional 
    int divisorNegativo   = (divisor < 0);
 
    criarRAM_vazia(5, ram);
    salvarValor(cpu, ram, dividendo, 0);
    salvarValor(cpu, ram, divisor, 1);
    salvarValor(cpu, ram, 1, 2);
    salvarValor(cpu, ram, 0, 3); //quociente começa em 0
 
    if(dividendoNegativo){
        salvarValor(cpu, ram, 0, 4);  //RAM[4] = 0
        subtrair(cpu, ram, 4, 0);     //RAM[4] = 0 - dividendo = |dividendo|
        salvarValor(cpu, ram, obterValor(cpu, ram, 4), 0); //devolve pra RAM[0] já no valor absoluto
    }
    if(divisorNegativo){
        salvarValor(cpu, ram, 0, 4);  //RAM[4] = 0
        subtrair(cpu, ram, 4, 1);     //RAM[4] = 0 - divisor = |divisor|
        salvarValor(cpu, ram, obterValor(cpu, ram, 4), 1); //devolve pra RAM[1] já positivo
    }
 
    //RAM[0] e RAM[1] são positivos
    int auxDividendo = obterValor(cpu, ram, 0);
    int auxDivisor = obterValor(cpu, ram, 1);
    while(auxDividendo >= auxDivisor){
        subtrair(cpu, ram, 0, 1);
        somar(cpu, ram, 3, 2);
        auxDividendo = obterValor(cpu, ram, 0);
    }
 
    int quocienteAbs = obterValor(cpu, ram, 3);
    int restoAbs = obterValor(cpu, ram, 0);
 
    int quociente = (dividendoNegativo != divisorNegativo) ? -quocienteAbs : quocienteAbs;
    int resto = dividendoNegativo ? -restoAbs : restoAbs;
 
    //printf("%d / %d = quociente %d, resto %d\n", dividendo, divisor, quociente, resto);
 
    if(restoSaida != NULL) *restoSaida = resto;
 
    destruirRAM(ram);
    return quociente;
}
 
int programaRaizQuadrada(RAM *ram, CPU *cpu, int n){
 
    if(n < 0){
        printf("Não existe raiz real para número negativo\n");
        return -1;
    }
 
    criarRAM_vazia(5, ram);
    salvarValor(cpu, ram, n, 0);
    salvarValor(cpu, ram, 1, 1); //primeiro ímpar
    salvarValor(cpu, ram, 2, 2); //incremento do ímpar
    salvarValor(cpu, ram, 0, 3); //contador/raiz começa em 0
    salvarValor(cpu, ram, 1, 4); //incremento do contador
 
    int aux = obterValor(cpu, ram, 0);
    int impar = obterValor(cpu, ram, 1);
 
    while(aux >= impar){
        subtrair(cpu, ram, 0, 1); //resto -= ímpar atual
        somar(cpu, ram, 3, 4);    //contador++
        somar(cpu, ram, 1, 2);    //ímpar += 2 (próximo ímpar da sequência)
 
        aux = obterValor(cpu, ram, 0);
        impar = obterValor(cpu, ram, 1);
    }
 
    int resto = obterValor(cpu, ram, 0);
    int raiz = obterValor(cpu, ram, 3);
 
    destruirRAM(ram);
 
    if(resto != 0){
        printf("%d não é quadrado perfeito (raiz aproximada: %d)\n", n, raiz);
        return -1;
    }
 
    printf("A raiz quadrada de %d é: %d\n", n, raiz);
    return raiz;
}
 
//  (-b +- sqrt(b² - 4ac))/2a

void programaBhaskara(RAM *ram, CPU *cpu, int a, int b, int c){
 
    if(a == 0){
        printf("Não é uma equação do 2º grau.\n");
        return;
    }
     
    //b²
    int moduloB = b;
    if(b < 0){
        criarRAM_vazia(2, ram);
        salvarValor(cpu, ram, 0, 0);
        salvarValor(cpu, ram, b, 1);
        subtrair(cpu, ram, 0, 1); //RAM[0] = 0 - b = |b|
        moduloB = obterValor(cpu, ram, 0);
        destruirRAM(ram);
    }
    
    programaPotencia(ram, cpu, moduloB, 2);
    int b2 = getRegistrador1(cpu);
 
    //a*c: olho o sinal dps
    int aNegativo = (a < 0), cNegativo = (c < 0);
    int moduloA = a, moduloC = c;
 
    if(aNegativo){
        criarRAM_vazia(2, ram);
        salvarValor(cpu, ram, 0, 0);
        salvarValor(cpu, ram, a, 1);
        subtrair(cpu, ram, 0, 1);
        moduloA = obterValor(cpu, ram, 0);
        destruirRAM(ram);
    }
    if(cNegativo){
        criarRAM_vazia(2, ram);
        salvarValor(cpu, ram, 0, 0);
        salvarValor(cpu, ram, c, 1);
        subtrair(cpu, ram, 0, 1);
        moduloC = obterValor(cpu, ram, 0);
        destruirRAM(ram);
    }
 
    programaMult(ram, cpu, moduloA, moduloC);
    int moduloAC = getRegistrador1(cpu);
    destruirRAM(ram);
 
    int ac = (aNegativo != cNegativo) ? -moduloAC : moduloAC;
 
    //4ac
    programaMult(ram, cpu, ac, 4);
    int quatroAC = getRegistrador1(cpu);
    destruirRAM(ram);
 
    //delta = b² - 4ac
    criarRAM_vazia(2, ram);
    salvarValor(cpu, ram, b2, 0);
    salvarValor(cpu, ram, quatroAC, 1);
    subtrair(cpu, ram, 0, 1);
    int delta = obterValor(cpu, ram, 0);
    destruirRAM(ram);
 
    printf("Delta = %d\n", delta);
 
    if(delta < 0){
        printf("A equação não possui raízes reais.\n");
        return;
    }
 
    int raizDelta = programaRaizQuadrada(ram, cpu, delta);
    if(raizDelta == -1){
        printf("A equação possui raízes reais, mas %d não é quadrado perfeito.\n", delta);
        return;
    }
 
    //-b
    criarRAM_vazia(2, ram);
    salvarValor(cpu, ram, 0, 0);
    salvarValor(cpu, ram, b, 1);
    subtrair(cpu, ram, 0, 1); //RAM[0] = 0 - b = -b
    int menosB = obterValor(cpu, ram, 0);
    destruirRAM(ram);
 
    //numeradores: (-b + raizDelta)
    criarRAM_vazia(2, ram);
    salvarValor(cpu, ram, menosB, 0);
    salvarValor(cpu, ram, raizDelta, 1);
    somar(cpu, ram, 0, 1);
    int numeradorMais = obterValor(cpu, ram, 0);
    destruirRAM(ram);
 
    //(-b - raizDelta)
    criarRAM_vazia(2, ram);
    salvarValor(cpu, ram, menosB, 0);
    salvarValor(cpu, ram, raizDelta, 1);
    subtrair(cpu, ram, 0, 1);
    int numeradorMenos = obterValor(cpu, ram, 0);
    destruirRAM(ram);
 
    //denominador: 2a
    programaMult(ram, cpu, a, 2);
    int denom = getRegistrador1(cpu);
    destruirRAM(ram);
 
    //x1 e x2 
    int restoX1, restoX2;
    int x1 = programaDivComSinal(ram, cpu, numeradorMais, denom, &restoX1);
    int x2 = programaDivComSinal(ram, cpu, numeradorMenos, denom, &restoX2);
 
    printf("\n--- Resultado do Bhaskara ---\n");
    if(restoX1 == 0) printf("x1 = %d\n", x1);
    else printf("x1 não é inteiro - Parte inteira %d Resto %d\n",x1, restoX1);
 
    if(restoX2 == 0) printf("x2 = %d\n", x2);
    else printf("x2 não é inteiro - Parte inteira %d Resto %d\n",x2, restoX2);
}