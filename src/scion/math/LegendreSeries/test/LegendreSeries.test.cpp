#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/LegendreSeries.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using LegendreSeries = math::LegendreSeries< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;

SCENARIO( "LegendreSeries" ) {

  GIVEN( "Legendre coefficients for an expansion" ) {

    WHEN( "the data is given explicitly" ) {

      // the 3rd order Legendre series was designed to have 3 real roots: 1, 2 and 4
      // the 3rd order polynomial series equivalent to this is the same as the
      // one in the PolynomialSeries example

      std::vector< double > coefficients = { -31./3., 73./5., -14./3., 2./5. };

      LegendreSeries< double > chunk( std::move( coefficients ) );

      THEN( "a LegendreSeries can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.order() );

        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -10.33333333 == Approx( chunk.coefficients()[0] ) );
        CHECK(  14.6        == Approx( chunk.coefficients()[1] ) );
        CHECK(  -4.66666667 == Approx( chunk.coefficients()[2] ) );
        CHECK(   0.4        == Approx( chunk.coefficients()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LegendreSeries can be evaluated" ) {

        CHECK(  -8.0 == Approx( chunk.evaluate(  0. ) ) );
        CHECK(   0.0 == Approx( chunk.evaluate(  1. ) ) );
        CHECK( -30.0 == Approx( chunk.evaluate( -1. ) ) );

        CHECK(  -8.0 == Approx( chunk(  0. ) ) );
        CHECK(   0.0 == Approx( chunk(  1. ) ) );
        CHECK( -30.0 == Approx( chunk( -1. ) ) );
      } // THEN

      THEN( "a LegendreSeries can be differentiated" ) {

        LegendreSeries< double > first = chunk.derivative();
        LegendreSeries< double > second = first.derivative();
        LegendreSeries< double > third = second.derivative();
        LegendreSeries< double > fourth = third.derivative();

        CHECK( 2 == first.order() );
        CHECK( 3 == first.coefficients().size() );
        CHECK(  15. == Approx( first.coefficients()[0] ) );
        CHECK( -14. == Approx( first.coefficients()[1] ) );
        CHECK(   2. == Approx( first.coefficients()[2] ) );

        CHECK( 1 == second.order() );
        CHECK( 2 == second.coefficients().size() );
        CHECK( -14. == Approx( second.coefficients()[0] ) );
        CHECK(   6. == Approx( second.coefficients()[1] ) );

        CHECK( 0 == third.order() );
        CHECK( 1 == third.coefficients().size() );
        CHECK( 6. == Approx( third.coefficients()[0] ) );

        CHECK( 0 == fourth.order() );
        CHECK( 1 == fourth.coefficients().size() );
        CHECK( 0. == Approx( fourth.coefficients()[0] ) );
      } // THEN


      THEN( "a LegendreSeries can be integrated" ) {

        LegendreSeries< double > primitive = chunk.primitive();

        CHECK( 4 == primitive.order() );
        CHECK( 5 == primitive.coefficients().size() );
        CHECK( -15.2 == Approx( primitive.coefficients()[0] ) );
        CHECK( -9.4 == Approx( primitive.coefficients()[1] ) );
        CHECK(  4.809523809523809 == Approx( primitive.coefficients()[2] ) );
        CHECK( -0.933333333333333 == Approx( primitive.coefficients()[3] ) );
        CHECK(  0.057142857142857 == Approx( primitive.coefficients()[4] ) );
      } // THEN

      THEN( "roots can be calculated" ) {

        std::vector< double > roots = chunk.roots();

        CHECK( 3 == roots.size() );
        CHECK( 1.0 == Approx( roots[0] ) );
        CHECK( 2.0 == Approx( roots[1] ) );
        CHECK( 4.0 == Approx( roots[2] ) );

        roots = chunk.roots( -8. );

        CHECK( 1 == roots.size() );
        CHECK(  0.0 == Approx( roots[0] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the coefficient vector is empty" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreSeries< double >( {} ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
