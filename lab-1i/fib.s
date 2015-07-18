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

	@ R4 = R0 - 0 (update flags)
	@ if(R0 <= 0) goto .L3 (which returns 0)

	@ Compare R4 wtih 1
	@ If R4 == 1 goto .L4 (which returns 1)

	cmp r0, #1
	beq .L4
	blt .L3

	mov r4, r0	@i=N
	mov r1, #0	@a=0
	mov r2, #1	@b=1
fib_forloop:
	add r0, r1, r2	@sum=a+b
	mov r1, r2	@a=b
	mov r2, r0	@b=sum
	sub r4, r4, #1	@i--
	cmp r4, #1
	bgt fib_forloop	@if (i>1) goto fib_forloop


	@ R0 = R4 - 1
	@ Recursive call to fibonacci with R4 - 1 as parameter

	@ R5 = R0
	@ R0 = R4 - 2
	@ Recursive call to fibonacci with R4 - 2 as parameter

	@ R0 = R5 + R0 (update flags)

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
