###################################################################
#			Estudiante:Anthony Quero c.i. 30.864.780			  #
###################################################################

################################################################
#
#  Recorrido de orden de columna principal de una matriz de palabras de 16 x 16.
#  Pete Sanderson
#  31 de Marzo de 2007
#
#  Para observar fácilmente el orden orientado a las columnas, ejecute la
#  herramienta Visualización de referencia de memoria con su configuración
#  predeterminada en este programa.
#  Puede, al mismo tiempo o por separado, ejecutar el Simulador de caché
#  de datos sobre este programa para observar el rendimiento del almacenamiento
#  en caché. Compare los resultados con los del algoritmo transversal de
#  orden de fila principal.
#
#  El equivalente C/C++/Java de este programa MIPS es:
#     int size = 16;
#     int[size][size] data;
#     int value = 0;
#     for (int col = 0; col < size; col++) {
#        for (int row = 0; row < size; row++) }
#           data[row][col] = value;
#           value++;
#        }
#     }
#
#  Note: El programa está hecho para matriz de 16 x 16.  Si desea cambiar esto, es
#        necesario cambiar tres declaraciones.
#        1.  La declaración del tamaño de almacenamiento de la matriz en "datos:"
#	    debe cambiarse de 256 (que es 16 * 16) a #columnas * #filas.
#        2. El "li" para inicializar $t0 debe cambiarse al nuevo numero de filas.
#        3. El "li" para inicializar $t1 debe cambiarse al nuevo numero de columnas.
#
         .data
data:    .word     0 : 256       # Almacenamiento para una matriz de 16 * 16
         .text
         li       $t0, 16        # $t0 = numero de filas
         li       $t1, 16        # $t1 = numero de colummnas
         move     $s0, $zero     # $s0 = iterador de filas
         move     $s1, $zero     # $s1 = iterador de columnas
         move     $t2, $zero     # $t2 = el valor a ser almacenado
#  Cada iteración del bucle almacenará el valor $t1 incrementado en el siguiente elemento de la matriz.
#  La dirección correcta se calcula en cada iteración. desplazamiento = 4 * (iterador de filas * numero de columnas + iterador de columnas)
#  Nota: no se intenta optimizar el rendimiento del tiempo de ejecución!
loop:    mult     $s0, $t1       # $s2 = iterador de filas * numero de columnas  (dos instrucciones en secuencia)
         mflo     $s2            # mover el al registro $s2 el valor del registro especial "lo"
         add      $s2, $s2, $s1  # $s2 += iterador de columnas
         sll      $s2, $s2, 2    # $s2 *= 4 (desplazamiento a la izquierda de 2 bits) para tener la direccíon con la restricción de alineación
         sw       $t2, data($s2) # Guardar el valor de $t2 en la matriz
         addi     $t2, $t2, 1    # Incrementar en 1 el valor de $t2
#  Control de bucle: si incrementamos más allá de la parte inferior de las columnas, reiniciamos el iterador de fila e incrementamos el de columna
#                Si incrementamos más allá de la última columna, hemos terminado.
         addi     $s0, $s0, 1    # Incrementar el iterador de columnas
         bne      $s0, $t0, loop # No se ha llegado a la parte inferior de las columnas, el ciclo sigue
         move     $s0, $zero     # Reiniciar iterador de filas
         addi     $s1, $s1, 1    # Incrementa el iterador de columnas
         bne      $s1, $t1, loop # retroceder si no se llega al final de la matriz (más allá de la última columna)
# Hemos terminado de atravesar la matriz.
         li       $v0, 10        # Especifica que syscall usará un servicio de salida
         syscall                 # Programa finalizado
