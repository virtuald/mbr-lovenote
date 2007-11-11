@echo off

..\nasm\nasm -fbin mbr.asm -o mbr.bin
copy mbr.bin ..\love\love\mbr.bin

pause