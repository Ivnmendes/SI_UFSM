# Projeto: Simulador MIPS
# Arquivo: mips1.asm
# Descricao: Trabalho 1 da disciplina de OrganizaÃ§Ã£o de Computadores
# Autor: Ivan Mendes Martignago
# Data: 21/06/24

# remover depois>>> conteudo dos registradores $sx
# $s0: descritor do arquivo aberto
# $s1: eb vetor instrucoes
#
#TODO:
# ( ) problema no acesso a pilha virtual
# (x) .data				:	f
# TIPO R
	# (x) ADD			:	ft
	# (x) syscall			:	ft
	# (x) JR			:	ft
	# (x) ADDU			:	ft
# TIPO J
	# (x) J				:	ft
	# (x) JAL			:	ft
# TIPO I
	# (x) ADDI			:	ft
	# (x) ADDIU			:	ft
	# (x) LW			:	ft
	# (x) SW			:	ft
	# (x) bne			:	ft
	# (x) ori			:	ft
	# (x) lui			:	ft
# PSEUDOINSTRUCAO
	# (x) MUL			:	ft
	
# |-------------|---------------|
# |legenda	|	status	|
# |-------------|---------------|
# |	ft  	|falta testar	|
# |	nf  	|nao funcionando|
# |	f 	|funcionando	|
# |-----------------------------|

.data
	dataVirtual:		.space		1024				#.data virtual
	buffer:			.space		4				#buffer para armazenar dados lidos
	pilhaVirtual:		.space		1024				#pilha virtual que o registrador $sp virtual ira utilizar
	arqBin:			.asciiz		"trabalho_01-2024_1.bin"	#endereco do arquivo onde estao as instrucoes
	arqData:		.asciiz		"trabalh0_01-2024_1.dat"	#endereco do arquivo onde esta guardado o .data do programa
	instrucoes:		.word		0				#numero de intrucoes guardadas no vetor
	registradores:		.space		128				#vetor com registradores simulados, tentarei seguir a mesma lógica padrão (pos 31 do vetor e o registrador $ra)
	#pcSimulado:		.word		0				#salva a posicao atual executada do vetor
	pcSimulado:		.word		0x00400000
	
.text

.globl main

	main:
		jal iniciaRegistradores						#inicia os registradores virtuais em 0
		jal leituraDeArquivoData
		jal leituraDeArquivoBin						#faz a leitura do arquivo
		jal executaPrograma						#executa o programa a partir do vetor de instrucoes
		#jal imprimeVetor
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
	la $t2, registradores							#carrega endereco base do vetor de registradores
	li $t3, 32								#numero de registradores
	#inicia todos os registradores com 0
	iniciaRegistradoresLoop:
		beq $t3, $zero, registradoresIniciados  			#se todos os registradores foram inicializados, sai do loop
    		sw $zero, 0($t2)  						#inicializa registrador com 0
    		addi $t2, $t2, 4  						#avanca para o proximo registrador
    		subi $t3, $t3, 1  						#decrementa o contador
    		j iniciaRegistradoresLoop
    	registradoresIniciados:
    	
    	#inicia o registrador $sp virutual
    	la $t0, pilhaVirtual
    	la $t1, registradores
    	addi $t0, $t0, 1024							#move o ponteiro para o final da pilha
    	sw $t0, 116($t1)							#carrega endereco de $sp, (testar depois, possivelmente endereco errado)
    	jr $ra


#-------------------------------------------------------------------------------
# procedimento leituraDeArquivoBin
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
leituraDeArquivoBin:
#prologo
	addiu $sp, $sp, -4							#libera espaco na pilha
	sw $ra, 0($sp)								#guarda $ra na pilha

