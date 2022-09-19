si possible
	- signaux et ctrl d dans le heredoc
	- finir norminette

supprimer fichiers inutiles
mettre les noms de fichiers dans le Makefile
/!\ makefile hardcode avec swalter, verifier que le programme fonctionne sur tt les macs
retirer les flags avec sanitizer

Le rend-on en l'etat ?

bugs :

2mminishell $ env asdf
/usr/bin/env: ‘asdf’: No such file or directory

42mminishell $ cat << fin
> $PATH
> fin
$PATH

2mminishell $ export sdf = p
42mminishell $ env
[ ... ] 
OLDPWD=/home/me2
_=./minishell
sdf

