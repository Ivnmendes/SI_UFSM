# Projeto: Simulador MIPS
# Arquivo: mips1.asm
# Descricao: Trabalho 1 da disciplina de Organização de Computadores
# Autor: Ivan Mendes Martignago
# Data: 21/06/24
.data
	arq:		.asciiz		"trabalho_01-2024_1.bin"		#endereco do arquivo
	buffer:		.space		4					#buffer para armazenar dados lidos
	#tamanhoArquivo	.space
	hex_digits: .asciiz "0123456789ABCDEF"
	newline: .asciiz "\n"
.text

.globl main

	main:
		jal leituraDeArquivo

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
	la $a0, arq						#endereco do arquivo
	li $a1, 0						#modo de leitura
	li $a2, 0						#permissao, usado no modo leitura apenas
	jal abrirArquivo
	
	add $s0, $v0, $zero					#salva o descritor para nao ser perdido
	
	#tamanho do arquivo
	add $a0, $s0, $zero					#salva o descritor em $a0
	jal obtemTamanhoArquivo
	
	add $s0, $v0, $zero					#salva o novo descritor para nao ser perdido
	
	#inicia leitura
	add $a0, $s0, $s0					#salva o descritor em $a0
	la $a1, buffer						#local onde a leitura vai ser salva
	la $a2, 4						#numero de bytes a serem lidos
	
	jal lerInstrucao

	#fecha o arquivo
	temp:
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
	addiu $sp, $sp, -8
	sw $ra, 0($sp)
#corpo
	li $t1, 0						#contador do tamanho do arquivo
	#move $t0, $a0						#t0 = descritor
	
	loop_tamanho:
		sw $t1, 4($sp)
		li $v0, 14					#leitura
		move $a0, $s0					#descritor do arquivo
		la $a1, buffer
		li $a2, 4					#le de 4 em 4 bytes para garantir que considera todas as instrucoes
		syscall
		
		lw $t1, 4($sp)
		
		move $t2, $v0					#guarda o valor de bytes lidos
		
		#add $t1, $t1, $t2				#contador += nDeBytesLidos
		
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
	move $v1, $v0
	lw $ra 0($sp)
	lw $v0 4($sp)
	addiu $sp, $sp, 8
			
   	jr $ra
#-------------------------------------------------------------------------------
# procedimento lerInstrucao
# ------------------------------------------------------------------------------
# mapa da pilha
# $sp+8		$a1	:	endereco onde a instrucao e guardada
# $sp+4		$a0	:	descritor do arquivo
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
	addiu $sp, $sp, -12					#libera espaco na pilha
	sw $ra, 0($sp)						#salva $ra
	sw $a0, 4($sp)						#salva o descritor
	sw $a1, 8($sp)						#salva o endereco
	
#corpo
	loop_leitura:
		li $v0, 14					#codigo leitura
		lw $a0, 4($sp)					#carrega o descritor da pilha
		lw $a1, 8($sp)					#carrega endereco do buffer da pilha
		li $a2, 4					#n de bytes a serem lidos
		syscall					
		
		#verifica se bytes foram lidos, caso nao, vai para depois do loop
		add $t0, $v0, $zero
		beq $t0, 0, fim_loop
	
		move $a0, $t0
		jal executaInstrucao
		
		j loop_leitura
	fim_loop:
#epilogo
	lw $ra, 0($sp)						#carrega $ra
	addiu $sp, $sp, 12					#devolve o espaco da pilha
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento executaInstrucao
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	descritor do arquivo
# $a1	:	endereco para guardar a leitura
# $a2	:	
# Retorno do procedimento:
# $v0	:	descritor do arquivo
#
#-------------------------------------------------------------------------------
executaInstrucao:


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