#corpo
	#la $s1, instrucoes							#endereco base do vetor de instrucoes
	la $a0, arqBin								#endereco do arquivo
	li $a1, 0								#modo de leitura
	li $a2, 0								#permissao, usado no modo leitura apenas
	jal abrirArquivo
	
	add $s0, $v0, $zero							#salva o descritor para nao ser perdido
	
	#tamanho do arquivo
	add $a0, $s0, $zero							#salva o descritor em $a0
	jal obtemTamanhoArquivo
	
	add $s0, $v1, $zero							#salva o novo descritor para nao ser perdido
	
	#aloca memoria para o vetor de instrucoes
	move $a0, $v0								#numero de bytes alocados e o retorno da funcao de obter tamanho do arquivo
	li $v0, 9								#codigo syscall de alocacao de memoria
	syscall

	move $s1, $v0								#endereco base do vetor
		
	#inicia leitura
	add $a0, $s0, $zero							#salva o descritor em $a0
	la $a1, buffer								#local onde a leitura vai ser salva
	la $a2, 4								#numero de bytes a serem lidos
	jal lerInstrucao

	#fecha o arquivo
	add $a0, $s0, $zero							#descritor como parametro
	jal fecharArquivo
	
#epilogo
	lw $ra, 0($sp)								#carrega $ra da pilha
	addiu $sp, $sp, 4							#devolve espaco da pilha
	
	jr $ra

#-------------------------------------------------------------------------------
# procedimento leituraDeArquivoData
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
leituraDeArquivoData:
#prologo
	addiu $sp, $sp, -4							#libera espaco na pilha
	sw $ra, 0($sp)								#guarda $ra na pilha

#corpo
	#la $s1, instrucoes							#endereco base do vetor de instrucoes
	la $a0, arqData								#endereco do arquivo
	li $a1, 0								#modo de leitura
	li $a2, 0								#permissao, usado no modo leitura apenas
	jal abrirArquivo
	
	add $s2, $v0, $zero							#salva o descritor para nao ser perdido
		
	#inicia leitura
	add $a0, $s2, $zero							#salva o descritor em $a0
	la $a1, dataVirtual							#local onde a leitura vai ser salva
	la $a2, 1024								#numero de bytes a serem lidos
	jal lerData

	#fecha o arquivo
	add $a0, $s2, $zero							#descritor como parametro
	jal fecharArquivo
	
#epilogo
	lw $ra, 0($sp)								#carrega $ra da pilha
	addiu $sp, $sp, 4							#devolve espaco da pilha
	
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
	li $v0, 13								#codigo para abertura
	syscall									#retorna o descritor
	
	bltz $v0, erro								#verifica se o arquivo foi abertor corretamente

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
	addiu $sp, $sp, -8							#libera espaco na pilha
	sw $ra, 0($sp)								#salva o endereco  de retorno na pilha
#corpo
	li $t1, 0								#contador do tamanho do arquivo
	
	loop_tamanho:
		sw $t1, 4($sp)
		li $v0, 14							#leitura
		move $a0, $s0							#descritor do arquivo
		la $a1, buffer							#carrega endereco do buffer para salvar a instrucao
		li $a2, 4							#le de 4 em 4 bytes para garantir que considera todas as instrucoes
		syscall
		
		lw $t1, 4($sp)							#carrega o contador
		
		move $t2, $v0							#guarda o valor de bytes lidos
		
		beqz $t2, fim_loop_tamanho					#verifica se chegou ao final
		bltz $t2, erro							#verifica se houve problemas na leitura
		
		add $t1, $t1, $t2						#contador += nDeBytesLidos
    		
		j loop_tamanho
	
	fim_loop_tamanho:
	sw $t1, 4($sp)								#salva t1 na pilha
    		
	jal fecharArquivo
	
	#abre o arquivo novamente
	la $a0, arqBin
	li $a1, 0
	li $a2, 0
	jal abrirArquivo
	
#epilogo			
	move $v1, $v0								#move o novo descritor para $v1
	lw $ra 0($sp)								#carrega $ra da pilha
	lw $v0 4($sp)								#carrega o valor do contador da pilha
	addiu $sp, $sp, 8							#restaura a pilha
			
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
	addiu $sp, $sp, -4					#		libera espaco na pilha
	sw $ra, 0($sp)								#salva $ra
	
