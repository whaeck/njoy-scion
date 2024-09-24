LogLogTableFunction( const LogLogTableFunction& ) = default;
LogLogTableFunction( LogLogTableFunction&& ) = default;

LogLogTableFunction& operator=( const LogLogTableFunction& ) = default;
LogLogTableFunction& operator=( LogLogTableFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param f   the f(y) functions of the tabulated data
 */
LogLogTableFunction( XContainer x, FContainer f ) :
  Parent( std::move( x ), std::move( f ) ) {}
