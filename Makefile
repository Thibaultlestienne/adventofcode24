compilerJ0:
	ocamlopt J0.ml -o ex
	rm -f J0.cmx J0.o J0.cmi J0.o


compilerJ1:
	gcc J1.c -o ex

compilerJ2:
	gcc J2.c -o ex

# Règle pour nettoyer le programme
nettoyer:
	rm -f ex

# Permet de add commit et push avec un message par default
partager : nettoyer
	sh partager.sh