b2rust is written in C++ and converts a B program into a Rust library (a set of Rust code files) which can be compiled without errors (but not necessarily without warnings). 
The produced Rust functions may be used in a separate Rust project.

It is a command-line program. Its usage is:

```sh
b2rust module -I directory [-O output_directory]
```

where

- `module` is the top-level B module: the module which recursively imports every module and which is not imported by any module.

- `directory` must be accessible and contain the top-level module (so, the files `directory/module.bxml` and `directory/module_i.bxml` must exist and be readable) as well as any imported component (which have to be implemented). All these files have to be BXML 1.0 compliant files.

- If `output_directory` is not provided, the Rust library will be generated in the current directory.

- b2rust needs to have write access to `output_directory`. It should not already contain files named `i.rs`, where `i` is the name of a module in `directory`.

`b2rust module -I directory [-O output_directory]`

The behavior is undefined if those constraints are not met.

b2rust translates

- concrete variables,
- concrete constants,
- sequential assignments,
- `if`/`then`/`else`,
- asserts,
- local variables
- operation calls
- arrays, different integers types and Booleans.

The library produced by b2rust may be compiled with the command `rustc --crate-type=lib a.rs` (if `a.rs` is the generated file).
The library can then be used in a Rust project (with a `main`), using the compilation option `--extern out=libout.rlib`.

Run `cmake . && make` if you want to compile, `ctest .` if you want to run the tests.

For further details, read the documentation: `doc/specification.pdf` (`doc/specification.tex` if you cannot read PDFs).

# Dependencies

b2rust relies on tinyxml2 and libboost and they need to be installed on your system when b2rust is compiled.

In Debian-based Linux distributions, you may install these external dependencies with the following commands:  

```sh
	sudo apt-get install libtinyxml2-dev
	sudo apt-get install libboost-dev
```

You may need to edit the compilation instructions in the file `CMakeLists.txt`.

