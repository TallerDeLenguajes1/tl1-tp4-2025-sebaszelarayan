//bibliotecas
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>

//constantes
#define M 100

//estructuras
typedef struct {
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;
typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;
//funciones
void mostrarLista(Nodo *start);
Nodo * crearlistaVacia();
Nodo *crearNodo(Tarea dato);
void InsertarNodo(Nodo **Start,Nodo *Nodo);

int main()
{
    //variables
    int operador,id_tarea=1000;
    Tarea dato;
    char tareaingresada[M];

    //creo las liastas
    Nodo *TareasPendientes=crearlistaVacia();
    //Nodo *TareasRealizadas=crearlistaVacia();
    do
    {
        printf("\n-----Cargar lista de Pendientes------\n");
        printf("Ingrese la descripcion de la tarea:\n");
        fflush(stdin);
        gets(tareaingresada);
        dato.Descripcion=(char*)malloc(strlen(tareaingresada)+1);
        strcpy(dato.Descripcion,tareaingresada);
        printf("Ingrese la duracion de la tarea:\n");
        fflush(stdin);
        scanf("%d",&dato.Duracion);
        dato.TareaID=id_tarea;

        InsertarNodo(&TareasPendientes,crearNodo(dato));

        
        printf("Desea ingresar otra tarea?\n 1=Si\n 0=No\n");
        fflush(stdin);
        scanf("%d",&operador);
        id_tarea++;
        
    } while (operador!=0);
    mostrarLista(TareasPendientes);
    
    return 0;
}
Nodo * crearlistaVacia(){
    return NULL;
}
Nodo *crearNodo(Tarea dato){
    Nodo * nuevo=(Nodo*)malloc(sizeof(Nodo));
    nuevo->T=dato;
    nuevo->Siguiente=NULL;
    return nuevo;
}
void InsertarNodo(Nodo **start,Nodo *nodo){
    nodo->Siguiente = *start;
    *start=nodo;
}
void mostrarLista(Nodo *start){
    if (start==NULL)
    {
        printf("Lista vacia\n");
    }else
    {
        while (start!=NULL)
        {
            printf("\nID_Tarea: %d\n",start->T.TareaID);
            printf("Descripcion: %s\n",start->T.Descripcion);
            printf("Duracion: %d\n",start->T.Duracion);
            start=start->Siguiente;
        }
        
    }
    
    
    
}