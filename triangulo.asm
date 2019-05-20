	TRIANGULO: 
	
	EQU 1
	tria: 
	
	equ 0

A: MACRO
lab: equ 0
INPUT g
if lab
MULT T
END

L:

 MACRO &a, &b, &d
A
IF lab
INPUT E
MULT &a, &b, &d
END

L2:

 macro &a
l x1, x2, x3
input &a
end

l3: 

macro &y, &u, &a
l4:

 equ 0
subi &u, &a
L2 yes
if tria
div 2
if l4
mult &y, &h
if lab
hhhh
end

SECTION TEXT

		INPUT		B
		INPUT		H
		LOAD		B
df:

		MULT		H
		IF tria


		DIV		DOIS
		;l2 xis
		l3 a, b, d
		;L2 yes
		STORE		R
		if triangulo
		OUTPUT	R
		STOP
		
		
SECTION DATA
	B:	
	
		SPACE
	H:		SPACE
	R:		SPACE
	DOIS:	CONST		2