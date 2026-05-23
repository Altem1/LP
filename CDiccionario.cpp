#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "CDiccionario.h"

using namespace std;
//Constructor
CDiccionario::CDiccionario()
{
    arch=NULL;//inicializa el archivo como NULL
    nAtributos=0; //inicializa el contador de los atributos
    tambloque=0;//inicializa el tamano del bloque
     int op;
   do
   {
       //Menu principal
       menu();
       cout<<"Eleccion:";
       cin>>op;
       switch(op)
       {
       case 1:
        {
          Nuevo();//crea un nuevo archivo
          break;
        }
       case 2:
        {
            abrir();//Abre un archivo ya existente
            break;
        }
       case 3:
        {
            cout<<"\n Saliendo del programa...........";
            break;
        }
       default:
        cout<<"\nOpcion invslida. \n";
       }


   }while(op != 3);
}
void CDiccionario::menu()
{
   cout<<"       MENU    \n";
   cout<<"   Seleccione la accion   \n";
   cout<<"   1.=Nuevo Archivo \n";
   cout<<"   2.=Abrir Archivo   \n";
   cout<<"   3.=Salir del programa   \n";

}
void CDiccionario::Nuevo()
{
    char Nombre[100];
    cin.ignore(1000, '\n'); //Limpia el buffer de entrada
    cout<<"\nIngresa el nombre del archivo: ";
    cin.getline(Nombre, sizeof(Nombre));

    arch=fopen(Nombre,"rb");
//Verifica si el archivo existe
         if(arch != NULL)
          {
            cout<<"ERROR: ARCHIVO EXISTENTE.\n";
            fclose(arch);
            return;
          }
//Crea el nuevo archivo
          arch=fopen(Nombre,"wb+");
          if(arch == NULL)
          {
              cout<<"\nError al crear el archivo\n";
              return;
          }
          cout<<"Archivo creado.\n";
          cout<<"Entidades -1\n";
          long cab=-1;
          fwrite(&cab,sizeof(long),1,arch);

          Menu_Entidades();
          fclose(arch);
}
void CDiccionario::abrir()
{
  char Nombre[100];
  cin.ignore(1000, '\n');//Limpiar buffer de entrada
  cout<<"\nIngresa el nombre del archivo: ";
  cin.getline(Nombre, sizeof(Nombre));

  arch=fopen(Nombre,"rb+");
  //Verifica si el archivo existe
  if(arch == NULL)
  {
      cout<<"\nARCHIVO INEXISTENTE.\n ";
      return;

  }
  cout<<"\n Archivo encontrado. \n";

  Menu_Entidades();
  fclose(arch);

}
void CDiccionario::Menu_Entidades()
{
      int Enti;


    do
    {
       cout<<" \n     Menu Entidades    \n";
    cout<<"   Seleccione la accion   \n";
    cout<<"   1.=Nueva Entidad \n";
    cout<<"   2.=Consultar Entidades  \n";
    cout<<"   3.=Eliminar Entidad   \n";
    cout<<"   4.=Modificar Entidad  \n";
    cout<<"   5.=Menu Atributos   \n";
    cout<<"   6.=Menu Datos    \n";
    cout<<"   7.=Regresar al menu anterior   \n";

    cout<<"Ingresa una opcion: ";
    cin>>Enti;
        switch(Enti)
        {
            case 1:
             {
                altaEntidad();//Crea una entidad nueva
                break;
             }
            case 2:
                {
                    ConsultaEntidades();//Muestra todas las entidades
                    break;
                }
            case 3:
                {
                 BajaEntidad();//Elimina entidades
                 break;
                }
            case 4:
                {
                 modificaEntidad();//Modifica una entidad
                 break;
                }
            case 5:
                {
                    //Entrar al menu de atributos
                 char nombreEntidad[30];
                 cout<<"\nIngresa el nombre de la entidad para editar atributos: ";
                 cin>>nombreEntidad;
                 long dirEntidad = buscaEntidad(nombreEntidad);
                 if(dirEntidad != -1)
                 {
                     activa = leeEntidad(dirEntidad);
                     dir = dirEntidad;
                     Menu_Atributos();
                 }
                 else
                 {
                     cout<<"No existe esa entidad\n";
                 }
                 break;
                }
            case 6:
                {
                  //Entra al menu de registros
                  preguntaEntidad();
                  if(cargaAtributos()==1)
                  {
                      Menu_Datos();
                  }
                 break;
                }
            case 7:
                {
                 cout<<"\nRegresando al menu anterior........\n";
                 break;
                }
            default:
                cout<<"\nOpcion invalida\n";
        }
    }while (Enti != 7);
}
void CDiccionario::Menu_Atributos()
{
      int Atri;


    do
    {
       cout<<"\n      Menu Atributos    \n";
    cout<<"   Seleccione la accion   \n";
    cout<<"   1.=Nuevo Atributo \n";
    cout<<"   2.=Consultar Atributos  \n";
    cout<<"   3.=Eliminar Atributos  \n";
    cout<<"   4.=Modificar Atributos  \n";
    cout<<"   5.=Regresar al menu anterior   \n";

    cout<<"\nIngresa una opcion: ";
    cin>>Atri;
        switch(Atri)
        {
            case 1:
             {
                AltaAtributo();//Crea un nuevo atributo
                break;
             }
            case 2:
                {
                    consultarAtributo();//Muestra los atributos
                    break;
                }
            case 3:
                {
                 BajaAtributo();//Elimina un atributo
                 break;
                }
            case 4:
                {
                 modificaAtributo();//Modifica un atributo
                 break;
                }
            case 5:
                {
                 cout<<"\nRegresando al menu anterior........\n";
                 break;
                }
            default:
                cout<<"\nOpcion invalida\n";
        }
    }while (Atri != 5);
}
void CDiccionario::Menu_Datos()
{
      int Dat;


    do
    {
    cout<<"\n      Menu Datos    \n";
    cout<<"   Seleccione la accion   \n";
    cout<<"   1.=Nuevo Registro \n";
    cout<<"   2.=Consultar Registro  \n";
    cout<<"   3.=Eliminar Registro  \n";
    cout<<"   4.=Modificar Registro  \n";
    cout<<"   5.=Regresar al menu anterior   \n";

    cout<<"Ingresa una opcion: ";
    cin>>Dat;
        switch(Dat)
        {
            case 1:
             {
                altaBloque();//Inserta un nuevo registro
                break;
             }
            case 2:
                {
                   consultaBloques();//Muestra los registros
                    break;
                }
            case 3:
                {
                 bajaBloque();//Elimina un registro
                 break;
                }
            case 4:
                {
                 modificaBloque();//Modifica un registro
                 break;
                }
            case 5:
                {
                 cout<<"Regresando al menu anterior........\n";
                 break;
                }
            default:
                cout<<"Opcion invalida\n";
        }
    }while (Dat != 5);
}

