#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generator.h"
#include "matriz.h"

int main(int argc, char *argv[]){

/* --- Se toma la matriz de distancias y se guarda en un array bidimensional */

  int tamano_matriz = 1;
  FILE * archivo;
  int ** matriz;

  archivo = fopen(argv[1], "r");

  matriz = constructor(archivo, &tamano_matriz);

/* --- Se comienza a generar la solución random que será la inicial para Hill Climbing */

  int ** initial;

  initial = generador(tamano_matriz);

  printf("\n");

  for(int i = 0; i < tamano_matriz-1; i++){
    for(int j = 0; j < tamano_matriz; j++)
      printf("%d ", initial[i][j]);
    printf("\n");
  }

/* Parte del codigo donde se libera la memoria dinámica y se cierran archivos */

  for(int i=0; i < tamano_matriz; i++)
    free(matriz[i]);
  free(matriz);

  for(int i = 0; i < tamano_matriz-1; i++)
    free(initial[i]);
  free(initial);

  fclose(archivo);

  return 0;
}
