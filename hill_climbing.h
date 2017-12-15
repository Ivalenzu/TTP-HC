int funcion_evaluadora(int ** solucion, int ** distancias, int tamano_matriz){
    int total = 0;
    for(int i = 0; i < (tamano_matriz-1)*2 ; i++){ /* Fechas */
      for(int j = 1; j <= tamano_matriz; j++){ /* Equipos */
          if(i == 0){
            if(solucion[j-1][i] < 0)
              total = total + distancias[j-1][abs(solucion[j-1][i])-1];
          }
          else{
            if(solucion[j-1][i-1] > 0 && solucion[j-1][i] < 0)
              total = total + distancias[(solucion[j-1][i-1])-1][abs(solucion[j-1][i])-1];
            else if(solucion[j-1][i-1] < 0)
              total = total + distancias[abs(solucion[j-1][i-1])-1][abs(solucion[j-1][i])-1];
          }
      }
    }
    for(int j = 1; j <= tamano_matriz; j++){
      if(solucion[j-1][(tamano_matriz-1)*2-1] < 0)
        total = total + distancias[j-1][abs(solucion[j-1][(tamano_matriz-1)*2-1])-1];
    }
    return total;
}

/* Funciones esenciales de Hill-Climbing */

void swap_localidad(int ** solucion, int equipo, int fecha, int tamano_matriz){
  solucion[equipo][fecha] = solucion[equipo][fecha]*(-1);
  solucion[abs(solucion[equipo][fecha])-1][fecha] = solucion[abs(solucion[equipo][fecha])-1][fecha]*(-1);
  for(int i = tamano_matriz-1; i < (tamano_matriz-1)*2; i++){
    if(solucion[equipo][i] == solucion[equipo][fecha]){
      solucion[abs(solucion[equipo][i])-1][i] = solucion[abs(solucion[equipo][i])-1][i]*(-1);
      solucion[equipo][i] = solucion[equipo][i]*(-1);
      break;
    }
  }
}

void swap_fechas(int ** solucion, int tamano_matriz, int fecha1, int fecha2){
  int * auxiliar = calloc(tamano_matriz, sizeof(int));

  for(int i = 0; i < tamano_matriz; i++)
    auxiliar[i] = solucion[i][fecha1];

  for(int i = 0; i < tamano_matriz; i++){
    solucion[i][fecha1] = solucion[i][fecha2];
    solucion[i][fecha2] = auxiliar[i];
  }

  free(auxiliar);
}

void swap_emparejamiento(int ** solucion, int tamano_matriz, int * equipos, int * fechas){
  int * auxiliar = calloc(2, sizeof(int));

  auxiliar[0] = solucion[equipos[1]-1][fechas[1]];
  auxiliar[1] = solucion[abs(solucion[equipos[1]-1][fechas[1]])-1][fechas[1]];

  solucion[abs(solucion[equipos[1]-1][fechas[1]])-1][fechas[1]] = solucion[abs(solucion[equipos[0]-1][fechas[0]])-1][fechas[0]];
  solucion[equipos[1]-1][fechas[1]] = solucion[equipos[0]-1][fechas[0]];

  solucion[abs(solucion[equipos[0]-1][fechas[0]])-1][fechas[0]] = auxiliar[1];
  solucion[equipos[0]-1][fechas[0]] = auxiliar[0];

  free(auxiliar);
}

