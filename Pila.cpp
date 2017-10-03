#include "Pila.h"
#include <iostream>
using namespace std;


Pila::Pila()
{              cima = 0;
                pila[0]=PILAVACIA;
}

int Pila :: getCima(){
    return cima;
}

bool Pila :: Apilar(char elemento)
{
bool res;
if(cima == MAX-1)
{   cerr << "Desbordamiento de Pila (Overflow)" << endl;
  res=false;
}else

     {cima++;
pila[cima] = elemento;
res = true;
}
return res;


}

bool Pila::Desapilar()
{
bool res;
if(cima == 0)
{   cerr << "Se esta intentando quitar un elemento de una pila vacia (underflow)" << endl;
  res=false;
}else

     {cima--;
res = true;
}
return res;


}

void Pila::VerPila()
{
for(int i=0;i<=cima;i++)
cout << pila[i] << endl;

}


bool Pila::CimaPila(char elemento)
{
bool res;
if(PilaVacia())//(cima == -1)
{cerr << "Se esta intentando quitar un elemento de una pila vacia (underflow)" << endl;
res = false;
}else

     { pila[cima];
cima--;
res = true;
}

return res;


}

bool Pila::PilaVacia()
{
return cima == 0;
}

void Pila::LimpiarPila()
{
cima = 0;
}

bool Pila :: pilaEstaVacia(){
    if (pila[0]==PILAVACIA){
        return true;
    }

    return false;
}








