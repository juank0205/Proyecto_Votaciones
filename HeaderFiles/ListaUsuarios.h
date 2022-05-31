#pragma once
#include "Usuario.h"
#define CANTIDAD_USUARIOS 100

//BASE DE DATOS DE USUARIOS VOTANTES
struct ListaUsuarios
{
    Usuario usuario[CANTIDAD_USUARIOS];
};

//INICIAR LISTAS
void inicListaUsuarios();
void inicListaVotos();
void mostrarListaUsuario();

//BUSCAR PARA INICIAR SESION
int buscarUsuario(int cedula);
int buscarNumeroUsuario(int cedula);

//MENUS
void menuVotante(int numeroUsuario);
void menuReportero();

//MODIFICAR USUARIOS
void agregarUsuario();
void eliminarUsuario();
void cambiarClave();
void actualizarArchivo();

//VOTACION
int votar();
int registrarVoto(int cedula, int voto, int numeroUsuario);

//FUNCIONES REPORTERO
void mostrarVotos();
void ganador(int n);
void gpr();
void ganaRegionN();
void ganaRegionC();
void ganaRegionS();
int segundaVuelta();
void gpe();
void ganaEdadJ();
void ganaEdadA();
void ganaEdadM();