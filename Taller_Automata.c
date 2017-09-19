#include <stdlib.h>
#include <stdio.h>

typedef struct stArco *adyunto;

typedef struct stNodo{
	char nombre;
	stNodo *siguiente;
	stArco *adyunto;
}nodo;

typedef struct stArco{
	int peso;
	stNodo *destino;
	stArco *siguiente;
}arco;

nodo *crearNodo(char x){
	nodo *p;

	p = (nodo*)malloc(sizeof(nodo));
	if(p != NULL){
		p -> nombre = x;
		p -> siguiente = NULL;
		p -> adyunto = NULL;
	}else{
		printf("No se pudo reservar memoria\n");
	}

	return p;
}

arco *crearArco(int x){
	arco* p;

	p = (arco*)malloc(sizeof(arco));
	if(p != NULL){
		p -> peso = x;
		p -> siguiente = NULL;
		p -> destino = NULL;
	}else{
		printf("No se pudo reservar memoria\n");
	}

	return p;
}

nodo *ultimoNodo(nodo *cabeza){
	nodo *u;

	if(cabeza -> siguiente != NULL){
		u = ultimoNodo(cabeza -> siguiente);
	}else{
		u = cabeza;
	}

	return u;
}

void insertarNodo(nodo **cabeza, char x){
	nodo *p, *i;

	p = crearNodo(x);
	if(*cabeza == NULL){
		*cabeza = p;
	}else{
		i = ultimoNodo(*cabeza);
		i -> siguiente = p;
	}
}

nodo *buscarNodo(nodo *cabeza, char x){
	nodo *b;

	if(cabeza == NULL){
		b = NULL;
	}else{
		if(cabeza -> nombre == x){
			b = cabeza;
		}else{
			b = buscarNodo(cabeza -> siguiente, x);
		}

	}
	return b;
}

arco *ultimoArco(arco *arista){
	arco *u;

	if(arista -> siguiente != NULL){
		u = ultimoArco(arista -> siguiente);
	}else{
		u = arista;
	}

	return u;
}

void insertarArco(nodo **cabeza, int x, char y, char z){
	nodo *a, *b;
	arco *d, *j;

	a = buscarNodo(*cabeza, y);
	b = buscarNodo(*cabeza, z);
	if(a != NULL && b != NULL){
		d = crearArco(x);
		if(a -> adyunto == NULL){
			a -> adyunto = d;
			d -> destino = b;
		}else{
			j = ultimoArco(a -> adyunto);
			j -> siguiente = d;
			d -> destino = b;
		}
	}
}

void mostrarArco(arco *arista){

	if(arista == NULL){
		return;
	}else{
		printf("[ %d ]-> ", arista -> peso);
		mostrarArco(arista -> siguiente);
	}
}

void mostrar(nodo *cabeza){

	if(cabeza == NULL){
		printf("[ NULL ]\n");
	}else{
		printf("[ %c ]-> ",cabeza -> nombre);
		mostrarArco(cabeza -> adyunto);
		printf("\n");
		mostrar(cabeza -> siguiente);
	}
}

arco *buscarArco(arco *arista, int p){
	arco *b;

	if(arista != NULL){
		if(p == arista -> peso){
			b = arista;
		}else{
			b = buscarArco(arista -> siguiente, p);
		}
	}else{
		b = NULL;
	}

	return b;
}

arco *anteriorArco(arco *arista, arco *e){
	arco *a;

	if(e != NULL){
		if(arista != NULL){
			if(arista -> siguiente == e){
				a = arista;
			}else{
				a = anteriorArco(arista -> siguiente, e);
			}
		}else{
			a = NULL;
		}
	}else{
		a = NULL;
	}

	return a;
}


bool existeArista(arco *arista, nodo *b){
	bool e;

	if(arista == NULL || b == NULL){
		e = false;
	}else{
		if(arista -> destino == b){
			e = true;
		}else{
			e = existeArista(arista -> siguiente, b);
		}
	}

	return e;
}

bool existeCamino(arco *arista, nodo *b){
	bool e;

	if(arista == NULL || b == NULL){
		e = false;
	}else{
		if(arista -> destino != NULL){
			if(arista -> destino == b){
				e = true;
			}else{
				e = existeCamino((arista -> destino) -> adyunto, b);
			}
		}else{
			e = false;
		}
	}

	return e;
}

nodo* nodoCamino(arco *arista, nodo *b){
	nodo *n, j;

	if(arista == NULL || b == NULL){
		n = NULL;
	}else{
		if(existeCamino(arista, b)){
			n = arista -> destino;
		}else{
			n = nodoCamino(arista -> siguiente, b);
		}
	}

	return n;
}

void mostrarCaminoXY(nodo *a, nodo *b, arco *arista){

	if(a == NULL || arista == NULL){
		return;
	}else{
		if(existeCamino(arista, b)){
			printf("- > [ %c ]", (arista -> destino) -> nombre);
			mostrarCaminoXY(nodoCamino(arista, b), b, nodoCamino(arista, b) -> adyunto);
		}
	}
}

void mostrarCaminos(nodo *a, nodo *b, arco *arista){
	bool e;

	if(a == NULL || b == NULL || arista == NULL){
		return;
	}else{
		if(existeCamino(arista, b)){
			printf("[ %c ] ", a -> nombre);
			mostrarCaminoXY(a, b, arista);
			printf("\n");
			mostrarCaminos(a, b, arista -> siguiente);
		}else{
			mostrarCaminos(a, b, arista -> siguiente);
		}
	}
}

void mostrarCamino(nodo *a, nodo *b, arco *arista){

	if(a == NULL || b == NULL){
		return;
	}else{
		printf("[ %c ]", a -> nombre);
		mostrarCaminoXY(a, b, arista);
	}
}

int main(){
	nodo *lista = NULL;
	nodo *a, *b;
	int x;
	bool e;

	insertarNodo(&lista, 'a');
	insertarNodo(&lista, 'b');
	insertarNodo(&lista, 'c');
	insertarNodo(&lista, 'd');
	insertarNodo(&lista, 'e');
	insertarNodo(&lista, 'f');

	insertarArco(&lista, 5, 'a', 'b');
	insertarArco(&lista, 2, 'a', 'd');
	insertarArco(&lista, 1, 'b', 'c');
	insertarArco(&lista, 22, 'c', 'e');
	insertarArco(&lista, 4, 'd', 'e');
	insertarArco(&lista, 21, 'f', 'e');

	mostrar(lista);

	a = buscarNodo(lista, 'a');
	b = buscarNodo(lista, 'e');


	system("pause");
	return 0;
}
