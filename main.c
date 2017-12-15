#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <ctype.h>
#include "aleatoria.h"
#include "matriz.h"
#include "hill_climbing.h"
#include "printeador.h"

int main(int argc, char *argv[]){

/* --- Se toma la matriz de distancias y se guarda en un array bidimensional */

  int tamano_matriz = 1;
  FILE * archivo;
  int ** distancias;
  int estatico = 0;
  int ** initial;
  int ** auxiliar;
  char ** equipos;
  int dist_final;
  int selector=0;
  int restart = 0;
  struct timeval t_ini, t_fin;
  double secs;

  archivo = fopen(argv[1], "r");
  printf("\nIngrese 0 si quiere una semilla estatica, 1 al contrario: ");
  scanf("%d", &estatico);

  if(estatico){
    printf("\nDecida la cantidad de restarts a utilizar: ");
    scanf("%d", &restart);
  }
  /* PORFAVOR IGNACIO ACUERDATE DE CAMBIAR ESTO AL INDICE CORRECTO PARA LA ENTREGA: Debería ser 1 */

  if(argv[1][11] == 'L')
    selector = 0;
  else if(argv[1][11] == 'u')
    selector = 61;
  else if(argv[1][11] == 'F')
    selector = 117;

  distancias = constructor(archivo, &tamano_matriz);

  auxiliar = calloc(tamano_matriz,sizeof(int*));
  for(int i=0; i<tamano_matriz;i++)
    auxiliar[i] = calloc(tamano_matriz*2,sizeof(int));
/* --- Se comienza a generar la solución random que será la inicial para Hill Climbing */
  if(estatico)
    initial = generador(tamano_matriz,1);
  else
    initial = generador(tamano_matriz,0);

  equipos = nombres(selector,tamano_matriz);

  gettimeofday(&t_ini, NULL);
  if(estatico){
    for(int i = 0; i < restart; i++){
      if(i == 0){
        dist_final = hc_fecha(initial,distancias,tamano_matriz);
        for(int j = 0; j < (tamano_matriz-1)*2;j++){
          for(int k = 0; k < tamano_matriz; k++)
            auxiliar[k][j] = initial[k][j];
        }
      }
      else{
        for(int j=0; j < tamano_matriz; j++)
          free(initial[j]);
        free(initial);
        initial = generador(tamano_matriz,1);
        dist_final = hc_emparejamiento(initial,distancias,tamano_matriz);
        if(dist_final < funcion_evaluadora(auxiliar,distancias,tamano_matriz)){
          for(int j = 0; j < (tamano_matriz-1)*2;j++){
            for(int k = 0; k < tamano_matriz; k++)
              auxiliar[k][j] = initial[k][j];
          }
        }
      }
    }
  }
  else
    dist_final = hc_emparejamiento(initial,distancias,tamano_matriz);
  /*dist_final = hc_fecha(initial,distancias,tamano_matriz);
  *//*dist_final = hc_localidad(initial,distancias,tamano_matriz);
  */gettimeofday(&t_fin, NULL);

  secs = timeval_diff(&t_fin,&t_ini);

  printf("%.16g milisegundos\n", secs * 1000.0);
  printf("Distancia: %d\n", dist_final);
  printeador_solucion(initial,tamano_matriz,equipos);

/* Parte del codigo donde se libera la memoria dinámica y se cierran archivos */

  for(int i=0; i < tamano_matriz; i++){
    free(distancias[i]);
    free(equipos[i]);
    free(initial[i]);
    free(auxiliar[i]);
  }

  free(auxiliar);
  free(distancias);
  free(initial);
  free(equipos);

  fclose(archivo);

  return 0;
}
