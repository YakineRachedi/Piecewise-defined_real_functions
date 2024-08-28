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

The function `PiecewiseFn<Segment, Affine_Fn<double>, double> make_tent_function(double a, double b, double h)` allows us to create an object from two pieces and a default value.

### Second example :

We now want to code functions $f : \mathbb{Z} \to \mathbb{R}$ that are non-zero only on a finite set. To achieve this, we will consider sets $A_i$ on which the function $f$ is constant and equal to $c_i$, while $f$ is zero outside the $A_i$. 

It is important to note that a constant function is an affine function with a slope $a$ equal to zero.

The function 
```cpp
PiecewiseFn<std::set<int>, Affine_Fn<double>> make_int_fn_from_file(std::istream &is);
``` 

takes as an argument a file structured as follows:

- On the first line, we have the number of pieces.
- Then each piece is represented as:
  - The first line contains the size of $A_i$ and the associated value $c_i$.
  - Then, one line for each integer in $A_i$.

This function returns the correct piecewise-defined function.

_Note:_ 

My compiler is a bit old, from 2016, and I didn't have time to update it. I searched online and found that std::set<E> containers did not have a contains method before C++20; after that, they introduced the method 
```cpp
bool std::set<E>::contains(const E &) const
```

I had to specialize the ```test_if_contains``` template and based it on the <algorithm> library using the ```std::find``` function (or possibly ```std::find_if```).

### Third example : Linear Forms and Cuboids

In this example now  we want to make a slightly more subtle construction. The space $E$ is now replaced by $\mathbb{R}^d$ and the sets $A_i$ are cuboids, i.e., Cartesian products of segments: 
$$
A_i = [u_1, v_1] \times \dots \times [u_d, v_d].
$$

The functions $f_i$ considered are linear forms on $\mathbb{R}^d$, i.e., functions 

$$
f(x) = \sum_{i=1}^{d} \alpha_i x_i.
$$

In this case,  we need a class template to code linear forms on an arbitrary space $K^d$ where $K$ is any field.

A cuboid in $ \mathbb{R}^d $ is coded using the type `vector<Segment>` and a point in $ \mathbb{R}^d $ is represented by the type `vector<double>`. However, as is currently implemented, there is no adequate `contains` method to make `test_if_contains` work. In this case, a partial specialization of the template is needed for the following scenario: we will check if each coordinate belongs to the corresponding segment in the same direction.

##### _Structure of `data3.txt`:_
- The first line contains the number of pieces.
- For each piece:
  - The next three lines define the segments of a cuboid in dimension 3.
  - The following three lines represent the coefficients of a linear form on $ \mathbb{R}^3 $.

We will read this file and define a `PiecewiseFn<std::vector<Segment>, LinearForm<double, 3>>` with a default value of zero. Then, we will display some values to ensure that this program works correctly.

Note: in file test3.cpp, we use different implementations of the operator>> (with struct Segment, class LinearForm, and the <fstream> library), and it is up to the compiler to choose one of them.