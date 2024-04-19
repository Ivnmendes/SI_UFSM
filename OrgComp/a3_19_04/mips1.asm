.text

# variavelA = variavelB + 1
la $t0, variavelB #carrega a variavelB no registrador $t0
lw $t1, 0($t0) #carrega o valor da variavelB no registrador $t1

addiu $t2, $t1, 1 #soma o valor de $t1 com 1 e guarda no reg $t2

la $t0, variavelA #carrega a variavelA no registrador $t0
sw $t2, 0($t0) #salva o valor de $t2 na variavelA

# variavelC = variavelB + 1000000
la $t0, variavelB #carrega a variavelB no registrador $t0
lw $t1, 0($t0) #carrega o valor da variavelB no registrador $t1

# 1000000 e muito grande para o uso de addiu (max 16 bits)
# 1000000 em hexdecimal e igual a 0x000F_4240
lui $t3, 0x000F #carrega nos bits mais significativos de $t3
ori $t3, 0x4240 #faz um or entre $t3 e 0x4240 

add $t2, $t1, $t3 # $t2 = valor da variavelB + $t3 (1000000)

la $t0, variavelC #carrega a variavelC no reg $t0
sw $t2, 0($t0) #salva o valor de $t2 na variavelC

.data
variavelA:.word 0
variavelB: .word 1234
variavelC: .word 0