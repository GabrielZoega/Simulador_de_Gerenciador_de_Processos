#ifndef ESTADOBLOQUEADO_H
#define ESTADOBLOQUEADO_H

#include "fila.h"

// Fila dos processos Bloqueados
typedef struct EstadoBloqueado {
    TFila processosB;
} EstadoBloqueado;

#endif