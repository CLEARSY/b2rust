# b2rust

## Introduction

b2rust is written in C++ and produces Rust source code from a B component.
The produced source code is a Rust library (a.k.a crate).

```text
Usage:
  b2rust [-h | --help]
  b2rust [-v | --version]
  b2rust [-x] -i src [ -c cfgpath ] ( -l lib )* [ -o dst ] component
Options:
  -c, --configuration path  Sets the path to the configuration directory
  -I, -i, --include path    Sets the path to a directory containing BXML files of the main project
  -l, --library path        Sets the path to a directory containing BXML files of a library project
  -o, --output path         Sets the path to a directory where the generated Rust files are stored
  -h, --help                Display this help message and exits
  -v, --version             Displays the program version and exits
  -x, --xml                 Output messages are embedded in XML elements (does not apply to -h and -v)
```

Generates Rust code from the given component, using the settings in the given configuration directory,
and the BXML files of the module and its dependencies. If the component has an implementation, the
generated code is that of this implementation. Otherwise, the component is considered that of a base
module.

If the B module associated with the `module.bxml` and `module_i.bxml`
as well as recursively imported modules codes are in the translatable
subset of the B language, b2rust generates a Rust library (a code file for
each module whose name is the name of the module) which matches the
specification of the B entry module.

In a nutshell, b2rust
translates variables, constants, assignments, `if`/`then`/`else`,
asserts, local variables definitions, and operation definition with
any number of input or output parameters, imports, operation calls,
some expressions using tabulars, integers, booleans, basic maths.

The library can be compiled with the command

```sh
rustc --crate-type=lib a.rs
```

(if `a.rs` is the generated file). The library can then be used
in a Rust project (with a `main`), using the compilation option
`--extern out=libout.rlib`.

## Dependencies

`b2rust` has dependencies on `fmtlib/fmt` (which should be
replaced by `std::format` in the future) and on `tinyxml2`.
They are available at the following URLs:

* <https://github.com/fmtlib/fmt>
* <https://github.com/leethomason/tinyxml2>

## Compilation

You need a C++ compiler, the CMake build system. The first build should be done while online so that the dependencies may be downloaded and compiled.

Create a directory for the compilation artifacts, and move
to that library:

```sh
mkdir build && cd build
```

Build

```sh
cmake <path to b2rust source code>
cmake --build .
```

## Future work

* Have a `b2rustc` binary that checks if a B implementation is
  compliant with the subset of B translatable wit `b2rust`.
  The output produced by such tool should be as user-friendly
  as possible by providing clear messages with line and column
  numbers of problems detected in the source file.

### Miscellaneous notes in French

Quelques remarques en langue française pour les futurs développeurs:
une section dans la documentation vous est destinée (elle s’appelle
« Development conventions »). Dans la théorie elle devrait aussi
contenir des pistes d’amélioration, mais elle est lacunaire pour
l’instant. Donc, je vais dire ce qu’il serait bon de faire ici. Par
ordre décroissant de priorité:

* "Deviner" les types quand c’est possible, c’est-à-dire lever
  l’obligation de devoir SEES un composant qui contient les types Rust
  et obliger l’utilisateur à s’en servir.
* Le produit cartésien pour définir un tableau, par exemple (0..4) *
  {0} pour un tableau de taille 5 ne contenant que des tableaux.
* La syntaxe alternative pour les tableaux: par exemple ((0..2) *
  (0..4)) --> rust_i32 au lieu de (0..2) --> ((0..4) -->
  rust_i32). Même chose pour ls définitions d’éléments & les accès aux
  éléments.