//---------ENTIDADES---------
//Crea una nueva entidad
Entidad CDiccionario::CapturaEntidad()
{
    //Pide el nombre de la entidad
    Entidad nueva;
    cout<< "Ingresa el nombre de la entidad: ";
    cin>>nueva.nombre;
    //Inicializa sus apuntadores en -1
    nueva.atr=-1;
    nueva.data=-1;
    nueva.sig=-1;
    return nueva;
}
//Inserta una nueva entidad al archivo
void CDiccionario::altaEntidad()
{
  Entidad nueva=CapturaEntidad();
//verifica  que no exista ya la entidad
  if(buscaEntidad(nueva.nombre)==-1)
  {
     long dir=escribeEntidad(nueva);
      insertaEntidad(nueva,dir);
      cout<<"Entidad guardada\n";
  }
  else
  {
      cout<<"Error:La entidad ya existe\n";
  }
}
//Busca la entidad dentro del archivo mediante su nombre
long CDiccionario::buscaEntidad(char nombre[30])
{
    long cab=getcabeceraEntidades();
    while(cab!=-1)
    {
      Entidad actual=leeEntidad(cab);
      if(strcmp(actual.nombre,nombre)==0)
      {
          //Regresa su direccion
          return cab;
      }
      cab=actual.sig;
    }
    return-1;//si no la encuentra regresa -1
}
//lee la primera direccion de la lista de entidades
long CDiccionario::getcabeceraEntidades()
{
    long dir;
    fseek(arch,0,SEEK_SET);//Mueve el puntero del archivo al inicio
    fread(&dir,sizeof(long),1,arch);//Lee el dato y lo guarda en dir
    return dir;//regresa la direccion
}
//Lee la entidad en el archivo con su direccion
Entidad CDiccionario::leeEntidad(long dir)
{
    Entidad nvo;
    fseek(arch,dir,SEEK_SET);//Desde el inicio se mueve a la direccion
    fread(&nvo,sizeof(Entidad),1,arch);//Lee la entidad
    return nvo;
}
//Guarda la direccion inicial de las entidades
void CDiccionario::EscribeCabEntidades(long cab)
{
  fseek(arch,0,SEEK_SET);//se posiciona al inicio del archivo
  fwrite(&cab,sizeof(long),1,arch);//Escribe la informacion
}
//Almacena una entidad al final del archivo
long CDiccionario::escribeEntidad(Entidad ant)
{
    fseek(arch,0,SEEK_END);//Se posiciona al final
    long dir=ftell(arch);//Obtiene la direccion final en el archivo
    fwrite(&ant,sizeof(Entidad),1,arch);//Inserta la informacion
    return dir;//regresa su direccion
}
//Inserta una entidad en el archivo ordenada por el nombre
void CDiccionario::insertaEntidad(Entidad nvo, long dir)
{
    long cab=getcabeceraEntidades();
    if(cab==-1)//caso 1. Lista vacia
    {
        nvo.sig=-1;
        reescribeEntidad(dir,nvo);
        EscribeCabEntidades(dir);
    }
    else
    {
        Entidad actual=leeEntidad(cab);
        if(strcmp(nvo.nombre,actual.nombre)<0)
        {
            //caso 2.Al inicio
            nvo.sig=cab;
            reescribeEntidad(dir,nvo);
            EscribeCabEntidades(dir);
        }
        else
        {
            long dirant=cab;
            Entidad ant=actual;
            while(cab!=-1 && strcmp(nvo.nombre,actual.nombre)>0)
            {
                dirant=cab;
                ant=actual;
                cab=actual.sig;
                if(cab!=-1)
                {
                    actual=leeEntidad(cab);
                }
            }
                nvo.sig=cab;
                reescribeEntidad(dir,nvo);
                ant.sig=dir;
                reescribeEntidad(dirant,ant);
        }
    }
}
//Recorre el archivo y muestra todas las entidades guardadas
void CDiccionario::ConsultaEntidades()
{
    long cab=getcabeceraEntidades();//Obtiene la cabecera de las entidades
    cout<<left <<setw(15) <<"Entidad" <<setw(10) <<"Atributos" <<setw(10) <<"Datos" <<setw(10) <<"siguiente\n";
    while(cab!=-1)
    {
      Entidad nvo=leeEntidad(cab);//lee su informacion
      cout<< left <<setw(15) <<nvo.nombre <<setw(10) <<nvo.atr <<setw(10) <<nvo.data <<setw(10) <<nvo.sig <<"\n";//Imprime una por una
      cab=nvo.sig;
    }
}
//Se pide el nombre y se elimina la entidad
void CDiccionario::BajaEntidad()
{
    char nom[30];
    cout<<"Ingresa nombre:";
    cin>>nom;
    if(EliminaEntidad(nom)==-1)
    {
        cout<<"No existe\n";
    }
    else
    {
        cout<<"Eliminado\n";
    }
}
//Elimina una entidad de la lista de entidades
long CDiccionario::EliminaEntidad(char nombre[30])
{
    long cab=getcabeceraEntidades();//Obtiene la cabecera
    //verifica si la lista esta vacia
    if(cab == -1)
    {
        return -1;
    }
    Entidad actual = leeEntidad(cab);//lee la entidad

    if(strcmp(nombre,actual.nombre)==0)//La entidad a elminar esta en el inicio
    {
        EscribeCabEntidades(actual.sig);//atcualiza la cabecera con la siguiente entidad
        return cab;//Regresa la direccion eliminada
    }
    long dirant=cab;
    Entidad ant=actual;
        while(cab!=-1 && strcmp(nombre,actual.nombre)!=0)//Recorre la lista para encontrar la entidad
        {
            //Guarda la informacion del nodo anterior y avanza al siguiente
            dirant=cab;
            ant=actual;
            cab=actual.sig;
            if(cab!=-1)//si existe un nodo siguiente lo lee
            {
                actual=leeEntidad(cab);
            }
        }
        if(cab == -1)//Verifica si la entidad no fue encontrada
        {
            return -1;
        }
        //Enlasa el nodo anterior con el siguiente del que se busca eliminar
            ant.sig=actual.sig;
        //Actualiza la direccion del nodo siguiente de la entidad anterior en el archivo
            reescribeEntidad(dirant,ant);
            return cab;
}
//Sobreescribe una entidad en una diraccion especifica
void CDiccionario::reescribeEntidad(long dir,Entidad ant)
{
    fseek(arch,dir,SEEK_SET);//se posiciona en la direccion
    fwrite(&ant,sizeof(Entidad),1,arch);//Actualiza la entidad
}
//Modifica la informacion de una entidad
void CDiccionario::modificaEntidad()
{
    char nombre[30];
    cout<<"Que entidad quieres modificar?:";//Pregunta la entidad
    cin>>nombre;
    long dir=buscaEntidad(nombre);//La busca

    if(dir == -1)
    {
        cout<<"No existe\n";
        return;
    }
    //Si la encuentra captura su nueva info
    Entidad nueva=CapturaEntidad();
    if(strcmp(nombre,nueva.nombre)!=0 && buscaEntidad(nueva.nombre)!=-1)
    {
        cout<<"Ya existe esta entidad\n";
        return;
    }
    //Elimina la vieja entidad
    EliminaEntidad(nombre);
    //Inserta la nueva
    long nuevaDir=escribeEntidad(nueva);
    insertaEntidad(nueva,nuevaDir);
    cout <<"Entidad Modificada\n";
}
//Busca una entidad y la prepara para trabajar con los atributos o los registros
void CDiccionario::preguntaEntidad()
{
    char nombre[30];
    cout<<"\nIngresa la entidad a utilizar:";
    cin>>nombre;
    long direccion=buscaEntidad(nombre);
    if(direccion!=-1)
    {
      activa=leeEntidad(direccion);
      this->dir=direccion;
    }
    else
    {
        cout<<"\n Entidad no encontrada.";
    }
}
//-------------FUNCIONES DE ATRIBUTOS-------------------

