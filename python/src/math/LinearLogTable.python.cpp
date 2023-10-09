// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/LinearLogTable.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapLinearLogTableFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::LinearLogTable< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "Tabulated data with log-log interpolation (y is linear in ln(x))"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< X >, std::vector< Y > >(),
    python::arg( "x" ), python::arg( "y" ),
    "Initialise the function\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    x      the x values of the tabulated data\n"
    "    y      the y values of the tabulated data"
  );

  // add standard function definitions
  addStandardSingleInterpolationTableDefinitions< Component, X, Y >( component );
}

void wrapLinearLogTable( python::module& module ) {

  wrapLinearLogTableFor< double >( module, "LinearLogTable" );
}

} // namespace math
