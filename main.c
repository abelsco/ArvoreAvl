#include "ArvoreAVL.h"
#define TAM 15
typedef struct Aluno {
  int RA, p1, p2, p3;
  double media;
} Aluno;

int main() {
  int res, i, valor;
  Aluno Aluno[TAM], aluno;
  srand((unsigned)time(NULL));
  ArvAVL *avl;

  avl = cria_ArvAVL();

  for (i = 0; i < TAM; i++) {
    printf("\nInserindo o RA: %d\n", i + 1);
    // ptrAluno = (Aluno*)malloc(sizeof(Aluno));
    Aluno[i].RA = i + 1;
    Aluno[i].p1 = rand() % 10;
    Aluno[i].p2 = rand() % 10;
    Aluno[i].p3 = rand() % 10;

    Aluno[i].media = (double)(Aluno[i].p1 + Aluno[i].p2 + Aluno[i].p3) / 3;

    res = insere_ArvAVL(avl, Aluno[i].RA);
    printf("\nAVL PRE-ORDEM:\n");
    preOrdem_ArvAVL(avl);
    printf("\n\n");
  }
  printf("\nAVL POS-ORDEM:\n");
  posOrdem_ArvAVL(avl);
  printf("\n\n");
  i = rand() % TAM;
  printf("RA ESCOLHIDO PARA REMOCAO:%d\n", i);
  remove_ArvAVL(avl, i);
  printf("\nAVL EM-ORDEM:\n");
  emOrdem_ArvAVL(avl);
  printf("\n\n");
  i = rand() % TAM;
  printf("RA ESCOLHIDO PARA REMOCAO:%d\n", i);
  remove_ArvAVL(avl, i);
  printf("\nAVL PRE-ORDEM:\n");
  preOrdem_ArvAVL(avl);
  printf("\n\n");
  i = rand() % TAM;
  printf("RA ESCOLHIDO PARA REMOCAO:%d\n", i);
  remove_ArvAVL(avl, i);
  printf("\nAVL PRE-ORDEM:\n");
  preOrdem_ArvAVL(avl);
  printf("\n\n");

  while (i != -1) {
    printf("\nCONSULTA, PARA SAIR DIGITE -1: ");
    scanf("%d", &i);
    if (i != -1) {
      valor = consulta_ArvAVL(avl, i);
      if (valor == 1) {
        aluno.RA = Aluno[i - 1].RA; // meu vetor ALUNO já esta ordenado de 0 até TAM
        aluno.p1 = Aluno[i - 1].p1;
        aluno.p2 = Aluno[i - 1].p2;
        aluno.p3 = Aluno[i - 1].p3;
        aluno.media = Aluno[i - 1].media;
        printf("\nRA:%d P1:%d P2:%d P3:%d MEDIA:%lf %s\n", aluno.RA, aluno.p1,
               aluno.p2, aluno.p3, aluno.media,
               aluno.media >= 6 ? "APROVADO" : "REPROVADO");
      }
      if (valor == 0) {
        printf("O RA %d NAO PODE SER ENCONTRADO");
      }
    }
  }

  // res = insere_ArvAVL(avl,aluno.RA);*/
  //    }

  libera_ArvAVL(avl);
  return 0;
}
