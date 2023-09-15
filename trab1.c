#include "trab1.h"

bolas *cria_bolas(int cor){
    bolas *novo = (bolas*) calloc(1,sizeof(bolas));
    if(novo == NULL){
        printf("Erro de alocacao\n");
        exit(1);
    }
    char palavra[50];
    printf("Digite a palavra aprendida: \n");
    getc(stdin);
    scanf("%s",palavra);
    novo->numbcor = cor;
    strcpy(novo->palavra,palavra);
    return novo;
}
bolas *cria_no_cabeca(){
    bolas*novo = (bolas*) calloc(1,sizeof(bolas));
    if(novo == NULL){
        printf("Erro de alocacao\n");
        exit(1);
    }
    return novo;
}

bolas *insere_bolas(bolas *lista,int cor,int bolass){
    if(lista == NULL){
        bolas *cabeca = cria_no_cabeca();
        lista = cabeca;
        bolas *novo = cria_bolas(cor);
        lista->numbcor = cor;
        lista->numbolas = bolass;
        lista->prox = novo;
        novo->ant = lista;
        return lista;
    }else{
        bolas *aux;
        aux = lista;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        bolas *novo = cria_bolas(cor);
        aux->prox = novo;
        novo->ant = aux;
        return lista;
    } 
}

bolas **inicializa_bolas(int numcores){
    bolas **novo = (bolas**) calloc(numcores,sizeof(bolas*));
    int a=0,i=0,numbolas;
    while(a<numcores){
        printf("Digite a quantidade de bolas da cor %d \n",a);
        scanf("%d",&numbolas);
        i=0;
        while(i<numbolas){
            novo[a] =  insere_bolas(novo[a],numcores,numbolas);
            i++;
        }
        a++;
    }
    return novo;
}

bolas *cria_pilha_inicial(bolas **lista,int numcaixas,int *ant,int *numbolas){
    //pilha inicial
    bolas *pilha = cria_pilha_cabeca();
    bolas **aux = lista;
    int menor;
    int i=0,x=0;
    while(x<numcaixas){
        if(aux[x]->numbolas > *ant){
            menor = aux[x]->numbolas;
            break;
        }
        x++;
    }
    while(i<numcaixas){
        if(aux[i]->numbolas < menor && aux[i]->numbolas > *ant){
            menor = aux[i]->numbolas;
        }
        i++;
    }
    *numbolas = menor;
    pilha = insere_pilha(pilha,lista,menor,numcaixas);
    *ant = menor;

    return pilha;

}

bolas *cria_pilha_cabeca(){
    bolas *novo = (bolas*) calloc(1,sizeof(bolas));
    if(novo == NULL){
        printf("Falha na alocacao");
        exit(1);
    }
    return novo;


}
bolas *insere_novo_pilha(bolas *pilha, bolas *lista){
    bolas *novo = (bolas*) calloc(1,sizeof(bolas));
    if(novo == NULL){
        printf("erro de alocacao");
        exit(1);
    }
    novo->numbcor = lista->numbcor;
    novo->numbolas = lista->numbolas;
    strcpy(novo->palavra,lista->palavra);


    if(pilha->ant == NULL){
        pilha->prox = novo;
    }else{
        pilha->ant->prox = novo;
        novo->ant = pilha ->ant;    
    }
    pilha->ant =novo;

    return pilha;

}


bolas *insere_pilha(bolas *pilha,bolas **lista,int menor,int numcaixas){
    bolas **aux2 = lista;
    bolas *aux3;
    int i=0;
    while(i<numcaixas){
        if(aux2[i]->numbolas ==menor){
            break;
        }
        i++;
    }
    aux3 = aux2[i]->prox;
    while(aux3 != NULL){
        pilha = insere_novo_pilha(pilha,aux3);
        aux3 = aux3->prox;
    }

    return pilha;


}

bolas ***cria_lista_armazena_permuta(int numcaixas){
    bolas ***novo = (bolas***) malloc(numcaixas*sizeof(bolas**));
    if (novo == NULL){
        printf("Erro de alocacao");
        exit(1);
    }
    return novo;
}

bolas ***aloca_vetor_armazem(int numbolas,bolas ***armazem,int caixamexendo){
    int vezes;
    int i= 0;
    vezes = calcula_numero_permuta(numbolas);
    armazem[caixamexendo] = (bolas**) malloc(vezes*sizeof(bolas*));
    while(i<vezes){
        armazem[caixamexendo][i] = NULL;
        i++;
    }
    return armazem;
}

