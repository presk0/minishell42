si possible
	- signaux et ctrl d dans le heredoc
	- finir norminette (j'ai fais le plus gros)

supprimer fichiers inutiles
mettre les noms de fichiers dans le Makefile
retirer les flags avec sanitizer

Le rend-on en l'etat ?

bugs :

2mminishell $ env asdf
/usr/bin/env: ‘asdf’: No such file or directory 
// utilise un path alors que la commande est un bultin


42mminishell $ cat << fin
> $PATH
> fin
$PATH				// on tente sans 

2mminishell $ export sdf = p.   // je pense qu on laisse ;)
42mminishell $ env
[ ... ] 
OLDPWD=/home/me2
_=./minishell
sdf

norminette dans libft et printf a refaire ;)
=> ou copier / coller une bibliotheque existante
(a moins qu'ils aient modifies les normes)

