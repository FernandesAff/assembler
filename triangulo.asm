	TRIANGULO: EQU 1

A: MACRO
lab: equ 0
INPUT g
if lab
MULT T
END

L: MACRO &a, &b, &d
A
IF lab
INPUT E
MULT &a, &b, &d
END

L2: macro &a
if triangulo
l x1, x2, x3
input &a
end

SECTION TEXT

		INPUT		B
		INPUT		H
		LOAD		B
		MULT		H
		IF TRIANGULO
		DIV		DOIS
		;l2 xis
		;Q:
		l2 a;, b, d
		STORE		R
		if lab
		OUTPUT	R
		STOP
		
		
SECTION DATA
	B:		SPACE
	H:		SPACE
	R:		SPACE
	DOIS:	CONST		2