//Crea un atributo nuevo para la entidad activa
void CDiccionario::AltaAtributo(){

	Atributo nuevoA = CapturaAt();//Captura la info del atributo
	//verifica que no exista
	if( BuscarAtributo(nuevoA.nombre) == -1 ){
        //Obtenemos su direccio
		long dirAtributo = EscribeAtributo(nuevoA);
		insertaAtributo(nuevoA, dirAtributo);//Se inserta en el archivo ordenada mente
		cout<<"Atributo creado exitosamente\n";
	}else{
		cout<<"Error: Ese atributo ya existe\n";
	}
}
//Solicita la info del artributo
Atributo CDiccionario::CapturaAt(){
	Atributo nuevoA;
	cout<<"\nDame el nombre: ";
	cin>>nuevoA.nombre;
	cout<<"\n¿Que tipo es?\n 1. Char \n 2. Entero \n 3. Float \n 4. Double \n 5. Long\n Tipo:";
	cin>>nuevoA.tipo;
	if( nuevoA.tipo == 1){
		cout << "\n¿Cuantas letras?: ";
		cin >> nuevoA.tamano;
		nuevoA.tamano++;
	}else{
		switch( nuevoA.tipo ){
			case 2:
				nuevoA.tamano = sizeof(int);
				break;
			case 3:
				nuevoA.tamano = sizeof(float);
				break;
            case 4:
                nuevoA.tamano=sizeof(double);
                break;
            case 5:
                nuevoA.tamano= sizeof(long);
                break;
		}
	}
	cout << "\n¿Este atributo es clave primaria? (S/N): ";
	cin >> nuevoA.iskp;
	cout << "\n¿Permite nulos? (S/N): ";
	cin >> nuevoA.null;
	cin.ignore(1000, '\n');
	cout << "\nindique una descripcion para el atributo: ";
	cin.getline(nuevoA.descripcion,30);
	nuevoA.sig = -1;
	return nuevoA;
}
//Inserta el atributo ala lista de atributos de manera ordenada
void CDiccionario::insertaAtributo(Atributo nvo, long dir)
{
    if(activa.atr == -1){
        activa.atr = dir;
        reescribeEntidad(this->dir, activa);
    }else{
        Atributo actual = leeAtributo(activa.atr);
        if(strcmp(actual.nombre, nvo.nombre)>0){
            nvo.sig = activa.atr;
            reescribeAtributo(dir,nvo);
            activa.atr = dir;
            reescribeEntidad(this->dir, activa);
        }else{
            long cab = activa.atr;
            Atributo atrant = actual;
            long dirant = cab;
            while(cab != -1 && strcmp(nvo.nombre, actual.nombre)>0){
                atrant = actual;
                dirant = cab;
                cab = actual.sig;
                if(cab != -1){
                    actual = leeAtributo(cab);
                }
            }
            if(cab != -1){
                nvo.sig = cab;
            }
            reescribeAtributo(dir, nvo);
            atrant.sig = dir;
            reescribeAtributo(dirant,atrant);
        }
    }
}
//Busca el atributo por el nombre
long CDiccionario::BuscarAtributo(char *atr){
    Atributo actual;
    long cab = activa.atr;
    while(cab != -1){
        actual = leeAtributo(cab);
        if(strcmp(actual.nombre, atr)==0){
            return cab;
        }
        cab = actual.sig;
    }
    return -1;
}
//Muestra todos los atributos
void CDiccionario::consultarAtributo(){
    Atributo nvo;
    long cab = activa.atr;
      cout<<left <<setw(15) <<"Nombre" <<setw(10) <<"Tipo" <<setw(10) <<"Tamano" <<setw(10) <<"iskp"<<setw(10)<<"Nulo"<<setw(10)<<"Descripcion\n";
    while(cab != -1){
        nvo = leeAtributo(cab);
        cout<< left <<setw(15) <<nvo.nombre <<setw(10) <<nvo.tipo <<setw(10) <<nvo.tamano <<setw(10) <<nvo.iskp <<setw(10)<<nvo.null<<setw(10)<<nvo.descripcion<<"\n";
        cab = nvo.sig;
    }
}

