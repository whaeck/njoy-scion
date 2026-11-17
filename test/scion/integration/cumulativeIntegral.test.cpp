// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/cumulativeIntegral.hpp"
#include "scion/integration/LinearLinear.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "integrate" ) {

  integration::LinearLinear integrator;

  GIVEN( "tabulated x and y values" ) {

    std::vector< double > x = { 1., 2., 3, 4, 5. };
    std::vector< double > y = { 5., 4., 3, 2, 1. };

    WHEN( "calculating the cumulative integral over the x values" ) {

      std::vector< double > c = { 0., 0., 0., 0., 0. };

      THEN( "the integration is performed correctly using iterators" ) {

        // over the entire table
        integration::cumulativeIntegral( x.begin(), x.end(), y.begin(), c.begin(), integrator );
        CHECK_THAT(  0. , WithinRel( c[0] ) );
        CHECK_THAT(  4.5, WithinRel( c[1] ) );
        CHECK_THAT(  8. , WithinRel( c[2] ) );
        CHECK_THAT( 10.5, WithinRel( c[3] ) );
        CHECK_THAT( 12. , WithinRel( c[4] ) );

        // reset the cumulative integral
        c = { 0., 0., 0., 0., 0. };

        // over the first 2 panels of the table
        integration::cumulativeIntegral( x.begin(), x.begin() + 3, y.begin(), c.begin(), integrator );
        CHECK_THAT(  0. , WithinRel( c[0] ) );
        CHECK_THAT(  4.5, WithinRel( c[1] ) );
        CHECK_THAT(  8. , WithinRel( c[2] ) );
        CHECK_THAT(  0. , WithinRel( c[3] ) );
        CHECK_THAT(  0. , WithinRel( c[4] ) );

        // reset the cumulative integral
        c = { 0., 4.5, 0., 0., 0. };

        // over the middle 2 panels of the table
        integration::cumulativeIntegral( x.begin() + 1, x.begin() + 4, y.begin() + 1, c.begin() + 1, integrator );
        CHECK_THAT(  0. , WithinRel( c[0] ) );
        CHECK_THAT(  4.5, WithinRel( c[1] ) );
        CHECK_THAT(  8. , WithinRel( c[2] ) );
        CHECK_THAT( 10.5, WithinRel( c[3] ) );
        CHECK_THAT(  0. , WithinRel( c[4] ) );

        // reset the cumulative integral
        c = { 0., 4.5, 8., 0., 0. };

        // over the last 2 panels of the table
        integration::cumulativeIntegral( x.begin() + 2, x.end(), y.begin() + 2, c.begin() + 2, integrator );
        CHECK_THAT(  0. , WithinRel( c[0] ) );
        CHECK_THAT(  4.5, WithinRel( c[1] ) );
        CHECK_THAT(  8. , WithinRel( c[2] ) );
        CHECK_THAT( 10.5, WithinRel( c[3] ) );
        CHECK_THAT( 12. , WithinRel( c[4] ) );
      } // THEN

      THEN( "the integration is performed correctly using ranges" ) {

        // over the entire table
        integration::cumulativeIntegral( x, y, c.begin(), integrator );
        CHECK_THAT(  0. , WithinRel( c[0] ) );
        CHECK_THAT(  4.5, WithinRel( c[1] ) );
        CHECK_THAT(  8. , WithinRel( c[2] ) );
        CHECK_THAT( 10.5, WithinRel( c[3] ) );
        CHECK_THAT( 12. , WithinRel( c[4] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
