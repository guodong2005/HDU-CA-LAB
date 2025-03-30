.text
.global _start
_start:
test_2:
	li x3, 2
	li x1, 0
	li x2, 0
	nop
	nop
	nop
	nop
	beq x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	beq x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_3:
	li x3, 3
	li x1, 1
	li x2, 1
	nop
	nop
	nop
	nop
	beq x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	beq x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_4:
	li x3, 4
	li x1, -1
	li x2, -1
	nop
	nop
	nop
	nop
	beq x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	beq x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_5:
	li x3, 5
	li x1, 0
	li x2, 1
	nop
	nop
	nop
	nop
	beq x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	beq x1, x2, 1b
	nop
	nop
3:
test_6:
	li x3, 6
	li x1, 1
	li x2, 0
	nop
	nop
	nop
	nop
	beq x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	beq x1, x2, 1b
	nop
	nop
3:
test_7:
	li x3, 7
	li x1, -1
	li x2, 1
	nop
	nop
	nop
	nop
	beq x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	beq x1, x2, 1b
	nop
	nop
3:
test_8:
	li x3, 8
	li x1, 1
	li x2, -1
	nop
	nop
	nop
	nop
	beq x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	beq x1, x2, 1b
	nop
	nop
3:
test_9:
	li x3, 9
	li x1, 0
	li x2, 0
	nop
	nop
	nop
	nop
	bge x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_10:
	li x3, 10
	li x1, 1
	li x2, 1
	nop
	nop
	nop
	nop
	bge x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_11:
	li x3, 11
	li x1, -1
	li x2, -1
	nop
	nop
	nop
	nop
	bge x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_12:
	li x3, 12
	li x1, 1
	li x2, 0
	nop
	nop
	nop
	nop
	bge x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_13:
	li x3, 13
	li x1, 1
	li x2, -1
	nop
	nop
	nop
	nop
	bge x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_14:
	li x3, 14
	li x1, -1
	li x2, -2
	nop
	nop
	nop
	nop
	bge x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_15:
	li x3, 15
	li x1, 0
	li x2, 1
	nop
	nop
	nop
	nop
	bge x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
3:
test_16:
	li x3, 16
	li x1, -1
	li x2, 1
	nop
	nop
	nop
	nop
	bge x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
3:
test_17:
	li x3, 17
	li x1, -2
	li x2, -1
	nop
	nop
	nop
	nop
	bge x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
3:
test_18:
	li x3, 18
	li x1, -2
	li x2, 1
	nop
	nop
	nop
	nop
	bge x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bge x1, x2, 1b
	nop
	nop
3:
test_19:
	li x3, 19
	li x1, 0
	li x2, 0
	nop
	nop
	nop
	nop
	bgeu x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_20:
	li x3, 20
	li x1, 1
	li x2, 1
	nop
	nop
	nop
	nop
	bgeu x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_21:
	li x3, 21
addiw x1, x0, 1
	nop
	nop
	nop
	nop
slli x1, x1, 0x20
	nop
	nop
	nop
	nop
addiw x1, x1, -1
addiw x2, x0, 1
	nop
	nop
	nop
	nop
slli x2, x2, 0x20
	nop
	nop
	nop
	nop
addiw x2, x2, -1
	nop
	nop
	nop
	nop
	bgeu x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_22:
	li x3, 22
	li x1, 1
	li x2, 0
	nop
	nop
	nop
	nop
	bgeu x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_23:
	li x3, 23
addiw x1, x0, 1
	nop
	nop
	nop
	nop
slli x1, x1, 0x20
	nop
	nop
	nop
	nop
addiw x1, x1, -1
addiw x2, x0, 1
	nop
	nop
	nop
	nop
slli x2, x2, 0x20
	nop
	nop
	nop
	nop
addiw x2, x2, -2
	nop
	nop
	nop
	nop
	bgeu x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_24:
	li x3, 24
addiw x1, x0, 1
	nop
	nop
	nop
	nop
