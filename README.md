# SServer
Simple HTTP Server or simply: **Simple Server**

Author: Ladislav Floriš

## Getting Started
After cloning the repository, run ``` make ``` in terminal, which will generate the documentation and compile the source files.
Then run the project using ``` make run ``` or call the generated binary directly, optionally passing a path to a
config file as an argument.

### Prerequisites

- C++ 17
- g++ verion 8 and higher
- Running on Linux/Unix os only

### Compiling & Running
Run ```make compile``` in project directory and then call the generated binary ```./sserver``` optionally, passing a config file,
you can see an example at ```examples/config.txt```, feel free to edit the config as you need.

Run ```make clean``` to delete the generated binaries and object files. 

## Specification
Minimalistic HTTP Server serving static files (html, images and other) as well as running executable scripts.
The server supports HTTP Version 1.1 and it is limited to GET requests only.
Due to usage of system calls like `sendfile()`, it is portable only to Unix/Linux.

It is possible to customize server configuration by modifying a config file (logic implemented in `CConfiguration` class).

Server implements a simple multi-threading model. Each connection gets a dedicated thread (ideally a thread pool should be used in the future),
to make serving multiple clients faster.

## Acknowledgments
- [HTTP 1.1](https://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html)
- The basics, well explained in this [medium article](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)