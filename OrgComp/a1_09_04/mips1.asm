# Projeto:
# Arquivo:
# Descricao:
# Autor:
# Data:

# Anotacoes
	# Tipos de registradores
		# $zero: Reservado para o numero 0
		# $at: Reservado temporario para o assembly
		# $vX:
		# $aX:
		# $t0 - $t7: Temporario (nao preservado na chamada da funcao)
		# $sX: Salvo (preservado na chamada da funcao)
		# $t8, $t9: Temporario
		# $kX:
		# $gp: Ponteiro global
		# $sp:
		# $fp:
		# $ra:

.text
# Codigo
nop			# nop: no operation (nao faz nada)
li	$t0, 12		# li: carrega imediatamente (atribui 12 ao registrador $t0) - equivalente de "addiu $t0, %0, 0x0000000C
la	$t1, loop	# la: carrega endereco
loop:			#
add 	$t1, $t2, $t3 	# 
lw 	$a0, 16($a1)	#
sw 	$a0, 32($a1)	#
beq 	$t1, $t2, loop	# beq: desvio condicional (se $t1 == $t2 desvia para loop)
j 	loop		# j: desvie o codigo para tal endereco

# Carregar arquivo binario na memoria
# Enquanto nao terminaram as instrucoes
	# (1) Ler uma instrucao
	# (2) Decodificar a instrucao
	# (3) Executar a instrucao
# Terminar programa

.data
# dados do simulador

# Variaveis memoria
	# Segmento da dados
	# Segmento de codigo
	# Segmento da pilha
# Registradores
# Campos da instrucao
