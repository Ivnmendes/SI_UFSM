# int g1; // variável global
#
# int p3(int i, int y) {
# 	int c; // variável local
#
# 	c = i & y; // c <- operação and bit a bit de i e y
# 	return c; // retorne c
# }
#
# int p2(int y) {
# 	int b[10]; // variável local
# 	int i; // variável local
# 	int acumulador; // variável local
#
# 	acumulador = 0;
# 	for (i = 0; i < 10; i++) {
# 		b[i] = p3(i, y) + y;
#		acumulador = acumulador + b[i];
# 	}
# 	return acumulador;
#}
#
# int p1(int x) {
# 	int a1; // variável local
#	int a2; // variável local
#
# 	a1 = p2(x);
# 	a2 = x + a1;
# 	return a2;
# }
#
# int main(void) {
# 	int resultado; // variável local
#
# 	g1 = 10;
# 	resultado = p1(g1);
# 	return 0;
# }

.data
	g1:	.word	0

.text
	j main
	
	p1:
		#int p1(int x) {
		add $t0, $a0, $zero			#guarda o valor passado em um reg temporario
		addiu $sp, $sp, -12			#libera espaco na pilha para guardar ra, fp e t0
		sw $ra, 0($sp)				#salva o endereco de retorno para main
		sw $fp, 4($sp)				#salva o frame pointer
		sw $t0, 8($sp)				#salva o valor passado como parametro
		move $fp, $sp
		
		#a1 = p2(x)
		jal p2
		move $t1, $v0				#salva o valor de retorno em um reg temporario
		
		lw $ra, 0($sp)				#carrega o endereco de retorno para main
		lw $fp, 4($sp)				#carrega o frame pointer
		lw $t0, 8($sp)				#carrega o valor passado como parametro
		addiu $sp, $sp, 12			#restaura o valor da pilha
		
		add $v0, $t0, $t1			#return x+1
		
		jr $ra					#volta para quem chamou a funcao
		
	p2:
		#int p2(int y) {
		add $t0, $a0, $zero			#guarda o valor passado em um reg temporario
		addiu $sp, $sp, -52			#libera espaco na pilha para guardar ra, fp, t0 e as variaveis locais, b[10], i, acumulador
		sw $ra, 48($sp)				#salva o endereco de retorno para main
		sw $fp, 44($sp)				#salva o frame pointer
		move $fp, $sp				#atualiza o fp
		
		#salva y
		sw $a0, -12($fp)
		
		#acumulador = 0;
		li $t0, 0
		sw $t0, -4($fp)				#armazena acumulador
		
		#i = 0;
		li $t0, 0
		sw $t0, -8($fp)				#armazena acumulador
		
		comecoFor:
			lw $t1, -8($fp)			#carrega i
			li $t2, 10			#valor final
			bge $t1, $t2, fimFor		#testa condicao
			
			#p3(i,y)
			lw $a0, -8($fp)			#a0 = i
			lw $a1, -12($fp)		#a1 = y
			jal p3
			
			lw $t3, -12($fp)		#carrega y novamente
			add $t4, $v0, $t3		#t4 = p(3,i) + y
			
			#b[i] = p(3,i) + y
			lw $t1, -8($fp)			#carrega i novamente
			sll $t5, $1, 2			#deslocamento
			add $t6, $fp, $t5		#endereco de b[i]
			sw $t4, -48($t6)		#armazena b[i]
			
			#acumulador = acumulador + b[i];
			lw $t7, -4($fp)			#carrega acumulador
			add $t7, $t7, $t4		#soma o acumulador com b[i]
			sw $t7, -4($fp)			#armazena o novo valor do acumulador
			
			#i++
			lw $t1, -8($fp)
			addi $t1, $t1, 1
			sw $t1, -8($fp)
			
			j comecoFor
			
		fimFor:
			lw $v0, -4($fp)				#coloca acumulador em $v0 para o retorno
			lw $ra, 48($sp)				#carrega o endereco de retorno para main
			lw $fp, 44($sp)				#carrega o frame pointer
			addiu $sp, $sp, 52			#restaura o valor da pilha
		
			jr $ra
	p3:
		#int p3 (int i, int y) {
		and $v0, $a0, $a1
		
		jr $ra
	main:
		#g1 = 10;
		la $s0, g1				#carrega endereco
		li $t0, 10				#carrega 10
		sw $t0, 0($s0)				#g1 = 10
		
		#resultado = p1(g1);
		move $a0, $t0				#passa o valor de g1 como parametro
		jal p1
		move $s1, $v0				#resultado = 10

		#imprime o resultado
		li $v0, 1
		add $a0, $s1, $zero
		syscall
		j fim
	fim:
		li $v0, 10
		syscall