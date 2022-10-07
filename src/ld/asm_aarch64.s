	.arch armv8-a
	.file	"a1.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	x19, [sp, 16]
	.cfi_offset 19, -16
	adrp	x0, ss.0
	add	x0, x0, :lo12:ss.0
	ldr	x19, [x0]
	adrp	x0, ss.0
	add	x0, x0, :lo12:ss.0
	ldr	x0, [x0]
	bl	strlen1
	mov	x2, x0
	mov	x1, x19
	mov	w0, 1
	bl	write
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.align	2
	.global	strlen1
	.type	strlen1, %function
strlen1:
.LFB7:
	.cfi_startproc
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, 8]
	str	xzr, [sp, 24]
	b	.L4
.L5:
	ldr	x0, [sp, 24]
	add	x0, x0, 1
	str	x0, [sp, 24]
.L4:
	ldr	x0, [sp, 8]
	add	x1, x0, 1
	str	x1, [sp, 8]
	ldrb	w0, [x0]
	cmp	w0, 0
	bne	.L5
	ldr	x0, [sp, 24]
	add	sp, sp, 32
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE7:
	.size	strlen1, .-strlen1
	.section	.rodata
	.align	3
.LC0:
	.string	"Hi, ASM\n"
	.section	.data.rel.local,"aw"
	.align	3
	.type	ss.0, %object
	.size	ss.0, 8
ss.0:
	.xword	.LC0
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
