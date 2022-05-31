#include <iostream>
#include <windows.h>
#include <string.h>
#include "HeaderFiles/ListaUsuarios.h"
#include "HeaderFiles/ListaCandidatos.h"
#include "HeaderFiles/ListaVotos.h"
using namespace std;

//Archivo y lista de usuarios
FILE *archivoUsuarios;
ListaUsuarios listaUsuarios;

//Archivo y lista de votos
FILE *archivoVotos;
ListaVotos listavotos;

//CADENAS DE FORMATO PARA LECTURA Y ESCRITURA DE ARCHIVOS
const char* FORMATO_USUARIO_OUT = "{\n\t\"nombre\": \"%[^\"]\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%[^\"]\",\n\t\"clave\":%d\n}\n";
const char* FORMATO_USUARIO_IN = "{\n\t\"nombre\": \"%s\",\n\t\"cedula\":%d,\n\t\"edad\":%d,\n\t\"region\": \"%s\",\n\t\"clave\":%d\n}\n";
const char* FORMATO_VOTO_OUT = "{\n\t\"cedula\":%d,\n\t\"voto\":%d,\n}\n";
const char* FORMATO_VOTO_IN = "{\n\t\"cedula\":%d,\n\t\"voto\":%d,\n}\n";

//ARREGLOS CON EL ORDEN DE LOS VOTOS
int arregloVotos[CANTIDAD_CANDIDATOS];
int arregloPosiciones[CANTIDAD_CANDIDATOS];

//Leer los datos del archivo usuarios.txt y guardarlos en la estructura
void inicListaUsuarios(){
    int i=0;
    fopen_s(&archivoUsuarios, "Datos/usuarios.txt", "r+");
    fseek(archivoUsuarios, 0, SEEK_SET);
    int ret = 0;
    while (ret!=EOF){
        ret=fscanf(archivoUsuarios, FORMATO_USUARIO_OUT, listaUsuarios.usuario[i].nombre, &listaUsuarios.usuario[i].cedula, &listaUsuarios.usuario[i].edad, listaUsuarios.usuario[i].region, &listaUsuarios.usuario[i].clave);
        i++;
    }
    fclose(archivoUsuarios);
}

//Iniciar la estructura que guarda los votos de los usuarios
void inicListaVotos(){
    int i=0, cedulaUsuario, voto;
    for (int j=0; j<CANTIDAD_CANDIDATOS; j++){
        listavotos.candidato[j].adulto=0;
        listavotos.candidato[j].joven=0;
        listavotos.candidato[j].mayor=0;
        listavotos.candidato[j].votos=0;
        listavotos.candidato[j].norte=0;
        listavotos.candidato[j].sur=0;
        listavotos.candidato[j].central=0;
    }
    fopen_s(&archivoVotos, "Datos/votos.txt", "r+");
    fseek(archivoVotos, 0, SEEK_SET);
    int ret = 0;
    while (ret!=EOF){
        ret=fscanf(archivoVotos, FORMATO_VOTO_OUT, &cedulaUsuario, &voto);
        if (ret == EOF){
            break;
        }
        for (int j=0; j<CANTIDAD_USUARIOS; j++){
            if (listaUsuarios.usuario[j].cedula == cedulaUsuario){
                listavotos.candidato[voto-1].votos++;
                switch (listaUsuarios.usuario[j].region[0]){
                    case 'C':
                        listavotos.candidato[voto-1].central++;
                        break;
                    case 'N':
                        listavotos.candidato[voto-1].norte++;
                        break;
                    case 'S':
                        listavotos.candidato[voto-1].sur++;
                        break;
                }

                if (listaUsuarios.usuario[j].edad < 30){
                    listavotos.candidato[voto-1].joven++;
                }
                else if (listaUsuarios.usuario[j].edad < 50){
                    listavotos.candidato[voto-1].adulto++;
                }else{
                    listavotos.candidato[voto-1].mayor++;
                }
                break;
            }
        }
        i++;
    }
    fclose(archivoUsuarios);
}

//Imprimir la estructura de usuarios (No necesario)
void mostrarListaUsuario(){
     
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (listaUsuarios.usuario[i].nombre[0] != '\0'){
            cout<<"___________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,2);
            cout <<"|    "<< i+1 <<"                 |"<< endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"___________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,1);
            cout << "| Nombre: " << listaUsuarios.usuario[i].nombre <<" |"<< endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"___________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,3);
            cout << "|  Cedula: " << listaUsuarios.usuario[i].cedula <<" |" <<endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"___________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,4);
            cout << "|  Edad: " << listaUsuarios.usuario[i].edad <<"    |" <<endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"____________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,5);
            cout << "|  Region: " << listaUsuarios.usuario[i].region <<"  |"<< endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"____________________________________"<<endl;
            SetConsoleTextAttribute(hConsole,6);
            cout << "| Clave: " << listaUsuarios.usuario[i].clave <<"  |"<< endl;
            SetConsoleTextAttribute(hConsole,7);
            cout<<"____________________________________"<<endl;
        }
    }
}

