
int main() {
	__asm {
        
        cmd_path db ?
        msg db 'no command line parameters!', 0Dh, 0Ah, '$'
        .code
        start :
        mov ax, @data
            mov ds, ax
            mov es, ax

            mov bx, 80h
            xor cx, cx
            mov cl, [bx]

            cmp cl, 0
            je no_param

            inc bx
            mov si, bx
            xor ax, ax
            cycle :
        lodsb
            cmp al, 0Dh
            je exit

            mov ah, 0eh
            int 10h


            jmp cycle


            no_param :
        lea dx, msg
            mov ah, 09h
            int 21h
            exit :

        mov ax, 4C00h
            int 21h
            end start

	}



	return 0;
}