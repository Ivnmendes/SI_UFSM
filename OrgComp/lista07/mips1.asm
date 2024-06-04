# 1 int a[10]={0,1,2,3,4,5,6,7,8,9};
# 2 int i, j, k;
# 3
# 4 int main(void)
# 5 {
# 6 i = 1;
# 7 j = 3;
# 8 k = 4;
# 9 a[0] = 5;
# 10 a[2] = a[0] + 20;
# 11 a[3] = a[4] + 200000;
# 12 a[4] = 10000;
# 13 a[5] = a[6] + a[7] - a[8];
# 14 a[6] = a[7] - i;
# 15 a[7] = a[8] - a[j];
# 16 a[j] = a[i+k] - i + j;
# 17 a[k] = a[a[i]];
# 18 return 0;
# 19 }

.text
#i = 1;
la $t0, i		#carrega o endereço de i em t0
addiu $t2, $zero, 1	#adiciona 1 no t2
sw $t2, 0($t0)		#salva 1 no endereço da variavel

#j = 3;
la $t0, j		#carrega o endereço de j em t0
addiu $t2, $zero, 3	#adiciona 3 no t2
sw $t2, 0($t0)		#salva 3 no endereço da variavel

#k = 4;
la $t0, k		#carrega o endereço de k em t0
addiu $t2, $zero, 4	#adiciona 4 no t2
sw $t2, 0($t0)		#salva 4 no endereço da variavel

#a[0] = 5;
la $t0, a		#carrega o vetor a[] em t0
li $t1, 0		#indice inicial
li $t2, 4		#tamanho de cada elemento do vetor
mul $t3, $t1, $t2	#t3 = i*tam
add $a0, $t0, $t3	#a0 recebe o endereço de a[0]
li $t4, 5		#salva 5 em t4
sw $t4, 0($a0)		#a[0] = 5

#a[2] = a[0] + 20
li $t1, 2		#indice 2
mul $t3, $t1, $t2	#t3 = i*tam
add $a0, $t0, $t3	#a0 recebe o endereço de a[2]
lw $t4, 0($t0)		#t4 = a[0]
addiu $t7, $t4, 20	#t7 = t4 + 20
sw $t7, 0($a0)		#a[0] = 5

#a[3] = a[4] + 200000
li $t1, 3		#indice 3
li $t3, 4		#indice 4
mul $t4, $t1, $t2	#t4 = i*tam
mul $t5, $t3, $t2	#t5 = i*tam
add $a0, $t0, $t4	#a0 recebe o endereço de a[3]
add $a2, $t0, $t5	#a2 recebe o endereço de a[4]
lw $t6, 0($a2)		#t6 = a[0]
lui $t7, 0x0003		#200000 e muito grande para usar li, portanto se carrega os bits mais significativos primeir0
ori $t7, 0x0D40		#faz um or entre t7 e o resto do numero
add $t1, $t6, $t7
sw $t1, 0($a0)

# Imprimir o valor de a[0]
lw $t5, 0($a0)      # Carrega o valor de a[0] em $t5
li $v0, 1           # Código do syscall para imprimir inteiro
move $a0, $t5       # Move o valor de a[0] para $a0
syscall             # Chama o syscall para imprimir o valor
    
# Finalizando o programa
li $v0, 10          # Código do syscall para terminar o programa
syscall

.data
i: .word 0
j: .word 0
k: .word 0
a: .word 0,1,2,3,4,5,6,7,8,9