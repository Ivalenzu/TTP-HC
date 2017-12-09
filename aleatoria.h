/* Esta función revisa si el equipo actual y el rival ya fueron escogidos para así revisar los restantes */

int helper(int tamano_matriz, int ** fila, int j, int rand_rival){
  for(int k = 0; k < tamano_matriz; k++){
    for(int l = 0; l < 2; l++){
      if(fila[k][l] == rand_rival || fila[k][l] == j){
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
  int ** initial = malloc(tamano_matriz * sizeof(int *));
  int ** fila = malloc(tamano_matriz * sizeof(int *));
  int ** columna = malloc(tamano_matriz * sizeof(int *));

/* Asignando memoria */

  for(int i = 0; i < tamano_matriz; i++){
    fila[i] = malloc(2 *sizeof(int));
    initial[i] = malloc((tamano_matriz-1) * sizeof(int));
    columna[i] = malloc((tamano_matriz-1) * sizeof(int));
  }

/* Rellenando con ceros */

  for(int k = 0; k < tamano_matriz; k++){
    for(int l = 0; l < tamano_matriz-1; l++){
      initial[k][l] = 0;
      columna[k][l] = 0;
    }
  }

  /* Debe ser un Double Robin Tournament
     No deben jugar los mismos equipos más de una vez en la misma rueda
     Máximo de 3 Home Stand and Road Trip

              Fechas[i]
               - - -
Equipos[j]     - - -
               - - -
               - - -

      */

  for(int i = 0; i < tamano_matriz-1; i++){
    tolerancia = 0;
    for(int k = 0; k < tamano_matriz; k++){
      for(int l = 0; l < 2; l++)
        fila[k][l] = 0;
    }
    if(aux2){
      for(int k = 0; k < tamano_matriz; k++)
          columna[k][i] = 0;
      aux2=0;
    }

    for(int j = 1; j <= tamano_matriz; j++){
      aux = 1;
      rand_rival = rand() % tamano_matriz + 1;

      /* Esta función revisa que el equipo j no haya jugado en alguna fecha anterior con rand_rival */
      for(int l = 0; l < tamano_matriz-1; l++){
        if(columna[j-1][l] == rand_rival){
          aux = 0;
          j = j-1;
          tolerancia = tolerancia + 1;
          break;
        }
      }
      if(aux){
        aux = 1;
        /* Esta función ayuda a evitar que se repita un equipo en una fecha */
        if(helper(tamano_matriz,fila,j,rand_rival)){
          /* Puede que coincida con un equipo anterior pero solo el rival, el actual aún no posee enfrentamiento */
          if(initial[j-1][i] == 0){
            j = j-1;
            tolerancia = tolerancia + 1;
          }
        }
        /* Puede ser que el rival sea el mismo al cual estamos intentando emparejar, por lo que se debe probar de nuevo*/
        else if(rand_rival == j){
          j = j-1;
          tolerancia = tolerancia + 1;
        }

        else{
          rand_local = rand() % 2 + 1;
          if (rand_local == 1){
            initial[j-1][i] = rand_rival;
            initial[rand_rival-1][i] = -(j);
            columna[j-1][i] = rand_rival;
            columna[rand_rival-1][i] = j;
            fila[j-1][0] = rand_rival;
            fila[j-1][1] = j;
          }
          else{
            initial[j-1][i] = -rand_rival;
            initial[rand_rival-1][i] = j;
            columna[j-1][i] = rand_rival;
            columna[rand_rival-1][i] = j;
            fila[j-1][0] = rand_rival;
            fila[j-1][1] = j;
          }
        }
      }
      if(tolerancia > 30){
        i = i-1;
        aux2 = 1;
        break;
      }
    }
  }

  for(int i = 0; i < tamano_matriz; i++){
    free(columna[i]);
    free(fila[i]);
  }
  free(columna);
  free(fila);

  return initial;
}
