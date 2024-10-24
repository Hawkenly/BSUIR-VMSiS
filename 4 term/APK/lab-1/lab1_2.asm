.model small
.stack 100h

.data

writeError db "Write error!",0Dh,0Ah,'$'
readError db "Read error!",0Dh,0Ah,'$'
           
.code

jmp start

init proc
   xor ax,ax
   mov al,10100011b    ;connection params: speed and amount of bits (101 - 2400, 11 -8)
   mov dx,0            ;port num - COM1
   int 14h
   ret            
init endp

checkToWrite proc
   mov al,'A'          ;symbol
   mov ah,1            ;write
   mov dx,0            ;COM1
   int 14h             ;return LSD+symbol in ax
   test al,80h         ;like AND but changes flag ZF
   jnz errorWrite         ;no FIFO
   ret 
checkToWrite endp

errorWrite proc
   mov ah,9
   mov dx,offset writeError
   add dx,2
   int 21h
   ret 
errorWrite endp

checkToRead proc
    mov ah,2
    mov dx,1         ;COM2
    int 14h          ;return LSR+symbol in ax
    test al,80h
    jnz errorRead
    ret
checkToRead endp

errorRead proc
   mov ah,9
   mov dx,offset readError
   add dx,2
   int 21h
   ret 
errorRead endp

Output proc
   mov ah,02h
   mov dl,al
   int 21h
   ret
Output endp

Exit proc
    mov ax,4C00h
    int 21h
    ret
Exit endp

start:  
   call init
   call checkToWrite
   call checkToRead      
   call Output   
   call Exit

end start