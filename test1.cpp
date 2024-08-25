#include "piecewisefunction.hpp"

PiecewiseFn<Segment,Affine_fn<double>> make_tent_function(double a, double b, double h) {
    PiecewiseFn<Segment,Affine_fn<double>> result;
    Segment S1(a,(a+b)/2);
    Segment S2((a+b)/2,b);
    result.add_piece(S1,Affine_fn<double>(((2*h)/(b+a)),-a * ((2*h)/(b+a)) ));
    result.add_piece(S2,Affine_fn<double>(-((2*h)/(b+a)) ,b * ((2*h)/(b+a)) ));
    /*
    The method add_piece takes a Function as its second argument, 
        which is why i add an object of the Affine_fn class with real (<double>) values.
    */
    return result;
}

int main() {
    auto Tent = make_tent_function(-1.,3.,5.);
    for(double x=-2.; x<4. ; x += 0.25 ) {
        std::cout << x << ":\t" << Tent(x) << "\n"; 
    } 
    return 0;
}
