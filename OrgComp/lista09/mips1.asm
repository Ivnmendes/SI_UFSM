# int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
# int i, j, k;
#
# int main(void) {
# i = 1;
# goto abc;
# a[4] = 123;
# a[5] = 900;
# abc:
# 	a[0] = i;
# 	j = a[0];
# 	k = i + 3000;
#
# 	if (i == j) {
# 		a[2] = k - a[9];
# 	} else {
# 		a[2] = a[4];
# 	}
# 	if ((k < i) && (i < 600)) {
# 		if ((k == 6) || (j >= i)) {
# 			a[9] = 400;
# 		} else {
# 			a[8] = 500;
# 		}
# 	}
# 	switch (a[j * 2 + 1]) {
# 		case 1:
# 			a[1] = 4
# 		case 3:
# 			switch (a[4]) {
# 				case 3:
# 					a[5] = 50000;
# 					break;
# 				case 4:
# 					a[6] = 50000;
# 				case 5:
# 					a[7] = 70000;
# 					break;
# 			}
# 			a[3] = 50000;
# 			break;
# 		case 5:
# 			a[5] = 6000;
# 			break;
# 	}
# }

.data
	a:		.word 0,1,2,3,4,5,6,7,8,9
	i:		.word 0
	j:		.word 0
	k:		.word 0
	novaLinha:	.asciiz "\n"
	str1:		.asciiz ":"
