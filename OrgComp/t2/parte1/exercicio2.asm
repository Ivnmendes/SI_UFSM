.data
	array:	.space 1000	#reserva 1000 byte, o necessário para guardar 250 elementos do array

.text
# formula para o indice do array 3d: ((i*D2*D3)+(j*D3)+K) * tamElemento
# onde d2 = n de colunas
# d3 = profundidade
	main:
	la $s0, array					#endereco base
	li $s1, 5					#d2
	li $s2, 10					#d3
	
	jal populaArray
	
	#carrega array[1][3][7]
	#calcula indice
	li $t0, 1		#i = 1
	li $t1, 3		#j = 3
	li $t2, 7		#k = 7
	mul $t4, $t0, $s1	#t4 = i*d2
	mul $t4, $t4, $s2	#t4 = t4*d3
	mul $t5, $t1, $s2	#t5 = j*d3
	add $t6, $t4, $t5	#t6 = (i*d2*d3) + (j*d3)
	add $t6, $t6, $t2	#t6 = t6 + k
	sll $t6, $t6, 2		#t6*2
	add $t6, $s0, $t6	#endereco array[i][j][k]
					
	lw $t7, 0($t6)		#t7 = a[1][3][7]
	
	#carrega array[2][2][3]
	#calcula indice
	li $t0, 2		#i = 2
	li $t1, 2		#j = 2
	li $t2, 3		#k = 3
	mul $t4, $t0, $s1	#t4 = i*d2
	mul $t4, $t4, $s2	#t4 = t4*d3
	mul $t5, $t1, $s2	#t5 = j*d3
	add $t6, $t4, $t5	#t6 = (i*d2*d3) + (j*d3)
	add $t6, $t6, $t2	#t6 = t6 + k
	sll $t6, $t6, 2		#t6*2
	add $t6, $s0, $t6	#endereco array[i][j][k]
					
	lw $t8, 0($t6)		#t8 = a[2][2][3]
	
	#soma os valores
	add $t9, $t7, $t8
	
	#guarda em array[1][4][8]
	li $t0, 1		#i = 1
	li $t1, 4		#j = 4
	li $t2, 8		#k = 8
	mul $t4, $t0, $s1	#t4 = i*d2
	mul $t4, $t4, $s2	#t4 = t4*d3
	mul $t5, $t1, $s2	#t5 = j*d3
	add $t6, $t4, $t5	#t6 = (i*d2*d3) + (j*d3)
	add $t6, $t6, $t2	#t6 = t6 + k
	sll $t6, $t6, 2		#t6*2
	add $t6, $s0, $t6	#endereco array[i][j][k]
	
	sw $t9, 0($t6)		#salva em a[1][4][8]
	
	#finaliza o programa
	li $v0, 10
	syscall
	
	#procedimento para preencher o array
	populaArray:
		li $t0, 0				#indice i
		
		loopI:
			bge $t0, 5, fimLoopI		#se i>=5 acaba o loop
			li $t1, 0			#indice j
			
			loopJ:
				bge $t1, $s1, fimLoopJ	#se j>=d2 acaba o loop
				li $t2, 0		#indice k
				
				loopK:
					bge $t2, $s2, fimLoopK	#se k>=d3 acaba o loop
					add $t3, $t0, $t1	#t3 = i + j
					add $t3, $t3, $t2	#t3 = t3 + k
					
					#calcula indice
					mul $t4, $t0, $s1	#t4 = i*d2
					mul $t4, $t4, $s2	#t4 = t4*d3
					mul $t5, $t1, $s2	#t5 = j*d3
					add $t6, $t4, $t5	#t6 = (i*d2*d3) + (j*d3)
					add $t6, $t6, $t2	#t6 = t6 + k
					sll $t6, $t6, 2		#t6*2
					add $t6, $s0, $t6	#endereco array[i][j][k]
					
					sw $t3, 0($t6)		#salva em array[i][j][k]
					
					addiu $t2, $t2, 1	#k++
					j loopK
					
				fimLoopK:
					addiu $t1, $t1, 1	#j++
					j loopJ
			fimLoopJ:
				addiu $t0, $t0, 1		#i++
				j loopI
		fimLoopI:
			jr $ra