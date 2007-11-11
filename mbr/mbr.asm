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


start:           			;Ok, dont change this stuff either..                
	xor ax,ax
	mov ss,ax
	mov sp,7c00h
	sti
	jmp short load_prog		

ident   db "ONETOLVE"				
					;note: this code won't work if you don't have more
					;than 32k of memory.. lol, such a big problem	
load_prog:
    
	cld
		
	mov ax,0800h
	mov es,ax						; initialize es w/ 0800h
	mov ds,ax						; initialize ds w/ 0800h
	
;
;	Load 6 sectors at 0800:0000
;

load_1:
	mov ax,0206h                    ;function/# of sec to read
	mov cx,0000h                    ;0-5 sec #, 6-7 hi cyl bits
	mov dx,0080h                    ;dh=head dl=drive (bit 7=hdd)
	mov bx,0h                       ;data buffer, points to es:0
	int 13h
	cmp ah,0
	jne load_1                      ;this is allowable because it is
									;relative
									
;
;	Jump to code at 0800:prog_continue
;

	mov ax,0800h
	push ax
	mov ax,prog_continue
	push ax
	retf
	

	
prog_continue:
	
;
;	Display the message located at 0800:0400
;
	
	mov ax,3
	int 10h			; clear screen
	
	; get length of string
	
	mov bp,0400h
	mov si,0ffffh
calc_loop:
	inc si
	cmp byte [bp + si],0	; try to find the null
	jnz calc_loop
	
	mov cx,si				; transfer si to the count register
	
	mov ax,1301h			; write line
	mov bx,07h				; attribute
	mov dx,0				; location
	int 10h	
	
;
;	Wait for key
;

	mov ah,0
	int 16h

;
;	Copy 512 bytes from 0800:0200 to 0000:7c00
;	Jump to 0000:7c00
;

	mov cx,0200h		; 512 bytes
	mov ax,0800h
	mov ds,ax			; src segment
	mov si,0200h		; src location
	xor ax,ax
	mov es,ax			; dest segment
	mov di,7c00h		; dest addr
	rep movsb			; move 512 bytes

;
;	And we're done... jump to the real boot sector
;

	mov ax,7c00h
	push ax
	xor ax,ax
	push ax
	retf


times 1beh-($-$$) db 0
	;ok.. a fake partition table. Who cares.
	db 80h                 ;active
	db 0,0,0
	db 55h                 ;fake
	times 59 db 0            
MBR_signature:
	db 55h,0aah