//Buscar si la cedula corresponde a un usuario y retornar su clave para validarla
int buscarUsuario(int cedula){
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            return listaUsuarios.usuario[i].clave;
        }
    }
    return -1;
}

//Busca la cedula que corresponde a un usuario y retorna su posicion en el arreglo
int buscarNumeroUsuario(int cedula){
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            return i;
        }
    }
    return -1;
}

//MENU PARA EL USUARIO VOTANTE
void menuVotante(int numeroUsuario){ 
	int op, voto=-1;
    do{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout << "_______________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout << "|SISTEMA DE VOTACION\t\t|" << endl;
        SetConsoleTextAttribute(hConsole,7);
        cout <<"_______________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout << "USUARIO:" << listaUsuarios.usuario[numeroUsuario].cedula << "\n" << listaUsuarios.usuario[numeroUsuario].nombre <<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<< "_______________________________"<<endl;
        SetConsoleTextAttribute(hConsole,5);
        cout << "|Ingrese la opcion que desea\t|"<<endl;
        cout << "|Recuerde guardar su voto\t|"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"_______________________________"<<endl;
        SetConsoleTextAttribute(hConsole,12);
        cout << "|1. Ver candidatos\t\t|" << endl;
        cout << "|2. Votar\t\t\t|" << endl;
        cout << "|3. Cambiar Voto\t\t|" << endl;
        cout << "|4. Guardar voto\t\t|" << endl;
        cout << "|0. Salir (Cerrar sesion)\t|" << endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"_______________________________"<<endl;
        cin>>op;
        system("cls");
        switch (op){
            case 1:
                //funcion que muestra los candidatos
                mostrarListaCandidatos();
                break;
            case 2:
                //funcion que retorna el valor de el voto
                voto = votar();
                break;
            case 3:
                voto = votar();
                break;
            case 4:
                //esta funcion guarda el voto definitivo y solo se podra usar una vez
                if (voto != -1){
                    if (registrarVoto(listaUsuarios.usuario[numeroUsuario].cedula, voto, numeroUsuario) == 0){
                        ganador(2);
                        op = 0;
                    }
                }else{
                    cout << "El usuario aun no ha seleccionado un candidato." << endl;
                }
                break;
            case 0:
                //REGRESAR O SALIR
                cout<<"__________________________"<<endl;
                 SetConsoleTextAttribute(hConsole,1);
                cout << "|   Cerrando sesion...   |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                 cout<<"___________________________"<<endl;
                break;
            default:
                cout<<"________________________________"<<endl;
                 SetConsoleTextAttribute(hConsole,5);
                cout << "| Ingrese una funcion valida  |" << endl;
                 SetConsoleTextAttribute(hConsole,7);
                cout<<"________________________________" <<endl;
        }                         
    }while(op!=0);
}

//MENU PARA EL USUARIO REPORTERO
void menuReportero(){
	int op;
    do{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        cout<<"________________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout<<"|MODO REPORTERO\t\t\t\t|"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"________________________________________"<<endl;
        SetConsoleTextAttribute(hConsole,3);
        cout<<"|Ingrese la opcion que desea:\t\t|"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"________________________________________"<<endl;
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"|1. Candidato con mayoria de votos\t|"<<endl;
        cout<<"|2. Ver tabla de votos actual\t\t|"<<endl;
        cout<<"|3. Ganador por regiones\t\t|"<<endl;
        cout<<"|4. Dos candidatos mejor posicionados\t|"<<endl;
        cout<<"|5. Saber si hay segunda vuelta\t\t|"<<endl;
        cout<<"|0. Salir\t\t\t\t|"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<"________________________________________"<<endl;
        cin>>op;
        system("cls");
        switch (op){
            case 1:
                ganador(0); 
                break;
            case 2:
                mostrarVotos();
                break;
            case 3:
                gpr();
                break;
            case 4:
                ganador(1);
                break;
            case 5:
                segundaVuelta();
                break;
            case 0:
                system("cls");
                cout << "Regresando..." << endl;
                break;
            default:
                cout << "_____________________________"<<endl;
                SetConsoleTextAttribute(hConsole,1);
                cout << "| Ingrese una funcion valida |" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout<<"______________________________"<<endl;
        }      
    }while(op!=0);
}

