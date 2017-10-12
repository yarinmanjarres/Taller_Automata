#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Pila.h"
#include <string>
#include <SDL2/SDL.h>
//#include "SDL/SDL.h"
#define T 11
#define COMODIN $
#define BRIGHT 1
#define GREEN 32
#define BLUE 34
#define BG_BLACK 40

using namespace std;
class Arco;
class Nodo {
	public:
	    char estado;
	int estadoAceptado;
	Nodo *siguiente;
	Arco *adyunto;
	friend class Grafo;
}
;
class Arco {
	public:
    char datoLeer, sacarPila1, apilar1, apilar2;
	Nodo *destino;
	Arco *siguiente;
	friend class Grafo;
}
;
class Grafo {
	Nodo *h;
	public:
    Nodo *crearNodo(char estadoI, int estadoAceptadoI);
	Arco *crearArco(char datoLeerI, char  sacarPila1I,char apilar1I, char apilar2I);
	void insertarNodo(Nodo **cabeza, char estadoI, int estadoAceptadoI);
	Nodo *ultimoNodo(Nodo *cabeza);
	Nodo *buscarNodo(Nodo *cabeza, char estadoI);
	void insertarArco(Nodo **cabeza,char datoLeerI,char  sacarPila1I, char apilar1I,char apilar2I, char y, char z);
	Arco *ultimoArco(Arco *arista);
	Arco *buscaArco(Arco *arista);
}
;
Nodo* Grafo :: crearNodo(char estadoI, int estadoAceptadoI) {
	Nodo *p;
	p = (Nodo*)malloc(sizeof(Nodo));
	if(p != NULL) {
		p -> estado = estadoI;
		p ->estadoAceptado = estadoAceptadoI;
		p -> siguiente = NULL;
		p -> adyunto = NULL;
	} else {
		printf("No se pudo reservar memoria\n");
	}
	return p;
}
Arco* Grafo :: crearArco(char datoLeerI, char  sacarPila1I,char apilar1I, char apilar2I) {
	Arco* p;
	p = (Arco*)malloc(sizeof(Arco));
	if(p != NULL) {
		p ->datoLeer = datoLeerI;
		p ->sacarPila1 = sacarPila1I;
		p ->apilar1 = apilar1I;
		p ->apilar2 = apilar2I;
		p -> siguiente = NULL;
		p -> destino = NULL;
	} else {
		printf("No se pudo reservar memoria\n");
	}
	return p;
}
void  Grafo :: insertarNodo(Nodo **cabeza, char estadoI, int estadoAceptadoI) {
	Nodo *p, *i;
	p = crearNodo(estadoI, estadoAceptadoI);
	if(*cabeza == NULL) {
		*cabeza = p;
	} else {
		i = ultimoNodo(*cabeza);
		i -> siguiente = p;
	}
}
Nodo* Grafo ::  ultimoNodo(Nodo *cabeza) {
	Nodo *u;
	if(cabeza -> siguiente != NULL) {
		u = ultimoNodo(cabeza -> siguiente);
	} else {
		u = cabeza;
	}
	return u;
}
Nodo* Grafo :: buscarNodo(Nodo *cabeza, char estadoI) {
	Nodo *b;
	if(cabeza == NULL) {
		b = NULL;
	} else {
		if(cabeza ->estado == estadoI) {
			b = cabeza;
		} else {
			b = buscarNodo(cabeza -> siguiente, estadoI);
		}
	}
	return b;
}
void  Grafo :: insertarArco(Nodo **cabeza,char datoLeerI,char  sacarPila1I, char apilar1I,char apilar2I, char y, char z) {
	Nodo *a, *b;
	Arco *d, *j;
	a = buscarNodo(*cabeza, y);
	b = buscarNodo(*cabeza, z);
	if(a != NULL && b != NULL) {
		d = crearArco(datoLeerI, sacarPila1I, apilar1I, apilar2I);
		if(a -> adyunto == NULL) {
			a -> adyunto = d;
			d -> destino = b;
		} else {
			j = ultimoArco(a -> adyunto);
			j -> siguiente = d;
			d -> destino = b;
		}
	}
}
Arco* Grafo :: ultimoArco(Arco *arista) {
	Arco *u;
	if(arista -> siguiente != NULL) {
		u = ultimoArco(arista -> siguiente);
	} else {
		u = arista;
	}
	return u;
}
Arco* Grafo :: buscaArco(Arco *arista) {
	Arco *b;
	if(arista != NULL) {
		b= arista;
		buscaArco(arista -> siguiente);
		return b;
	} else {
		return b=NULL;
	}
}

