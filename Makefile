compilerJ0:
	ocamlopt J0.ml -o ex
	rm -f J0.cmx J0.o J0.cmi J0.o


compilerJ1:
	gcc J1.c -o ex

compilerJ2:
	gcc J2.c -o ex

compilerJ3:
	gcc J3.c -o ex

compilerJ4:
	gcc J4.c -o ex

compilerJ5:
	gcc J5.c -o ex

compilerJ6:
	gcc J6.c -o ex

compilerJ7:
	gcc J7.c -o ex

compilerJ8:
	gcc J8.c -o ex

compilerJ9:
	gcc J9.c -o ex

compilerJ10:
	gcc J10.c -o ex

compilerJ11:
	gcc J11.c -o ex -g -fsanitize=address

compilerJ12:
	gcc J12.c -o ex -g 

compilerJ13:
	gcc J13.c -o ex -g 

compilerJ14:
	gcc J14.c -o ex -g 

# Règle pour nettoyer le programme
nettoyer:
	rm -f ex

# Permet de add commit et push avec un message par default
partager : nettoyer
	sh partager.sh