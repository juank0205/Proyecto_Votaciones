#pragma once
#define CANTIDAD_ADMINISTRADORES 10
#include "Administrador.h"

struct ListaAdministradores
{
    Administrador administradores[CANTIDAD_ADMINISTRADORES];
};


//INICIAR LISTAS
void iniciarListaAdmin();
void mostrarListaAdmin();

//BUSCAR PARA INICIAR SESION
int buscarAdmin(int cedula);
int buscarNumeroAdmin(int cedula);
void menuAdmin(int numeroUsuario);
void administrarUsuarios();
void administrarCandidatos();