int calcula_numero_permuta(int numerobolas){
    int permuta = numerobolas;
    int inicio = permuta - 1;
    for(int i = numerobolas - 1 ; i > 0; i--){
        permuta  =  permuta * inicio;
        inicio = inicio - 1;
    }
    return permuta;
}
bolas *copia_pilha(bolas *pilha){
    bolas *novo = (bolas*) calloc(1,sizeof(bolas));
    if(novo == NULL){
        printf("Erro alocacao");
        exit(1);
    }
    strcpy(novo->palavra,pilha->palavra);
    novo->numbcor = pilha->numbcor;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;

}

bolas ***adiciona_permuta(bolas ***lista, int caixamexendo, bolas *pilha,int vezes){
    bolas *aux;
    bolas *aux2 = pilha->prox;
    if(lista[caixamexendo][vezes] == NULL){   
        lista[caixamexendo][vezes] = cria_no_cabeca();
    } 
    aux = lista[caixamexendo][vezes];;
    while(aux2 != NULL){
        aux = lista[caixamexendo][vezes];
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = copia_pilha(aux2);
        //printf("%d, %s, ----", aux->prox->numbcor,aux->prox->palavra);
        aux2 = aux2->prox;
    }
    return lista;

}



void insere_fila_remove_pilha(bolas *lista, bolas *fila){
    bolas *aux = lista->ant;
    //Exclui o ultimo elemento da pilha
    if(aux != NULL){
        lista->ant = aux->ant;
        if(lista->ant != NULL){
            lista->ant->prox = NULL;
        }else{
            lista->prox = NULL;
        }
    }
    //Pego o elemento excluido da pilha e insere na fila
    if(fila->ant == NULL){
        fila->prox = aux;
    }else{
        fila->ant->prox = aux;
        aux->ant = fila->ant;
    }
    fila->ant = aux;
}

void insere_pilha_remove_fila(bolas *lista, bolas *fila){
    //Remove o primeiro elemento da fila 
    bolas *aux = fila->prox;
    if(aux != NULL){
        fila->prox = aux->prox;
        if(aux->prox == NULL){
            fila->ant = NULL;
        }else{
            aux->prox->ant = NULL;
        }
    }
    aux->prox = NULL;
    aux->ant = NULL;

    if(lista->ant == NULL){
        lista->prox = aux;
    }else{
        lista->ant->prox = aux;
        aux->ant = lista->ant;
    }
    lista->ant = aux;
}
    


bolas ***permuta_bolas(bolas *pilha, int numbolas,bolas ***armazem,int caixamexendo){
    int *novoqt = (int*) calloc(numbolas-1,sizeof(int));
    int n = 0;
    while(n < numbolas-1){
        novoqt[n] = 0;
        n++;
    }
    bolas *fila = cria_no_cabeca();
    int qt = 2;
    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int x=0,z=0,k=0,mat= 0,p=0;
    int aux = 0;
    int vezes = calcula_numero_permuta(numbolas);
    int i = 0;
    int v = 0;
    int e,auxe;
    while(i < vezes){
        count3 = 0;
        while(count3 < numbolas -1){
            x=0;
            aux = 0;
            while(x < numbolas -1){
                if(novoqt[x] == 0){
                    aux = 1; 
                    break;
                }
                x++;
            }
            if(aux == 1){
                if(novoqt[count3] == 0){
                    novoqt[count3] = 1;
                    z=0;
                    while(z <count3){
                        novoqt[z] = 0;
                        z++;
                    }
                    qt = 2;
                    p=0;
                    while(p<numbolas-1){
                        if(novoqt[p] == 1){
                            mat = mat + 1;
                        }
                        p++;
                    }
                    mat = 0;
                    if(mat >= 2){
                        qt = mat+1;
                        break;
                    }


                    auxe = 0;
                    e = 0;
                    while(e < numbolas -1){
                        if(novoqt[e] == 0){
                            auxe = 1;
                            break;
                        }
                        e++;
                    }
                    if(auxe == 1){
                        break;
                    }else{
                        qt = numbolas;
                        k=0;
                        while(k<numbolas-1){
                            if(k == 0){
                                novoqt[k] =1;
                                k++;
                            }else{
                                novoqt[k]= 0;
                                k++;
                            }
                        }
                        break;
                    }
                    break;
                }
            }else{
                k=0;
                while(k<numbolas-1){
                    if(k == 0){
                        novoqt[k] = 1;
                        k++;
                    }else{
                        novoqt[k] = 0;
                        k++;
                    }
                }
                qt = 2;
                break;
            }
            count3 ++;
        }
        v = 0;
        while(v <numbolas-1){
            v++;
        }
        count = 0;

        while(count < qt){
            insere_fila_remove_pilha(pilha,fila);
            count++;
        }
        count2 = 0;
        while(count2 <qt){
            insere_pilha_remove_fila(pilha,fila);
            count2++;
        }
        armazem = adiciona_permuta(armazem,caixamexendo,pilha,i);
        i++;
    }
    return armazem;
}

