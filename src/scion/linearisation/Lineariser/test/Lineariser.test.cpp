#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// what we are testing
#include "scion/linearisation/Lineariser.hpp"

// other includes
#include <cmath>
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/MidpointSplit.hpp"

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;

SCENARIO( "Lineariser" ) {

  GIVEN( "valid data for linearisation" ) {

    // y = f(x) = exp(x)
    auto functor = [] ( double x ) { return std::exp( x ); };

    // split a panel using the midpoint
    linearisation::MidpointSplit< double > split;

    // convergence tolerance < 25%
    linearisation::ToleranceConvergence< double > convergence( 0.25 );

    WHEN( "the minimal grid is used" ) {

      std::vector< double > grid = { 0., 10. };

      THEN( "the function can be linearised" ) {

        std::vector< double > x;
        std::vector< double > y;

        linearisation::Lineariser linearise( x, y );
        linearise( grid.begin(), grid.end(), functor, convergence, split );

        CHECK( 9 == x.size() );
        CHECK( 9 == y.size() );

        CHECK(  0.0   == Approx( x[0] ) );
        CHECK(  1.25  == Approx( x[1] ) );
        CHECK(  2.5   == Approx( x[2] ) );
        CHECK(  3.75  == Approx( x[3] ) );
        CHECK(  5.0   == Approx( x[4] ) );
        CHECK(  6.25  == Approx( x[5] ) );
        CHECK(  7.5   == Approx( x[6] ) );
        CHECK(  8.75  == Approx( x[7] ) );
        CHECK( 10.0   == Approx( x[8] ) );

        CHECK( std::exp( 0.0  ) == Approx( y[0] ) );
        CHECK( std::exp( 1.25 ) == Approx( y[1] ) );
        CHECK( std::exp( 2.5  ) == Approx( y[2] ) );
        CHECK( std::exp( 3.75 ) == Approx( y[3] ) );
        CHECK( std::exp( 5.0  ) == Approx( y[4] ) );
        CHECK( std::exp( 6.25 ) == Approx( y[5] ) );
        CHECK( std::exp( 7.5  ) == Approx( y[6] ) );
        CHECK( std::exp( 8.75 ) == Approx( y[7] ) );
        CHECK( std::exp(10.0  ) == Approx( y[8] ) );
      } // THEN
    } // WHEN

    WHEN( "an extended grid is used" ) {

      std::vector< double > grid = { 0., 2., 4., 6., 8., 10. };

      THEN( "the function can be linearised" ) {

        std::vector< double > x;
        std::vector< double > y;

        linearisation::Lineariser linearise( x, y );
        linearise( grid.begin(), grid.end(), functor, convergence, split );

        CHECK( 11 == x.size() );
        CHECK( 11 == y.size() );

        CHECK(  0.0 == Approx( x[ 0] ) );
        CHECK(  1.0 == Approx( x[ 1] ) );
        CHECK(  2.0 == Approx( x[ 2] ) );
        CHECK(  3.0 == Approx( x[ 3] ) );
        CHECK(  4.0 == Approx( x[ 4] ) );
        CHECK(  5.0 == Approx( x[ 5] ) );
        CHECK(  6.0 == Approx( x[ 6] ) );
        CHECK(  7.0 == Approx( x[ 7] ) );
        CHECK(  8.0 == Approx( x[ 8] ) );
        CHECK(  9.0 == Approx( x[ 9] ) );
        CHECK( 10.0 == Approx( x[10] ) );

        CHECK( 1.0              == Approx( y[ 0] ) );
        CHECK( std::exp(  1.0 ) == Approx( y[ 1] ) );
        CHECK( std::exp(  2.0 ) == Approx( y[ 2] ) );
        CHECK( std::exp(  3.0 ) == Approx( y[ 3] ) );
        CHECK( std::exp(  4.0 ) == Approx( y[ 4] ) );
        CHECK( std::exp(  5.0 ) == Approx( y[ 5] ) );
        CHECK( std::exp(  6.0 ) == Approx( y[ 6] ) );
        CHECK( std::exp(  7.0 ) == Approx( y[ 7] ) );
        CHECK( std::exp(  8.0 ) == Approx( y[ 8] ) );
        CHECK( std::exp(  9.0 ) == Approx( y[ 9] ) );
        CHECK( std::exp( 10.0 ) == Approx( y[10] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