//REGISTRAR NUEVO USUARIO
void agregarUsuario(){
    char nombre[50];
    int cedula;
    int edad;
    char region[30];
    int clave;

    cout << "Ingrese el nombre del nuevo usuario: ";
    fflush(stdin);
    gets(nombre);
    cout << "Ingrese la cedula: ";
    fflush(stdin);
    cin >> cedula;
    cout << "Ingrese la edad: ";
    fflush(stdin);
    cin >> edad;
    cout << "Ingrese la region del nuevo usuario: ";
    fflush(stdin);
    gets(region);
    cout << "Ingrese la clave: ";
    fflush(stdin);
    cin >> clave;

    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] == '\0'){
           for (int j=0; j<strlen(nombre); j++){
               listaUsuarios.usuario[i].nombre[j] = nombre[j];
           }
           for (int j=0; j<strlen(region); j++){
               listaUsuarios.usuario[i].region[j] = region[j];
           }
            listaUsuarios.usuario[i].cedula = cedula;
            listaUsuarios.usuario[i].edad = edad;
            listaUsuarios.usuario[i].clave = clave;
            break;
        }
    }
    actualizarArchivo();
}

//ELIMINAR USUARIO DE LA ESTRUCTURA
void eliminarUsuario(){
    int cedula;
    cout << "Ingrese la cedula a eliminar: ";
    cin >> cedula;

    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            cout << "Corresponde a: " << listaUsuarios.usuario[i].nombre << endl;
            cout << "Desea eliminarlo? (1. Si, 2. No)" << endl;
            cin >> cedula;
            if (cedula == 1){
                listaUsuarios.usuario[i].nombre[0] = '\0';
                listaUsuarios.usuario[i].region[0] = '\0';
                listaUsuarios.usuario[i].cedula = 0;
                listaUsuarios.usuario[i].edad = 0;
                system("cls");
                cout << "Eliminado exitosamente" << endl;
                break; 
            }
            else{
                system("cls");
                cout << "No se elimino el usuario" << endl;
            }
        }
        if (i==CANTIDAD_USUARIOS-1){
            cout << "No se encontro la cedula" << endl;
        }
    }
    actualizarArchivo();
}

//CAMBIAR LA CLAVE DE UN USUARIO
void cambiarClave(){
    int cedula, clave;
    cout << "Ingrese la cedula: ";
    cin >> cedula;

    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0' && listaUsuarios.usuario[i].cedula == cedula){
            cout << "Corresponde a: " << listaUsuarios.usuario[i].nombre << endl;
            cout << "Desea cambiar su clave? (1. Si, 2. No)" << endl;
            cin >> cedula;
            if (cedula == 1){
                cout << "Ingrese su nueva clave: ";
                cin >> clave;
                listaUsuarios.usuario[i].clave = clave;
                system("cls");
                cout << "Clave cambiada exitosamente" << endl;
                break;
            }
            else{
                system("cls");
                cout << "No se elimino el usuario" << endl;
                break;
            }
        }
        if (i==CANTIDAD_USUARIOS-1){
            cout << "No se encontro la cedula" << endl;
        }
    }
    actualizarArchivo();
}

//ACTUALIZAR ARCHIVO DE USUARIOS
void actualizarArchivo(){
    fopen_s(&archivoUsuarios, "Datos/usuarios.txt", "w+");
    fseek(archivoUsuarios, 0, SEEK_SET);
    for (int i=0; i<CANTIDAD_USUARIOS; i++){
        if (listaUsuarios.usuario[i].nombre[0] != '\0'){
            fprintf_s(archivoUsuarios, FORMATO_USUARIO_IN, listaUsuarios.usuario[i].nombre, listaUsuarios.usuario[i].cedula, listaUsuarios.usuario[i].edad, listaUsuarios.usuario[i].region, listaUsuarios.usuario[i].clave);
        }
    }
    fclose(archivoUsuarios);
}

//PREGUNTAR POR QUE CANDIDATO VA A VOTAR Y VALIDAR
int votar(){
    int voto;
    mostrarListaCandidatos();
    cout << endl << "Seleccione su candidato: ";
    cin >> voto;
    system("cls");
    if (voto >= 1 && voto <= 4){
        cout << "Usted esta votando por: " << voto << endl;
        return voto;
    }else{
        cout << "Ingrese un voto valido" << endl;
        return -1;
    }
}

