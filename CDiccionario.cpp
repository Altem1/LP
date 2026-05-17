#include "CDiccionario.h"
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

CDiccionario::CDiccionario() {
  arch = NULL;
  nAtributos = 0;
  tambloque = 0;
  int op;
  do {
    // Menu principal
    menu();
    cout << "Eleccion:";
    cin >> op;
    switch (op) {
    case 1: {
      Nuevo();
      break;
    }
    case 2: {
      abrir();
      break;
    }
    case 3: {
      cout << "\n Saliendo del programa...........";
      break;
    }
    default:
      cout << "\nOpcion invslida. \n";
    }

  } while (op != 3);
}
void CDiccionario::menu() {
  cout << "       MENU    \n";
  cout << "   Seleccione la accion   \n";
  cout << "   1.=Nuevo Archivo \n";
  cout << "   2.=Abrir Archivo   \n";
  cout << "   3.=Salir del programa   \n";
}
void CDiccionario::Nuevo() {
  char Nombre[100];
  cin.ignore(1000, '\n'); // Limpia el buffer de entrada
  cout << "\nIngresa el nombre del archivo: ";
  cin.getline(Nombre, sizeof(Nombre));

  arch = fopen(Nombre, "rb");
  // Verifica si el archivo existe
  if (arch != NULL) {
    cout << "ERROR: ARCHIVO EXISTENTE.\n";
    fclose(arch);
    return;
  }
  // Crea el nuevo archivo
  arch = fopen(Nombre, "wb+");
  if (arch == NULL) {
    cout << "Error al crear el archivo";
    return;
  }
  cout << "Archivo creado.\n";
  cout << "Entidades -1";
  long cab = -1;
  fwrite(&cab, sizeof(long), 1, arch);

  Menu_Entidades();
  fclose(arch);
}
void CDiccionario::abrir() {
  char Nombre[100];
  cin.ignore(1000, '\n'); // Limpiar buffer de entrada
  cout << "\nIngresa el nombre del archivo: ";
  cin.getline(Nombre, sizeof(Nombre));

  arch = fopen(Nombre, "rb+");
  // Verifica si el archivo existe
  if (arch == NULL) {
    cout << "\nARCHIVO INEXISTENTE.\n ";
    return;
  }
  cout << "\n Archivo encontrado. \n";

  Menu_Entidades();
  fclose(arch);
}
void CDiccionario::Menu_Entidades() {
  int Enti;

  do {
    cout << "       Menu Entidades    \n";
    cout << "   Seleccione la accion   \n";
    cout << "   1.=Nueva Entidad \n";
    cout << "   2.=Consultar Entidades  \n";
    cout << "   3.=Eliminar Entidad   \n";
    cout << "   4.=Modificar Entidad  \n";
    cout << "   5.=Menu Atributos   \n";
    cout << "   6.=Menu Datos    \n";
    cout << "   7.=Regresar al menu anterior   \n";

    cout << "Ingresa una opcion: ";
    cin >> Enti;
    switch (Enti) {
    case 1: {
      altaEntidad();
      break;
    }
    case 2: {
      ConsultaEntidades();
      break;
    }
    case 3: {
      BajaEntidad();
      break;
    }
    case 4: {
      modificaEntidad();
      break;
    }
    case 5: {
      char nombreEntidad[30];
      cout << "Ingresa el nombre de la entidad para editar atributos: ";
      cin >> nombreEntidad;
      long dirEntidad = buscaEntidad(nombreEntidad);
      if (dirEntidad != -1) {
        activa = leeEntidad(dirEntidad);
        dir = dirEntidad;
        Menu_Atributos();
      } else {
        cout << "No existe esa entidad\n";
      }
      break;
    }
    case 6: {
      Menu_Datos();
      break;
    }
    case 7: {
      cout << "Regresando al menu anterior........\n";
      break;
    }
    default:
      cout << "Opcion invalida\n";
    }
  } while (Enti != 7);
}
void CDiccionario::Menu_Atributos() {
  int Atri;

  do {
    cout << "       Menu Atributos    \n";
    cout << "   Seleccione la accion   \n";
    cout << "   1.=Nuevo Atributo \n";
    cout << "   2.=Consultar Atributos  \n";
    cout << "   3.=Eliminar Atributos  \n";
    cout << "   4.=Modificar Atributos  \n";
    cout << "   5.=Regresar al menu anterior   \n";

    cout << "Ingresa una opcion: ";
    cin >> Atri;
    switch (Atri) {
    case 1: {
      AltaAtributo();
      break;
    }
    case 2: {
      consultarAtributo();
      break;
    }
    case 3: {
      BajaAtributo();
      break;
    }
    case 4: {
      modificaAtributo();
      break;
    }
    case 5: {
      cout << "Regresando al menu anterior........\n";
      break;
    }
    default:
      cout << "Opcion invalida\n";
    }
  } while (Atri != 5);
}
void CDiccionario::Menu_Datos() {
  int Dat;

  do {
    cout << "       Menu Atributos    \n";
    cout << "   Seleccione la accion   \n";
    cout << "   1.=Nuevo Registro \n";
    cout << "   2.=Consultar Registro  \n";
    cout << "   3.=Eliminar Registro  \n";
    cout << "   4.=Modificar Registro  \n";
    cout << "   5.=Regresar al menu anterior   \n";

    cout << "Ingresa una opcion: ";
    cin >> Dat;
    switch (Dat) {
    case 1: {
      cout << "\nCreando nuevo Registro\n";
      break;
    }
    case 2: {
      cout << "Consultando Registros\n";
      break;
    }
    case 3: {
      cout << "Eliminando Registros\n";
      break;
    }
    case 4: {
      cout << "Modificando Registros\n";
      break;
    }
    case 5: {
      cout << "Regresando al menu anterior........\n";
      break;
    }
    default:
      cout << "Opcion invalida\n";
    }
  } while (Dat != 5);
}

