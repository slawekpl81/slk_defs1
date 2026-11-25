# slk_defs1

A lightweight C++ library providing core definitions, type aliases, and utility helpers.

## Requirements

* A C++ compiler supporting **C++17** (or newer)
* **[Xmake](https://xmake.io)** build system

## Integration

### Using Xmake

You can integrate `slk_defs1` into your project by including its directory or adding the header path to your `xmake.lua`:

```lua
includes("path/to/slk_defs1")

target("your_app")
    set_kind("binary")
    add_files("src/main.cpp")
    add_deps("slk_defs1")
```

*(Alternatively, if it is a header-only library, simply add the include path:)*

```lua
add_includedirs("path/to/slk_defs1/include")
```

## Quick Start

```cpp
#include <iostream>
#include <slk_defs1/your_header.hpp> // Replace with your actual header file

int main() {
    // Example usage of types, macros, or functions from slk_defs1
    return 0;
}
```

## Building & Running Tests

To build the library and execute the unit tests located in the `tests/` directory:

```bash
# Build the project
xmake

# Run all unit tests with verbose output
xmake test -v
```

## Project Structure

* `include/slk_defs1/` – Public header files (API)
* `src/` – Library source files
* `tests/` – Unit tests
* `xmake.lua` – Xmake build configuration
