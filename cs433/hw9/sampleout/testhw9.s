.globl main
main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	movl	$globals, %esi
	call	yo_YOCO
	xorl	%eax, %eax	
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
//================================
yo_f:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_f, %esp
      //--------------------------  9:     int #count @ 0!
	movl	$0, -16(%ebp)
while4:
      //-------------------------- 10:     while #x > 1:
	cmpl	$1, 8(%ebp)
	jle	stmt3
      //-------------------------- 11:         #count @ #count + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
      //-------------------------- 12:         writeRightAligned(#x, 4)!
	pushl	$4
	pushl	8(%ebp)
	call	yo_writeRightAligned
	addl	$8, %esp
      //-------------------------- 13:         spaceOrNewline(#count)!
	pushl	-16(%ebp)
	call	yo_spaceOrNewline
	addl	$4, %esp
      //-------------------------- 14:         if #x % 2 like 0:
	movl	8(%ebp), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	cmpl	$0, %edx
	jne	else8
      //-------------------------- 15:             #x @ #x/2!
	movl	8(%ebp), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	movl	%eax, 8(%ebp)
	jmp	while4
else8:
      //-------------------------- 17:             #x @ 3*#x + 1!
	movl	$3, %eax
	imull	8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, 8(%ebp)
	jmp	while4
stmt3:
      //-------------------------- 20:     writeRightAligned(#x, 4)!
	pushl	$4
	pushl	8(%ebp)
	call	yo_writeRightAligned
	addl	$8, %esp
      //-------------------------- 21:     spaceOrNewline(0)!
	pushl	$0
	call	yo_spaceOrNewline
	addl	$4, %esp
      //-------------------------- 22:     retweet #count!
	movl	-16(%ebp), %eax
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_f, 4
//================================
yo_writeRightAligned:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_writeRightAligned, %esp
      //-------------------------- 26:     int #n2 @ #n!
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
while14:
      //-------------------------- 27:     while #fieldwidth > 1:
	cmpl	$1, 12(%ebp)
	jle	stmt13
      //-------------------------- 28:         if #n2 > 9:
	cmpl	$9, -16(%ebp)
	jle	else16
      //-------------------------- 29:             #n2 @ #n2 / 10!
	movl	-16(%ebp), %eax
	movl	$10, %ecx
	cltd	
	idivl	%ecx
	movl	%eax, -16(%ebp)
	jmp	stmt15
else16:
      //-------------------------- 31:             putc(' ')!
	pushl	$32
	call	yo_putc
	addl	$4, %esp
stmt15:
      //-------------------------- 33:         #fieldwidth @ #fieldwidth - 1!
	movl	12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 12(%ebp)
	jmp	while14
stmt13:
      //-------------------------- 35:     put(#n)!
	pushl	8(%ebp)
	call	yo_put
	addl	$4, %esp
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_writeRightAligned, 4
//================================
yo_spaceOrNewline:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_spaceOrNewline, %esp
      //-------------------------- 39:     if #n % 10 like 0:
	movl	8(%ebp), %eax
	movl	$10, %ecx
	cltd	
	idivl	%ecx
	cmpl	$0, %edx
	jne	else18
      //-------------------------- 40:         putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
	jmp	funend17
else18:
      //-------------------------- 42:         putc(' ')!
	pushl	$32
	call	yo_putc
	addl	$4, %esp
funend17:
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_spaceOrNewline, 0
//================================
yo_YOCO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_YOCO, %esp
      //-------------------------- 49:     #a @ 27!			       	// non-interactive version
	movl	$27, -16(%ebp)
      //-------------------------- 51:     put(f(#a))!
	pushl	-16(%ebp)
	call	yo_f
	addl	$4, %esp
	pushl	%eax
	call	yo_put
	addl	$4, %esp
      //-------------------------- 52:     putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_YOCO, 4
//================================
yo_put:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	8(%ebp)	
	pushl	$intStr
	call	printf	
	leave	
	ret	
//================================
yo_get:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp	
	leal	-4(%ebp), %eax	
	pushl	%eax	
	pushl	$intStr
	call	scanf	
	movl	-4(%ebp), %eax	
	leave	
	ret	
//================================
yo_putc:
	jmp	putchar	
//================================
yo_getc:
	jmp	getchar	

.section	.rodata
intStr: .string "%d"

.section	.data
globals: .space 1
