#include <iostream>
#include <stdlib.h>
#include "avl.hpp"

using namespace std;

// Inicializa D como uma árvore vazia.
void inicializar (DicAVL &D) {
	D.raiz = NULL;
}

// Desaloca os nós da árvore.
void terminar (DicAVL &D) {
	if (D.raiz != NULL) {
		Noh *no = D.raiz;

		deletar(no); // função recursiva
		
		D.raiz = NULL;
	}
}

// Retorna um ponteiro para o nó da chave procurada, ou nulo se a chave não estiver em D.
Noh* procurar (DicAVL &D, TC c) {
	if (D.raiz != NULL){
		Noh *aux = D.raiz;
	
		while (aux != NULL)
		{
			if (c > (*aux).chave)
				aux = (*aux).dir;
			else if (c < (*aux).chave)
				aux = (*aux).esq;
			else 
				return aux; // chave encontrada
		}
	}

	return NULL; // nó procurado não está na arv
}

// Retorna um ponteiro para o novo nó, ou nulo se erro de alocação
Noh* inserir(DicAVL &D, TC c, TV v) {
	Noh *no = (Noh*) malloc(sizeof(Noh));

	if (no == NULL) return NULL; // erro de alocação
	// criando o novo nó
	(*no).chave = c;
	(*no).valor = v;
	(*no).dir = NULL;
	(*no).esq = NULL;
	(*no).pai = NULL;
	(*no).h = 1;

	// árvore vazia
	if (D.raiz == NULL) {
		D.raiz = no;
		return no;
	}
	
	Noh *temp = D.raiz, *aux = NULL;
	// percorremos até o chegar em um nó folha
	while (temp != NULL) {
		aux =  temp;

		if (c < (*temp).chave)
			temp = (*temp).esq;
		else if (c > (*temp).chave)
			temp = (*temp).dir;
		else
			return NULL; // se chave forem iguais
	}
	// posição que o novo nó deve ficar em relação ao seu pai
	if (c < (*aux).chave)
		(*aux).esq = no;
	else 
		(*aux).dir = no;

	(*no).pai = aux; // guardando pai do novo nó
	int haux;
	
	// consertar altura da árvore
	while (aux != NULL) {
		haux = (*aux).h; // guardando a altura antiga
		
		atualizar_altura(aux);

		// se tam da subarv aumentar. // obs: valor positivo = árvore pensa a direita; valor negativo = árvore pensa a esquerda
		if (haux < (*aux).h) 
		{ 
			// (aux = +2; filho_de_aux = +1) subárvore direita da subárvore direita de 'aux'
			if (esta_pensa_a(aux) == 2 && esta_pensa_a((*aux).dir) == 1)
			{
				rotacao_esquerda(D, aux);
			}// (aux = +2; filho_de_aux = -1) subárvore esquerda da subárvore direita de 'aux'
			else if (esta_pensa_a(aux) == 2 && esta_pensa_a((*aux).dir) == -1)
			{
				rotacao_direita(D, (*aux).dir);
				rotacao_esquerda(D, aux);

			}// (aux = -2; filho_de_aux = -1) subárvore esquerda da subárvore esquerda de 'aux'
			else if (esta_pensa_a(aux) == -2 && esta_pensa_a((*aux).esq) == -1)
			{
				rotacao_direita(D, aux);
			}// (aux = -2; filho_de_aux = +1) subárvore direita da subárvore esquerda de 'aux'
			else if (esta_pensa_a(aux) == -2 && esta_pensa_a((*aux).esq) == 1)
			{
				rotacao_esquerda(D, (*aux).esq);
				rotacao_direita(D, aux);
			}
		}

		aux = (*aux).pai;
	}
	
	return no;
}