//---------ENTIDADES---------
// Crea una nueva entidad
Entidad CDiccionario::CapturaEntidad() {
  Entidad nueva;
  cout << "Ingresa el nombre de la entidad: ";
  cin >> nueva.nombre;
  nueva.atr = -1;
  nueva.data = -1;
  nueva.sig = -1;
  return nueva;
}
void CDiccionario::altaEntidad() {
  Entidad nueva = CapturaEntidad();

  if (buscaEntidad(nueva.nombre) == -1) {
    long dir = escribeEntidad(nueva);
    insertaEntidad(nueva, dir);
    cout << "Entidad guardada\n";
  } else {
    cout << "Error:La entidad ya existe\n";
  }
}
long CDiccionario::buscaEntidad(char nombre[30]) {
  long cab = getcabeceraEntidades();
  while (cab != -1) {
    Entidad actual = leeEntidad(cab);
    if (strcmp(actual.nombre, nombre) == 0) {
      return cab;
    }
    cab = actual.sig;
  }
  return -1;
}
long CDiccionario::getcabeceraEntidades() {
  long dir;
  fseek(arch, 0, SEEK_SET);
  fread(&dir, sizeof(long), 1, arch);
  return dir;
}
Entidad CDiccionario::leeEntidad(long dir) {
  Entidad nvo;
  fseek(arch, dir, SEEK_SET);
  fread(&nvo, sizeof(Entidad), 1, arch);
  return nvo;
}
void CDiccionario::EscribeCabEntidades(long cab) {
  fseek(arch, 0, SEEK_SET);
  fwrite(&cab, sizeof(long), 1, arch);
}
long CDiccionario::escribeEntidad(Entidad ant) {
  fseek(arch, 0, SEEK_END);
  long dir = ftell(arch);
  fwrite(&ant, sizeof(Entidad), 1, arch);
  return dir;
}
void CDiccionario::insertaEntidad(Entidad nvo, long dir) {
  long cab = getcabeceraEntidades();
  if (cab == -1) // caso 1. Lista vacia
  {
    nvo.sig = -1;
    reescribeEntidad(dir, nvo);
    EscribeCabEntidades(dir);
  } else {
    Entidad actual = leeEntidad(cab);
    if (strcmp(nvo.nombre, actual.nombre) < 0) {
      // caso 2.Al inicio
      nvo.sig = cab;
      reescribeEntidad(dir, nvo);
      EscribeCabEntidades(dir);
    } else {
      long dirant = cab;
      Entidad ant = actual;
      while (cab != -1 && strcmp(nvo.nombre, actual.nombre) > 0) {
        dirant = cab;
        ant = actual;
        cab = actual.sig;
        if (cab != -1) {
          actual = leeEntidad(cab);
        }
      }
      nvo.sig = cab;
      reescribeEntidad(dir, nvo);
      ant.sig = dir;
      reescribeEntidad(dirant, ant);
    }
  }
}
void CDiccionario::ConsultaEntidades() {
  long cab = getcabeceraEntidades();
  while (cab != -1) {
    Entidad nvo = leeEntidad(cab);
    printf("%s,%ld,%ld,%ld\n", nvo.nombre, nvo.atr, nvo.sig, nvo.data);
    cab = nvo.sig;
  }
}

