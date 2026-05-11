# About the Project
## Overview
This project is about creating a simple compiler for C++ for EECS 348. It focuses on an Arithmetic Expression Evaluator in C++ using the Unified Process for Education.
## Getting Started
- C++
- make
- Bash Shell
- Git
## Installation
1. Clone the repository
2. Compile the program
3. Execute the program
## Usage

### Building

`make` is required to build this project.

**Linux/macOS:**
```bash
make
```

**Windows (PowerShell):**

`make` must be installed first.
pacman -S make
```
Then add it to your PATH if PowerShell cannot find it:
```powershell
$env:PATH += ";C:\msys64\usr\bin"
```
Then build:
```powershell
make
```

### Running

**Windows:**
```powershell
.\evaluator.exe
```

**Linux/macOS:**
```bash
./evaluator
```

> **Windows tip:** If the AST tree display looks garbled, run `chcp 65001` before launching to enable UTF-8 output.

### Supported Operators

| Operator | Description    | Associativity |
|----------|----------------|---------------|
| `+`      | Addition       | Left-to-right |
| `-`      | Subtraction    | Left-to-right |
| `*`      | Multiplication | Left-to-right |
| `/`      | Division       | Left-to-right |
| `%`      | Modulo         | Left-to-right |
| `**`     | Exponentiation | Right-to-left |

Unary `+` and `-` are also supported (e.g. `-3`, `+2`).

### Example Expressions

```
> 3 + 4
result: 3 + 4 = 7

> 2 ** 3
result: 2 ** 3 = 8

> 4 * (3 + 2) % 7 - 1
result: 4 * (3 + 2) % 7 - 1 = 5

> +(-2) * (-3) - ((-4) / (+5))
result: +(-2) * (-3) - ((-4) / (+5)) = 6.8

> -(-(-3)) + (-4) + (+5)
result: -(-(-3)) + (-4) + (+5) = -2
```

### Error Handling

```
> 4 / 0
error: Division by zero

> 2 * (4 + 3
error: Unmatched parenthesis

> 7 & 3
error: Invalid character '&' at position 2

> * 5 + 2
error: Unexpected token '*' at position 0
```

Type `exit` to quit the program.

## Roadmap
- [x] Project plan
- [x] Software requirements
- [x] Architecture design
- [x] Test cases
- [x] Use cases
- [x] Bug fixes
## Authors and Contributors
Quinn Sells, Hudson Rupp, Logan Sigg, Lauren Wesely, Collin Rawson, Jacob Harmsen
## Contacts
Quinn Sells - quinnsells@ku.edu
Hudson Rupp - hudson.rupp@ku.edu
Logan Sigg - l550s255@ku.edu
Lauren Wesely - wesely@ku.edu
Collin Rawson - collinrawson@ku.edu
Jacob Harmsen - j068h985@ku.edu
## License
Distributed under the Unlicense License. See LICENSE.txt for more information.
