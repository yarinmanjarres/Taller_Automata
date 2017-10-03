#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

const int pantallaanchura = 800;
const int pantallaaltura = 600;

bool iniciar();


bool cargarimagen();

void cerrar();

SDL_Window* ventana = NULL;
	

SDL_Surface* superficieventana = NULL;


SDL_Surface* nodoaceptado = NULL;
SDL_Surface* no = NULL;
SDL_Surface* flecha2 = NULL;
SDL_Surface* flecha3 = NULL;
SDL_Surface* flecha4 = NULL;
SDL_Surface* flecha5 = NULL;
SDL_Surface* flecha6 = NULL;
SDL_Surface* flecha2r = NULL;
SDL_Surface* flecha3r = NULL;
SDL_Surface* flecha4r = NULL;
SDL_Surface* flecha5r = NULL;
SDL_Surface* flecha6r= NULL;


SDL_Surface* a = NULL;
SDL_Surface* b = NULL;
SDL_Surface* c = NULL;
SDL_Surface* d = NULL;
SDL_Surface* e = NULL;
SDL_Surface* f = NULL;
SDL_Surface* g = NULL;
SDL_Surface* h= NULL;










typedef struct stArco *adyunto;

typedef struct stNodo{
	char nombre;
	int bandera = 0; 
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



bool iniciar()
{
	
	bool valor = true;

	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "error de inicio sdl %s\n", SDL_GetError() );
		valor = false;
	}
	else
	{
	       
		

		ventana = SDL_CreateWindow( "Automata", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, pantallaanchura, pantallaaltura, 	SDL_WINDOW_SHOWN );
		if( ventana == NULL )
		{
			
			printf( "no se pudo crear la venatana: %s\n", SDL_GetError() );
			valor = false;
		}
		else
		{
			superficieventana = SDL_GetWindowSurface( ventana );
		}
	}



     if( (TTF_Init()) < 0 ){
		printf( "error de inicio del ttf %s\n", SDL_GetError() );
		valor = false;
	}


	return valor;
}


