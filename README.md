--README--

Ejecución del programa:

  1) Primero se escoje el tipo de semilla. Si se elije 0, se utilizará la función rand() normal,
     la cual genera siempre los mismos números aleatorios. Esto es útil para comprobar las soluciones.
     Si se escoje 1, la semilla dependerá de la hora del computador, por lo que siempre generará soluciones
     diferentes.

  2) En caso de elegir una semilla que depende de la hora del computador, se puede elegir la cantidad de restart del
     algoritmo. No tiene sentido aplicar restart a una con semilla estática ya que en cada restart generará la misma matriz.

  4) Finalmente se decide el tipo de movimiento que se generará, donde se pueden escoger los siguientes valores:
      0 -> Hace HC con swap de emparejamientos
      1 -> Hace HC con swaps de fechas
      2 -> Hace HC con swaps de localidades
      Otro valor -> Hace HC con los 3 movimientos a la vez.

  3) Finalmente se aplica HC con los tres tipos de movimientos y nos devuelve la solución minimizada.

Archivos utilizados.

 - main.c : Este es el archivo principal de programa en el cual se ejecuta el programa y llama a las funciones que necesite
            desde los headers.

 - matriz.h: Este es el primer header. Se encarga de tareas mas representativas:

            - Constructor : Esta función nos toma la matriz de distancia dependiendo del argumento ingresado al ejecutar el  algoritmo.
            - Nombres: Función que nos almacena los nombres de los equipos que se guardan en el archivo ciudades.txt. En este último estan todos los nombres seguidos, y dependiendo del tipo de torneo que se ingrese como argumento son las iniciales que se almacenan.
            - timeval_diff: Función que ayuda a representar de mejor forma el tiempo que se demora el HC

  - printeador.h: Este header posee funciones para imprimir ciertos datos:

            - printeador_matriz: esta función imprime cualquier matriz que se ingrese con sus datos originales
            - printeador_solucion: esta función toma una matriz de solución y la imprime como un calendario, de forma que sea mas representativa que simples números que forman una matriz. Con esto se aprecia perfectamente las fechas, los equipos y sus roles a través del torneo.

  - aleatoria.h: Este header es uno de los mas extensos y posee dos funciones que generan la solución aleatoria inicial.

            - helper: Esta función sirve mucho para ver la restricción de una fecha. Esta función comprueba que no se repitan equipos en una fecha (y tampoco hayan equipos sin jugar)
            - generador: La función mas extensa del programa y que se encarga de generar la función aleatoria sea del tamaño que sea. Considera todas las soluciones duras para generarla y lo hace con un Doble Robin Round.

  - hill_climbing.h: Este último header posee todas las funciones necesarias para ejecutar el algoritmo de Hill-Climbing con alguna mejora:

            - funcion_evaluadora: Esta función calcula la distancia de la matriz de solución que se ingrese a ella. Esta es la función míope que nos ayuda a comprobar si la solución es mejor que la actual.
            - swap_localidad: Función que nos genera el intercambio de localidades de un enfrentamiento
            - swap_fechas: Función que nos genera el intercambio de fechas dentro del torneo
            - swap_emparejamiento: Función que nos genera el intercambio de duelos a través de la misma fecha u otras.
            - restriccion_columna: Función que nos ayuda a comprobar que todas las columnas de la matriz de solución cumpla con la restricción de NoRepeaters
            - restriccion_seguidas: Función que nos ayuda a comprobar que se cumplen las reglas de homestand y roadtrip
            - restriccion_fila: Función que nos comprueba que no se repitan equipos en una fecha (filas)
            - hc_localidad: Realiza hill_climbing utilizando swap_localidad.
            - hc_fecha: Realiza hill_climbing utilizando swap_fechas.
            - hc_emparejamiento: Realiza hill_climbing utilizando swap_emparejamiento.


Por último, ciertas consideraciones que se deben aclarar:

  - Por problemas de tiempo no se alcanzó a implementar la variación "Relaxed" con k = 1, aunque una solución posterior sería con el generador agregar una fila vacía y realizar los movimientos, lo que dejaría algún descanso para cada fecha. Eso sí, habría que agregar una restricción para que cada equipo solo pueda tener una fecha libre en el torneo (dos si se consideran las dos ruedas).

  - Respecto a la función evaluadora parece no estar implementada adecuadamente o fue un error mío bastante grave. Como ejemplo, la matriz de NL4.txt, que sale en la página web del problema (adjuntado en referencias en el informe) se muestra la matriz que, hasta ahora, es la que menor distancia posee (8276) pero la función calcula 8516, y a realizar el proceso a mano considerando la matriz y la calculadora da igualmente este último valor, tras 4 intentos dando el mismo resultado, y se consideraron las distancias correctas de las matrices y que deben todos comenzar desde su ciudad y al final del torneo deben devolverse. Es por eso que ciertas distancias pueden estar alteradas, incluso hay soluciones que poseen como distancia un valor menor a la presentada en la página, por lo que el sesgo puede ser bastante grande.
