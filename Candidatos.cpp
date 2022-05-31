#include <iostream>
#include <windows.h>
#include <string.h>
#include "HeaderFiles/ListaCandidatos.h"
using namespace std;

FILE *archivoCandidatos;
ListaCandidatos listaCandidatos;

//CADENA DE FORMATO PARA LECTURA DE ARCHIVOS
const char* FORMATO_CANDIDATO_OUT = "{\n\t\"presidente\":\"%[^\"]\",\n\t\"vicepresidente\":\"%[^\"]\",\n\t\"partido\":\"%[^\"]\",\n\t\"votos\":%d\n}\n";

//Leer los datos del archivo candidatos.txt y guardarlos en la estructura
void iniciarListaCandidatos(){
    int i=0; 
    fopen_s(&archivoCandidatos, "Datos/candidatos.txt", "r+");
    fseek(archivoCandidatos, 0, SEEK_SET);
    int ret=0;
    while (ret!=EOF){
        ret = fscanf(archivoCandidatos, FORMATO_CANDIDATO_OUT, listaCandidatos.candidatos[i].presidente, listaCandidatos.candidatos[i].vicepresidente, listaCandidatos.candidatos[i].partido, &listaCandidatos.candidatos[i].votos);
        i++;
    }
    fclose(archivoCandidatos);
}

//MOSTRAR LA ESTRUCTURA DE CANDIDATOS
void mostrarListaCandidatos(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            
    cout << "_________________________________________________________________"<<endl;
    SetConsoleTextAttribute(hConsole,12);
    cout << "|  Opcion numero 1        |     |       Opcion numero 2        |" <<endl;      
    cout << "|Presidente: " << listaCandidatos.candidatos[0].presidente <<"|\t" <<"|Presidente: " << listaCandidatos.candidatos[1].presidente <<"|\t"<<endl;
    cout << "|Vicepre:  "  << listaCandidatos.candidatos[0].vicepresidente <<"|\t"<<"|Vicepre:    " << listaCandidatos.candidatos[1].vicepresidente <<"      |\t"<< endl;
    cout << "|Partido:  " << listaCandidatos.candidatos[0].partido <<"|\t"<<"|Partido: " << listaCandidatos.candidatos[1].partido <<"  |\t"<< endl;
    //cout << "Votos: " << listaCandidatos.candidatos[i].votos << endl;
    SetConsoleTextAttribute(hConsole,7);
    cout << "__________________________________________________________________"<<endl;
    SetConsoleTextAttribute(hConsole,13);
    cout << "|  Opcion numero 3         |    |      Opcion numero 4         |" <<endl;  
    cout << "|Presidente: " << listaCandidatos.candidatos[2].presidente <<"|\t" <<"|Presidente: " << listaCandidatos.candidatos[3].presidente <<"    |\t"<<endl;
    cout << "|Vicepre:  "  << listaCandidatos.candidatos[2].vicepresidente <<"|\t"<<"|Vicepre: " << listaCandidatos.candidatos[3].presidente <<"       |\t"<< endl;
    cout << "|Partido:  " << listaCandidatos.candidatos[2].partido <<"|\t"<<"|Partido:  " << listaCandidatos.candidatos[3].presidente <<"      |\t"<< endl;
    SetConsoleTextAttribute(hConsole,7);
    cout << "__________________________________________________________________"<<endl;
    cout << "Opicon numero 5: Voto en blanco" << endl;
}

//RETORNA EL NOMBRE DEL CANDIDATO EN CUESTION
void getNombre(int pos){
    cout << listaCandidatos.candidatos[pos].presidente << endl;
}