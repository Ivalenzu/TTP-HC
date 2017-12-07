/* Función que se encarga de extraer la matriz de distancias de un texto */

int ** constructor(FILE * archivo, int * aux){

  char * caracter;
  int ** matriz;

  caracter = malloc(80 * sizeof(char));

  fgets(caracter, 80, archivo);

  for(int i=0; caracter[i] != 0; i++){
    if(caracter[i] == 32)
      *aux = *aux + 1;
  }

  rewind(archivo);

  matriz = malloc(*aux * sizeof(int*));
  for(int i=0; i < *aux; i++)
    matriz[i] = malloc(*aux * sizeof(int));

  for(int i=0; i < *aux; i++){
    for(int j=0; j < *aux; j++)
      fscanf(archivo, "%d", &matriz[i][j]);
  }

  free(caracter);

  return matriz;
}


/* Función simple que nos imprime el contenido de los arrays bidimensionales */

void printeador_matriz(int ** matriz, int tamano_matriz){
  for(int i=0; i < tamano_matriz; i++){
    for(int j=0; j < tamano_matriz; j++){
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
}