#corpo
	loop_leitura:
		li $v0, 14							#codigo leitura
		move $a0, $s0							#move o descritor para $a0
		la $a1, buffer
		li $a2, 4							#n de bytes a serem lidos
		syscall					
		
		#verifica se bytes foram lidos ou se houve erro, caso nao, vai para depois do loop
		add $t0, $v0, $zero
		
		beq $t0, 0, fim_loop
		bltz $t0, erro
		
		#salva a ultima instrucao no vetor
		la $t0, buffer							#carrega endereco do buffer da pilha
		lw $a0, 0($t0)							#carrega a ultima instrucao lida
		jal salvaInstrucao
			
		j loop_leitura
	fim_loop:
#epilogo
	lw $ra, 0($sp)								#carrega $ra
	addiu $sp, $sp, 4							#devolve o espaco da pilha
	jr $ra

#-------------------------------------------------------------------------------
# procedimento lerData
# ------------------------------------------------------------------------------
# mapa da pilha
# $sp+0		$ra	:	endereco de retorno
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	descritor do arquivo
# $a1	:	endereco para guardar a leitura
# $a2	:	numero de bytes a serem lidos
# Retorno do procedimento:
# $v0	:	
#
#-------------------------------------------------------------------------------
lerData:
	li $v0, 14								#codigo leitura
	syscall					

	bltz $v0, erro
	
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
	la $t0, instrucoes							#endereco da variavel que guarda o numero de instrucoes
	add $t1, $s1, 0								#endereco base do vetor
	
	#obtem o proximo endereco
	lw $t2, 0($t0)								#carrega o valor de t0
	sll $t4, $t2, 2								#deslocamento
	add $t4, $t1, $t4							#endereco para inserir uma nova instrucao
	
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
		#codigo experimental
		subiu $t4, $t3, 0x00400000
		div $t4, $t4, 4							#conversao para formato de indice
		
		sll $t4, $t4, 2							#calcula deslocamento
		add $t4, $s1, $t4						#$s1 = endereco base do vetor de instrucoes, calcula o endereco da instrucao atual
		lw $a0, 0($t4)							#carrega instrucao atual
		
		#executa instrucao
		jal executaInstrucao
			
		#realiza operacoes necessarias para a proxima instrucao			
		la $t2, pcSimulado						#carrega endereco do pcSimulado
		lw $t3, 0($t2)							#carrega valor atual de pcSimulado
		#addiu $t3, $t3, 1						#aumenta o contador pc simulado
		addiu $t3, $t3, 4 #experimental
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
	srl $a1, $a0, 26							#desloca os 6 bits mais signifativos para os 6 menos significativos
	andi $a1, $a1, 0x3F							#mascara para obter os bits menos significativos

	#verifica tipo de opcode
	#verifica se a instrucao e do tipo pseudo (por enquanto, intervalo entre 24 e 31)
	li $t0, 24
	li $t1, 31
	ble $t0, $a1, nao_pseudo
	ble $t1, $a1, tipo_pseudo
	
	nao_pseudo:
	#verifica se a instrucao e tipo j (j = 2 e jal = 3)
	li $t1, 2
	beq $a1, $t1, tipo_j
	li $t1, 3
	beq $a1, $t1, tipo_j
	
	verifica_opcode:
	li $t1, 0x00
	beq $a1, $t1, tipo_r							#se opcode = 00 a instrucao e de tipo r
	#se nao j, r e nem pseudo, a instrucao e tipo i
	tipo_i:
	jal executaTipoI
	j epilogo_executa_instrucao
	
	tipo_j:
	jal executaTipoJ
	j epilogo_executa_instrucao
	
	tipo_r:
	jal executaTipoR
	j epilogo_executa_instrucao
	
	tipo_pseudo:
	jal executaTipoPseudo
