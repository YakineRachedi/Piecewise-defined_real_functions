#include "linearform.hpp"
#include "piecewisefunction.hpp"
using namespace std;

/* . . . Specializing template . . .*/
template <>
    bool test_if_contains <> (const vector<Segment> & cuboid, const vector<double> & point){
        for(int i = 0; i < cuboid.size(); i++){
            if( !(cuboid[i].contains(point[i])) ){
                return false;
            }
        }
        return true;
    }

int main() {
    const int dimension = 3;
    PiecewiseFn< vector<Segment> , LinearForm <double,dimension> > my_function(0.);
    ifstream input("data3.txt");
    if (!input) {
    std::cerr << "Error opening the file.\n";
    }
    int nb_of_pieces;
    input >> nb_of_pieces;

    for(int i = 0; i < nb_of_pieces; i++){

        vector<Segment> cuboid(dimension);
        
        for(int k = 0; k < dimension; k++){
            input >> cuboid[k];
        }

        LinearForm<double, dimension> phi;
        input >> phi;
        my_function.add_piece(cuboid,phi);
    }
    input.close();

    // Testing

    vector<double> P1{0.3,0.1,0.4};
    vector<double> P2{1.5,0.5,3.5};
    vector<double> P3{2.3,1.7,3.6};
    
    cout <<  my_function(P1) << "\n" << my_function(P2) << "\n" << my_function(P3) << "\n"; 
    return 0;
}

