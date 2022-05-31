#include <iostream>
#include <windows.h>
#include "HeaderFiles/ListaAdministradores.h"
#include "HeaderFiles/ListaCandidatos.h"
#include "HeaderFiles/ListaUsuarios.h"
using namespace std;

    

//VALIDAR QUE SOLO SE INGRESEN ENTEROS
int get_int(void)
{    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;

    char str[5];
    char* end;
    int num;
    do{
        GetConsoleMode(hStdInput, &mode);
        SetConsoleMode(hStdInput, mode & (~ENABLE_ECHO_INPUT));

        fgets(str,5,stdin);
        fflush(stdin);
        num=strtol(str,&end,10);
        if(!(*end))
            return num;
        else
        {
            cout << endl;
            system("cls");
            cout<<"__________________________________________"<<endl,
             SetConsoleTextAttribute(hConsole,2);
            puts("| Ingrese una clave numerica de 4 digitos |");
            cout << endl;
             SetConsoleTextAttribute(hConsole,7);
            cout<<"___________________________________________"<<endl;
            num=0;
        }
    }while(num==0);
}

//FUNCION PARA OBTENER LA CONTRASEÑA
int capturarClave(){
    HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;

    GetConsoleMode(hStdInput, &mode);
    SetConsoleMode(hStdInput, mode & (~ENABLE_ECHO_INPUT));

    int clave = get_int();

    cout << endl;
    SetConsoleMode(hStdInput, mode);

    return clave;
}


//INICIAR SESION Y VALIDAR TIPO DE USUARIO
void inicSesion(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int cedula, clave, claveIngresada, op;
    int numeroUsuario;
    bool sesionIniciada = false;
    do {
        op = 0;
        cout<< "______________________"<<endl;
         SetConsoleTextAttribute(hConsole,3);
        cout << "| Ingrese su cedula: |" << endl;
         SetConsoleTextAttribute(hConsole,7);
         cout<<"______________________"<<endl;

        fflush(stdin);
        cin >> cedula;
        fflush(stdin);

        clave = buscarAdmin(cedula); //Revisar si la cedula corresponde a un admin
        numeroUsuario = buscarNumeroAdmin(cedula);
        if (clave != -1){
            cout<<"______________________"<<endl;
             SetConsoleTextAttribute(hConsole,3);
            cout << "| Ingrese su clave: |"<<endl;;
             SetConsoleTextAttribute(hConsole,7);
             cout<<"______________________"<<endl;
            claveIngresada = capturarClave();

            if (claveIngresada == clave){
                system("cls");
                menuAdmin(numeroUsuario);
                sesionIniciada = true;
            }else{
                system("cls");
                cout << "______________________" << endl;
                SetConsoleTextAttribute(hConsole,12);
                cout << "| Clave incorrecta, intente de nuevo |" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout<<"______________________"<<endl;
            }
        }else{
            cout << "________________________" << endl;
            SetConsoleTextAttribute(hConsole,3);
            cout << "| Ingrese su clave:  |"<<endl;
            SetConsoleTextAttribute(hConsole,7);
            cout << "______________________" << endl;
            clave = buscarUsuario(cedula); //Revisar si la cedula corresponde a un usuario
            numeroUsuario = buscarNumeroUsuario(cedula);
            
            if (clave != -1){
                claveIngresada = capturarClave();
                if (claveIngresada == clave){
                    system("cls");
                    menuVotante(numeroUsuario);
                    sesionIniciada = true;
                }else{
                    system("cls");
                    cout << "______________________" <<endl;
                    SetConsoleTextAttribute(hConsole,3);
                    cout << "| Clave incorrecta, intente de nuevo |" << endl;
                    SetConsoleTextAttribute(hConsole,7);
                    cout << "______________________" << endl;
                }
            }else{
                system("cls");
                cout<<"____________________________________________________________________________"<<endl;
                SetConsoleTextAttribute(hConsole,3);
                cout << "| No se encuentra la cedula, Desea ingresar como reportero? (0. No, 1. Si) |" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout << "____________________________________________________________________________" << endl;
                cin >> op;
                if (op==1){
                    system("cls");
                    menuReportero();
                }
                system("cls");
            }
        }
    }while(sesionIniciada == false);
}

//MENU PRINCIPAL
void menuPrincipal(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int op;
    do{
        cout<<  "______________________"<<endl;
        SetConsoleTextAttribute(hConsole, 3);
        cout << "|PROTOTIPO VOTACIONES|" << endl;
        SetConsoleTextAttribute(hConsole,7);
        cout<<  "______________________"<<endl;
        SetConsoleTextAttribute(hConsole,12);
        cout << "|1. Iniciar sesion   |"<<endl;
        cout << "|0. Salir            |"<<endl;
        SetConsoleTextAttribute(hConsole,7);
        cout << "______________________"<<endl;
        cin >> op;
        system("cls");
        switch(op){
            case 1:
                system("cls");
                inicSesion();
                break;
            case 0:
                cout <<"______________________" <<endl;
                SetConsoleTextAttribute(hConsole,4);
                cout << "|   Adios           |" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout <<"______________________"<<endl;
                break;
            default:
                cout<<  "______________________"<<endl;
                SetConsoleTextAttribute(hConsole,5);
                cout << "| Ingrese una opcion valida |" << endl;
                SetConsoleTextAttribute(hConsole,7);
                cout<<"____________________________";
        }
    }while(op!=0);
    
}

//FUNCION PRINCIPAL
int main(){
    iniciarListaAdmin();
    inicListaUsuarios();
    iniciarListaCandidatos();
    inicListaVotos();
    
    menuPrincipal();

    //mostrarListaAdmin();
    //mostrarListaUsuario();
    //mostrarListaCandidatos();

    system("pause");
    return 0;
}