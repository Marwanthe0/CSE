
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt


.model small
.stack 100h
.data
a db 'Marwan:$'
b db '20:$'
c db '30:$'
.code 
main proc
    mov ax, @data
    mov ds, ax
    mov ah,9
    lea dx, a
    int 21h    
    mov cx, 20
    mov ah, 2
    mov dl, 'A'
    level:
    int 21h
    inc dl
    loop level
     
    main endp
end main