#epilogo:
	epilogo_executa_instrucao:
	lw $ra, 0($sp)
	addiu $sp, $sp, 8
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento executaTipoI
# ------------------------------------------------------------------------------
# mapa da pilha
#  $sp+0	$ra	:	endereco de retorno
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0		:	instrucao a ser executada
# $a1		:	opcode
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
executaTipoI:
#prologo
	addiu $sp, $sp, -4							#libera espaco na pilha
	sw $ra, 0($sp)								#salva o endereco de retorno na pilha
	move $t0, $a0								#coloca a instrucao em outro registrador
	move $t1, $a1								#coloca o opcode em t1
	la $t2, registradores
#corpo
	#extrai rs
	srl $a0, $t0, 21							#transfere os bits referentes a rs para os 5 menos significativos
	andi $t3, $a0, 0x1F							#faz um and entre o valor obtido e 0001 1111
	#carrega rs
	sll $a0, $t3, 2								#calcula o deslocamento para chegar no registrador rs
	add $a0, $t2, $a0							#endereco desejado
	
	#testa se rs e o registrador $sp
	bne $t3, 29, nao_sp_rs_i
	
	#ajusta rs para a pilha virtual
	lw $a0, 0($a0)								#carrega o endereco da pilha
	
	nao_sp_rs_i:
	#extrai rt
	srl $a1, $t0, 16							#transfere os bits referentes a rt para os 5 menos significativos
	andi $t3, $a1, 0x1F							#faz um and entre o valor obtido e 0001 1111
	#carrega rt
	sll $a1, $t3, 2								#calcula o deslocamento para chegar no registrador rt
	add $a1, $t2, $a1							#endereco desejado
	
	#testa se rt e o registrador $sp
	bne $t3, 29, nao_sp_rt_i
	
	#ajusta rs para a pilha virtual
	lw $a1, 0($a1)								#carrega o endereco da pilha
	
	nao_sp_rt_i:
	#extrai imm
	andi $a2, $t0, 0xFFFF							#faz um and entre a instrucao e 1111 1111 1111 1111
	
	beq $t1, 5, jump_bne
	beq $t1, 8, jump_addi
	beq $t1, 9, jump_addiu
	beq $t1, 13, jump_ori
	beq $t1, 15, jump_lui
	beq $t1, 35, jump_lw
	beq $t1, 43, jump_sw
	
	j epilogo_executa_tipo_i
	
	jump_bne:
	jal opBne
	j epilogo_executa_tipo_i
	
	jump_addi:
	jal opAddi
	j epilogo_executa_tipo_i
	
	jump_addiu:
	jal opAddiu
	j epilogo_executa_tipo_i
	
	jump_ori:
	jal opOri
	j epilogo_executa_tipo_i
	
	jump_lui:
	jal opLui
	j epilogo_executa_tipo_i
	
	jump_lw:
	jal opLw
	j epilogo_executa_tipo_i
	
	jump_sw:
	jal opSw
	
#epilogo
	epilogo_executa_tipo_i:
	lw $ra, 0($sp)								#carrega o endereco de retorno da pilha
	addiu $sp, $sp, 4							#restaura a pilha
	
	jr $ra

#-------------------------------------------------------------------------------
# procedimento executaTipoJ
# ------------------------------------------------------------------------------
# mapa da pilha
#  $sp+0	$ra	:	endereco de retorno
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0		:	instrucao a ser executada
# $a1		:	opcode
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
executaTipoJ:
#prologo
	addiu $sp, $sp, -4							#libera espaco na pilha
	sw $ra, 0($sp)								#salva o endereco de retorno na pilha
	move $t0, $a0								#coloca a instrucao em outro registrador
#corpo
	#extrai imm
	andi $a0, $t0, 0x3FFFFFF						#faz um and entre a instrucao e 0011 1111 1111 1111 1111 1111 1111

	beq $a1, 2, jump_j
	beq $a1, 3, jump_jal
	
	j epilogo_executa_tipo_j
	
	jump_j:
	jal opJ
	j epilogo_executa_tipo_j
	
	jump_jal:
	jal opJal
	
