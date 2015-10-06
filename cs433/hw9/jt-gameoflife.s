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
yo_updateBoard:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_updateBoard, %esp
      //-------------------------- 36: 	#i @ 0! 
	movl	$0, -124(%ebp)
while11:
      //-------------------------- 37: 	while #i < #BOARDSIZE:
	movl	-124(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	stmt10
      //-------------------------- 38: 		#nextGen[#i] @ #board[#i]!
	movl	-124(%ebp), %eax
	movl	-124(%ebp), %ecx
	movl	12(%esi, %eax, 4), %eax
	movl	%eax, -120(%ebp, %ecx, 4)
      //-------------------------- 39: 		#i @ #i + 1!
	movl	-124(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -124(%ebp)
	jmp	while11
stmt10:
      //-------------------------- 42: 	#i @ 0! 
	movl	$0, -124(%ebp)
while15:
      //-------------------------- 43: 	while #i < #BOARDSIZE:
	movl	-124(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	stmt14
      //-------------------------- 45: 		#neighborCount @ 0!
	movl	$0, -16(%ebp)
      //-------------------------- 46: 		#j @ -1! 
	movl	$-1, -128(%ebp)
while19:
      //-------------------------- 47: 		while #j<=1:
	cmpl	$1, -128(%ebp)
	jg	stmt18
      //-------------------------- 49: 			#rowAbove @ #i - #ROWSIZE + #j!
	movl	-124(%ebp), %eax
	subl	0(%esi), %eax
	addl	-128(%ebp), %eax
	movl	%eax, -132(%ebp)
      //-------------------------- 50: 			if 0 <= #rowAbove and #rowAbove < #BOARDSIZE and #board[#rowAbove] like yo: 
	movl	$0, %eax
	cmpl	-132(%ebp), %eax
	jg	stmt21
	movl	-132(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	stmt21
	movl	-132(%ebp), %eax
	cmpl	$1, 12(%esi, %eax, 4)
	jne	stmt21
      //-------------------------- 51: 				#neighborCount @ #neighborCount + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
stmt21:
      //-------------------------- 54: 			#thisRow @ #i + #j!
	movl	-124(%ebp), %eax
	addl	-128(%ebp), %eax
	movl	%eax, -136(%ebp)
      //-------------------------- 55: 			if #j not like 0 and 0 < #thisRow and #thisRow < #BOARDSIZE and #board[#thisRow] like yo: 
	cmpl	$0, -128(%ebp)
	je	stmt23
	movl	$0, %eax
	cmpl	-136(%ebp), %eax
	jge	stmt23
	movl	-136(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	stmt23
	movl	-136(%ebp), %eax
	cmpl	$1, 12(%esi, %eax, 4)
	jne	stmt23
      //-------------------------- 56: 				#neighborCount @ #neighborCount + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
stmt23:
      //-------------------------- 59: 			#rowBelow @ #i + #ROWSIZE + #j!
	movl	-124(%ebp), %eax
	addl	0(%esi), %eax
	addl	-128(%ebp), %eax
	movl	%eax, -140(%ebp)
      //-------------------------- 60: 			if 0 < #rowBelow and #rowBelow < #BOARDSIZE and #board[#rowBelow] like yo: 
	movl	$0, %eax
	cmpl	-140(%ebp), %eax
	jge	stmt25
	movl	-140(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	stmt25
	movl	-140(%ebp), %eax
	cmpl	$1, 12(%esi, %eax, 4)
	jne	stmt25
      //-------------------------- 61: 				#neighborCount @ #neighborCount + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
stmt25:
      //-------------------------- 64: 			#j @ #j + 1!
	movl	-128(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -128(%ebp)
	jmp	while19
stmt18:
      //-------------------------- 67: 		if #board[#i] like yo:
	movl	-124(%ebp), %eax
	cmpl	$1, 12(%esi, %eax, 4)
	jne	else27
      //-------------------------- 69: 			if #neighborCount < 2:
	cmpl	$2, -16(%ebp)
	jge	else28
      //-------------------------- 70: 				#nextGen[#i] @ no!
	movl	-124(%ebp), %eax
	movl	$0, -120(%ebp, %eax, 4)
	jmp	stmt26
else28:
      //-------------------------- 71: 			else if #neighborCount > 3:
	cmpl	$3, -16(%ebp)
	jle	stmt26
      //-------------------------- 73: 				#nextGen[#i] @ no!
	movl	-124(%ebp), %eax
	movl	$0, -120(%ebp, %eax, 4)
	jmp	stmt26
else27:
      //-------------------------- 75: 		else if(#neighborCount like 3):
	cmpl	$3, -16(%ebp)
	jne	stmt26
      //-------------------------- 78: 			#nextGen[#i] @ yo!
	movl	-124(%ebp), %eax
	movl	$1, -120(%ebp, %eax, 4)
stmt26:
      //-------------------------- 80: 		#i @ #i + 1!
	movl	-124(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -124(%ebp)
	jmp	while15
stmt14:
      //-------------------------- 83: 	#i @ 0! 
	movl	$0, -124(%ebp)
while30:
      //-------------------------- 84: 	while #i < #BOARDSIZE:
	movl	-124(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	funend1
      //-------------------------- 85: 		#board[#i] @ #nextGen[#i]!
	movl	-124(%ebp), %eax
	movl	-124(%ebp), %ecx
	movl	-120(%ebp, %eax, 4), %eax
	movl	%eax, 12(%esi, %ecx, 4)
      //-------------------------- 86: 		#i @ #i + 1!
	movl	-124(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -124(%ebp)
	jmp	while30
funend1:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_updateBoard, 128
//================================
yo_printGeneration:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_printGeneration, %esp
      //-------------------------- 92: 	int #i @ 0! 
	movl	$0, -16(%ebp)
while34:
      //-------------------------- 93: 	while #i < #BOARDSIZE:
	movl	-16(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	funend32
      //-------------------------- 94: 		if #i % #ROWSIZE like 0: 
	movl	-16(%ebp), %eax
	cltd	
	idivl	0(%esi)
	cmpl	$0, %edx
	jne	stmt35
      //-------------------------- 95: 			putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
stmt35:
      //-------------------------- 97: 		if #board[#i] like yo:
	movl	-16(%ebp), %eax
	cmpl	$1, 12(%esi, %eax, 4)
	jne	else37
      //-------------------------- 98: 			putc('X')!
	pushl	$88
	call	yo_putc
	addl	$4, %esp
	jmp	stmt36
else37:
      //-------------------------- 100: 			putc('_')!
	pushl	$95
	call	yo_putc
	addl	$4, %esp
stmt36:
      //-------------------------- 102: 		#i @ #i + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while34
funend32:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_printGeneration, 4
//================================
yo_initBoard:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_initBoard, %esp
      //-------------------------- 110: 	int #i @ 0!
	movl	$0, -16(%ebp)
while41:
      //-------------------------- 111: 	while #i < #BOARDSIZE:
	movl	-16(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	stmt40
      //-------------------------- 112: 		#board[#i] @ no!
	movl	-16(%ebp), %eax
	movl	$0, 12(%esi, %eax, 4)
      //-------------------------- 113: 	 	#i @ #i + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while41
stmt40:
      //-------------------------- 118: 	int #base @ 1!
	movl	$1, -20(%ebp)
      //-------------------------- 119: 	#board[#base] @ yo!
	movl	-20(%ebp), %eax
	movl	$1, 12(%esi, %eax, 4)
      //-------------------------- 120: 	#board[#base+#ROWSIZE + 1] @ yo!
	movl	-20(%ebp), %eax
	addl	0(%esi), %eax
	addl	$1, %eax
	movl	$1, 12(%esi, %eax, 4)
      //-------------------------- 121: 	#board[#base+2*#ROWSIZE -1] @ yo!
	movl	$2, %eax
	imull	0(%esi), %eax
	movl	-20(%ebp), %ecx
	addl	%eax, %ecx
	subl	$1, %ecx
	movl	$1, 12(%esi, %ecx, 4)
      //-------------------------- 122: 	#board[#base+2*#ROWSIZE] @ yo!
	movl	$2, %eax
	imull	0(%esi), %eax
	movl	-20(%ebp), %ecx
	addl	%eax, %ecx
	movl	$1, 12(%esi, %ecx, 4)
      //-------------------------- 123: 	#board[#base+2*#ROWSIZE + 1] @ yo!
	movl	$2, %eax
	imull	0(%esi), %eax
	movl	-20(%ebp), %ecx
	addl	%eax, %ecx
	addl	$1, %ecx
	movl	$1, 12(%esi, %ecx, 4)
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_initBoard, 8
//================================
yo_YOCO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_YOCO, %esp
      //-------------------------- 127: 	#ROWSIZE @ 5!
	movl	$5, 0(%esi)
      //-------------------------- 128: 	#BOARDSIZE @ #ROWSIZE * #ROWSIZE!
	movl	0(%esi), %eax
	imull	0(%esi), %eax
	movl	%eax, 4(%esi)
      //-------------------------- 129: 	#NUMGEN @ 8!
	movl	$8, 8(%esi)
      //-------------------------- 130: 	initBoard()!
	call	yo_initBoard
	addl	$0, %esp
      //-------------------------- 132: 	printGeneration()!
	call	yo_printGeneration
	addl	$0, %esp
      //-------------------------- 134: 	int #i @ 0! 
	movl	$0, -16(%ebp)
while55:
      //-------------------------- 135: 	while #i < #NUMGEN:
	movl	-16(%ebp), %eax
	cmpl	8(%esi), %eax
	jge	funend48
      //-------------------------- 136: 		putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 137: 		updateBoard()!
	call	yo_updateBoard
	addl	$0, %esp
      //-------------------------- 138: 		printGeneration()!
	call	yo_printGeneration
	addl	$0, %esp
      //-------------------------- 139: 		#i @ #i + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while55
funend48:
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
globals: .space 116
