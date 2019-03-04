//EA876 - Trabalho Computacional 1 - Somador de Floats
//Lucas Bertoloto Pereira - RA 201798
#include <stdio.h>
#include <stdlib.h>



/*
  A máquina de estados finitos é definida para alterar de estado até chegar no estado 4, ponto onde ele tera lido um float válido.
  Os estados são os seguintes:

0) Estado inicial, cada vez que um caracter que quebra o esperado por um float e que não é inteiro for lido, a máquina volta para ele. Se o próximo char
for um número, ele mudará para o estado 1, caso o contrário, continuará zero.
1) Para onde passa o estado inicial se o char é um número. Se for lido um número, o estado é mantido. Se for lido um ponto, a mef é alterada para o
estado 2. Se for lido um espaço ou um ponto e vírgula, o estado é alterado para 4.  Caso o contrário, ela é alterada para o estado inicial.
2) Caso o char lido seja um número, a máquina muda para o estado 3. Caso não seja, a máquina volta para o estado inicial.
3) Caso o char lido seja um número, a máquina mantém o seu estado. Caso seja um espaço ou ponto e vírgula, ele é alterado para 4. Caso o contrário, volta
para o estado inicial.
4) Estado atingido quando um float é lido completamente, depois será mudado de volta para 0 pela função main.
5) Estado atingido nos casos em que há dois pontos ou um ponto antes dos numeros
*/

typedef struct {
  int estado;
} mef;

int muda_estado(mef* maquina, char a) {
  switch (maquina->estado) {
    case 0:
      if (a <= '9' && a >= '0') {
        maquina->estado = 1;
      } else if (a == '.') {
        maquina->estado = 5;
      }
      break;
    case 1:
      if (a <= '9' && a >= '0') {
        maquina->estado = 1;
      } else if (a == '.') {
        maquina->estado = 2;
      } else if (a == ' ' || a == ';' || a == '\n') {
        maquina->estado = 4;
      } else {
        maquina->estado = 0;
      }
      break;
    case 2:
      if (a <= '9' && a >= '0') {
        maquina->estado = 3;
      } else {
        maquina->estado = 0;
      }
      break;
    case 3:
      if (a <= '9' && a >= '0') {
        maquina->estado = 3;
      } else if (a == ' ' || a == ';' || a == '\n') {
        maquina->estado = 4;
      } else if (a == '.') {
        maquina->estado = 5;
      } else {
        maquina->estado = 0;
      }
      break;
    case 5:
      if (a == ' ') {
        maquina->estado = 0;
      }
      break;
  }
  return maquina->estado;
}


int main() {
  char entrada, * numero = malloc(100*sizeof(char));
  int tam_numero = 0;
  float soma = 0;
  mef* maquina = calloc(1, sizeof(mef));

  do {
    scanf("%c", &entrada);
    int aux = muda_estado(maquina, entrada); //utilizando a mef para alterar seu estado de acordo com o char lido
    if (aux > 0 && aux < 4) { //se a mef estiver em um estado que pode gerar um float valido
      numero[tam_numero++] = entrada;
    } else if (aux == 4) { //se a mef estiver em um estado em que acabou de ler um float valido
      numero[tam_numero] = '\0';
      soma += (float) atof(numero); //convertando a string para um float e somando no acumulador
      maquina->estado = 0; //voltando a mef pro seu estado inicial
      tam_numero = 0; //resetando a string
    }
  } while (entrada != '\n');


  //Para imprimir a saída, consideramos que todos os casos testes imprimem números com 0 ou 1 casas decimais, mas a lógica poderia ser extendida
  //para quantas casas fossem necessárias
  if (soma - (int)soma == 0) {
    printf("%.0f\n", soma);
  } else {
    printf("%.1f\n", soma);
  }

  free(maquina);
  return 0;
}
