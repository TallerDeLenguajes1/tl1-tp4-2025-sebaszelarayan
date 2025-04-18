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
void eliminarNodo(Nodo **star,Nodo *nodo);
void InsertarNodo(Nodo **Start,Nodo *Nodo);
Nodo * BuscarNodoId(Nodo ** Start,int ID);
Nodo * BuscarNodoPalabra(Nodo ** Start,char *palabra);

int main()
{
    //variables
    int operador,id_inicial=1000,id_ingresado,op_tarea,op_busqueda;
    Tarea dato;
    char tareaingresada[M],*clave;

    Nodo *buscado;

    //creo las liastas
    Nodo *TareasPendientes=crearlistaVacia();
    Nodo *TareasRealizadas=crearlistaVacia();
    do
    {
        printf("\nOperaciones\n 0 = Salir del Programa\n 1 = Cargar Listas de pendientes\n 2 = Marcar Tareas Realizadas\n 3 = Mostrar Listas \n 4 = Consultar Tarea\n");
        fflush(stdin);
        scanf("%d",&operador);
        switch (operador)
        {
        case 0:
            printf("Saliendo del programa ....\n");
            break;
            
        case 1:
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
                dato.TareaID=id_inicial;
                InsertarNodo(&TareasPendientes,crearNodo(dato));
                printf("Desea ingresar otra tarea?\n 1=Si\n 0=No\n");
                fflush(stdin);
                scanf("%d",&op_tarea);
                id_inicial++;

            } while (op_tarea);
            break;
        case 2:
            
            printf("\nIngrese el ID de la tarea realizada:\n");
            fflush(stdin);
            scanf("%d",&id_ingresado);
            //busco la tarea en cuestion y agrego a la lista de realizados creando un nuevo nodo
            InsertarNodo(&TareasRealizadas,crearNodo((BuscarNodoId(&TareasPendientes,id_ingresado))->T));
            //elimino el nodo de la lista de pendientes 
            eliminarNodo(&TareasPendientes,BuscarNodoId(&TareasPendientes,id_ingresado));
            break;
        case 3:
            printf("\nTareas Pendientes:\n");
            mostrarLista(TareasPendientes);
            printf("\nTareas Realizadas:\n");
            mostrarLista(TareasRealizadas);
            
            break;
        case 4:
            do
            {
                printf("Ingrese: \n 0 = Salir de Busqueda\n 1 = busqueda por id\n 2 = busqueda por palabra clave\n");
                scanf("%d",&op_busqueda);
                switch (op_busqueda)
                {
                case 1:
                    printf("\nIngrese el ID de la tarea Buscada:\n");
                    fflush(stdin);
                    scanf("%d",&id_ingresado);
                    
                    if (BuscarNodoId(&TareasPendientes,id_ingresado))
                    {
                        printf("Pertenece a Lista de Tareas Pendiente\n");
                        buscado=BuscarNodoId(&TareasPendientes,id_ingresado);
                    }else
                    {
                        printf("Pertenece a Lista de Tareas Realizadas\n");
                        buscado=BuscarNodoId(&TareasRealizadas,id_ingresado);
                    }
                    //muestra la tarea
                    mostrarLista(buscado);
                    break;
                
                case 2:
                    printf("\nIngrese la Palabra Clave de la tarea Buscada:\n");
                    fflush(stdin);
                    gets(tareaingresada);
                    clave=(char*)malloc(strlen(tareaingresada)+1);
                    strcpy(clave,tareaingresada);

                    if (BuscarNodoPalabra(&TareasPendientes,clave))
                    {
                        printf("Pertenece a Lista de Tareas Pendiente");
                        buscado=BuscarNodoPalabra(&TareasPendientes,clave);
                    }else
                    {
                        printf("Pertenece a Lista de Tareas Realizadas");
                        buscado=BuscarNodoPalabra(&TareasRealizadas,clave);
                    }
                    //muestra la tarea
                    mostrarLista(buscado);
                    break;
                }
            } while (op_busqueda!=0);
            
            break;
        }
        
    } while (operador!=0);
    
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
        printf("\nLista vacia\n");
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
void eliminarNodo(Nodo **star,Nodo *nodo){
    Nodo ** aux=star; // Usamos un puntero doble para apuntar al puntero actual.
    // Iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista.
    while (*aux != NULL && (*aux)->T.TareaID != nodo->T.TareaID) {
        aux = &(*aux)->Siguiente;
    }
    // Si encontramos el nodo con el t especificado, lo eliminamos.
    if (*aux) {
        Nodo *temp = *aux;  // Guardamos el nodo a eliminar en una variable temporal.
        *aux = (*aux)->Siguiente;  // Desvinculamos el nodo de la lista.
        free(temp);  // Liberamos la memoria ocupada por el nodo.
    }
}
Nodo * BuscarNodoId(Nodo ** Start,int ID)
{
    Nodo * Aux = *Start;
    while (Aux && Aux->T.TareaID != ID)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}
Nodo * BuscarNodoPalabra(Nodo ** Start,char *palabra)
{
    Nodo * Aux = *Start;
    while (Aux && strstr(Aux->T.Descripcion,palabra)==NULL)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}