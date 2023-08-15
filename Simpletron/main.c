#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_WORD 4

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

void read(int *memoria, int palavra)
{
  int endereco = palavra / 100;
  int valor = palavra % 100;
  //printf("\n >> [palavra = %d] Guardei o valor %d no registrador %d", palavra, valor, endereco);
  memoria[endereco] = valor;
}

void write(int *memoria, int palavra)
{
  int endereco = palavra / 100;
  printf("\nNa posicao %d foi lido o valor %d\n", endereco, memoria[endereco]);
}

void load(int *memoria, int *acumulador, int palavra)
{
  int endereco = palavra / 100;
  *acumulador = memoria[endereco];
}

void store(int *memoria, int *acumulador, int palavra)
{
  int endereco = palavra / 100;
  memoria[endereco] = *acumulador;
}

void add(int *memoria, int *acumulador, int palavra)
{
  int endereco = palavra / 100;
  *acumulador += memoria[endereco];
}

void subtract(int *memoria, int *acumulador, int palavra)
{
  int endereco = palavra / 100;
  *acumulador -= memoria[endereco];
}

void divide(int *memoria, int *acumulador, int palavra)
{
  //printf("\n >> palavra = %d", palavra);
  //printf("\n >> acumulador = %d", *acumulador);
  int endereco = palavra / 100;
  //printf("\n >> endereço = %d", endereco);
  //printf("\n >> Dividindo %d por %d", *acumulador, memoria[1]);
  *acumulador = *acumulador / memoria[endereco];
}

void multiply(int *memoria, int *acumulador, int palavra)
{
  int endereco = palavra / 100;
  *acumulador *= memoria[endereco];
}

int branchneg(int acumulador, int palavra)
{
  if (acumulador < 0)
  {
    return palavra % 100;
  }
  else
  {
    return 0;
  }
}

int branchzero(int acumulador, int palavra)
{
  if (acumulador == 0)
  {
    return palavra % 100;
  }
  else
  {
    return 0;
  }
}

int main()
{
  int memoria[MAX] = {0};
  int vetor[50];
  int acumulador = 0;
  int contador = 0;
  int palavra = 0;
  int jump = 0;
  printf("A memoria de dados tem endereco de 00 ate 99\n");
  printf("A memoria de instrucoes tem endereco de 00 ate 49\n");
  printf("Desvios ocorrem dentro da memeoria de instrucoes\n");
  printf("-----------------------------------------------\n");
  printf("Read: 10xxyy - Le o valor yy e armazena na posicao xx\n");
  printf("Write: 11xx - Escreve o valor da posicao xx\n");
  printf("Load: 20xx - Carrega o valor da posicao xx no acumulador\n");
  printf("Store: 21xx - Armazena o valor do acumulador na posicao xx\n");
  printf("Add: 30xx - Soma o valor da posicao xx ao acumulador\n");
  printf("Subtract: 31xx - Subtrai o valor da posicao xx ao acumulador\n");
  printf("Divide: 32xx - Divide o valor da posicao xx pelo acumulador\n");
  printf("Multiply: 33xx - Multiplica o valor da posicao xx ao acumulador\n");
  printf("Branch: 40xx - Desvia para a posicao xx\n");
  printf("BranchNeg: 41xx - Desvia para a posicao xx se o acumulador for negativo\n");
  printf("BranchZero: 42xx - Desvia para a posicao xx se o acumulador for zero\n");
  printf("Halt: 43 - Encerra o programa\n");
  printf("-----------------------------------------------\n");
  printf("O use 43 para encerrar o programa\n");
  printf("Se for desviado para um enderço invalido ou sem nada o programa sera encerrado\n");
  printf("Nao tem como escolher as linhas de execução, desvios para a frente implicam em escrever ate o local desejado\n");
  printf("Use -1 para encerrar a leitura de instrucoes\n");
  printf("-----------------------------------------------\n");
  printf("Digite as instrucoes:\n");
  while (contador < 50 && palavra != -1)
  {
    printf("\n%d: ", contador);
    scanf("%d", &palavra);

    if (palavra == -1)
      break;

    vetor[contador] = palavra;
    contador++;
  }

  for (int i = 0; i < contador; i++)
  {
    palavra = vetor[i];
    //printf("\n >> %d", palavra);

    if (vetor[i] == 0)
    {
      break;
    }
    int aux;
    //printf("\n #%d# \n", palavra / 10000);

    switch (palavra / 10000)
    {
    case READ:
      printf("\n >> comando READ");
      aux = palavra % 10000;
      read(memoria, aux);
      break;
    case WRITE:
      printf("\n >> comando WRITE");
      aux = palavra % 10000;
      write(memoria, aux);
      break;
    case LOAD:
      printf("\n >> comando LOAD");
      aux = palavra % 10000;
      load(memoria, &acumulador, aux);
      break;
    case STORE:
      printf("\n >> comando STORE");
      aux = palavra % 10000;
      store(memoria, &acumulador, aux);
      break;
    case ADD:
      printf("\n >> comando ADD");
      aux = palavra % 10000;
      add(memoria, &acumulador, aux);
      break;
    case SUBTRACT:
      printf("\n >> comando SUBTRACT");
      aux = palavra % 10000;
      subtract(memoria, &acumulador, aux);
      break;
    case DIVIDE:
      printf("\n >> comando DIVIDE [%d]", palavra % 10000);
      aux = palavra % 10000;
      divide(memoria, &acumulador, aux);
      break;
    case MULTIPLY:
      printf("\n >> comando MULTIPLY");
      aux = palavra % 10000;
      multiply(memoria, &acumulador, aux);
      break;
    case BRANCH:
      printf("\n >> comando BRANCH");
      aux = palavra % 10000;
      i = aux - 1;
      break;
    case BRANCHNEG:
      printf("\n >> comando BRANCHNEG");
      aux = palavra % 10000;
      jump = branchneg(acumulador, aux);
      break;
    case BRANCHZERO:
      printf("\n >> comando BRANCHZERO");
      aux = palavra % 10000;
      jump = branchzero(acumulador, aux);
      break;
    case HALT:
      printf("\n >> comando HALT");
      i = contador;
    }
    if (jump != 0){i = jump - 1;}
  }

  printf("\n\nValor no acumulador: %d\n", acumulador);
  printf("\n\nPrograma encerrado\n");

  getchar();
  return 0;
}