#epilogo
	epilogo_executa_tipo_j:
	lw $ra, 0($sp)								#carrega o endereco de retorno da pilha
	addiu $sp, $sp, 4							#restaura a pilha
	
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento executaTipoR
# ------------------------------------------------------------------------------
# mapa da pilha
#  $sp+0	$ra	:	endereco de retorno
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0		:	instrucao a ser executada
# $a1		:	opcode (necessario em alguns casos)
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
executaTipoR:
#prologo
	addiu $sp, $sp, -4							#libera espaco na pilha
	sw $ra, 0($sp)								#salva o endereco de retorno na pilha
	move $t0, $a0								#coloca a instrucao em outro registrador
	la $t2, registradores
#corpo
	#extrai rs
	srl $a0, $t0, 21							#transfere os bits referentes a rs para os 5 menos significativos
	andi $t3, $a0, 0x1F							#faz um and entre o valor obtido e 0001 1111
	
	#carrega rs
	sll $a0, $t3, 2								#calcula o deslocamento para chegar no registrador rs
	add $a0, $t2, $a0							#endereco desejado
	
	#testa se rs e o registrador $sp
	bne $t3, 29, nao_sp_rs_r
	
	#ajusta rs para a pilha virtual
	lw $a0, 0($a0)								#carrega o endereco da pilha
	
	nao_sp_rs_r:
	#extrai rt
	srl $a1, $t0, 16							#transfere os bits referentes a rt para os 5 menos significativos
	andi $t3, $a1, 0x1F							#faz um and entre o valor obtido e 0001 1111
	#carrega rt
	sll $a1, $t3, 2								#calcula o deslocamento para chegar no registrador rt
	add $a1, $t2, $a1							#endereco desejado
	
	#testa se rt e o registrador $sp
	bne $t3, 29, nao_sp_rt_r
	
	#ajusta rs para a pilha virtual
	lw $a1, 0($a1)								#carrega o endereco da pilha
	
	nao_sp_rt_r:
	#extrai rd
	srl $a2, $t0, 11							#transfere os bits referentes a rd para os 5 menos significativos
	andi $t3, $a2, 0x1F							#faz um and entre o valor obtido e 0001 1111
	#carrega rd
	sll $a2, $t3, 2								#calcula o deslocamento para chegar no registrador rd
	add $a2, $t2, $a2							#endereco desejado
	
	#testa se rd e o registrador $sp
	bne $t3, 29, nao_sp_rd_r
	
	#ajusta rs para a pilha virtual
	lw $a2, 0($a2)								#carrega o endereco da pilha
	
	nao_sp_rd_r:
	#extrai shamt	
	srl $a3, $t0, 6								#transfere os bits referentes a shamt para os 5 menos significativos
	andi $a3, $a3, 0x1F							#faz um and entre o valor obtido e 0001 1111
	#extrai o funct
	andi $t1, $t0, 0x3F							#faz um and entre a instrucao e 0011 1111
	
	beq $t1, 8, jump_jr
	beq $t1, 12, jump_syscall
	beq $t1, 32, jump_add
	beq $t1, 33, jump_addu
	
	j epilogo_executa_tipo_r
	
	jump_jr:
	jal opJr
	j epilogo_executa_tipo_r
	
	jump_syscall:
	jal opSyscall
	j epilogo_executa_tipo_r
	
	jump_add:
	jal opAdd
	j epilogo_executa_tipo_r
	
	jump_addu:
	jal opAddu
	
#epilogo
	epilogo_executa_tipo_r:
	lw $ra, 0($sp)								#carrega o endereco de retorno da pilha
	addiu $sp, $sp, 4							#restaura a pilha
	
	jr $ra

