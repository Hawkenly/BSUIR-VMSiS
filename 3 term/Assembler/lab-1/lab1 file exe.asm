.model small
.stack 100h    
.data     
;CrLf db 0Dh, 0Ah, '$' 
message1 db   "Hello World!",0Dh,0Ah,'$' 
;message2 db   "Your string:",0Dh,0Ah,'$' 
;bufer db 10      
;string db "$$$$$$$$$$$$"      ;bufer db 10,?,"$$$$$$$$$$" 
.code
start:
    mov ax,@data
    mov ds,ax      
    
    mov dx,offset message1
    mov ah,09h      
    int 21h       ;Output message1
    
   ; mov dx,offset bufer  
   ; mov ah,0Ah
   ; int 21h       ;Input string
    
   ; mov dx,offset CrLf
   ; mov ah,09h
   ; int 21h 
    
   ; mov dx,offset message2
   ; mov ah,09h      
   ; int 21h       ;Output message2
    
   ; mov dx,offset bufer+2
   ; mov ah,09h
   ; int 21h       ;Output string
      
    mov ax,4C00h    ;End program
    int 21h   
              
end start