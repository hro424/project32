# This program calculates Fibonacci number.

	mov	r0, 1
	mov	r1, 0x1
	mov	r2, 10		# max
.loop:
	beq	.out		# branch if under-carry
	add	r0, r1
	swp	r0, r1
	sub	r2, 1
	jmp	.loop
.out:
	jmp	.out
