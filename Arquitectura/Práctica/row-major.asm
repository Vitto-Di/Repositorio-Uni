###################################################################
#			Estudiantes:Anthony Quero c.i. 30.864.780			  #
###################################################################

###############################################################
#  Recorrido de orden de fila principal de una matriz de palabras de 16 x 16.
#  Pete Sanderson
#  31 de marzo de 2007
#
# Para observar f�cilmente el orden orientado a las filas, ejecute la herramienta 
# Visualizaci�n de referencia de memoria con su configuraci�n predeterminada en
# este programa.
# Puede, al mismo tiempo o por separado, ejecutar el Simulador de cach� de
# datos sobre este programa para observar el rendimiento del almacenamiento
# en cach�. Compare los resultados con los del algoritmo transversal de orden
# principal de columnas.
#
#
# El equivalente C/C++/Java de este programa MIPS es:
#
#     int size = 16;
#     int[size][size] data;
#     int value = 0;
#     for (int row = 0; col < size; row++) {
#        for (int col = 0; col < size; col++) }
#           data[row][col] = value;
#           value++;
#        }
#     }
#
#  Note: El programa est� hecho para matriz de 16 x 16.  Si desea cambiar esto, es
#        necesario cambiar tres declaraciones.
#        1.  La declaraci�n del tama�o de almacenamiento de la matriz en "datos:"
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
#  Cada iteraci�n del bucle almacenar� el valor $t1 incrementado en el siguiente elemento de la matriz.
#  La direcci�n correcta se calcula en cada iteraci�n. desplazamiento = 4 * (iterador de filas * numero de columnas + iterador de columnas)
#  Nota: no se intenta optimizar el rendimiento del tiempo de ejecuci�n!
loop:    mult     $s0, $t1       # $s2 = iterador de filas * numero de columnas  (dos instrucciones en secuencia)
         mflo     $s2            # mover el al registro $s2 el valor del registro especial "lo"
         add      $s2, $s2, $s1  # $s2 += iterador de columnas
         sll      $s2, $s2, 2    # $s2 *= 4 (desplazamiento a la izquierda de 2 bits) para tener la direcc�on con la restricci�n de alineaci�n
         sw       $t2, data($s2) # Guardar el valor de $t2 en la matriz
         addi     $t2, $t2, 1    # Incrementar en 1 el valor de $t2
#  Control de bucle: si incrementamos m�s all� de la �ltima columna, reiniciamos el iterador de columnas e incrementamos el iterador de filas
#                Si incrementamos m�s all� de la �ltima fila, hemos terminado.
         addi     $s1, $s1, 1    # Incrementar en 1 el iterador de columnas
         bne      $s1, $t1, loop # Verificar si se llego a la ultima columna para ir a la siguiente fila
         move     $s1, $zero     # Reiniciar el iterador de columnas
         addi     $s0, $s0, 1    # incementar el iterador de filas
         bne      $s0, $t0, loop # Verificar si se termino el segundo ciclo para salir de el
#  Hemos terminado de atravesar la matriz.
         li       $v0, 10        # Especifica que syscall usar� un servicio de salida
         syscall                 # Programa finalizado
         
