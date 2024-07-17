.data
	str1:	.asciiz	": overflow na operacao de soma"
	
.text
	main:
		#0x12341234 + 0x11223344
		lui $a0, 0x1234
		ori $a0, $a0, 0x1234
		
		lui $a1, 0x1122
		ori $a1, $a1, 0x3344
		
		li $a2, 1	#numero da operacao
		jal soma
		
		#0x89891122 + 0xABCD9876
		lui $a0, 0x8989
		ori $a0, $a0, 0x1122
		
		lui $a1, 0xABCD
		ori $a1, $a1, 0x9876
		
		li $a2, 2	#numero da operacao
		jal soma
		
		li $v0, 10
		syscall
		
	soma:
		addu $t0, $a0, $a1			#soma os numeros passados como parametro
		
		xor $t1, $a0, $a1			#verifica se os sinais de a0 e a1 sao diferentes
		slt $t2, $t1, $zero			#$t2 = 1 se $t1 < 0 (sinais diferentes)
		bnez $t2, semOverflow			#se os sinais são diferentes não é possível ocorrer um overflow
		
		xor $t1, $a0, $t0			#verifica se os sinais de a0 e do resultado sao diferentes
		slt $t2, $t1, $zero			#$t2 = 1 se $t1 < 0 (sinais diferentes)
		beqz $t2, semOverflow			#se os dois tem o mesmo sinal nao ocorreu overflow
		
		overflow:
		li $v0, 1
		move $a0, $a2
		syscall
		
		li $v0, 4
		la $a0, str1
		syscall
		
		semOverflow:
		jr $ra