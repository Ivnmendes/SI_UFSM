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
la $t0, i		#carrega o endereÃ§o de i em t0
addiu $s0, $zero, 1	#adiciona 1 no t2
sw $s0, 0($t0)		#salva 1 no endereÃ§o da variavel

#j = 3;
la $t0, j		#carrega o endereÃ§o de j em t0
addiu $s1, $zero, 3	#adiciona 3 no t2
sw $s1, 0($t0)		#salva 3 no endereÃ§o da variavel

#k = 4;
la $t0, k		#carrega o endereÃ§o de k em t0
addiu $s2, $zero, 4	#adiciona 4 no t2
sw $s2, 0($t0)		#salva 4 no endereÃ§o da variavel

#a[0] = 5;
la $t0, a		#carrega o vetor a[] em t0
li $t1, 0		#indice inicial
li $t2, 4		#tamanho de cada elemento do vetor
mul $t3, $t1, $t2	#t3 = i*tam
add $a0, $t0, $t3	#a0 recebe o endereÃ§o de a[0]
li $t4, 5		#salva 5 em t4
sw $t4, 0($a0)		#a[0] = 5

#a[2] = a[0] + 20
li $t1, 2		#indice 2
mul $t3, $t1, $t2	#t3 = i*tam
add $a1, $t0, $t3	#a0 recebe o endereÃ§o de a[2]
lw $t4, 0($t0)		#t4 = a[0]
addiu $t7, $t4, 20	#t7 = t4 + 20
sw $t7, 0($a1)		#a[0] = 5

#a[3] = a[4] + 200000
li $t1, 3		#indice 3
li $t3, 4		#indice 4
mul $t4, $t1, $t2	#t4 = i*tam
mul $t5, $t3, $t2	#t5 = i*tam
add $a1, $t0, $t4	#a0 recebe o endereÃ§o de a[3]
add $a2, $t0, $t5	#a2 recebe o endereÃ§o de a[4]
lw $t6, 0($a2)		#t6 = a[0]
lui $t7, 0x0003		#200000 e muito grande para usar li, portanto se carrega os bits mais significativos primeir0
ori $t7, 0x0D40		#faz um or entre t7 e o resto do numero
add $t1, $t6, $t7	#t1 = a[0] + 200000
sw $t1, 0($a1)		#a[3]

#a[4] = 10000;
li $t1, 4		#indice 4
mul $t3, $t1, $t2	#t3 = 4 * tam
add $a1, $t0, $t3	#salva o endereço de a[4] em $a0 (&a + deslocamento)
li $t4, 10000		#carrega 10000 em t4
sw $t4, 0($a1)		#salva t4 em a[4]

#a[5] = a[6] + a[7] - a[8];
li $t1, 5		#indice 5
li $t9, 6		#indice 6
li $t3, 7		#indice 7
li $t4, 8		#indice 8
mul $t5, $t1, $t2	#t5 = 5 * tam
mul $t6, $t9, $t2	#t6 = 6 * tam
mul $t7, $t3, $t2	#t7 = 7 * tam
mul $t8, $t4, $t2	#t8 = 8 * tam
add $a0, $t0, $t5	#salva o endereço de a[5] em $a0 (&a + deslocamento)
add $a1, $t0, $t6	#salva o endereço de a[6] em $a1 (&a + deslocamento)
add $a2, $t0, $t7	#salva o endereço de a[7] em $a2 (&a + deslocamento)
add $a3, $t0, $t8	#salva o endereço de a[8] em $a3 (&a + deslocamento)
lw $t1, 0($a1)		#salva o valor de a[6] em t1
add $t9, $t1, $zero	#adiciona o valor de t1 na variavel acumuladora
lw $t1, 0($a2)		#salva o valor de a[7] em t1
add $t9, $t1, $t9	#adiciona o valor de t1 na variavel acumuladora
lw $t1, 0($a3)		#salva o valor de a[8] em t1
sub $t9, $t9, $t1	#subtrai o valor de t1 na variavel acumuladora
sw $t9, 0($a0)		#salve o valor de t2 em a[5]

