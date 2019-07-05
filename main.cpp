#include <iostream>
#include "avl.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
	DicAVL r; 
	inicializar(r);

	//inserir(r, 4, 0);
	//inserir(r, 5, 0);
	//inserir(r, 7, 0);
	//inserir(r, 2, 0);
	//inserir(r, 1, 0);
	//inserir(r, 3, 0);
	//inserir(r, 6, 0);
	
	// inserir(r, 7, 0);
	// inserir(r, 3, 0);
	// inserir(r, 10, 0);
	// inserir(r, 1, 0);
	// inserir(r, 9, 0);
	// inserir(r, 11, 0);
	
	// inserir(r, 5, 0);
	// inserir(r, 3, 0);
	// inserir(r, 8, 0);
	// inserir(r, 2, 0);
	// inserir(r, 4, 0);
	// inserir(r, 7, 0);
	// inserir(r, 10, 0);
	// inserir(r, 1, 0);
	// inserir(r, 6, 0);
	// inserir(r, 9, 0);
	// inserir(r, 11, 0);
	
	// remover(r, procurar(r, 4));
	// remover(r, procurar(r, 8));
	// remover(r, procurar(r, 6));
	// remover(r, procurar(r, 5));
	// remover(r, procurar(r, 2));
	// remover(r, procurar(r, 1));
	// remover(r, procurar(r, 7));
	// remover(r, procurar(r, 11));
	
	inserir(r, 160.75, -44);
	mostrar_no(r.raiz, procurar(r, 160.75));
	inserir(r, 32.25, -4.5);
	mostrar_no(r.raiz, procurar(r, 32.25));
	//inserir(r, 40.57, -4.5);
	//mostrar_no(r.raiz, procurar(r, 40.57));
	
	cout << "deletar\n";
	remover(r, procurar(r, 160.75));
	
	mostrar_no(r.raiz, procurar(r, 32.25));

	terminar(r);

	//if (procurar(r, 11) == NULL) cout << "mostrar naaaos" << endl;
	//mostrar_no(r.raiz, procurar(r, 11));

	// mostrar_no(r.raiz, procurar(r, 7));
	// mostrar_no(r.raiz, procurar(r, 3));
	// mostrar_no(r.raiz, procurar(r, 10));
	// mostrar_no(r.raiz, procurar(r, 1));
	// mostrar_no(r.raiz, procurar(r, 9));
	// mostrar_no(r.raiz, procurar(r, 11)); 
	//mostrar_no(r.raiz, procurar(r, 7));

	// mostrar_no(r.raiz, procurar(r, 2));
	// remover(r, procurar(r, 2));
	// mostrar_no(r.raiz, procurar(r, 1));

	return 0;
}