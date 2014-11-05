# This program calculates Fibonacci number.

	mov	r0, 1
	# 8500_0001

	mov	r15, 0x1
	# 85F00001

	mov	r2, 10		# max
	# 8520000a

.loop:
	mov	r3, .out
	# 8530000c

	cmp	r2, 0
	# 85270000

	beq	r3		# branch if under-carry
	# 40310000

	add	r0, r15
	# 810f2000

#	swp	r0, r1
	mov	r4, r0
	# 81400000

	mov	r0, r15
	# 810f0000

	mov	r15, r4
	# 81f40000

	sub	r2, 1
	# 85230001

	mov	r3, .loop
	# 8530000c

.out:
	jmp	r3
	# 40300000
