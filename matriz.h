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

char ** nombres(int selector, int tamano_matriz){

  FILE * archivo;
  char ** equipos;
  char * lector;
  int k = selector;

  archivo = fopen("ciudades.txt", "r");
  equipos = malloc(tamano_matriz * sizeof(char*));
  lector = malloc(300 * sizeof(char));

  for(int i = 0; i < tamano_matriz; i++)
    equipos[i] = malloc(3 * sizeof(char));

    fgets(lector, 245, archivo);

  for(int i = 0; i < tamano_matriz; i++){
    if((int)lector[k] == 32)
      k++;
    for(int j = 0; j < 3; j++){
      if((int)lector[k] == 32)
        equipos[i][j] = 32;
      else{
        equipos[i][j] = lector[k];
        k++;
      }
    }
  }

  free(lector);
  fclose(archivo);

  return equipos;
}
