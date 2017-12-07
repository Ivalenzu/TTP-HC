#include <stdio.h>
#include <stdlib.h>

int main(){

  int ** matriz;

  matriz = malloc(4 * sizeof(int *));
  for(int i = 0; i < 4; i++)
    matriz[i] = malloc(4 * sizeof(int));

  matriz[0][0] = 1;
  matriz[0][1] = 2;
  matriz[1][0] = 3;

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++)
      printf("%d ", matriz[i][j]);
    printf("\n");
  }
}
