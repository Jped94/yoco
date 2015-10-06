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
yo_random2:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_random2, %esp
      //-------------------------- 30:     #rand @ (123 * #rand + 1341) % 1677!
	movl	$123, %eax
	imull	12(%esi), %eax
	addl	$1341, %eax
	movl	$1677, %ecx
	cltd	
	idivl	%ecx
	movl	%edx, 12(%esi)
      //-------------------------- 31:     retweet #rand % #max!
	movl	12(%esi), %eax
	cltd	
	idivl	8(%ebp)
	movl	%edx, %eax
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_random2, 0
//================================
yo_random:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_random, %esp
      //-------------------------- 36:     int #k1 @ 223!
	movl	$223, -16(%ebp)
      //-------------------------- 37:     #k1 @ 100 * #k1 + 280!
	movl	$100, %eax
	imull	-16(%ebp), %eax
	addl	$280, %eax
	movl	%eax, -16(%ebp)
      //-------------------------- 38:     int #k2 @ 49!
	movl	$49, -20(%ebp)
      //-------------------------- 39:     #k2 @ 100 * #k2 + 297!
	movl	$100, %eax
	imull	-20(%ebp), %eax
	addl	$297, %eax
	movl	%eax, -20(%ebp)
      //-------------------------- 40:     #rand @ 9301 * #rand + #k2!
	movl	$9301, %eax
	imull	12(%esi), %eax
	addl	-20(%ebp), %eax
	movl	%eax, 12(%esi)
      //-------------------------- 41:     #rand @ #rand % #k1!
	movl	12(%esi), %eax
	cltd	
	idivl	-16(%ebp)
	movl	%edx, 12(%esi)
      //-------------------------- 42:     retweet (#n * #rand) / #k1!
	movl	8(%ebp), %eax
	imull	12(%esi), %eax
	cltd	
	idivl	-16(%ebp)
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_random, 8
//================================
yo_getBit:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_getBit, %esp
while12:
      //-------------------------- 46:     while #j > 0:
	cmpl	$0, 12(%ebp)
	jle	stmt11
      //-------------------------- 47:         #a @ #a / 2!
	movl	8(%ebp), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	movl	%eax, 8(%ebp)
      //-------------------------- 48:         #j @ #j - 1!
	movl	12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 12(%ebp)
	jmp	while12
stmt11:
      //-------------------------- 50:     retweet #a % 2 like 1!
	movl	8(%ebp), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	cmpl	$1, %edx
	je	booltrue14
	movl	$0, %eax
	jmp	boolend15
booltrue14:
	movl	$1, %eax
boolend15:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_getBit, 0
//================================
yo_setBit:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_setBit, %esp
      //-------------------------- 54:     int #j @ #k!
	movl	12(%ebp), %eax
	movl	%eax, -16(%ebp)
      //-------------------------- 55:     int #b @ 0!
	movl	$0, -20(%ebp)
while20:
      //-------------------------- 56:     while #j > 0:
	cmpl	$0, -16(%ebp)
	jle	stmt19
      //-------------------------- 57:         #b @ 2 * #b + (#a % 2)!
	movl	$2, %eax
	imull	-20(%ebp), %eax
	movl	8(%ebp), %ecx
