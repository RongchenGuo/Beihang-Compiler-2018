.data
string0: .asciiz " x = "
string1: .asciiz " y = "
string2: .asciiz " SWAP x = "
string3: .asciiz " SWAP y = "
string4: .asciiz " OVERFLOW!          "
string5: .asciiz " complete number: "
string6: .asciiz "  "
string7: .asciiz "          "
string8: .asciiz " ---------------------------------------------------------------          "
string9: .asciiz " b = "
string10: .asciiz " ---------------------------------------------------------------          "
string11: .asciiz " "
string12: .asciiz "          "
string13: .asciiz "          The total is "
string14: .asciiz " 10! = "
.text
subi $sp $sp 4
addi $t8 $sp 0
li $t0 512
sw $t0 0x4($sp)
j main
factorial:subi $sp $sp 40
sw $ra 4($sp)
sw $t9 8($sp)
sw $s0 12($sp)
sw $s1 16($sp)
sw $s2 20($sp)
sw $s3 24($sp)
sw $s4 28($sp)
sw $s5 32($sp)
sw $s6 36($sp)
sw $s7 40($sp)
addi $t9 $sp 0
subi $sp $sp 20
lw $t0 0x4($sp)
li $t1 1
slt $t0 $t1 $t0
slti $t0 $t0 1
bne $t0 1 LAB0
li $v0 1
j fend_factorial
j LAB1
LAB0:
LAB1:
lw $t0 0x4($sp)
li $t1 1
sub $s0 $t0 $t1
addi $t7 $sp 0
subi $t7 $t7 56
sw $s0 ($t7)
jal factorial
addi $s1 $v0 0
lw $t0 0x4($sp)
mul $s2 $t0 $s1
addi $v0 $s2 0
j fend_factorial
fend_factorial:
addi $sp $t9 0
lw $s0 12($sp)
lw $s1 16($sp)
lw $s2 20($sp)
lw $s3 24($sp)
lw $s4 28($sp)
lw $s5 32($sp)
lw $s6 36($sp)
lw $s7 40($sp)
lw $ra 4($sp)
lw $t9 8($sp)
addi $sp $sp 40
jr $ra
mod:subi $sp $sp 40
sw $ra 4($sp)
sw $t9 8($sp)
sw $s0 12($sp)
sw $s1 16($sp)
sw $s2 20($sp)
sw $s3 24($sp)
sw $s4 28($sp)
sw $s5 32($sp)
sw $s6 36($sp)
sw $s7 40($sp)
addi $t9 $sp 0
subi $sp $sp 20
lw $t0 0x4($sp)
addi $s0 $t0 0
lw $t1 0x8($sp)
div $s1 $s0 $t1
lw $t1 0x8($sp)
mul $s2 $s1 $t1
sub $t0 $s0 $s2
sw $t0 0x4($sp)
lw $v0 0x4($sp)
j fend_mod
fend_mod:
addi $sp $t9 0
lw $s0 12($sp)
lw $s1 16($sp)
lw $s2 20($sp)
lw $s3 24($sp)
lw $s4 28($sp)
lw $s5 32($sp)
lw $s6 36($sp)
lw $s7 40($sp)
lw $ra 4($sp)
lw $t9 8($sp)
addi $sp $sp 40
jr $ra
swap:subi $sp $sp 40
sw $ra 4($sp)
sw $t9 8($sp)
sw $s0 12($sp)
sw $s1 16($sp)
sw $s2 20($sp)
sw $s3 24($sp)
sw $s4 28($sp)
sw $s5 32($sp)
sw $s6 36($sp)
sw $s7 40($sp)
addi $t9 $sp 0
subi $sp $sp 12
li $v0 4
la $a0 string0
syscall
li $v0 1
lw $a0 0x4($sp)
syscall
li $v0 4
la $a0 string1
syscall
li $v0 1
lw $a0 0x8($sp)
syscall
lw $t0 0x4($sp)
addi $s1 $t0 0
lw $t0 0x8($sp)
addi $s2 $t0 0
addi $s0 $s1 0
sw $s1 0x8($sp)
sw $s2 0x4($sp)
li $v0 4
la $a0 string2
syscall
li $v0 1
lw $a0 0x4($sp)
syscall
li $v0 4
la $a0 string3
syscall
li $v0 1
lw $a0 0x8($sp)
syscall
fend_swap:
addi $sp $t9 0
lw $s0 12($sp)
lw $s1 16($sp)
lw $s2 20($sp)
lw $s3 24($sp)
lw $s4 28($sp)
lw $s5 32($sp)
lw $s6 36($sp)
lw $s7 40($sp)
lw $ra 4($sp)
lw $t9 8($sp)
addi $sp $sp 40
jr $ra
complete_num:subi $sp $sp 40
sw $ra 4($sp)
sw $t9 8($sp)
sw $s0 12($sp)
sw $s1 16($sp)
sw $s2 20($sp)
sw $s3 24($sp)
sw $s4 28($sp)
sw $s5 32($sp)
sw $s6 36($sp)
sw $s7 40($sp)
addi $t9 $sp 0
subi $sp $sp 732
lw $t0 0x4($sp)
addi $s1 $t0 0
LAB2:
lw $t1 0x4($t8)
slt $t0 $s1 $t1
bne $t0 1 LAB3
li $t0 1
addi $s0 $t0 0
sw $s1 0x214($sp)
li $t0 0
li $t1 1
sub $s4 $t0 $t1
LAB4:
slt $t0 $s0 $s1
bne $t0 1 LAB5
div $t0 $s1 $s0
sw $t0 0x244($sp)
lw $t0 0x244($sp)
mul $t0 $t0 $s0
sw $t0 0x218($sp)
addi $t7 $sp 0
subi $t7 $t7 56
sw $s1 ($t7)
addi $t7 $sp 0
subi $t7 $t7 52
sw $s0 ($t7)
jal mod
sw $v0 0x248($sp)
lw $t0 0x248($sp)
li $t1 0
slt $t2 $t0 $t1
slti $t2 $t2 1
slt $t3 $t1 $t0
slti $t3 $t3 1
and $t0 $t2 $t3
bne $t0 1 LAB6
sw $s4 0x250($sp)
lw $t0 0x214($sp)
sw $t0 0x254($sp)
lw $t0 0x254($sp)
sub $t0 $t0 $s0
sw $t0 0x214($sp)
lw $t0 0x250($sp)
li $t1 1
addu $s4 $t0 $t1
li $t1 128
slt $t0 $s4 $t1
slti $t0 $t0 1
bne $t0 1 LAB8
li $v0 4
la $a0 string4
syscall
j LAB9
LAB8:
LAB9:
li $t1 128
slt $t0 $s4 $t1
bne $t0 1 LAB10
mul $t1 $s4 4
addi $t1 $t1 8
addu $t1 $t1 $sp
sw $s0 ($t1)
j LAB11
LAB10:
LAB11:
j LAB7
LAB6:
LAB7:
addi $s2 $s0 0
li $t1 1
addu $s0 $s2 $t1
j LAB4
LAB5:
lw $t0 0x214($sp)
li $t1 0
slt $t2 $t0 $t1
slti $t2 $t2 1
slt $t3 $t1 $t0
slti $t3 $t3 1
and $t0 $t2 $t3
bne $t0 1 LAB12
li $v0 4
la $a0 string5
syscall
li $v0 1
addi $a0 $s1 0
syscall
li $t0 0
addi $s0 $t0 0
LAB14:
slt $t0 $s4 $s0
slti $t0 $t0 1
bne $t0 1 LAB15
li $v0 4
la $a0 string6
syscall
mul $t1 $s0 4
addi $t1 $t1 8
addu $t1 $t1 $sp
lw $t0 ($t1)
sw $t0 0x26c($sp)
li $v0 1
lw $a0 0x26c($sp)
syscall
addi $s2 $s0 0
li $t1 1
addu $s0 $s2 $t1
j LAB14
LAB15:
li $v0 4
la $a0 string7
syscall
j LAB13
LAB12:
LAB13:
sw $s1 0x270($sp)
lw $t0 0x270($sp)
li $t1 1
addu $s1 $t0 $t1
j LAB2
LAB3:
li $v0 4
la $a0 string8
syscall
li $t0 0
addi $s7 $t0 0
li $t0 0
addi $s0 $t0 0
LAB16:
lw $t1 0x4($t8)
slt $t0 $s0 $t1
bne $t0 1 LAB17
sw $s7 0x278($sp)
addi $s2 $s0 0
mul $t0 $s1 $s4
sw $t0 0x238($sp)
li $t1 1
addu $s0 $s2 $t1
lw $t0 0x278($sp)
mul $s5 $t0 $s2
addu $t0 $s5 $s5
sw $t0 0x27c($sp)
lw $t0 0x27c($sp)
lw $t1 0x238($sp)
addu $s7 $t0 $t1
j LAB16
LAB17:
addi $s5 $s7 0
li $t0 0
addi $s0 $t0 0
LAB18:
lw $t1 0x4($t8)
slt $t0 $s0 $t1
bne $t0 1 LAB19
sw $s5 0x284($sp)
addi $s2 $s0 0
li $t1 1
addu $s0 $s2 $t1
lw $t0 0x284($sp)
addu $s5 $t0 $s2
j LAB18
LAB19:
li $v0 4
la $a0 string9
syscall
li $v0 1
addi $a0 $s5 0
syscall
li $v0 4
la $a0 string10
syscall
li $t0 0
addi $s6 $t0 0
li $t0 1
sw $t0 0x228($sp)
li $t0 2
addi $s3 $t0 0
LAB20:
lw $t1 0x4($t8)
slt $t0 $t1 $s3
slti $t0 $t0 1
bne $t0 1 LAB21
li $t0 2
addi $s0 $t0 0
li $t1 2
div $t0 $s3 $t1
sw $t0 0x220($sp)
LAB22:
lw $t1 0x220($sp)
slt $t0 $t1 $s0
slti $t0 $t0 1
bne $t0 1 LAB23
div $t0 $s3 $s0
sw $t0 0x290($sp)
lw $t0 0x290($sp)
mul $t0 $t0 $s0
sw $t0 0x22c($sp)
addi $t7 $sp 0
subi $t7 $t7 56
sw $s3 ($t7)
addi $t7 $sp 0
subi $t7 $t7 52
sw $s0 ($t7)
jal mod
sw $v0 0x294($sp)
lw $t0 0x294($sp)
li $t1 0
slt $t2 $t0 $t1
slti $t2 $t2 1
slt $t3 $t1 $t0
slti $t3 $t3 1
and $t0 $t2 $t3
bne $t0 1 LAB24
li $t0 0
sw $t0 0x228($sp)
j LAB25
LAB24:
LAB25:
addi $s2 $s0 0
li $t1 1
addu $s0 $s2 $t1
j LAB22
LAB23:
lw $t0 0x228($sp)
li $t1 1
slt $t2 $t0 $t1
slti $t2 $t2 1
slt $t3 $t1 $t0
slti $t3 $t3 1
and $t0 $t2 $t3
bne $t0 1 LAB26
li $v0 4
la $a0 string11
syscall
li $v0 1
addi $a0 $s3 0
syscall
sw $s6 0x2a0($sp)
lw $t0 0x2a0($sp)
li $t1 1
addu $s6 $t0 $t1
li $t1 10
div $t0 $s6 $t1
sw $t0 0x2a4($sp)
lw $t0 0x2a4($sp)
li $t1 10
mul $t0 $t0 $t1
sw $t0 0x22c($sp)
lw $t0 0x22c($sp)
slt $t2 $t0 $s6
slti $t2 $t2 1
slt $t3 $s6 $t0
slti $t3 $t3 1
and $t0 $t2 $t3
bne $t0 1 LAB28
li $v0 4
la $a0 string12
syscall
j LAB29
LAB28:
LAB29:
j LAB27
LAB26:
LAB27:
sw $s3 0x2ac($sp)
li $t0 1
sw $t0 0x228($sp)
lw $t0 0x2ac($sp)
li $t1 1
addu $s3 $t0 $t1
j LAB20
LAB21:
li $v0 4
la $a0 string13
syscall
li $v0 1
addi $a0 $s6 0
syscall
fend_complete_num:
addi $sp $t9 0
lw $s0 12($sp)
lw $s1 16($sp)
lw $s2 20($sp)
lw $s3 24($sp)
lw $s4 28($sp)
lw $s5 32($sp)
lw $s6 36($sp)
lw $s7 40($sp)
lw $ra 4($sp)
lw $t9 8($sp)
addi $sp $sp 40
jr $ra
main:subi $sp $sp 40
sw $ra 4($sp)
sw $t9 8($sp)
sw $s0 12($sp)
sw $s1 16($sp)
sw $s2 20($sp)
sw $s3 24($sp)
sw $s4 28($sp)
sw $s5 32($sp)
sw $s6 36($sp)
sw $s7 40($sp)
addi $t9 $sp 0
subi $sp $sp 8
li $t0 5
addi $t7 $sp 0
subi $t7 $t7 56
sw $t0 ($t7)
jal factorial
addi $s0 $v0 0
sw $s0 0x4($sp)
li $v0 4
la $a0 string14
syscall
li $v0 1
lw $a0 0x4($sp)
syscall
li $t0 5
addi $t7 $sp 0
subi $t7 $t7 48
sw $t0 ($t7)
li $t0 10
addi $t7 $sp 0
subi $t7 $t7 44
sw $t0 ($t7)
jal swap
li $t0 2
addi $t7 $sp 0
subi $t7 $t7 768
sw $t0 ($t7)
jal complete_num
fend_main:
addi $sp $t9 0
lw $s0 12($sp)
lw $s1 16($sp)
lw $s2 20($sp)
lw $s3 24($sp)
lw $s4 28($sp)
lw $s5 32($sp)
lw $s6 36($sp)
lw $s7 40($sp)
lw $ra 4($sp)
lw $t9 8($sp)
addi $sp $sp 40
li $v0 10
syscall
