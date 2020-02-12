.CODE

DllEntry PROC hInstDLL: DWORD, reason: DWORD, reserved1: DWORD

	mov rax, 1
	ret
DllEntry ENDP

BordersAsm proc _height: QWORD, _width: QWORD, _bytesInRow: QWORD, _pOldBytesDIB: QWORD, _pNewBytesDIB: QWORD, _pTable: QWORD
; declaring variables
local	one:	DWORD
local	zero:	DWORD
	mov one, 1h
	mov	zero, 0h

; loading first 4 parameters from registers
	mov _height, rcx
	mov _width, rdx
	mov _bytesInRow, r8
	mov _pOldBytesDIB, r9

; setting parameters
	mov r12, _width
	mov r8d, one
	mov r9d, zero

; @1 putting '1' on left border
	mov rcx, 0h			; reset the height counter (j)
	mov r11, _pTable	; move _pTable address to r11 register
	LeftB:	
		mov [r11], r8b		; place '1' in address stored in r11
		mov r11, _pTable	; move the original _pTable address back to r11
		inc rcx				; inc the counter
		mov rax, rcx		; move counter to the accumulator
		mul r12				; multiply the counter by the width
		add r11, rax		; add the content of the accumulator to the address (now r11 = *(table + j * width))
		cmp rcx, _height	; check if loop is done
	jl LeftB

; @2 loops for the rest of pixels
	mov r10, _height	; move the value of _height into r10
	dec r10				; r10 = _height - 1
	mov rcx, 0h			; reset the height counter (j)
	LoopH:	
		mov rbx, 1h			; reset the width counter (i)
		LoopW:	
			; current pixel
			mov rax, _bytesInRow; put number of bytes in a row into the accumulator
			mul rcx				; multiply it by the height counter, it is now the correct line of the pixel
			push rax			; put it on the stack
			mov rax, rbx		; put the width counter into the accumulator
			mov rdx, 3h			; put '3' into the rdx register
			mul rdx				; multiply widtht counter by 3
			mov rdx, rax		; move the content of the accumulator into the rdx register
			pop rax				; get the correct line form the stack
			add rax, rdx		; add the correct line and the width counter
			mov r14, _pOldBytesDIB ; move the pointer of the begining of the pixels' data into r14 register
			add r14, rax		; add the content of the accumulator into the address
			mov r14, [r14]		; move the content of the calculated address into the r14 register
			and r14, 00ffffffh	; leave only the last 6 bytes, r14 now has the color of current pixel
			movq xmm1, r14		; put current pixel's color value in lower part of xmm1 register
			pinsrq xmm1, r14, 1	; put current pixel's color value in higher part of xmm1 register
			; *(table + j * width + i)
			mov r11, _pTable	; put _pTable in r11 regiser
			mov rax, rcx		; move the height counter to the accumulator
			mul r12				; multiply it by the width
			add rax, rbx		; add the width counter
			add r11, rax		; add all of the above to the address (now r11 = *(table + j * width + i))
			cmp rcx, r9			; check if it is a lower border (height = 0)
			je UDBorders
			cmp rcx, r10		; check if it is an upper border (height = _height - 1)
			je UDBorders
			; j - 1 pixel
			mov rax, _bytesInRow; put number of bytes in a row into the accumulator
			dec rcx				; decrement the height counter value, j - 1
			mul rcx				; multiply it by the height counter, it is now the correct line of the pixel
			inc rcx				; increment back the height counter value, j
			push rax			; put it on the stack
			mov rax, rbx		; put the width counter into the accumulator
			mov rdx, 3h			; put '3' into the rdx register
			mul rdx				; multiply it by 3
			mov rdx, rax		; move the content of the accumulator into the rdx register
			pop rax				; get the correct line form the stack
			add rax, rdx		; add the correct line and the width counter
			mov r15, _pOldBytesDIB ; move the pointer of the begining of the pixels' data into r15 register
			add r15, rax		; add the content of the accumulator into the address
			mov r15, [r15]		; move the content of the calculated address into the r15 register
			and r15, 00ffffffh	; leave only the last 6 bytes, r15 now has the color of j - 1 pixel
			movq xmm2, r15		; move color value of j - 1 pixel to the lower part of xmm2 reigster
			; j + 1 pixel
			mov rax, _bytesInRow; put number of bytes in a row into the accumulator
			inc rcx				; increment the height counter value, j + 1
			mul rcx				; multiply it by the height counter, it is now the correct line of the pixel
			dec rcx				; decrement back the height counter value, j
			push rax			; put it on the stack
			mov rax, rbx		; put the width counter into the accumulator
			mov rdx, 3h			; put '3' into the rdx register
			mul rdx				; multiply it by 3
			mov rdx, rax		; move the content of the accumulator into the rdx register
			pop rax				; get the correct line form the stack
			add rax, rdx		; add the correct line and the width counter
			mov r15, _pOldBytesDIB ; move the pointer of the begining of the pixels' data into r15 register
			add r15, rax		; add the content of the accumulator into the address
			mov r15, [r15]		; move the content of the calculated address into the r15 register
			and r15, 00ffffffh	; leave only the last 6 bytes, r15 now has the color of j + 1 pixel
			pinsrq xmm2, r15, 1	; move color value of j + 1 pixel to the higher part of xmm2 register
			pcmpeqq xmm2, xmm1	; compare colors vertically
			pmovmskb rax, xmm2	; create bitmask from result
			sub rax, 0FFFFh		; set flags based on bitmask
			jne different
			UDBorders:
			; i - 1 pixel
			mov rax, _bytesInRow; put number of bytes in a row into the accumulator
			mul rcx				; multiply it by the height counter, it is now the correct line of the pixel
			push rax			; put it on the stack
			dec rbx				; decrement the width counter, i - 1
			mov rax, rbx		; put the width counter into the accumulator
			inc rbx				; increment back the width counter, i
			mov rdx, 3h			; put '3' into the rdx register
			mul rdx				; multiply it by 3
			mov rdx, rax		; move the content of the accumulator into the rdx register
			pop rax				; get the correct line form the stack
			add rax, rdx		; add the correct line and the width counter
			mov r15, _pOldBytesDIB ; move the pointer of the begining of the pixels' data into r15 register
			add r15, rax		; add the content of the accumulator into the address
			mov r15, [r15]		; move the content of the calculated address into the r15 register
			and r15, 00ffffffh	; leave only the last 6 bytes, r15 now has the color of i - 1 pixel
			movq xmm2, r15		; move color value of i - 1 pixel to the lower part of xmm2 reigster
			; i + 1 pixel
			mov rax, _bytesInRow; put number of bytes in a row into the accumulator
			mul rcx				; multiply it by the height counter, it is now the correct line of the pixel
			push rax			; put it on the stack
			inc rbx				; increment the width counter, i + 1
			mov rax, rbx		; put the width counter into the accumulator
			dec rbx				; decrement back the width counter, i
			mov rdx, 3h			; put '3' into the rdx register
			mul rdx				; multiply it by 3
			mov rdx, rax		; move the content of the accumulator into the rdx register
			pop rax				; get the correct line form the stack
			add rax, rdx		; add the correct line and the width counter
			mov r15, _pOldBytesDIB ; move the pointer of the begining of the pixels' data into r15 register
			add r15, rax		; add the content of the accumulator into the address
			mov r15, [r15]		; move the content of the calculated address into the r15 register
			and r15, 00ffffffh	; leave only the last 6 bytes, r15 now has the color of i + 1 pixel
			pinsrq xmm2, r15, 1	; move color value of i + 1 pixel to the higher part of xmm2 register
			pcmpeqq xmm2, xmm1	; compare colors horizontally
			pmovmskb rax, xmm2	; create bitmask from result
			sub rax, 0FFFFh		; set flags based on bitmask
			jne different
			mov [r11], r9b		; place '0'
			jmp done
			different:
			mov [r11], r8b		; place '1'
			done:
			inc rbx				; inc the width counter
			cmp rbx, _width		; check if width loop is done
			jl LoopW
		inc rcx				; inc the height counter
		cmp rcx, _height	; check if height loop is done
		jl LoopH