// ’n’ aponta para o nó a ser removido
void remover(DicAVL &D, Noh *n) {
	if (n == NULL) return;

	Noh* no = procurar(D, (*n).chave);
	
	if (no == NULL) return;
	
	// criando novas variavéis para facilitar a leitura do código.
	Noh *noE = (*no).esq, *noD = (*no).dir, *noP = (*no).pai, *aux;
	
	aux = noP; // obs: variáveis 'aux' é usada no conserto da árvore, caso necessário

	// obs: a remoção dos 3 primeiros casos abaixo são semelhantes.

	// 'no' sem filhos
	if (noE == NULL && noD == NULL) {
		if (noP != NULL) {
			// corrigindo o ponteiro dos filhos do pai do nó removido
			if ((*noP).dir == no) 
				(*noP).dir = NULL;
			else 
				(*noP).esq = NULL;

		} else {
			D.raiz = NULL; // se não tiver pai, logo o nó removido é a raiz
			return; // não há mais nada a fazer
		}
	} // possui somente filho esquerdo
	else if (noD == NULL) {
		if (noP != NULL) {
			
			if ((*noP).dir == no)
				(*noP).dir = noE;
			else
				(*noP).esq = noE;
			
			(*noE).pai = noP;
		
		} else D.raiz = noE;
	} // possui somente filho direito
	else if (noE == NULL) {
		if (noP != NULL) {
			
			if ((*noP).dir == no)
				(*noP).dir = noD;
			else
				(*noP).esq = noD;
			
			(*noD).pai = noP;
		
		} else D.raiz = noE;
	} // possui os 2 filhos
	else {
		Noh *ant = max(noE); // 'ant' é antecessor de 'no'
		
		aux = ant; // obs: variáveis 'aux' é usada no conserto da árvore, caso necessário
		
		// se pai de ant não for 'no'
		if ((*ant).pai != no)
		{	
			aux = (*ant).pai; // obs: é necessário começar o conserto do ponto certo. por isso, guardamos os nós a cada situação diferente

			if ((*ant).esq != NULL) // se 'ant' tiver filho esquerdo, temos que ajeitar os ponteiros envolvidos na relação
			{
				(*ant).esq->pai = (*ant).pai; // filho esquerdo de 'ant' tem como pai o seu avó
				(*ant).pai->dir = (*ant).esq; // obs: como 'no' não é pai de ant, então ele é filho direito de alguem
			} 
			else // 'ant' não tem filhos. atualizamos os filhos de seu pai
			{
				if ((*ant).pai->dir == ant) (*ant).pai->dir = NULL;
				else (*ant).pai->esq = NULL;
			}
			// aqui, nós já começamos a substituição de 'no'
			(*ant).esq = noE; // note que atualizamos os ponteiros do filho do nó substituto 'ant' somente se ele não tiver o nó que será removido como pai
			(*ant).esq->pai = ant;
		}

		(*ant).dir = noD; // note que o nó removido terá sempre o filho direito como nulo
		(*ant).dir->pai = ant;

		// se o nó que será removido não for a raiz, atualizamos o ponteiro dos filhos do pai do nó que será removido
		if (noP != NULL && (*noP).dir == no)
			(*noP).dir = ant;
		else if (noP != NULL && (*noP).esq == no)
			(*noP).esq = ant;
			
		(*ant).pai = noP;
		
		atualizar_altura(ant); // atualizamos a altura do nó, agora já substito de 'no'

		if (D.raiz == no) D.raiz = ant;
	}
	
	int haux;
	// consertando a altura da árvore caso necessário. note que é muito semelhante a inserção.
	// entretanto dos 4 casos, 2 são diferentes. esses casos da rotação simples a direita e a esquerda
	while (aux != NULL) {
		haux = (*aux).h; // guardando a altura antiga
		
		atualizar_altura(aux);

		// se tam da subarv diminuir, verificamos se há necessidade de conserto da árvore
		if (haux >= (*aux).h) 
		{
			if (esta_pensa_a(aux) == 2)
			{
				if (esta_pensa_a((*aux).dir) == -1) // caso iguai a inserção
				{
					rotacao_direita(D, (*aux).dir);
					rotacao_esquerda(D, aux);
				} 
				else 
				{ // ao contrário da inserção, na remoção não vemos se o os filhos de 'aux' estão pendendo alguma direção
					rotacao_esquerda(D, aux);
				}
			}
			else if (esta_pensa_a(aux) == -2)
			{
				if (esta_pensa_a((*aux).esq) == 1) // caso iguai a inserção
				{
					rotacao_esquerda(D, (*aux).esq);
					rotacao_direita(D, aux);
				} 
				else
				{ // ao contrário da inserção, na remoção não vemos se o os filhos de 'aux' estão pendendo alguma direção
					rotacao_direita(D, aux);
				}
			}
		}

		aux = (*aux).pai;
	}

	(*no).esq = (*no).dir = (*no).pai = NULL;

	delete(no);
}