#a[6] = a[7] - i;
li $t1, 6		#indice 6
li $t3, 7		#indice 7
la $a0, i		#carrega o endereco da variavel global i
lw $t7, 0($a0)		#carrega o valor de i
mul $t5, $t2, $t1	#t5 = 6 * tam
mul $t6, $t2, $t3	#t6 = 7 * tam
add $a0, $t0, $t5	#salva o endereço de a[6] em $a0 (&a + deslocamento)
add $a1, $t0, $t6	#salva o endereço de a[7] em $a1 (&a + deslocamento
lw $t1, 0($a1)		#carrega o valor de a[7]
sub $t3, $t1, $t7	#t2 = a[7] - i
sw $t3, 0($a0)		#salva em a[6]

#a[7] = a[8] - a[j]
li $t1, 7		#indice 7
li $t3, 8		#indice 8
mul $t5, $t2, $t1	#t5 = tam * 7
mul $t6, $t2, $t3	#t6 = tam * 8
mul $t7, $t2, $s1	#t7 = tam * j
add $a0, $t5, $t0	#salva o endereço de a[7] em $a0 (&a + deslocamento)
add $a1, $t6, $t0	#salva o endereço de a[8] em $a1 (&a + deslocamento)
add $a2, $t7, $t0	#salva o endereço de a[j] em $a2 (&a + deslocamento)
lw $t1, 0($a1)		#t1 = a[8]
lw $t4, 0($a2)		#t4 = a[j]
sub $t3, $t1, $t4	#t3 = a[8] - a[j]
sw $t3, 0($a0)		#salva em a[7]

#a[j] = a[i+k] - i + j
add $t1, $s0, $s2	#indice i+k (5)
mul $t3, $t2, $s1	#t3 = j * tam
mul $t4, $t2, $t1	#t4 = i+k * tam
add $a0, $t3, $t0	#salva o endereço de a[j] em $a0 (&a + deslocamento)
add $a1, $t4, $t0	#salva o endereço de a[i+k] em $a1 (&a + deslocamento)
lw $t1, 0($a1)		#t1 = a[i+k]
sub $t3, $t1, $s0	#t3 = t1 - i
add $t3, $t3, $s1	#t3 += j
sw $t3, 0($a0)		#salva em a[j]

#a[k] = a[a[i]]
mul $t1, $t2, $s2	#t1 = tam * k
mul $t3, $t2, $s0	#t3 = tam * i
add $a0, $t0, $t1 	#salva o endereço de a[k] em $a0 (&a + deslocamento)
add $a1, $t0, $t3	#salva o endereço de a[i] em $a1 (&a + deslocamento)
lw $t1, 0($a1)		#t1 = a[i]
mul $t3, $t2, $t1	#t3 = tam * a[i]
add $a1, $t0, $t3	#salva o endereço de a[a[i]] em $a1 (&a + deslocamento)
lw $t1, 0($a1)		#t1 = a[a[i]]
sw $t1, 0($a0)		#salva em a[k]

li $t0, 0
la $t1, a
loop1:
	bge $t0, 10, exit
	# load word from addrs and goes to the next addrs
    	lw      $t2, 0($t1)
    	addi    $t1, $t1, 4
	
	#imprime indice
	li      $v0, 1      
    	add	$a0, $t0, $zero
    	syscall
    	#print(":");
    	la $a0, str1
   	li $v0, 4
    	syscall
    	#print(" ");
	li      $a0, 32
    	li      $v0, 11  
    	syscall
    	# syscall to print value
    	li      $v0, 1      
    	move    $a0, $t2
    	syscall
    	#print("\n");
    	la $a0, novaLinha
   	li $v0, 4
    	syscall


    	#increment counter
    	addi    $t0, $t0, 1
    	j      loop1

 	exit:
    		li      $v0, 10
    		syscall
    
##
.data
i: .word 0
j: .word 0
k: .word 0
a: .word 0,1,2,3,4,5,6,7,8,9
str1: .asciiz ":"
novaLinha: .asciiz "\n"

