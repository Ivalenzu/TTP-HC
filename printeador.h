/* Función simple que nos imprime el contenido de los arrays bidimensionales */

void printeador_matriz(int ** matriz, int tamano_matriz, int num){
  for(int i=0; i < tamano_matriz; i++){
    for(int j=0; j < tamano_matriz-num; j++){
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
}

void * clean(char * lector){
  for(int i = 0; i < 130; i++)
    lector[i] = 0;
}

/* Función que nos imprime la matriz en el formato de la solución solicitada */

void printeador_solucion(int ** solucion, int tamano_matriz, char ** equipos){

  printf("Slot    ");
  for(int i=0; i < tamano_matriz; i++){
    for(int j=0; j < 3; j++){
      printf("%c", equipos[i][j]);
    }
    printf("    ");
  }

  printf("\n\n");
  for(int i = 0; i < tamano_matriz-1; i++){
    if(i >= 10)
      printf("%d      ", i);
    else
      printf("%d       ",i);
    for(int j = 0; j < tamano_matriz; j++){
      if(solucion[j][i] < 0)
        printf("@%c%c%c   ", equipos[(-solucion[j][i])-1][0], equipos[(-solucion[j][i])-1][1], equipos[(-solucion[j][i])-1][2]);
      else
        printf("%c%c%c    ", equipos[solucion[j][i]-1][0], equipos[solucion[j][i]-1][1], equipos[solucion[j][i]-1][2]);
    }
    printf("\n");
  }
}
