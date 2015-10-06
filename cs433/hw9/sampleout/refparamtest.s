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
yo_incto10:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_incto10, %esp
      //--------------------------  4:     #n @ #n + 1!
	movl	8(%ebp), %eax
	movl	0(%eax), %eax
	addl	$1, %eax
	movl	8(%ebp), %ecx
	movl	%eax, 0(%ecx)
      //--------------------------  5:     retweet #n <= 10!
	movl	8(%ebp), %eax
	cmpl	$10, 0(%eax)
	jle	booltrue3
	movl	$0, %eax
	jmp	boolend4
booltrue3:
	movl	$1, %eax
boolend4:
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_incto10, 0
//================================
yo_YOCO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_YOCO, %esp
      //--------------------------  9:     int #a @ 0!
	movl	$0, -16(%ebp)
while7:
      //-------------------------- 10:     while (incto10(#a)):
	leal	-16(%ebp), %eax
	pushl	%eax
	call	yo_incto10
	addl	$4, %esp
	cmpl	$0, %eax
	je	funend5
      //-------------------------- 11:         put(#a)!
	pushl	-16(%ebp)
	call	yo_put
	addl	$4, %esp
      //-------------------------- 12:         putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
	jmp	while7
funend5:
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
