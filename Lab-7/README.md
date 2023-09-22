# Question-1

## Write a program using pipe() and fork() in which parent process takes one string as input. The same is sent to the child using pipe1 and child will reverse it. After the reversing is completed, the child process will send it (reversed string) to parent process using pipe2. Subsequently, parent process will read the string and displays it.

# Question-2

## A parent process creates a child process and the child process creates a grandchild process. The parent creates a pipe that is shared between the parent and the child. The parent writes a message to the pipe and the child reads it from the pipe. The child creates another pipe which is shared between the child and the grandchild. Note that this pipe is not available to the parent and is not the same as the one shared by the parent and the child. The grandchild writes another message to the pipe and the child reads it from the pipe. After obtaining the two messages from the pipes, the child prints the difference in lengths of the two messages. Moreover, each of the three processes prints the PID of its respective parent process. The contents of the two messages must be taken as user inputs.