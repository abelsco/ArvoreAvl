/*
     * criar ArvoreAVL.h
     * Implementar:
          - Altura do nó;
          - Altura da árvore;
          - Fator de balanceamento;
          - Rotações.

     * Aplicar a avl em um contexto, por exemplo, um sistema pequeno,
          popular a struct com informações (no minimo 6);
     * Aplicar buscas em duas chaves, por exemplo, RA_Aluno e NomeAluno.
     * Individual;
     * Entrega para 18/05/2016
*/
#include "ArvoreAVL.h"

ArvAVL *cria_ArvAVL() {
  ArvAVL *raiz = (ArvAVL *)malloc(sizeof(ArvAVL));
  if (raiz != NULL)
    *raiz = NULL;
  return raiz;
}

void libera_NO(struct NO *no) {
  if (no == NULL)
    return;
  libera_NO(no->esq);
  libera_NO(no->dir);
  free(no);
  no = NULL;
}

void libera_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return;
  libera_NO(*raiz);
  free(raiz);
}

int altura_NO(struct NO *no) {
  /* Implementar está função */
  if (no == NULL)
    return -1;
  return no->altura;
}

int altura_ArvAVL(ArvAVL *raiz) {
  /* Implementar está função */
  int esq, dir;
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  esq = altura_NO(&((*raiz)->esq));
  dir = altura_NO(&((*raiz)->dir));

  if (esq > dir)
    return esq + 1;
  if (esq <= dir)
    return dir + 1;
}

int fatorBalanceamento_NO(struct NO *no) {
  /* Implementar está função */
  //     he-hd;

  return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y) {
  if (x > y)
    return x;
  else
    return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return 1;
  if (*raiz == NULL)
    return 1;
  return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
  int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
  return (alt_esq + alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return;
  if (*raiz != NULL) {
    printf("No %d: H(%d) fb(%d)\n", (*raiz)->info, altura_NO(*raiz),
           fatorBalanceamento_NO(*raiz));
    preOrdem_ArvAVL(&((*raiz)->esq));
    preOrdem_ArvAVL(&((*raiz)->dir));
  }
}

void emOrdem_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return;
  if (*raiz != NULL) {
    emOrdem_ArvAVL(&((*raiz)->esq));
    printf("No %d: H(%d) fb(%d)\n", (*raiz)->info, altura_NO(*raiz),
           fatorBalanceamento_NO(*raiz));
    emOrdem_ArvAVL(&((*raiz)->dir));
  }
}

