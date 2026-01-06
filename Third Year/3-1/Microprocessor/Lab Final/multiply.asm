
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt


.MODEL SMALL
.STACK 100H

.DATA
    NUM1 DW 2
    NUM2 DW 4
    RESULT DW ?

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    MOV AX, NUM1     
    MOV BX, NUM2     

    MUL BX           

    MOV RESULT, AX 

    MOV AH, 4CH
    INT 21H
MAIN ENDP
END MAIN


