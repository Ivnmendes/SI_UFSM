# Projeto: Simulador MIPS
# Arquivo: mips1.asm
# Descricao: Trabalho 1 da disciplina de OrganizaÃ§Ã£o de Computadores
# Autor: Ivan Mendes Martignago
# Data: 21/06/24

# remover depois>>> conteudo dos registradores $sx
# $s0: descritor do arquivo aberto
# $s1: eb vetor instrucoes
.data
	buffer:			.space		4					#buffer para armazenar dados lidos
	arq:			.asciiz		"trabalho_01-2024_1.bin"		#endereco do arquivo
	instrucoes:		.word		0					#numero de intrucoes guardadas no vetor
	registradores:		.space		128					#vetor com registradores simulados, tentarei seguir a mesma lógica padrão (pos 31 do vetor e o registrador $ra)
	pcSimulado:		.word		0					#salva a posicao atual executada do vetor
.text

.globl main

	main:
		jal iniciaRegistradores							#inicia os registradores virtuais em 0
		jal leituraDeArquivo							#faz a leitura do arquivo
		jal executaPrograma							#executa o programa a partir do vetor de instrucoes
		jal imprimeVetor
	fim:
		#finaliza programa
		li $v0, 10
		syscall
		
	erro:
		#erro ao abrir arquivo
		li $a0, -1
		li $v0, 1
		syscall
		j fim
		
#-------------------------------------------------------------------------------
# procedimento iniciaRegistradores
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# 
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
iniciaRegistradores:
	la $t2, registradores						#carrega endereco base do vetor de registradores
	li $t3, 32							#numero de registradores
	iniciaRegistradoresLoop:
		beq $t3, $zero, registradoresIniciados  		#se todos os registradores foram inicializados, sai do loop
    		sw $zero, 0($t2)  					#inicializa registrador com 0
    		addi $t2, $t2, 4  					#avança para o próximo registrador
    		subi $t3, $t3, 1  					#decrementa o contador
    		j iniciaRegistradoresLoop
    	
    	registradoresIniciados:
    	jr $ra
#-------------------------------------------------------------------------------
# procedimento leituraDeArquivo
# ------------------------------------------------------------------------------
# mapa da pilha
# $sp+0		$ra	:	endereco de retorno
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# 
# 
# Retorno do procedimento:
# $v0
#-------------------------------------------------------------------------------
leituraDeArquivo:
#prologo
	addiu $sp, $sp, -4					#libera espaco na pilha
	sw $ra, 0($sp)						#guarda $ra na pilha

#corpo
	#la $s1, instrucoes					#endereco base do vetor de instrucoes
	la $a0, arq						#endereco do arquivo
	li $a1, 0						#modo de leitura
	li $a2, 0						#permissao, usado no modo leitura apenas
	jal abrirArquivo
	
	add $s0, $v0, $zero					#salva o descritor para nao ser perdido
	
	#tamanho do arquivo
	add $a0, $s0, $zero					#salva o descritor em $a0
	jal obtemTamanhoArquivo
	
	add $s0, $v1, $zero					#salva o novo descritor para nao ser perdido
	
	#aloca memoria para o vetor de instrucoes
	move $a0, $v0						#numero de bytes alocados e o retorno da funcao de obter tamanho do arquivo
	li $v0, 9						#codigo syscall de alocacao de memoria
	syscall

	move $s1, $v0						#endereco base do vetor
		
	#inicia leitura
	add $a0, $s0, $zero					#salva o descritor em $a0
	la $a1, buffer						#local onde a leitura vai ser salva
	la $a2, 4						#numero de bytes a serem lidos
	jal lerInstrucao

	#fecha o arquivo
	add $a0, $s0, $zero					#descritor como parametro
	jal fecharArquivo
	
#epilogo
	lw $ra, 0($sp)						#carrega $ra da pilha
	addiu $sp, $sp, 4					#devolve espaco da pilha
	
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento abrirArquivo
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	endereco do arquivo
# $a1	:	modo de abertura, 0 para leitura e 1 para escrita
# $a2	:	permissao
# Retorno do procedimento:
# $v0	:	descritor do arquivo
#-------------------------------------------------------------------------------
abrirArquivo:
	#abertura do arquivo
	li $v0, 13						#codigo para abertura
	syscall							#retorna o descritor
	
	bltz $v0, erro						#verifica se o arquivo foi abertor corretamente

	jr $ra
