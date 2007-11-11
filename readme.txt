Boot Sector Love Note for Windows
==================================

This was inspired by http://xkcd.com/340/. It copies a message to your boot 
sector area, and displays it at boot (since its far more useful than "OS not 
found").

In addition, just for fun it automatically places a "Missing operating system"
message at the end. However, if you hit a key then the computer should
boot normally. 

The original MBR is located on the second sector. 

Don'ts:
========

* Don't use this program if you do not know how to uninstall this program 
manually. For that reason, there is no uninstaller. 
* Don't use this on 64-bit machines or ones with EFI -- I really have no idea if it
will work on those machines, but I seriously doubt it would. If you don't know what 
EFI is, don't use this program. 
* Don't use this on machines with GRUB, it will kill your system. 
* Don't use this on any system that is important to you or one that you do 
not own/control, it may kill that system.
* Don't use this program if you cannot pass the following quiz without any 
references. Especially don't use this program if you have no idea how to
decode the answers to the quiz. 

Quiz:
======

1) What is the difference between an MBR and a boot sector? 

2) What does interrupt 0x19 do? 

3) What offset does the partition table start at in an MBR, and how many bytes 
is each entry?

4) What offset is the "signature" of the MBR located at, and what is it?


Quiz Answers (encoded in ROT13)
================================

1) Obbg frpgbef ner qrsvarq cre cnegvgvba, gurer vf bayl bar (hfrq) ZOE.
2) Vg vf gur vagreehcg pnyyrq gb obbg sebz n qvfx. 
3) 0k1OR, fvkgrra olgrf
4) Vg vf ybpngrq ng 0k1sr, naq vf 0k55nn

Compiling the program
======================

I used NASM to compile the MBR code, and Visual Studio 2005 to compile the Windows
installation program. I've never coded with MFC before, and this experience has not
motivated me to do it again anytime in the near future. 

If you have any questions/comments/bug reports for this, feel free to contact me.

Dustin Spicuzza <dustin@virtualroadside.com>