int restriccion_columna(int ** solucion_nueva, int tamano_matriz){
  int cumple = 1;
  int cumple2 = 1;
  int ** auxiliar = calloc(2,sizeof(int*));
  auxiliar[0] = calloc(tamano_matriz, sizeof(int));
  auxiliar[1] = calloc(tamano_matriz, sizeof(int));

  for(int i = 0; i < tamano_matriz;i++){
    if(abs(solucion_nueva[i][tamano_matriz-2]) == abs(solucion_nueva[i][tamano_matriz-1])){
      cumple = 0;
      cumple2 = 0;
      break;
    }
  }

  while(cumple2){
    for(int i = 0; i < tamano_matriz; i++){
      for(int a = 0; a < tamano_matriz; a++){
        auxiliar[0][a] = 0;
        auxiliar[1][a] = 0;
      }
      for(int j = 0; j < (tamano_matriz-1); j++){
        if(abs(solucion_nueva[i][j]) == i+1){
          cumple = 0;
          cumple2 = 0;
        }
        else
          auxiliar[0][abs(solucion_nueva[i][j])-1]++;
      }
      for(int j = (tamano_matriz-1); j < (tamano_matriz-1)*2; j++){
        if(abs(solucion_nueva[i][j]) == i+1){
          cumple = 0;
          cumple2 = 0;
        }
        else
          auxiliar[1][abs(solucion_nueva[i][j])-1]++;
      }
      for(int j=0; j < tamano_matriz; j++){
          if(auxiliar[0][j] > 1 || auxiliar[1][j] > 1){
            cumple = 0;
            cumple2 = 0;
          }
      }
    }
    cumple2=0;
  }

  free(auxiliar[0]);
  free(auxiliar[1]);
  free(auxiliar);
  return cumple;
}

int restriccion_seguidas(int ** solucion_nueva, int tamano_matriz, int pareja1 , int pareja2, int tipo){
  int cumple = 1;
  int ** evaluador = calloc(2, sizeof(int *));
  evaluador[0] = calloc(2, sizeof(int));
  evaluador[1] = calloc(2, sizeof(int));

  if(tipo){
    for(int i = 0; i < (tamano_matriz-1)*2; i++){
      if(evaluador[0][0] > 3 || evaluador[0][1] > 3 || evaluador[1][0] > 3 || evaluador[1][1] > 3){
        cumple = 0;
        break;
      }
      else{
        if(solucion_nueva[pareja1-1][i] > 0){
          if(evaluador[0][0] == 3){
            cumple = 0;
            break;
          }
          else{
            if(evaluador[0][0] == 0){
              evaluador[0][1] = 0;
              evaluador[0][0] = 1;
            }
            else
              evaluador[0][0]++;
          }
        }
        else{
          if(evaluador[0][1] == 3){
            cumple = 0;
            break;
          }
          else{
            if(evaluador[0][1] == 0){
              evaluador[0][1] = 1;
              evaluador[0][0] = 0;
            }
            else
              evaluador[0][1]++;
          }
        }
        if(solucion_nueva[pareja2-1][i] > 0){
          if(evaluador[1][0] == 3){
            cumple = 0;
            break;
          }
          else{
            if(evaluador[1][0] == 0){
              evaluador[1][1] = 0;
              evaluador[1][0] = 1;
            }
            else
              evaluador[1][0]++;
          }
        }
        else{
          if(evaluador[1][1] == 3){
            cumple = 0;
            break;
          }
          else{
            if(evaluador[1][1] == 0){
              evaluador[1][1] = 1;
              evaluador[1][0] = 0;
            }
            else
              evaluador[1][1]++;
          }
        }
      }
    }
  }
  else{
    for(int j = 0; j < (tamano_matriz-1)*2; j++){
      if(evaluador[0][0] > 3 || evaluador[0][1] > 3){
        cumple = 0;
        break;
      }
      else{
        if(solucion_nueva[pareja1-1][j] > 0){
          if(evaluador[0][0] == 3){
            cumple = 0;
            break;
          }
          else{
            if(evaluador[0][0] == 0){
              evaluador[0][0] = 1;
              evaluador[0][1] = 0;
            }
            else
              evaluador[0][0]++;
          }
        }
        else{
          if(evaluador[0][1] == 3){
            cumple = 0;
            break;
          }
          else{
            if(evaluador[0][1] == 0){
              evaluador[0][1] = 1;
              evaluador[0][0] = 0;
            }
            else
              evaluador[0][1]++;
          }
        }
      }
    }
  }

  free(evaluador[0]);
  free(evaluador[1]);
  free(evaluador);

  return cumple;
}