//GUARDA EL VOTO EN LA ESTRUCTURA Y EN EL ARCHIVO votos.txt
int registrarVoto(int cedula, int voto, int numeroUsuario){
    int cedulaYaUsada, votoUsado, i=0;
    fopen_s(&archivoVotos, "Datos/votos.txt", "r+");
    fseek(archivoVotos, 0, SEEK_SET);
    int ret = 0;
    while (ret!=EOF){
        ret=fscanf(archivoVotos, FORMATO_VOTO_OUT, &cedulaYaUsada, &votoUsado);
        i++;
        if (cedulaYaUsada == cedula){
            cout << "Este usuario ya ha votado, su voto fue por el candidato: " << votoUsado << endl;
            fclose(archivoVotos);
            return -1;
        }
    }
    fclose(archivoUsuarios);
    listavotos.candidato[voto-1].votos++;
    //FALTA VERIFICAR SU EDAD Y REGION
    switch (listaUsuarios.usuario[numeroUsuario].region[0]){
        case 'C':
            listavotos.candidato[voto-1].central++;
            break;
        case 'N':
            listavotos.candidato[voto-1].norte++;
            break;
        case 'S':
            listavotos.candidato[voto-1].sur++;
            break;
    }

    if (listaUsuarios.usuario[numeroUsuario].edad < 30){
        listavotos.candidato[voto-1].joven++;
    }
    else if (listaUsuarios.usuario[numeroUsuario].edad < 50){
        listavotos.candidato[voto-1].adulto++;
    }else{
        listavotos.candidato[voto-1].mayor++;
    }

    fopen_s(&archivoVotos, "Datos/votos.txt", "at+");
    fseek(archivoVotos, 0, SEEK_END);
    fprintf_s(archivoVotos, FORMATO_VOTO_IN, cedula, voto);
    fclose(archivoVotos);
    cout << "Voto registrado exitosamente, cerrando sesion..." << endl;
    return 0;
}

//IMPRIME UNO O DOS CANDIDATOS CON MAS VOTOS
void ganador(int n){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int temp, pos;
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        arregloVotos[i] = listavotos.candidato[i].votos;
        arregloPosiciones[i] = i;
    }
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        temp = arregloVotos[i];
        pos = i;
        for (int j=i-1; j>=0; j--){
            if (arregloVotos[j] < temp){
                arregloVotos[j+1] = arregloVotos[j];
                pos = j;
            }else{
                pos = j+1;
                break;
            }
        }
        if (pos != i){
            arregloVotos[i] = arregloVotos[pos];
            arregloVotos[pos] = temp;

            temp = arregloPosiciones[i];
            arregloPosiciones[i] = arregloPosiciones[pos];
            arregloPosiciones[pos] = temp;
        }
    }

    //Segun el valor de n, imprime los dos candidatos que van a segunda vuelta o solamente el ganador
    switch (n){
        case 0:
            cout << "_____________________________"<< endl;
            SetConsoleTextAttribute(hConsole,10);
            cout << "Ganador: ";
            getNombre(arregloPosiciones[0]);
            SetConsoleTextAttribute(hConsole,7);
            cout<<"______________________________"<< endl;
            break;
        case 1:
            cout << "_____________________________"<< endl;
            SetConsoleTextAttribute(hConsole,10);
            cout << "Dos mas votados: " << endl;
            getNombre(arregloPosiciones[0]);
            getNombre(arregloPosiciones[1]);
            SetConsoleTextAttribute(hConsole,7);
            cout<<"______________________________"<< endl;
            break;
        case 2:
            //SOLAMENTE ORDENA LOS ARREGLOS Y NO IMPRIME NADA
            break;
    }
}

//MUESTRA LA LISTA DE LOS VOTOS DE CADA CANDIDATO
void mostrarVotos(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        cout << "_____________________________"<< endl;
        SetConsoleTextAttribute(hConsole,10);
        cout << i+1 << ". ";
        getNombre(i);

        SetConsoleTextAttribute(hConsole,11);
        cout << "Numero de votos: " << listavotos.candidato[i].votos << endl;
        cout << endl << "Numero de votos por region: " << endl;
        cout << "Central: " << listavotos.candidato[i].central << endl;
        cout << "Norte: " << listavotos.candidato[i].norte << endl;
        cout << "Sur: " << listavotos.candidato[i].sur << endl;
        cout << endl << "Numero de votos por edad: " << endl;
        cout << "Joven: " << listavotos.candidato[i].joven << endl;
        cout << "Adulto: " << listavotos.candidato[i].adulto << endl;
        cout << "Mayor: " << listavotos.candidato[i].mayor << endl;
        SetConsoleTextAttribute(hConsole,7);
    }
    cout << "_____________________________"<< endl;
}

