#ifndef ATRIBUTO_H
#define ATRIBUTO_H

typedef char cadena[30];

typedef struct {
  cadena nombre;
  unsigned int tipo;
  unsigned int tamano;
  char iskp;
  long sig;
  cadena descripcion;
  char null;
} Atributo;

#endif