.text

	main:
		#i = 1;
		la $t0, i			#carrega o endereco da variavel em t0
		li $t1, 1			#carrega 1 em t1
		sw $t1, 0($t0)			#salva 1 na variavel i
		
		#goto abc;
		j abc
		
		#a[4] = 123;
		la $t0, a			#carrega o endereco base de a[]
		li $t1, 4			#indice
		sll $t1, $t1, 2			#deslocamento = indice * nBytes
		add $a0, $t0, $t1		#ee = eb + d
		li $t0, 123			#valor a ser guardado
		sw $t1, 0($a0)
		
		#a[5] = 900;
		la $t0, a			#carrega o endereco base de a[]
		li $t1, 5			#indice
		sll $t1, $t1, 2			#deslocamento = indice * nBytes
		add $a0, $t0, $t1		#ee = eb + d
		li $t0, 900			#valor a ser guardado
		sw $t1, 0($a0)
		
		abc:
			#a[0] = i
			la $t0, a			#carrega o endereco base de a[]
			la $t1, i			#carrega o endereco de i
			lw $t2, 0($t1)			#valor a ser guardado
			sw $t2, 0($t0)			#salva o valor em a[]
			
			#j = a[0]
			lw $t1, 0($t0)			#carrega o valor de a[0]
			la $t2, j			#carrega o endereco de j
			sw $t1, 0($t2)			#salva o valor de a[0] em j
			
			#k = i + 3000;
			la $t1, i			#carrega o endereco de i
			lw $t1, 0($t1)			#carrega o valor de i
			la $t4, k			#carrega o endereco de k
			li $t3, 3000			#carrega 3000 no reg t3
			add $t1, $t1, $t3		#realiza a soma
			sw $t1, 0($t4)			#salva o resultado em k
			
			#if (i == j) {
			la $t0, i			#carrega o endereco de i
			la $t1, j			#carrega o endereco de j
			lw $a0, 0($t0)			#carrega o valor de i
			lw $a1, 0($t1)			#carrega o valor de j
			beq $a0, $a1, result1		#if()
			
			#else {
			#a[2] = a[4]
			la $s0, a			#carrega o endereco base de a
			li $t0, 2			#indice
			li $t1, 4			#indice
			sll $t0, $t0, 2			#calcula deslocamento de a[2]
			sll $t1, $t1, 2			#calcula deslocamento de a[4]
			add $t0, $t0, $s0		#ee = eb + d (a[2])
			add $t1, $t1, $s0		#ee = eb + d (a[4]
			lw $t2, 0($t1)			#t1 = a[4]
			sw $t2, 0($t0)			#a[2] = a[4]
			
			volta1:
			#if ((k < i) && (i < 600)) {
			la $t0, i			#carrega o endereco de i
			la $t1, k			#carrega o endereco de k
			lw $a0, 0($t0)			#carrega o valor de i
			lw $a1, 0($t1)			#carrega o valor de k
			bgt $a1, $a0, volta3		#se falso
			li $a2, 600			#carrega 600
			bgt $a0, $a2, volta3		#se falso
			
			volta3:
			#switch (a[j * 2 + 1]) {
			la $t0, a			#carrega o endereco base de a[]
			la $t4, j			#carrega o endereco de j
			lw $t1, 0($t4)			#carrega o valor de j
			lw $t5, 0($t2)
			sll $t1, $t1, 1			#multiplica j por 1
			addiu $t1, $t1, 1		#soma 1
			sll $t1, $t1, 2			#calcula deslocamento
			add $t1, $t1, $t0		#calcula endereco desejado
			lw $t3, 0($t1)			#carrega o valor no endereco desejado
			#case 1:
			li $t2, 1
			beq $t3, $t2, result3
			#case 3:
			li $t2, 3
			beq $t3, $t2, result4
			#case 5:
			li $t2, 5
			beq $t3, $t2, result5
			posSwitch:
			
			j imprimeVetor
			
			result1:
				#a[2] = k - a[9]
				la $s0, a			#carrega o endereco base de a
				li $t0, 2			#indice
				li $t1, 9			#indice
				sll $t0, $t0, 2			#calcula deslocamento de a[2]
				sll $t1, $t1, 2			#calcula deslocamento de a[9]
				add $t0, $t0, $s0		#ee = eb + d (a[2])
				add $t1, $t1, $s0		#ee = eb + d (a[4]
				la $t2, k			#carrega o endereco de k
				lw $t3, 0($t2)			#carrega o valor de k
				lw $t4, 0($t1)			#t4 = a[9]
				sub $t4, $t3, $t4		#t4 = k - a[9]
				sw $t4, 0($t0)			#a[2] = k - a[9]
				j volta1
			result2:
				#if ((k == 6) || (j >= i)
				la $t2, k			#carrega o endereco de k
				lw $a2, 0($t2)			#carrega o valor de k
				li $a3, 6			#carrega o valor 6
				beq $a3, $a2, volta2		#se verdadeiro desvia
				la $t0, i			#carrega o endereco de i
				la $t1, j			#carrega o endereco de j
				lw $a0, 0($t0)			#carrega o valor de i
				lw $a1, 0($t1)			#carrega o valor de j
				bge $a1, $a0, volta2		#se verdadeiro desvia
				#a[8] = 500
				la $a0, a			#carrega o endereco base de a
				li $t1, 8			#indice
				sll $t1, $t1, 2			#deslocamento = i * tam
				add $t1, $t1, $a0		#ee = eb + d
				li $t2, 500			#carrega o valor a ser armazenado
				sw, $t2, 0($t1)			#salva o valor em a[8]
				j volta3
				
				volta2:
				#a[9] = 400
				la $a0, a			#carrega o endereco base de a
				li $t1, 9			#indice
				sll $t1, $t1, 2			#deslocamento = i * tam
				add $t1, $t1, $a0		#ee = eb + d
				li $t2, 400			#carrega o valor a ser armazenado
				sw, $t2, 0($t1)			#salva o valor em a[9]
				j volta3
			result3:
				#a[1] = 4000;
				la $a0, a			#carrega o endereco base de a
				li $t1, 1			#indice
				sll $t1, $t1, 2			#deslocamento = i * tam
				add $t1, $t1, $a0		#ee = eb + d
				li $t2, 4000			#carrega o valor a ser armazenado
				sw, $t2, 0($t1)			#salva o valor em a[9]
				j posSwitch			#break;
			result4:
				#switch (a[4]) {}
				la $a0, a			#carrega o endereco base de a
				li $t1, 4			#indice
				sll $t1, $t1, 2			#deslocamento = i * tam
				add $t1, $t1, $a0		#ee = eb + d
				lw $t1, 0($t1)			#carrega o valor de a[4]
				#case 3:
				li $t2, 3
				beq $t1, $t2, result6
				#case 4:
				li $t2, 4
				beq $t1, $t2, result7
				#case 5:
				li $t2, 5
				beq $t1, $t2, result8
				
				volta4:
				#a[3] = 50000
				la $a0, a			#carrega o endereco base de a
				li $t1, 3			#indice
				sll $t1, $t1, 2			#deslocamento = i * tam
				add $t1, $t1, $a0		#ee = eb + d
				li $t2, 50000			#carrega o valor a ser armazenado
				sw, $t2, 0($t1)			#salva o valor em a[3]
				j posSwitch			#break;
			result5:
				#a[5] = 6000;
				la $a0, a			#carrega o endereco base de a
				li $t1, 5			#indice
				sll $t1, $t1, 2			#deslocamento = i * tam
				add $t1, $t1, $a0		#ee = eb + d
				li $t2, 6000			#carrega o valor a ser armazenado
				sw, $t2, 0($t1)			#salva o valor em a[9]
				j posSwitch			#break;
			result6:
				#a[5] = 50000
				la $a0, a			#carrega o endereco base de a
				li $t1, 5			#indice
				sll $t1, $t1, 2			#deslocamento = i * tam
				add $t1, $t1, $a0		#ee = eb + d
				li $t2, 50000			#carrega o valor a ser armazenado
				sw, $t2, 0($t1)			#salva o valor em a[5]
				j volta4
			result7:
				#a[6] = 50000
				la $a0, a			#carrega o endereco base de a
				li $t1, 6			#indice
				sll $t1, $t1, 2			#deslocamento = i * tam
				add $t1, $t1, $a0		#ee = eb + d
				li $t2, 50000			#carrega o valor a ser armazenado
				sw, $t2, 0($t1)			#salva o valor em a[5]
			result8:
				#a[7] = 70000
				la $a0, a			#carrega o endereco base de a
				li $t1, 7			#indice
				sll $t1, $t1, 2			#deslocamento = i * tam
				add $t1, $t1, $a0		#ee = eb + d
				li $t2, 70000			#carrega o valor a ser armazenado
				sw, $t2, 0($t1)			#salva o valor em a[7]
				j volta4
	imprimeVetor:
	li $t0, 0
	la $t1, a
	loop1:
	bge $t0, 10, fim
	# load word from addrs and goes to the next addrs
    	lw      $t2, 0($t1)
    	addi    $t1, $t1, 4
		
    	# syscall to print value
    	li      $v0, 1      
    	move    $a0, $t2
    	syscall
	#print(" ");
	li      $a0, 32
    	li      $v0, 11  
    	syscall
    	
    	#increment counter
    	addi    $t0, $t0, 1
    	j      loop1
    	
    	fim:
    		#print(" ");
	li      $a0, 32
    	li      $v0, 11  
    	syscall
    	#print(" ");
	li      $a0, 32
    	li      $v0, 11  
    	syscall
    	#print(" ");
	li      $a0, 32
    	li      $v0, 11  
    	syscall
    		la $t0, i
		lw $t1, 0($t0)
		li $v0, 1
		move $a0, $t1
		syscall
		#print(" ");
	li      $a0, 32
    	li      $v0, 11  
    	syscall
		
		la $t0, j
		lw $t1, 0($t0)
		li $v0, 1
		move $a0, $t1
		syscall
		
	#print(" ");
	li      $a0, 32
    	li      $v0, 11  
    	syscall
		la $t0, k
		lw $t1, 0($t0)
		li $v0, 1
		move $a0, $t1
		syscall
		
		li $v0, 10
		syscall
