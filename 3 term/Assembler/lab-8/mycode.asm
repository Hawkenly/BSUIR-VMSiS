.model tiny
.code    
org     100h   

start:  
        jmp load 
        old_int_1Ch dd ?          ;old int  
   
decode  proc                
        ;unpack BCD
        mov ah,0
        ror ax,4                 
        shr ah,4                  
        add ah,30h   ;to ascii
        add al,30h
        
        mov es:[di],al
        mov es:[di+1],0Fh 
        mov es:[di+2],ah
        mov es:[di+3],0Fh 
        add di,4
        ret   
                
decode  endp             

clock   proc  
            
        push es      
        pusha 
        
        push 0B800h
        pop es   
        
        mov     ah,  02h         ;get current time BCD-code        
        int     1Ah              ;ch - hours, cl - minutes, dh - seconds
         
        add di, 80*2*12+40*2
        
        mov al,ch      
        call decode              ;show hours
        
        mov es:[di],":"       
        mov es:[di+1],0Fh  
        add di,2 
               
        mov al,cl
        call decode              ;show minutes
        
        mov es:[di],":"       
        mov es:[di+1],0Fh  
        add di,2   
        
        mov al,dh   
        call decode              ;show seconds
        
        popa
        pop es  
              
        iret    
clock   endp            

load:   
       
        mov ax,3     
        int 10h      
     
        mov ah,35h                        ;get old int (es:bx)
        mov al,1Ch 
        int 21h     
    
        mov word ptr old_int_1Ch,bx       ;shift
        mov word ptr old_int_1Ch+2,es     ;segment
    
        mov ah,25h                        ;set new int
        mov al,1Ch  
        mov dx,offset clock               ;shift
        int 21h            
    
        mov ax,3100h                      ;make rezident
        mov dx,(load - start + 10Fh)/16   ;memory
        int 21h       
    
        end start                   