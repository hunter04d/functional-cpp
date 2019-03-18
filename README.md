# Functional C++

## Examples of some functional patterns in C++17

This repository contains my attempt at implementing functional patterns in C++.\
I attempt to make the code as simple as possible which sometimes means that\
examples might contain some copies that can possibly be avoided in some, possibly large amount of code.

Most of the examples are usable in **constexpr** context.

Examples also contain a link to the same code in [compiler explorer](https://godbolt.org/) (where applicable).
Console output in compiler explorer links is replaced with return so that you can clearly see that the sample is inlined.

**note:** all of the examples are tested using latest stable **clang** build.\
They should work in gcc and they *might* work in msvc.\
If something does not work in gcc for some weird reason let me know (and raise an issue to the gcc and/or clang team depending on who is not conforming to the c++ standard this time).

## Usage

You need cmake (minimum version 3.13) and a clang with c++17 support (version 5 or latter)

```bash
mkdir build && cd build

CXX=$(which clang++) cmake ..

make

./[name of the executable]
```

each .cpp file creates a separate executable so that all of the examples can be tested individually without effecting each other.

## List of examples

Currently the following examples are implemented:

* [function composition](composition.cpp)
  
   the art of combining (chaining) functions to build more complicated ones.

* [partial_application](partial_application.cpp)
  
  The mechanism that allows to invoke a function with only a part of its arguments, producing a function with the rest of the arguments.\
  **note 1**: this is similar to `std::bind`(or actually c++20's `std::bind_front`) however much faster and constexpr. Also don't use `std::bind`.\
  **note 2**: if you really need to bind to some specific parameters of a function just use a lambda.

* [curring](curring.cpp)
  
  Separating a function of n arguments into a sequence of n functions each with a single argument.\
  This implementation separates a function of *p* arguments into some number of functions *n*
  with *p<sub>i</sub>* arguments such that *Σ<sup>n</sup><sub>i=1</sub>( p<sub>i</sub> ) = p*.\
  It will make sense when you will see the example.\
  Credit to [here](https://github.com/HowProgrammingWorks/PartialApplication/blob/master/JavaScript/7-curry.js) for inspiration.
  
* [pattern matching for `std::variant` and `std::optional`](match.cpp)
 
  This one uses naming to make it look like pattern matching is supported on language level 