#-------------------------------------------------------------------------------
# procedimento executaTipoJ
# ------------------------------------------------------------------------------
# mapa da pilha
#  $sp+0	$ra	:	endereco de retorno
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0		:	instrucao a ser executada
# $a1		:	opcode
# Retorno do procedimento:
# 
#
#-------------------------------------------------------------------------------
executaTipoPseudo:
#prologo
	addiu $sp, $sp, -4							#libera espaco na pilha
	sw $ra, 0($sp)								#salva o endereco de retorno na pilha
	move $t0, $a0								#coloca a instrucao em outro registrador
#corpo
	#extrai rs
	srl $a0, $t0, 21							#transfere os bits referentes a rs para os 5 menos significativos
	andi $a0, $a0, 0x1F							#faz um and entre o valor obtido e 0001 1111
	#extrai rt
	srl $a1, $t0, 16							#transfere os bits referentes a rt para os 5 menos significativos
	andi $a1, $a1, 0x1F							#faz um and entre o valor obtido e 0001 1111
	#extrai rd
	srl $a2, $t0, 11							#transfere os bits referentes a rd para os 5 menos significativos
	andi $a2, $a2, 0x1F							#faz um and entre o valor obtido e 0001 1111
	#extrai shamt	
	srl $a3, $t0, 6								#transfere os bits referentes a shamt para os 5 menos significativos
	andi $a3, $a3, 0x1F							#faz um and entre o valor obtido e 0001 1111
	#extrai o funct
	andi $t1, $t0, 0x3F							#faz um and entre a instrucao e 0011 1111
	
	beq $t1, 2, jump_mul
	
	j epilogo_executa_tipo_pseudo
	
	jump_mul:
	jal opMul
	j epilogo_executa_tipo_pseudo
	
#epilogo
	epilogo_executa_tipo_pseudo:
	lw $ra, 0($sp)								#carrega o endereco de retorno da pilha
	addiu $sp, $sp, 4							#restaura a pilha
	
	jr $ra
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
	li $v0, 16								#codigo para fechar o arquivo
	syscall
	
	jr $ra
	
#-------------------------------------------------------------------------------#
#										#
#		Procedimentos para executar instrucoes em mips			#
#										#
#-------------------------------------------------------------------------------#

#-------------------------------------------------------------------------------#
#					Tipo I					#
#-------------------------------------------------------------------------------#

#-------------------------------------------------------------------------------
# procedimento opBne
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	imm
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opBne:
	#carrega endereco do pcSimulado
	la $t1, pcSimulado
	
	lw $a0, 0($a0)								#carrega o valor salvo no registrador virtual
	
	lw $a1, 0($a1)								#carrega o valor salvo no registrador virtual
	
	#faz o teste
	beq $a0, $a1, fim_teste_bne
	#desvio = pc + 4 + (imm * 4), (obs: pc+4 e feito no looping de instrucoes
	lw $t2, 0($t1)								#carrega o valor atual de pc
	sll $a2, $a2, 2								#imm * 4
	add $t2, $t2, $a2							#endereco desejado
	
	sw $t2, 0($t1)								#muda o valor de pc para o endereco desejado
	
	fim_teste_bne:
	jr $ra

#-------------------------------------------------------------------------------
# procedimento opAddi
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	imm
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opAddi:
	#converte para numero com sinal
	andi $t0, $a2, 0x8000							#mascara para ver qual o bit mais significativo
	beq $t0, $zero, nao_convertido_addi					#se positivo, nao faz nada
	
	ori $a2, $a2, 0xFFFF0000						#transforma em numero com sinal
	
	nao_convertido_addi:
	
	lw $a0, 0($a0)								#carrega o valor salvo no registrador virtual
	
	add $t1, $a0, $a2							#t1 recebe rs + imm
	
	sw $t1, 0($a1)								#salva o valor no registrador rt
	
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento opAddiu
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	imm
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opAddiu:
	#converte para numero com sinal
	andi $t0, $a2, 0x8000							#mascara para ver qual o bit mais significativo
	beq $t0, $zero, nao_convertido_addiu					#se positivo, nao faz nada
	
	ori $a2, $a2, 0xFFFF0000						#transforma em numero com sinal
	
	nao_convertido_addiu:
	lw $a0, 0($a0)								#carrega o valor salvo no registrador virtual
	
	addu $t1, $a0, $a2							#t1 recebe rs + imm
	sw $t1, 0($a1)								#salva o valor no registrador rt
	
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento opOri
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	imm
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opOri:
	lw $a0, 0($a0)								#carrega o valor salvo no registrador virtual
	
	or $t1, $a0, $a2							#t1 recebe rs Or imm
	sw $t1, 0($a1)           						#salva o valor no registrador rt
	
	jr $ra

