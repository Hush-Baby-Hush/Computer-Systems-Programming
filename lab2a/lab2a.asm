.ORIG x3000
; Write code to read in characters and echo them
; till a newline character is entered.
READ_ChAR

        AND R0, R0, #0 
        GETC
        OUT
        ST R7, SAVE_R7
        JSR NEG_IN
        LD R7, SAVE_R7
        LD R2, SPACE
        ADD R2, R2, R6
        BRz READ_ChAR
        LD R2, CHAR_RETURN
        ADD R2, R2, R6
        BRz CHECK_BALANCE
        LD R2, NEW_LINE
        ADD R2, R2, R6
        BRz CHECK_BALANCE
        BR IS_BALANCED   
 
SPACE   .FILL x0020
NEW_LINE        .FILL x000A
CHAR_RETURN     .FILL x000D
SAVE_R7 .BLKW #1

CHECK_BALANCE
        LD R3, STACK_START      ;
        LD R4, STACk_TOP   
        ST R0, SAVE_R0   ;
        ADD R0, R3, #0
        JSR NEG_IN
        LD R0, SAVE_R0
        ADD R3, R6, R4   
        BRz BALANCED
        BR UN_BALANCE

SAVE_R0 .BLKW #1


BALANCED
        AND R5, R5, #0
        ADD R5, R5, #1
        HALT
UN_BALANCE
        AND R5, R5, #0
        ADD R5, R5, #-1
        HALT      

; IN R0
; OUT R6 = -R0
NEG_IN
        NOT R6, R0
        ADD R6, R6, #1
        RET
SAVE_R2 .BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else 1.
IS_BALANCED
        AND R2,R2,#0
        ADD R2,R2,R0
        ST R2, BALANCED_SaveRO
        LD R4, NEG_CLOSE
        ADD R2, R2, R4
        BRz POP
        LD R2, BALANCED_SaveRO
        LD R4, NEG_OPEN
        ADD R2, R2, R4
        BRz PUSH
        BR READ_ChAR


NEG_OPEN .FILL xFFD8
NEG_CLOSE .FILL xFFD7
BALANCED_SaveRO .BLKW #1
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
        ST R3, PUSH_SaveR3      ;save R3
        ST R4, PUSH_SaveR4      ;save R4
        AND R5, R5, #0          ;
        LD R3, STACK_END        ;
        LD R4, STACk_TOP        ;
        ADD R3, R3, #-1         ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz OVERFLOW            ;stack is full
        STR R0, R4, #0          ;no overflow, store value in the stack
        ADD R4, R4, #-1         ;move top of the stack
        ST R4, STACK_TOP        ;store top of stack pointer
        BRnzp DONE_PUSH         ;
OVERFLOW
        LD R3, PUSH_SaveR3      ;
        LD R4, PUSH_SaveR4  
        BR UN_BALANCE
DONE_PUSH
        LD R3, PUSH_SaveR3      ;
        LD R4, PUSH_SaveR4      ;
        BR READ_ChAR


PUSH_SaveR3     .BLKW #1        ;
PUSH_SaveR4     .BLKW #1        ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4 
        BR UN_BALANCE          ;

DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        BR READ_ChAR


POP_SaveR3      .BLKW #1        ;
POP_SaveR4      .BLKW #1        ;
STACK_END       .FILL x3FF0     ;
STACK_START     .FILL x4000     ;
STACK_TOP       .FILL x4000     ;

.END


