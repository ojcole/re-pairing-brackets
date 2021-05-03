# Re-Pairing Brackets

This software results from a project that continued the work of Dmitry Chistikov and Mikhail Vyalyi, whose paper is available [here](https://dl.acm.org/doi/10.1145/3373718.3394752). Alongside theoretical results, this project ended in this software to assist with continued research into the area. Those who have no understanding of this paper and the game it introduces should refer to the paper this game is based on before approaching this library.

The library is written in C++, allowing the user to take advantage of C++ features in conjunction with the library.

## Bazel

As the software is written using Bazel as the build tool, for cloning and using this repository, the user should install Bazel from [here](https://docs.bazel.build/versions/master/install.html). Bazel can be run from any directory that has a `WORKSPACE` file at its root.

## Software Tests

To run all of the tests of the system with some additional compilation flags on, run the following command. These tests should take around 3 minutes to complete and should all pass. There is a minute chance that the tests fail due to statistical anomalies; however, this is vanishingly small. One should run this command from within the `src` folder.

```bash
bazel test //...:all --copt=-Ofast --copt=-std=c++2a
```

This command will run all of the tests found in the source. The general structure of the tests is to sit alongside the source file they are testing with a `_test` suffix. For example, to test the `generate_all.h` interface, the test file `generate_all_test.cc` contains the correctness checks. While running these tests, depending on your system performance, there is a chance a test will timeout. In such cases, one can rerun the tests using the `--test_timeout=[num]` flag where `[num]` specifies the number of seconds after which the test should time out.

## Examples

Included with the software are examples of using the library. There are seven different examples, and the user is invited to refer to the examples [README](./examples/README.md) for more details on each of them.

## Software Components

The software breaks down into different modules that represent a grouping of functionality. These modules are: generate, helpers, manual, search, solve, and stats. Alongside each of these components are some additional file used for benchmarking, generating code jobs, and Bazel config files. Each of the modules is broken down further into subcomponents.

In the following section, the different interfaces that each module and submodule provides will be detailed, giving more information on their purpose.

### Generation

The `generate` module contains all of the word generation functions that exist in the library. This module splits into four generation types: all generation, next generation, specific generation, and random generation.

-   All generation
    -   `generate_all.h` that interfaces for generating all Dyck words of a particular length
-   Next generation
    -   `generate_next.h` provides interfaces for generating the next Dyck word given the current
    -   `generate_next_symmetric.h` provides interfaces for generating the next positive Dyck walk of `n` symbols given the current
-   Specific generation
    -   `generate_xyz.h` provides interfaces for generating the different types of words: X, Y, and Z from the original paper
-   Random generation
    -   `generate_random.h` provides interfaces for generating uniform and Symmetric Dyck words
    -   `generate_random_hard.h` provides interfaces for generating Symmetric Hard words and Hard words

### Helpers

The `helpers` module contains different functionality for assisting the user with handling words and giving miscellaneous components a home. This module includes `parallel` and `solutions` as submodules, providing helpers for parallel computation and combining solutions, respectively.

-   Parallel
    -   `compute_parallel.h` provides interfaces for performing generalised parallel computation, handling most of the boilerplate code for you
    -   `reducers.h` provides interfaces for reducing output for usage in conjunction with the parallel computation interfaces
-   Solutions
    -   `combine_solutions.h` provides interfaces for combining solutions in a meaningful way
-   General
    -   `catalan.h` provides interfaces for generating the `nth` Catalan number
    -   `constants.h` provides constants used throughout the project for opening brackets, closing brackets, and spaces
    -   `manipulators.h` provides interfaces for manipulating the structure of Dyck words
    -   `n_choose_k.h` provides interfaces for calculating `nCk`
    -   `traversal.h` provides interfaces for traversing through words allowing for the next or previous of different symbols to be selected
    -   `verifiers.h` provides interfaces for verifying whether a Dyck word is valid or of a specific type

### Manual

The `manual` module contains functionality to assist with manually manipulating words and reducing their size. This module also includes some visualisation of the form of the words.

-   Manual search
    -   `manual_search.h` provides interfaces for storing and loading words from files in different forms and transforming words into different representations

### Search

The `search` module contains functionality to assist with searching for new Dyck words with given properties. This search either reduces existing words or tests properties of randomly generated words.

-   Random walk
    -   `random_walk.h` provides interfaces for randomly walking to find shorter words with the same width. Randomly walking takes a word, removes a character and then randomly flips symbols before testing the width
-   Segmented width search
    -   `segment_width_search.h` provides interfaces for substituting segments into a word to find shorter words with the same width. This search exhaustively generates all words of a given length as a segment
-   Width search
    -   `width_search.h` provides interfaces for randomly searching for a word of a specific width at a given value of `n`

### Solve

The `solve` module is the most significant part of the library, providing interfaces for finding approximate and optimal re-pairings for general Dyck words. The `solve` module provides basic interfaces at the top-level for solutions and approximating width and provides the following submodules: `chistikov`, `derived`, `exhaustive`, `greedy`, `minimise`, `parallel`, `predicate`, and `repairings`.

-   Chistikov
    -   `solve_chistikov.h` provides interfaces for finding re-pairings of words using the methods specified by Chistikov et al. in the [original paper](https://dl.acm.org/doi/10.1145/3373718.3394752)
-   Derived
    -   `derived_strategy.h` provides interfaces for finding re-pairings using the derived strategy based on the shortest width 3 word
    -   `free_moves.h` provides interfaces for performing what is known as free moves as part of the derived strategy
    -   `obvious_moves.h` provides interfaces for performing what is known as obvious moves as part of the derived strategy
-   Exhaustive
    -   `solve_exhaustive.h` provides interfaces for exhaustively solving a general Dyck word with different memory constraints
-   Greedy
    -   `calculate_strahler.h` provides interfaces for calculating the slightly modified Strahler number of the tree representation of a Dyck word - equivalent to calculating a simple re-pairing of the tree
    -   `greedy_strategy_1.h` and `greedy_strategy_2.h` provide scoring strategies for the scoring based non-simple greedy re-pairing strategy
    -   `greedy.h` provides interfaces for combining the different types of simple and non-simple greedy re-pairings
    -   `solve_greedy.h` provides interfaces for the non-simple scoring greedy re-pairing strategy
    -   `solve_simple_greedy.h` provides interfaces for the new greedy simple re-pairing strategy equivalent to the variation of the Strahler numbers providing a strong average width
-   Minimise
    -   `minimise_width.h` provides interfaces for removing all possible symbols from a word while maintaining its width
-   Parallel
    -   `parallel_worker.h` provides interfaces for the worker of the parallel search
    -   `result.h` provides the interface for the result of the parallel worker
    -   `solve_parallel.h` provides interfaces for exhaustively solving many words of varying lengths across multiple cores
-   Predicate
    -   `width_check.h` provides interfaces for testing if a word has a width of at least `k`
-   All re-pairings
    -   `all_repairings.h` provides interfaces for getting the set of all optimal re-pairings of a significant length `k`
-   General
    -   `solution.h` provides the interface used for all solutions produced by solving algorithms
    -   `solve_approximate.h` combines all different approximation methods for finding the width of a word into a single interface

### Stats

The `stats` module provides interfaces for gaining insights around words in terms of visualisation, properties and trends.

-   Hardness
    -   `hardness.h` provides interfaces for calculating the `Hardness` of a specific word
-   Random sampling
    -   `random_sample_width.h` provides interfaces for randomly sampling the widths of words of a specific length `n`
-   Results output
    -   `results_output.h` provides interfaces for outputting the results of re-pairings, parallel results, and samples
