/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Legendre series function (from
 *                        lowest to highest order coefficient)
 */
LegendreSeries( std::vector< Y > coefficients ) :
  Parent( IntervalDomain( -1., 1. ) ),
  coefficients_( std::move( coefficients ) ) {

  verifyCoefficients( this->coefficients() );
}
