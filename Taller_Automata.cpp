#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Pila.h"
#include <string>
#include <SDL2/SDL.h>
#include "SDL/SDL.h"
#include <string>

#define T 11
#define COMODIN $

#define BRIGHT 1
#define GREEN 32
#define BLUE 34
#define BG_BLACK 40

using namespace std;



class Arco;

class Nodo{


public:

    char estado;
    int estadoAceptado;
	Nodo *siguiente;
	Arco *adyunto;

	friend class Grafo;
	friend class Mostrare;

};


class Arco{
    public:
	char datoLeer, topePila, sacarPila1, sacarPila2, apilar1, apilar2;
	Nodo *destino;
	Arco *siguiente;

	friend class Grafo;
	friend class Mostrare;
};

class Grafo{
    Nodo *h;


    public:

Nodo *crearNodo(char estadoI, int estadoAceptadoI){
        Nodo *p;

        p = (Nodo*)malloc(sizeof(Nodo));
        if(p != NULL){
            p -> estado = estadoI;
            p ->estadoAceptado = estadoAceptadoI;
            p -> siguiente = NULL;
            p -> adyunto = NULL;
        }else{
            printf("No se pudo reservar memoria\n");
        }

        return p;
    }

Arco *crearArco(char datoLeerI, char topePilaI, char  sacarPila1I, char sacarPila2I, char apilar1I,char apilar2I){

        Arco* p;

        p = (Arco*)malloc(sizeof(Arco));
        if(p != NULL){
            p ->datoLeer = datoLeerI;
            p ->topePila = topePilaI;
            p ->sacarPila1 = sacarPila1I;
            p ->sacarPila2 = sacarPila1I;
            p ->sacarPila2 = sacarPila2I;
            p ->apilar1 = apilar1I;
            p ->apilar2 = apilar2I;
            p -> siguiente = NULL;
            p -> destino = NULL;
        }else{
            printf("No se pudo reservar memoria\n");
        }

        return p;
    }

void insertarNodo(Nodo **cabeza, char estadoI, bool estadoAceptadoI){
        Nodo *p, *i;

        p = crearNodo(estadoI, estadoAceptadoI);
        if(*cabeza == NULL){
            *cabeza = p;
        }else{
            i = ultimoNodo(*cabeza);
            i -> siguiente = p;
        }
    }

Nodo *ultimoNodo(Nodo *cabeza){
        Nodo *u;

        if(cabeza -> siguiente != NULL){
            u = ultimoNodo(cabeza -> siguiente);
        }else{
            u = cabeza;
        }

        return u;
    }

Nodo *buscarNodo(Nodo *cabeza, char estadoI){
	Nodo *b;

	if(cabeza == NULL){
		b = NULL;
	}else{
		if(cabeza ->estado == estadoI){
			b = cabeza;
		}else{
			b = buscarNodo(cabeza -> siguiente, estadoI);
		}

	}
	return b;
}


void insertarArco(Nodo **cabeza,char datoLeerI, char topePilaI,char  sacarPila1I, char sacarPila2I, char apilar1I,char apilar2I, char y, char z){
	Nodo *a, *b;
	Arco *d, *j;

	a = buscarNodo(*cabeza, y);
	b = buscarNodo(*cabeza, z);
	if(a != NULL && b != NULL){
		d = crearArco(datoLeerI, topePilaI, sacarPila1I, sacarPila2I, apilar1I, apilar2I);
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

Arco *ultimoArco(Arco *arista){
	Arco *u;

	if(arista -> siguiente != NULL){
		u = ultimoArco(arista -> siguiente);
	}else{
		u = arista;
	}

	return u;
}

void mostrarArco(Arco *arista){

	if(arista == NULL){
		return;
	}else{
		printf("[ %c, %c, %c,%c,%c,%c ]-> ", arista ->datoLeer, arista->topePila, arista->sacarPila1, arista->sacarPila2, arista->apilar1, arista->apilar2 );
		mostrarArco(arista -> siguiente);
	}
}


Arco *BuscaArco(Arco *arista){
    Arco *b;

	if(arista != NULL){
		b= arista;
		mostrarArco(arista -> siguiente);
		return b;
	}else{
		return b=NULL;
	}
}

void mostrar(Nodo *cabeza){

	if(cabeza == NULL){
		printf("[ NULL ]\n");
	}else{
		printf("[ %c ]->",cabeza ->estado);
		mostrarArco(cabeza -> adyunto);
		printf("\n");
		mostrar(cabeza -> siguiente);
	}
}

Arco *buscarArco(Arco *arista, char datoLeerI, char topePilaI, char  sacarPila1I, char sacarPila2I, char apilar1I,char apilar2I){
	Arco *b;

	if(arista != NULL){
		if((datoLeerI == arista ->datoLeer) && (topePilaI == arista->topePila)  && (sacarPila1I == arista->sacarPila1) && (sacarPila2I == arista->sacarPila2)){
			b = arista;
		}else{
			b = buscarArco(arista -> siguiente, datoLeerI, topePilaI, sacarPila2I, sacarPila2I, apilar1I, apilar2I);
		}
	}else{
		b = NULL;
	}

	return b;
}

Arco *anteriorArco(Arco *arista, Arco *e){
	Arco *a;

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

bool existeArista(Arco *arista, Nodo *b){
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

};


class Automata : public Grafo{
    Pila pilaPalabra;
    Pila pilaSistema;
    Grafo grafo;
    char estado;


    public:

    void leerPalabra(Nodo *cabeza, string PalabraI){
        for(int i=0; i<PalabraI.size(); i++){
        	pilaPalabra.Apilar(PalabraI[i]);
        }

          pilaPalabra.VerPila();
    }
    void desapilarPalabra(Pila pilaPalabra){
        pilaPalabra.Desapilar();
    }
    void desapilarSistema(Pila pilaSistema){
        pilaSistema.Desapilar();
    }
    void apilar(Pila pilaSistema, char apilaI){
        pilaSistema.Apilar(apilaI);
    }
    void automta(Arco *arista, Pila pilaPalabra,Pila pilaSistema){

        if(arista->datoLeer=='$'){
                if(arista->sacarPila1!='$'){
                    desapilarSistema(pilaSistema);
                }else if(arista->sacarPila2!='$'){
                    desapilarSistema(pilaSistema);
                }else if (arista->apilar1!='$'){
                    apilar(pilaSistema,(arista->apilar1));
                }else if(arista->apilar2!='$'){
                    apilar(pilaSistema,(arista->apilar2));
                }
        }
        else(arista->datoLeer!='$');{
                desapilarPalabra(pilaPalabra);
                if(arista->sacarPila1!='$'){
                    desapilarSistema(pilaSistema);
                }else if(arista->sacarPila2!='$'){
                    desapilarSistema(pilaSistema);
                }else if (arista->apilar1!='$'){
                    apilar(pilaSistema,(arista->apilar1));
                }else if(arista->apilar2!='$'){
                    apilar(pilaSistema,(arista->apilar2));
                }
        }
        return;

    }
    void validar(Nodo *cabeza){
        if (cabeza->estadoAceptado==1){
            cout<<"la palabra es valida";
        }else{
            cout<<"palabra erronea";
        }
    }

void moverAutomata(Nodo *cabeza, Pila pilaPalabraI){
    Arco *b;
    Pila pilaSistema;
	if(cabeza == NULL){
		printf("[ NULL ]\n");
	}else{
		b=grafo.BuscaArco(cabeza->adyunto);
		if(b==NULL){
            validar(cabeza);
        }else if(b!=NULL){
            if((b->datoLeer==pilaPalabraI.getCima()) && (b->topePila==pilaSistema.getCima())){
                estado= cabeza->estado;
                automta(b, pilaPalabraI, pilaSistema);
                moverAutomata(b ->destino, pilaPalabraI);
            }

        }else {
        validar(cabeza);
    }

	}

}


};


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

	
	flecha1= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha1.bmp" );
	flecha1r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha1r.bmp" );
	flecha2= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha2.bmp" );
	flecha2r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha2r.bmp" );
	flecha3= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha3.bmp" );
	flecha3r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha3r.bmp" );
	flecha4= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha4.bmp" );
	flecha4r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha4r.bmp" );
	flecha5= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha5.bmp" );
	flecha5r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha5r.bmp" );
	flecha6= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha6.bmp" );
	flecha6r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha6r.bmp" );
	flecha7= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha7.bmp" );
	flecha7r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha7r.bmp" );
	flecha8= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha8.bmp" );
	flecha8r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha8r.bmp" );
	flecha9= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha9.bmp" );
	flecha9r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha9r.bmp" );
	flecha10= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha10.bmp" );
	flecha10r= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flecha10r.bmp" );
	flechaarriba2= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba2.bmp" );
	flechaarriba3= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba3.bmp" );
	flechaarriba4= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba4.bmp" );
	flechaarriba5= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba5.bmp" );
	flechaarriba6= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba6.bmp" );
	flechaarriba7= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba7.bmp" );
	flechaarriba8= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba8.bmp" );
	flechaarriba9= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba9.bmp" );
	flechaarriba10= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba10.bmp" );
	a= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/an.bmp" );
	b= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/bn.bmp" );
	c= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/cn.bmp" );
	d= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/dn.bmp" );
	e= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/en.bmp" );
	f= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/fn.bmp" );
	g= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/gn.bmp" );
	h= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/hn.bmp" );
	i= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/in.bmp" );
	j= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/jn.bmp" );
	k= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/kn.bmp" );
	l= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/ln.bmp" );
	m= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/mn.bmp" );
	n= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/nn.bmp" );
	o= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/on.bmp" );
	p= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/pn.bmp" );
	q= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/qn.bmp" );
	r= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/rn.bmp" );
	s= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/sn.bmp" );
	t= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/tn.bmp" );
	u= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/un.bmp" );
	v= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/vn.bmp" );
	w= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/wn.bmp" );
	x= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/xn.bmp" );
	y= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/yn.bmp" );
	z= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/zn.bmp" );
	

	aA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/a.bmp" );
	bA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/b.bmp" );
	cA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/c.bmp" );
	dA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/d.bmp" );
	eA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/e.bmp" );
	fA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/f.bmp" );
	gA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/g.bmp" );
	hA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/h.bmp" );
	iA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/i.bmp" );
	jA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/j.bmp" );
	kA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/k.bmp" );
	lA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/l.bmp" );
	mA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/m.bmp" );
	nA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/n.bmp" );
	oA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/o.bmp" );
	pA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/p.bmp" );
	qA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/q.bmp" );
	rA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/r.bmp" );
	sA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/s.bmp" );
	tA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/t.bmp" );
	uA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/u.bmp" );
	vA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/v.bmp" );
	wA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/w.bmp" );
	xA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/x.bmp" );
	yA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/y.bmp" );
	zA= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/z.bmp" );
	


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
					printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');
					SDL_BlitSurface( flecha1, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					printf("xx %c\n", (nodoOrigen->estado));
					//UpdateWindowSurface( ventana );
					
					SDL_BlitSurface( flecha1r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
					break;

			case 1:
					printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->estado));
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
					printf("xx %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha3r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );


					break;
			case 3: 	printf("he hey %c\n", (nodoOrigen->estado));
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
					printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');
					SDL_BlitSurface(flechaarriba2 , NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					//printf("xx %c\n", (nodoOrigen->estado));
					//while ( getchar() != '\n');

					SDL_BlitSurface( flecha2r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );



					break;

			case 2:		printf("presione enter para mostrar con las relaciones del estado 2 %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');
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

	printf("Relación de %c y %c", (nodoOrigen->estado),(nodoDestino->estado));
	printf("REGLA dato a leer [%c]/ dato a sacar de la pila [%c]/estado de la pila [%c,%c]",(regla-> datoLeer),(regla-> topePila), (regla->apilar1),(regla->apilar2));

 if(origen1 < destino1 or origen1 == destino1){
		 distancia= (destino1 - origen1);
              
		origen1--;
		
		 y = (origen1*83);  
		printf("distancia %d--------",distancia);
		
		flechaAbajo(x,y,distancia, nodoOrigen);
		
	
	}else{

		if(origen > destino){
		distancia= (origen1 - destino1);
		destino1--;
		y = (destino1*83);
		printf("FLECHA ARRIBA ");
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
	printf("%d ", (esta->estadoAceptado));

	switch(esta->estado){

		case 'a':	
				if(valor == 0 ){
				SDL_BlitSurface( a, NULL, superficieventana, &coordenada ); }
				else{
				       if(valor == 1 ){
					SDL_BlitSurface( aA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'b':	
				if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( b, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( bA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'c':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( c, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( cA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'd':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( d, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( dA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'e':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( e, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( eA, NULL, superficieventana, &coordenada ); }
					} 
				break;
		case 'f':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( f, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( fA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'g':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( g, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( gA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'h':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( h, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( hA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'i':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( i, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( iA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'j':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( j, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( jA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'k':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( k, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( kA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'l':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( l, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( lA, NULL, superficieventana, &coordenada ); }
					} 
				break;
		case 'm':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( m, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( mA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'n':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( n, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( nA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'o':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( o, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( oA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'p':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( p, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( pA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'q':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( q, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( qA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'r':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( r, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( rA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 's':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( s, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( sA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 't':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( t, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( tA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'u':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( u, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( uA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'v':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( v, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( vA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'w':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( w, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( wA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'x':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( x, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( xA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'y':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( y, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
					SDL_BlitSurface( yA, NULL, superficieventana, &coordenada ); }
					}
				break;
		case 'z':	if((esta->estadoAceptado) == 0 ){
				SDL_BlitSurface( z, NULL, superficieventana, &coordenada ); }
				else{
				       if((esta->estadoAceptado) == 1 ){
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
					printf("ahora vienien las relaciones\n");
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
						  printf("no tiene mas relaciones el estado %c\n",a->estado);
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
































int main(){
    Nodo *lista = NULL;
	Grafo grafo;
	Pila pila;
	Automata automata;
	char estadoI,  datoLeerI, topePilaI, sacarPila1I, sacarPila2I, apilar1I, apilar2I, estadoPartida, estadoLlegada;
	int estadoAceptadoI;
	int num;
	string palabraI;
	Mostrare resultado;

    int salirMenu = 0;
while(salirMenu == 0){
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
switch(num)
{
      case 1:
        printf("ingrese estado\n");
	scanf("%s",&estadoI);
	
	printf("ingrese valoraceptado\n");
	scanf("%d",&estadoAceptadoI);
       // cin>>estadoI>>estadoAceptadoI;
        grafo.insertarNodo(&lista,estadoI, estadoAceptadoI);
      break;
      case 2:
         // cout<<"Ingrese una regla: Dato a leer, dato en pila, dato desapilar, estado de partida, estado de llegada: \n";
          //cin>>datoLeerI >> topePilaI >> sacarPila1I >> sacarPila2I>> apilar1I>> apilar2I>> estadoPartida >> estadoLlegada;
	
	  printf("dato a leer,");
	  scanf("%s",&datoLeerI);
	
	  printf("dato en pila,\n");
	  scanf("%s",&topePilaI);
	
	  printf("el dato a sacar de la pila 1,");
	  scanf("%s",&sacarPila1I);
	
	  //printf("dato a desapilar");
	  scanf("%s",&sacarPila2I);
	
	   printf("dato a apilar 1,");
	  scanf("%s",&apilar1I);
	
	    printf("dato a apilar 2,");
	  scanf("%s",&apilar2I);	

	  printf("estado de partida ,");
	  scanf("%s",&estadoPartida);

	  printf("y estado de llegada,");
	  scanf("%s",&estadoLlegada);

          grafo.insertarArco(&lista, datoLeerI, topePilaI, sacarPila1I, sacarPila2I, apilar1I, apilar2I, estadoPartida, estadoLlegada);

      break;
      case 3:
	  resultado.mostrar(lista); 
          //grafo.mostrar(lista);
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
	break;
}
}
} 