#-------------------------------------------------------------------------------
# procedimento obterTamahoArquivo
# ------------------------------------------------------------------------------
# mapa da pilha
# $sp+4		$t1	:	n de bytes lidos
# $sp+0		$ra	:	endereco de retorno
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	descritor do arquivo
# Retorno do procedimento:
# $v0	:	tamanho do arquivo
# $v1	:	novo descritor arquivo
#-------------------------------------------------------------------------------
obtemTamanhoArquivo:
#prologo
	addiu $sp, $sp, -8					#libera espaco na pilha
	sw $ra, 0($sp)						#salva o endereco  de retorno na pilha
#corpo
	li $t1, 0						#contador do tamanho do arquivo
	
	loop_tamanho:
		sw $t1, 4($sp)
		li $v0, 14					#leitura
		move $a0, $s0					#descritor do arquivo
		la $a1, buffer					#carrega endereco do buffer para salvar a instrucao
		li $a2, 4					#le de 4 em 4 bytes para garantir que considera todas as instrucoes
		syscall
		
		lw $t1, 4($sp)					#carrega o contador
		
		move $t2, $v0					#guarda o valor de bytes lidos
		
		beqz $t2, fim_loop_tamanho			#verifica se chegou ao final
		bltz $t2, erro					#verifica se houve problemas na leitura
		
		add $t1, $t1, $t2				#contador += nDeBytesLidos
    		
		j loop_tamanho
	
	fim_loop_tamanho:
	sw $t1, 4($sp)						#salva t1 na pilha
    		
	jal fecharArquivo
	
	#abre o arquivo novamente
	la $a0, arq
	li $a1, 0
	li $a2, 0
	jal abrirArquivo
	
#epilogo			
	move $v1, $v0						#move o novo descritor para $v1
	lw $ra 0($sp)						#carrega $ra da pilha
	lw $v0 4($sp)						#carrega o valor do contador da pilha
	addiu $sp, $sp, 8					#restaura a pilha
			
   	jr $ra
#-------------------------------------------------------------------------------
# procedimento lerInstrucao
# ------------------------------------------------------------------------------
# mapa da pilha
# $sp+0		$ra	:	endereco de retorno
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	descritor do arquivo
# $a1	:	endereco para guardar a leitura
# Retorno do procedimento:
# $v0	:	
#
#-------------------------------------------------------------------------------
lerInstrucao:
#prologo
	addiu $sp, $sp, -4					#libera espaco na pilha
	sw $ra, 0($sp)						#salva $ra
	
#corpo
	loop_leitura:
		li $v0, 14					#codigo leitura
		move $a0, $s0					#move o descritor para $a0
		la $a1, buffer
		li $a2, 4					#n de bytes a serem lidos
		syscall					
		
		#verifica se bytes foram lidos ou se houve erro, caso nao, vai para depois do loop
		add $t0, $v0, $zero
		
		beq $t0, 0, fim_loop
		bltz $t0, erro
		
		#salva a ultima instrucao no vetor
		la $t0, buffer					#carrega endereco do buffer da pilha
		lw $a0, 0($t0)					#carrega a ultima instrucao lida
		jal salvaInstrucao
			
		j loop_leitura
	fim_loop:
#epilogo
	lw $ra, 0($sp)						#carrega $ra
	addiu $sp, $sp, 4					#devolve o espaco da pilha
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento salvaInstrucao
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	instrucao
#	
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
salvaInstrucao:
	la $t0, instrucoes						#endereco da variavel que guarda o numero de instrucoes
	add $t1, $s1, 0							#endereco base do vetor
	
	#obtem o proximo endereco
	lw $t2, 0($t0)							#carrega o valor de t0
	sll $t4, $t2, 2							#deslocamento
	add $t4, $t1, $t4						#endereco para inserir uma nova instrucao
	
	#atualiza o contador de instrucoes e guarda os valores
	addiu $t2, $t2, 1
	sw $t2, 0($t0)
	sw $a0, 0($t4)
	
	jr $ra
#-------------------------------------------------------------------------------
# procedimento executaPrograma
# ------------------------------------------------------------------------------
# mapa da pilha
# $sp+0		$ra	:	endereco de retorno
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
#
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
executaPrograma:
#prologo
	addiu $sp, $sp, -4							#libera espaco na pilha
	sw $ra, 0($sp)								#salva $ra na pilha
#corpo
	la $t0, instrucoes							#carrega endereco do total de instrucoes
	lw $t0, 0($t0)								#carrega valor do total de instrucoes
	la $t1, registradores							#carrega endereco base do vetor de registradores
	la $t2, pcSimulado							#carrega endereco do pcSimulado
	lw $t3, 0($t2)								#carrega o valor de pcSimulado
	loopExecucao:
		beqz, $t0, fimDaExecucao
		#obtem instrucao do vetor de instrucoes
		sll $t4, $t3, 2							#calcula deslocamento
		add $t4, $s1, $t4						#$s1 = endereco base do vetor de instrucoes, calcula o endereco da instrucao atual
		lw $a0, 0($t4)							#carrega instrucao atual
		
		#executa instrucao
		jal executaInstrucao
						
		la $t2, pcSimulado						#carrega endereco do pcSimulado
		lw $t3, 0($t2)							#carrega valor atual de pcSimulado
		addiu $t3, $t3, 1						#aumenta o contador pc simulado
		sw $t3, 0($t2)							#salva novo valor de pcSimulado
		subi $t0, $t0, 1						#decrementa o contador de instrucoes em 1
		j loopExecucao
