;No partner. 
;This program read a char from the keyboard and output it to the screen. It compute postfix
;expressions.
;My program read the input via READ_ChAR subroutine, and then evalute the input via EVALUATE
;function, it will determine which subroutines from PLUS, MIN, MUL, DIV, EXP to be used to 
;calculate the expression. 
;R0, input and contain value to be print to the screen
;R1, temporary variable
;R2, temporary variable
;R3, temporary variable
;R4, temporary variable
;R5, contain the final result, and used as flag
;R6, temporary variable
;R7, used when I use JSR
;All these registers have different meaning in different subroutines. 


.ORIG x3000
	
;your code goes here

SAVE_R0 .BLKW #0
;read from the keyboard
READ_ChAR

	AND R0, R0, #0 
	GETC	;R0 contain input from keyboard
	OUT		;output to the screen
	ST R0, SAVE_R0	;save R0
	ST R7, SAVE_R7
	JSR EVALUATE
	LD R7, SAVE_R7		;save R7 before use JSR
	BR READ_ChAR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here
	AND R5, R5, #0
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR NEG_IN
	LD R7, SAVE_R7
	LD R2, EQUAL		;compare with =
	ADD R2, R2, R6
	BRnp #3
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR CHECK_ANSWER	;if input is =, check stack 
	LD R7, SAVE_R7
	LD R2, SPACE		;compare with space
	ADD R2, R2, R6
	BRnp #3
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR READ_ChAR		;if input is space, ignore it and get the next input
	LD R7, SAVE_R7
	LD R2, PLUS_INPUT	;compare with +
	ADD R2, R2, R6
	BRnp #3
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR PLUS			;if input is + , go to the PLUS subroutine
	LD R7, SAVE_R7
	LD R2, MIN_INPUT	;compare with -
	ADD R2, R2, R6
	BRnp #3
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR MIN				;if input is - , go to the MIN subroutine
	LD R7, SAVE_R7
	LD R2, MUL_INPUT	;compare with *
	ADD R2, R2, R6
	BRnp #3
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR MUL				;if input is * , go to the MUL subroutine
	LD R7, SAVE_R7
	LD R2, DIV_INPUT	;compare with /
	ADD R2, R2, R6
	BRnp #3
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR DIV				;if input is / , go to the DIV subroutine
	LD R7, SAVE_R7
	LD R2, EXP_INPUT	;compare with ^
	ADD R2, R2, R6
	BRnp #3
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR EXP				;if input is ^ , go to the EXP subroutine
	LD R7, SAVE_R7
	ADD R5, R5, #0
	BRp READ_ChAR		;END LOOP
;begin check numbers
	LD R2, VALUE_ZERO	;compare ascill value with ascill character 0
	ADD R2, R2, R6
	BRnz #3
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR PRINT_STRING	;if ascii value is smaller than 0, then it is not a number
	LD R7, SAVE_R7
	LD R2, VALUE_NINE	;compare ascill value with ascill character 9
	ADD R2, R2, R6
	BRzp #3
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR PRINT_STRING	;if ascii value is bigger than 9, then it is not a number
	LD R7, SAVE_R7
	LD R0, SAVE_R0
	LD R2, VALUE_ZERO
	NOT R2, R2
	ADD R2, R2, #1		;get ascii value negative 0
	ADD R0, R0, R2		;get the decimal number
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR PUSH			;push input decimal number into stack
	LD R7, SAVE_R7
	RET


SPACE   .FILL x0020
SAVE_R7 .BLKW #1
EQUAL .FILL x003D
PLUS_INPUT .FILL x002B
MIN_INPUT .FILL x002D
MUL_INPUT .FILL x002A
DIV_INPUT .FILL x002F
EXP_INPUT .FILL x005E
VALUE_NINE .FILL x0039

; IN R0
; OUT R6 = -R0
NEG_IN
	NOT R6, R0
	ADD R6, R6, #1
	RET


CHECK_ANSWER
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R4
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3			;
	ADD R3, R3, #1		;
	ADD R4, R4, #1
	LDR R5, R4, #0
	ADD R3, R3, R4		;compare stack_start with (stack_top+1)
	BRnp #3
	ST R7, SAVE_R7
	JSR PRINT_HEX		;if so, indicate there is only one number remain in the stack
	LD R7, SAVE_R7
	ST R7, SAVE_R7
	JSR PRINT_STRING	;or the input expression is invalid
	LD R7, SAVE_R7
	RET 


PRINT_STRING
	LEA R3, STRING		;let R3 point to the address of the string

	PRINT_STRING_LOOP		;loop to print the string
		LDR R0, R3, #0
		BRnp #1
		JSR FINISH
		OUT
		ADD R3, R3, #1
		BR PRINT_STRING_LOOP
		RET


