
#include<SDL2/SDL.h>
#include <stdio.h>


const int pantallaanchura = 800;
const int pantallaaltura = 600;


bool iniciar();


bool cargarimagen();

void cerrar();

SDL_Window* ventana = NULL;
	

SDL_Surface* superficieventana = NULL;


SDL_Surface* hola = NULL;

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
		
		ventana = SDL_CreateWindow( "hola mundo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, pantallaanchura, pantallaaltura, SDL_WINDOW_SHOWN );
		if( ventana == NULL )
		{
			printf( "no se pudo crear la venatana: %s\n", SDL_GetError() );
			valor = false;
		}
		else
		{
			//Get window surface
			superficieventana = SDL_GetWindowSurface( ventana );
		}
	}

	return valor;
}

bool cargarimagen()
{
	
	bool valor = true;

	
	hola = SDL_LoadBMP( "/home/yarin/Descargas/prueba/dos/hello_world.bmp" );
	if( hola == NULL )
	{
		printf( "no se cargo la imagen %s! SDL Error: %s\n", "/home/yarin/Descargas/prueba/dos/hello_world.bmp", SDL_GetError() );
		valor = false;
	}

	return valor;
}

void cerrar()
{
	
	SDL_FreeSurface( hola );
	hola = NULL;

	
	SDL_DestroyWindow( ventana );
	ventana = NULL;


	SDL_Quit();
}

int main( int argc, char* args[] )
{
	
	if( !iniciar() )
	{
		printf( "error inicio\n" );
	}
	else
	{
		
		if( !cargarimagen() )
		{
			printf( "error imagen\n" );
		}
		else
		{
			
			SDL_BlitSurface( hola, NULL, superficieventana, NULL );
			
			
			SDL_UpdateWindowSurface( ventana );

			
			SDL_Delay( 2000 );
		}
	}

	
	cerrar();

	return 0;
}
