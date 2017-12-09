#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aleatoria.h"
#include "matriz.h"
#include "printeador.h"

int main(int argc, char *argv[]){

/* --- Se toma la matriz de distancias y se guarda en un array bidimensional */

  int tamano_matriz = 1;
  FILE * archivo;
  int ** matriz;
  int ** initial;
  int selector;

  archivo = fopen(argv[1], "r");

  /* PORFAVOR IGNACIO ACUERDATE DE CAMBIAR ESTO AL INDICE CORRECTO PARA LA ENTREGA: Debería ser 1 */

  if(argv[1][11] == 'L')
    selector = 0;
  else if(argv[1][11] == 'F')
    selector = 1;
  else if(argv[1][11] == 'u')
    selector = 2;

  matriz = constructor(archivo, &tamano_matriz);

/* --- Se comienza a generar la solución random que será la inicial para Hill Climbing */

  initial = generador(tamano_matriz);

  printeador_matriz(initial,tamano_matriz,1);

/* Parte del codigo donde se libera la memoria dinámica y se cierran archivos */

  for(int i=0; i < tamano_matriz; i++){
    free(matriz[i]);
    free(initial[i]);
  }
  free(matriz);
  free(initial);

  fclose(archivo);

  return 0;
}
