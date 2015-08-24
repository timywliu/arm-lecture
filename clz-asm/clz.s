	.syntax unified
	.arch armv7-a
	.cpu cortex-a15
	.text
	.align 2
	.thumb
	.thumb_func

	.global clz
	.type clz, function

clz:
	@ ADD/MODIFY CODE BELOW
	@ PROLOG
	push {r3, r4, lr}

	@ if (x == 0) return 32
	mov r3, r0
	cmp r3, #0
	beq .L7

	@ n = 1
	mov r0, #1

	@ if ((x>>16)==0) { n+=16; x<<=16;}
	mov r4, #0
	cmp r4, r3, lsr #16
	bne .L3
	add r0, r0, #16
	lsl r3, r3, #16

.L3:
	@ if ((x>>24)==0) { n+=8; x<<=8;}
	cmp r4, r3, lsr #24
	bne .L4
	add r0, r0, #8
	lsl r3, r3, #8

.L4:
	@ if ((x>>28)==0) { n+=4; x<<=4;}
	cmp r4, r3, lsr #28
	bne .L5
	add r0, r0, #4
	lsl r3, r3, #4

.L5:
	@ if ((x>>30)==0) { n+=2; x<<=2;}
	cmp r4, r3, lsr #30
	bne .L6
	add r0, r0, #2
	lsl r3, r3, #2

.L6:
	@ n = n-(x>>31)
	sub r0, r0, r3, lsr #31
	pop {r3, r4, pc}		@ EPILOG

.L7:
	mov r0, #32
	pop {r3, r4, pc}		@ EPILOG

	.size clz, .-clz
	.end
