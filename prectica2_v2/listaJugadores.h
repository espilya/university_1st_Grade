﻿#ifndef _listaJugadores
#define _listaJugadores
#include "jugador.h"
#include <fstream>


const int MAX_JUGADORES = 10;
typedef tJugador tListaJugadores[MAX_JUGADORES];

//inicializa lista a una lista vacía.
void creaListaVacia(tListaJugadores & lista);

//guarda en lista el contenido del archivo listaJugadores.txt; devuelve un booleano que indica si la carga se ha podido realizar.
bool cargar(tListaJugadores & lista);

//visualiza por pantalla la lista de jugadores dada.
void mostrar(const tListaJugadores & lista);

//almacena en el archivo listaJugadores.txt el contenido de lista y devuelve un valor
//booleano indicando si la acción fue posible.Debe respetar el formato indicado para el archivo.
bool guardar(const tListaJugadores & lista);

//solicita que se introduzca el identificador de un jugador por teclado y se
//actualiza su información en lista.La actualización puede consistir en
//aumentar su puntuación con los nuevos puntos obtenidos(si el jugador se
//	encontraba ya en la lista) o en incorporarlo a la lista con la puntuación
//	obtenida(si no está llena).
void puntuarJugador(tListaJugadores & lista, int puntos);

//busca al jugador con identificador id en lista; devuelve true y la posición(pos)
//en la que se encuentra si el jugador está en la lista; devuelve false y la posición(pos) en la que debería estar si el jugador no está en la
//lista.Debe implementar una búsqueda binaria.
bool buscar(const tListaJugadores & lista, string id, int &pos);

//devuelve una copia de la lista dada ordenada por ranking (decrecientemente por puntos, y a igualdad de puntos crecientemente por identificador).
tListaJugadores ordenarPorRanking(const tListaJugadores &lista);


#endif