//making reg eax available
	movl	%eax, %ebx
	movl	0(%ecx), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	addl	%edx, %ebx
	movl	%ebx, -20(%ebp)
      //-------------------------- 58:         #a @ #a / 2!
	movl	8(%ebp), %eax
	movl	0(%eax), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	movl	8(%ebp), %ecx
	movl	%eax, 0(%ecx)
      //-------------------------- 59:         #j @ #j - 1!
	movl	-16(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while20
stmt19:
      //-------------------------- 61:     if #a % 2 like 1:
	movl	8(%ebp), %eax
	movl	0(%eax), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	cmpl	$1, %edx
	jne	else24
      //-------------------------- 62:         if not #val:
	cmpl	$0, 16(%ebp)
	jne	stmt23
      //-------------------------- 63:             #a @ #a - 1!
	movl	8(%ebp), %eax
	movl	0(%eax), %eax
	subl	$1, %eax
	movl	8(%ebp), %ecx
	movl	%eax, 0(%ecx)
	jmp	stmt23
else24:
      //-------------------------- 66:         if #val:
	cmpl	$0, 16(%ebp)
	je	stmt23
      //-------------------------- 67:             #a @ #a + 1!
	movl	8(%ebp), %eax
	movl	0(%eax), %eax
	addl	$1, %eax
	movl	8(%ebp), %ecx
	movl	%eax, 0(%ecx)
stmt23:
while25:
      //-------------------------- 70:     while #j < #k:
	movl	-16(%ebp), %eax
	cmpl	12(%ebp), %eax
	jge	funend16
      //-------------------------- 71:         #a @ 2 * #a + (#b % 2)!
	movl	8(%ebp), %eax
	movl	$2, %ecx
	imull	0(%eax), %ecx
	movl	-20(%ebp), %eax
	movl	$2, %ebx
	cltd	
	idivl	%ebx
	addl	%edx, %ecx
	movl	8(%ebp), %eax
	movl	%ecx, 0(%eax)
      //-------------------------- 72:         #b @ #b / 2!
	movl	-20(%ebp), %eax
	movl	$2, %ecx
	cltd	
	idivl	%ecx
	movl	%eax, -20(%ebp)
      //-------------------------- 73:         #j @ #j + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while25
funend16:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_setBit, 8
//================================
yo_i:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_i, %esp
      //-------------------------- 78:     retweet #c + #r * #cols!
	movl	8(%ebp), %eax
	imull	8(%esi), %eax
	movl	12(%ebp), %ecx
	addl	%eax, %ecx
	movl	%ecx, %eax
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_i, 0
//================================
yo_inBounds:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_inBounds, %esp
      //-------------------------- 82:     retweet #r >= 0 and #r < #rows and #c >= 0 and #c < #cols!
	cmpl	$0, 8(%ebp)
	jl	and32
	movl	8(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	and32
	cmpl	$0, 12(%ebp)
	jl	and32
	movl	12(%ebp), %eax
	cmpl	8(%esi), %eax
	jl	booltrue30
and32:
	movl	$0, %eax
	jmp	boolend31
booltrue30:
	movl	$1, %eax
boolend31:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_inBounds, 0
//================================
yo_visited:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_visited, %esp
      //-------------------------- 86:     retweet (not inBounds(#r, #c))      // out of bounds always visited (not free)
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_inBounds
	addl	$8, %esp
	cmpl	$0, %eax
	je	booltrue34
      //-------------------------- 87:         or getBit(#m[i(#r, #c)], 4)!
	pushl	$4
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_i
	addl	$8, %esp
	pushl	64(%esi, %eax, 4)
	call	yo_getBit
	addl	$8, %esp
	cmpl	$0, %eax
	jne	booltrue34
      //-------------------------- 86:     retweet (not inBounds(#r, #c))      // out of bounds always visited (not free)
	movl	$0, %eax
	jmp	boolend35
booltrue34:
	movl	$1, %eax
boolend35:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_visited, 0
//================================
yo_setVisited:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_setVisited, %esp
      //-------------------------- 91:     if inBounds(#r, #c):
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_inBounds
	addl	$8, %esp
	cmpl	$0, %eax
	je	funend36
      //-------------------------- 92:         setBit(#m[i(#r, #c)], 4, #val)!
	pushl	16(%ebp)
	pushl	$4
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_i
	addl	$8, %esp
	leal	64(%esi, %eax, 4), %eax
	pushl	%eax
	call	yo_setBit
	addl	$12, %esp
funend36:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_setVisited, 0
//================================
yo_visit:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_visit, %esp
      //-------------------------- 97:     setVisited(#r, #c, yo)!
	pushl	$1
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_setVisited
	addl	$12, %esp
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_visit, 0
//================================
yo_isWall:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_isWall, %esp
      //-------------------------- 101:     retweet inBounds(#r, #c)           // no walls out of bounds
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_inBounds
	addl	$8, %esp
	cmpl	$0, %eax
	je	and41
      //-------------------------- 102:         and getBit(#m[i(#r, #c)], #dir)!
	pushl	16(%ebp)
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_i
	addl	$8, %esp
	pushl	64(%esi, %eax, 4)
	call	yo_getBit
	addl	$8, %esp
	cmpl	$0, %eax
	jne	booltrue39
and41:
      //-------------------------- 101:     retweet inBounds(#r, #c)           // no walls out of bounds
	movl	$0, %eax
	jmp	boolend40
booltrue39:
	movl	$1, %eax
boolend40:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_isWall, 0
//================================
yo_setWall:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_setWall, %esp
      //-------------------------- 106:     int #r1 @ #r + #dr[#dir]!
	movl	16(%ebp), %eax
	movl	8(%ebp), %ecx
	addl	48(%esi, %eax, 4), %ecx
	movl	%ecx, -16(%ebp)
      //-------------------------- 107:     int #c1 @ #c + #dc[#dir]!
	movl	16(%ebp), %eax
	movl	12(%ebp), %ecx
	addl	32(%esi, %eax, 4), %ecx
	movl	%ecx, -20(%ebp)
      //-------------------------- 108:     int #dir1 @ (#dir + 2) % 4!
	movl	16(%ebp), %eax
	addl	$2, %eax
	movl	$4, %ecx
	cltd	
	idivl	%ecx
	movl	%edx, -24(%ebp)
      //-------------------------- 109:     if inBounds(#r, #c):
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_inBounds
	addl	$8, %esp
	cmpl	$0, %eax
	je	stmt46
      //-------------------------- 110:         setBit(#m[i(#r, #c)], #dir, #val)!
	pushl	20(%ebp)
	pushl	16(%ebp)
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_i
	addl	$8, %esp
	leal	64(%esi, %eax, 4), %eax
	pushl	%eax
	call	yo_setBit
	addl	$12, %esp
stmt46:
      //-------------------------- 112:     if inBounds(#r1, #c1):
	pushl	-20(%ebp)
	pushl	-16(%ebp)
	call	yo_inBounds
	addl	$8, %esp
	cmpl	$0, %eax
	je	funend42
      //-------------------------- 113:         setBit(#m[i(#r1, #c1)], #dir1, #val)!
	pushl	20(%ebp)
	pushl	-24(%ebp)
	pushl	-20(%ebp)
	pushl	-16(%ebp)
	call	yo_i
	addl	$8, %esp
	leal	64(%esi, %eax, 4), %eax
	pushl	%eax
	call	yo_setBit
	addl	$12, %esp
funend42:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_setWall, 12
//================================
yo_initSquare:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_initSquare, %esp
      //-------------------------- 118:     setVisited(#r, #c, no)!
	pushl	$0
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_setVisited
	addl	$12, %esp
      //-------------------------- 119:     int #dir @ 0!
	movl	$0, -16(%ebp)
while50:
      //-------------------------- 120:     while #dir < 4:
	cmpl	$4, -16(%ebp)
	jge	funend47
      //-------------------------- 121:         setWall(#r, #c, #dir, yo)!
	pushl	$1
	pushl	-16(%ebp)
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	yo_setWall
	addl	$16, %esp
      //-------------------------- 122:         #dir @ #dir + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while50
funend47:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_initSquare, 4
//================================
yo_loopOver:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_loopOver, %esp
      //-------------------------- 127:     #n @ #n + 1!
	movl	8(%ebp), %eax
	movl	0(%eax), %eax
	addl	$1, %eax
	movl	8(%ebp), %ecx
	movl	%eax, 0(%ecx)
      //-------------------------- 128:     retweet #n <= #rows * #cols!
	movl	8(%ebp), %eax
	movl	4(%esi), %ecx
	imull	8(%esi), %ecx
	cmpl	%ecx, 0(%eax)
	jle	booltrue54
	movl	$0, %eax
	jmp	boolend55
booltrue54:
	movl	$1, %eax
boolend55:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_loopOver, 0
//================================
yo_nr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_nr, %esp
      //-------------------------- 132:     retweet (#n-1) / #cols!
	movl	8(%ebp), %eax
	subl	$1, %eax
	cltd	
	idivl	8(%esi)
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_nr, 0
//================================
yo_nc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_nc, %esp
      //-------------------------- 136:     retweet (#n-1) % #cols!
	movl	8(%ebp), %eax
	subl	$1, %eax
	cltd	
	idivl	8(%esi)
	movl	%edx, %eax
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_nc, 0
//================================
yo_initDirs:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_initDirs, %esp
      //-------------------------- 140:     #top @ 0!
	movl	$0, 16(%esi)
      //-------------------------- 141:     #left @ 1!
	movl	$1, 20(%esi)
      //-------------------------- 142:     #bottom @ 2!
	movl	$2, 24(%esi)
      //-------------------------- 143:     #right @ 3!
	movl	$3, 28(%esi)
      //-------------------------- 144:     #dr[#top] @ -1!
	movl	16(%esi), %eax
	movl	$-1, 48(%esi, %eax, 4)
      //-------------------------- 145:     #dr[#left] @ 0!
	movl	20(%esi), %eax
	movl	$0, 48(%esi, %eax, 4)
      //-------------------------- 146:     #dr[#bottom] @ 1!
	movl	24(%esi), %eax
	movl	$1, 48(%esi, %eax, 4)
      //-------------------------- 147:     #dr[#right] @ 0!
	movl	28(%esi), %eax
	movl	$0, 48(%esi, %eax, 4)
      //-------------------------- 148:     #dc[#top] @ 0!
	movl	16(%esi), %eax
	movl	$0, 32(%esi, %eax, 4)
      //-------------------------- 149:     #dc[#left] @ -1!
	movl	20(%esi), %eax
	movl	$-1, 32(%esi, %eax, 4)
      //-------------------------- 150:     #dc[#bottom] @ 0!
	movl	24(%esi), %eax
	movl	$0, 32(%esi, %eax, 4)
      //-------------------------- 151:     #dc[#right] @ 1!
	movl	28(%esi), %eax
	movl	$1, 32(%esi, %eax, 4)
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_initDirs, 0
//================================
yo_initMaze:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_initMaze, %esp
      //-------------------------- 155:     int #n @ 0!
	movl	$0, -16(%ebp)
while72:
      //-------------------------- 156:     while loopOver(#n):
	leal	-16(%ebp), %eax
	pushl	%eax
	call	yo_loopOver
	addl	$4, %esp
	cmpl	$0, %eax
	je	funend70
      //-------------------------- 157:         initSquare(nr(#n), nc(#n))!
	pushl	-16(%ebp)
	call	yo_nc
	addl	$4, %esp
	pushl	%eax
	pushl	-16(%ebp)
	call	yo_nr
	addl	$4, %esp
	pushl	%eax
	call	yo_initSquare
	addl	$8, %esp
	jmp	while72
funend70:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_initMaze, 4
//================================
yo_follow:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_follow, %esp
      //-------------------------- 163:     visit(#r, #c)!
	movl	12(%ebp), %eax
	pushl	0(%eax)
	movl	8(%ebp), %eax
	pushl	0(%eax)
	call	yo_visit
	addl	$8, %esp
      //-------------------------- 164:     int #d1 @ random(4)!
	pushl	$4
	call	yo_random
	addl	$4, %esp
	movl	%eax, -16(%ebp)
      //-------------------------- 165:     int #d2 @ 0!
	movl	$0, -20(%ebp)
while77:
      //-------------------------- 166:     while #d2 < 4:
	cmpl	$4, -20(%ebp)
	jge	funend73
      //-------------------------- 167:         int #dir @ (#d1 + #d2) % 4!
	movl	-16(%ebp), %eax
	addl	-20(%ebp), %eax
	movl	$4, %ecx
	cltd	
	idivl	%ecx
	movl	%edx, -24(%ebp)
      //-------------------------- 168:         int #r1 @ #r + #dr[#dir]!
	movl	8(%ebp), %eax
	movl	-24(%ebp), %ecx
	movl	0(%eax), %eax
	addl	48(%esi, %ecx, 4), %eax
	movl	%eax, -28(%ebp)
      //-------------------------- 169:         int #c1 @ #c + #dc[#dir]!
	movl	12(%ebp), %eax
	movl	-24(%ebp), %ecx
	movl	0(%eax), %eax
	addl	32(%esi, %ecx, 4), %eax
	movl	%eax, -32(%ebp)
      //-------------------------- 170:         if not visited(#r1, #c1):
	pushl	-32(%ebp)
	pushl	-28(%ebp)
	call	yo_visited
	addl	$8, %esp
	cmpl	$0, %eax
	jne	stmt81
      //-------------------------- 171:             setWall(#r, #c, #dir, no)!
	pushl	$0
	pushl	-24(%ebp)
	movl	12(%ebp), %eax
	pushl	0(%eax)
	movl	8(%ebp), %eax
	pushl	0(%eax)
	call	yo_setWall
	addl	$16, %esp
      //-------------------------- 172:             follow(#r1, #c1)!
	leal	-32(%ebp), %eax
	pushl	%eax
	leal	-28(%ebp), %eax
	pushl	%eax
	call	yo_follow
	addl	$8, %esp
stmt81:
      //-------------------------- 174:         #d2 @ #d2 + 1!
	movl	-20(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -20(%ebp)
	jmp	while77
funend73:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_follow, 20
//================================
yo_makeMaze:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_makeMaze, %esp
      //-------------------------- 179:     int #r @ random(#rows)!
	pushl	4(%esi)
	call	yo_random
	addl	$4, %esp
	movl	%eax, -16(%ebp)
      //-------------------------- 180:     int #c @ random(#cols)!
	pushl	8(%esi)
	call	yo_random
	addl	$4, %esp
	movl	%eax, -20(%ebp)
      //-------------------------- 181:     follow(#r, #c)!
	leal	-20(%ebp), %eax
	pushl	%eax
	leal	-16(%ebp), %eax
	pushl	%eax
	call	yo_follow
	addl	$8, %esp
      //-------------------------- 182:     #r @ random(#rows)!
	pushl	4(%esi)
	call	yo_random
	addl	$4, %esp
	movl	%eax, -16(%ebp)
      //-------------------------- 183:     setWall(#r, 0, #left, no)!
	pushl	$0
	pushl	20(%esi)
	pushl	$0
	pushl	-16(%ebp)
	call	yo_setWall
	addl	$16, %esp
      //-------------------------- 184:     #r @ random(#rows)!
	pushl	4(%esi)
	call	yo_random
	addl	$4, %esp
	movl	%eax, -16(%ebp)
      //-------------------------- 185:     setWall(#r, #cols-1, #right, no)!
	pushl	$0
	pushl	28(%esi)
	movl	8(%esi), %eax
	subl	$1, %eax
	pushl	%eax
	pushl	-16(%ebp)
	call	yo_setWall
	addl	$16, %esp
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_makeMaze, 8
//================================
yo_printFirstRow:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_printFirstRow, %esp
      //-------------------------- 189:     int #c @ 0!
	movl	$0, -16(%ebp)
      //-------------------------- 190:     putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 191:     putc(' ')!
	pushl	$32
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 192:     putc(' ')!
	pushl	$32
	call	yo_putc
	addl	$4, %esp
while95:
      //-------------------------- 193:     while #c < #cols:
	movl	-16(%ebp), %eax
	cmpl	8(%esi), %eax
	jge	funend90
      //-------------------------- 194:         putc('_')! putc('_')! putc(' ')!
	pushl	$95
	call	yo_putc
	addl	$4, %esp
	pushl	$95
	call	yo_putc
	addl	$4, %esp
	pushl	$32
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 195:         #c @ #c+1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while95
funend90:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_printFirstRow, 4
//================================
yo_printRow:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_printRow, %esp
      //-------------------------- 200:     int #c @ 0!
	movl	$0, -16(%ebp)
      //-------------------------- 201:     putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 202:     putc(' ')!
	pushl	$32
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 203:     if isWall(#r, #c, #left):
	pushl	20(%esi)
	pushl	-16(%ebp)
	pushl	8(%ebp)
	call	yo_isWall
	addl	$12, %esp
	cmpl	$0, %eax
	je	else104
      //-------------------------- 204:         putc('|')!
	pushl	$124
	call	yo_putc
	addl	$4, %esp
	jmp	stmt103
else104:
      //-------------------------- 206:         putc(' ')!
	pushl	$32
	call	yo_putc
	addl	$4, %esp
stmt103:
while105:
      //-------------------------- 209:     while #c < #cols:
	movl	-16(%ebp), %eax
	cmpl	8(%esi), %eax
	jge	funend99
      //-------------------------- 210:         if isWall(#r, #c, #bottom):
	pushl	24(%esi)
	pushl	-16(%ebp)
	pushl	8(%ebp)
	call	yo_isWall
	addl	$12, %esp
	cmpl	$0, %eax
	je	else107
      //-------------------------- 211:             putc('_')! putc('_')!
	pushl	$95
	call	yo_putc
	addl	$4, %esp
	pushl	$95
	call	yo_putc
	addl	$4, %esp
	jmp	stmt106
else107:
      //-------------------------- 213:             putc(' ')! putc(' ')!
	pushl	$32
	call	yo_putc
	addl	$4, %esp
	pushl	$32
	call	yo_putc
	addl	$4, %esp
stmt106:
      //-------------------------- 215:         if isWall(#r, #c, #right):
	pushl	28(%esi)
	pushl	-16(%ebp)
	pushl	8(%ebp)
	call	yo_isWall
	addl	$12, %esp
	cmpl	$0, %eax
	je	else111
      //-------------------------- 216:             putc('|')!
	pushl	$124
	call	yo_putc
	addl	$4, %esp
	jmp	stmt110
else111:
      //-------------------------- 218:             putc(' ')!
	pushl	$32
	call	yo_putc
	addl	$4, %esp
stmt110:
      //-------------------------- 220:         #c @ #c+1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while105
funend99:
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_printRow, 4
//================================
yo_printMaze:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_printMaze, %esp
      //-------------------------- 225:     printFirstRow()!
	call	yo_printFirstRow
	addl	$0, %esp
      //-------------------------- 226:     int #r @ 0!
	movl	$0, -16(%ebp)
while116:
      //-------------------------- 227:     while #r < #rows:
	movl	-16(%ebp), %eax
	cmpl	4(%esi), %eax
	jge	stmt115
      //-------------------------- 228:         printRow(#r)!
	pushl	-16(%ebp)
	call	yo_printRow
	addl	$4, %esp
      //-------------------------- 229:         #r @ #r + 1!
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	while116
stmt115:
      //-------------------------- 231:     putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 232:     putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_printMaze, 4
//================================
yo_initRand:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_initRand, %esp
      //-------------------------- 236:     putc('\n')! putc('r')! putc('a')! putc('n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
	pushl	$114
	call	yo_putc
	addl	$4, %esp
	pushl	$97
	call	yo_putc
	addl	$4, %esp
	pushl	$110
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 237:     putc('d')! putc('o')! putc('m')! putc(' ')!
	pushl	$100
	call	yo_putc
	addl	$4, %esp
	pushl	$111
	call	yo_putc
	addl	$4, %esp
	pushl	$109
	call	yo_putc
	addl	$4, %esp
	pushl	$32
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 238:     putc('=')! putc(' ')! putc('?')!
	pushl	$61
	call	yo_putc
	addl	$4, %esp
	pushl	$32
	call	yo_putc
	addl	$4, %esp
	pushl	$63
	call	yo_putc
	addl	$4, %esp
      //-------------------------- 240:     #rand @ 13!
	movl	$13, 12(%esi)
      //-------------------------- 241:     putc('\n')!
	pushl	$10
	call	yo_putc
	addl	$4, %esp
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_initRand, 0
//================================
yo_YOCO:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$frsize_YOCO, %esp
      //-------------------------- 245:     initRand()!
	call	yo_initRand
	addl	$0, %esp
      //-------------------------- 246:     #rows @ 30!
	movl	$30, 4(%esi)
      //-------------------------- 247:     #cols @ 25!
	movl	$25, 8(%esi)
      //-------------------------- 248:     initDirs()!
	call	yo_initDirs
	addl	$0, %esp
      //-------------------------- 249:     initMaze()!
	call	yo_initMaze
	addl	$0, %esp
      //-------------------------- 250:     makeMaze()!
	call	yo_makeMaze
	addl	$0, %esp
      //-------------------------- 251:     printMaze()!
	call	yo_printMaze
	addl	$0, %esp
	leal	-12(%ebp), %esp	
	popl	%esi
	popl	%edi
	popl	%ebx
	leave	
	ret	
	.set	frsize_YOCO, 0
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
globals: .space 25668
