all: shell

shell: sash.c
	@gcc -o sash sash.c utilities.c info.c pwd.c command.c print.c cd.c ls.c pinfo.c signal.c redirect.c pipe.c jobs.c sig.c ground.c replay.c

execute: sash
	@./sash