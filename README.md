# pipex
The program executes standard commands (at least two) with input from a file, and writes output to another file.
## How it works
- Allocates an array to store opened descriptors of files and pipes
- Opens pipes
- Forks ❤️and creates as many child processes as there are commands
- Every child process except first and last changes input and output from standard to pipes'. First and last ones open files to read or write
- If a command's file can be found with relative or absolute path or using PATH environment variable and it is executable each child process calls execve() and starts command
- Parent process finishes after all commands are executed
## Usage
	make
	./pipex [input file] [cmd] [cmd] ... [cmd] [output file]
If a command takes arguments they should be in one string, like 'cat -e'.
### All task conditions:
[en.subject.pdf](https://github.com/squickfi/pipex/blob/master/en.subject.pdf)
