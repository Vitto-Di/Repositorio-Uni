# Para utilizar el bubble sort del libro se añadieron las lineas de codigo necesarias y un caso de prueba
# El array es declarado en memoria y luego cargado en registros
# Se implemento un procedimiento para mostrar el estado del array y asi facilitar su estudio

.data
	array: .word 4 5 3 1 2 6 8 7
	size_array: .word 8
	espacio: .asciiz " "
	salto: .asciiz "\n"
.text
	main:
	
	la $a0,array
	lw $a1,size_array
	
	jal mostrar # Muestra arreglo inicial
	
	li $v0,4
	la $a0,salto
	syscall     # Imprime "\n"
	
	la $a0,array
	lw $a1,size_array
	jal sort	# Ordena
	
	la $a0,array
	lw $a1,size_array
	
	jal mostrar # Muestra arreglo ordenado

	li $v0,10
	syscall  # Fin de programa
	
	
	swap:
	
	sll $t1,$a1,2
	add $t1, $a0, $t1
	
	lw $t0, 0($t1)
	lw $t2, 4($t1)
	
	sw $t2, 0($t1)
	sw $t0, 4($t1)
	
	jr $ra
	
	mostrar:
	
	addi $t0,$a0,0 # t0 es registro base array
	addi $t1,$a1,0 # t1 contiene tamaño
	sll $t1,$t1,2 # tamaño x 4
	
	move $t3,$zero # indice 
	
	loop:
	
	add $t5,$t3,$t0 # Obtiene direccion del elemento
	
	li $v0,1
	lw $a0,0($t5) # Muestra elemento
	syscall
	
	li $v0,4
	la $a0,espacio # Imprime espaciado
	syscall
	
	addi $t3,$t3,4 # Siguiente elemento
	
	slt $t4,$t3,$t1 # Verifica tamaño
	
	beq $t4,$zero,exit # Si sobrepasa el tamaño termina ciclo
	
	j loop # repite
	
	exit:
	
	jr $ra
	
	sort:
	
	addi $sp,$sp,-20
	
	sw $ra, 16($sp)
	sw $s3,12($sp)
	sw $s2, 8($sp)
	sw $s1, 4($sp)
	sw $s0, 0($sp)
	
	move $s2,$a0
	move $s3,$a1
	
	move $s0,$zero
	
	for1tst: slt $t0,$s0,$s3
		beq $t0,$zero,exit1
		addi $s1,$s0,-1
	
	for2tst: slti $t0,$s1,0
		bne $t0,$zero, exit2
		sll $t1, $s1, 2
		add $t2, $s2, $t1
		lw $t3, 0($t2)
		lw $t4, 4($t2)
		slt $t0, $t4, $t3
		beq $t0, $zero, exit2
		
		move $a0, $s2
		move $a1, $s1
		jal swap
		
		addi $s1,$s1,-1
		j for2tst
		
		exit2: addi $s0,$s0,1
		j for1tst
		
		exit1: lw $s0, 0($sp)
			lw $s1, 4($sp)
			lw $s2, 8($sp)
			lw $s3,12($sp)
			lw $ra,16($sp)
			
			addi $sp,$sp,20
			
			jr $ra
	
	
	

