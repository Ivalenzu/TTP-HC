int helper(int tamano_matriz, int ** fila, int j, int rand_rival){
  for(int k = 0; k < tamano_matriz; k++){
    for(int l = 0; l < 2; l++){
      if(fila[k][l] == rand_rival || fila[k][l] == j){
        printf("c");
        return 1;
      }
    }
  }
  return 0;
}

int ** generador(int tamano_matriz){

  int rand_rival;
  int rand_local;
  int aux;
  int aux2 = 0;
  int tolerancia;
  int ** initial = malloc((tamano_matriz-1) * sizeof(int *));
  int ** fila = malloc(tamano_matriz * sizeof(int*));
  int ** columna = malloc(tamano_matriz * sizeof(int*));

/* Asignando memoria */

  for(int i = 0; i < tamano_matriz; i++)
    fila[i] = malloc(2 *sizeof(int));

  for(int i = 0; i < tamano_matriz; i++)
    columna[i] = malloc((tamano_matriz-1) *sizeof(int));

  for(int i = 0; i < tamano_matriz-1; i++){
    initial[i] = malloc((tamano_matriz-1) * sizeof(int));
  }

/* Rellenando con ceros */

  for(int k = 0; k < tamano_matriz-1; k++){
    for(int l = 0; l < tamano_matriz-1; l++)
      initial[k][l] = 0;
  }

  for(int k = 0; k < tamano_matriz; k++){
    for(int l = 0; l < tamano_matriz-1; l++)
      columna[k][l] = 0;
  }

  /* Debe ser un Double Robin Tournament
     No deben jugar los mismos equipos más de una vez en la misma rueda
     Máximo de 3 Home Stand and Road Trip */

  for(int i = 0; i < tamano_matriz-1; i++){
    tolerancia = 0;
    for(int k = 0; k < tamano_matriz-1; k++){
      for(int l = 0; l < 2; l++)
        fila[k][l] = 0;
    }
    if(aux2){
      for(int k = 0; k < tamano_matriz; k++){
          printf("asdasdasd%d ", columna[k][i]);
          columna[k][i] = 0;}
      aux2=0;
    }

    if(i == 1){
      for(int i = 0; i < tamano_matriz; i++){
        for(int j = 0; j < tamano_matriz-1; j++)
          printf("%d ", columna[i][j]);
        printf("\n");
      }
    }

    for(int j = 1; j <= tamano_matriz; j++){
      printf("Iteracion %d ", j);
      aux = 1;
      rand_rival = rand() % tamano_matriz + 1;
      printf("Rival: %d ", rand_rival);
      if(j == 4 && i == 1){
        printf("\n");
        for(int i = 0; i < tamano_matriz; i++){
          for(int j = 0; j < tamano_matriz-1; j++)
            printf("%d ", columna[i][j]);
          printf("\n");
        }
      }
      tolerancia = tolerancia + 1;
      printf("%d ", tolerancia);
      for(int l = 0; l < tamano_matriz; l++){
        if(columna[j-1][l] == rand_rival){
          printf("%d %d ", columna[j-1][l],l);
          printf(" d ");
          aux = 0;
          j = j-1;
        }
      }
      if(aux){
        aux = 1;
        if(helper(tamano_matriz,fila,j,rand_rival)){
          if(initial[i][j-1] == 0){
            j = j-1;
            printf(" a ");
            continue;
          }
        }

        else if(rand_rival == j){
          j = j-1;
          printf(" b ");
        }

        else{
          rand_local = rand() % 2 + 1;
          printf("Local: %d \n", rand_local);
          if (rand_local == 1){
            initial[i][j-1] = rand_rival;
            initial[i][rand_rival-1] = -(j);
            columna[j-1][i] = rand_rival;
            columna[rand_rival-1][i] = j;
            fila[j-1][0] = rand_rival;
            fila[j-1][1] = j;
          }
          else{
            initial[i][j-1] = -rand_rival;
            initial[i][rand_rival-1] = j;
            columna[j-1][i] = rand_rival;
            columna[rand_rival-1][i] = j;
            fila[j-1][0] = rand_rival;
            fila[j-1][1] = j;
          }
        }
      }
      if(tolerancia > 80){
        i = i-1;
        aux2 = 1;
        break;
      }
    }
  }

  for(int i = 0; i < tamano_matriz; i++)
    free(columna[i]);
  free(columna);

  return initial;
}
