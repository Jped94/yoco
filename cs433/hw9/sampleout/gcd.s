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
yo_gcd:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_gcd, %esp
      //--------------------------  8:     if #b > #a:
	movl	12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jle	else2
      //--------------------------  9:         retweet gcd(#b, #a)!
	pushl	8(%ebp)
	pushl	12(%ebp)
	call	yo_gcd
	addl	$8, %esp
	jmp	funend1
else2:
      //-------------------------- 10:     else if #b like 0:
	cmpl	$0, 12(%ebp)
	jne	else3
      //-------------------------- 11:         retweet #a!
	movl	8(%ebp), %eax
	jmp	funend1
else3:
      //-------------------------- 13:         retweet gcd(#b, #a % #b)!
	movl	8(%ebp), %eax
	cltd	
	idivl	12(%ebp)
	pushl	%edx
	pushl	12(%ebp)
	call	yo_gcd
	addl	$8, %esp
funend1:
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_gcd, 0
//================================
yo_YOCO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_YOCO, %esp
      //-------------------------- 18:     putc('?')!
	pushl	$63
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 19:     int #x @ 60!   // get first number
	movl	$60, -16(%ebp)
      //-------------------------- 20:     put(#x)! putc('\n')!
	pushl	-16(%ebp)
	call	yo_put
	addl	$4, %esp
	pushl	$10
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 21:     putc('?')!
	pushl	$63
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 22:     int #y @ 84!   // get second number
	movl	$84, -20(%ebp)
      //-------------------------- 23:     put(#y)! putc('\n')!
	pushl	-20(%ebp)
	call	yo_put
	addl	$4, %esp
	pushl	$10
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 24:     putc('G')! putc('C')! putc('D')! putc('=')!
	pushl	$71
	call	yo_putc
	addl	$4, %esp
	pushl	$67
	call	yo_putc
	addl	$4, %esp
	pushl	$68
	call	yo_putc
	addl	$4, %esp
	pushl	$61
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 25:     put(gcd(#x, #y))! putc('\n')!
	pushl	-20(%ebp)
	pushl	-16(%ebp)
	call	yo_gcd
	addl	$8, %esp
	pushl	%eax
	call	yo_put
	addl	$4, %esp
	pushl	$10
	call	yo_putc
	addl	$4, %esp
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_YOCO, 8
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
