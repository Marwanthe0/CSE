
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

.MODEL SMALL
.STACK 100H

.DATA
    N   DW 3        
    RES DW 1        

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    MOV CX, N       
    MOV AX, 1       

FCT_LOOP:
    MUL CX          
    LOOP FCT_LOOP  

    MOV RES, AX     

    MOV AH, 4CH     
    INT 21H
MAIN ENDP
END MAIN

