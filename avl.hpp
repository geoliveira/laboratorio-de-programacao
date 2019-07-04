typedef double TC; typedef float TV;

struct Noh { 
	TC chave;
	TV valor;
	Noh *esq, *dir, *pai;
	int h;
};

struct DicAVL {
	Noh *raiz;

}; // Nulo quando árvore vazia

void inicializar (DicAVL &D); // Inicializa D como uma árvore vazia.

Noh* inserir (DicAVL &D, TC c, TV v); // Retorna um ponteiro para o novo nó, ou nulo se erro de alocação

Noh* procurar (DicAVL &D, TC c); // Retorna um ponteiro para o nó da chave procurada, ou nulo se a chave não estiver em D.

void remover (DicAVL &D, Noh *n); // ’n’ aponta para o nó a ser removido

void terminar (DicAVL &D); // Desaloca os nós da árvore.

// =========================	FUNÇÕES COMPLEMENTARES	=========================

Noh *rotacao_esquerda(DicAVL &D, Noh *noA);

Noh *rotacao_direita(DicAVL &D, Noh *noA);

Noh *min(Noh *no);

Noh *max(Noh *no);

int altura(Noh *no);

void atualizar_altura(Noh *no);

int esta_pensa_a(Noh *no);

void mostrar_no(Noh *raiz, Noh *no);

void deletar(Noh* no);