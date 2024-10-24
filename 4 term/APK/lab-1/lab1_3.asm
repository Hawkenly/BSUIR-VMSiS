.model small
.stack 100h

.data

writeError db "Write error!",0Dh,0Ah,'$'
readError db "Read error!",0Dh,0Ah,'$'
buffer1 db 'A','$'
buffer2 db ?
           
.code
           
init proc     
    xor ax,ax
    mov al,0DBh   ;11011011
    mov dx,3FBh   ;3F8h+03h
    out dx,al     ;initialise LCR
                  
    mov al,01h     
    mov dx,3F8h  ;3F8h+00h
    out dx,al    ;DLL
    
    mov al,00h      
    mov dx,3F9h  ;3F8h+01h
    out dx,al    ;DIM  
    
    mov al,5Bh      
    mov dx,3FBh  ;3F8h+03h
    out dx,al    ;DLAB=0    
    
    ret
init endp

checkToWrite proc
    xor al,al
    mov dx,3FDh   ;3F8h+05h
    in al,dx      ;get LSR
    test al,10h   ;check 5th bit (THRE=1)    like AND
    jnz errorWrite
    ret
checkToWrite endp

errorWrite proc
   mov ah,9
   mov dx,offset writeError
   int 21h
   ret 
errorWrite endp

checkToRead proc
    xor al,al
    mov dx,2FDh
    in al,dx        ;get LSR
    test al,01h     ;check 0 bit (DR=1)
    jnz errorRead
    ret
checkToRead endp

errorRead proc
   mov ah,9
   mov dx,offset readError
   int 21h
   ret 
errorRead endp

writeData proc
    mov dx,3F8h        ;3F8h+00h THR
    mov al,buffer1
    out dx,al         
    ret
writeData endp

readData proc
    mov dx,2F8h        ;2F8h+00h RBR
    in al,dx
    mov buffer2,al
    ret
readData endp

exit proc
    mov ax,4C00h
    int 21h
    ret
exit endp

start:
    mov ax,@data
    mov ds,ax    
    
    call init     
    
    call checkToWrite
    call writeData   
    
    call checkToRead
    call readData
    
    mov ah,02h
    mov dl,buffer2
    int 21h   
    
    call exit
   
end start