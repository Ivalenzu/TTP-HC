int funcion_evaluadora(int ** solucion, int ** distancias, int tamano_matriz){
    int total = 0;
    for(int i = 0; i < tamano_matriz-1; i++){ /* Fechas */
      for(int j = 0; j < tamano_matriz; j++){ /* Equipos */
          if(i == 0){
            if(solucion[j][i] < 0)
              total = total + distancias[j][(-solucion[j][i])-1];
          }
          else{
            if(solucion[j][i-1] > 0){
              if(solucion[j][i] < 0)
                total = total + distancias[j][(-solucion[j][i])-1];
            }
            else{
              if(solucion[j][i] < 0)
                total = total + distancias[(-solucion[j][i-1])-1][(-solucion[j][i])-1];
              else
                total = total + distancias[(-solucion[j][i-1])-1][solucion[j][i]-1];
            }
          }
      }
    }
    return total;
}
