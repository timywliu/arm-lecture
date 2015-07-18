	.syntax unified
	.arch armv7-a
	.text
	.align 2
	.thumb
	.thumb_func

	.global fibonacci
	.type fibonacci, function

fibonacci:
	@ ADD/MODIFY CODE BELOW
	@ PROLOG
	push {r3, r4, r5, lr}

	@ if(R0 <= 0) goto .L3 (which returns 0)

	@ If R0 == 1 goto .L4 (which returns 1)

	cmp r0, #1
	beq .L4
	blt .L3

	@ i = N - 1
	@ a = 0
	@ b = 1
	sub r5, r0, #1
	mov r3, #0
	mov r4, #1

	@ sum = a + b
	@ a = b
	@ b = sum
	@ i--
	@ if (i > 0) goto fib_forloop
fib_forloop:
	add r0, r3, r4
	mov r3, r4
	mov r4, r0
	subs r5, r5, #1
	bgt fib_forloop

	pop {r3, r4, r5, pc}		@EPILOG

	@ END CODE MODIFICATION
.L3:
	mov r0, #0			@ R0 = 0
	pop {r3, r4, r5, pc}		@ EPILOG

.L4:
	mov r0, #1			@ R0 = 1
	pop {r3, r4, r5, pc}		@ EPILOG

	.size fibonacci, .-fibonacci
	.end