#-------------------------------------------------------------------------------
# procedimento opLui
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	imm
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opLui:
	srl $t1, $a2, 16       							#move 16 bits para direita para zerar os 16 menos significativos
   	sll $t1, $t1, 16						 	#move os bits restantes novamente ao local desejado
	sw $t1, 0($a1)           						#salva o valor no registrador rt
	
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento opLw
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	imm
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opLw:
	#lw $a0, 0($a0)
	add $a0, $a0, $a2							#endereco desejado, soma do endereco do registrador e imm. ex: imm = 2 entao lw vai carregar o valor de 2($a0)
	
	lw $t1, 0($a0)           						#carrega o valor no registrador rs
	sw $t1, 0($a1)								#salva o valor em rt
	
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento opSw
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	imm
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opSw:
	#lw $a0, 0($a0)
	add $a0, $a0, $a2							#endereco desejado, soma do endereco do registrador e imm. ex. imm = 2 entao lw vai salvar em 2($a0)
	
	#obtem registrador de rt
	lw $a1, 0($a1)								#carrega o valor salvo no registrador virtual
	
	sw $a1, 0($a0)           						#salva o valor no registrador rs
	
	jr $ra


#-------------------------------------------------------------------------------#
#					Tipo J					#
#-------------------------------------------------------------------------------#

#-------------------------------------------------------------------------------
# procedimento opJ
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	imm
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opJ:
	#carrega endereco e valor do pcSimulado
	la $t0, pcSimulado
	lw $t1, 0($t0)
	
	sll $a0, $a0, 2								#desloca imm em dois bits para a esquerda
	
	li $t2, 0xF0000000							#mascara para extrair os 4 bits mais significativos de pc virtual
	and $t1, $t1, $t2
	
	or $t1, $t1, $a0							#concatena os 4 bits mais significativos de pc com os 26 bits deslocados de imm
	subi $t1, $t1, 4							#gambiarra
	sw $t1, 0($t0)								#salva o novo valor de pcSimulado
	
	jr $ra

#-------------------------------------------------------------------------------
# procedimento opJal
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
opJal:
	#carrega endereco e valor do pcSimulado
	la $t0, pcSimulado
	lw $t1, 0($t0)
	
	#carrega o registrador $ra
	la $t3, registradores							#carrega vetor de registradores
	li $t4, 31								#indice do registrador $ra
	sll $t4, $t4, 2								#deslocamento
	add $t3, $t4, $t3							#endereco desejado
	
	#salva o valor de pc em $ra
	sw $t1, 0($t3)
	
	#seta pcSimulado como o endereco de desvio
	sll $a0, $a0, 2								#desloca imm em dois bits para a esquerda
	li $t2, 0xF0000000							#mascara para extrair os 4 bits mais significativos de pc virtual
	and $t1, $t1, $t2
	or $t1, $t1, $a0							#concatena os 4 bits mais significativos de pc com os 26 bits deslocados de imm
	subi $t1, $t1, 4						#gambiarra
	sw $t1, 0($t0)								#salva o novo valor de pcSimulado
	
	jr $ra
	
#-------------------------------------------------------------------------------#
#					Tipo R					#
#-------------------------------------------------------------------------------#

