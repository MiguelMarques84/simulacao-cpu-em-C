# TP1 – Simulador de Computador em C

Projeto desenvolvido como parte do **Trabalho Prático 1 (TP1)** da disciplina de **Organização de Computadores**, na Universidade Federal de Ouro Preto (UFOP).

O objetivo é simular o funcionamento básico de um computador utilizando a linguagem C, implementando componentes como CPU, RAM e um conjunto de instruções para realizar operações computacionais.

## Sobre o projeto

O simulador representa uma arquitetura simplificada de computador, na qual a CPU executa instruções que manipulam dados armazenados na memória RAM.

A CPU possui dois registradores, um contador de programa (PC) e um conjunto de instruções que permite realizar operações básicas.

### Conjunto de instruções da CPU

| Opcode | Operação | Descrição |
|---|---|---|
| -1 | HALT | Finaliza a execução do programa |
| 0 | ADD | Soma dois valores da RAM |
| 1 | SUB | Subtrai dois valores da RAM |
| 2 | COPY REG → RAM | Copia o conteúdo de um registrador para a RAM |
| 3 | COPY RAM → REG | Copia um valor da RAM para um registrador |

## Organização dos arquivos

O projeto está dividido nos seguintes arquivos:

| Arquivo | Responsabilidade |
|---|---|
| `main.c` | Ponto de entrada do programa e menu de seleção das operações |
| `tp1.h` | Definição das estruturas, tipos e protótipos das funções |
| `cpu.c` | Implementação da CPU, registradores, contador de programa e execução das instruções |
| `ram.c` | Implementação das operações de criação, acesso, impressão e liberação da memória RAM |
| `linguagemAltoNivel.c` | Implementação de operações auxiliares que utilizam as instruções da CPU |
| `programas.c` | Implementação dos programas e algoritmos executados pelo simulador |

## Como executar

É necessário ter o GCC instalado.

Na raiz do projeto, compile os arquivos utilizando:

```bash
gcc -Wall -Wextra -std=c11 main.c cpu.c ram.c linguagemAltoNivel.c programas.c -o tp1
```

Em seguida, execute:

```bash
./tp1
```

Um menu será apresentado no terminal, permitindo selecionar qual programa deseja executar.

## Programas disponíveis

Os valores utilizados em cada operação estão previamente definidos no arquivo `main.c`. Portanto, não é necessário informar os parâmetros durante a execução.

O menu disponibiliza os seguintes programas:

1. Divisão
2. Fatorial
3. Soma até N
4. Potência
5. Raiz Quadrada
6. Resto da Divisão
7. Elemento de uma PA
8. Elemento de uma PG
9. MDC
10. Imprimir PA
11. Imprimir PG
12. Verificar se é Primo
13. Fibonacci
14. Divisão com Sinal
15. Bhaskara

**Observação:** algumas funções são auxiliares e servem de base para operações mais complexas. Por exemplo, o cálculo de Bhaskara utiliza operações de multiplicação, potenciação, raiz quadrada, soma, subtração e divisão.

## Como funciona a implementação

As operações dos programas são realizadas por meio da manipulação da RAM e da execução de instruções pela CPU.

O arquivo `linguagemAltoNivel.c` reúne funções auxiliares que facilitam a construção de operações mais complexas, como:

- `somar()`: realiza a soma de dois endereços da RAM.
- `subtrair()`: realiza a subtração de dois endereços da RAM.
- `salvarValor()`: armazena um valor na memória RAM.
- `obterValor()`: recupera um valor armazenado na RAM.

Essas funções utilizam o conjunto de instruções implementado em `cpu.c`, permitindo construir algoritmos sem manipular diretamente cada instrução da CPU.

## Observações

- O projeto utiliza alocação dinâmica de memória para representar a RAM.
- Os dados armazenados na RAM são representados por valores inteiros.
- A maioria das operações matemáticas é construída a partir das instruções básicas implementadas na CPU.
- Os parâmetros das operações podem ser modificados diretamente no arquivo `main.c`.
- Para adicionar novos programas, é necessário implementar a função em `programas.c`, adicionar seu protótipo em `tp1.h` e incluí-la no menu de opções em `main.c`.

**Este repositório corresponde especificamente ao TP1 da disciplina de Organização de Computadores.**
