# Custom Database Language Compiler

A high-level, stateful database management language built from scratch in C. 

## Project Vision
This project is not just a standard compiler; it is a **Stateful Database Engine**. The goal is to create a unique language that allows users to:
1.  **Define Structure**: Create Databases and Tables using high-level syntax.
2.  **Maintain State**: The compiler "remembers" its context (e.g., which DB or Table is currently active).
3.  **Store Multimedia**: Design tables to hold text, integers, and references to complex media (Images, Video, Audio).
4.  **Connect Remotely**: In the future, this C backend will act as a Socket Server, allowing external applications (like Swift iOS apps) to connect, query, and retrieve data.

## Architecture
The system follows a Compiler-to-Executor pipeline:
* **Lexer**: Tokenizes the custom source code (Keywords: `NEW`, `DB`, `ADD`, `GET`).
* **Parser**: Builds an Abstract Syntax Tree (AST) of **Commands** rather than just variable declarations.
* **Executor**: Walks the AST and performs physical file operations:
    * `NEW DB` -> Creates a directory.
    * `NEW TABLE` -> Creates a human-readable `.txt` file with headers.
    * `ADD` -> Appends data to the file.

## Syntax Preview
The language is designed to be imperative and readable.

```text
CODE {
    ## 1. Create a container
    NEW DB db1;
    USE db1;

    ## 2. Define a Table Schema
    NEW TABLE Movies {
        Int: id,
        String: title,
        String: file_path
    };

    ## 3. Enter Table Context
    USE Movies;

    ## 4. Manipulate Data
    ADD NEW { "Finding Nemo", "videos/nemo.mov" };
    ADD NEW { "The Matrix", "videos/matrix.mp4" };
    
    ## 5. Query
    GET id = 1;
    FIND DUPLICATE;
    REMOVE id = 2;
}