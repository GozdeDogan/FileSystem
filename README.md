/******************************************************************************/
/* Gozde DOGAN - 131044019
/* CSE312 - Homework3
/*
/* 15 Haziran 2018
/*
/* Kisa odev aciklamasi
/*
/******************************************************************************/

file class'i yazildigi icin makefile'i ona gore duzenledim, o sekilde atiyorum.
Benim gonderdigim makefile'i calistirmak isteiyorsaniz elinizdeki makefile'da;
	DEPS = File.h Thread.h gtuos.h memory.h 8080emuCPP.h memoryBase.h File.cpp Thread.cpp gtuos.cpp 8080emu.cpp
seklinde duzeltme yapabilirsiniz.


ONEMLI:
make yapildiginde memory.h da cstdlib kutuphanesi tanimlanmadigi icin malloc kullanimina hata veriyor.
Bu nedenle memory.h ve MemoryBase.h kutuphaneleri de dosyanin icinde gonderildi.
Eger bu sekilde calistirmak istemiyorsaniz elinizdeki memory.h kutuphanesine
	#include <cstdlib> 
seklinde C'nin standart kutuphanesini eklemelisiniz.
Bu sekilde duzeltme yaptiginizda calisacaktir.

File islemleri icin bir cycle verilmedigi icin hepsinin cycle'ı 1 kabul edildi!

P1.asm, P2.asm, P3.asm, P4.asm yazildi.

P1.asm, P2.asm, P3.asm, P4.asm, P5.asm istenilenlere uymaya calisarak implement etmeye calistim. 
Iclerinde thread system call'llari kullanildigi icin cycle sayilari da ona gore cikacaktir.

ASM dosyalari bir klasor icinde bulunmaktadir. 
!! Ama .com uzantili dosyalar programlarin bulundugu klasor de yer almalidir !!

Odev denenmesi istenilen linux surumunde segment fault yememiştir. 
Butun asm dosyalari calistirilip denendi. Hepsi sonlandi.

