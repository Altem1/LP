#ifndef CDICCIONARIO_H_INCLUDED
#define CDICCIONARIO_H_INCLUDED

#include <cstdio>
#include "Atributo.h"
#include "Entidad.h"

class CDiccionario
{
private:
    FILE *arch;
    Entidad activa;
    long dir;
    int nAtributos;
    long tambloque;
    Atributo arrAtributos[50];
    char nombreArchivo[50];
public:
    //constructor
    CDiccionario();

    //Entidades
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
    void preguntaEntidad();


    //Atributos
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
    int cargaAtributos();


    //Datos
    void Menu_Datos();
    void* CapturaBloque();
    float comparaBloques(void*b1,void*b2);
    void altaBloque();
    void reescribeBloque(void* bloque, long dir);
    void* LeeBloque(long dir);
    long escribeBloque(void* bloque);
    void InsertaBloque(void *nvo, long dirnvo);
    void consultaBloques();
    long buscaBloque(void *bloquebus);
    void modificaBloque();
    void bajaBloque();
    void eliminaBloque(void*bloque);
    void *pideClaveBloque();





    //Principal
    void menu();
    void Nuevo();
    void abrir();

};

#endif // CDICCIONARIO_H_INC
