# Ajouter les modifications
git add .

# Demander à l'utilisateur d'entrer un message de commit
echo "Entrez votre message de commit (appuyez sur Entrée pour utiliser le message par défaut 'RAS'):"
read commit_message

# Utiliser le message par défaut s'il est vide, sinon utiliser le message personnalisé
if [ -z "$commit_message" ]; then
    commit_message="RAS"
fi

# Effectuer le commit avec le message choisi
git commit -m "$commit_message"

# Pousser les modifications vers le dépôt distant
git push
