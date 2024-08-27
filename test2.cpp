#include "piecewisefunction.hpp"
#include <fstream>

PiecewiseFn<std::set<int>, Affine_fn<double>> 
        make_int_fn_from_file(std::istream & is) {
            unsigned nb_of_pieces; // Number of pieces in the piecewise function
            is >> nb_of_pieces; // Read the number of pieces
            PiecewiseFn<std::set<int>, Affine_fn<double>> result;
            if (is.fail()) {
                std::cerr << "Failed to read nb_of_pieces. Check the file format.\n";
                return result;
            }
            for (int i = 0; i < nb_of_pieces; i++) {
                std::set<int> Ai; // Set to store the domain of the current piece
                int size_of_Ai = 0; // Number of elements in the current set Ai
                double constant_value_ci; // Constant value associated with this piece (f(x) = c_i)

                // Read the size of Ai and the constant value c_i
                is >> size_of_Ai >> constant_value_ci;
                // Read each integer value and add it to the set Ai
                for (int j = 0; j < size_of_Ai; j++) {
                    int value;
                    is >> value;
                    //std::cout << value << "\n";
                    Ai.insert(value);
                }

                // Define the affine function as a constant function f(x) = c_i
                Affine_fn<double> my_fct(0, constant_value_ci); // The slope is 0 because the function is constant

                // Add the piece (Ai, f(x)) to the piecewise function
                result.add_piece(Ai, my_fct);
            }

            return result;
        }
int main()  {
    std::cout << "----- Second example -----\n";
    auto input = std::ifstream("data2.txt");
    auto f = make_int_fn_from_file(input);
    for (int i = 0; i < 20; i++)
    {
        std::cout << i << ":\t" << f(i) << "\n";
    }
    
    return 0;
}
