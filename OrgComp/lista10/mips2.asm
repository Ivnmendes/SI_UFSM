#int g1; // variável global
#int g2; // variável global
#
# // y: ponteiro para um inteiro
# int incrementa2(int *y) {
# 	*y = *y + 1;
# 	return *y;
# }
#
# // x: um valor inteiro
# int incrementa1(int x) {
# 	x = x + 1;
# 	return x;
# }

# int main(void) {
# 	int inc1; // variável local
# 	int inc2; // variável local
#
# 	g1 = 10;
# 	g2 = 10;
#
# 	inc1 = incrementa1(g1);
# 	inc2 = incrementa2(&g2);
# 	return 0;
# }

.data
	g1:	.word
	g2:	.word
	
.text
init:
	jal main
finit:
	move $v0, $a0
	syscall
#-------------------------------------------------------------------------------
# procedimento incrementa 2
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# int *y
# 
# Retorno do procedimento:
# $v0   : y+1
#-------------------------------------------------------------------------------
#int incrementa2(int *y) {
incrementa2:
	#*y = *y + 1;
	lw $t1, 0($a0)
	addiu $t1, $t1, 1
	sw $t1, 0($a0)
	
	#return *y;
	move $v0, $t1
	jr $ra

#-------------------------------------------------------------------------------
# procedimento incrementa 1
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# int x
# 
# Retorno do procedimento:
# $v0   : x+1
#-------------------------------------------------------------------------------
#int incrementa1(int x) {
incrementa1:
	#x = x + 1;
	addiu $t1, $a0, 1
	
	#return x;
	move $v0, $t1
	jr $ra

#-------------------------------------------------------------------------------
# procedimento main
# ------------------------------------------------------------------------------
# mapa da pilha
# $sp + 0	$ra	: endereço de retorno do procedimento
# $sp + 4	$fp	: endereço fp
# $sp + 8	inc1	: variavel local
#-------------------------------------------------------------------------------
# Argumentos
# Não existem argumentos
# 
# Retorno do procedimento:
# $v0   : código da execução do programa
#-------------------------------------------------------------------------------
#int main(void) {
main:
	add $sp, $sp, -8				#libera espaco na pilha para guardar ra, fp e as variaveis locais
	sw $ra, 0($sp)
	sw $fp, 4($sp)
	
	#atualiza valor das variaveis globais
	#g1 = 10;
	la $t0, g1
	li $t1, 10
	sw $t1, 0($t0)
	#g2 = 10;
	la $t0, g2
	sw $t1, 0($t0)
	
	#inc1 = incrementa1(g1)
	move $a0, $t1					#passa o valor de g1 como parametro
	jal incrementa1
	
	#inc2 = incrementa(&g2);
	la $a0, g2					#passa o endereco de g2 como parametro
	jal incrementa2
	
	#restaura os valores de ra e fp, e retorna a pilha ao seu tamanho anterior
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	addiu $sp, $sp, 8
	
	#return 0;
	li $a0, 10
	jr $ra
#}
	
	