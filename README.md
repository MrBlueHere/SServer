# SServer
Simple HTTP Server or simply: **Simple Server**

Author: Ladislav Floriš

## Original assignment
HTTP server

The task is to program a simple HTTP server with support for various content generators. The content generator must support:

1. listing the contents of the directory
2. specific html page (static content)
3. an external script or program

The server must implement:

1. loading the configuration file
2. network listening parameters (IP address, m_port)
3. Restrictions on working with a specific directory
4. log of transmissions (where to save, in what format, what should the header of each record look like, ...)
5. shut down the server at a (configurable) URL

HTTP server can be able to serve multiple domains or provide a virtual filesystem (mapping virtual URLs to physical disk paths)

Optional: Support for HTTPS (openssl), multi-threaded client service

Where can polymorphism be used? (recommended)

- File type: directory, HTML file, image, script, unsupported format, ...
- Logging: on console, to file, to database, ...
- Logging style: simple header, complete request (eg only for error states), access statistics, ...

## Getting Started
After cloning the repository, run ``` make ``` in terminal, which will generate the documentation and compile the source files.
Then run the project using ``` make run ``` or call the generated binary directly, optionally passing a path to a
config file as an argument.

### Prerequisites

- C++ 17
- g++ verion 8 and higher
- Running on Linux/Unix os only


## Specification
I will create a Simple HTTP Server serving static files (html, images and other) as well as running executable scripts.
The server will support HTTP Version 1.1 and it will be limited to GET requests only.
Due to usage of system calls like `sendfile()`, it is portable only to Unix/Linux.

It will be possible to customize server configuration by modifying a config file (logic implemented in `CConfiguration` class).

Each connection will get a dedicated thread (for simplicity purposes, we won't use thread pools or in any way reuse
already created threads) to make serving multiple clients faster.

### Polymorphism 
Polymorphism used in class `CFile`. `CFile` is an abstract class with derived classes `CStaticFile` `CDirectory`, `CExecutableScript`,
 `CError` and `CShutdown`.
`CFile` contains a pure virtual function `SendResponse` to send response to a given socket. When a file type is determined, appropriate
class derived from `CFile` is instantiated and when sending response, method `SendResponse` is called irrespective of the file type.

Polymorphism is used in class `CLogger`. `CLogger` is an abstract class with 2 derived classes `CConsoleLogger` and `CFileLogger`
which implement logging to console and file respectively. `CServer` class instantiates an appropriate logger class in `Startup` 
based on the configuration. Logging methods are then used to log messages irrespective of the instantiated logger.
There are 3 methods for logging `Info`, `Warn` and `Error`. All of them are pure virtual methods and they are implemented in 
the derived logger classes.

## Acknowledgments
- [HTTP 1.1](https://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html)
- The basics, well explained in this [medium article](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)