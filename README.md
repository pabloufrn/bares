# Introduction

This programming project implements simple versions of two algorthms to become part of the BARES programming project.

We introduce a few simplifications on the input so we may focus only on the algorithms itself.
They are: the arithmetic expressions must only accept one-digit operands, and; all expressions are considered syntactically correct.

# Operations, scope, and precedence

The supported operations and scope delimiters are:

- `^`: power, right association, weight=3.
- `*`: multiplication, left association, weight=2.
- `/`: division, left association, weight=2.
- `%`: module, left association, weight=2.
- `+`: addition, left association, weight=1.
- `-`: subtraction, left association, wight=1.
- `(`: opening scope, weight=0.
- `)`: closing scope, weight=n/a.

# Compilation

	If you are in a GNU/LINUX environment with make file available, you can use the commands
	- make: to compile the file.

	- in case the make command isn't available, you can use g++ commands:  
	`g++ -Wall -std=c++11 src/driver_bares.cpp`

# Execute

	To this step you need to compile the code, if you didn't compile visit the 'Compilation' section.

	- You can use ./exec in LINUX (using make to compile). 


# Authorship
Program developed by Henrique David de Medeiros (*henriquemed101@gmail.com*) and Pablo Emanuell L. Targino (*pabloemanuell@academico.ufrn.br*)