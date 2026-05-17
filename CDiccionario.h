#ifndef CDICCIONARIO_H_INCLUDED
#define CDICCIONARIO_H_INCLUDED

#include "Atributo.h"
#include "Entidad.h"
#include <cstdio>

class CDiccionario {
private:
  FILE *arch;
  Entidad activa;
  long dir;
  int nAtributos;
  long tambloque;

  char nombreArchivo[50];

public:
  // constructor
  CDiccionario();

  // Entidades
  void Menu_Entidades();
  Entidad CapturaEntidad();
  void altaEntidad();
  long buscaEntidad(char nombre[30]);
  long getcabeceraEntidades();
  Entidad leeEntidad(long dir);
  void EscribeCabEntidades(long cab);
  long escribeEntidad(Entidad ant);
  void insertaEntidad(Entidad nvo, long dir);
  void ConsultaEntidades();
  void BajaEntidad();
  long EliminaEntidad(char nombre[30]);
  void reescribeEntidad(long dir, Entidad ant);
  void modificaEntidad();

  // Atributos
  void Menu_Atributos();
  void consultarAtributo();
  long eliminaAtributo(char cad[30]);
  void modificaAtributo();
  void AltaAtributo();
  Atributo CapturaAt();
  void insertaAtributo(Atributo nvo, long dir);
  long BuscarAtributo(char *atr);
  Atributo leeAtributo(long dir);
  long EscribeAtributo(Atributo ant);
  void reescribeAtributo(long dir, Atributo atr);
  void BajaAtributo();

  // Datos
  void Menu_Datos();

  // Principal
  void menu();
  void Nuevo();
  void abrir();
};

#endif // CDICCIONARIO_H_INC