#epilogo
	lw $ra, 0($sp)								#carrega $ra da pilha
	addiu $sp, $sp, 4							#restaura a pilha
	fimDaExecucao:
	jr $ra
#-------------------------------------------------------------------------------
# procedimento executaInstrucao
# ------------------------------------------------------------------------------
# mapa da pilha
# $sp+0		$ra	:	endereco de retorno
# $sp+4		$a0	:	instrucao a ser executada
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0		:	instrucao a ser executada
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
executaInstrucao:
#prologo:
	addiu $sp, $sp, -8							#libera espaco na pilha
	sw $ra, 0($sp)								#salva $ra na pilha
	sw $a0, 4($sp)								#salva $a0 na pilha
#corpo:
	#obtem opcode
	srl $t0, $a0, 26							#desloca os 6 bits mais signifativos para os 6 menos significativos
	andi $t0, $t0, 0x3F							#mascara para obter os bits menos significativos

	#verifica tipo de opcode
	
	#verifica se a instrucao e tipo j (j = 2 e jal = 3)
	li $t1, 2
	beq $t0, $t1, tipo_j
	li $t1, 3
	beq $t0, $t1, tipo_j
	
	verifica_opcode:
	li $t1, 0x00
	beq $t0, $t1, tipo_r							#se opcode = 00 a instrucao e de tipo r
	#se nao j e nem r, a instrucao e tipo i
	tipo_i:
	jal executaTipoI
	j epilogo_executa_instrucao
	tipo_j:
	jal executaTipoJ
	j epilogo_executa_instrucao
	tipo_r:
	jal executaTipoR
	j epilogo_executa_instrucao
#epilogo:
	epilogo_executa_instrucao:
	lw $ra, 0($sp)
	addiu $sp, $sp, 8
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento executaTipoI
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0		:	instrucao a ser executada
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
executaTipoI:

#-------------------------------------------------------------------------------
# procedimento executaTipoJ
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0		:	instrucao a ser executada
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
executaTipoJ:

#-------------------------------------------------------------------------------
# procedimento executaTipoR
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0		:	instrucao a ser executada
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
executaTipoR:

#-------------------------------------------------------------------------------
# procedimento fecharArquivo
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	descritor do arquivo
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
fecharArquivo:
	li $v0, 16						#codigo para fechar o arquivo
	syscall
	
	jr $ra
	
imprimeVetor:
	addiu $sp, $sp, -12
	sw $ra, 0($sp)
	li $t0, 0
	add $t1, $s1, 0
	loop1:
	bge $t0, 49, final
	# load word from addrs and goes to the next addrs
    	lw      $a0, 0($t1)
    	addi    $t1, $t1, 4
    	sw $t0, 4($sp)
    	sw $t1, 8($sp)
    	
    	jal imprime_binario
    	
    	lw $t0, 4($sp)
    	lw $t1, 8($sp)
    	#increment counter
    	addi    $t0, $t0, 1
    	j      loop1
    	
    	final:
    	lw $ra, 0($sp)
    	addiu $sp, $sp, 12
    	jr $ra
    	
imprime_binario:
    add $t1, $a0, $zero
    li $t2, 32
    print_bits:
    beq $t2, 0, end_print    # Se o contador de bits chegar a 0, termine

    # Extraia o bit mais significativo (31º bit)
    andi $t3, $t1, 0x80000000 # Isola o bit mais significativo
    srl $t3, $t3, 31         # Desloca o bit isolado para a posição menos significativa

    # Converte o bit para um caractere ASCII ('0' ou '1')
    addi $t3, $t3, 48        
    li $v0, 11               # Syscall para imprimir caractere
    move $a0, $t3            # Move o caractere para $a0
    syscall                  # Chama a syscall para imprimir o caractere

    # Desloca o número para a esquerda para processar o próximo bit
    sll $t1, $t1, 1         
    subi $t2, $t2, 1         # Decrementa o contador de bits
    j print_bits             # Repete para o próximo bit

end_print:
    # Imprime uma nova linha para finalizar
    li  $a0, 10
    li  $v0, 11  
    syscall
    jr $ra
