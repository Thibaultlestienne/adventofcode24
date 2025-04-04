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
	gcc J13.c -o ex

compilerJ14:
	gcc J14.c -o ex

compilerJ15:
	gcc J15.c -o ex
	
compilerJ16:
	gcc J16.c -o ex -g #-fsanitize=address

compilerJ17:
	gcc J17.c -o ex -g -fsanitize=address

compilerJ18:
	gcc J18.c -o ex -g -fsanitize=address

compilerJ19:
	gcc J19.c -o ex -g -fsanitize=address

compilerJ20:
	gcc J20.c -o ex -g 
	
compilerJ21:
	gcc J21.c -o ex -g -fsanitize=address

compilerJ22:
	gcc J22.c -o ex -g -fsanitize=address

compilerJ23:
	gcc J23.c -o ex -g -fsanitize=address

compilerJ24:
	gcc J24.c -o ex -g -fsanitize=address

compilerJ25:
	gcc J25.c -o ex -g -fsanitize=address

# Règle pour nettoyer le programme
nettoyer:
	rm -f ex

# Permet de add commit et push avec un message par default
partager : nettoyer
	sh partager.sh