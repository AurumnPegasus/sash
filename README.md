# SASH

Hey, this is a shell I created!

## How to use:

- Clone the directory
- run `make` inside the directory
- Profit!

## Features and Assumption

* `MAXLEN = 1024` , which is the maximum length of strings, maximum length of arguments etc


#### Multiple Commands

* Use `;` to use multiple commands in the same line!
* How does it work? sash uses a tokenizer to split the command line arguments based on `;`

* One can also use `|` to pipe commands like `ls -al | wc`, where the output of `ls -al` becomes input of `wc`. This was done using an iterative function and C's `pipe()` command

* You can also use `>`, `<` or `>>` for redirecting input manually, and this can also be used with piping.

#### cd 

* Change the directory to place mentioned by using `cd`
* `~ . .. -~ can be used just as you would in a normal shell
* A very simple and effecient implementation where sash gets the relative path from current dir to required, and then changes directory. 

#### pwd

* Get path to the current working directory by using `pwd`
* Simply gets the absolute path of current working directory, then converts it into relative based on `home`

#### echo

* Print everything which follows the command `echo`

#### pinfo

* Print the information for a given Process ID using `pid`
* Gives information about:
    - Proccess ID
    - Process Status
    - Virtual Memory
    - Executable Path
* Reads extra information from `proc` files and displays it accordingly. 

#### jobs

* Prints all the background processes which arent terminated yet `jobs`.
* `-r` flag only prints running jobs, and `-s` flag only prints stopped jobs
* To implement this, sash stores a array of structs with all the background jobs in it. It also works in conjuction with `CTRL+Z`. 

#### sig

* Sends a signal given index (of process in job list) and signal to send.
* Sash uses `kill` to implement this function

#### bg

* Brings a stopped background process back to life!! (still in background tho)
* A signal is sent to the process to achieve this

#### replay

* A very simple command `replay -command echo hi -interval 3 -period 6` where command `echo hi` is executed every `3 seconds` till `6 second` pass.
* This was done using C's `<time.h>` module and `sleep()` function

#### Signal Handling

* Basing signal handling is implemented to keep sash as close to normal bash, where `CTRL+` terminates a foreground process, `CTRL+Z` stopps a foreground process and takes it to background and `CTRL+D` exits the shell

## Directory Structure

* The main loop is within `sash.c`, which also intialises constants like `home` and sets up `signal`
* Then command goes to `command.c` which parses the input string, and redirects it accordingly 
* In each loop, we run `info.c` to print the prompt
* `cd.c` contains code related to cd
* `ls.c` contains code related to ls
* `pinfo.c` contains code related to pinfo
* `pwd.c` contains code related to pwd
* `print.c` contains code related to echo
* `signal.c` handles reaping the background child processes, also does signal handling
* `ground.c` contains code related to `bg`
* `jobs.c` prints a list of jobs and contains code for it
* `pipe.c` is the first step of command parsing, which then goes to `redirect.c`
* `redirect.c` is the second part of command parsing which then goes to `command.c`
* `replay.c` is used to handle the command `replay`. It calls `pipe.c` to execute the said command
* `sig.c` is code related to `sig` function
* `utilities.c` contains some functions which are used everywhere
* `header.h` contains some headers and function definitions

.
├── cd.c
├── command.c
├── ground.c
├── header.h
├── info.c
├── jobs.c
├── LICENSE
├── ls.c
├── Makefile
├── pinfo.c
├── pipe.c
├── print.c
├── pwd.c
├── README.md
├── redirect.c
├── replay.c
├── sash
├── sash.c
├── sig.c
├── signal.c
└── utilities.c


