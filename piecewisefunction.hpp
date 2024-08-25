#ifndef PIECE_WISE_FCT_INCLUDED
#define PIECE_WISE_FCT_INCLUDED

#include <iostream>
#include <vector>
#include <utility>


template <typename Domain, typename Function> class PiecewiseFn;
template <class Domain, class Value> bool test_if_contains(const Domain & A, const Value & v);


template <class Domain, class Function>
    class PiecewiseFn{
        private :
            std::vector<std::pair<Domain, Function> pieces; // Each pair corresponds to (A_i, f_i)
            double default_v; // Corresponds to the default value y_0
        public :
            PiecewiseFn(double y0 = 0);
            void add_piece(const Domain & A, const Function & f);
            template <class Argument> double operator() (const Argument & x) const;
    };

#endif