bool cargarimagenes()
{
	
	bool valor = true;

	
	no= SDL_LoadBMP( "/home/yarin/Documentos/ta/b.bmp" );
	nodoaceptado= SDL_LoadBMP( "/home/yarin/Documentos/ta/aceptado.bmp" );
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
	a= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/a.bmp" );
	b= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/b.bmp" );
	c= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/c.bmp" );
	d= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/d.bmp" );
	e= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/e.bmp" );
	f= SDL_LoadBMP( "/home/yarin/Documentos/ta/abc/f.bmp" );
	if( no == NULL )
	{
		printf( "no se cargo la imagen %s! SDL Error: %s\n", "no", SDL_GetError() );
		 return false;
	}
       
	
	if( flecha2 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 2 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	
	if( flecha3 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 3%s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	
	
	if( flecha4 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 4 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	
	if( flecha5 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 5 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
	
	if( flecha6 == NULL )
	{
		printf( "no se cargo la imagen FLECHA 6 %s! SDL Error: %s\n", "flecha", SDL_GetError() );
		 return valor=0;
	}
      
	if( nodoaceptado == NULL )
	{
		printf( "no se cargo la imagen %s! SDL Error: %s\n", "nodoaceptadp", SDL_GetError() );
		 return valor=0;
	}
       
		
	


	return valor;
}


/*void pintar(nodo *origen, arco *regla, nodo *destino, int x, int y){

	
	//SDL_Color colorWhite;
	//SDL_Surface *texto; 
	//char vector [9]= {'a','r','i','a','l','.','t','t','f'};
	//char lifeChar;


	SDL_Rect coordenada; 
        coordenada.x= x;
	coordenada.y= y; 
	
	

	//colorWhite.b = 0xFF; 
	//colorWhite.g = 0xFF; 
	//colorWhite.r = 0xFF;
	//colorWhite.unused = 0xFF; 

 
	//TTF_SetFontStyle(arial, TTF_STYLE_NORMAL);
		
	

	if((origen->bandera) == 1){
		SDL_BlitSurface( nodoaceptado, NULL, superficieventana, &coordenada );
		printf("hola");
		//texto = TTF_RenderUTF8_Blended (NULL, &(origen->nombre), colorWhite); 
		//x= x+83;
		//coordenada.x= x;
		//SDL_BlitSurface( texto, NULL, superficieventana, &coordenada );
		//TTF_CloseFont(arial);


	}else{
                if((origen->bandera) == 0){
		SDL_BlitSurface( no, NULL, superficieventana, &coordenada );
	        }
		}	
        x= x+83;
	coordenada.x= x;

	SDL_BlitSurface(flecha, NULL, superficieventana, &coordenada);
	

        x= x+83;
	coordenada.x= x;
	
	if((destino->bandera)== 1){
		SDL_BlitSurface( nodoaceptado, NULL, superficieventana, &coordenada );
	}else{
                if((destino->bandera)== 0){
		SDL_BlitSurface( no, NULL, superficieventana, &coordenada );
	        }
		}
        



     SDL_UpdateWindowSurface( ventana );
     SDL_Delay(500);
 
}*/

int cambioValor(nodo *estado){
	char nodoNombre= (estado->nombre);

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

void flechaAbajo(int x, int  y, int distancia, nodo *nodoOrigen){

	SDL_Rect coordenada; 
        coordenada.x= x;
	coordenada.y= y; 
        Uint32 colorkey;
	
	//printf("distancia %d\n", distancia);

    	 	switch(distancia){

			case 1:		
					printf("presione enter para mostrar con las relaciones del estado 1 %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');
					SDL_BlitSurface( flecha2, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);

					printf("xx %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');
					
					SDL_BlitSurface( flecha2r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
					
					

					break;
					
			case 2:		printf("presione enter para mostrar con las relaciones del estado 2 %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');
					SDL_BlitSurface( flecha3, NULL, superficieventana, &coordenada ); 
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					printf("xx %c\n", (nodoOrigen->nombre));
					while ( getchar() != '\n');
					
					SDL_BlitSurface( flecha3r, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
					
					
					break;
			case 3: 	printf("he hey %c\n", (nodoOrigen->nombre));			
					SDL_BlitSurface( flecha4, NULL, superficieventana, &coordenada );
					SDL_UpdateWindowSurface( ventana );
     					SDL_Delay(600);
					printf("xx %c\n", (nodoOrigen->nombre));
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










void pintarRelacion(nodo *origen, arco *regla, nodo *destino, int x){
			
	nodo *nodoOrigen= origen; 	
	nodo *nodoDestino= destino;
	//printf("%c-----destino\n", (nodoDestino->nombre)); 
	
	int origen1 = cambioValor(nodoOrigen);
	int destino1 = cambioValor(nodoDestino);
	int distancia= (destino1 - origen1); 
	
		
	//printf("origen %d-----",origen1 );	
	//printf("destino %d--------",destino1 );


   if(origen1 < destino1){
		origen1--;
		int y = (origen1*83);  
		printf("distancia %d--------",distancia);
		
		flechaAbajo(x,y,distancia, nodoOrigen);
		
	
	}else{

		if(origen > destino){
		printf("FLECHA ARRIBA ");
		//flechaArriba();


		}
	}
	 
	

}




void cerrar(){
	
	SDL_FreeSurface(no);
	no = NULL;
	
	SDL_FreeSurface(nodoaceptado);
	nodoaceptado = NULL;

	SDL_FreeSurface(flecha2);
	flecha2 = NULL;


	
	SDL_DestroyWindow( ventana );
	ventana = NULL;

	TTF_Quit();
	SDL_Quit();
}


void pintarEstados(nodo *estado, int x, int y){
		
	
	
	SDL_Rect coordenada; 
        coordenada.x= x;
	coordenada.y= y; 

	switch((estado->nombre)){

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







void mostrare (nodo *cabeza){
	TTF_Font *arial;
	nodo *a;
	arco *p;
	int x=0;
	int y=0; 
          
        arial = TTF_OpenFont("SIXTY.ttf", 28);
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
						  printf("no tiene mas relaciones el estado %c\n",a->nombre);
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
	insertarArco(&lista, 21, 'e', 'f');

	mostrare(lista);
	

	a = buscarNodo(lista, 'a');
	b = buscarNodo(lista, 'e');


	//system("pause");
	return 0;
}

