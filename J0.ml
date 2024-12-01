let rec lire_fichier nom_fichier =
    let rec parcourslignes ic =
        try
            let ligne = input_line ic in
            print_endline ligne;          (* Afficher la ligne *)
            (* String -> list : List.of_seq(String.to_seq ligne)*)
            parcourslignes ic     (* Lire la ligne suivante *)
        with    
        |End_of_file -> ()             (* Fin de fichier *)
    in  
    let ic = open_in nom_fichier in
    parcourslignes ic;
    close_in ic



(*========================== J1 2023 =========================*)

let lignetonombre ligne = 
    let txt = List.of_seq (String.to_seq ligne) in
    let rec recupererpremiernb l = 
        match l with 
            |[] -> 0
            |'0' :: q |'z'::'e'::'r'::'o'::q|'o'::'r'::'e'::'z'::q -> 0
            |'1' :: q |'o'::'n'::'e'::q | 'e' :: 'n' :: 'o' :: q-> 1
            |'2' :: q |'t'::'w'::'o'::q |'o'::'w'::'t'::q -> 2
            |'3' :: q |'t'::'h'::'r'::'e'::'e' ::q |'e'::'e'::'r'::'h'::'t' ::q -> 3
            |'4' :: q |'f'::'o'::'u'::'r'::q |'r'::'u'::'o'::'f'::q -> 4
            |'5' :: q |'f'::'i'::'v'::'e'::q |'e'::'v'::'i'::'f'::q -> 5
            |'6' :: q |'s'::'i'::'x'::q |'x'::'i'::'s'::q -> 6
            |'7' :: q |'s'::'e'::'v'::'e'::'n'::q |'n'::'e'::'v'::'e'::'s'::q -> 7
            |'8' :: q |'e'::'i'::'g'::'h'::'t'::q |'t'::'h'::'g'::'i'::'e'::q -> 8
            |'9' :: q |'n'::'i'::'n'::'e'::q |'e'::'n'::'i'::'n'::q -> 9
            |e :: q-> recupererpremiernb q
    in
    10 * recupererpremiernb(txt) + recupererpremiernb(List.rev txt)

let rec calculer nom_fichier =
    let rec parcourslignes ic =
        try
            let ligne = input_line ic in
            lignetonombre ligne + parcourslignes ic     (* Lire la ligne suivante *)
        with    
        |End_of_file -> 0             (* Fin de fichier *)
    in  
    let ic = open_in nom_fichier in
    let r = parcourslignes ic in 
    close_in ic;
    r


let () = print_int (calculer "entreeJ0.txt")