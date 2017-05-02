#include <iostream>
#include <functional>

#include "lmoments.hpp"

int main( int argc, char **argv ) {
    
    std::random_device rd;
    std::mt19937 mt( rd() );
    std::uniform_int_distribution<> uniform_dist( 0, 10 );

    std::vector<int> uniform_data( 10000 );
    std::generate( uniform_data.begin(), uniform_data.end(), std::bind( uniform_dist, std::ref( mt ) ) );

    double l1 = lmoments::l1( uniform_data.begin(), uniform_data.end() );
    double l2 = lmoments::l2( uniform_data.begin(), uniform_data.end() );
    double l3 = lmoments::l3( uniform_data.begin(), uniform_data.end() );
    double l4 = lmoments::l4( uniform_data.begin(), uniform_data.end() );

    std::cout << "L-statistics for uniform distribution (0, 10) \n";
    std::cout << "  L-moments:\n";
    std::cout << "    l1 (L-mean): " << l1 << "\n";
    std::cout << "    l2 (L-scale): " << l2 << "\n";
    std::cout << "    l3: " << l3 << "\n";
    std::cout << "    l4: " << l4 << "\n";
    std::cout << "  L-moment ratios:\n";
    std::cout << "    L-variation: " << l2 / l1 << "\n";
    std::cout << "    L-skewness: " << l3 / l2 << "\n";
    std::cout << "    L_kurtosis: " << l4 / l2 << "\n\n";

    std::normal_distribution<> normal_dist( 10, 3 );
    std::vector<int> normal_data( 10000 );
    std::generate( normal_data.begin(), normal_data.end(), std::bind( normal_dist, std::ref( mt ) ) );

    l1 = lmoments::l1( normal_data.begin(), normal_data.end() );
    l2 = lmoments::l2( normal_data.begin(), normal_data.end() );
    l3 = lmoments::l3( normal_data.begin(), normal_data.end() );
    l4 = lmoments::l4( normal_data.begin(), normal_data.end() );

    std::cout << "L-statistics for normal distribution (10, 3)\n";
    std::cout << "  L-moments:\n";
    std::cout << "    l1 (L-mean): " << l1 << "\n";
    std::cout << "    l2 (L-scale): " << l2 << "\n";
    std::cout << "    l3: " << l3 << "\n";
    std::cout << "    l4: " << l4 << "\n";
    std::cout << "  L-moment ratios:\n";
    std::cout << "    L-variation: " << l2 / l1 << "\n";
    std::cout << "    L-skewness: " << l3 / l2 << "\n";
    std::cout << "    L_kurtosis: " << l4 / l2 << "\n";

    return 0;
}