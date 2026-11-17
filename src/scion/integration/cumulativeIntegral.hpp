#ifndef NJOY_SCION_INTEGRATION_CUMULATIVE_INTEGRAL
#define NJOY_SCION_INTEGRATION_CUMULATIVE_INTEGRAL

// system includes
#include <iterator>

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @brief Calculate the cumulative integral by applying an analytical integrator
   *         on tabulated x and y values
   *
   *  This calculates the cumulative integral over the entire x range.
   *
   *  @param[in] xbegin       the iterator to the first x value
   *  @param[in] xend         the iterator to the end of the x values
   *  @param[in] ybegin       the iterator to the first y value
   *  @param[in] rbegin       the iterator to the cumulative integral for the first x value
   *  @param[in] integrator   the integrator to be applied
   */
  template< typename XIterator, typename YIterator, typename RIterator, typename Integrator >
  void cumulativeIntegral( XIterator xbegin, XIterator xend, YIterator ybegin,
                           RIterator rbegin, const Integrator& integrator ) {

    auto previous = rbegin;
    if ( xbegin != xend ) {

      ++xbegin;
      ++ybegin;
      ++rbegin;
    }

    while ( xbegin != xend ) {

      *rbegin = *previous + integrator( *std::prev( xbegin ), *xbegin, *std::prev( ybegin ), *ybegin );
      previous = rbegin;
      ++xbegin;
      ++ybegin;
      ++rbegin;
    }
  }

  /**
   *  @brief Calculate the cumulative integral by applying an analytical integrator
   *         on tabulated x and y values
   *
   *  This calculates the cumulative integral over the entire x range.
   *
   *  @param[in] x            the range of x values
   *  @param[in] y            the range of y values
   *  @param[in] rbegin       the iterator to the cumulative integral for the first x value
   *  @param[in] integrator   the integrator to be applied
   */
  template< typename XRange, typename YRange, typename RIterator, typename Integrator >
  auto cumulativeIntegral( const XRange& x, const YRange& y,
                           RIterator rbegin, const Integrator& integrator ) {

    cumulativeIntegral( x.begin(), x.end(), y.begin(), rbegin, integrator );
  }

} // integration namespace
} // scion namespace
} // njoy namespace

#endif
