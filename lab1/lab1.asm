;R1, digit counter
;R2, bit counter
;R4, digit to be printed
;R5, temporary

.ORIG x3000
; write your code here

AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
AND R4, R4, #0
AND R5, R5, #0


CHECK_DIGIT
    ADD R5, R1, #-4
    BRz FINISH
    AND R4, R4, #0
    AND R2, R2, #0
    
CHECK_BIT
    ADD R5, R2, #-4
    BRz PRINT
    ADD R4, R4, R4
    ADD R3, R3, #0
    BRzp ZERO
    ADD R4, R4, #1
    ADD R3, R3, R3
    ADD R2, R2, #1
    BR CHECK_BIT

ZERO
    ADD R4, R4, #0
    ADD R3, R3, R3
    ADD R2, R2, #1
    BR CHECK_BIT

PRINT   
    ADD R5, R4, #-9
    BRp ALPHABET
    LD R5, VALUE_ZERO
    ADD R4, R4, R5
    AND R0, R0, #0
    ADD R0, R4, #0
    OUT
    ADD R1, R1, #1
    BR CHECK_DIGIT


ALPHABET
    LD R5, VALUE_A
    ADD R4, R4, R5
    ADD R4, R4, #-10
    AND R0, R0, #0
    ADD R0, R4, #0
    OUT
    ADD R1, R1, #1
    BR CHECK_DIGIT


FINISH  
    HALT



VALUE_ZERO .FILL x0030
VALUE_A .FILL x0041




.END