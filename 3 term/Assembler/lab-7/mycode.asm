.model tiny  
.code 
org 100h
               
main:       
    fillFilePathLength:     
        mov si,80h
    	xor cx, cx        
    	mov cl, es:[si]   
  	
	checkEmptyCmd:
    	cmp cl, 0
    	jne fillFilePath
    	printMessage emptyCmdErrorMessage
        jmp exit
	          
	fillFilePath:
	    dec cl
    	mov es:filePathLength, cl  
	    mov si,82h 
	    mov di, offset filePath  
	    inc cl
read:
    	lodsb
    	mov [di],al 
    	inc di
    	loop read
    	                   
already_read:    
    mov di,offset filePath      
    
    mov cl, filePathLength
    add di,cx
    mov byte ptr [di],0
    
    call changeMemoryBlock        
    call openFile   
    jnc openFileSuccessfully
        printMessage openFileErrorMessage
        jmp exit    
    openFileSuccessfully:
    
    runProgramsLoop:   
        checkSeparator:      
        mov cl, 1
        mov dx, offset bufferChar 
        call readFile  
        checkEOF:
            cmp bufferChar,00h
            je endMain    
        checkEnter:   
            cmp bufferChar, 13
            je readProgramPath
            mov al, programPathLength
            inc al
            mov programPathLength, al
    jmp runProgramsLoop    
        readProgramPath:      
        call setPointer 
        mov cl, programPathLength
        mov dx, offset programPath 
        call readFile            
        call runProgram   
        jnc runProgramSuccessfully     
        
        runProgramNotSuccessfully:
        printMessage runProgramErrorMessage 
        jmp  endMain                
                  
        runProgramSuccessfully:
        printMessage runProgramSuccessMessage
               
        mov al, programPathLength       
        add byte ptr stringBeginIndex, al 
        add stringBeginIndex, 2
        call setPointer
               
        mov byte ptr programPathLength, 0
    jmp runProgramsLoop                    
      endMain:
        call closeFile
        exit:                  
        ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
printMessage macro string
    mov ah, 9
    lea dx, string 
    int 21h 
endm 

changeMemoryBlock proc
    mov ah, 4Ah                                                          
    mov bx, (programSize/16+1)+(100h/16+1)+(100h/16+1)
	int 21h                 
	jnc changeMemorySuccessfully    
    printMessage changeMemoryErrorMessage 
    jmp exit
    
    changeMemorySuccessfully:
    
    mov ax,cs
    mov word ptr epb+4,ax
    mov word ptr epb+8,ax
    mov word ptr epb+12,ax   
    ret
changeMemoryBlock endp 

openFileFunction macro
    mov ah, 3dh
    mov al, 00h
    mov dx, offset filePath
    int 21h      
endm    

openFile proc
    printMessage openFileMessage   
        openFileFunction 
        mov fileID, ax
    ret
openFile endp

closeFile proc
    printMessage closeFileMessage
      
    mov ah, 3eh
    mov bx, fileID
    int 21h
    jnc closeFileSuccessfully    
    printMessage closeFileErrorMessage 
    jmp exit
    
    closeFileSuccessfully:
    ret
closeFile endp

setPointer proc 
    ;si = offset shift  
    mov ah, 42h  
    mov al, 00h
    mov bx, fileID
    mov cx, 0           ;cx:dx
    mov dx, stringBeginIndex
    int 21h        
    jnc setPointerSuccessfully          
        
    printMessage movePointerErrorMessage
    jmp endMain
    
    setPointerSuccessfully: 
    ret
setPointer endp

readFile proc
    
    mov ah, 3fh
    mov bx, fileID 
    xor ch, ch
    int 21h
    jnc readFileSuccessfully
    
    printMessage readErrorMessage
    jmp endMain
        
    readFileSuccessfully: 
    ret
readFile endp

runProgram proc
    printRunProgramMessage:
        printMessage runProgramMessage
        mov si, offset programPath
        xor ax, ax
        mov al, programPathLength       
        add si, ax
        mov byte ptr [si], '$' 
        printMessage programPath
        printMessage newLine
        mov byte ptr [si], 0  
           
    tryRunProgram:
    	mov ah, 4bh
    	mov al, 0				
    	mov bx, offset epb
    	mov dx, offset programPath
        int 21h  	
        ret
runProgram endp

 filePath            db 126 dup(0)  
 
epb     dw 0
        dw 0080h,0
		dw 005Ch,0,006Ch,0 
                  
filePathLength      db  0  
fileID              dw  0 
fileEnd             db  0   
  
programPathLength   db  0 
programPath         db  35 dup(0)
bufferChar          db  0  
changeMemoryErrorMessage      db  'Change memory error.', 13, 10, '$'  
emptyCmdErrorMessage          db  'Error. Cmd is empty.', 13, 10, '$'
openFileErrorMessage          db  'Open file error.', 13, 10, '$'
closeFileErrorMessage         db  'Close file error.', 13, 10, '$'
movePointerErrorMessage       db  'Move pointer error.', 13, 10, '$'
readErrorMessage              db  'Read error.', 13, 10, '$'
runProgramErrorMessage        db  'Run program error.', 13, 10, '$'                             
openFileMessage               db  'Open file.', 13, 10, '$'
closeFileMessage              db  13, 10, 'Close file.', 13, 10, '$'
runProgramMessage             db  13, 10, 'Run program: ', '$'
runProgramSuccessMessage      db  13, 10, 'Success.', 13, 10, '$'
newLine                       db  13, 10, '$'
stringBeginIndex    dw  2 dup(0)   

programSize = $ - main  

end main