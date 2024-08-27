#ifndef LINEARFORM_TEMPLATES
#define LINEARFORM_TEMPLATES


#include <iostream>
#include <vector>
#include <fstream>

template <class Field,int d> class LinearForm;
template <class Field,int d> std::istream & operator>> ( std::istream & is, LinearForm<Field,d> & f);

template <class Field,int d>
    class LinearForm {
        private:
            std::vector<Field> coeff;
        public:
            // Constructors :
            LinearForm() : coeff(d,0) {}
            LinearForm(const std::vector<Field> & input) : coeff(input) {}
            
            // Methods :
            Field operator () (const std::vector<Field> & v) const;  // this operator calculates the linear form f(x)
    };

template <class Field,int d>
    Field LinearForm<Field,d>::operator () (const std::vector<Field> & input) const {
        Field result = 0;
        for(int i = 0; i < d; i++){
            result += coeff[i] * input[i];
        }
        return result;
    }
#endif
