.data
	array: .word 4 2 1 3
	tam: .word 4
	espacio: .asciiz " "
	salto: .asciiz "\n"
.text

	main:
	
	la $a0,array
	lw $a1,tam
	jal mostrar
	
	la $a0,array  #Se pasa direccion del array
	lw $a1,tam    #Se pasa su tamaño
	jal insertion_sort #Llamada principal
	
	la $a0,array
	lw $a1,tam
	jal mostrar
	
	li $v0,10 # Fin algoritmo
	syscall
#------------------------------------

	mostrar:
	move $t0,$a0
	move $t1,$a1
	addi $t2,$zero,0
	
	loop:
	sll $t3,$t2,2
	add $t3,$t3,$t0
	
	li $v0,1
	lw $a0,0($t3)
	syscall
	
	li $v0,4
	la $a0,espacio
	syscall
	
	addi $t2,$t2,1
	slt $t4,$t2,$t1
	
	beqz $t4,exit
	j loop
	
	exit: 
	li $v0,4
	la $a0,salto
	syscall
	
	jr $ra
#---------------------------------------------
	insertion_sort:
	
	addi $sp,$sp,-20 # Abre 5 espacios en la pila
	sw $s0,0($sp)
	sw $s1,4($sp)
	sw $s2,8($sp)
	sw $s3,12($sp)
	sw $ra,16($sp)
	
	
	move $s0,$a0 # s0 = registro base array
	move $s1,$a1 # s1 = tamaño array
	addi $s2,$zero,1 # s2 = 1, s2 indice loop externo
	
	loop1:
	slt $t1,$s2,$s1  #Ejecuta el ciclo mientras:
	beqz $t1,f_loop1 # s2 < tamaño del array
	
	###Zona interna loop
	add $s3,$zero,$s2 # s3 Indice loop interno,s3 = s2
	loop2:
	bgtz $s3,continue # Si s3 es mayor que 0..
	j f_loop2	  #..termina el ciclo
	continue:	  # 
	
	sll $t3,$s3,2 # s3 x 4, Indice se ajusta para el array
	add $t3,$t3,$s0 # t3 = array[s3
	sub $t4,$t3,4 # t4 = array[s3-1
	
	lw $t5,0($t3) # Carga valor de a[s3 en registro
	lw $t6,0($t4) # Carga valor de a[s3-1 en registro
	
	slt $t7,$t5,$t6 # t7 = a[s3 < a[s3-1
	beqz $t7,f_loop2 # Sino finaliza ciclo
	
	move $a0,$s0 # Paso de direccion de array
	move $a1,$s3 # #Paso de indice s3
	jal swap    # Se intercambian a[s3 y a[s3-1
	
	sub $s3,$s3,1 #Se decrementa indice s3 en 1
	j loop2 # Repite ciclo
	
	f_loop2:
	###Fin zona interna loop
	
	addi $s2,$s2,1 #Incrementa indice s2 en 1
	j loop1 #Repite ciclo
	
	f_loop1:         # Restaura registros
	lw $s0,0($sp)    #
	lw $s1,4($sp)    #
	lw $s2,8($sp)    #
	lw $s3,12($sp)   #
	lw $ra,16($sp)   #
	addi $sp,$sp,20  #
	jr $ra  # Vuelta a main
	
	
#----------------------------------------------
	swap:
	#Algoritmo de intercambio
	#Modificado para cambiar a[k y a[k-1
	sll $t1,$a1,2
	add $t1, $a0, $t1
	
	lw $t0, 0($t1)
	lw $t2, -4($t1)
	
	sw $t2, 0($t1)
	sw $t0, -4($t1)
	
	jr $ra
#------------------------------------------------
	
		
