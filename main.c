#include "trab1.h"

int main(){
    bolas **lista;
    bolas *pilha;
    bolas ***armazem;
    int ant = 0;
    int numbolas = 0;
    int cores,a = 0;
    int *listasequencial;
    printf("Digite o numero de cores a ser usado: ");
    scanf("%d",&cores);
    armazem = cria_lista_armazena_permuta(cores);
    listasequencial = cria_lista_sequencial(cores);
    lista = inicializa_bolas(cores);
   
    while(a < cores){
        pilha = cria_pilha_inicial(lista,cores,&ant,&numbolas);
        armazem = aloca_vetor_armazem(numbolas,armazem,a);
        armazem = permuta_bolas(pilha,numbolas,armazem,a);
        a++;
    }
    imprime_armazem(listasequencial,armazem,cores,lista);
}