STRING	.STRINGZ "Invalid Expression"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	ST R5, SAVE_R5		;The final result is in R5, so first store it
	LD R3, SAVE_R5		;the PRINT_HEX subroutine print the value stored in R3

	AND R0, R0, #0		;clear register
	AND R1, R1, #0		;clear register
	AND R2, R2, #0		;clear register
	AND R4, R4, #0		;clear register
	AND R5, R5, #0		;clear register


	CHECK_DIGIT			;this subroutine check if the digit printed reach 4
		ADD R5, R1, #-4
		BRz FINISH		;if already print 4 digit, then halt the program
		AND R4, R4, #0	;clear register
		AND R2, R2, #0	;clear register
		
	CHECK_BIT			;this subroutine check if the bit count reach 4
		ADD R5, R2, #-4
		BRz PRINT		;when reach 4 bit, print it. 
		ADD R4, R4, R4
		ADD R3, R3, #0
		BRzp ZERO		;if the bit is 0, go to the ZERO subroutine
		ADD R4, R4, #1	;or the bit is 1, and add 1 to the register
		ADD R3, R3, R3	;left move all bits
		ADD R2, R2, #1
		BR CHECK_BIT

	ZERO
		ADD R4, R4, #0	;the current bit is 0, so add 0 to the register
		ADD R3, R3, R3	;then left move all bits
		ADD R2, R2, #1
		BR CHECK_BIT

	PRINT   			;this subroutine print 4 bits into a hexadecimal number
		ADD R5, R4, #-9
		BRp ALPHABET		;the ascii character is alphabet
		LD R5, VALUE_ZERO	;the ascii character is number, so add 0's ascii value
		ADD R4, R4, R5
		AND R0, R0, #0
		ADD R0, R4, #0
		OUT				;print the 4 bits into a hexadecimal character to the screen
		ADD R1, R1, #1
		BR CHECK_DIGIT


	ALPHABET
		LD R5, VALUE_A	;add the A's ascii value
		ADD R4, R4, R5
		ADD R4, R4, #-10 ;and then minus 10 to get the correct ascii value
		AND R0, R0, #0
		ADD R0, R4, #0
		OUT				;rint the 4 bits into a hexadecimal character to the screen
		ADD R1, R1, #1
		BR CHECK_DIGIT	;then start to print the next four bits


	FINISH  
		LD R5, SAVE_R5	;load the final result into R5
		HALT			;halt the program

	SAVE_R5 .BLKW #1

	VALUE_ZERO .FILL x0030
	VALUE_A .FILL x0041



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R3, R0, #0		;load the pop number into R3
	ADD R5, R5, #0
	BRnz #1	
	JSR PRINT_STRING	;check if underflow, if so, go to print invalid expression
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R4, R0, #0		;load the pop number into R4
	ADD R5, R5, #0
	BRnz #1	
	JSR PRINT_STRING	;check if underflow, if so, go to print invalid expression	ADD R0, R3, R4		;add the two number into R0
	ADD R0, R3, R4
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR PUSH			;push the answer in the stack
	LD R7, SAVE_R7
	AND R5, R5, #0
	ADD R5, R5, #1
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R3, R0, #0		;load the pop number into R3
	ADD R5, R5, #0
	BRp PRINT_STRING	;check if underflow, if so, go to print invalid expression
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R4, R0, #0		;load the pop number into R4
	ADD R5, R5, #0
	BRp PRINT_STRING	;check if underflow, if so, go to print invalid expression
	NOT R3, R3
	ADD R3, R3, #1
	ADD R0, R4, R3		;minus the two number into R0
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR PUSH			;push the answer in the stack
	LD R7, SAVE_R7
	AND R5, R5, #0
	ADD R5, R5, #1
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R3, R0, #0		;load the pop number into R3
	ADD R5, R5, #0
	BRp PRINT_STRING	;check if underflow, if so, go to print invalid expression
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R4, R0, #0		;load the pop number into R4
	ADD R5, R5, #0
	BRp PRINT_STRING	;check if underflow, if so, go to print invalid expression
	ADD R6, R3, #0
	AND R0, R0, #0
MUL_LOOP				;loop to add R4 R3 times.
	ADD R0, R4, R0
	ADD R6, R6, #-1
	BRp MUL_LOOP
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR PUSH			;push the answer in the stack
	LD R7, SAVE_R7
	AND R5, R5, #0
	ADD R5, R5, #1
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R3, R0, #0		;load the pop number into R3
	ADD R5, R5, #0
	BRp PRINT_STRING	;check if underflow, if so, go to print invalid expression
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R4, R0, #0		;load the pop number into R4
	ADD R5, R5, #0
	BRp PRINT_STRING	;check if underflow, if so, go to print invalid expression
	NOT R3, R3
	ADD R3, R3, #1
	AND R1, R1, #0
	AND R0, R0, #0
DIV_LOOP				;loop to minus R4 R3 times, and ignore the remainder
	ADD R0, R0, #1
	ADD R4, R4, R3
	BRp DIV_LOOP
	BRz GET_ZERO
	ADD R0, R0, #-1
GET_ZERO				;if the remainder is zero, we don't need to minus R0 by 1
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR PUSH			;push the answer in the stack
	LD R7, SAVE_R7
	AND R5, R5, #0
	ADD R5, R5, #1
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R3, R0, #0		;load the pop number into R3
	ADD R5, R5, #0
	BRp PRINT_STRING	;check if underflow, if so, go to print invalid expression
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR POP
	LD R7, SAVE_R7
	ADD R4, R0, #0		;load the pop number into R4
	ADD R5, R5, #0
	BRp PRINT_STRING	;check if underflow, if so, go to print invalid expression
	ADD R1, R3, #0
	ST R4, SAVE_R4
	ADD R6, R4, #0
	AND R2, R2, #0
EXP_LOOP1				;this loop count R3 times, means multiple R4 by itself R3 times
	AND R0, R0, #0
	ADD R3, R3, #-1
	BRz END_EXP
EXP_LOOP2				;this loop count R4 times, means add R4 by itself R4 times. 
	ADD R0, R6, R0
	ADD R4, R4, #-1
	BRp EXP_LOOP2
	LD R4, SAVE_R4
	ADD R6, R0, #0
	BR EXP_LOOP1
END_EXP					;when finish the loops, load final result into R0
	ADD R0, R6, #0
	ST R7, SAVE_R7		;save R7 before use JSR
	JSR PUSH			;push the answer in the stack
	LD R7, SAVE_R7
	AND R5, R5, #0
	ADD R5, R5, #1
	RET
SAVE_R4 .BLKW #1



;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