//FUNCIONES DE GANADOR POR CADA REGION
void gpr(){
    ganaRegionN();
    ganaRegionC();
    ganaRegionS();
}

//GANADOR REGION NORTE
void ganaRegionN(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int arregloRegion[CANTIDAD_CANDIDATOS];
    int arregloPosRegion[CANTIDAD_CANDIDATOS];
    int temp, pos;
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        arregloRegion[i] = listavotos.candidato[i].norte;
        arregloPosRegion[i] = i;
    }
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        temp = arregloRegion[i];
        pos = i;
        for (int j=i-1; j>=0; j--){
            if (arregloRegion[j] < temp){
                arregloRegion[j+1] = arregloRegion[j];
                pos = j;
            }else{
                pos = j+1;
                break;
            }
        }
        if (pos != i){
            arregloRegion[i] = arregloRegion[pos];
            arregloRegion[pos] = temp;

            temp = arregloPosRegion[i];
            arregloPosRegion[i] = arregloPosRegion[pos];
            arregloPosRegion[pos] = temp;
        }
    }
    cout << "_____________________________"<< endl;
    SetConsoleTextAttribute(hConsole,10);
    cout << "Ganador norte: ";
    getNombre(arregloPosRegion[0]);
    SetConsoleTextAttribute(hConsole,7);
    cout<<"______________________________"<< endl;
}

//GANADOR REGION CENTRAL
void ganaRegionC(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int arregloRegion[CANTIDAD_CANDIDATOS];
    int arregloPosRegion[CANTIDAD_CANDIDATOS];
    int temp, pos;
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        arregloRegion[i] = listavotos.candidato[i].central;
        arregloPosRegion[i] = i;
    }
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        temp = arregloRegion[i];
        pos = i;
        for (int j=i-1; j>=0; j--){
            if (arregloRegion[j] < temp){
                arregloRegion[j+1] = arregloRegion[j];
                pos = j;
            }else{
                pos = j+1;
                break;
            }
        }
        if (pos != i){
            arregloRegion[i] = arregloRegion[pos];
            arregloRegion[pos] = temp;

            temp = arregloPosRegion[i];
            arregloPosRegion[i] = arregloPosRegion[pos];
            arregloPosRegion[pos] = temp;
        }
    }
    cout << "_____________________________"<< endl;
    SetConsoleTextAttribute(hConsole,10);
    cout << "Ganador centro: ";
    getNombre(arregloPosRegion[0]);
    SetConsoleTextAttribute(hConsole,7);
    cout<<"______________________________"<< endl;

}

//GANADOR REGION SUR
void ganaRegionS(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int arregloRegion[CANTIDAD_CANDIDATOS];
    int arregloPosRegion[CANTIDAD_CANDIDATOS];
    int temp, pos;
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        arregloRegion[i] = listavotos.candidato[i].sur;
        arregloPosRegion[i] = i;
    }
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        temp = arregloRegion[i];
        pos = i;
        for (int j=i-1; j>=0; j--){
            if (arregloRegion[j] < temp){
                arregloRegion[j+1] = arregloRegion[j];
            }else{
                pos = j+1;
                break;
            }
        }
        if (pos != i){
            arregloRegion[i] = arregloRegion[pos];
            arregloRegion[pos] = temp;

            temp = arregloPosRegion[i];
            arregloPosRegion[i] = arregloPosRegion[pos];
            arregloPosRegion[pos] = temp;
        }
    }
    cout << "_____________________________"<< endl;
    SetConsoleTextAttribute(hConsole,10);
    cout << "Ganador sur: ";
    getNombre(arregloPosRegion[0]);
    SetConsoleTextAttribute(hConsole,7);
    cout<<"______________________________"<< endl;
}

//HISTOGRAMA
void segundaVuelta(){
    int totalVotos=0;
    float porcentaje;
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        totalVotos+=listavotos.candidato[i].votos;
    }

    //ACA VA EL HISTOGRAMA
    for (int i=0; i<CANTIDAD_CANDIDATOS; i++){
        cout << i << ". ";
        getNombre(i);

        //LO HICE ASI PARA QUE NO HAYA PROBLEMAS ENTRE LOS TIPOS INT Y FLOAT
        porcentaje = 0.0;
        porcentaje+=listavotos.candidato[i].votos;
        porcentaje/=totalVotos;
        porcentaje*=100;
        cout << "Porcentaje: " << porcentaje << "%" << endl;
    }
}