slli x1, x1, 0x20
	nop
	nop
	nop
	nop
addiw x1, x1, -1
	li x2, 0
	nop
	nop
	nop
	nop
	bgeu x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_25:
	li x3, 25
	li x1, 0
	li x2, 1
	nop
	nop
	nop
	nop
	bgeu x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
3:
test_26:
	li x3, 26
addiw x1, x0, 1
	nop
	nop
	nop
	nop
slli x1, x1, 0x20
	nop
	nop
	nop
	nop
addiw x1, x1, -2
addiw x2, x0, 1
	nop
	nop
	nop
	nop
slli x2, x2, 0x20
	nop
	nop
	nop
	nop
addiw x2, x2, -1
	nop
	nop
	nop
	nop
	bgeu x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
3:
test_27:
	li x3, 27
	li x1, 0
addiw x2, x0, 1
	nop
	nop
	nop
	nop
slli x2, x2, 0x20
	nop
	nop
	nop
	nop
addiw x2, x2, -1
	nop
	nop
	nop
	nop
	bgeu x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
3:
test_28:
	li x3, 28
lui x1, 0x80000
	nop
	nop
	nop
	nop
addiw x1, x1, -1
addiw x2, x0, 1
	nop
	nop
	nop
	nop
slli x2, x2, 0x1f
	nop
	nop
	nop
	nop
	bgeu x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bgeu x1, x2, 1b
	nop
	nop
3:
test_29:
	li x3, 29
	li x1, 0
	li x2, 1
	nop
	nop
	nop
	nop
	blt x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	blt x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_30:
	li x3, 30
	li x1, -1
	li x2, 1
	nop
	nop
	nop
	nop
	blt x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	blt x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_31:
	li x3, 31
	li x1, -2
	li x2, -1
	nop
	nop
	nop
	nop
	blt x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	blt x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_32:
	li x3, 32
	li x1, 1
	li x2, 0
	nop
	nop
	nop
	nop
	blt x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	blt x1, x2, 1b
	nop
	nop
3:
test_33:
	li x3, 33
	li x1, 1
	li x2, -1
	nop
	nop
	nop
	nop
	blt x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	blt x1, x2, 1b
	nop
	nop
3:
test_34:
	li x3, 34
	li x1, -1
	li x2, -2
	nop
	nop
	nop
	nop
	blt x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	blt x1, x2, 1b
	nop
	nop
3:
test_35:
	li x3, 35
	li x1, 1
	li x2, -2
	nop
	nop
	nop
	nop
	blt x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	blt x1, x2, 1b
	nop
	nop
3:
test_36:
	li x3, 36
	li x1, 0
	li x2, 1
	nop
	nop
	nop
	nop
	bltu x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bltu x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_37:
	li x3, 37
addiw x1, x0, 1
	nop
	nop
	nop
	nop
slli x1, x1, 0x20
	nop
	nop
	nop
	nop
addiw x1, x1, -2
addiw x2, x0, 1
	nop
	nop
	nop
	nop
slli x2, x2, 0x20
	nop
	nop
	nop
	nop
addiw x2, x2, -1
	nop
	nop
	nop
	nop
	bltu x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bltu x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_38:
	li x3, 38
	li x1, 0
addiw x2, x0, 1
	nop
	nop
	nop
	nop
slli x2, x2, 0x20
	nop
	nop
	nop
	nop
addiw x2, x2, -1
	nop
	nop
	nop
	nop
	bltu x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bltu x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_39:
	li x3, 39
	li x1, 1
	li x2, 0
	nop
	nop
	nop
	nop
	bltu x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bltu x1, x2, 1b
	nop
	nop
3:
test_40:
	li x3, 40
addiw x1, x0, 1
	nop
	nop
	nop
	nop
slli x1, x1, 0x20
	nop
	nop
	nop
	nop
addiw x1, x1, -1
addiw x2, x0, 1
	nop
	nop
	nop
	nop
slli x2, x2, 0x20
	nop
	nop
	nop
	nop
