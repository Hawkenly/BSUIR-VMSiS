.model tiny    
.code   
.org 100h

jmp start  
 
macro Output message
    push ax
    push dx
    xor dx,dx
    xor ax,ax
    lea dx, message
    mov ah, 09h
    int 21h  
    pop dx
    pop ax
endm 
 
openFile proc
    mov ah,3Dh
    mov al,00h
    lea dx,path 
    int 21h   
    ret
endp openFile
               
setPointer proc
    mov ah,42h        
    mov bx,handler
    mov al,00h  
    mov cx,0
    mov dx,start_string  
    int 21h
    ret
endp setPointer               

readFile proc
    mov ah,3Fh
    mov bx,handler 
    mov cx,1
    lea dx,buffer  
    int 21h  
    ret
endp readFile

get_cmd proc
    mov si, 80h      
    
    xor cx, cx     
    mov cl, es:[si] 
    
    cmp cl, 0      
    jz  stop   
    
    mov si,82h
    mov di,offset path
    next_char:        
        mov al, es:[si]     
       
        cmp al,' '
        je Symb
        
        cmp al,0Dh
        je stop     
        
        mov [di],al
        inc si
        inc di
        loop    next_char
   
    Symb:     
    mov [di],0
    xor bx,bx                       
    lea bx,symbols    
    inc si
    next_char1:                  
        mov al,es:[si] 
          
        cmp al, 0Dh
        je stop         
        
        mov [bx],al 
        inc bx    
        inc si
        jmp next_char1         
    stop:  
    ret
endp get_cmd 


 work_with_file  proc
    push ax
    push bx
    push cx
    push dx 
    push di   
    push si
    xor ax,ax
    xor cx,cx
    xor dx,dx
    
    call openFile 
    jnc  openFileSuccessfully
    jmp not_open
    
openFileSuccessfully:      
    mov handler,ax
 
big_cycle:    
    lea di,symbols
    mov cx,start_string
    add cx,counter_bytes
    mov start_string,cx  
    call setPointer
    cycle:              
        call readFile           
        jc exit  
        
        inc counter_bytes
        
        cmp buffer,00h
        je eof 
                
        cmp buffer,0Dh
        je next_string
        
        mov si,offset buffer
        mov al,[di]
        cmp al,[si]
        je next_symbol 
  
        jmp cycle
        
        next_symbol:
            inc di                
            cmp [di],'$'
            je plus       
            inc di            
            mov counter_bytes,0 
            call setPointer                  
            jc exit
            jmp cycle
    next_string:
       add counter_bytes,1
       jmp big_cycle
       plus:
           inc counter_strings 
           to_end:
                call readFile
                inc counter_bytes 
                cmp buffer,0Dh
                je  next_string 
                cmp buffer, 00h
                je eof
                jmp to_end
                   
    exit:
    eof:     
    mov bx,handler
    mov ah,3Eh
    int 21h        
not_open:    
    pop si
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret
work_with_file endp

WriteChar proc  
    push    ax  
    push    dx  
    mov     dl, al  
    mov     ah, 02h  
    int     21h  
    pop     dx  
    pop     ax  
    ret  
WriteChar endp

WriteInteger proc 
    push    ax  
    push    cx  
    push    bx  
    push    dx  
    xor     cx, cx  
    mov     bx, 10  
  

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
        call get_cmd
        cmp cl,0
        jz no_param
        
        call work_with_file  
        jc errorOpenFile
         
        Output msg1
        Output path   
        Output CrLf
        Output msg2
        Output symbols
        Output CrLF
        Output msg3  
        
        mov ax,counter_strings  
        call WriteInteger
        jmp gg                
    
      no_param:
      Output msg    
      jmp gg      
      errorOpenFile:
      Output errorOpenFileMessage
      gg: 
        ret 
     
msg db 'no command line parameters!', 0Dh,0Ah,'$' 
msg1 db "Path to the file:",0Dh,0Ah,'$'
msg2 db "Symbols to check:",0Dh,0Ah,'$' 
msg3 db "Amount of suitable strings:",0Dh,0Ah,'$'
errorOpenFileMessage db "Open file error.",0Dh,0Ah,'$'
CrLf db 0Dh,0Ah,'$'
path db 200 DUP ('$')
symbols db 200 DUP('$')  
buffer db 0
counter_strings dw 0 
counter_bytes dw 0
start_string dw 0          
handler dw ?        
        
end start        
