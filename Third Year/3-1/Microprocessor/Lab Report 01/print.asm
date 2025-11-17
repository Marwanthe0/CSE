.MODEL SMALL
.STACK 100H

.DATA
    PROMPT_MSG DB 'Please enter a single character: $'
    OUTPUT_MSG DB 0DH, 0AH, 'You entered: $'

.CODE
MAIN PROC
    ; Initialize Data Segment
    MOV AX, @DATA
    MOV DS, AX

    ; Display the prompt message
    MOV AH, 09H         ; Function 09H: Display string
    LEA DX, PROMPT_MSG  ; Load address of message into DX
    INT 21H             ; Call DOS interrupt

    ; Read a single character from keyboard
    MOV AH, 01H         ; Function 01H: Read character with echo
    INT 21H             ; Character is stored in AL

    ; Store the input character
    MOV BL, AL          ; Save the character in BL

    ; Display the output message
    MOV AH, 09H
    LEA DX, OUTPUT_MSG
    INT 21H

    ; Display the character that was input
    MOV AH, 02H         ; Function 02H: Display character
    MOV DL, BL          ; Move the saved character to DL
    INT 21H

    ; Exit to DOS
    MOV AH, 4CH
    INT 21H
MAIN ENDP
END MAIN