class Automata : public Grafo {
	Grafo grafo;
	char estado;
	public:
            Pila pilaSistema;
	        Pila pilaPalabra;
	void leerPalabra(Nodo *cabeza, string PalabraI);
	void desapilarPalabra(Pila pilaPalabra);
	void desapilarSistema(Pila pilaSistema);
	void apilar(Pila pilaSistema, char apilaI);
	void automta(Arco *arista, Pila pilaPalabra,Pila pilaSistema);
	void validar(Nodo *cabeza, Pila pilaPalabraI);
	void moverAutomata(Nodo *cabeza, Arco *arista, Pila pilaPalabraI);
}
;
void  Automata :: leerPalabra(Nodo *cabeza, string PalabraI) {
	for (int i=0; i<PalabraI.size(); i++) {
		pilaPalabra.entrarDato(PalabraI[i]);
	}
    pilaSistema.entrarDato('#');
	moverAutomata(cabeza, cabeza->adyunto, pilaPalabra);
}
void Automata :: validar(Nodo *cabeza, Pila pilaPalabraI) {
	if(cabeza->estadoAceptado==1) {
		cout<<"*no*";
	}else if (cabeza->estadoAceptado==2) {
		if(pilaPalabraI.cuantosDatos()==0) {
			cout<<"**la palabra es valida**";
		} else {
			cout<<"la palabra esta en nodo de aceptacion pero no es valida";
		}
	}
	return;
}
void Automata :: moverAutomata(Nodo *cabeza, Arco *arista, Pila pilaPalabraI) {
	Nodo *b;
	if(cabeza == NULL) {
		printf("no hay automata");
	} else {
        if(arista!=NULL) {
			if((arista->datoLeer==pilaPalabraI.mostrarTope()||arista->datoLeer=='$') and (arista->sacarPila1==pilaSistema.mostrarTope())) {
				 cout <<"++++++++++";
				if(arista->datoLeer!='$') {
                    pilaPalabraI.sacarDato();
                    cout << "---------";
                    pilaPalabraI.mostrarDatos();
                    if(arista->sacarPila1!='$') {
                        pilaSistema.sacarDato();
                    } if (arista->apilar1!='$') {
                        cout<<"&&&&&&";
                        pilaSistema.entrarDato(arista->apilar1);
                        pilaSistema.mostrarDatos();
                    } if(arista->apilar2!='$') {
                        pilaSistema.entrarDato(arista->apilar2);
                    }
                }else if(arista->datoLeer=='$') {
                        cout << "*********";
                    if(arista->sacarPila1!='$') {
                        pilaSistema.sacarDato();
                    }if (arista->apilar1!='$') {
                        cout << "xxxxxxxx";
                        pilaSistema.entrarDato(arista->apilar1);
                        pilaSistema.mostrarDatos();
                    }if(arista->apilar2!='$') {
                        pilaSistema.entrarDato(arista->apilar2);
                    }
                }
				b = arista->destino;
				cout << b->estado;
				pilaSistema.mostrarDatos();
                moverAutomata(b, b->adyunto, pilaPalabraI);
			}
			else {
			moverAutomata(cabeza, arista->siguiente, pilaPalabraI);
		}
		}if(arista==NULL|| pilaPalabra.cuantosDatos()==0){
			validar(cabeza, pilaPalabraI);
			return;
		}
	}
}

