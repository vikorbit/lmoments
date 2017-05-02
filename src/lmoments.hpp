#pragma once

#include <algorithm>

namespace lmoments {

    int64_t binomial_coefficient(size_t n, size_t k) {
        // special cases
        if( k > n ) {
            return 0;
        }

        // symmetry
        if( k > n - k ) {
            k = n - k;
        }
        if( k > n / 2 ) {
            k = n - k;
        }

        int64_t result = 1;
        for ( size_t c = 1; c <= k; c++ ) {
            result *= n--;
            result /= c;
        }

        return result;
    }

    template<typename _RandomAccessIterator>
    double l1(_RandomAccessIterator first, _RandomAccessIterator last)
    {
        if ( first == last ) {
            throw std::invalid_argument( "First and last iterators is equal" );
        }

        std::sort( first, last );
        size_t count = last - first;
        double l1 = 0.0l;
        while ( first != last ) {
            l1 += static_cast<double>( *first );
            first++;
        }
        l1 *= ( 1.0l / binomial_coefficient( count, 1 ) );

        return l1;
    }

    template<typename _RandomAccessIterator>
    double l2(_RandomAccessIterator first, _RandomAccessIterator last)
    {
        if ( first == last ) {
            throw std::invalid_argument( "First and last iterators is equal" );
        }

        std::sort( first, last );
        size_t count = last - first;
        double l2 = 0.0l;

        size_t i = 1;
        while ( first != last ) {
            l2 += ( ( binomial_coefficient( i - 1, 1 ) - binomial_coefficient( count - i, 1 ) ) * static_cast<double>( *first ) );
            i++;
            first++;
        }
        l2 *= ( 1.0l / ( binomial_coefficient( count, 2 ) * 2.0l ) );

        return l2;
    }

    template<typename _RandomAccessIterator>
    double l3(_RandomAccessIterator first, _RandomAccessIterator last)
    {
        if ( first == last ) {
            throw std::invalid_argument( "First and last iterators is equal" );
        }

        std::sort( first, last );
        size_t count = last - first;
        double l3 = 0.0l;

        size_t i = 1;
        while ( first != last ) {
            l3 += ( ( binomial_coefficient( i - 1, 2 ) - 2 * ( binomial_coefficient( i - 1, 1 ) * binomial_coefficient( count - i, 1 ) ) + 
                    binomial_coefficient( count - i, 2 ) ) * static_cast<double>( *first ) );
            i++;
            first++;
        }
        l3 *= ( 1.0l / ( binomial_coefficient( count, 3 ) * 3.0l ) );

        return l3;
    }

    template<typename _RandomAccessIterator>
    double l4(_RandomAccessIterator first, _RandomAccessIterator last)
    {
        if ( first == last ) {
            throw std::invalid_argument( "First and last iterators is equal" );
        }

        std::sort( first, last );
        size_t count = last - first;
        double l4 = 0.0l;

        size_t i = 1;
        while ( first != last ) {
            l4 += ( ( binomial_coefficient( i - 1, 3 ) - 3 * ( binomial_coefficient( i - 1, 2 ) * binomial_coefficient( count - i, 1 ) ) +
                    3 * ( binomial_coefficient( i - 1, 1 ) * binomial_coefficient( count - i, 2 ) ) - binomial_coefficient( count - i, 3 ) ) 
                    * static_cast<double>( *first ) );
            i++;
            first++;
        }

        l4 *= ( 1.0l / ( binomial_coefficient( count, 4 ) * 4.0l ) );

        return l4;
    }

}
