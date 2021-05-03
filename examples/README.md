# Examples

This folder contains some examples that utilise the library. The library is imported using the [Bazel](https://www.bazel.build/) WORKSPACE file, and then [Bazel](https://www.bazel.build/) is used in each directory to set the library components on which the code depends. To run the examples, [Bazel](https://www.bazel.build/) must be installed and included in your PATH. Each example is runnable using the following command from within the `examples` directory.

```bash
bazel run [example-name]
```

Where `[example-name]` refers to the folder of the example you wish to run.

This section demonstrates portions of the library's capabilities and acts as a reference point for those wishing to begin their experiments.

## Width 3

The width 4 example shows the generation of the shortest width 3 word using random generation. This word can be seen as follows.

```
(((())(((())))(())))(((())(((())))(())))
```

## Width 4

The width 4 example shows the verification that one of the currently known width 4 words with `n = 170` actually has width 4. This verification is performed using the predicate.

## Visualise Re-Pairing

The visualise re-pairing program is used to visualise the re-pairing of the Hardest word obtainable from the first width 3 word. This word is the subject of the derived strategy, and its full re-pairing is shown upon running the program as follows:

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

Each of the different random generation methods has an example that generates a word of `n = 30`; one can change this length in the source code if required. This value is printed to the console for viewing. All types have examples, including: `Random Hard`, `Random Symmetric`, `Random Symmetric Hard`, and `Random Uniform` generation.
