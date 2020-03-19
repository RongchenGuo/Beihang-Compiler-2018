.data
string0: .asciiz "successfully reach the playing func"
string1: .asciiz "testing if"
string2: .asciiz "calculating the factorial of 3"
string3: .asciiz "calculating the factorial of 4"
string4: .asciiz "the number is not 3 or 4"
string5: .asciiz "testing for"
string6: .asciiz "testing while"
string7: .asciiz "True"
string8: .asciiz "True"
string9: .asciiz "! ~}|{abcABC<=+-$%&*()/"
.text
subi $sp $sp 124
addi $t8 $sp 0
li $t0 622
sw $t0 0x4($sp)
li $t0 1020
sw $t0 0x8($sp)
li $t0 95
sw $t0 0xc($sp)
li $t0 102
sw $t0 0x10($sp)
li $t0 71
sw $t0 0x14($sp)
li $t0 -213
sw $t0 0x18($sp)
li $t0 9
sw $t0 0x1c($sp)
li $t0 42
sw $t0 0x20($sp)
li $t0 43
sw $t0 0x24($sp)
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
slt $t2 $t0 $t1
slti $t2 $t2 1
slt $t3 $t1 $t0
slti $t3 $t3 1
and $t0 $t2 $t3
bne $t0 1 LAB0
li $v0 1
j fend_factorial
j LAB1
LAB0:
lw $t0 0x4($sp)
li $t1 1
sub $t0 $t0 $t1
sw $t0 0xc($sp)
lw $t0 0xc($sp)
addi $t7 $sp 0
subi $t7 $t7 56
sw $t0 ($t7)
jal factorial
sw $v0 0x10($sp)
lw $t0 0x4($sp)
lw $t1 0x10($sp)
mul $t0 $t0 $t1
sw $t0 0x14($sp)
lw $v0 0x14($sp)
j fend_factorial
LAB1:
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
returnplus:subi $sp $sp 40
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
subi $sp $sp 0
li $v0 43
j fend_returnplus
fend_returnplus:
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
returnbirth:subi $sp $sp 40
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
lw $t0 0x8($t8)
sw $t0 0x8($sp)
li $t0 2
sw $t0 0x4($sp)
lw $t0 0x4($sp)
lw $t1 0x8($sp)
addu $t0 $t0 $t1
sw $t0 0xc($sp)
lw $t0 0x4($sp)
lw $t1 0x4($sp)
mul $t0 $t0 $t1
sw $t0 0x10($sp)
lw $t0 0xc($sp)
lw $t1 0x10($sp)
sub $t0 $t0 $t1
sw $t0 0x14($sp)
lw $t0 0x14($sp)
sw $t0 0x8($sp)
lw $v0 0x8($sp)
j fend_returnbirth
fend_returnbirth:
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
printchar:subi $sp $sp 40
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
subi $sp $sp 4
li $v0 11
lw $a0 0x4($sp)
syscall
j fend_printchar
fend_printchar:
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
playing:subi $sp $sp 40
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
subi $sp $sp 0
li $v0 4
la $a0 string0
syscall
j fend_playing
fend_playing:
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
testif:subi $sp $sp 40
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
subi $sp $sp 24
li $v0 4
la $a0 string1
syscall
lw $t0 0x4($sp)
li $t1 3
slt $t2 $t0 $t1
slti $t2 $t2 1
slt $t3 $t1 $t0
slti $t3 $t3 1
and $t0 $t2 $t3
bne $t0 1 LAB2
lw $t0 0x4($sp)
addi $t7 $sp 0
subi $t7 $t7 56
sw $t0 ($t7)
jal factorial
sw $v0 0x10($sp)
lw $t0 0x10($sp)
sw $t0 0x8($sp)
li $v0 4
la $a0 string2
syscall
li $v0 1
lw $a0 0x8($sp)
syscall
j LAB3
LAB2:
lw $t0 0x4($sp)
li $t1 4
slt $t2 $t0 $t1
slti $t2 $t2 1
slt $t3 $t1 $t0
slti $t3 $t3 1
and $t0 $t2 $t3
bne $t0 1 LAB4
li $t0 4
addi $t7 $sp 0
subi $t7 $t7 56
sw $t0 ($t7)
jal factorial
sw $v0 0x18($sp)
lw $t0 0x18($sp)
sw $t0 0x8($sp)
li $v0 4
la $a0 string3
syscall
li $v0 1
lw $a0 0x8($sp)
syscall
j LAB5
LAB4:
li $v0 4
la $a0 string4
syscall
LAB5:
LAB3:
fend_testif:
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
testfor:subi $sp $sp 40
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
subi $sp $sp 24
li $t0 0
sw $t0 0x8($sp)
li $v0 4
la $a0 string5
syscall
li $t0 0
sw $t0 0xc($sp)
j LAB9
LAB6:
lw $t0 0xc($sp)
lw $t1 0x4($sp)
slt $t0 $t1 $t0
slti $t0 $t0 1
bne $t0 1 LAB7
j LAB9
LAB8:
lw $t0 0xc($sp)
li $t1 1
addu $t0 $t0 $t1
sw $t0 0x14($sp)
lw $t0 0x14($sp)
sw $t0 0xc($sp)
j LAB6
LAB9:
lw $t0 0x8($sp)
lw $t1 0xc($sp)
addu $t0 $t0 $t1
sw $t0 0x18($sp)
lw $t0 0x18($sp)
sw $t0 0x8($sp)
j LAB8
LAB7:
lw $v0 0x8($sp)
j fend_testfor
fend_testfor:
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
testwhile:subi $sp $sp 40
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
subi $sp $sp 36
li $t0 100
sw $t0 0x8($sp)
lw $t0 0x4($sp)
sw $t0 0xc($sp)
lw $t0 0x4($t8)
sw $t0 0x10($sp)
li $v0 4
la $a0 string6
syscall
LAB10:
lw $t0 0xc($sp)
li $t1 0
slt $t0 $t1 $t0
bne $t0 1 LAB11
lw $t0 0x8($sp)
lw $t1 0xc($sp)
sub $t0 $t0 $t1
sw $t0 0x18($sp)
lw $t0 0x18($sp)
sw $t0 0x8($sp)
lw $t0 0xc($sp)
li $t1 1
sub $t0 $t0 $t1
sw $t0 0x1c($sp)
lw $t0 0x1c($sp)
sw $t0 0xc($sp)
j LAB10
LAB11:
lw $t0 0x10($sp)
li $t1 2
mul $t0 $t0 $t1
sw $t0 0x20($sp)
lw $t0 0x8($sp)
lw $t1 0x20($sp)
addu $t0 $t0 $t1
sw $t0 0x24($sp)
lw $v0 0x24($sp)
j fend_testwhile
fend_testwhile:
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
subi $sp $sp 160
li $t0 63
sw $t0 0x34($sp)
li $t0 9
sw $t0 0x38($sp)
li $t0 2
sw $t0 0x3c($sp)
li $t0 0
sw $t0 0x28($sp)
j LAB15
LAB12:
lw $t0 0x28($sp)
lw $t1 0x1c($t8)
slt $t0 $t0 $t1
bne $t0 1 LAB13
j LAB15
LAB14:
lw $t0 0x28($sp)
li $t1 1
addu $t0 $t0 $t1
sw $t0 0x54($sp)
lw $t0 0x54($sp)
sw $t0 0x28($sp)
j LAB12
LAB15:
lw $t0 0x28($sp)
lw $t1 0x28($sp)
mul $t0 $t0 $t1
sw $t0 0x58($sp)
lw $t1 0x28($sp)
mul $t1 $t1 4
addi $t1 $t1 4
lw $t0 0x58($sp)
addu $t1 $t1 $sp
sw $t0 ($t1)
lw $t1 0x28($sp)
mul $t1 $t1 4
addi $t1 $t1 4
addu $t1 $t1 $sp
lw $t0 ($t1)
sw $t0 0x5c($sp)
li $v0 1
lw $a0 0x5c($sp)
syscall
lw $t1 0x28($sp)
mul $t1 $t1 4
addi $t1 $t1 4
addu $t1 $t1 $sp
lw $t0 ($t1)
sw $t0 0x60($sp)
lw $t0 0x60($sp)
li $t1 1
addu $t0 $t0 $t1
sw $t0 0x64($sp)
lw $t1 0x28($sp)
mul $t1 $t1 4
addi $t1 $t1 92
lw $t0 0x64($sp)
addu $t1 $t1 $t8
sw $t0 ($t1)
lw $t1 0x28($sp)
mul $t1 $t1 4
addi $t1 $t1 92
addu $t1 $t1 $t8
lw $t0 ($t1)
sw $t0 0x68($sp)
li $v0 1
lw $a0 0x68($sp)
syscall
j LAB14
LAB13:
lw $t0 0x3c($sp)
li $t1 1
addu $t0 $t0 $t1
sw $t0 0x6c($sp)
lw $t0 0x34($sp)
lw $t1 0x6c($sp)
mul $t0 $t0 $t1
sw $t0 0x70($sp)
lw $t0 0x70($sp)
lw $t1 0x38($sp)
div $t0 $t0 $t1
sw $t0 0x74($sp)
lw $t0 0x74($sp)
sw $t0 0x40($sp)
li $v0 1
lw $a0 0x40($sp)
syscall
li $v0 5
syscall
sw $v0 0x44($sp)
li $v0 5
syscall
sw $v0 0x48($sp)
li $v0 5
syscall
sw $v0 0x4c($sp)
lw $t0 0x34($sp)
li $t1 72
addu $t0 $t0 $t1
sw $t0 0x78($sp)
lw $t0 0x78($sp)
lw $t1 0x38($sp)
div $t0 $t0 $t1
sw $t0 0x7c($sp)
lw $t0 0x4c($sp)
addi $t7 $sp 0
subi $t7 $t7 72
sw $t0 ($t7)
jal testwhile
sw $v0 0x80($sp)
lw $t0 0x7c($sp)
lw $t1 0x80($sp)
sub $t0 $t0 $t1
sw $t0 0x84($sp)
lw $t0 0x84($sp)
sw $t0 0x40($sp)
li $v0 1
lw $a0 0x40($sp)
syscall
lw $t0 0x34($sp)
lw $t1 0x38($sp)
slt $t2 $t0 $t1
slt $t3 $t1 $t0
or $t0 $t2 $t3
bne $t0 1 LAB16
li $v0 4
la $a0 string7
syscall
li $v0 1
li $a0 1
syscall
j LAB17
LAB16:
LAB17:
lw $t0 0x34($sp)
lw $t1 0x3c($sp)
slt $t0 $t0 $t1
slti $t0 $t0 1
bne $t0 1 LAB18
li $v0 4
la $a0 string8
syscall
li $v0 1
li $a0 2
syscall
j LAB19
LAB18:
LAB19:
li $v0 4
la $a0 string9
syscall
lw $t0 0x44($sp)
addi $t7 $sp 0
subi $t7 $t7 60
sw $t0 ($t7)
jal testif
lw $t0 0x48($sp)
addi $t7 $sp 0
subi $t7 $t7 60
sw $t0 ($t7)
jal testfor
sw $v0 0x90($sp)
lw $t0 0x90($sp)
sw $t0 0x2c($sp)
li $v0 1
lw $a0 0x2c($sp)
syscall
lw $t0 0x4c($sp)
addi $t7 $sp 0
subi $t7 $t7 72
sw $t0 ($t7)
jal testwhile
sw $v0 0x94($sp)
lw $t0 0x94($sp)
sw $t0 0x2c($sp)
li $v0 1
lw $a0 0x2c($sp)
syscall
li $t0 6
addi $t7 $sp 0
subi $t7 $t7 56
sw $t0 ($t7)
jal factorial
sw $v0 0x98($sp)
lw $t0 0x98($sp)
sw $t0 0x2c($sp)
li $v0 1
lw $a0 0x2c($sp)
syscall
jal playing
lw $t0 0xc($t8)
addi $t7 $sp 0
subi $t7 $t7 40
sw $t0 ($t7)
jal printchar
lw $t0 0x24($t8)
addi $t7 $sp 0
subi $t7 $t7 40
sw $t0 ($t7)
jal printchar
jal returnplus
sw $v0 0x9c($sp)
lw $t0 0x9c($sp)
sw $t0 0x30($sp)
li $v0 11
lw $a0 0x30($sp)
syscall
jal returnbirth
sw $v0 0xa0($sp)
lw $t0 0xa0($sp)
sw $t0 0x2c($sp)
li $v0 1
lw $a0 0x2c($sp)
syscall
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
