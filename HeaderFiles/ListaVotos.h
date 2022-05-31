#pragma once
#include "Votos.h"
#include "ListaCandidatos.h"

struct ListaVotos
{
    Votos candidato[CANTIDAD_CANDIDATOS];
};

void inicListaVotos();
void actualizarArchivoVotos();