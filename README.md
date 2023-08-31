b2rust is written in C++ and converts a B program into a Rust library (a set of Rust code files) which can be compiled without errors (but not necessarily without warnings). The functions it defines can be used in a separate Rust project.

Its calling syntax is the following:

`b2rust module -I directory [-O output_directory]`

If an `output_directory` is not provided, the Rust library will be generated in the current directory.

Input requirements:
--- `module` is the base module or entry module: the module which recursively imports every module and which is not imported by any module.

--- `directory` must be accessible and contain the base module (so, the files `directory/module.bxml` and `directory/module_i.bxml` must exist and be readable) as well as any imported component (which have to be implemented). All these files have to be BXML 1.0 compliant files.

--- b2rust needs to have write access to `output_directory`. It should not already contain files whose name are under the shape `i.rs`, where `i` is the name of a module in `directory`.

`b2rust module -I directory [-O output_directory]`

If these requirements are not respected, an unknown behaviour could happen.

If the B module associated with the `module.bxml` and `module_i.bxml` as well as recursively imported modules codes match some specifications, b2rust shall generate a Rust library (a code file for each module whose name is the name of the module) which matches the specification of the B entry module. To put in a nutshell, b2rust translates variables, constants, assignments, `if`/`then`/`else`, asserts, local variables definitions, and operation definition with any number of input or output parameters, imports, operation calls, some expressions using tabulars, integers, booleans, basic maths.

If the B implementation associated with the provided BXML file matches some specifications, b2rust shall give the user a Rust library which matches the specification of the B module. To put in a nutshell, b2rust translates variables, constants, assignments, if/then/else, asserts, local variables definitions, and operation definition with any number of input or output parameters.

The library can be compiled with the command `rustc --crate-type=lib a.rs` (if `a.rs` is the generated file). The library can then be used in a Rust project (with a `main`), using the compilation option `--extern out=libout.rlib`.

Run `cmake . && make` if you want to compile, `ctest .` if you want to run the tests.

For further details, read the documentation: `doc/specification.pdf` (`doc/specification.tex` if you cannot read PDFs).

If the B module associated with the `module.bxml` and `module_i.bxml` as well as recursively imported modules codes match some specifications, b2rust shall generate a Rust library (a code file for each module whose name is the name of the module) which matches the specification of the B entry module. To put in a nutshell, b2rust translates variables, constants, assignments, `if`/`then`/`else`, asserts, local variables definitions, and operation definition with any number of input or output parameters, imports, operation calls, some expressions using tabulars, integers, booleans, basic maths.

# Dependencies

b2rust relies on tinyxml2 and libboost. The src code of tinyxml2 and libboost are not included in b2rust. In order to use both package please download them and configure the CMakeList yourself.  
	
	sudo apt-get install libtinyxml2-dev
	sudo apt-get install libboost-dev

They can also be found in  
https://packages.debian.org/buster/libtinyxml2-dev  
https://pkgs.org/download/libboost-dev  
	
# SEES clause 

SEES clause is not well translated yet, please refer to the reference manual of B language. For the moment; sees clause is exactly like an import.

# Ce qu’il manque dans `b2rust`

Quelques remarques en langue française pour les futurs développeurs: une section dans la documentation vous est destinée (elle s’appelle « Development conventions »). Dans la théorie elle devrait aussi contenir des pistes d’amélioration, mais elle est lacunaire pour l’instant. Donc, je vais dire ce qu’il serait bon de faire ici. Par ordre décroissant de priorité:

* "Deviner" les types quand c’est possible, c’est-à-dire lever l’obligation de devoir SEES un composant qui contient les types Rust et obliger l’utilisateur à s’en servir.