addiw x2, x2, -2
	nop
	nop
	nop
	nop
	bltu x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bltu x1, x2, 1b
	nop
	nop
3:
test_41:
	li x3, 41
addiw x1, x0, 1
	nop
	nop
	nop
	nop
slli x1, x1, 0x20
	nop
	nop
	nop
	nop
addiw x1, x1, -1
	li x2, 0
	nop
	nop
	nop
	nop
	bltu x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bltu x1, x2, 1b
	nop
	nop
3:
test_42:
	li x3, 42
addiw x1, x0, 1
	nop
	nop
	nop
	nop
slli x1, x1, 0x1f
lui x2, 0x80000
	nop
	nop
	nop
	nop
addiw x2, x2, -1
	nop
	nop
	nop
	nop
	bltu x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bltu x1, x2, 1b
	nop
	nop
3:
test_43:
	li x3, 43
	li x1, 0
	li x2, 1
	nop
	nop
	nop
	nop
	bne x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bne x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_44:
	li x3, 44
	li x1, 1
	li x2, 0
	nop
	nop
	nop
	nop
	bne x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bne x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_45:
	li x3, 45
	li x1, -1
	li x2, 1
	nop
	nop
	nop
	nop
	bne x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bne x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_46:
	li x3, 46
	li x1, 1
	li x2, -1
	nop
	nop
	nop
	nop
	bne x1, x2, 2f
	nop
	nop
	bne x0, x3, fail
	nop
	nop
1:	bne x0, x3, 3f
	nop
	nop
2:	bne x1, x2, 1b
	nop
	nop
bne x0, x3, fail
	nop
	nop
3:
test_47:
	li x3, 47
	li x1, 0
	li x2, 0
	nop
	nop
	nop
	nop
	bne x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bne x1, x2, 1b
	nop
	nop
3:
test_48:
	li x3, 48
	li x1, 1
	li x2, 1
	nop
	nop
	nop
	nop
	bne x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bne x1, x2, 1b
	nop
	nop
3:
test_49:
	li x3, 49
	li x1, -1
	li x2, -1
	nop
	nop
	nop
	nop
	bne x1, x2, 1f
	nop
	nop
bne x0, x3, 2f
	nop
	nop
1:	bne x0, x3, fail
	nop
	nop
2:	bne x1, x2, 1b
	nop
	nop
3:
test_50:
	li x3, 50
	li ra, 0
	jal x4, target_50
linkaddr_50:
	nop
	nop
	j fail
	nop
	nop
target_50:
	auipc x2, 0x0
	nop
	nop
	nop
	nop
	addi x2, x2, -20
	nop
	nop
	nop
	nop
	bne x2, x4, fail
	nop
	nop
test_51:
	li x3, 51
	li t0, 0
	auipc x6, 0x0
	nop
	nop
	nop
	nop
	addi x6, x6, 64
	nop
	nop
	nop
	nop
	jalr t0, t1, 0
linkaddr_51:
	nop
	nop
	j fail
	nop
	nop
target_51:
	la t1, linkaddr_51
	nop
	nop
	nop
	nop
	bne t0, t1, fail
	nop
	nop
test_52:
	li x3, 52
	auipc x5, 0x0
	nop
	nop
	nop
	nop
	addi x5, x5, 64
	nop
	nop
	nop
	nop
	jalr t0, t0, 0
linkaddr_52:
	nop
	nop
	j fail
	nop
	nop
target_52:
	auipc x6, 0x0
	nop
	nop
	nop
	nop
	addi x6, x6, -20
	nop
	nop
	nop
	nop
	bne t0, t1, fail
	nop
	nop
	bne x0, x3, pass
	nop
	nop
fail:
1:	beqz x3, 1b
	nop
	nop
	sll x3, x3, 1
	nop
	nop
	nop
	nop
	or x3, x3, 1
	li x17, 93
	nop
	nop
	addi x10, x3, 0
	ecall
pass:
	li x3, 1
	li x17, 93
	li x10, 0
	ecall