//Lee un atributo desde el archivo
Atributo CDiccionario::leeAtributo(long dir)
{
    Atributo nvo;
    if(dir==-1)
    {
        Atributo vacio={};
        return vacio;
    }
    fseek(arch, dir, SEEK_SET);//se pocisiona en la direccion del atributo en el archivo
    fread(&nvo, sizeof(Atributo), 1, arch);//Lee la info
    return nvo;//lo regresa
}
//Guarda un nuevo atributo al final del archivo
long CDiccionario::EscribeAtributo(Atributo ant)
{
    fseek(arch, 0, SEEK_END);//Se posiciona en el final
    long dir = ftell(arch);//Obtiene esa direccion
    fwrite(&ant, sizeof(Atributo), 1, arch);//Inserta el atributo en el archivo
    return dir;//regresa su direccion
}
//Actualiza un atributo que ya existe
void CDiccionario::reescribeAtributo(long dir, Atributo atr)
{
    fseek(arch, dir, SEEK_SET);//Se posiciona en su direccion
    fwrite(&atr, sizeof(Atributo), 1, arch);//Actualiza el archivo
}
//Elimina un atributo
void CDiccionario::BajaAtributo()
{
    long dir;
    char nombre[30];
    cout<<"Ingresa el nombre del atributo a eliminar: ";
    cin>>nombre;
    dir=BuscarAtributo(nombre);
    if(dir==-1)
    {
        cout<<"Error: el atributo no existe ";
    }
    else
    {
        eliminaAtributo(nombre);
    }
}
//elimina un atributo de la lista
long CDiccionario::eliminaAtributo(char cad[30])
{
    if(activa.data!=-1)
    {
        cout<<"\nNo se puede eliminar el atributo porque la entidad ya contiene registros\n";
        return -1;
    }
    long cab=activa.atr;
    long dirant=-1;
    Atributo ant,actual;
    actual=leeAtributo(cab);

    if(strcmp(actual.nombre,cad)==0)
    {
        activa.atr=actual.sig;
        reescribeEntidad(this->dir,activa);
    }
    else
    {
        while(cab!=-1&&strcmp(cad,actual.nombre)!=0)
        {
            dirant=cab;
            ant=actual;
            cab=actual.sig;
            if(cab!=-1)
            {
                actual=leeAtributo(cab);
            }
        }
        if(cab != -1 && strcmp(cad,actual.nombre)==0)
        {
            ant.sig=actual.sig;
            reescribeAtributo(dirant,ant);
        }
    }
    return (cab);
}
//Modifica la informacion del atributo
void CDiccionario::modificaAtributo()
{
    char nombre[30];
    Atributo nuevo;
    //Verifica si la entidad ya tiene registros
    if(activa.data != -1)
    {
        cout<<"\n No se puede modificar el atributo porque contiene registros\n";
        return;
    }
    //Pide el atributo a modificar
    cout<<"\nAtributo a modificar: ";
    cin.ignore();
    cin.getline(nombre,30);
    //Busca el atributo
    long direccion1= BuscarAtributo(nombre);
     //si lo encuentra
    if(direccion1!= -1)
    {  //Se captura la nueva informacion
        cout<<"\nIngrese la nueva informacion\n";
        nuevo= CapturaAt();
        //Busca si ya existe un atributo con el nuevo nombre
        long direccion2= BuscarAtributo(nuevo.nombre);
        //Verifica que no haya problemas con los nombres
        if(direccion1== direccion2 || direccion2== -1)
        {
            //elimina el atributo viejo
            long direccion3 = eliminaAtributo(nombre);
            nuevo.sig = -1;//inicializa el apuntador a siguente
            reescribeAtributo(direccion3, nuevo);//sobreescribe el atributo al archivo
            insertaAtributo(nuevo, direccion3);//Inserta el atributo nuevamente pero ordenado
            cout<<"\nAtributo modificado\n";
        }
        else
            cout<<"\nNo se pudo modificar por que ya existe uno con ese nombre\n";
    }
    else
    {
      cout<<"\nNo existe ese atributo\n";
    }

}
//Carga los atibutos de la entidad activa para trabajar con los registros
int CDiccionario::cargaAtributos()
{
    long cab= activa.atr;
    Atributo actual;
    nAtributos=0;
    tambloque= sizeof(long);
    int kp=0;

    while(cab!=-1)
    {
        actual=leeAtributo(cab);
        //Verifica clave primaria
        if(actual.iskp=='S'|| actual.iskp=='s')
        {
            kp++;
            //intercambia atributos
            arrAtributos[nAtributos]=arrAtributos[0];
            arrAtributos[0]=actual;
        }
        else
        {
            arrAtributos[nAtributos]=actual;
        }
        tambloque+=actual.tamano;
        nAtributos++;
        cab=actual.sig;
    }
    //verificar que solo este una clave primaria
    if(kp>1)
    {
        cout<<"\nTiene mas de una Clave Primaria\n";
    }
    else if(kp==0)
    {
        cout<<"\n No tiene Claves Primarias\n";
    }
    return kp;
}
   //FUNCIONES DE BLOQUES
   //Solicita los datos de el registro
   void* CDiccionario::CapturaBloque()
   {
       void* bloque;
       bloque=malloc(tambloque);
       memset(bloque,0,tambloque);
       long desp=0;
       *((long*)bloque)=-1;
       desp=sizeof(long);
       //Captura la informacion de cada atributo segun el tipo
       for(int i=0; i<nAtributos;i++)
       {
           cout<<"\n Ingrese el "<<arrAtributos[i].nombre<<":";
           switch(arrAtributos[i].tipo)
           {
           case 1:
            {
                char texto[200];
                cin.getline(texto,200);
                strncpy((char*)bloque+desp,texto,arrAtributos[i].tamano-1);
                ((char*)bloque+desp)[arrAtributos[i].tamano-1]='\0';
                break;
            }
           case 2:
            {
                int valor;
                cin>>valor;
                cin.ignore(1000,'\n');
                *((int*)((char*)bloque+desp))=valor;
                break;
            }
           case 3:
            {
                float valor;
                cin>>valor;
                cin.ignore(1000,'\n');
                *((float*)((char*)bloque+desp))=valor;
                break;
            }
           case 4:
            {
                double valor;
                cin>>valor;
                cin.ignore(1000,'\n');
                *((double*)((char*)bloque+desp))=valor;
                break;
            }
           case 5:
            {
            long valor;
            cin>>valor;
            cin.ignore(1000,'\n');
            *((long*)((char*)bloque+desp))=valor;
            break;
            }

           }
           desp+=arrAtributos[i].tamano;
       }
       return bloque;//Regresa el bloque de los atributos
   }
   //Compara dos registros con su clave primaria
   float CDiccionario::comparaBloques(void* b1, void*b2)
   {
       long desp=sizeof(long);
       switch(arrAtributos[0].tipo)
       {
       case 1:return strcmp((char*)b1+desp,(char*)b2+desp);
              break;
       case 2:return*((int*)((char*)b1+desp))-*((int*)((char*)b2+desp));
              break;
       case 3:return*((float*)((char*)b1+desp))- *((float*)((char*)b2+desp));
              break;
       case 4:return*((double*)((char*)b1+desp))- *((double*)((char*)b2+desp));
              break;
       case 5:return *((long*)((char*)b1+desp))- *((long*)((char*)b2+desp));
              break;
       }
       return 0;
   }
   //Inserta un registro en el archivo
   void CDiccionario::altaBloque()
   {
       //Captura la info del registro
       void *Nuevo=CapturaBloque();
       //Verifica que no exista
       if(buscaBloque(Nuevo)==-1)
       {
          long  dirnuevo=escribeBloque(Nuevo);//Lo inserta al final y obtiene su direccion
           InsertaBloque(Nuevo,dirnuevo);//Lo inserta ordenadamente
           cout<<"\n Registro insertado correctamente\n";
       }
       else
       {
           cout<<"\n El bloque ya existe";
       }
       free(Nuevo);
   }
   //Actualiza un bloque en el archivo
   void CDiccionario::reescribeBloque(void *bloque,long dir)
   {
       fseek(arch,dir,SEEK_SET);
       fwrite(bloque,tambloque,1,arch);
   }
   //Lee un bloque desde el archivo
   void* CDiccionario::LeeBloque(long dir)
   {
       void *bloque=malloc(tambloque);
       fseek(arch,dir,SEEK_SET);
       fread(bloque,tambloque,1,arch);
       return bloque;
   }
   //Guarda el nuevo bloque al final del archivo
   long CDiccionario::escribeBloque(void* bloque)
   {
       fseek(arch,0,SEEK_END);
       long direccion=ftell(arch);
       fwrite(bloque,tambloque,1,arch);
       return direccion;
   }
   //Inserta un bloque de manera ordenada segun la clave
   void CDiccionario::InsertaBloque(void *nvo, long dirnvo)
   {
      if(activa.data==-1)
      {
          activa.data=dirnvo;
          reescribeEntidad(this->dir,activa);
          return;
      }
      long actualdir=activa.data;
      long anteriordir=-1;

      while(actualdir!=-1)
      {
          void *actual=LeeBloque(actualdir);
          if(comparaBloques(nvo,actual)<0)
          {
              *((long*)nvo)=actualdir;
              if(anteriordir==-1)
              {
                  activa.data=dirnvo;
                  reescribeEntidad(this->dir,activa);
              }
              else
              {
                  void *anterior=LeeBloque(anteriordir);
                  *((long*)anterior)=dirnvo;
                  reescribeBloque(anterior,anteriordir);
                  free(anterior);
              }
              reescribeBloque(nvo,dirnvo);
              free(actual);
              return;
          }
          anteriordir=actualdir;
          actualdir=*((long*)actual);
          free(actual);
      }
      *((long*)nvo)=-1;
      reescribeBloque(nvo,dirnvo);
      void *anterior=LeeBloque(anteriordir);
      *((long*)anterior)=dirnvo;
      reescribeBloque(anterior,anteriordir);
      free(anterior);
   }
   //Muestra los registros almacenados
