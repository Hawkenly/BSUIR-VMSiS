.model small
.stack 100h

.data 
      mes0 db "Input chislo:",0Dh,0Ah,'$'
      mes1 db "Input a massive:",0Dh,0Ah,'$'
      mes2 db "Your massive:",0Dh,0Ah,'$'
      mes3 db "Average value(Integer part): ",'$' 
      mes4 db "Average value(Fractional part): ",'$'  
      CrLf db 0Dh,0Ah,'$'
      mas dw Len DUP (?) 
      averageInt dw 67
      averageFract dw 67
      fl dw ?     
      Len EQU 30
      
.code     

Output macro mes    
    push ax
    mov dx,offset mes
    mov ah,09h
    int 21h  
    pop ax
endm

ReadChar proc  
    mov     ah,01h
    int     21h
    ret  
ReadChar endp

ReadInteger proc  
    push    cx     
    push    bx
    push    dx
    mov     fl,0    
    xor     cx, cx  
    mov     bx, 10
    call    ReadChar  
 
    cmp     al,'-'  
    je      nnn
    jmp     nn
nnn:
    mov     fl,1
  
read:
  
    call    ReadChar   
nn: cmp     al, 13     
    je      done       
    
    sub     al, '0'    
    xor     ah, ah  
    xor     dx, dx  
    xchg    cx, ax  
    mul     bx  
    add     ax, cx  
    xchg    ax, cx  
    jmp     read  
done:  
    xchg    ax, cx  
    cmp     fl,1
    je      eee
    jmp     ee
eee:
    neg     ax
ee:              
    Output CrLf
    pop     dx
    pop     bx  
    pop     cx
    ret  
ReadInteger endp  

WriteChar proc  
    push    ax  
    push    dx  
    mov     dl, al  
    mov     ah, 2  
    int     21h  
    pop     dx  
    pop     ax  
    ret  
WriteChar endp  

WriteInteger proc near
    push    ax  
    push    cx  
    push    bx  
    push    dx  
    xor     cx, cx  
    mov     bx, 10  
  
    cmp     ax,0
    jl      ddd 
    jmp     divl    

ddd:
    push    ax
    mov     dl, '-'  
    mov     ah, 2  
    int     21h
    pop     ax
    neg     ax  
 

divl:  
    xor     dx, dx  
    idiv    bx  
    push    dx  
    inc     cx  
    cmp     ax,0    
    jg     divl  
 

popl:  
    pop     ax  
    add     al, '0'
  
    call    WriteChar  
    loop    popl  
 
    pop     dx
    pop     bx  
    pop     cx  
    pop     ax
    ret  
WriteInteger endp 



start:   

    mov ax,@data
    mov ds,ax
    
    Output mes1
    mov di,0
    mov cx,Len
    input: 
        call ReadInteger
        mov mas[di],ax  
        add di,2
    loop input
    
    xor ax,ax
    xor di,di  
    mov cx,Len
    count:
        add ax,mas[di]
        add di,2
    loop count                
    
    mov bx,Len 
    cmp ax,0
    jl d  
    jmp dd
    d: 
       mov fl,1
       neg ax
    
    dd: 
    xor dx,dx   
    div bx
   
    cmp fl,1
    je z
    jmp zz 
    z: 
       neg ax
    zz:
    mov averageInt,ax 
    mov averageFract,dx
    
    mov ax,averageInt
    Output mes3
    call WriteInteger  
    Output CrLf
    mov ax, averageFract  
    Output mes4
    call WriteInteger
    Output CrLf
 
    mov ax,4C00h
    int 21h
    
end start
    