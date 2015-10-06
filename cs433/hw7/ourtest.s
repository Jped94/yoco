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

	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
