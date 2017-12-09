/* Función simple que nos imprime el contenido de los arrays bidimensionales */

void printeador_matriz(int ** matriz, int tamano_matriz, int num){
  for(int i=0; i < tamano_matriz; i++){
    for(int j=0; j < tamano_matriz-num; j++){
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
}

/* Función que nos imprime la matriz en el formato de la solución solicitada */

void printeador_solucion(int ** solucion, int tamano_matriz){
  
}