int busca_cor_retorna_numero_bolas(bolas **lista, int cor,int numcaixas){
    int x = 0;
    bolas **aux = lista;
    int numerodebolas = 0;
    while(x < numcaixas){
        if(aux[x]->numbcor == cor){
            numerodebolas = aux[x]->numbolas;
            break;
        }
        x++;
    }
    return numerodebolas;
}


int *cria_lista_sequencial(int numcaixas){
    int *lista = (int*) calloc(numcaixas,sizeof(int));
    int x = 0;
    if (lista == NULL){
        printf("ERRO");
        exit(1);
    }
    while(x<numcaixas){
        lista[x] = 0;
        x++;
    }
    return lista;
}

int *arruma_lista_sequencial(int numcaixas,int *listasequencial,bolas **lista,bolas ***armazem){
    int x=0,y=0,z=0;
    int numerodebolas;
    int cor;
    int aux = 0;
    int vezes = 0;
    //bolas *point;
    while(x<numcaixas){
        cor = armazem[x][0]->prox->numbcor;
        numerodebolas = busca_cor_retorna_numero_bolas(lista,cor,numcaixas);
        vezes = calcula_numero_permuta(numerodebolas);
        if(listasequencial[x] == vezes - 1){
            y = x;
            while(y<numcaixas){
                //point = armazem[y][0]->prox;
                cor = armazem[y][0]->prox->numbcor;
                numerodebolas = busca_cor_retorna_numero_bolas(lista,cor,numcaixas);
                vezes = calcula_numero_permuta(numerodebolas);
                aux = 0;
                if(listasequencial[y] != vezes - 1){
                    aux = 1;
                }
                y++;

            }
            if(aux == 0){
                listasequencial[x-1] = listasequencial[x-1] + 1;
                z = x;
                while(z < numcaixas){
                    listasequencial[z] = 0;
                }
                break;
            }   
        }else{
            if(x == numcaixas-1){
                listasequencial[numcaixas-1] = listasequencial[numcaixas-1] + 1;
            }
        }
        x++;
    }
    return listasequencial;
}
int calcula_permuta_total(bolas ***armazem,int numcaixas,bolas **lista){
    int x = 0; 
    int cor;
    int numerodebolas;
    int vezes;
    int permuta = 1;
    bolas *aux;
    while(x<numcaixas){
        aux = armazem[x][0]->prox;;
        cor = aux->numbcor;
        numerodebolas = busca_cor_retorna_numero_bolas(lista,cor,numcaixas); 
        vezes = calcula_numero_permuta(numerodebolas);
        permuta = permuta * vezes; 
        
        x++;
    }
    return permuta;
}



void imprime_armazem(int *listasequencial, bolas***armazem,int numcaixas,bolas **lista){
    int  linha = 0, coluna = 0;
    int vztotal;
    int y = 0;
    bolas *aux;
    vztotal = calcula_permuta_total(armazem,numcaixas,lista);
    //printf("\nvztotal %d",vztotal);
    while(y< vztotal){
        coluna = 0;
        while(coluna < numcaixas){
            linha = listasequencial[coluna];
            aux = armazem[coluna][linha]->prox;
            while(aux != NULL){
                printf("Cor: %d,  Palavra: %s -- ",aux->numbcor,aux->palavra);
                aux = aux->prox;
            }
            coluna++;
        }
        printf("\n");
        listasequencial = arruma_lista_sequencial(numcaixas,listasequencial,lista,armazem);
        y++;
    }
}