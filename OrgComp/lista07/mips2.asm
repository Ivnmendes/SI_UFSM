.data
	#inicializa todos os elementos da matriz
	M:		.word 0, 1, 2, 3, 4
			.word 5, 6, 7, 8, 9
			.word 10, 11, 12, 13, 14
			.word 15, 16, 17, 18, 19
			.word 20, 21, 22, 23, 24
	tamanho:	.word 25	#tamanho da matriz
	str1:		.asciiz "Resultado"

.text
	main:
		la $a0, M	#endereco base da matriz
		#linha e coluna do elemento desejado
		li $s0, 1
		li $s1, 3
		
		li $s2, 4	#tam do elemento em bytes
		li $s3, 5	#dimensoes da matriz
		#(linha*dimensaoLinha+coluna)
		mul $s4, $s3, $s0
		add $s4, $s4, $s1
		
		mul $t0, $s2, $s4	#deslocamento
		
		add $a1, $a0, $t0	#enderecoBase+deslocamento = endereco objetivo
		
		lw $t5, ($a1)		#carrega a palavra do endereco obtido
		
		#linha e coluna do elemento desejado
		li $s0, 2
		li $s1, 2
		
		#(linha*dimensaoLinha+coluna)
		mul $s4, $s3, $s0
		add $s4, $s4, $s1
		
		mul $t0, $s2, $s4	#deslocamento
		
		add $a1, $a0, $t0	#enderecoBase+deslocamento = endereco objetivo
		
		lw $t6, 0($a1)		#carrega a palavra do endereco obtido
		
		add $t7, $t5, $t6	#soma ambos os elementos encontrados
		
		#linha e coluna do elemento desejado
		li $s0, 2
		li $s1, 4
		
		#(linha*dimensaoLinha+coluna)
		mul $s4, $s3, $s0
		add $s4, $s4, $s1
		
		mul $t0, $s2, $s4	#deslocamento
		
		add $a1, $a0, $t0	#enderecoBase+deslocamento = endereco objetivo
		
		sw $t7, 0($a1)		#carrega a palavra do endereco obtido
		
		#imprime o valor
		li $v0, 1
		lw $t1, 56($a0)		#endereco do valor
		move $a0, $t1
		syscall
		
		#encerra programa
		li      $v0, 10
    		syscall