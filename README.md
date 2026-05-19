_This project has been created as part of the 42 curriculum by pkongkha_

# Description
The project aims to teach you about pipe and file descriptor, which will helps you be able to create program that can manipulate file contents, and help you understand how "|" work in shell.

# Instructions
This program is split in two parts, one is standard, another is bonus

For standard program, it takes 4 arguments
```sh
./pipex <file_in> <cmd1> <cmd2> <file_out>
```
Which will open file_in and redirect it into cmd1 then STDOUT from cmd1 is piped (redirected) into STDIN cmd2 then STDOUT is redirected to the file_out.
Which equivlent to
```sh
< file_in cmd1 | cmd2 file_out >
```

The program is like the standard, just can takes more commands
```sh
./pipex <file_in> <cmd1> <cmd2> <cmd3> ... <cmdN> <file_out>
```

Which equivlent to
```sh
< file_in cmd1 | cmd2 | cmd3 | ... | cmdN file_out >
```

# Resources
- manpages
- [RedHat | How to use Valgrind to track file descriptors](https://developers.redhat.com/articles/2023/01/09/how-use-valgrind-track-file-descriptors#valgrind___track_fds_yes)
- [OpenGroup | IEEE Std 1003.1-2017 - Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
	- Section 2.7 redirection
	- Section 2.9.1 simple commands
	- Section 2.9.2 pipelines

## AI Usage
- Ask where to close fd.
- How to check for zombied process
- How can pipe be used
- Find source about pipe behavior
- Ask about WIFEXITED behavior
