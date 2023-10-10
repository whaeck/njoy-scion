// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/LogLinearTable.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using LogLinearTable = math::LogLinearTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "LogLinearTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      LogLinearTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLinearTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLinear == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LogLinearTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.46410161513775, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.44948974278318, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.41421356237309, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLinearTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 21 == linear.first.size() );
        CHECK( 21 == linear.second.size() );

        CHECK_THAT( 1.   , WithinRel( linear.first[0] ) );
        CHECK_THAT( 1.25 , WithinRel( linear.first[1] ) );
        CHECK_THAT( 1.5  , WithinRel( linear.first[2] ) );
        CHECK_THAT( 1.75 , WithinRel( linear.first[3] ) );
        CHECK_THAT( 2    , WithinRel( linear.first[4] ) );
        CHECK_THAT( 2.125, WithinRel( linear.first[5] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.first[6] ) );
        CHECK_THAT( 2.375, WithinRel( linear.first[7] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.first[8] ) );
        CHECK_THAT( 2.625, WithinRel( linear.first[9] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.first[10] ) );
        CHECK_THAT( 2.875, WithinRel( linear.first[11] ) );
        CHECK_THAT( 3.   , WithinRel( linear.first[12] ) );
        CHECK_THAT( 3.125, WithinRel( linear.first[13] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.first[14] ) );
        CHECK_THAT( 3.375, WithinRel( linear.first[15] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.first[16] ) );
        CHECK_THAT( 3.625, WithinRel( linear.first[17] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.first[18] ) );
        CHECK_THAT( 3.875, WithinRel( linear.first[19] ) );
        CHECK_THAT( 4.   , WithinRel( linear.first[20] ) );

        CHECK_THAT( 4.              , WithinRel( linear.second[0] ) );
        CHECK_THAT( 3.72241943640840, WithinRel( linear.second[1] ) );
        CHECK_THAT( 3.46410161513775, WithinRel( linear.second[2] ) );
        CHECK_THAT( 3.22370979547063, WithinRel( linear.second[3] ) );
        CHECK_THAT( 3.              , WithinRel( linear.second[4] ) );
        CHECK_THAT( 2.85173947486242, WithinRel( linear.second[5] ) );
        CHECK_THAT( 2.71080601082953, WithinRel( linear.second[6] ) );
        CHECK_THAT( 2.57683750325897, WithinRel( linear.second[7] ) );
        CHECK_THAT( 2.44948974278318, WithinRel( linear.second[8] ) );
        CHECK_THAT( 2.32843553092180, WithinRel( linear.second[9] ) );
        CHECK_THAT( 2.21336383940064, WithinRel( linear.second[10] ) );
        CHECK_THAT( 2.10397901101729, WithinRel( linear.second[11] ) );
        CHECK_THAT( 2.              , WithinRel( linear.second[12] ) );
        CHECK_THAT( 1.83400808640934, WithinRel( linear.second[13] ) );
        CHECK_THAT( 1.68179283050743, WithinRel( linear.second[14] ) );
        CHECK_THAT( 1.54221082540794, WithinRel( linear.second[15] ) );
        CHECK_THAT( 1.41421356237309, WithinRel( linear.second[16] ) );
        CHECK_THAT( 1.29683955465101, WithinRel( linear.second[17] ) );
        CHECK_THAT( 1.18920711500272, WithinRel( linear.second[18] ) );
        CHECK_THAT( 1.09050773266526, WithinRel( linear.second[19] ) );
        CHECK_THAT( 1.              , WithinRel( linear.second[20] ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( 1., 4. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly using iterator views" ) {

      using View = njoy::utility::IteratorView< std::vector< double >::const_iterator >;

      const std::vector< double > xvalues= { 1., 2., 3., 4. };
      const std::vector< double > yvalues = { 4., 3., 2., 1. };

      View x = njoy::utility::make_view( xvalues );
      View y = njoy::utility::make_view( yvalues );

      LogLinearTable< double, double, View, View > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLinearTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLinear == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LogLinearTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.46410161513775, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.44948974278318, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.41421356237309, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLinearTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 21 == linear.first.size() );
        CHECK( 21 == linear.second.size() );

        CHECK_THAT( 1.   , WithinRel( linear.first[0] ) );
        CHECK_THAT( 1.25 , WithinRel( linear.first[1] ) );
        CHECK_THAT( 1.5  , WithinRel( linear.first[2] ) );
        CHECK_THAT( 1.75 , WithinRel( linear.first[3] ) );
        CHECK_THAT( 2    , WithinRel( linear.first[4] ) );
        CHECK_THAT( 2.125, WithinRel( linear.first[5] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.first[6] ) );
        CHECK_THAT( 2.375, WithinRel( linear.first[7] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.first[8] ) );
        CHECK_THAT( 2.625, WithinRel( linear.first[9] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.first[10] ) );
        CHECK_THAT( 2.875, WithinRel( linear.first[11] ) );
        CHECK_THAT( 3.   , WithinRel( linear.first[12] ) );
        CHECK_THAT( 3.125, WithinRel( linear.first[13] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.first[14] ) );
        CHECK_THAT( 3.375, WithinRel( linear.first[15] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.first[16] ) );
        CHECK_THAT( 3.625, WithinRel( linear.first[17] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.first[18] ) );
        CHECK_THAT( 3.875, WithinRel( linear.first[19] ) );
        CHECK_THAT( 4.   , WithinRel( linear.first[20] ) );

        CHECK_THAT( 4.              , WithinRel( linear.second[0] ) );
        CHECK_THAT( 3.72241943640840, WithinRel( linear.second[1] ) );
        CHECK_THAT( 3.46410161513775, WithinRel( linear.second[2] ) );
        CHECK_THAT( 3.22370979547063, WithinRel( linear.second[3] ) );
        CHECK_THAT( 3               , WithinRel( linear.second[4] ) );
        CHECK_THAT( 2.85173947486242, WithinRel( linear.second[5] ) );
        CHECK_THAT( 2.71080601082953, WithinRel( linear.second[6] ) );
        CHECK_THAT( 2.57683750325897, WithinRel( linear.second[7] ) );
        CHECK_THAT( 2.44948974278318, WithinRel( linear.second[8] ) );
        CHECK_THAT( 2.32843553092180, WithinRel( linear.second[9] ) );
        CHECK_THAT( 2.21336383940064, WithinRel( linear.second[10] ) );
        CHECK_THAT( 2.10397901101729, WithinRel( linear.second[11] ) );
        CHECK_THAT( 2.              , WithinRel( linear.second[12] ) );
        CHECK_THAT( 1.83400808640934, WithinRel( linear.second[13] ) );
        CHECK_THAT( 1.68179283050743, WithinRel( linear.second[14] ) );
        CHECK_THAT( 1.54221082540794, WithinRel( linear.second[15] ) );
        CHECK_THAT( 1.41421356237309, WithinRel( linear.second[16] ) );
        CHECK_THAT( 1.29683955465101, WithinRel( linear.second[17] ) );
        CHECK_THAT( 1.18920711500272, WithinRel( linear.second[18] ) );
        CHECK_THAT( 1.09050773266526, WithinRel( linear.second[19] ) );
        CHECK_THAT( 1.              , WithinRel( linear.second[20] ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( 1., 4. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LogLinearTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLinearTable< double >( empty, empty ) );
        CHECK_THROWS( LogLinearTable< double >( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLinearTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLinearTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLinearTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