; @3 loops for coloring the bmp
	mov rcx, 0h			; reset the height counter (j)
	LoopHC:	
		mov rbx, 0h			; reset the width counter (i)
		LoopWC: 
			mov r11, _pTable	; put _pTable in r11 regiser
			mov rax, rcx		; move the height counter to the accumulator
			mul r12				; multiply it by the width
			add rax, rbx		; add the width counter
			add r11, rax		; add all of the above to the address (now r11 = *(table + j * width + i))
			mov r13, [r11]		; move the content from the address to r13
			and r13, 00ffh		; clear the register apart from the last 2 bytes
			cmp r13, r8			; compare if the contet of r13 is '1'
			je black
			mov rax, _bytesInRow; put number of bytes in a row into the accumulator
			mul rcx				; multiply it by the height counter, it is now the correct line of the pixel
			push rax			; put it on the stack
			mov rax, rbx		; put the width counter into the accumulator
			mov rdx, 3h			; put '3' into the rdx register
			mul rdx				; multiply it by 3
			mov rdx, rax		; move the content of the accumulator into the rdx register
			pop rax				; get the correcrt line form the stack
			add rax, rdx		; add the correct line and the width counter
			mov r14, _pNewBytesDIB ; move the pointer of the begining of the pixels' data into r14 register
			add r14, rax		; add the content of the accumulator into the address
			mov r15, 0ffffffh	; move RGB white into r15 register
			mov [r14], r15		; move RGB white into calculated address
			jmp endC
			black:	
			mov rax, _bytesInRow; put number of bytes in a row into the accumulator
			mul rcx				; multiply it by the height counter, it is now the correct line of the pixel
			push rax			; put it on the stack
			mov rax, rbx		; put the width counter into the accumulator
			mov rdx, 3h			; put '3' into the rdx register
			mul rdx				; multiply it by 3
			mov rdx, rax		; move the content of the accumulator into the rdx register
			pop rax				; get the correcrt line form the stack
			add rax, rdx		; add the correct line and the width counter
			mov r14, _pNewBytesDIB ; move the pointer of the begining of the pixels' data into r14 register
			add r14, rax		; add the content of the accumulator into the address
			mov r15, 0h			; move RGB black into r15 register
			mov [r14], r15		; move RGB black into calculated address
			endC:
			inc rbx				; inc the width counter
			cmp rbx, _width		; check if width loop is done
		jl LoopWC
		inc rcx				; inc the height counter
		cmp rcx, _height	; check if height loop is done
	jl LoopHC
	ret
BordersAsm endp

END