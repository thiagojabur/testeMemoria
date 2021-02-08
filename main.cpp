#include <iostream>
#include <ctime>
#include <chrono>

#define TAMANHO 120000
#define MOSTRAR 0

using namespace std;

struct Node
{
    int num;
    struct Node *prox;
};
typedef struct Node node;

int tam;

void inicia(node *LISTA);
node *criaNo();
void insereFim(node *LISTA, int i);
void insereInicio(node *LISTA, int i);
void exibe(node *LISTA);
void libera(node *LISTA);
void insere (node *LISTA, int i);
node *retiraInicio(node *LISTA);
node *retiraFim(node *LISTA);
node *retira(node *LISTA, int posicao);
void bolha(int *primeiro, int *ultimo);
void ordena(node *LISTA);
int vazia(node *LISTA);
void swap(node *a, node *b);

int main()
{
    node *LISTA = (node *) malloc(sizeof(node));
    if(!LISTA)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    else
    {
        inicia(LISTA);

        int i, vetor[TAMANHO], vetorAleatorios[TAMANHO]; //alocação estática

        cout << "*** Pesquisa de alocacao de memoria ***" << endl << endl;

        srand((unsigned)time(0));
        int maior = 9999;
        int menor = 1000;

        cout << "Criando " << TAMANHO << " numeros aleatorios" << endl << endl;
        //gerando numeros aleatorios
        for( i = 0 ; i <= (TAMANHO-1); i++)
        {
            vetorAleatorios[i] = rand()%(maior-menor+1) + menor;
        }

        cout << endl << "Criando o arranjo (memoria estatica)" << endl << endl;
        auto inicio = std::chrono::high_resolution_clock::now();
        for( i = 0 ; i <= (TAMANHO-1); i++)
        {
            vetor[i] = vetorAleatorios[i];
            if (MOSTRAR)
                std::cout << "Numero aleatorio gerado no arranjo[" << i << "] -> " << vetor[i] << std::endl;
        }
        auto resultado = std::chrono::high_resolution_clock::now() - inicio;
        long long tempo = std::chrono::duration_cast<std::chrono::seconds>(resultado).count();
        cout<<endl<< "Tempo de criacao do arranjo (memoria estatica): " << tempo << " segundos" << endl << endl;

        cout << endl << "Criando a lista encadeada (memoria dinamica)" << endl << endl;
        inicio = std::chrono::high_resolution_clock::now();
        //inserindo na lista dinamica
        for( i = 0 ; i <= (TAMANHO-1); i++)
        {
            insereFim(LISTA, vetor[i]);
        }
        resultado = std::chrono::high_resolution_clock::now() - inicio;
        tempo = std::chrono::duration_cast<std::chrono::seconds>(resultado).count();

        cout<<endl<< "Tempo de criacao da lista encadeada (memoria dinamica): " << tempo << " segundos" << endl << endl;

        inicio = std::chrono::high_resolution_clock::now();

        cout << endl << "Ordenando o arranjo estatico via Bubble Sort" << endl << endl;
        //ordenando pelo método bolha
        bolha(vetor, &vetor[TAMANHO-1]);

        resultado = std::chrono::high_resolution_clock::now() - inicio;
        tempo = std::chrono::duration_cast<std::chrono::seconds>(resultado).count();

        cout<<std::endl<< "Tempo de ordenacao do arranjo (memoria estatica): " << tempo << " segundos" << std::endl << std::endl;

        if (MOSTRAR) {
            cout<<std::endl<<"Arranjo apos ordenacao Bubble Sort." << std::endl;
            for( i = 0 ; i <= (TAMANHO-1); i++)
            {
                std::cout << "arranjo[" << i << "] -> " << vetor[i] << std::endl;
            }
            printf("\n");
            exibe(LISTA);
        }

        inicio = std::chrono::high_resolution_clock::now();
        ordena(LISTA);
        resultado = std::chrono::high_resolution_clock::now() - inicio;
        tempo = std::chrono::duration_cast<std::chrono::seconds>(resultado).count();

        cout<<std::endl<< "Tempo de ordenacao da lista encadeada (memoria dinamica): " << tempo << " segundos" << std::endl << std::endl;

        if (MOSTRAR)
            exibe(LISTA);

        cout<<endl<< "Retirando terceiro elemento da lista encadeada"<<endl;
        inicio = std::chrono::high_resolution_clock::now();
        retira(LISTA, 3);
        resultado = std::chrono::high_resolution_clock::now() - inicio;
        tempo = std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count();

        if (MOSTRAR)
            exibe(LISTA);

        cout<<endl<< "Tempo de remocao da lista encadeada (memoria dinamica): " << tempo << " nanosegundos" << endl << endl;

        cout<<endl<< "Retirando terceiro elemento do arranjo"<<endl;

        // tem que passar todos elementos depois dele para uma casa antes
        inicio = std::chrono::high_resolution_clock::now();
        for( i = 2 ; i <= (TAMANHO-2); i++)
               vetor[i] = vetor[i+1];
        vetor[TAMANHO-1] = 0;
        resultado = std::chrono::high_resolution_clock::now() - inicio;
        tempo = std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count();


        if (MOSTRAR)
            for( i = 0 ; i <= (TAMANHO-2); i++)
                cout << "arranjo[" << i << "] -> " << vetor[i] << endl;

        cout<<endl<< "Tempo de remocao do arranjo (memoria estatica): " << tempo << " nanosegundos" << endl << endl;

        free(LISTA);
        return 0;
    }
}

