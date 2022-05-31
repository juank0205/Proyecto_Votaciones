#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "HeaderFiles/ListaAdministradores.h"
#include "HeaderFiles/ListaUsuarios.h"
using namespace std;

FILE *archivoAdmin;
ListaAdministradores listaAdministradores;

//CADENAS DE FORMATO PARA LECTURA DE ARCHIVOS
const char* FORMATO_ADMIN_OUT = "{\n\t\"nombre\": \"%[^\"]\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%[^\"]\",\n\t\"clave\":%d\n}\n";

//Leer los datos del archivo administradores.txt y guardarlos en la estructura
void iniciarListaAdmin(){
    int i=0;
    fopen_s(&archivoAdmin, "Datos/administradores.txt", "r+");
    fseek(archivoAdmin, 0, SEEK_SET);
    int ret = 0;
    while (ret!=EOF){
        ret=fscanf(archivoAdmin, FORMATO_ADMIN_OUT, listaAdministradores.administradores[i].nombre, &listaAdministradores.administradores[i].cedula, &listaAdministradores.administradores[i].edad, listaAdministradores.administradores[i].region, &listaAdministradores.administradores[i].clave);
        i++;
    }
    fclose(archivoAdmin);
}

//Imprimir la estructura de administradores (No necesario)
void mostrarListaAdmin(){
    for (int i=0; i<CANTIDAD_ADMINISTRADORES; i++){
        if (listaAdministradores.administradores[i].nombre[0]!='\0'){
             HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            cout << "________________________________________________"<< endl;
            SetConsoleTextAttribute(hConsole,12);
            cout << "|"<<i+1 << "." <<"|"<< endl;
            cout << "|Nombre: " << listaAdministradores.administradores[i].nombre <<"|"<< endl;
            cout << "|Cedula: " << listaAdministradores.administradores[i].cedula <<"|"<< endl;
            cout << "|Edad: " << listaAdministradores.administradores[i].edad <<"|"<< endl;
            cout << "|Region: " << listaAdministradores.administradores[i].region <<"|"<< endl;
            cout << "|Clave: " << listaAdministradores.administradores[i].clave <<"|"<< endl;
            cout << "_________________________________________________" << endl;
        }
        else{
            break;
        }
    }
}

//Buscar si la cedula coincide con un administrador y retornar su clave para validarla
int buscarAdmin(int cedula){
    for (int i=0; i<CANTIDAD_ADMINISTRADORES; i++){
        if (listaAdministradores.administradores[i].nombre[0] != '\0' && listaAdministradores.administradores[i].cedula == cedula){
            return listaAdministradores.administradores[i].clave;
        }
    }
    return -1;
}

//Busca la cedula que coincide con un administrador y retorna su posicion en el arreglo
int buscarNumeroAdmin(int cedula){
    for (int i=0; i<CANTIDAD_ADMINISTRADORES; i++){
        if (listaAdministradores.administradores[i].nombre[0] != '\0' && listaAdministradores.administradores[i].cedula == cedula){
            return i;
        }
    }
    return -1;
}

