#ifndef __TRAB1_H__
#define __TRAB1_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct bolas{
    int numbcor;
    int numbolas;
    char palavra[100];
    struct bolas *prox,*ant;
}bolas;

bolas *cria_bolas(int cor);
bolas *cria_no_cabeca();
bolas *insere_bolas(bolas *lista,int cor,int bolass);
bolas **inicializa_bolas(int numcores);
bolas *cria_pilha_inicial(bolas **lista,int numcaixas,int *ant,int *numbolas);
bolas *cria_pilha_cabeca();
bolas *insere_novo_pilha(bolas *pilha, bolas *lista);
bolas *insere_pilha(bolas *pilha,bolas **lista,int menor,int numcaixas);
bolas ***cria_lista_armazena_permuta(int numcaixas);//
bolas ***aloca_vetor_armazem(int numbolas,bolas ***armazem,int caixamexendo);//
bolas *copia_pilha(bolas *pilha);
int calcula_numero_permuta(int numerobolas);
bolas ***adiciona_permuta(bolas ***lista, int caixamexendo, bolas *pilha,int vezes);//
void insere_fila_remove_pilha(bolas *lista, bolas *fila);
void insere_pilha_remove_fila(bolas *lista, bolas *fila);
bolas ***permuta_bolas(bolas *pilha, int numbolas,bolas ***armazem,int caixamexendo);//
int busca_cor_retorna_numero_bolas(bolas **lista, int cor,int numcaixas);
int *cria_lista_sequencial(int numcaixas);
int *arruma_lista_sequencial(int numcaixas,int *listasequencial,bolas **lista,bolas ***armazem);//
int calcula_permuta_total(bolas***armazem,int numcaixas,bolas **lista);//
void imprime_armazem(int *listasequencial, bolas***armazem,int numcaixas,bolas **lista);//

#endif