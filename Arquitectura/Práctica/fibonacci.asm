###################################################################
#			Estudiantes:Anthony Quero c.i. 30.864.780			  #
###################################################################


# Programa que obtiene varios numeros Fibonacci
.data
fibs:.word   0 : 19         # "Vector" de palabras de memoria (32 bits = 4 bytes) que contendra los numeros fib
size: .word  19             # Tamaño del "arreglo" del tamaño del vector
prompt: .asciiz "Cuanto numeros Fibonacci quieres generar? (2 <= x <= 19): " #prompt es el mensaje a mostrar en pantalla
.text
      la   $s0, fibs        # Cargar la direccion del arreglo
      la   $s5, size        # Cargar la dirección del tamaño del arreglo
      lw   $s5, 0($s5)      # Cargar el tamaño del arreglo

# Está parte en el codigo la marcan como opcional, pero la habilite, sirve para leer la cantidad de numeros fibonacci a dar
pr:   la   $a0, prompt      # Lee la direccion del mensaje para una llamada a una rutina(servicio) del sistema o syscall
      li   $v0, 4           # Especifica que syscall usará un servicio de escritura de cadenas de caracteres por pantalla
      syscall               # Esta sección imprime la cadena
      li   $v0, 5           # Especifica que syscall usará un servicio de lectura de enteros
      syscall               # Lee un numero por pantalla y lo guarda en el registro de resultados $v0.
      bgt  $v0, $s5, pr     # Si el numero ingresado es mayor que el tamaño del "vector" salta a "pr" para volver a leer un numero
      blt  $v0, $zero, pr   # Si el numero ingresado es menor a 0 salta a "pr" para volver a leer un numero
      add  $s5, $v0, $zero  # Aqui se transfiere el numero ingresado al registro con el que se va a trabajar $s5
      
      li   $s2, 1           # Esta instruccion carga un 1 para usar en la primera y segunda posicion de los numeros Fibonacci
      sw   $s2, 0($s0)      # F[0] = 1
      sw   $s2, 4($s0)      # F[1] = F[0] = 1
      addi $s1, $s5, -2     # Registro $s1 es el iterador del ciclo para obtener los numeros (numero ingresado por el usuario - 2) 
      
      # Ciclo que obtiene el resto de los numeros Fibonacci
loop: lw   $s3, 0($s0)      # Obtiene del "vector" F[n-2]
      lw   $s4, 4($s0)      # Obtiene del "vector" F[n-1]
      add  $s2, $s3, $s4    # F[n] = F[n-1] + F[n-2]
      sw   $s2, 8($s0)      # Guarda el resultado de un numero Fibonacci en una nueva posición del "vector"
      addi $s0, $s0, 4      # Aumenta en 1 numero entero la dirección del "vector"
      addi $s1, $s1, -1     # Desincrementa el iterador en 1
      bgtz $s1, loop        # Mientras el iterador sea mayor a 0 repetir el ciclo
      
      # Los numeros Fibonacci ya están obtenidos u guardados en el "vector".
      la   $a0, fibs        # Primera argumento del procedimiento "print" (dirección del "vector")
      add  $a1, $zero, $s5  # Segundo argumento del procedimiento "print" (Cantidad de numeros a imprimir)
      jal  print            # Lamma al procedimiento "print" para mostrar los numeros obtenido

      # Está parte es equivalente a return 0 de la función "main" en c, en otras palabras finaliza el programa.
      li   $v0, 10          # Especifica que syscall usará un servicio de salida
      syscall               # Programa finalizado
		
###############################################################
# Procedimiento que imprime los numeros Fibonacci en una linea.
      .data
space:.asciiz  " "          # Esta etiqueta servira para dar los espacios entre numeros
head: .asciiz  "Los numeros Fibonacci son:\n"
      .text
print:add  $t0, $zero, $a0  # Carga en el registro temporal $t0 la direccion del "vector" para imprimir los numeros
      add  $t1, $zero, $a1  # Carga la cantidad de numeros a imprimir en $t1 (iterador)
      la   $a0, head        # Carga la direccion de la cadena a imprimir con syscall
      li   $v0, 4           # Especifica que syscall usará un servicio de escritura de cadenas de caracteres por pantalla
      syscall               # Imprime la cadena "head"
      
out:  lw   $a0, 0($t0)      # Carga el nuemro Fibonacci que actualmente se debe imprimir
      li   $v0, 1           # Especifica que syscall usará un servicio de escritura de un entero por pantalla
      syscall               # Imprime el numero Fibonacci actual
      
      la   $a0, space       # Carga la direccion de la cadena a imprimir con syscall
      li   $v0, 4           # Especifica que syscall usará un servicio de escritura de cadenas de caracteres por pantalla
      syscall               # Coloca un espacio en pantalla
      
      addi $t0, $t0, 4      # Incrementa en 1 entero la dirección del "vector"
      addi $t1, $t1, -1     # desincrementa en 1 el iterador
      bgtz $t1, out         # Si no se han imprimido todos los numeros seguir imprimiendo
      
      jr   $ra              # Retornar al programa principal
# Final del procedimiento para imprimir los numeros Fibonacci
###############################################################