void CDiccionario::BajaEntidad() {
  char nom[30];

  cout << "Ingresa nombre:";
  cin >> nom;
  if (EliminaEntidad(nom) == -1) {
    cout << "No existe\n";
  } else {
    cout << "Eliminado\n";
  }
}
long CDiccionario::EliminaEntidad(char nombre[30]) {
  long cab = getcabeceraEntidades();
  if (cab == -1) {
    return -1;
  }
  Entidad actual = leeEntidad(cab);

  if (strcmp(nombre, actual.nombre) == 0) {
    EscribeCabEntidades(actual.sig);
    return cab;
  }
  long dirant = cab;
  Entidad ant = actual;
  while (cab != -1 && strcmp(nombre, actual.nombre) != 0) {
    dirant = cab;
    ant = actual;
    cab = actual.sig;
    if (cab != -1) {
      actual = leeEntidad(cab);
    }
  }
  if (cab == -1) {
    return -1;
  }
  ant.sig = actual.sig;
  reescribeEntidad(dirant, ant);
  return cab;
}
void CDiccionario::reescribeEntidad(long dir, Entidad ant) {
  fseek(arch, dir, SEEK_SET);
  fwrite(&ant, sizeof(Entidad), 1, arch);
}
void CDiccionario::modificaEntidad() {
  char nombre[30];
  cout << "Que entidad quieres modificar?:";
  cin >> nombre;
  long dir = buscaEntidad(nombre);

  if (dir == -1) {
    cout << "No existe\n";
    return;
  }
  Entidad nueva = CapturaEntidad();
  if (strcmp(nombre, nueva.nombre) != 0 && buscaEntidad(nueva.nombre) != -1) {
    cout << "Ya existe esta entidad\n";
    return;
  }
  // Elimina la vieja entidad
  EliminaEntidad(nombre);
  // Inserta la nueva
  long nuevaDir = escribeEntidad(nueva);
  insertaEntidad(nueva, nuevaDir);
  cout << "Entidad Modificada\n";
}
// FUNCIONES DE ATRIBUTOS

void CDiccionario::AltaAtributo() {

  Atributo nuevoA = CapturaAt();
  if (BuscarAtributo(nuevoA.nombre) == -1) {
    long dirAtributo = EscribeAtributo(nuevoA);
    insertaAtributo(nuevoA, dirAtributo);
    cout << "Atributo creado exitosamente\n";
  } else {
    cout << "Error: Ese atributo ya existe\n";
  }
}

Atributo CDiccionario::CapturaAt() {
  Atributo nuevoA;
  cout << "Dame el nombre: ";
  cin >> nuevoA.nombre;
  cout << "¿Que tipo es?: 1. Char \n2. Entero \n3. Float \n4. Double \n5. "
          "Long\n";
  cin >> nuevoA.tipo;
  if (nuevoA.tipo == 1) {
    cout << "¿Cuantas letras?: ";
    cin >> nuevoA.tamano;
  } else {
    switch (nuevoA.tipo) {
    case 2:
      nuevoA.tamano = sizeof(int);
      break;
    case 4:
      nuevoA.tamano = sizeof(float);
      break;
    case 3:
      nuevoA.tamano = sizeof(double);
      break;
    case 5:
      nuevoA.tamano = sizeof(long);
      break;
    }
  }
  cout << "¿Este atributo es clave primaria? (S/N): ";
  cin >> nuevoA.iskp;
  cout << "¿Permite nulos? (S/N): ";
  cin >> nuevoA.null;
  cin.ignore(1000, '\n');
  cout << "indique una descripcion para el atributo: ";
  cin.getline(nuevoA.descripcion, 30);
  nuevoA.sig = -1;
  return nuevoA;
}

