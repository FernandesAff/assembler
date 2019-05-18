	TRIANGULO: EQU 1
	
L: MACRO &a &b &d
&a aqui
esta &b
as coisas &d
END
	
SECTION TEXTO
		INPUT		B
		INPUT		H
		LOAD		B
		MULT		H
		IF TRIANGULO
		DIV		DOIS
		STORE		R
		OUTPUT	R
		STOP
SECTION DATA
	B:		SPACE
	H:		SPACE
	R:		SPACE
	DOIS:	CONST		2