#-------------------------------------------------------------------------------
# procedimento opJr
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opJr:
	lw $t2, 0($a0)								#carrega o valor contido em registradores[rs]
	
	#salva novo valor de pcSimulado
	la $t0, pcSimulado
	sw $t2, 0($t0)
	
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento opAdd
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	rd
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opAdd:
	#carrega o vetor de registradores
	la $t1, registradores
	
	#carrega rs
	lw $t0, 0($a0)
	
	#carrega rt
	lw $t2, 0($a1)
	
	add $t0, $t0, $t2							#t0 recebe rs + rt
	sw $t0, 0($a2)								#salva no registrador rd
	
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento opAddu
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	rd
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opAddu:
	#carrega o vetor de registradores
	la $t1, registradores
	
	#carrega rs
	lw $t0, 0($a0)
	
	#carrega rt
	lw $t2, 0($a1)
	
	addu $t0, $t0, $t2							#t0 recebe rs + rt (sem sinal)
	sw $t0, 0($a2)								#salva no registrador rd
	
	jr $ra

#-------------------------------------------------------------------------------
# procedimento opSyscall
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# 
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opSyscall:
	#carrega o vetor de registradores
	la $t0, registradores
	
	#carrega $v0 virtual
	li $t1, 2
	sll $t2, $t1, 2								#calcula o deslocamento para chegar no registrador $v0
	add $t2, $t2, $t0							#endereco desejado
	lw $v0, 0($t2)								#carrega valor de $v0 virtual (codigo de funcao do syscall)
	
	#carrega $v1 virtual
	li $t1, 3
	sll $t3, $t1, 2								#calcula o deslocamento para chegar no registrador $v1
	add $t3, $t3, $t0							#endereco desejado
	
	#carrega $a0 virtual
	li $t1, 4
	sll $a0, $t1, 2								#calcula o deslocamento para chegar no registrador $a0
	add $a0, $a0, $t0							#endereco desejado
	lw $a0, 0($a0)
	
	#carrega $a1 virtual
	li $t1, 5
	sll $a1, $t1, 2								#calcula o deslocamento para chegar no registrador $a1
	add $a1, $a1, $t0							#endereco desejado
	lw $a1, 0($a1)
	
	#carrega $a2 virtual
	li $t1, 6
	sll $a2, $t1, 2								#calcula o deslocamento para chegar no registrador $a2
	add $a2, $t0, $a2							#endereco desejado
	lw $a2, 0($a2)
	
	#carrega $a3 virtual
	li $t1, 7
	sll $a3, $t1, 2								#calcula o deslocamento para chegar no registrador $a3
	add $a3, $t0, $a3							#endereco desejado
	lw $a3, 0($a3)
	
	syscall
	
	#guarda o retorno nos registradores virtuais
	sw $v0, 0($t2)
	sw $v1, 0($t3)
	
	jr $ra
	
#-------------------------------------------------------------------------------
# procedimento opMul
# ------------------------------------------------------------------------------
# mapa da pilha
# 
# 
# 
#-------------------------------------------------------------------------------
# Argumentos
# $a0	:	rs
# $a1	:	rt
# $a2	:	rd
# Retorno do procedimento:
# 
#-------------------------------------------------------------------------------
opMul:
	#carrega o vetor de registradores
	la $t1, registradores
	
	#carrega rs
	sll $t0, $a0, 2								#calcula o deslocamento para chegar no registrador rs
	add $t0, $t1, $t0							#endereco desejado
	lw $t0, 0($t0)
	
	#carrega rt
	sll $t2, $a1, 2								#calcula o deslocamento para chegar no registrador rt
	add $t2, $t1, $t2							#endereco desejado
	lw $t2, 0($t2)
	
	#carrega rd
	sll $t3, $a2, 2								#calcula o deslocamento para chegar no registrador rd
	add $t3, $t1, $t3							#endereco desejado
	
	mul $t0, $t0, $t2							#t0 recebe os 32 bits menos significativos do produto entre rs e rt
	sw $t0, 0($t3)								#salva no registrador rd
	
	jr $ra