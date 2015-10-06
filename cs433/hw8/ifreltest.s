// James Thornton and Josh Pedowitz
.globl yocomain
yocomain:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
//================================
yo_YOCO:
      //--------------------------  5:     yono #g @ yo!
	movl	$1, -16(%ebp)
      //--------------------------  6:     int #x @ 2!
	movl	$2, -20(%ebp)
      //--------------------------  7:     if (#x < 1):
	cmpl	$1, -20(%ebp)
	jge	else5
      //--------------------------  8:         #x @ #x +3!
	movl	-20(%ebp), %eax
	addl	$3, %eax
	movl	%eax, -20(%ebp)
	jmp	stmt4
else5:
      //--------------------------  9:     else if (#x like 2):
	cmpl	$2, -20(%ebp)
	jne	else6
      //-------------------------- 10:         #x @ #x - 13!
	movl	-20(%ebp), %eax
	subl	$13, %eax
	movl	%eax, -20(%ebp)
      //-------------------------- 11:         if (#g like yo):
	cmpl	$1, -16(%ebp)
	jne	stmt8
      //-------------------------- 12:             #x @ #x + 3!
	movl	-20(%ebp), %eax
	addl	$3, %eax
	movl	%eax, -20(%ebp)
	jmp	stmt8
stmt8:
      //-------------------------- 14:         if (yo):
      //-------------------------- 15:             #x @ #x + 1!
	movl	-20(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -20(%ebp)
	jmp	stmt4
      //-------------------------- 10:         #x @ #x - 13!
	jmp	stmt4
else6:
      //-------------------------- 18:         #x @ 10!
	movl	$10, -20(%ebp)
      //-------------------------- 19:         #x @ 2!
	movl	$2, -20(%ebp)
stmt4:
      //-------------------------- 22:     int #y @ 3!
	movl	$3, -24(%ebp)
while12:
      //-------------------------- 24:     while (#y < 20) :
	cmpl	$20, -24(%ebp)
	jge	stmt11
      //-------------------------- 25:         if ((yo and #g or not no) not like (yo and ((#g or #g)))):    
	movl	$0, %eax
	movl	$0, %ecx
	cmpl	$0, -16(%ebp)
	je	label15
//making reg ecx available
	movl	%ecx, %edx
	movl	$1, %ecx
label15:
	movl	$0, %edx
//making reg edx available
	movl	%edx, %ebx
	movl	$1, %edx
	cmpl	$0, -16(%ebp)
	jne	or17
or17:
//making reg eax available
	movl	%eax, %ecx
	movl	$1, %eax
	movl	$0, %ecx
	movl	$0, %edx
	cmpl	$0, -16(%ebp)
	jne	or21
	cmpl	$0, -16(%ebp)
	je	label20
or21:
//making reg edx available
	movl	%edx, %ebx
	movl	$1, %edx
label20:
	cmpl	$0, -16(%ebp)
	jne	or22
	cmpl	$0, -16(%ebp)
	je	label19
or22:
//making reg ecx available
	movl	%ecx, %edx
	movl	$1, %ecx
label19:
	cmpl	%ecx, %eax
	je	stmt13
      //-------------------------- 26:             #x @ #x + 1!
	movl	-20(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -20(%ebp)
	jmp	stmt13
stmt13:
      //-------------------------- 28:         #y @ #y + 1!
	movl	-24(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -24(%ebp)
	jmp	while12
stmt11:
      //-------------------------- 30:     if (yo):
      //-------------------------- 31:         #x @ #x + 9001!
	movl	-20(%ebp), %eax
	addl	$9001, %eax
	movl	%eax, -20(%ebp)
	jmp	funend1
      //-------------------------- 32:     else if (no):
	jmp	funend1
      //-------------------------- 33:         #x @ 14!
	movl	$14, -20(%ebp)
	jmp	funend1
funend1:

	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