void CDiccionario::insertaAtributo(Atributo nvo, long dir) {
  if (activa.atr == -1) {
    activa.atr = dir;
    reescribeEntidad(this->dir, activa);
  } else {
    Atributo actual = leeAtributo(activa.atr);
    if (strcmp(actual.nombre, nvo.nombre) > 0) {
      nvo.sig = activa.atr;
      reescribeAtributo(dir, nvo);
      activa.atr = dir;
      reescribeEntidad(this->dir, activa);
    } else {
      long cab = activa.atr;
      Atributo atrant = actual;
      long dirant = cab;
      while (cab != -1 && strcmp(nvo.nombre, actual.nombre) > 0) {
        atrant = actual;
        dirant = cab;
        cab = actual.sig;
        if (cab != -1) {
          actual = leeAtributo(cab);
        }
      }
      if (cab != -1) {
        nvo.sig = cab;
      }
      reescribeAtributo(dir, nvo);
      atrant.sig = dir;
      reescribeAtributo(dirant, atrant);
    }
  }
}

long CDiccionario::BuscarAtributo(char *atr) {
  Atributo actual;
  long cab = activa.atr;
  while (cab != -1) {
    actual = leeAtributo(cab);
    if (strcmp(actual.nombre, atr) == 0) {
      return cab;
    }
    cab = actual.sig;
  }
  return -1;
}

void CDiccionario::consultarAtributo() {
  Atributo nvo;
  long cab = activa.atr;
  while (cab != -1) {
    nvo = leeAtributo(cab);
    printf("%s,%d,%d,%c,%c,%s\n", nvo.nombre, nvo.tipo, nvo.tamano, nvo.iskp,
           nvo.null, nvo.descripcion);
    cab = nvo.sig;
  }
}

Atributo CDiccionario::leeAtributo(long dir) {
  Atributo nvo;
  if (dir == -1) {
    Atributo vacio;
    return vacio;
  }
  fseek(arch, dir, SEEK_SET);
  fread(&nvo, sizeof(Atributo), 1, arch);
  return nvo;
}

long CDiccionario::EscribeAtributo(Atributo ant) {
  fseek(arch, 0, SEEK_END);
  long dir = ftell(arch);
  fwrite(&ant, sizeof(Atributo), 1, arch);
  return dir;
}

void CDiccionario::reescribeAtributo(long dir, Atributo atr) {
  fseek(arch, dir, SEEK_SET);
  fwrite(&atr, sizeof(Atributo), 1, arch);
}
void CDiccionario::BajaAtributo() {
  long dir;
  char nombre[30];
  cout << "Ingresa el nombre del atributo a eliminar: ";
  cin >> nombre;
  dir = BuscarAtributo(nombre);
  if (dir == -1) {
    cout << "Error: el atributo no existe ";
  } else {
    eliminaAtributo(nombre);
  }
}

long CDiccionario::eliminaAtributo(char cad[30]) {
  long cab = activa.atr;
  long dirant = -1;
  Atributo ant, actual;
  actual = leeAtributo(cab);

  if (strcmp(actual.nombre, cad) == 0) {
    activa.atr = actual.sig;
    reescribeEntidad(this->dir, activa);
  } else {
    while (cab != -1 && strcmp(cad, actual.nombre) != 0) {
      dirant = cab;
      ant = actual;
      cab = actual.sig;
      if (cab != -1) {
        actual = leeAtributo(cab);
      }
    }
    if (cab != -1 && strcmp(cad, actual.nombre) == 0) {
      ant.sig = actual.sig;
      reescribeAtributo(dirant, ant);
    }
  }
  return (cab);
}

void CDiccionario::modificaAtributo() {
  char nombre[30];
  Atributo nuevo;

  cout << "\nAtributo a modificar: ";
  cin.ignore();
  cin.getline(nombre, 30);

  long direccion1 = BuscarAtributo(nombre);

  if (direccion1 != -1) {
    cout << "\nIngrese la nueva informacion\n";
    nuevo = CapturaAt();

    long direccion2 = BuscarAtributo(nuevo.nombre);
    if (direccion1 == direccion2 || direccion2 == -1) {
      long direccion3 = eliminaAtributo(nombre);
      nuevo.sig = -1;
      reescribeAtributo(direccion3, nuevo);
      insertaAtributo(nuevo, direccion3);
      cout << "\nAtributo modificado\n";
    } else
      cout << "\nNo se pudo modificar por que ya existe uno con ese nombre\n";
  } else {
    cout << "\nNo existe ese atributo\n";
  }
}