void inicia(node *LISTA)
{
    LISTA->prox = NULL;
    tam=0;
}


void ordena(node *LISTA) {

    if(vazia(LISTA)) return; //se for nulo(vazio)
    if(vazia(LISTA->prox)) return; //se for apenas 1 elemento não precisa ordenar

    int swapped;
    node *ptr1;
    node *lptr = NULL;

    cout<<"Ordenando a lista encadeada via Bubble Sort \n";

    do
    {
        swapped = 0;
        ptr1 = LISTA->prox;

        while (ptr1->prox != lptr)
        {

            if (ptr1->num > ptr1->prox->num)
            {
                swap(ptr1, ptr1->prox);
                swapped = 1;
            }
            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    }
    while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap(node *a, node *b)
{
    int temp = a->num;

    a->num = b->num;
    b->num = temp;


}

void troca(int* a, int* b) {
   int aux = *a;
   *a = *b;
   *b = aux;
}

void bolha (int *primeiro, int *ultimo) {
   int naoTrocou;
   int *posAtual;
   for (; ultimo > primeiro; --ultimo) {
      naoTrocou = 1;
      for (posAtual = primeiro; posAtual < ultimo; ++posAtual) {
         if (*posAtual > *(posAtual+1)) {
            troca (posAtual, posAtual+1);
            naoTrocou = 0;
         }
      }
      if (naoTrocou) return;
   }
}


int vazia(node *LISTA)
{
    if(LISTA->prox == NULL)
        return 1;
    else
        return 0;
}

node *aloca(int i)
{
    node *novo=(node *) malloc(sizeof(node));
    if(!novo)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    else
    {
        novo->num = i;
        return novo;
    }
}


void insereFim(node *LISTA, int i)
{
    node *novo=aloca(i);
    novo->prox = NULL;

    if(vazia(LISTA))
        LISTA->prox=novo;
    else
    {
        node *tmp = LISTA->prox;

        while(tmp->prox != NULL)
            tmp = tmp->prox;

        tmp->prox = novo;
    }
    tam++;
}

void insereInicio(node *LISTA, int i)
{
    node *novo=aloca(i);
    node *oldHead = LISTA->prox;

    LISTA->prox = novo;
    novo->prox = oldHead;

    tam++;
}

void exibe(node *LISTA)
{

    if(vazia(LISTA))
    {
        printf("Lista vazia!\n\n");
        return ;
    }

    node *tmp;
    tmp = LISTA->prox;
    printf("Lista:");
    while( tmp != NULL)
    {
        printf("%5d", tmp->num);
        tmp = tmp->prox;
    }
    printf("\n        ");
    int count;
    for(count=0 ; count < tam ; count++)
        printf("  ^  ");
    printf("\nOrdem:");
    for(count=0 ; count < tam ; count++)
        printf("%5d", count);


    printf("\n\n");
}

void libera(node *LISTA)
{
    if(!vazia(LISTA))
    {
        node *proxNode,
             *atual;

        atual = LISTA->prox;
        while(atual != NULL)
        {
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}

void insere(node *LISTA, int i)
{
    int pos,
        count;
    printf("Em que posicao, [de 1 ate %d] voce deseja inserir: ", tam);
    scanf("%d", &pos);

    if(pos>0 && pos <= tam)
    {
        if(pos==1)
            insereInicio(LISTA, i);
        else
        {
            node *atual = LISTA->prox,
                  *anterior=LISTA;
            node *novo=aloca(i);

            for(count=1 ; count < pos ; count++)
            {
                anterior=atual;
                atual=atual->prox;
            }
            anterior->prox=novo;
            novo->prox = atual;
            tam++;
        }

    }
    else
        printf("Elemento invalido\n\n");
}

node *retiraInicio(node *LISTA)
{
    if(LISTA->prox == NULL)
    {
        printf("Lista ja esta vazia\n");
        return NULL;
    }
    else
    {
        node *tmp = LISTA->prox;
        LISTA->prox = tmp->prox;
        tam--;
        return tmp;
    }

}

node *retiraFim(node *LISTA)
{
    if(LISTA->prox == NULL)
    {
        printf("Lista ja vazia\n\n");
        return NULL;
    }
    else
    {
        node *ultimo = LISTA->prox,
              *penultimo = LISTA;

        while(ultimo->prox != NULL)
        {
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }

        penultimo->prox = NULL;
        tam--;
        return ultimo;
    }
}

node *retira(node *LISTA, int posicao)
{
    int count;




    if(posicao>0 && posicao <= tam)
    {
        if(posicao==1)
            return retiraInicio(LISTA);
        else
        {
            node *atual = LISTA->prox,
                  *anterior=LISTA;

            for(count=1 ; count < posicao ; count++)
            {
                anterior=atual;
                atual=atual->prox;
            }

            anterior->prox=atual->prox;
            tam--;
            return atual;
        }

    }
    else
    {
        printf("Elemento invalido\n\n");
        return NULL;
    }
}
