# Mathematical description :
Let $E$ be a set. Let $(A_i)_{1 \leq i \leq n}$ be a finite sequence of disjoint subsets of $E$, and let $(f_i)_{1 \leq i \leq n}$ be a finite sequence of real-valued functions $f_i: A_i \to \mathbb{R}$. Let $y_0 \in \mathbb{R}$ be a fixed real number. We can then define a piecewise function $F: E \to \mathbb{R}$ on $E$ as follows:

$$
F(x) = 
\begin{cases} 
f_i(x) & \text{if } x \in A_i \text{ for some } i, \\
y_0 & \text{if } x \notin A_i \text{ for all } i.
\end{cases}
$$

# Implementation C++ :

The idea is to introduce a class template where `Domain` is an arbitrary type intended to describe the sets $A_i$ and `Function` is an arbitrary type intended to describe the functions $f_i$.

```cpp
template <typename Domain, typename Function> class PiecewiseFn;
```

To make the class as general and flexible as possible, i also introduce a function template:

```cpp
template<class Domain,class Value>
    bool test_if_contains(const Domain & A, const Value & v);
```

This function determines whether the value $v \in E$ belongs to a given subset $A \subset E$.

### Methods :

The `add_pieces` method adds a new pair $(A_i, f_i)$. We still assume that the sets $A_i$ are disjoint.

### First example :

The class `Affine_fn` allows encoding functions of the type f(x)=ax+b in an arbitrary field (real, complex, integers).

We need to define a function `tente` with parameters $(a, b, h)$ using the `Segment` structure and the `Affine_Fn` class such that:
$$
F(x) = 
\begin{cases} 
0 & \text{if } x < a \\
\frac{2h}{b + a}(x - a) & \text{if } a \leq x \leq \frac{a + b}{2} \\
\frac{2h}{b + a}(b - x) & \text{if } \frac{a + b}{2} \leq x \leq b \\
0 & \text{if } x > b
\end{cases}
$$
This will allow us to perform an initial test.
