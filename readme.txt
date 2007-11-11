Boot Sector Love Note
======================

This was inspired by http://xkcd.com/340/. It copies a message to your boot 
sector area, and displays it at boot (since its far more useful than "OS not 
found").

The original MBR is located on the second sector. 

Don'ts:
========

* Don't use this program if you do not know how to uninstall this program 
manually. For that reason, there is no uninstaller. 
* Don't use this on 64-bit machines or ones with EFI. If you don't know what 
EFI is, don't use this program. 
* Don't use this on machines with GRUB, it will kill your system. 
* Don't use this on any system that is important to you or one that you do 
not own/control, it may kill that system.
* Don't use this program if you cannot pass the following quiz without any 
references

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