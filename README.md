lmoments
========

L-moments are a sequence of statistics used to summarize the shape of a probability distribution. The lmoments is a C++ library that allows calculate the first four [L-moments](https://en.wikipedia.org/wiki/L-moment)

Example
-------

```C++
#include <iostream>

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

    return 0;
}
```

Building and running tests
--------------------------

### Requirements
  * SCons ([http://scons.org/](http://scons.org/))

### 1. Run SCons
    scons -j 2

### 2. Run Test
    cd test
    test