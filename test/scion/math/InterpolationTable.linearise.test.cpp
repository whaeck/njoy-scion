// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/InterpolationTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X >
using InterpolationTable = math::InterpolationTable< X, Y >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "InterpolationTable - histogram linearisation bug - November 14, 2026" ) {

  GIVEN( "data with a histogram region" ) {

    WHEN( "two regions have different y values at the shared boundary" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 1., 2., 5., 5. };
      std::vector< std::size_t > boundaries = { 2, 3 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::Histogram,
        InterpolationType::LinearLinear
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "the table gets linearised correctly" ) {

        // a jump will be inserted at the end of the histogram region
        auto linear = chunk.linearise();

        CHECK( 6 == linear.numberPoints() );
        CHECK( 3 == linear.numberRegions() );

        CHECK( 6 == linear.x().size() );
        CHECK( 6 == linear.y().size() );
        CHECK( 3 == linear.boundaries().size() );
        CHECK( 3 == linear.interpolants().size() );

        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 3 == linear.boundaries()[1] );
        CHECK( 5 == linear.boundaries()[2] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( 1., WithinRel( linear.x()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.x()[3] ) );
        CHECK_THAT( 3., WithinRel( linear.x()[4] ) );
        CHECK_THAT( 4., WithinRel( linear.x()[5] ) );

        CHECK_THAT( 1., WithinRel( linear.y()[0] ) );
        CHECK_THAT( 1., WithinRel( linear.y()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[2] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[3] ) );
        CHECK_THAT( 5., WithinRel( linear.y()[4] ) );
        CHECK_THAT( 5., WithinRel( linear.y()[5] ) );

        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN
    } // WHEN

    WHEN( "two regions have equal y values at the shared boundary" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 1., 2., 2., 5. };
      std::vector< std::size_t > boundaries = { 2, 3 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::Histogram,
        InterpolationType::LinearLinear
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "the table gets linearised correctly" ) {

        // no jump will be inserted at the end of the histogram region
        auto linear = chunk.linearise();

        CHECK( 5 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 5 == linear.x().size() );
        CHECK( 5 == linear.y().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );

        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 4 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( 1., WithinRel( linear.x()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.x()[3] ) );
        CHECK_THAT( 4., WithinRel( linear.x()[4] ) );

        CHECK_THAT( 1., WithinRel( linear.y()[0] ) );
        CHECK_THAT( 1., WithinRel( linear.y()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[2] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[3] ) );
        CHECK_THAT( 5., WithinRel( linear.y()[4] ) );

        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN
    } // WHEN

    WHEN( "two histogram regions have different y values at the shared boundary" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 1., 2., 5., 7. };
      std::vector< std::size_t > boundaries = { 2, 3 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::Histogram,
        InterpolationType::Histogram
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "the table gets linearised correctly" ) {

        // a jump will be inserted at the end of the first histogram region
        auto linear = chunk.linearise();

        CHECK( 6 == linear.numberPoints() );
        CHECK( 3 == linear.numberRegions() );

        CHECK( 3 == linear.boundaries().size() );
        CHECK( 3 == linear.interpolants().size() );

        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 3 == linear.boundaries()[1] );
        CHECK( 5 == linear.boundaries()[2] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[2] );

        CHECK_THAT( 1., WithinRel( linear.x()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.x()[3] ) );
        CHECK_THAT( 3., WithinRel( linear.x()[4] ) );
        CHECK_THAT( 4., WithinRel( linear.x()[5] ) );

        CHECK_THAT( 1., WithinRel( linear.y()[0] ) );
        CHECK_THAT( 1., WithinRel( linear.y()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[2] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[3] ) );
        CHECK_THAT( 5., WithinRel( linear.y()[4] ) );
        CHECK_THAT( 5., WithinRel( linear.y()[5] ) );

        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN
    } // WHEN

    WHEN( "two histogram regions have equal y values at the shared boundary" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 1., 2., 2., 5. };
      std::vector< std::size_t > boundaries = { 2, 3 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::Histogram,
        InterpolationType::Histogram
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "the table gets linearised correctly" ) {

        // no jump will be inserted at the end of the first histogram region
        auto linear = chunk.linearise();

        CHECK( 5 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 4 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( 1., WithinRel( linear.x()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.x()[3] ) );
        CHECK_THAT( 4., WithinRel( linear.x()[4] ) );

        CHECK_THAT( 1., WithinRel( linear.y()[0] ) );
        CHECK_THAT( 1., WithinRel( linear.y()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[2] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[3] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[4] ) );

        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
