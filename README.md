# Minishell

## As beautiful as a shell

### This project is about creating a simple shell

## To Do
* Initialise an enrionment for the program, i.e. copy data from envp into data->env, so we are not modifying the environment variables of the parent process that launched minishell.
* Executor
* Ctrl-D, Ctrl-C, Ctrl-/
* Handle $?
* Heredoc
* Working history
* Check for leaks

## Tests
### Fork & Execve
* Run minishell, then run the following command `$> foo`. It must fail with a proper error message and then give back the prompt.
* Run the following command `$> /bin/ls`. ls must be properly executed and then give back the prompt.
* Run the following command `$> /bin/ls -laF`. ls must be properly executed with the -l, -a, -F flags and
* Run the following command `$> /bin/ls -l -a -F`. ls must be properly executed with the -l, -a, -F flags and then give back the prompt.
then give back the prompt.
### Builtins
- Run minishell, then run the following command `$> exit`. The program must terminate proprely and give back the parent's shell. Run the minishell again.
- Run a command such as `$> echo `It works``. The message must be properly displayed.
- Run a command such as `$> echo It works` (without the double quotes). The message must be properly displayed.
- Run a command such as `$> cd /absolute/path/of/your/choice`, then run the following command `$> /bin/pwd`. /bin/pwd
must confirm that the current folder was updated.
- Run a command such as `$> cd relative/path/of/your/choice`, then run the following command `$> /bin/pwd`. /bin/pwd
must confirm that the current folder was updated.
- Run the following command `$> cd`, then run `$> /bin/pwd`. /bin/pwd must confirm that the current folder is the
user's home folder.
- Run the following command `$> cd -`, then run `$> /bin/pwd`. /bin/pwd must confirm that the current folder is the
folder relative/path/of/your/choice used before.
- Run the following command `$> cd ~/path/of/your/choice`, then run `$> /bin/pwd`. `$> /bin/pwd`. /bin/pwd must confirm that the current folder was updated.
### Environment management
- Run the following command `$> env`. Environment variables must be displayed as key=value.
- Run a command such as `$> setenv FOO bar` or
`$> setenv FOO=bar` depending on the implemented syntax. Then run the following command `$> env`. The environment must display a FOO variable with the value bar.
- Run the following command `$> echo $FOO`. The value bar must be displayed.
- Run the following command `$> /usr/bin/env`. Minishell must send the appropriate environment to ran binaries. /usr/bin/env must display environment including FOO and its value bar.
- Run the following command `$> unsetenv FOO`. Then run `$> env`. The environment variable FOO must not be displayed anymore.
- Run the following command again `$> unsetenv FOO`. Then run `$> env`. Environment must not change.
- Run the following command again `$> /usr/bin/env`. /usr/bin/env must not display variable FOO anymore.
### PATH management
- Run the following command `$> unsetenv PATH`, then run `$> setenv PATH `/bin:/usr/bin` or `$> setenv `PATH=/bin:/usr/bin` depending on the implemented syntax. Then run the following command `$> ls`. /bin/ls must be properly executed.
- Run the following command `$> emacs`. /usr/bin/emacs must be properly executed.
- Run the following command `$> unsetenv PATH`, then run `$> ls`. It must fail.
- Run now the following command `$> emacs`. It must also fail.
- Run the following command `$> /bin/ls`. /bin/ls must be properly executed.
- Run the following command `$> /usr/bin/emacs`. /usr/bin/emacs must be properly executed.
### Command line management
- Run an empty command `$> `. The shell must do nothing and give back the prompt.
- Run a command made of just a single space `$> `. The shell must do nothing and give back the prompt.
- Run a command made of spaces and tabulations. The shell must do nothing and give back the prompt.
- Run a command made of spaces and tabulations before and after its named and between its parameters such as
`$> /bin/ls -l -A`. All those
spaces and tabulations musn't interfere with the
command's execution.
### Signal

- Instead of typing a command press Ctrl-C. The shell must just give back the prompt
- Type a random command but instead of running it press Ctrl-C. The minishell must give back and empty prompt.
- Run the following command `$> cat`, then when cat waits for inputs on the standard input, press Ctrl-C. The
minishell must kill cat's process and give back the
prompt.

## Sources

### Writing your own shell

[https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

[https://github.com/Swoorup/mysh](https://github.com/Swoorup/mysh)

### Shell Command Language

[https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)

### Bash Reference Manual

[https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/index.html#SEC_Contents](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/index.html#SEC_Contents)