class Mostrare{

SDL_Window* ventana = NULL;
SDL_Surface* superficieventana = NULL;

SDL_Surface* flecha1 = NULL;
SDL_Surface* flecha1r = NULL;
SDL_Surface* flecha2 = NULL;
SDL_Surface* flecha3 = NULL;
SDL_Surface* flecha4 = NULL;
SDL_Surface* flecha5 = NULL;
SDL_Surface* flecha6 = NULL;
SDL_Surface* flecha7 = NULL;
SDL_Surface* flecha8 = NULL;
SDL_Surface* flecha9 = NULL;
SDL_Surface* flecha10 = NULL;
SDL_Surface* flecha7r = NULL;
SDL_Surface* flecha8r = NULL;
SDL_Surface* flecha9r = NULL;
SDL_Surface* flecha10r = NULL;
SDL_Surface* flecha6r = NULL;
SDL_Surface* flecha2r = NULL;
SDL_Surface* flecha3r = NULL;
SDL_Surface* flecha4r = NULL;
SDL_Surface* flecha5r = NULL;
SDL_Surface* flechaarriba2 = NULL;
SDL_Surface* flechaarriba3 = NULL;
SDL_Surface* flechaarriba4 = NULL;
SDL_Surface* flechaarriba5 = NULL;
SDL_Surface* flechaarriba6 = NULL;
SDL_Surface* flechaarriba7 = NULL;
SDL_Surface* flechaarriba8 = NULL;
SDL_Surface* flechaarriba9 = NULL;
SDL_Surface* flechaarriba10 = NULL;

SDL_Surface* a = NULL;
SDL_Surface* b = NULL;
SDL_Surface* c = NULL;
SDL_Surface* d = NULL;
SDL_Surface* e = NULL;
SDL_Surface* f = NULL;
SDL_Surface* g = NULL;
SDL_Surface* h= NULL;


SDL_Surface* i = NULL;
SDL_Surface* j = NULL;
SDL_Surface* k = NULL;
SDL_Surface* l = NULL;
SDL_Surface* m = NULL;
SDL_Surface* n = NULL;
SDL_Surface* o = NULL;
SDL_Surface* p= NULL;
SDL_Surface* q = NULL;
SDL_Surface* r = NULL;
SDL_Surface* s = NULL;
SDL_Surface* t= NULL;
SDL_Surface* u = NULL;
SDL_Surface* v= NULL;
SDL_Surface* w = NULL;
SDL_Surface* x = NULL;
SDL_Surface* y = NULL;
SDL_Surface* z= NULL;
SDL_Surface* aA = NULL;
SDL_Surface* bA = NULL;
SDL_Surface* cA = NULL;
SDL_Surface* dA = NULL;
SDL_Surface* eA = NULL;
SDL_Surface* fA = NULL;
SDL_Surface* gA = NULL;
SDL_Surface* hA= NULL;
SDL_Surface* iA = NULL;
SDL_Surface* jA = NULL;
SDL_Surface* kA = NULL;
SDL_Surface* lA = NULL;
SDL_Surface* mA = NULL;
SDL_Surface* nA = NULL;
SDL_Surface* oA = NULL;
SDL_Surface* pA= NULL;
SDL_Surface* qA = NULL;
SDL_Surface* rA = NULL;
SDL_Surface* sA = NULL;
SDL_Surface* tA= NULL;
SDL_Surface* uA = NULL;
SDL_Surface* vA= NULL;
SDL_Surface* wA = NULL;
SDL_Surface* xA = NULL;
SDL_Surface* yA = NULL;
SDL_Surface* zA= NULL;

 const int pantallaanchura = 800;
 const int pantallaaltura = 600;

public:

bool iniciar(){

    bool valor = true;

	        if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "error de inicio sdl %s\n", SDL_GetError() );
		valor = false;
		}else{
        	ventana = SDL_CreateWindow( "Automata", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, pantallaanchura, pantallaaltura, SDL_WINDOW_SHOWN );
			if( ventana == NULL ){
            		printf( "no se pudo crear la venatana: %s\n", SDL_GetError() );
			valor = false;
			}else{
			superficieventana = SDL_GetWindowSurface( ventana );
			}
	          }
           //  if( (TTF_Init()) < 0 ){
	///	printf( "error de inicio del ttf %s\n", SDL_GetError() );
	///	valor = false;
	//}


	return valor;
    }

