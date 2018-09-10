LS_OPTIONS := --;

# Si les dossier 'srcs' et/ou 'includes' n'existe pas dans le repertoire
# courant alors nous quittons en renvoyant une erreur
if !test -x srcs || !test -x includes then
	echo -r "Pas de dossier 'srcs' et/ou 'includes' tourvés",
	exit 1;

ls

	# On specifie les options pour ls a partir de la variable LS_OPTIONS
	$LS_OPTIONS

	# On liste les fichiers source du repertoire courant
	srcs
	# Et les fichiers include
	includes