int restriccion_fila(int ** solucion_nueva, int tamano_matriz){

  int * auxiliar = calloc(tamano_matriz, sizeof(int));
  int cumple = 1;
  int cumple2 = 0;

  for(int i = 0; i <(tamano_matriz-1)*2; i++){
    for(int h = 0; h < tamano_matriz; h++)
      auxiliar[h] = 0;
    for(int j = 0; j < tamano_matriz; j++){
       auxiliar[abs(solucion_nueva[j][i])-1]++;
    }
    for(int j = 0; j < tamano_matriz; j++){
      if(auxiliar[j] > 1 || (solucion_nueva[j][i])*(solucion_nueva[abs(solucion_nueva[j][i])-1][i]) > 0){
        cumple = 0;
        cumple2 = 1;
        break;
      }
    }
    if(cumple2)
      break;
  }

  free(auxiliar);
  return cumple;
}

int hc_localidad(int ** solucion_inicial, int ** distancias, int tamano_matriz){
  int min_dist = funcion_evaluadora(solucion_inicial, distancias, tamano_matriz);
  int pareja1;
  int pareja2;
  int dist_aux;
  int interruptor = 0;
  int interruptor2 = 1;
  int swaps = 0;
  int iteraciones = 0;

  int ** matriz_aux = calloc(tamano_matriz, sizeof(int *));
  for(int i = 0; i < tamano_matriz; i++)
    matriz_aux[i] = calloc(tamano_matriz*2, sizeof(int));

  for(int i = 0; i < (tamano_matriz-1)*2; i++){
    for(int j = 0; j < tamano_matriz; j++)
      matriz_aux[j][i] = solucion_inicial[j][i];
  }
  while(1){
    interruptor2 = 1;
    for(int i = 0; i < (tamano_matriz-1)*2; i++){
      for(int j = 1; j <= tamano_matriz; j++){
        iteraciones++;
        swap_localidad(matriz_aux,j-1,i,tamano_matriz);
        pareja1 = j;
        pareja2 = abs(matriz_aux[j-1][i]);
        if(restriccion_seguidas(matriz_aux,tamano_matriz,pareja1,pareja2,1)){
          dist_aux = funcion_evaluadora(matriz_aux,distancias,tamano_matriz);
          if(dist_aux < min_dist){
            min_dist = dist_aux;
            for(int h = 0; h < (tamano_matriz-1)*2; h++){
              for(int k = 0; k < tamano_matriz; k++)
                solucion_inicial[k][h] = matriz_aux[k][h];
            }
            interruptor = 1;
            swaps++;
            break;
          }
        }
        else{
          for(int h = 0; h < (tamano_matriz-1)*2; h++){
            for(int k = 0; k < tamano_matriz; k++)
              matriz_aux[k][h] = solucion_inicial[k][h];
          }
        }
      }
      if(interruptor){
        interruptor = 0;
        interruptor2 = 0;
        break;
      }
    }
    if(interruptor2)
      break;
  }

  for(int j = 0; j < tamano_matriz; j++)
    free(matriz_aux[j]);
  free(matriz_aux);

  printf("\nSwaps: %d\n", swaps);
  printf("Iteraciones: %d\n", iteraciones);

  return min_dist;
}

int hc_fecha(int ** solucion_inicial, int ** distancias, int tamano_matriz){
  int min_dist = funcion_evaluadora(solucion_inicial, distancias, tamano_matriz);
  int dist_aux;
  int interruptor = 0;
  int interruptor2 = 1;
  int swaps = 0;
  int homestand = 0;
  int iteraciones = 1;

  int ** matriz_aux = calloc(tamano_matriz, sizeof(int *));
  for(int i = 0; i < tamano_matriz; i++)
    matriz_aux[i] = calloc(tamano_matriz*2, sizeof(int));

  while(1){
    interruptor2 = 1;
    for(int i = 0; i < (tamano_matriz-1)*2; i++){
      for(int j = 0; j < (tamano_matriz-1)*2; j++){
        iteraciones++;
        if(i != j){
          swap_fechas(matriz_aux,tamano_matriz,i,j);
          for(int a = 0; a < tamano_matriz; a++){
            if(restriccion_seguidas(matriz_aux,tamano_matriz,a+1,0,0)){
              homestand = 1;
            }
            else{
              homestand = 0;
              break;
            }
          }
          if(restriccion_columna(matriz_aux,tamano_matriz) && homestand){
            dist_aux = funcion_evaluadora(matriz_aux,distancias,tamano_matriz);
            if(dist_aux < min_dist){
              min_dist = dist_aux;
              for(int h = 0; h < (tamano_matriz-1)*2; h++){
                for(int k = 0; k < tamano_matriz; k++)
                  solucion_inicial[k][h] = matriz_aux[k][h];
              }
              interruptor = 1;
              swaps++;
              break;
            }
          }
          else{
            for(int h = 0; h < (tamano_matriz-1)*2; h++){
              for(int k = 0; k < tamano_matriz; k++)
                matriz_aux[k][h] = solucion_inicial[k][h];
            }
          }
        }
      }
      if(interruptor){
        interruptor = 0;
        interruptor2 = 0;
        break;
      }
    }
    if(interruptor2)
      break;
  }

  for(int j = 0; j < tamano_matriz; j++)
    free(matriz_aux[j]);
  free(matriz_aux);

  printf("\nSwaps: %d\n", swaps);
  printf("Iteraciones: %d\n", iteraciones);

  return min_dist;
}