//MENU PARA EL USUARIO ADMINISTRADOR
void menuAdmin(int numeroUsuario){ 
    
    int op;
    do{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout<<"________________________________" << endl;
        SetConsoleTextAttribute(hConsole,3);
        cout << "|MODO ADMINISTRADOR\t\t|" << endl;
        SetConsoleTextAttribute(hConsole,3);
        cout << "|No. " << listaAdministradores.administradores[numeroUsuario].cedula << "\t" << listaAdministradores.administradores[numeroUsuario].nombre <<"|" <<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"________________________________" << endl;
        SetConsoleTextAttribute(hConsole,12);
        cout << "|1. Administrar Usuarios\t|" << endl;
        cout << "|2. Ver estadisticas\t\t|" << endl;
        cout << "|3. Finalizar votaciones\t| " << endl;
        cout << "|4. Reiniciar votaciones\t| " << endl;
        cout << "|0. Salir\t\t\t|" << endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"__________________________________"<<endl;

        cin >> op;
        system("cls");
        switch (op){
            case 1:
                administrarUsuarios();
                break;
            case 2:
                menuReportero();
                break;
            case 3:
                if (segundaVuelta() == 1){
                    cout << "_____________________________"<<endl;
                    SetConsoleTextAttribute(hConsole,1);
                    cout << "Hay segunda vuelta" << endl;
                    SetConsoleTextAttribute(hConsole,7);
                    cout<<"______________________________"<<endl;
                    ganador(1);
                }else{
                    cout << "_____________________________"<<endl;
                    SetConsoleTextAttribute(hConsole,1);
                    cout << "No hay segunda vuelta" << endl;
                    SetConsoleTextAttribute(hConsole,7);
                    cout<<"______________________________"<<endl;
                    ganador(0);
                }
                system("pause");
                exit(EXIT_SUCCESS);
                break;
            case 4:
                reiniciarVotos();
                break;
            case 0:
                //REGRESAR O SALIR
                cout<<"________________________________________"<<endl;
                SetConsoleTextAttribute(hConsole,4);
                cout << "| Saliendo del modo adminstrador...\t|" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout<<"________________________________________"<<endl;
                break;
            default:
                cout<<"__________________________________"<<endl;
                SetConsoleTextAttribute(hConsole,2);
                cout << "|  Ingrese una funcion válida\t|" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout<<"__________________________________"<<endl;

        }
    }while (op!=0);
}

//MENU DE ADMINISTRAR USUARIOS
void administrarUsuarios(){
    int op;
    do{
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout << "____________________________"<<endl;
         SetConsoleTextAttribute(hConsole,14);
        cout << "|ADMINISTRAR USUARIOS      |" << endl;
        cout << "|1. Agregar usuario        |" << endl;
        cout << "|2. Eliminar usuario       |" << endl;
        cout << "|3.Cambiar clave de usuario|" << endl;
        cout << "|0. Volver                 |" << endl;
        cout << "____________________________" << endl;
        
        cin >> op;
        system("cls");
        switch(op){
            case 1:
                agregarUsuario();
                system("cls");
                 cout << "________________________________"<<endl;
                 SetConsoleTextAttribute(hConsole,15);
                cout << "| Usuario agregado exitosamente |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                cout << "________________________________"<< endl;
                break;
            case 2:
                eliminarUsuario();
                break;
            case 3:
                cambiarClave();
                mostrarListaUsuario();
                break;
            case 0:
                system("cls");
                cout << "_________________"<<endl;
                 SetConsoleTextAttribute(hConsole,14);
                cout << "| Regresando... |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                cout << "_________________"<<endl;
                break;
            default:
                cout << "_____________________________" << endl;
                 SetConsoleTextAttribute(hConsole,14);
                cout << "| Ingrese una opcion valida |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                cout << "_____________________________" << endl;
        }
    }while(op!=0);
}

//MENU ADMINISTRAR CANDIDATOS - NO SE USA
void administrarCandidatos(){
    int op;
    do{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout << "__________________________" << endl;
         SetConsoleTextAttribute(hConsole,14); 
        cout << "| ADMINISTRAR CANDIDATOS |" << endl;
        cout << "| 1. Agregar candidato   |" << endl;
        cout << "| 2. Eliminar candidato  |" << endl;
        cout << "| 0. Volver              |" << endl;
        SetConsoleTextAttribute(hConsole,7);
        cout << "__________________________" << endl;
        cin >> op;
        system("cls");
        switch(op){
            case 1:
                //agregarCandidato();
                system("cls");
                 cout << "___________________________________" << endl;
                 SetConsoleTextAttribute(hConsole,14);
                cout << "| Candidato agregado exitosamente |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                cout << "___________________________________" << endl;
                break;
            case 2:
                
                break;
            case 0:
                system("cls");
                cout << "_________________" << endl;
                 SetConsoleTextAttribute(hConsole,14);
                cout << "| Regresando... |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                cout << "_________________" << endl;
                break;
            default:
                 cout << "_____________________________" << endl;
                 SetConsoleTextAttribute(hConsole,14);
                cout << "| Ingrese una opcion valida |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                cout << "_____________________________" << endl;
        }
    }while(op!=0);
}