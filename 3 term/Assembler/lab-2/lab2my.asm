.model small
.stack 100h   

.data  
string db 203 DUP ('$') 
Input db "Input string:",0Dh,0Ah,'$'
Output db "Your string:",0Dh,0AH,'$'
StrLen dw ? 
CrLf db 0Dh,0Ah,'$'   
DelimChar db ' ','$'


ptrStartWordCur dw ?
ptrEndWordCur dw ?
lenWordCur dw ?  

ptrStartWord dw ?
ptrEndWord dw ?
lenWord dw ?

ptrStartWordAlf dw ?
ptrEndWordAlf dw ?
lenWordAlf dw ?  

collector dw ?

.code  


    outputStr  macro out_str
        mov dx,offset out_str
        mov ah,09h
        int 21h 
    endm
    
    inputChar proc
        mov ah,01h
        int 21h
        ret
    inputChar endp
    
    inputStr proc 
        push cx
        xor cx,cx
        push ax
        push si   
        lea si,string
        dd:
            call inputChar
            cmp al,13
            je done
            mov [si],al    
            inc cx
            inc si
            jmp dd
     
        done:      
            mov StrLen,cx
            pop si
            pop ax   
            pop cx
         ret
     inputStr endp

    enter proc
        mov dx, offset CrLf
        mov ah,09h
        int 21h
        ret
    endp enter
    
    Compare proc
        push di
        push cx
        push bx
        push ax
        mov si,ptrStartWordAlf 
        mov di,ptrStartWordCur   
        mov ax,lenWordAlf
        mov bx,lenWordCur 
    
        for3:
            cmp [si],al
            je below
            cmp [si],'$'
            je below
            cmp [di],al
            je above  
            cmp [di],'$'
            je above
            mov dl,[si]
            cmp dl,[di]
            ja above
            jb below
            inc si
            inc di
            jmp for3
        above:
        mov lenWordAlf,bx
        mov ptrStartWordAlf,di 
        mov di,ptrEndWordCur
        mov ptrEndWordAlf,di
      
        mov si,ptrEndWordAlf
        jmp quit1
            

        below:
       
        mov si,ptrEndWordCur
 
        quit1:
        pop ax
        pop bx
        pop cx  
        pop di
        
        ret
        endp compare
        
        
    
    
  
  
    print proc
         
        push di
        push si
        push cx
        mov si,ptrStartWordAlf
        mov cx,lenWordAlf
        for4:
            cmp [si],'$'
                je goback  
            mov ah,02h
            mov dl,[si]  
            int 21h
            mov [si],' ' 
            inc si
        loop for4  
        goback:
        
       mov dx, offset DelimChar
       mov ah,09h
       int 21h
       
       pop cx 
       pop si
       pop di
       
       ret
       endp print
    
    
                              
    
    findword proc 
        push si
        push bx
        push cx 
      for1:
            cmp [si],'$'
            je break1
            cmp al,[si]
            jne break1_s
            inc si
            jmp for1   
    break1:
        pop cx
        pop bx
        mov di,si
        pop si
        jmp gg        
    break1_s:
        mov ptrStartWord,si
        pop cx
        pop bx  
        pop si
    gg:
    ret
    endp findword
    
    checkword proc
        push cx
        push bx
        push si
        xor bx,bx  

        for2:
        cmp [si],'$'
        je break2             
        cmp al,[si]
        je break2 
        inc bx
        inc si
        jmp for2
    break2:
    mov ptrEndWord, si
    mov lenWord,bx
    pop si
    pop bx  
    pop cx
    ret
    endp checkword
        
    
    
    Translocation proc 
        push ax
        push bx 
        xor bx,bx
        push di
        push si
        push cx 
        
        mov si,offset string
        mov di,ptrEndWordAlf  
        
        mov cx,lenWordAlf+1
        while1:    
            lea si,string
            mov di,ptrEndWordAlf
            mov bx,[di] 
            while2:
                mov al,string[di-1]
                mov string[di],al 
                dec di           
                cmp di,0000h 
                je off  
            jmp while2
            off: 
            mov [si],bx  
            loop while1
            
        pop cx
        pop si
        pop di
        pop bx
        pop ax    
            
        ret
        endp Translocation      
    
    
    
    start:   
    mov ax,@data
    mov ds,ax
    
    outputStr Input
    call inputStr
    call enter
    outputStr Output 

    call enter
    
    mov cx,StrLen
    mov si,offset string
    mov al,DelimChar 
    xor dx,dx            
    cicle:
        call findword 
        mov si,ptrStartWord 
        mov ptrStartWordAlf, si
        call checkword 
        mov si, ptrEndWord 
        mov ptrEndWordAlf,si
        mov bx,lenWord
        mov lenWordAlf,bx
        
        cycle:  
        cmp [si],'$'
        je quit  
        call findword    
        cmp [di],'$'
        je quit
        mov si,ptrStartWord 
        mov ptrStartWordCur, si 
        
        call checkword 
        mov si, ptrEndWord 
        mov ptrEndWordCur,si
        mov bx,lenWord
        mov lenWordCur,bx
        
        call Compare
        
        jmp cycle 
        
        
        quit: 
   
        call print  

        mov si,offset string   
        ed: 
            cmp [si],'$'
                je exit
            cmp [si],' '
                jne continue
            inc si
        jmp ed
        
        continue:          
        mov si,offset string
        mov al,DelimChar
              
      jmp cicle
    
      exit:
      
      outputStr string
    
     mov ax,4c00h
     int 21h
    
 end start




 
  

                                                                   