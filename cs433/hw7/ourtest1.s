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
	movl	$2, -4020(%ebp)
      //--------------------------  8:     yono #j @ no!
	movl	$0, -4024(%ebp)
      //--------------------------  9:     int #g, #h @ 8!
	movl	$8, -4032(%ebp)
      //-------------------------- 10:     #g @ #h / #x + #x * -#g % 8!
	movl	-4032(%ebp), %eax
	cltd	
	idivl	-4020(%ebp)
	movl	-4028(%ebp), %ecx
	negl	%ecx
	movl	-4020(%ebp), %edx
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
	movl	%ebx, -4028(%ebp)
      //-------------------------- 11:     #y[2*#h + #g] @ #j!
	movl	$2, %eax
	imull	-4032(%ebp), %eax
	addl	-4028(%ebp), %eax
	movl	-4024(%ebp), %ecx
	movl	%ecx, -4016(%ebp, %eax, 4)
      //-------------------------- 12:     #y[2] @ #j!
	movl	-4024(%ebp), %eax
	movl	%eax, -4008(%ebp)
      //-------------------------- 13:     #y[3] @ yo!
	movl	$1, -4004(%ebp)
      //-------------------------- 14:     #h @ 2 + 5 / 6 + #g!
	movl	$2, %eax
	addl	-4028(%ebp), %eax
	movl	%eax, -4032(%ebp)

	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
