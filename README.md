# Unix SPITBOL V4.0 (July 2017)

SPITBOL is an extremely high performance implementation of the SNOBOL4 language that brings raw power and speed
to non-numeric computation.

SPITBOL V4.0 is currently only available for 64-bit x86_64 processors running Unix.  

The latest version of SPITBOL V4.0 can be found at [github.com/spitbol/x64](http://github.com/spitbol/x64).

Address comments, suggestions, and bug reports to `spitbol@fastmail.com`.

## Language Changes

Version 4.0 differs from previous versions of SPITBOL as follows:

*   The initial value of &ANCHOR is one, not null as in prior versions.

*   The initial value of &TERM is one, not null as in prior versions.

*   The initial value of &CASE is zero, not one as in prior versions.

The manual has always suggested setting &ANCHOR and &TERM to non-null values for more efficient searching.

Prior versions also folded cases by default, so that variables differing only in case, such as
'Var' and 'VAR' were treated as the same variable. Though this may have made sense when
lower case terminals and printers were just coming into use, those days are long gone.


## Known Problems and Limitations

The SAVE function doesn't work. (This loss of function occurred whilst adding 64-bit support).
Note that SAVE mode was mainly of interest back in the day when Spitbol was proprietary,
so that one could distribute a program written in Spitbol without having to disclose the source.

Load modules are not supported.

Loading of external functions is not supported.

## Installing SPITBOL

If you just want to use SPITBOL without building it, the file `./bin/spitbol`
contains a statically-linked copy of the 64-bit version of spitbol.

You can install it in `/usr/local/bin/spitbol` with the command:

```
    $ sudo make install
```
## Required Programs
    
Three tools are needed to build Spitbol:

  1. A C compiler
  2. A C runtime library
  3. An assembler

SPITBOL uses the gcc compiler to compile C source files.

SPITBOL uses [musl](http://musl-libc.org) for the runtime support.
The command `musl-gcc` must be used instead of `gcc` to link to the musl library and include files.

SPITBOL requires NASM, the Netwide ASseMbler: [nasm](http://www.nasm.us) to assemble the generated
x86_64 machine code.


## Building SPITBOL

You should be able to build SPITBOL on most Unix systems.

The file `./bin/spitbol` is the base version of Spitbol that is used to build the system.  

To see if spitbol is working, try the "hello world" program:

```    
    $ ./bin/spitbol test/hello.sbl
```
    
To build the system:

    
```    
    $ make clean
    $ make
```

This should produce the file `./spitbol`. You can test it with the "hello world"
program:

    
   ``` 
    $ ./spitbol test/hello.sbl
   ``` 

To test the system more comprehensively, do:
    
```    
    $ ./test/sanity-test
```    
    
This shell script should be run after bulding the system. Since part of the SPITBOL translator is written
in SPITBOL, it is essential to make sure that a new build of SPITBOL is able to build the system. The test
uses successive versions to build the system three times; first to see if the new version runs, second to see the
results of using it to build the system, and finally building the system again to see that none of the essential files were changed.

Three builds are needed, since it possible the new version contains an optimization or other code change whose effects will only
be tested in the final build.

Additional test programs can be found in the directory `./bin`.

NEVER replace the file `./bin/spitbol` with a newly built `spitbol` without first running and checking the results of
running the sanity test.  There's a good reason it has that name.  

Use the command below to install `spitbol` in `/usr/local/bin`.
    
```    
    $ make install
```    


## Files

The SPITBOL implementation includes the following files:

### Minimal source

The principal source file is `s.min`. The file `s.cnd` contains the definition of conditional assembly options.

### Minimal translation

`lex.sbl` is the first state of compilation. It converts the source file into a sequence of lexical tokens. 

The lexcal scan is followed by running `asm.sbl` to translate the tokens into machine code for the target machine.

The program `err.sbl` is used to produce a compact representation of the error messages contained in the Minimal source.

`./bin/spitbol` is the statically linked binary for SPITBOL. You should be able to run in on any 64-bit x86_64 processor
using Unix.


### OSINT - Operating System Interface

The directory `osint` contains the source files written in C99 that provide an interface to the Unix
environment.

### Assembly Language Support

The files  `x64.h`,  `x64.hdr`, and `x64.s` contain that part of the runtime that cannot be expressed in C and
so is written in assembler.

### Instruction Tracing

The file `z.sbl` can be used to insert trace code in generated assembly for debugging. This is not required to
build this system, and was last used in 2009 as part of the port of SPITBOL to Linux.

### Demonstration Programs

Some demonstration programs can be found in the directory `./demos`.

## Documentation

The documentation files for SPITBOL can be found in the repository:
http://github.com/spitbol/spitbol-docs.

## Additional Resources

Mark Emmer's SNOBOL4 site: [snobol4.com](http://snobol4.com)

Phil Bunde's SNOBOL site: [snobol4.org](http://www.snobol4.org)

