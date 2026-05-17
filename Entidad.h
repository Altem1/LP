#ifndef ENTIDAD_H_INCLUDED
#define ENTIDAD_H_INCLUDED
#include <cstdio>
#include <iostream>

typedef char cadena[30];
struct Entidad {
  cadena nombre;
  long atr;
  long data;
  long sig;
};

#endif // ENTIDAD_H_INCLUDED
