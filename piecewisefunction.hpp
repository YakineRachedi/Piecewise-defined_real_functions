#ifndef PIECE_WISE_FCT_INCLUDED
#define PIECE_WISE_FCT_INCLUDED

#include <iostream>
#include <vector>
#include <utility>


template <typename Domain, typename Function> class PiecewiseFn;
template <class Domain, class Value> bool test_if_contains(const Domain & A, const Value & v);

template <class Domain, class Value>
    bool test_if_contains(const Domain & D, const Value & v) {
        return D.contains(v);
}
template <class Domain, class Function>
    class PiecewiseFn{
        private :
            std::vector<std::pair<Domain, Function> > pieces; // Each pair corresponds to (A_i, f_i)
            double default_v; // Corresponds to the default value y_0
        public :
            // constructors :
            PiecewiseFn(double y0 = 0) : pieces(), default_v(y0) {} // Here in pieces, i use the default constructor of the vector class
            
            // Getters :
            int get_pieces() const {return this->pieces.size();}
            double default_value() const {return this->default_v;}
            // Methods :
            void add_piece(const Domain & A, const Function & f);
            template <class Argument> double operator() (const Argument & x) const;

    };

/*================================================Implementation of the methods==========================================================*/

template <class Domain, class Function> 
    void PiecewiseFn<Domain, Function>::add_piece(const Domain & A, const Function & f){
        pieces.push_back(std::make_pair(A,f));
    }

template <class Domain, class Function>
    template <class Argument> 
        double PiecewiseFn<Domain, Function>::operator() (const Argument & x) const{
            double Result = default_v;
            for(const auto & p : pieces){
                if( test_if_contains(p.first,x) ){
                    Result = p.second(x);
                    break;
                }
            }
            return Result;
        }
#endif