# minishell

A small Unix shell written in C, modelled on bash. Built as part of the 42 curriculum.

## Overview

minishell reads a command line, breaks it into tokens, expands variables, builds a list of commands and runs them. It connects commands with pipes and redirections the way bash does.

It covers the core of an interactive shell: running programs from `PATH`, seven builtins, pipes, redirections, heredocs, environment variable expansion, quoting, exit statuses and signal handling.

## Features

| Feature | Details |
|---|---|
| Prompt | Interactive prompt with command history (GNU readline) |
| Commands | Runs programs by name (searched in `$PATH`) or by relative/absolute path |
| Builtins | `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit` (see [Builtins](#builtins)) |
| Pipes | `\|` sends the output of one command into the next |
| Redirections | `<` input, `>` output (truncate), `>>` output (append) |
| Heredoc | `<<` reads lines until the delimiter. Variables are expanded unless the delimiter is quoted |
| Quotes | `'...'` blocks all expansion. `"..."` blocks everything except `$` |
| Expansion | `$VAR` for environment variables, `$?` for the last exit status |
| Exit status | `127` command not found, `126` not executable, `128 + N` killed by signal N, `2` syntax error |
| Signals | `Ctrl-C` shows a new prompt, `Ctrl-D` exits, `Ctrl-\` is ignored at the prompt. Child processes get the default behaviour |

## Builtins

Builtins are commands implemented inside minishell itself instead of being separate programs. When a builtin is the only command on the line, it runs inside the shell process, so changes made by `cd`, `export`, `unset` and `exit` stay in effect. Inside a pipeline it runs in a child process like any other command, so those changes only last for that command.

| Builtin | Purpose |
|---|---|
| [`echo`](#echo) | Print text |
| [`cd`](#cd) | Change the current directory |
| [`pwd`](#pwd) | Print the current directory |
| [`export`](#export) | Set or list environment variables |
| [`unset`](#unset) | Remove environment variables |
| [`env`](#env) | Print the environment |
| [`exit`](#exit) | Leave the shell |

### echo

```
echo [-n] [text ...]
```

Prints its arguments separated by single spaces, followed by a newline.

- `-n` leaves out the trailing newline. Repeated forms such as `-n -n` or `-nnn` are accepted too.
- Once a normal argument appears, everything after it is printed as text, even something that looks like `-n`.
- Always returns `0`.

```
minishell:~$ echo hello    world
hello world
minishell:~$ echo -n no newline
no newlineminishell:~$
```

### cd

```
cd [directory]
```

Changes the current directory and updates the `PWD` and `OLDPWD` variables.

- With no argument (or `--`), goes to `$HOME`. Fails with `HOME not set` if `HOME` is missing or empty.
- `cd -` goes back to the previous directory stored in `$OLDPWD`. Fails with `OLDPWD not set` if there is none.
- More than one argument fails with `too many arguments`.
- Returns `0` on success and `1` on error.

```
minishell:~$ cd /tmp
minishell:~$ pwd
/tmp
minishell:~$ cd nowhere
minishell: cd: nowhere: No such file or directory
```

### pwd

```
pwd
```

Prints the full path of the current directory. Any arguments are ignored. Returns `0`, or `1` if the directory can't be read.

```
minishell:~$ pwd
/home/user/minishell
```

### export

```
export [NAME=value ...]
```

Sets environment variables, which are then passed to every program minishell runs.

- With no arguments, lists every variable as `declare -x NAME="value"`, in the order they are stored.
- `NAME=value` creates the variable, or replaces its value if it already exists.
- `NAME` without `=` is checked but not added.
- A valid name starts with a letter or `_` and contains only letters, digits and `_`. An invalid name prints `not a valid identifier` and makes the status `1`, but the other arguments are still processed.

```
minishell:~$ export GREETING=hi
minishell:~$ echo $GREETING
hi
minishell:~$ export 1abc=x
minishell: export: '1abc': not a valid identifier
```

### unset

```
unset [NAME ...]
```

Removes each named variable from the environment.

- Names that don't exist are silently ignored.
- An invalid name prints `not a valid identifier` and makes the status `1`.

```
minishell:~$ export TEMP=1
minishell:~$ unset TEMP
minishell:~$ echo "[$TEMP]"
[]
```

### env

```
env
```

Prints every environment variable as `NAME=value`, one per line.

- It takes no options or arguments. Passing any prints `too many arguments` and returns `2`.

```
minishell:~$ env
HOME=/home/user
PATH=/usr/local/bin:/usr/bin:/bin
...
```

### exit

```
exit [n]
```

Exits the shell.

- Prints `exit` first, unless it is part of a pipeline.
- With no argument, exits with the status of the last command (`$?`).
- With a number, exits with that number modulo 256. For example, `exit 300` exits with `44`.
- A non-numeric argument prints `numeric argument required` and exits with `2`.
- More than one argument prints `too many arguments` and returns `1`. The shell keeps running.

```
minishell:~$ exit 42
exit
$ echo $?
42
```

## How it works

Each line typed at the prompt goes through these stages:

```
prompt → lexer → syntax check → expansion → parser → heredocs → execution
```

1. **Prompt** (`prompt/`): reads a line with readline, adds it to the history and handles `Ctrl-C` / `Ctrl-D`.
2. **Lexer** (`lexer/`, `tokenize/`): splits the line into tokens (words, `|`, `<`, `>`, `>>`, `<<`) and records which parts were quoted. An unclosed quote is rejected.
3. **Syntax check** (`prompt/validation.c`): rejects invalid input such as `| ls` or `ls >` and sets `$?` to `2`.
4. **Expansion** (`expansion/`): replaces `$VAR` and `$?`, leaving single-quoted text untouched. Adjacent pieces like `a"b"'c'` are then joined into one word.
5. **Parser** (`parser/`): builds a linked list of commands, each with its arguments and redirections.
6. **Heredocs** (`heredocs/`): collects all `<<` input in a child process before anything runs, so `Ctrl-C` cancels the whole line cleanly.
7. **Execution** (`executes/`, `redirection/`):
   - A single builtin runs in the shell process itself, so `cd`, `export`, `unset` and `exit` affect the shell.
   - Otherwise each command gets its own child process. The children are connected with pipes, their redirections are applied, and then they run a builtin or `execve` the program.
   - The shell waits for all children and stores the last command's status in `$?`.

## Project Structure

```
minishell/
├── Makefile
├── includes/
│   └── minishell.h          structs, constants and prototypes
├── libft/                   our C utility library
├── sources/
│   ├── main.c               entry point: sets up signals and starts the prompt loop
│   ├── prompt/              read loop, signal handlers, syntax validation
│   ├── lexer/               splits input into tokens and tracks quotes
│   ├── tokenize/            token list helpers and joining of adjacent tokens
│   ├── expansion/           $VAR and $? expansion
│   ├── parser/              builds the command list and its redirections
│   ├── heredocs/            << input collection
│   ├── executes/            forking, pipes, PATH lookup, execve
│   ├── redirection/         opening files and dup2 of input/output
│   ├── builtins/            echo, cd, pwd, export, unset, env, exit
│   ├── env/                 environment variable storage
│   └── utils/               error messages, cleanup, exit
└── valgrind_readline.supp   valgrind suppressions for readline's own leaks
```

## Installation

**Requirements**

- `cc` and `make`
- The GNU readline development library. On Debian/Ubuntu:

  ```sh
  sudo apt install libreadline-dev
  ```

**Build**

```sh
git clone git@github.com:melwongwk/minishell-anything.git minishell
cd minishell
make
```

This builds `libft` first, then produces the `minishell` executable.

## Makefile Targets

| Command | What it does |
|---|---|
| `make` | Builds `libft` and `minishell` |
| `make clean` | Removes object files (`objects/` and libft's objects) |
| `make fclean` | Runs `clean`, then removes `minishell` and `libft.a` |
| `make re` | Runs `fclean`, then builds everything again |
| `make VERBOSE=1` | Builds while showing the full compiler commands |

## Usage

Start the shell:

```sh
./minishell
```

You get the prompt `minishell:~$ `. Type commands as you would in bash. Use `exit` or `Ctrl-D` to quit.

## Usage Examples

**Variables and quotes**

```
minishell:~$ export NAME=world
minishell:~$ echo "hello $NAME" 'hello $NAME'
hello world hello $NAME
minishell:~$ unset NAME
minishell:~$ echo "[$NAME]"
[]
```

**Pipes**

```
minishell:~$ env | grep ^HOME=
HOME=/home/user
```

**Redirections**

```
minishell:~$ echo first > out.txt
minishell:~$ echo second >> out.txt
minishell:~$ cat < out.txt
first
second
```

**Heredoc**

```
minishell:~$ cat << EOF
> Hello $USER
> EOF
Hello user
```

**Exit status**

```
minishell:~$ notacommand
minishell: notacommand: command not found
minishell:~$ echo $?
127
```

## Authors

| Name | 42 login | Worked on |
|---|---|---|
| Howard Ho Jia Hao | hho-jia- | Builtins, environment, redirection, execution |
| Melvin Wong Wai Kit | melwong | Prompt, lexer, parser, expansion, heredocs, utils |