int hc_emparejamiento(int ** solucion_inicial, int ** distancias, int tamano_matriz){
  int min_dist = funcion_evaluadora(solucion_inicial, distancias, tamano_matriz);
  int * equipos = calloc(2, sizeof(int));
  int * fechas = calloc(2, sizeof(int));
  int dist_aux;
  int restr_seguidas = 0;
  int interruptor = 0;
  int special = 0;
  int interruptor2 = 1;
  int swaps = 0;
  int iteraciones = 0;

  int ** matriz_aux = calloc(tamano_matriz, sizeof(int *));
  for(int i = 0; i < tamano_matriz; i++)
    matriz_aux[i] = calloc(tamano_matriz*2, sizeof(int));

  for(int i = 0; i < (tamano_matriz-1)*2; i++){
    for(int j = 0; j < tamano_matriz; j++)
      matriz_aux[j][i] = solucion_inicial[j][i];
  }

  while(1){
    interruptor2 = 1;
    special = 0;
    for(int i = 0; i < (tamano_matriz-1)*2; i++){
      for(int j = 1; j <= tamano_matriz; j++){
        for(int k = 0; k < (tamano_matriz-1)*2; k++){
          for(int l = 1; l <= tamano_matriz; l++){
            iteraciones++;
            equipos[0] = j;
            equipos[1] = l;
            fechas[0] = i;
            fechas[1] = k;
            swap_emparejamiento(matriz_aux,tamano_matriz,equipos,fechas);
            for(int p = 1; p <= tamano_matriz;p++){
              if(restriccion_seguidas(matriz_aux,tamano_matriz,p,0,0))
                restr_seguidas = 1;
              else{
                restr_seguidas = 0;
                break;
              }
            }
            if(restriccion_fila(matriz_aux,tamano_matriz) && restriccion_columna(matriz_aux,tamano_matriz) && restr_seguidas){
              dist_aux = funcion_evaluadora(matriz_aux,distancias,tamano_matriz);
              if(min_dist > dist_aux){
                min_dist = dist_aux;
                for(int a = 0; a < (tamano_matriz-1)*2; a++){
                  for(int b = 0; b < tamano_matriz; b++)
                    solucion_inicial[b][a] = matriz_aux[b][a];
                }
                interruptor = 1;
                special = 1;
                swaps++;
                break;
              }
            }
            else{
              for(int a = 0; a < (tamano_matriz-1)*2; a++){
                for(int b = 0; b < tamano_matriz; b++)
                  matriz_aux[b][a] = solucion_inicial[b][a];
              }
            }
          }
          if(interruptor){
            interruptor = 0;
            interruptor2 = 0;
            break;
          }
        }
        if(special)
          break;
      }
      if(special)
        break;
    }
    if(interruptor2)
      break;
  }

  printf("\nSwaps: %d\n", swaps);
  printf("Iteraciones: %d\n", iteraciones);

  for(int j = 0; j < tamano_matriz; j++)
    free(matriz_aux[j]);
  free(matriz_aux);

  free(equipos);
  free(fechas);
  return min_dist;
}
