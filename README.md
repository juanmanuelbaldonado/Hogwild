
## Hogwild! GLM

An C++ implementation of a Generalized Linear Model using Hogwild! algorithm.


### Input File structure

The input file should be comprised of a set of rows, one for each example. Each row should follow the grammar:

    ```
    Start -> Label Attributes
    Attributes -> AttributeName:Value Attributes | AttributeName Attributes
    Label -> <integer> | <string> | <double>
    AttributeName -> <string>
    AttributeValue -> <integer> | <string>
    ```

# References

[1] HOGWILD!: A Lock-Free Approach to Parallelizing Stochastic Gradient Descent

2. Slow Learners are Fast
    ```
    We propose the following two variants:

    I) Several processing cores perform stochastic gradient descent independently of each other while sharing a common parameter vector which is updated asynchronously. This allows us to accelerate computationally inten- sive problems whenever gradient computations are relatively expensive.

    II) We assume that we have linear function classes where parts of the function can be computed independently on several cores. Subsequently the results are combined and the combination is then used for a descent step.
    ```

3. Zinkevich: Parallelized Stochastic Gradient Descent.
    ```
    The key algorithmic difference to [7] is that the batch solver of the inner loop is replaced by a stochastic gradient descent algorithm which digests not a fixed fraction of data but rather a random fixed subset of data. This means that if we process `T` instances per machine, each processor ends up seeing `T` of the data which is likely to exceed 1 .
    ```