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

2mminishell $ cat -e << e < redir.c 
> e
AddressSanitizer:DEADLYSIGNAL
=================================================================
==67767==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000

2mminishell $ <<e
> sd
> sdf
> sdf 
> sdf 
> e
command not found
=================================================================
==68583==ERROR: LeakSanitizer: detected memory leaks

