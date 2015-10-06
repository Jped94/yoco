.globl yocomain
yocomain:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
//================================
yo_YOCO:
      //--------------------------  7:     #x @ 2!
	movl	$2, 0(%esi)
      //--------------------------  8:     int #g, #h @ 3!
	movl	$3, -20(%ebp)
      //--------------------------  9:     #g @ #h / #x + #x * -#g % 8!
	movl	-20(%ebp), %eax
	cltd	
	idivl	0(%esi)
	movl	-16(%ebp), %ecx
	negl	%ecx
	movl	0(%esi), %edx
	imull	%ecx, %edx
//making reg edx available
	movl	%edx, %ecx
//making reg eax available
	movl	%eax, %ebx
	movl	%ecx, %eax
	movl	$8, %ecx
	cltd	
	idivl	%ecx
	addl	%edx, %ebx
	movl	%ebx, -16(%ebp)
      //-------------------------- 10:     yono #j @ #y[2*#h + #g]!
	movl	$2, %eax
	imull	-20(%ebp), %eax
	addl	-16(%ebp), %eax
	movl	20(%esi, %eax, 4), %eax
	movl	%eax, -24(%ebp)
      //-------------------------- 11:     #y[2] @ #j!
	movl	-24(%ebp), %eax
	movl	%eax, 28(%esi)
      //-------------------------- 12:     #y[3] @ yo!
	movl	$1, 32(%esi)
      //-------------------------- 13:     #h @ 2 + 5 / 6 % 2!
	movl	$2, -20(%ebp)

	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
