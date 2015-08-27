	.syntax unified
	.arch armv7-a
	.cpu cortex-a15
	.text
	.align 2
	.thumb
	.thumb_func

	.global findGCDv2
	.type findGCDv2, function

findGCDv2:
	@ ADD/MODIFY CODE BELOW
	@ PROLOG
	push {r3, lr}

.L3:
	@ R0=R0%R1
	sdiv r3, r0, r1
	mls r0, r3, r1, r0

	@ if R0 == 0 goto .L4 (which returns R1)
	cmp r0, #0
	beq .L4

	@ if R0 == 1 goto .L5 (which returns R0)
	cmp r0, #1
	beq .L5

	@ R1=R1%R0
	sdiv r3, r1, r0
	mls r1, r3, r0, r1

	@ if R1 == 0 goto .L5 (which returns R0)
	cmp r1, #0
	beq .L5

	@ if R1 == 1 goto .L4 (which returns R1)
	cmp r1, #1
	beq .L4

	@ others goto .L3
	bne .L3

.L4:
	@ return R1
	mov r0, r1
	pop {r3, pc}		@ EPILOG

.L5:
	@ return R0
	pop {r3, pc}		@ EPILOG

	.size findGCDv2, .-findGCDv2
	.end