bool cargarimagenes(){

	bool valor = true;


	flecha1= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha1.bmp" );
	flecha1r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha1r.bmp" );
	flecha2= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha2.bmp" );
	flecha2r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha2r.bmp" );
	flecha3= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha3.bmp" );
	flecha3r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha3r.bmp" );
	flecha4= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha4.bmp" );
	flecha4r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha4r.bmp" );
	flecha5= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha5.bmp" );
	flecha5r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha5r.bmp" );
	flecha6= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha6.bmp" );
	flecha6r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha6r.bmp" );
	flecha7= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha7.bmp" );
	flecha7r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha7r.bmp" );
	flecha8= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha8.bmp" );
	flecha8r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha8r.bmp" );
	flecha9= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha9.bmp" );
	flecha9r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha9r.bmp" );
	flecha10= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha10.bmp" );
	flecha10r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flecha10r.bmp" );
	flechaarriba2= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flechaarriba2.bmp" );
	flechaarriba3= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flechaarriba3.bmp" );
	flechaarriba4= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flechaarriba4.bmp" );
	flechaarriba5= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flechaarriba5.bmp" );
	flechaarriba6= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flechaarriba6.bmp" );
	flechaarriba7= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flechaarriba7.bmp" );
	flechaarriba8= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flechaarriba8.bmp" );
	flechaarriba9= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flechaarriba9.bmp" );
	flechaarriba10= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/imagenes/flechaarriba10.bmp" );
	a= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/an.bmp" );
	b= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/bn.bmp" );
	c= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/cn.bmp" );
	d= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/dn.bmp" );
	e= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/en.bmp" );
	f= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/fn.bmp" );
	g= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/gn.bmp" );
	h= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/hn.bmp" );
	i= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/in.bmp" );
	j= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/jn.bmp" );
	k= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/kn.bmp" );
	l= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/ln.bmp" );
	m= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/mn.bmp" );
	n= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/nn.bmp" );
	o= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/on.bmp" );
	p= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/pn.bmp" );
	q= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/qn.bmp" );
	r= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/rn.bmp" );
	s= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/sn.bmp" );
	t= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/tn.bmp" );
	u= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/un.bmp" );
	v= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/vn.bmp" );
	w= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/wn.bmp" );
	x= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/xn.bmp" );
	y= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/yn.bmp" );
	z= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/zn.bmp" );


	aA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/a.bmp" );
	bA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/b.bmp" );
	cA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/c.bmp" );
	dA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/d.bmp" );
	eA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/e.bmp" );
	fA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/f.bmp" );
	gA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/g.bmp" );
	hA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/h.bmp" );
	iA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/i.bmp" );
	jA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/j.bmp" );
	kA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/k.bmp" );
	lA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/l.bmp" );
	mA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/m.bmp" );
	nA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/n.bmp" );
	oA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/o.bmp" );
	pA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/p.bmp" );
	qA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/q.bmp" );
	rA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/r.bmp" );
	sA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/s.bmp" );
	tA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/t.bmp" );
	uA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/u.bmp" );
	vA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/v.bmp" );
	wA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/w.bmp" );
	xA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/x.bmp" );
	yA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/y.bmp" );
	zA= SDL_LoadBMP( "/home/diego/Documentos/SEMESTRE_VI/COMPILADORES/Taller/abc/z.bmp" );



	if( flecha2 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( flecha2r == NULL )
	{
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha3 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 3%s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha3r == NULL )
	{
		printf( "no se cargo la imagen FLECHA 3%s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}


	if( flecha4 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 4 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha4r == NULL )
	{
		printf( "no se cargo la imagen FLECHA 4 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha5 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 5 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha5r == NULL )
	{
		printf( "no se cargo la imagen FLECHA 5 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( flecha6 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 6 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha6r == NULL ){
		printf( "no se cargo la imagen FLECHA 6r %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( flechaarriba2 == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flechaarriba3 == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flechaarriba4 == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

        if( a == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( b == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}



	 if( c == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( d == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( e == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( f == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( g == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}


	 if( h == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( i == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( j == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( k == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( l == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( m == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( n == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}


	 if( o == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( p == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( q == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( r == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( s == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( t == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( u == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( v == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( w == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( x == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	 if( y == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( z == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( aA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( bA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}



	 if( cA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( dA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( eA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( fA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( gA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}


	 if( hA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( iA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( jA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( kA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( lA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( mA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( nA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}


	 if( oA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( pA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( qA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( rA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( sA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( tA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	 if( uA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( vA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( wA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( xA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	 if( yA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
 	if( zA == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}



	return valor;
}

int cambioValor(Nodo *estado){
	char nodoNombre= (estado->estado);

	int origen;
	 	switch(nodoNombre){

		case 'a':	origen=1;
				break;
		case 'b':	origen=2;
				break;
		case 'c':	origen=3;
				break;
		case 'd':	origen=4;
				break;
		case 'e':	origen=5;
				break;
		case 'f':	origen=6;
				break;
		case 'g':	origen=7;
				break;
		case 'h':	origen=8;
				break;
		case 'i':	origen=9;
				break;
		case 'j':	origen=10;
				break;
		case 'k':	origen=11;
				break;
		case 'l':	origen=12;
				break;
		case 'm':	origen=13;
				break;
		case 'n':	origen=14;
				break;
		case 'o':	origen=15;
				break;
		case 'p':	origen=16;
				break;
		case 'q':	origen=17;
				break;
		case 'r':	origen=18;
				break;
		case 's':	origen=19;
				break;
		case 't':	origen=20;
				break;
		case 'u':	origen=21;
				break;
		case 'v':	origen=22;
				break;
		case 'w':	origen=23;
				break;
		case 'x':	origen=24;
				break;
		case 'y':	origen=25;
				break;
		case 'z':	origen=26;
				break;
		default:
				origen=0;
				printf("no esta ese nombre de nodo");
				break;

		}



	return origen;
}

void flechaAbajo(int x, int  y, int distancia, Nodo *nodoOrigen){

	SDL_Rect coordenada;
        coordenada.x= x;
	coordenada.y= y;
        Uint32 colorkey;

	//printf("distancia %d\n", distancia);

    	 	switch(distancia){
			case 0:
					//printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');
					SDL_BlitSurface( flecha1, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					//printf("xx %c\n", (nodoOrigen->estado));
					//UpdateWindowSurface( ventana );

					SDL_BlitSurface( flecha1r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
					break;

			case 1:
					//printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');
					SDL_BlitSurface( flecha2, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					//printf("xx %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha2r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );



					break;

			case 2:		//printf("presione enter para mostrar con las relaciones del estado 2 %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');
					SDL_BlitSurface( flecha3, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					//printf("xx %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha3r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );


					break;
			case 3: 	//printf("he hey %c\n", (nodoOrigen->estado));
					SDL_BlitSurface( flecha4, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					//printf("xx %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha4r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;

			case 4:		//printf("presione enter para mostrar con las relaciones del estado %c\n", (nodoOrigen->nombre));
					//while ( getchar() != '\n');
					SDL_BlitSurface( flecha5, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					//printf("xx %c\n", (nodoOrigen->nombre));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha5r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;

			case 5: 	SDL_BlitSurface( flecha6, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha6r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );


					break;
			case 6: 	SDL_BlitSurface( flecha7, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha7r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );


					break;
			case 7: 	SDL_BlitSurface( flecha8, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha8r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );


					break;
			case 8: 	SDL_BlitSurface( flecha9, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha9r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );


					break;

			case 9: 	SDL_BlitSurface( flecha10, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha10r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );


					break;




			default:
				printf("no NO SE PUEDE IMPRIMIR LA FLECHA ABAJO NO ESTA \n");
				break;

		}
			SDL_UpdateWindowSurface( ventana );
     			SDL_Delay(1000);





}

void flechaArriba(int x, int  y, int distancia, Nodo *nodoOrigen){

	SDL_Rect coordenada;
        coordenada.x= x;
	coordenada.y= y;
        Uint32 colorkey;

	//printf("distancia %d\n", distancia);

    	 		switch(distancia){


			case 1:
					//printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');
					SDL_BlitSurface(flechaarriba2 , NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					//printf("xx %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha2r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );



					break;

			case 2:		//printf("presione enter para mostrar con las relaciones del estado 2 %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');
					SDL_BlitSurface(flechaarriba3, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					//printf("xx %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha3r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );


					break;
			case 3: 	//printf("he hey %c\n", (nodoOrigen->nombre));
					SDL_BlitSurface( flechaarriba4, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					//printf("xx %c\n", (nodoOrigen->nombre));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha4r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;

			case 4:		//printf("presione enter para mostrar con las relaciones del estado %c\n", (nodoOrigen->nombre));
					//while ( getchar() != '\n');
					SDL_BlitSurface( flechaarriba5, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					//printf("xx %c\n", (nodoOrigen->nombre));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha5r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;

			case 5: 	SDL_BlitSurface( flechaarriba6, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha6r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;
			case 6: 	SDL_BlitSurface( flechaarriba7, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha7r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;
			case 7: 	SDL_BlitSurface( flechaarriba8, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha8r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;
			case 8: 	SDL_BlitSurface( flechaarriba9, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha9r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;
			case 9: 	SDL_BlitSurface( flechaarriba10, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha10r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;

			default:
				printf("no NO SE PUEDE IMPRIMIR LA FLECHA ABAJO NO ESTA \n");
				break;

		}
			SDL_UpdateWindowSurface( ventana );
     			SDL_Delay(1000);



}

void pintarRelacion(Nodo *origen, Arco *regla, Nodo *destino, int x){


	Nodo *nodoOrigen= origen;
	Nodo *nodoDestino= destino;
	//printf("%c-----destino\n", (nodoDestino->estado));

	int origen1 = cambioValor(nodoOrigen);
	int destino1 = cambioValor(nodoDestino);
	int distancia, y;


	//printf("origen %d-----",origen1 );
	//printf("destino %d--------",destino1 );

	printf("Relación de %c y %c\n", (nodoOrigen->estado),(nodoDestino->estado));
	printf("REGLA [%c]/ [%c]/ [%c,%c]\n",(regla-> datoLeer),(regla->sacarPila1 ), (regla->apilar1),(regla->apilar2));

 if(origen1 < destino1 or origen1 == destino1){
		 distancia= (destino1 - origen1);

		origen1--;

		 y = (origen1*83);
		//printf("distancia %d--------",distancia);

		flechaAbajo(x,y,distancia, nodoOrigen);


	}else{

		if(origen > destino){
		distancia= (origen1 - destino1);
		destino1--;
		y = (destino1*83);
		//printf("FLECHA ARRIBA ");
		flechaArriba(x,y,distancia, nodoOrigen);


		}
	}



}

void cerrar(){

	SDL_FreeSurface(flecha1);
	flecha1 = NULL;

	SDL_FreeSurface(flecha1r);
	flecha1r= NULL;

	SDL_FreeSurface(flecha2);
	flecha2 = NULL;

	SDL_FreeSurface(flecha2r);
	flecha2r= NULL;


	SDL_FreeSurface(flecha3);
	flecha3 = NULL;

	SDL_FreeSurface(flecha3r);
	flecha3r= NULL;

	SDL_FreeSurface(flecha4);
	flecha4 = NULL;

	SDL_FreeSurface(flecha5r);
	flecha5r= NULL;


	SDL_FreeSurface(flecha6);
	flecha6 = NULL;

	SDL_FreeSurface(flecha6r);
	flecha6r= NULL;

	SDL_FreeSurface(a);
	a = NULL;

	SDL_FreeSurface(aA);
	aA = NULL;

	SDL_FreeSurface(b);
	b = NULL;

	SDL_FreeSurface(bA);
	bA = NULL;

	SDL_FreeSurface(cA);
	cA = NULL;

	SDL_FreeSurface(c);
	c = NULL;

	SDL_FreeSurface(d);
	d = NULL;

	SDL_FreeSurface(dA);
	dA = NULL;

	SDL_FreeSurface(e);
	e = NULL;

	SDL_FreeSurface(eA);
	eA = NULL;

	SDL_FreeSurface(f);
	f = NULL;

	SDL_FreeSurface(fA);
	fA = NULL;

	SDL_FreeSurface(gA);
	gA = NULL;

	SDL_FreeSurface(g);
	g = NULL;

	SDL_FreeSurface(h);
	h = NULL;

	SDL_FreeSurface(hA);
	hA = NULL;

	SDL_FreeSurface(iA);
	iA = NULL;

	SDL_FreeSurface(i);
	i = NULL;

	SDL_FreeSurface(j);
	j = NULL;

	SDL_FreeSurface(jA);
	jA = NULL;

	SDL_FreeSurface(k);
	k = NULL;

	SDL_FreeSurface(kA);
	kA = NULL;

	SDL_FreeSurface(l);
	l = NULL;

	SDL_FreeSurface(lA);
	lA = NULL;

	SDL_FreeSurface(mA);
	mA = NULL;

	SDL_FreeSurface(m);
	m = NULL;

	SDL_FreeSurface(n);
	n = NULL;

	SDL_FreeSurface(nA);
	nA = NULL;

	SDL_FreeSurface(o);
	o = NULL;

	SDL_FreeSurface(oA);
	oA = NULL;

	SDL_FreeSurface(p);
	p = NULL;

	SDL_FreeSurface(pA);
	pA = NULL;

	SDL_FreeSurface(q);
	q = NULL;

	SDL_FreeSurface(qA);
	qA = NULL;

	SDL_FreeSurface(rA);
	rA = NULL;

	SDL_FreeSurface(r);
	r = NULL;

	SDL_FreeSurface(s);
	s = NULL;

	SDL_FreeSurface(sA);
	sA = NULL;

	SDL_FreeSurface(tA);
	tA = NULL;

	SDL_FreeSurface(t);
	t = NULL;

	SDL_FreeSurface(uA);
	uA = NULL;

	SDL_FreeSurface(vA);
	vA = NULL;

	SDL_FreeSurface(v);
	v = NULL;

	SDL_FreeSurface(w);
	w = NULL;

	SDL_FreeSurface(wA);
	wA = NULL;

	SDL_FreeSurface(xA);
	xA = NULL;

	SDL_FreeSurface(x);
	x = NULL;

	SDL_FreeSurface(y);
	y = NULL;

	SDL_FreeSurface(yA);
	yA = NULL;

	SDL_FreeSurface(z);
	z = NULL;

	SDL_FreeSurface(zA);
	zA = NULL;



	//TTF_Quit();
	SDL_Quit();
}

void pintarEstados(Nodo *esta, int xc, int yc){


	int valor =(esta->estadoAceptado);
	SDL_Rect coordenada;
        coordenada.x= xc;
	coordenada.y= yc;
	//printf("%d ", (esta->estadoAceptado));

	switch(esta->estado){

		case 'a':
				if(valor == 1 ){
				SDL_BlitSurface( a, NULL, superficieventana, &coordenada ); }
				else{
				       if(valor == 2 ){
					SDL_BlitSurface( aA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'b':
				if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( b, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( bA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'c':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( c, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( cA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'd':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( d, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( dA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'e':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( e, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( eA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'f':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( f, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( fA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'g':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( g, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( gA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'h':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( h, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( hA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'i':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( i, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( iA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'j':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( j, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( jA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'k':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( k, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( kA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'l':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( l, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( lA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'm':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( m, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( mA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'n':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( n, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( nA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'o':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( o, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( oA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'p':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( p, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( pA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'q':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( q, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( qA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'r':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( r, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( rA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 's':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( s, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( sA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 't':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( t, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( tA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'u':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( u, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( uA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'v':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( v, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( vA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'w':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( w, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( wA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'x':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( x, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( xA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'y':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( y, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( yA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'z':	if((esta->estadoAceptado) == 1 ){
				SDL_BlitSurface( z, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 2 ){
					SDL_BlitSurface( zA, NULL, superficieventana, &coordenada ); }
					}
				break;
		default:

				printf("no esta ese nombre de nodo");
				break;

		}


     SDL_UpdateWindowSurface( ventana );
     SDL_Delay(500);

}

void mostrar(Nodo *cabeza){
	//TTF_Font *arial;
	Nodo *a;
	Arco *p;
	int x=0;
	int y=0;

    //arial = TTF_OpenFont("SIXTY.ttf", 28);
	if(cabeza == NULL){
		printf("[ NULL no hay automata ]\n");
	}else{
		a= cabeza;
		if( !iniciar() ){
		printf( "error inicio\n" );
		}
		else{
			if( !cargarimagenes() ){
				printf( "error de cargo de imagenes\n" );
			}else{

				while (a != NULL){
					 pintarEstados(a,x,y);
					 printf("\n");
					 y=y+83;

					 a= a-> siguiente;

					}

				     if(a==NULL){
					//printf("ahora vienien las relaciones\n");
					//SDL_Delay(1000);
					//cerrar();
					}



					a= cabeza;
					x=90;
					y=0;

					while (a != NULL){

				   		if((a->adyunto) != NULL){

						p = a-> adyunto;


						pintarRelacion(a,p,(p->destino), x);


				        	while(p->siguiente != NULL){
							 p = p->siguiente;

					      		 pintarRelacion(a, p, (p->destino), x);
							}

						  if(p->siguiente == NULL){
						  printf("end  %c\n",a->estado);
							}


						 }
					 a= a-> siguiente;
					}
				     if(a==NULL){
					printf("YA SE ACABO");
					SDL_Delay(600);
					cerrar();
					}

}// tercer else
}//segundo else


}//primer else

}//mostrare

};
//

int main() {
	Nodo *lista = NULL;
	Grafo grafo;
	Pila pila;
	Automata automata;
	Mostrare resultado;
	char estadoI, datoLeerI, sacarPila1I, apilar1I, apilar2I, estadoPartida, estadoLlegada;
	int num, estadoAceptadoI;
	string palabraI;
	int salirMenu = 0;
	while(salirMenu == 0) {
		printf("%c[%d;%d;%dm", 0x1B, BRIGHT,BLUE,BG_BLACK);
		cout<<"\n\n";
		cout<<"\t\t\tВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВ\n";
		cout<<"\t\t\tВ       AUTOMATA DE PILA         В\n";
		cout<<"\t\t\tВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВ\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 1  ->  Ingresar estado         В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 2  ->  Ingresar regla          В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 3  ->  Mostrar automata        В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 4  ->  validar palabra         В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВ 5  ->  Salir                   В\n";
		cout<<"\t\t\tВ                                В\n";
		cout<<"\t\t\tВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВ\n";
		cout<<"\t\t\tВ      Elija una opcion...       В\n";
		cout<<"\t\t\tВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВВ\n";
		cin>>num;
		switch(num) {
			case 1:
			        cout<<"Ingrese un Estado(si es de aceptacion 2/1): \n";
			cin>>estadoI>>estadoAceptadoI;
			grafo.insertarNodo(&lista,estadoI, estadoAceptadoI);
			break;
			case 2:
			          cout<<"Ingrese una regla: Dato a leer, dato desapilar, Primer dato a apilar, segundo datooa apilar, estado de partida, estado de llegada: \n";
			cin>>datoLeerI >> sacarPila1I >> apilar1I>> apilar2I>> estadoPartida >> estadoLlegada;
			grafo.insertarArco(&lista, datoLeerI, sacarPila1I, apilar1I, apilar2I, estadoPartida, estadoLlegada);
			break;
			case 3:
                    resultado.mostrar(lista);
			         // grafo.mostrar(lista);
			break;
			case 4:
            cout << " Ingrese palabra: ";
			cin>> palabraI;
			automata.leerPalabra(lista,palabraI);
			break;
			case 5:
			          salirMenu=1;
			break;
			default:
			      printf( "Tienes que selecionar una opcion correcta.\n" );
		}
	}
}
