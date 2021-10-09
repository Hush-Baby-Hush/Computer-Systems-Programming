;number to print in decimal is in R3.
;it will be positive.
.ORIG x3000



LOOP
	AND R4, R4, #0
	ADD R4, R4, #-10
	ST R7, SAVE_R7
	JSR DIV
	LD R7, SAVE_R7
	ST R7, SAVE_R7
	JSR PUSH
	LD R7, SAVE_R7
	ADD R5, R5, #0
	BRp DONE
	ADD R3, R1, #0
	BRp LOOP
	BR PRINT

PRINT
	ST R7, SAVE_R7
	JSR POP
	LD R7, SAVE_R7
	ADD R5, R5, #0
	BRp DONE
	LD R1, ASCII_0
	ADD R0, R0, R1
	OUT
	BR PRINT
	
ASCII_0 .FILL x30
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R1-quotient, R0-remainder
DIV	
	AND R1, R1, #0
	AND R0, R0, #0
DIVLOOP
	ADD R1, R1, #1
	ADD R3, R3, R4
	BRp DIVLOOP
	ADD R1, R1, #-1
	ADD R0, R3, #10
	RET

SAVE_R7 .BLKW #1

DONE
	HALT

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

