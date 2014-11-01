# This program calculates Fibonacci number.

	mov	r0, 1
	mov	r1, 0x1
	mov	r2, 10		# max
.loop:
	mov	r3, .out
	beq	r3		# branch if under-carry
	add	r0, r1
	swp	r0, r1
	sub	r2, 1
	mov	r3, .loop
	jmp	r3
.out:
	jmp	r3
