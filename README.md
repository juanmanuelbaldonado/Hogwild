
## Hogwild! GLM

An C++ implementation of a Generalized Linear Model using Hogwild! [1] algorithm and
feature hashing.

### Input File structure

The input files should be in the svmlight format [2].

```
<line> .=. <target> <feature>:<value> <feature>:<value> ... <feature>:<value> # <info>
<target> .=. +1 | -1 | 0 | <float> 
<feature> .=. <integer> | "qid"
<value> .=. <float>
<info> .=. <string>
```

### Options

```
Allowed options:
  --help                       produce help message
  --train-files arg            Training dataset files
  --test-files arg             Testing dataset files
  --regression arg (=logistic) Testing dataset files
  --eta arg (=0.01)            learning rate
  --lambda arg (=0)            L2 regularization coefficient
  --epochs arg (=1)            number of epochs
  --nworkers arg (=1)          number of workers
  --bits arg (=22)             Size in bits of the parameter vector
```

### Build

To build the project do:

```
1. mkdir build
2. cd build
3. cmake ..
4. make
```

and then run it

```
./bin/main
```

# References

[1] HOGWILD!: A Lock-Free Approach to Parallelizing Stochastic Gradient Descent

[2] http://svmlight.joachims.org
