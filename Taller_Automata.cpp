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

SDL_Surface* nodoaceptado = NULL;
SDL_Surface* no = NULL;
SDL_Surface* flecha2 = NULL;
SDL_Surface* flecha3 = NULL;
SDL_Surface* flecha4 = NULL;
SDL_Surface* flecha5 = NULL;
SDL_Surface* flecha6 = NULL;
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

SDL_Surface* a = NULL;
SDL_Surface* b = NULL;
SDL_Surface* c = NULL;
SDL_Surface* d = NULL;
SDL_Surface* e = NULL;
SDL_Surface* f = NULL;
SDL_Surface* g = NULL;
SDL_Surface* h= NULL;

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
	flechaarriba2= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba2.bmp" );
	flechaarriba3= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba3.bmp" );
	flechaarriba4= SDL_LoadBMP( "/home/yarin/Documentos/ta/imagenes/flechaarriba4.bmp" );
	a= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/a.bmp" );
	b= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/b.bmp" );
	c= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/c.bmp" );
	d= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/d.bmp" );
	e= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/e.bmp" );
	f= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/f.bmp" );
	


	if( flecha2 == NULL ){
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha2r == NULL ){
		printf( "no se cargo la imagen FLECHA 2r %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha3 == NULL ){
		printf( "no se cargo la imagen FLECHA 3%s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	
	if( flecha3r == NULL ){
		printf( "no se cargo la imagen FLECHA 3r%s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( flecha4 == NULL ){
		printf( "no se cargo la imagen FLECHA 4 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha4r == NULL ){
		printf( "no se cargo la imagen FLECHA 4r %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( flecha5 == NULL ){
		printf( "no se cargo la imagen FLECHA 5 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	if( flecha5r == NULL ){
		printf( "no se cargo la imagen FLECHA 5r %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}

	if( flecha6 == NULL ){
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

			case 1:
					printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');
					SDL_BlitSurface( flecha2, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					printf("xx %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');

					SDL_BlitSurface( flecha2r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );



					break;

			case 2:		printf("presione enter para mostrar con las relaciones del estado 2 %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');
					SDL_BlitSurface( flecha3, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					printf("xx %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');

					SDL_BlitSurface( flecha3r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );


					break;
			case 3: 	printf("he hey %c\n", (nodoOrigen->estado));
					SDL_BlitSurface( flecha4, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					printf("xx %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');

					SDL_BlitSurface( flecha4r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;

			case 4:		//printf("presione enter para mostrar con las relaciones del estado %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');
					SDL_BlitSurface( flecha5, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					//printf("xx %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');

					SDL_BlitSurface( flecha5r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;

			case 5: 	SDL_BlitSurface( flecha6, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);


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
			case 0:		
					printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');
					SDL_BlitSurface( flecha1, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					printf("xx %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');
					
					SDL_BlitSurface( flecha1r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
					break;

			case 1:
					printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');
					SDL_BlitSurface(flechaarriba2 , NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					printf("xx %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');

					SDL_BlitSurface( flecha2r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );



					break;

			case 2:		printf("presione enter para mostrar con las relaciones del estado 2 %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');
					SDL_BlitSurface(flechaarriba3, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					printf("xx %c\n", (nodoOrigen->estado));
					while ( getchar() != '\n');

					SDL_BlitSurface( flecha3r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					/*
					break;
			case 3: 	printf("he hey %c\n", (nodoOrigen->nombre));
					SDL_BlitSurface( flechaarriba, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					printf("xx %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');

					SDL_BlitSurface( flecha4r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;

			case 4:		//printf("presione enter para mostrar con las relaciones del estado %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');
					SDL_BlitSurface( flechaarriba5, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					//printf("xx %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');

					SDL_BlitSurface( flecha5r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;

			case 5: 	SDL_BlitSurface( flechaarriba6, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					SDL_BlitSurface( flecha6r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );

					break;*/

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
	//printf("%c-----destino\n", (nodoDestino->nombre));

	int origen1 = cambioValor(nodoOrigen);
	int destino1 = cambioValor(nodoDestino);
	int distancia, y;


	printf("origen %d-----",origen1 );
	printf("destino %d--------",destino1 );


   if(origen1 < destino1){
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

	SDL_FreeSurface(flecha2);
	flecha2 = NULL;

	SDL_FreeSurface(flecha2r);
	flecha2r= NULL;
	
	
	SDL_FreeSurface(flecha3);
	flecha3 = NULL;

	SDL_FreeSurface(flecha3r);
	flecha3r= NULL;
	


	SDL_DestroyWindow( ventana );
	ventana = NULL;

	//TTF_Quit();
	SDL_Quit();
}




void pintarEstados(Nodo *estado, int x, int y){



	SDL_Rect coordenada;
        coordenada.x= x;
	coordenada.y= y;

	switch((estado->estado)){

		case 'a':	SDL_BlitSurface( a, NULL, superficieventana, &coordenada );
				break;
		case 'b':	SDL_BlitSurface( b, NULL, superficieventana, &coordenada );
				break;
		case 'c':	SDL_BlitSurface( c, NULL, superficieventana, &coordenada );
				break;
		case 'd':	SDL_BlitSurface( d, NULL, superficieventana, &coordenada );
				break;
		case 'e':	SDL_BlitSurface( e, NULL, superficieventana, &coordenada );
				break;
		case 'f':	SDL_BlitSurface( f, NULL, superficieventana, &coordenada );
				break;
		/*case 'g':	SDL_BlitSurface( g, NULL, superficieventana, &coordenada );
				break;
		case 'h':	SDL_BlitSurface( h, NULL, superficieventana, &coordenada );
				break;
		case 'i':	SDL_BlitSurface( i, NULL, superficieventana, &coordenada );
				break;
		case 'j':	SDL_BlitSurface( j, NULL, superficieventana, &coordenada );
				break;
		case 'k':	SDL_BlitSurface( k, NULL, superficieventana, &coordenada );
				break;
		case 'l':	SDL_BlitSurface( l, NULL, superficieventana, &coordenada );
				break;
		case 'm':	SDL_BlitSurface( m, NULL, superficieventana, &coordenada );
				break;
		case 'n':	SDL_BlitSurface( n, NULL, superficieventana, &coordenada );
				break;
		case 'o':	SDL_BlitSurface( o, NULL, superficieventana, &coordenada );
				break;
		case 'p':	SDL_BlitSurface( p, NULL, superficieventana, &coordenada );
				break;
		case 'q':	SDL_BlitSurface( q, NULL, superficieventana, &coordenada );
				break;
		case 'r':	SDL_BlitSurface( r, NULL, superficieventana, &coordenada );
				break;
		case 's':	SDL_BlitSurface( s, NULL, superficieventana, &coordenada );
				break;
		case 't':	SDL_BlitSurface( t, NULL, superficieventana, &coordenada );
				break;
		case 'u':	SDL_BlitSurface( u, NULL, superficieventana, &coordenada );
				break;
		case 'v':	SDL_BlitSurface( v, NULL, superficieventana, &coordenada );
				break;
		case 'w':	SDL_BlitSurface( w, NULL, superficieventana, &coordenada );
				break;
		case 'x':	SDL_BlitSurface( x, NULL, superficieventana, &coordenada );
				break;
		case 'y':	SDL_BlitSurface( y, NULL, superficieventana, &coordenada );
				break;
		case 'z':	SDL_BlitSurface( z, NULL, superficieventana, &coordenada );
				break;*/
		default:

				printf("no esta ese nombre de nodo");
				break;

		}

	/*if((estado->bandera) == 1){
		SDL_BlitSurface( no, NULL, superficieventana, &coordenada );
	//	printf("hola");

	}else{
                if((estado->bandera) == 0){
		SDL_BlitSurface( no, NULL, superficieventana, &coordenada );
	        }
		}*/
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
	char estadoI, estadoAceptadoI, datoLeerI, topePilaI, sacarPila1I, sacarPila2I, apilar1I, apilar2I, estadoPartida, estadoLlegada;
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
        cout<<"Ingrese un Estado(si es de aceptacion 1/0): \n";
        cin>>estadoI>>estadoAceptadoI;
        grafo.insertarNodo(&lista,estadoI, estadoAceptadoI);
      break;
      case 2:
          cout<<"Ingrese una regla: Dato a leer, dato en pila, dato desapilar, estado de partida, estado de llegada: \n";
          cin>>datoLeerI >> topePilaI >> sacarPila1I >> sacarPila2I>> apilar1I>> apilar2I>> estadoPartida >> estadoLlegada;
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
}
}
}


