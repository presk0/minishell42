# minishell42
school project
2mminishell $ unset sdgf
AddressSanitizer:DEADLYSIGNAL
=================================================================
==64340==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x5606069aeb7c bp 0x7ffd2ba07350 sp 0x7ffd2ba07350 T0)
==64340==The signal is caused by a READ memory access.
==64340==Hint: address points to the zero page.
    #0 0x5606069aeb7b in ft_memcmp (/home/me2/minishell42/minishell+0xfb7b)
    #1 0x5606069a44da in run_unset /home/me2/minishell42/bultins2.c:213
    #2 0x5606069a2ee4 in check_built /home/me2/minishell42/bultins2.c:77
    #3 0x5606069aa0ae in exec_bultins /home/me2/minishell42/pipe.c:24
    #4 0x5606069a65c5 in execute_single /home/me2/minishell42/exec_single.c:24
    #5 0x5606069a67c3 in single_cmd /home/me2/minishell42/exec_single.c:45
    #6 0x5606069a9f6c in parser /home/me2/minishell42/parser.c:25
    #7 0x5606069a93b2 in main /home/me2/minishell42/main.c:97
    #8 0x7f7dab0d5082 in __libc_start_main ../csu/libc-start.c:308
    #9 0x5606069a26cd in _start (/home/me2/minishell42/minishell+0x36cd)


si possible
signaux et ctrl d dans le heredoc


