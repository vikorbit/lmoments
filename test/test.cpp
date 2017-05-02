#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <functional>

#include "lmoments.hpp"

TEST_CASE( "Binomial coefficient are computed", "[binomial]" ) {
    REQUIRE( lmoments::binomial_coefficient(0, 0) == 1 );
    REQUIRE( lmoments::binomial_coefficient(0, 1) == 0 );
    REQUIRE( lmoments::binomial_coefficient(1, 0) == 1 );
    REQUIRE( lmoments::binomial_coefficient(10, 5) == 252 );
    REQUIRE( lmoments::binomial_coefficient(10000000, 200) == 67602962522481855 );
}

TEST_CASE( "L-moments are computed", "[lmoments]" ) {

    SECTION( "test for empty vector" ) {
        std::vector<int> data;
        REQUIRE_THROWS( lmoments::l1( data.begin(), data.begin() ) );
        REQUIRE_THROWS( lmoments::l2( data.begin(), data.begin() ) );
        REQUIRE_THROWS( lmoments::l3( data.begin(), data.begin() ) );
        REQUIRE_THROWS( lmoments::l4( data.begin(), data.begin() ) );

        REQUIRE_THROWS( lmoments::l1( data.end(), data.end() ) );
        REQUIRE_THROWS( lmoments::l2( data.end(), data.end() ) );
        REQUIRE_THROWS( lmoments::l3( data.end(), data.end() ) );
        REQUIRE_THROWS( lmoments::l4( data.end(), data.end() ) );
    }

    SECTION( "test for vector of 0" ) {
        std::vector<int> data( 1000, 0 );
        REQUIRE( lmoments::l1( data.begin(), data.end() ) == 0.0l );
        REQUIRE( lmoments::l2( data.begin(), data.end() ) == 0.0l );
        REQUIRE( lmoments::l3( data.begin(), data.end() ) == 0.0l );
        REQUIRE( lmoments::l4( data.begin(), data.end() ) == 0.0l );
    }

    SECTION( "test for vector of 1" ) {
        std::vector<int> data( 1000, 1 );
        REQUIRE( lmoments::l1( data.begin(), data.end() ) == 1.0l );
        REQUIRE( lmoments::l2( data.begin(), data.end() ) == 0.0l );
        REQUIRE( lmoments::l3( data.begin(), data.end() ) == 0.0l );
        REQUIRE( lmoments::l4( data.begin(), data.end() ) == 0.0l );
    }

    SECTION( "test for vector of -1" ) {
        std::vector<int> data( 1000, -1 );
        REQUIRE( lmoments::l1( data.begin(), data.end() ) == -1.0l );
        REQUIRE( lmoments::l2( data.begin(), data.end() ) == 0.0l );
        REQUIRE( lmoments::l3( data.begin(), data.end() ) == 0.0l );
        REQUIRE( lmoments::l4( data.begin(), data.end() ) == 0.0l );
    }

    SECTION( "test for uniform distribution" ) {
        std::random_device rd;
        std::mt19937 mt( rd() );
        std::uniform_int_distribution<> uniform_dist( 0, 10 );

        std::vector<int> uniform_data( 10000 );
        std::generate( uniform_data.begin(), uniform_data.end(), std::bind( uniform_dist, std::ref( mt ) ) );

        Approx approx_l1 = Approx(5).epsilon(0.1);
        Approx approx_l2 = Approx(1.7).epsilon(0.1);
        Approx approx_t3 = Approx(0).margin(0.1);
        Approx approx_t4 = Approx(0).margin(0.1);

        double l1 = lmoments::l1( uniform_data.begin(), uniform_data.end() );
        double l2 = lmoments::l2( uniform_data.begin(), uniform_data.end() );
        double l3 = lmoments::l3( uniform_data.begin(), uniform_data.end() );
        double l4 = lmoments::l4( uniform_data.begin(), uniform_data.end() );
        double t3 = l3 / l2;
        double t4 = l4 / l2;

        REQUIRE( l1 == approx_l1 );
        REQUIRE( l2 == approx_l2 );
        REQUIRE( t3 == approx_t3 );
        REQUIRE( t4 == approx_t4 );
    }

    SECTION( "test for normal distribution" ) {
        std::random_device rd;
        std::mt19937 mt( rd() );
        std::normal_distribution<> normal_dist( 5, 3 );
        std::vector<int> normal_data( 10000 );
        std::generate( normal_data.begin(), normal_data.end(), std::bind( normal_dist, std::ref( mt ) ) );

        Approx approx_l1 = Approx(5).epsilon(0.1);
        Approx approx_l2 = Approx(1.69).epsilon(0.1);
        Approx approx_t3 = Approx(0).margin(0.1);
        Approx approx_t4 = Approx(0.12).margin(0.1);

        double l1 = lmoments::l1( normal_data.begin(), normal_data.end() );
        double l2 = lmoments::l2( normal_data.begin(), normal_data.end() );
        double l3 = lmoments::l3( normal_data.begin(), normal_data.end() );
        double l4 = lmoments::l4( normal_data.begin(), normal_data.end() );
        double t3 = l3 / l2;
        double t4 = l4 / l2;

        REQUIRE( l1 == approx_l1 );
        REQUIRE( l2 == approx_l2 );
        REQUIRE( t3 == approx_t3 );
        REQUIRE( t4 == approx_t4 );
    }
}