// =========================	FUNÇÕES COMPLEMENTARES	=========================

Noh *rotacao_esquerda(DicAVL &D, Noh *noA) {
	if (noA != NULL && (*noA).dir != NULL) {
		Noh *noB = (*noA).dir;
		
		(*noA).dir = (*noB).esq;
		if ((*noA).dir != NULL) (*noA).dir->pai = noA;

		(*noB).esq = noA;
		(*noB).pai = (*noA).pai;

		if ((*noA).pai != NULL) {
			if (noA == (*noA).pai->dir) (*noA).pai->dir = noB;
			else (*noA).pai->esq = noB;
		} 
		else {
			D.raiz = noB;
		}
		
		(*noA).pai = noB; 

		atualizar_altura(noA);
		atualizar_altura(noB);
		
		noA = noB;
	}

	return noA;
}

Noh *rotacao_direita(DicAVL &D, Noh *noA) {
	if (noA != NULL && (*noA).esq != NULL) {
		Noh *noB = (*noA).esq;

		(*noA).esq = (*noB).dir;
		if ((*noA).esq != NULL) (*noA).esq->pai = noA; // se não for folha, atualiza o pai

		(*noB).dir = noA;
		(*noB).pai = (*noA).pai;

		if ((*noA).pai != NULL) {
			if (noA == (*noA).pai->dir) (*noA).pai->dir = noB;
			else (*noA).pai->esq = noB;
		} 
		else {
			D.raiz = noB;
		}

		(*noA).pai = noB;

		atualizar_altura(noA);
		atualizar_altura(noB);
		
		noA = noB;
	}

	return noA;
}

Noh *min(Noh *raiz) {
	if (raiz == NULL) return NULL;

	Noh *aux = raiz;

	while ((*aux).esq != NULL) aux = (*aux).esq;
	
	return aux;
}

Noh *max(Noh *raiz) {
	if (raiz == NULL) return NULL;

	Noh *aux = raiz;

	while ((*aux).dir != NULL) aux = (*aux).dir;
	
	return aux;
}

int altura(Noh *no) {
	if (no != NULL) return (*no).h;
	return 0;
}

void atualizar_altura(Noh *no) {
	if (no != NULL) {
		if (altura((*no).esq) > altura((*no).dir)) 
			(*no).h = altura((*no).esq)+1;
		else	
			(*no).h = altura((*no).dir)+1;
	}
}

int esta_pensa_a(Noh *no) {
	return altura((*no).dir) - altura((*no).esq);
}
// função usada no apenas para debug do código
void mostrar_no(Noh *raiz, Noh *no) {
	if (no != NULL) {
		if ((*no).pai != NULL) cout << "\t\t" << (*no).pai->chave << " (" << (*no).pai->h << ")" << endl;
		else if (raiz == no) cout << "\t\traiz" << endl;
		else cout << "\t\t* (*)" << endl;
		
		cout << "\t\t" << (*no).chave << " (" << (*no).h << ")" << endl;

		if ((*no).esq != NULL) cout << "\t" << (*no).esq->chave << " (" << (*no).esq->h << ")";
		else cout << "\t* (*)";

		if ((*no).dir != NULL) cout << "\t\t" << (*no).dir->chave << " (" << (*no).dir->h << ")" << endl;
		else cout << "\t\t* (*)" << endl;
	}
}

void deletar(Noh* no){
    if(no != NULL) {
		deletar((*no).esq);
		deletar((*no).dir);
		delete(no);
    }
}