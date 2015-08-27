	.syntax unified
	.arch armv7-a
	.cpu cortex-a15
	.text
	.align 2
	.thumb
	.thumb_func

	.global findGCDv3
	.type findGCDv3, function

findGCDv3:
	@ ADD/MODIFY CODE BELOW
	@ PROLOG
	push {r3, lr}

.L3:
	@ if R0 < R1 goto .L5
	cmp r0, r1
	blt .L5

	@ if R0 > R1*4 goto .L4
	cmp r0, r1, LSL #2
	bgt .L4

	@ R0=R0-R1
	subs r0, r0, r1

	@ if R0 == 0 goto .L7 (which returns R1)
	beq .L7

	@ if R0 == 1 goto .L8 (which returns R0)
	cmp r0, #1
	beq .L8

	@ others goto .L5
	bne .L5

.L4:
	@ R0=R0%R1
	sdiv r3, r0, r1
	mls r0, r3, r1, r0

	@ if R0 == 0 goto .L7 (which returns R1)
	cmp r0, #0
	beq .L7

	@ if R0 == 1 goto .L8 (which returns R0)
	cmp r0, #1
	beq .L8

.L5:
	@ if R0 > R1 goto .L3
	cmp r0, r1
	bgt .L3

	@ if R1 > R0*4 goto .L6
	cmp r1, r0, LSL #2
	bgt .L6

	@ R1=R1-R0
	subs r1, r1, r0

	@ if R1 == 0 goto .L8 (which returns R0)
	beq .L8

	@ if R1 == 1 goto .L7 (which returns R1)
	cmp r1, #1
	beq .L7

	@ others goto .L3
	bne .L3

.L6:
	@ R1=R1%R0
	sdiv r3, r1, r0
	mls r1, r3, r0, r1

	@ if R1 == 0 goto .L8 (which returns R0)
	cmp r1, #0
	beq .L8

	@ if R1 == 1 goto .L7 (which returns R1)
	cmp r1, #1
	beq .L7

	@ others goto .L3
	bne .L3

.L7:
	@ return R1
	mov r0, r1
	pop {r3, pc}		@ EPILOG

.L8:
	@ return R0
	pop {r3, pc}		@ EPILOG

	.size findGCDv3, .-findGCDv3
	.end
