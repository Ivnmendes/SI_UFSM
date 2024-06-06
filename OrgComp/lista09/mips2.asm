#int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
# int i, j, k;
# int acc = 0;
#
# int main(void) {
# 	i = 1;
# 	j = 2;
# 	k = 4;
# 	for (i = 1; i < 10; i++) {
# 	a[i] = a[i - 1] + 19;
# 	}
#
#	for (i = 0; i < 10; i++) {
# 		for (j = i; j < 10; j++) {
# 			acc = acc + a[j];
# 		}
# 	}
# 	a[6] = acc;
# 	while (a[k] < acc) {
# 		a[k] = a[k] + 10;
# 	}
# 	do {
# 		a[7] = a[k] + 1;
# 	} while (a[7] < a[8]);
# }

.data
	a: 	.word 0,1,2,3,4,5,6,7,8,9
	i: 	.word 0
	j:	.word 0
	k:	.word 0
	acc:	.word 0
	
.text
	main:
		#i = 1;
		la $t0, i
		li $t1, 1
		sw $t1, 0($t0)
		
		#j = 2;
		la $t0, j
		li $t1, 2
		sw $t1, 0($t0)
		
		#k = 4;
		la $t0, k
		li $t1, 4
		sw $t1, 0($t0)
		
		#for (i = 1; i < 10; i++) {
		li $t1, 19					#constante que vai ser somada
		li $t0, 1					#valor inicial de i
		li $s0, 10					#limite do looping
		la $a0, a					#carrega endereco de a
		voltaFor1:
			bge $t0, $s0, fimFor1			#se i>=10 vai para apos o fim do loping
			#a[i] = a[i-1] + 19;
			sll $t2, $t0, 2				#calcula o deslocamento para a[i]
			subi $t3, $t0, 1			#i-1
			sll $t3, $t3, 2				#deslocamento de a[i-1]
			add $t2, $a0, $t2			#endereco de a[i]
			add $t3, $a0, $t3			#endereco de a[i-1]
			lw $t3, 0($t3)				#valor em a[i-1]
			add $t3, $t3, $t1			#a[i-1] + 19
			sw $t3, 0($t2)				#salva o valor em a[i]
			addiu $t0, $t0, 1			#i++;
			j voltaFor1				#prox volta
		
		fimFor1:
		#for (i = 0; i < 10; i++) {
		li $t0, 0					#contador
		li $t1, 10					#limite
		li $t2, 0					#acumulador
		la $a0, a					#endereco base de a
		voltaFor2:
			bge $t0, $s0, fimFor2			#se i>=10 vai para apos o fim do loping
			add $t3, $t0, $zero			#contador2
			voltaFor2.1:
				bge $t3, $s0, fimFor2.1		#se j>=10 vai para apos o fim do loping
				sll $t4, $t3, 2			#deslocamento
				add $t4, $a0, $t4		#endereco desejado
				lw $t4, 0($t4)			#carrega valor em a[j]
				add $t2, $t4, $t2		#acc = a[j] + acc
				addiu $t3, $t3, 1		#j++;
			
				j voltaFor2.1			#prox volta
				
			fimFor2.1:
			addiu $t0, $t0, 1			#i++;
			j voltaFor2				#prox volta
			
		fimFor2:
		#salva os valores que sobraram nas variaveis
		la $a0, i					#endereco de i
		la $a1, j					#endereco de j
		la $a2, acc					#endereco de acc
		sw $t0, 0($a0)					#salva valor de i
		sw $t3, 0($a1)					#salva valor de j
		sw $t2, 0($a2)					#salva valor de acc
		
		#a[6] = acc;
		li $t0, 6					#indice
		la $a0, a					#endereco base de a
		
		sll $t0, $t0, 2					#deslocamento
		add $t0, $t0, $a0				#a[6]
		
		sw $t2, 0($t0)					#a[6] = acc
		
		#while (a[k] < acc) {
		la $t0, k					#carrega endereco de k
		lw $t0, 0($t0)					#carrega o valor de k
		sll $t0, $t0, 2					#deslocamento
		add $t0, $t0, $a0				#a[k]
		
		voltaWhile:
			lw $t1, 0($t0)				#t1 = a[k]
			bge $t1, $t2, fimWhile			#a[k] >= acc
			addiu $t3, $t1, 10			#t3 = a[k] + 10
			sw $t3, 0($t0)				#a[k] = t3
			j voltaWhile
		fimWhile:
		
		# do {} while(a[7] < a[8])
		li $t1, 7					#indice
		li $t2, 8					#indice
		sll $t1, $t1, 2					#deslocamento (7)
		sll $t2, $t2, 2					#deslocamento (8)
		add $t1, $t1, $a0				#endereco de a[7]
		add $t2, $t2, $a0				#endereco de a[8]
		lw $t2, 0($t2)					#t2 = a[8]
		lw $t0, 0($t0)					#t0 = a[k]
		
		voltaDoWhile:
			addiu $t3, $t0, 1
			sw $t3, 0($t1)
			lw $t3, 0($t1)
			blt $t3, $t2, voltaDoWhile
		
		j imprimeVetor
		
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
		
		#print(" ");
		li      $a0, 32
    		li      $v0, 11  
    		syscall
		la $t0, acc
		lw $t1, 0($t0)
		li $v0, 1
		move $a0, $t1
		syscall
		
		li $v0, 10
		syscall