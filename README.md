# minishell42
school project


reste a faire : 

nicolas ; gestion des reidrections et implementation heredoc -> voir le fichier command.c   / le heredoc se trouve dans redir.c

stephane ; signaux et ctrl d

norme


strucure de minishell ; 


Parser2

  si 1 commande : f_matrix redir
                  execute
                  
  si plusiseurs commandes :
                  ft_child process -> execute_pipe
                  ft_parent_process -> wait et close
gestion du cat | ls pas sur de le faire

echo $? doit renvoyer param->retour 

space et entree affiche commande non valide mais devrait afficher un nouveau prompt