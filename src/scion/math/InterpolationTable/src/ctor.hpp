/**
 *  @brief Copy constructor
 *
 *  @param[in] table    the table to be copied
 */
InterpolationTable( const InterpolationTable& table ) :
  Parent( IntervalDomain( table.x_.front(), table.x_.back() ) ),
  x_( table.x_ ), y_( table.y_ ),
  boundaries_( table.boundaries_ ),
  interpolants_( table.interpolants_ ) {

  this->generateTables();
}

/**
 *  @brief Move constructor
 *
 *  @param[in] table    the table to be moved
 */
InterpolationTable( InterpolationTable&& table ) :
  Parent( IntervalDomain( table.x_.front(), table.x_.back() ) ),
  x_( std::move( table.x_ ) ), y_( std::move( table.y_ ) ),
  boundaries_( std::move( table.boundaries_ ) ),
  interpolants_( std::move( table.interpolants_ ) ) {

  this->generateTables();
}

/**
 *  @brief Copy assignment using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be copied
 */
InterpolationTable& operator=( const InterpolationTable& base ) {

  if ( this != &base ) {

    new (this) InterpolationTable( base );
  }
  return *this;
}

/**
 *  @brief Move assignment using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be moved
 */
InterpolationTable& operator=( InterpolationTable&& base ) {

  if ( this != &base ) {

    new (this) InterpolationTable( std::move( base ) );
  }
  return *this;
}

/**
 *  @brief Constructor
 *
 *  @param x              the x values of the tabulated data
 *  @param y              the y values of the tabulated data
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
InterpolationTable( std::vector< X > x, std::vector< Y > y,
                    std::vector< std::size_t > boundaries,
                    std::vector< interpolation::InterpolationType > interpolants ) :
  Parent( IntervalDomain( x.front(), x.back() ) ),
  x_( std::move( x ) ), y_( std::move( y ) ),
  boundaries_( std::move( boundaries ) ),
  interpolants_( std::move( interpolants ) ) {

  this->generateTables();
}

/**
 *  @brief Constructor for tabulated data in a single interpolation zone
 *
 *  @param x              the x values of the tabulated data
 *  @param y              the y values of the tabulated data
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
InterpolationTable( std::vector< X > x, std::vector< Y > y,
                    interpolation::InterpolationType interpolant =
                        interpolation::InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( x ), std::move( y ),
                      { std::size( x ) },
                      { interpolant } ) {}
