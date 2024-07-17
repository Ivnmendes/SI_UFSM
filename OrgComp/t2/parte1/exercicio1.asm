.data
# int g1;
	g1: .word 0
# int g2;
	g2: .word 0
.text
#################################################
#	Procedimento main(void)			#
#						#
#################################################
# Mapa da pilha:				#
#						#
#						#
#						#
#						#
#################################################
# Argumentos:					#
# sem argumentos				#
#						#
#						#
#################################################
# Retorno do procedimento:			#
# sem retorno					#
#						#
#						#
#################################################
	#int main(void) {
	main:
		#g1 = 10;
		la $s0, g1
		li $t1, 10
		sw $t1, 0($s0)
		
		#g2 = 10;
		la $s1, g2
		sw $t1, 0($s1)
		
		#inc1 = incrementa1(g1);
		move $a0, $t1			#move o valor de g1 para $a0
		jal incrementa1
		#salva o retorno na variavel local
		move $t0, $v0
		addiu $sp, $sp, -4		#prepara a pilha para receber a variavel local
		sw $t0, 0($sp)			#salva a variavel local na pilha
		
		#inc2 = incrementa2(&g2);
		move $a0, $s1			#move o endereco de g2 para $a0
		jal incrementa2
		#salva o retorno na variavel local
		move $t1, $v0
		#carrega inc1 da pilha
		lw $t0, 0($sp)
		addiu $sp, $sp, 4		#ajusta a pilha novamente
		
		#return 0;
		li $v0, 10
		syscall
#################################################
#	Procedimento incrementa1(int x)		#
#						#
#################################################
# Mapa da pilha:				#
# Não houve manipulação da pilha		#
#						#
#						#
#						#
#################################################
# Argumentos:					#
# $a0	:	inteiro				#
#						#
#						#
#################################################
# Retorno do procedimento:			#
# $v0	:	inteiro resultante da operação	#
#						#
#						#
#################################################
	#int incrementa1(int x) {
	incrementa1:
		#x = x + 1;
		addiu $v0, $a0, 1 		#coloca o resultao em $v0 para o retorno
		#return x;
		jr $ra
		
#################################################
#	Procedimento incrementa2(int *x)	#
#						#
#################################################
# Mapa da pilha:				#
# Não houve manipulação da pilha		#
#						#
#						#
#						#
#################################################
# Argumentos:					#
# $a0	:	ponteiro para inteiro		#
#						#
#						#
#################################################
# Retorno do procedimento:			#
# $v0	:	inteiro resultante da operação	#
#						#
#						#
#################################################
	#incrementa2(int *x) {
	incrementa2:
		#*y = *y + 1;
		lw $t0, 0($a0)			#carrega valor de y
		addiu $t0, $t0, 1		#y = y+1
		sw $t0, 0($a0)			#salva o resultado no endereco passado como parametro
		#return *y;
		move $v0, $t0
		jr $ra