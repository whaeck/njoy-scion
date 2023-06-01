// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/HistogramTable.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapHistogramTableFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::HistogramTable< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "Tabulated data with histogram interpolation (y is constant in x)"
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

void wrapHistogramTable( python::module& module ) {

  wrapHistogramTableFor< double >( module, "HistogramTable" );
}

} // namespace math
