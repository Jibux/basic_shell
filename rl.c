/*
 * rl - command-line interface to read a line from the standard input
 *      (or another fd) using readline.
 *
 * usage: rl [-p prompt] [-u unit] [-d default] [-n nchars]
 */

/* Copyright (C) 1987-2009 Free Software Foundation, Inc.

   This file is part of the GNU Readline Library (Readline), a library for
   reading lines of text with interactive input and history editing.

   Readline is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Readline is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Readline.  If not, see <http://www.gnu.org/licenses/>.
   */

#if defined (HAVE_CONFIG_H)
#  include <config.h>
#endif

#include <string.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <setjmp.h>

#ifdef HAVE_STDLIB_H
#  include <stdlib.h>
#else 
extern void exit();
#endif

#if defined (READLINE_LIBRARY)
#  include "posixstat.h"
#  include "readline.h"
#  include "history.h"
#else
#  include <sys/stat.h>
#  include <readline/readline.h>
#  include <readline/history.h>
#endif

extern int optind;
extern char *optarg;

#define RETSIGTYPE void
typedef RETSIGTYPE SigHandler (int);

static char *progname;
// static char *deftext;

sigjmp_buf ctrlc_buf;
// static int new_line = 0;

void handle_sigint(int sig) {
	//rl_callback_sigcleanup();
	//rl_cleanup_after_signal();
	//rl_callback_handler_remove();
	/*printf("\n"); // Move to a new line
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_free_line_state();
	rl_redisplay();*/
	/*rl_free_line_state();
	rl_cleanup_after_signal();
	RL_UNSETSTATE(RL_STATE_ISEARCH|RL_STATE_NSEARCH|RL_STATE_VIMOTION|RL_STATE_NUMERICARG|RL_STATE_MULTIKEY);
	rl_line_buffer[rl_point = rl_end = rl_mark = 0] = 0;*/
	//rl_signal_event_hook = handle_signals2;
	// new_line = 1;
	write(STDOUT_FILENO, "\n", 1);
	siglongjmp(ctrlc_buf, 1);
}

/*	static int
set_deftext ()
{
	if (deftext)
	{
		rl_insert_text (deftext);
		deftext = (char *)NULL;
		rl_startup_hook = (rl_hook_func_t *)NULL;
	}
	return 0;
}*/

	static void
usage()
{
	fprintf (stderr, "%s: usage: %s [-p prompt] [-u unit] [-d default] [-n nchars]\n",
			progname, progname);
}


SigHandler *
set_signal_handler (sig, handler)
     int sig;
     SigHandler *handler;
{
  struct sigaction act, oact;

  act.sa_handler = handler;
  act.sa_flags = 0;

  if (sig == SIGCHLD)
    act.sa_flags |= SA_RESTART;		/* XXX */
  /* If we're installing a SIGTERM handler for interactive shells, we want
     it to be as close to SIG_IGN as possible. */
  if (sig == SIGTERM && handler == handle_sigint)
    act.sa_flags |= SA_RESTART;		/* XXX */

  sigemptyset(&act.sa_mask);
  sigemptyset(&oact.sa_mask);
  if (sigaction(sig, &act, &oact) == 0)
    return (oact.sa_handler);
  else
    return (SIG_DFL);
}

int test_rl() {
	printf("TEST");

	return 0;
}

	int
main (argc, argv)
	int argc;
	char **argv;
{
	char *temp, *prompt;
//	struct stat sb;
//	int opt, fd, nch;
//	FILE *ifp;

	/*if (signal(SIGINT, handle_signals) == SIG_ERR) {
		printf("failed to register interrupts with kernel\n");
	}*/
    set_signal_handler(SIGINT, handle_sigint);

	progname = strrchr(argv[0], '/');
	if (progname == 0)
		progname = argv[0];
	else
		progname++;


	using_history();
	read_history("history_file");

	/* defaults */
	prompt = "readline$ ";
	/*fd = nch = 0;
	deftext = (char *)0;

	while ((opt = getopt(argc, argv, "p:u:d:n:")) != EOF)
	{
		switch (opt)
		{
			case 'p':
				prompt = optarg;
				break;
			case 'u':
				fd = atoi(optarg);
				if (fd < 0)
				{
					fprintf (stderr, "%s: bad file descriptor `%s'\n", progname, optarg);
					exit (2);
				}
				break;
			case 'd':
				deftext = optarg;
				break;
			case 'n':
				nch = atoi(optarg);
				if (nch < 0)
				{
					fprintf (stderr, "%s: bad value for -n: `%s'\n", progname, optarg);
					exit (2);
				}
				break;
			default:
				usage ();
				exit (2);
		}
	}

	if (fd != 0)
	{
		if (fstat (fd, &sb) < 0)
		{
			fprintf (stderr, "%s: %d: bad file descriptor\n", progname, fd);
			exit (1);
		}
		ifp = fdopen (fd, "r");
		rl_instream = ifp;
	}

	if (deftext && *deftext)
		rl_startup_hook = set_deftext;

	if (nch > 0)
		rl_num_chars_to_read = nch;*/

	/*rl_persistent_signal_handlers = 1;
	rl_catch_signals = 1;
	rl_set_signals();
	rl_reset_after_signal();*/

	//rl_signal_event_hook = test_rl;

	for(;;) {
		while ( sigsetjmp( ctrlc_buf, 1 ) != 0 );
		/*if(new_line == 1) {
			//printf("\n");
			// write(STDOUT_FILENO, "\n", 1);
			new_line = 0;
		}*/

		temp = readline(prompt);
		/*if(new_line == 1) {
			printf("\n");
			new_line = 0;
			free(temp);
			continue;
		}*/
		/* Test for EOF. */
		if (temp == 0) {
			write_history ("history_file");
			free(temp);
			rl_clear_history();
			return 0;
		}

		/*if (strlen(temp) >= 1) {
			char *expansion;
			int result;

			result = history_expand(temp, &expansion);
			if (result)
				fprintf (stderr, "%s\n", expansion);

			if (result < 0 || result == 2)
			{
				free(expansion);
				free(temp);
				continue;
			}

			add_history (expansion);
			// strncpy (temp, expansion, sizeof (temp) - 1);
			free (expansion);
		}*/

		add_history(temp);

		printf ("%s\n", temp);
		free(temp);
	}

	write_history ("history_file");
	rl_clear_history();

	return 0;
}