void posOrdem_ArvAVL(ArvAVL *raiz) {
  if (raiz == NULL)
    return;
  if (*raiz != NULL) {
    posOrdem_ArvAVL(&((*raiz)->esq));
    posOrdem_ArvAVL(&((*raiz)->dir));
    printf("No %d: H(%d) fb(%d)\n", (*raiz)->info, altura_NO(*raiz),
           fatorBalanceamento_NO(*raiz));
  }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor) {
  if (raiz == NULL)
    return 0;
  struct NO *atual = *raiz;
  while (atual != NULL) {
    if (valor == atual->info) {
      return 1;
    }
    if (valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return 0;
}
//=================================
void RotacaoSimplesDireita(ArvAVL *A) // LL
{
  printf("\nRotacaoSimplesDireita\n");
  /* Implementar está função */
  // A É A MINHA RAIZ
  struct NO *aux;
  aux = (*A)->esq;
  (*A)->esq = aux->dir;
  aux->dir = *A;

  (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
  (aux)->altura = maior(altura_NO((aux)->esq), (*A)->altura) + 1;
  (*A) = aux;
  // free(aux);
}

void RotacaoSimplesEsquerda(ArvAVL *A) // RR
{
  printf("\nRotacaoSimplesEsquerda\n");
  /* Implementar está função */
  struct NO *aux;
  aux = (*A)->dir;
  (*A)->dir = aux->esq;
  aux->esq = (*A);

  (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
  (aux)->altura = maior(altura_NO((aux)->dir), (*A)->altura) + 1;
  (*A) = aux;
  // free(aux);
}

void RotacaoDuplaDireita(ArvAVL *A) // LR
{
  printf("\nRotacaoDuplaDireita\n");

  /* Implementar está função */
  RotacaoSimplesEsquerda(&(*A)->esq);
  RotacaoSimplesDireita(A);
}

void RotacaoDuplaEsquerda(ArvAVL *A) // RL
{
  printf("\nRotacaoDuplaEsquerda\n");
  /* Implementar está função */
  RotacaoSimplesDireita(&(*A)->dir);
  RotacaoSimplesEsquerda(A);
}

int insere_ArvAVL(ArvAVL *raiz, int valor) {
  int res;
  if (*raiz == NULL) { //�rvore vazia ou nó folha
    struct NO *novo;
    novo = (struct NO *)malloc(sizeof(struct NO));
    if (novo == NULL)
      return 0;

    novo->info = valor;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    *raiz = novo;
    return 1;
  }

  struct NO *atual = *raiz;
  if (valor < atual->info) {
    if ((res = insere_ArvAVL(&(atual->esq), valor)) == 1) {
      if (fatorBalanceamento_NO(atual) >= 2) {
        if (valor < (*raiz)->esq->info) {
          RotacaoSimplesDireita(raiz);
        } else {
          RotacaoDuplaDireita(raiz);
        }
      }
    }
  } else {
    if (valor > atual->info) {
      if ((res = insere_ArvAVL(&(atual->dir), valor)) == 1) {
        if (fatorBalanceamento_NO(atual) >= 2) {
          if ((*raiz)->dir->info < valor) {
            RotacaoSimplesEsquerda(raiz);
          } else {
            RotacaoDuplaEsquerda(raiz);
          }
        }
      }
    } else {
      printf("Valor duplicado!!\n");
      return 0;
    }
  }

  atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;

  return res;
}

struct NO *procuraMenor(struct NO *atual) {
  struct NO *no1 = atual;
  struct NO *no2 = atual->esq;
  while (no2 != NULL) {
    no1 = no2;
    no2 = no2->esq;
  }
  return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor) {
  if (*raiz == NULL) { // valor não existe
    printf("valor nao existe!!\n");
    return 0;
  }

  int res;
  if (valor < (*raiz)->info) {
    if ((res = remove_ArvAVL(&(*raiz)->esq, valor)) == 1) {
      if (fatorBalanceamento_NO(*raiz) >= 2) {
        if (altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
          RotacaoSimplesEsquerda(raiz);
        else
          RotacaoDuplaEsquerda(raiz);
      }
    }
  }

  if ((*raiz)->info < valor) {
    if ((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1) {
      if (fatorBalanceamento_NO(*raiz) >= 2) {
        if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
          RotacaoSimplesDireita(raiz);
        else
          RotacaoDuplaDireita(raiz);
      }
    }
  }

  if ((*raiz)->info == valor) {
    if (((*raiz)->esq == NULL ||
         (*raiz)->dir == NULL)) { // nó tem 1 filho ou nenhum
      struct NO *oldNode = (*raiz);
      if ((*raiz)->esq != NULL)
        *raiz = (*raiz)->esq;
      else
        *raiz = (*raiz)->dir;
      free(oldNode);
    } else { // nó tem 2 filhos
      struct NO *temp = procuraMenor((*raiz)->dir);
      (*raiz)->info = temp->info;
      remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
      if (fatorBalanceamento_NO(*raiz) >= 2) {
        if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
          RotacaoSimplesDireita(raiz);
        else
          RotacaoDuplaDireita(raiz);
      }
    }
    if (*raiz != NULL)
      (*raiz)->altura =
          maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    return 1;
  }

  (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;

  return res;
}
