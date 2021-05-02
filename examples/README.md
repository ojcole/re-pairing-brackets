# Examples

This folder contains some examples that utilise the library. The library is imported using the [Bazel](https://www.bazel.build/) WORKSPACE file and then [Bazel](https://www.bazel.build/) is used in each directory to set which parts of the library the code depends on. To run the examples, [Bazel](https://www.bazel.build/) must be installed and included in your PATH. Each of the different examples can be run using:

```bash
bazel run [example-name]
```

Where `[example-name]` refers to the folder of the example you wish to run.

The goal of this section is to show the user some of the library in action as well as acting as a point of reference for getting started with their own experiments using the software.

## Width 3

The width 4 example shows the generation of the shortest width 3 word using random generation. This word can be seen as follows.

```
(((())(((())))(())))(((())(((())))(())))
```

## Width 4

The width 4 example shows the verification that one of the currently known width 4 words with `n = 170` actually has width 4. This is performed using the predicate.

## Visualise Re-Pairing

The visualise re-pairing program is used to visualise the re-pairing of the Hardest word obtainable from the first width 3 word. This word is the subject of the dervied strategy and its full re-pairing is shown upon running the program as follows:

```
(((())((()))(())))(((())(((())))(())))
(((())((()))(  )))(((())(((())))(())))
(((())((()))    ))(((())(((())))(())))
 ((())((())     ))(((())(((())))(())))
  (())((()      ))(((())(((())))(())))
  (())((        ))(((())(((())))(())))
  (())(          )(((())(((())))(())))
  (())            (((())(((())))(())))
   ()             (((())(((())))(())))
                  (((())(((())))(())))
                   ((())(((())))(()))
                    (())(((())))(())
                     ( )(((())))(())
                        (((())))(())
                        (((())))(  )
                        (((())))
                         ((()))
                          (())
                           ()
```

## Random Generation

Each of the different random generation methods are included that simply generate a word of `n = 30`. This value can be easily changed in the source code if a different length is required. This value is then printed to the console for viewing. All types exist including `Random Hard`, `Random Symmetric`, `Random Symmetric Hard`, and `Random Uniform`.