void CDiccionario::consultaBloques()
{
    cout<<left<<setw(11)<<"siguiente";
    //Muestra el nombre de los atributos
    for(int i=0; i<nAtributos;i++)
    {
        cout<<left<<setw(15)<< arrAtributos[i].nombre;
    }
    cout<<endl;
    long cab=activa.data;
    int contador=0;
    //Muestra la informacion de cada atributo
    while(cab!=-1 && contador<100)
    {
       void *bloque=LeeBloque(cab);
        cout<<left<<setw(11)<<*((long*)bloque);
        long desp =sizeof(long);
        for(int i=0;i<nAtributos;i++)
        {
           switch (arrAtributos[i].tipo)
           {
               case 1: cout<<left<<setw(11)<<((char*)bloque+desp);
                       break;
               case 2:cout<<left<<setw(11)<<*((int*)((char*)bloque+desp));
                      break;
               case 3:cout<<left<<setw(11)<<*((float*)((char*)bloque+desp));
                      break;
               case 4:cout<<left<<setw(11)<<*((double*)((char*)bloque+desp));
                      break;
               case 5:cout<<left<<setw(11)<<*((long*)((char*)bloque+desp));
                      break;
           }
           cout<<"\t";
           desp+=arrAtributos[i].tamano;
        }
          cout<<endl;
          cab=*((long*)bloque);
          free(bloque);
          contador++;
    }
}
//Busca un bloque con la clave primaria
long CDiccionario::buscaBloque(void *bloquebus)
{
    long cab=activa.data;
    cout << "\nInicio buscaBloque";
    cout << "\nCabecera: " << cab;

    while(cab!=-1)
    {
        cout << "\nLeyendo bloque en: " << cab;
        void* bloqueact=LeeBloque(cab);
        cout << "\nComparando...";

        //Compara bloques con la clave primaria
        if(comparaBloques(bloquebus,bloqueact)==0)
        {
            free(bloqueact);
            cout << "\nBloque encontrado";

            //bloque encontrado
            return cab;
        }
        long siguiente=*((long*)bloqueact);
         cout << "\nSiguiente: " << siguiente;
        //ir al bloque siguiente
        cab=siguiente;

        free(bloqueact);
    }
     cout << "\nNo encontrado";
    //No se encontro el bloque
    return(-1);
}
//modifica un bloque de la lista de bloques
void CDiccionario::modificaBloque()
{    //captura datos del bloque a modificar
     void* bloque;
     bloque = pideClaveBloque();
    //obtiene la direccion de la cabesera de bloques
    long cab=activa.data;
    long ant=-1;
//recorre lista de bloques
    while(cab!=-1)
    {
         void *actual=LeeBloque(cab);//Obtiene la info del bloque actual
         if(comparaBloques(bloque,actual)==0)//compara las claves
         {
             long sig=*((long*)actual);//guardamos la direccion del siguiente bloque
             if(ant==-1)//si se encuentra en el inicio
             {
                 activa.data=sig;//se actualiza la cabecera
                 reescribeEntidad(this->dir,activa);//se actualiza
             }
             else// si esta en medio o al final
             {
                 void *bloqueant=LeeBloque(ant);// lee el bloque anterior
                 *((long*)bloqueant)=sig;//se enlasa el anterior con el siguiente
                 reescribeBloque(bloqueant,ant);//se actualiza el anterior
                 free(bloqueant);
             }
             free(actual);
             //se ingresan los datos del nuevo bloque
             cout<<"\n ingresa los datos nuevos\n";
             void *Nvo=CapturaBloque();
             //se verifica que no exista ya
             if(buscaBloque(Nvo)!=-1)
             {
                 cout<<"\n Este bloque ya existe\n";
                 free(Nvo);
                 free(bloque);
                 return;

             }
             //se inserta al final del archivo
             long dirnvo=escribeBloque(Nvo);
             InsertaBloque(Nvo,dirnvo);//Se inserta ordenadamente
             cout<<"\nBloque modificado\n";
             free(Nvo);
             free(bloque);
             return;
         }
         //Moverse por la lista de bloques
         ant=cab;
         cab=*((long*)actual);
         free(actual);
    }
    //si no se encuentra se libera el bloque a buscar
    cout<<"\n Bloque no encontrado\n";
    free(bloque);
}
//Elimina un bloque
void CDiccionario::bajaBloque()
{
    void*Bloque;
    Bloque=pideClaveBloque();
    eliminaBloque(Bloque);
}
void CDiccionario::eliminaBloque(void*bloque)
{
    long cab=activa.data;//conseguimos la cabecera de la lista
    long ant=-1;
    //Recorremos la lista
    while(cab!=-1)
    {
        void *actual=LeeBloque(cab);//Leemos el bloque actual
        if(comparaBloques(bloque,actual)==0)//lo comparamos con el que buscamos
        {
            long sig=*((long*)actual);//guadamos la direccion del bloque siguiente
            if(ant==-1)//si  esta en el inicio
            {
                activa.data=sig;//actualizamos la cabecera y guardamos el cambio
                reescribeEntidad(this->dir,activa);
            }
            else//si esta n medio o al final
            {
                void *bloqueant=LeeBloque(ant);//Leemos el bloque anterior
                *((long*)bloqueant)=sig;//lo enlasamos con el siguiente
                reescribeBloque(bloqueant,ant);//actualizamos el bloque anterior
                free(bloqueant);
            }
            cout<<"\n Se elimino el bloque \n";

            free(actual);
            free(bloque);
            return;
        }
        //Avanzamos  al bloque siguiente
        ant=cab;
        cab=*((long*)actual);
        free(actual);
    }
    //Si no se encuentra el bloque
    cout<<"\n Bloque no encontrado \n";
    free(bloque);
}
void *CDiccionario::pideClaveBloque()
{
    void *bloque=malloc(tambloque);
    cout<<"Ingrese"<<arrAtributos[0].nombre<<":";
    switch(arrAtributos[0].tipo)
    {
    case 1:
        {
        cin.ignore();
        cin.getline((char*)bloque+sizeof(long),arrAtributos[0].tamano);
        break;
        }
    case 2:
        {
            cin>>*((int*)((char*)bloque+sizeof(long)));
            break;
        }
    case 3:
        {
            cin>>*((float*)((char*)bloque+sizeof(long)));
            break;
        }
    case 4:
        {
            cin>>*((double*)((char*)bloque+sizeof(long)));
            break;
        }
    case 5:
        {
            cin>>*((long*)((char*)bloque+sizeof(long)));
            break;
        }
    }
    return bloque;
}
