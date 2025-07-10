# Rovar Programming Language

**What is Rovar?**
Rovar is a new programming language designed and implemented by a single developer. It aims to be a low-level language with many modern features. The syntax is inspired by C and Rust, but also includes ideas from Python and other languages.

## Features
- **Strong Typing:** All variables are explicitly typed (e.g. `var x :int = 5`).
- **Low-Level Memory Management:** Allocate, free, and manipulate memory directly (like C/Rust) with `alloc`, `free`, `memcpy`, `memset`, and pointer types.
- **Type Conversion:** Convert variables between types with `convert.var('variable_name' :str => int)`.
- **Error Handling:** Modern error handling with `error_handling { try { ... } error (err) { ... } finally { ... } }` blocks. No silent failures—errors are always explicit.
- **System & Network Functions:** Built-in commands for file, process, system, and network operations (e.g. restart, shutdown, ping, ftp, sockets).
- **Pattern Matching:** `switch` blocks for clear multi-case logic, including a `NULL` case for unmatched values.
- **Lambda Functions:** Anonymous functions for functional programming and filtering.
- **Logging & Debugging:** Built-in logging, debug, and assertion tools for easier development.
- **Modern Syntax:** Inspired by Rust, Python, and C, but with its own style. Supports comments, multi-line comments, and readable blocks.
- **Cross-Platform:** Designed to work on Windows and Linux, with system-specific commands.

## Example
```rov
var name :str = std::scan();
printf("Hello, {name}!");

error_handling {
    try {
        var ptr :*int = alloc(10);
        ptr[0] = 42
        printf(ptr[0]);
        free(ptr);
    }
    error (err) {
        printf("Error: {err}");
    }
}

# Type conversion example
var num_str :str = "123";
convert.var('num_str' :str => int);
printf(num_str);
```

## Syntax Highlights
- **Variables:** `var x :int = 5` / `var mut y :str = "hello"` (all variables must have a type)
- **Functions:** `fn my_func { ... }` (define reusable code blocks)
- **If/Else:** `if (x == 1) { ... } elseif (x == 2) { ... } else { ... }` (conditional logic)
- **Loops:** `loop { ... }` (infinite loop) / `for i in my_list { ... }` (iterate over lists)
- **Switch:**
  ```rov
  switch (x) {
      "1" => { ... }
      "2" => { ... }
      NULL => { ... }  # fallback/default case
  }
  ```
- **Memory:** `let ptr = alloc(100)` / `free(ptr)` (manual memory management)
- **Type Conversion:** `convert.var('x' :str => int)`
- **System:** `system.restart()`, `system.kill.process("name.exe")`, etc.
- **Network:** `network.ping("example.com")`, `ftp.connect(...)`, etc.
- **Lists/Arrays:** `my_list = arr! ["a", "b", "c"]` (easy list creation)
- **Dictionaries:** `user = {"name": "Max", "password": "1234"}`
- **Comments:** `< this is a comment >` and `/**/ multi line comment`

**Status:**
Rovar is still in progress. Contributions, feedback, and ideas are welcome!
