;
;   Copyright (C)2002-2007 Dustin Spicuzza
;
;   This program is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 3 of the License, or
;   (at your option) any later version.
;
;   This program is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License
;   along with this program.  If not, see <http://www.gnu.org/licenses/>.
;   
;   Derived from my earlier program, Passprot 3
;

CPU 386
BITS 16
org 0h 


start:           					;Ok, dont change this stuff either..                
	
	jmp short load_prog	
	
	ident   db "ONETOLVE"				
	
load_prog:

	cld
	xor ax,ax
	mov ss,ax
	mov sp,7c00h					; setup stack
		
	mov ax,8000h
	mov es,ax						; initialize es w/ 8000h
	mov ds,ax						; initialize ds w/ 8000h
	
	
;
;	Load 6 sectors at es:0000
;

load_1:
	mov ax,0206h                    ;function/# of sec to read
	mov cx,0001h                    ;0-5 sec # (counts from one), 6-7 hi cyl bits
	mov dx,0080h                    ;dh=head dl=drive (bit 7=hdd)
	mov bx,0h                       ;data buffer, points to es:0
	int 13h
	cmp ah,0
	jne load_1                      ;this is allowable because it is
									;relative
	
;
;	Jump to code at es:prog_continue
;
	
	push es
	mov ax,prog_continue
	push ax
	retf
	

	
prog_continue:
	
	mov ax,3
	int 10h							; clear screen
	
;
;	Display the null terminated message located at 0800:0400
;

	
	mov bp,0400h
	mov ah,0eh
	mov si,0ffffh
	
write_char:
	inc si
	cmp byte [ds:bp + si],0			; keep writing until there is a null byte 
	jz wait_for_key

	push bp
	
	mov al, [byte ds:bp + si]
	mov bx, 07h
	int 10h							; teletype the character
	
	pop bp
	
	jmp write_char
	
;
;	Wait for key
;
wait_for_key:
	mov ah,0
	int 16h

;
;	Copy 512 bytes from ds:0200 to 0000:7c00
;	Jump to 0000:7c00h
;

	mov cx,0200h					; 512 bytes
	mov si,0200h					; src location
	xor ax,ax
	mov es,ax						; dest segment
	mov di,7c00h					; dest addr
	rep movsb						; move 512 bytes
	
;
;	And we're done... jump to the real boot sector
;
	mov dx,0080h					;BIOS function
	xor ax,ax
	push ax
	mov ax,7c00h
	push ax
	retf


times 1beh-($-$$) db 0
	;ok.. a fake partition table. Who cares.
	db 80h                			 ;active
	db 0,0,0
	db 55h                			 ;fake
	times 59 db 0            
MBR_signature:
	db 55h,0aah
