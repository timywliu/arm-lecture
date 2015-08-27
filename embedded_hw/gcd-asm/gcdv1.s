	.syntax unified
	.arch armv7-a
	.cpu cortex-a15
	.text
	.align 2
	.thumb
	.thumb_func

	.global findGCDv1
	.type findGCDv1, function

findGCDv1:
	@ ADD/MODIFY CODE BELOW
	@ PROLOG
	push {lr}

.L3:
	@ if R0 == R1 goto .L5 (which returns R0)
	cmp r0, r1
	beq .L5

	@ if(R0 > R1) goto .L4
	bgt .L4

	@ if(R0 < R1) R1=R1-R0 goto .L3
	subs r1, r1, r0
	bgt .L3

.L4:
	@ R0=R0-R1 goto .L3
	subs r0, r0, r1
	bgt .L3

.L5:
	pop {pc}		@ EPILOG

	.size findGCDv1, .-findGCDv1
	.end
