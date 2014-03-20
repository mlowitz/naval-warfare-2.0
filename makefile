all : naval_warfare 


compile:
			gcc -w -o naval_warfare battleship.c battleship_header.h

run: 
		./naval_warfare

