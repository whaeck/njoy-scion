# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import ChebyshevSeries
from scion.math import IntervalDomain

class Test_scion_math_ChebyshevSeries( unittest.TestCase ) :
    """Unit test for the ChebyshevSeries class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.order )

            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -11.50, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.75, chunk.coefficients[1] )
            self.assertAlmostEqual(  -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.25, chunk.coefficients[3] )

            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )

            # verify evaluation
            self.assertAlmostEqual(  -8.0, chunk.evaluate( x =  0. ) )
            self.assertAlmostEqual(   0.0, chunk.evaluate( x =  1. ) )
            self.assertAlmostEqual( -30.0, chunk.evaluate( x = -1. ) )

            self.assertAlmostEqual(  -8.0, chunk( x =  0. ) )
            self.assertAlmostEqual(   0.0, chunk( x =  1. ) )
            self.assertAlmostEqual( -30.0, chunk( x = -1. ) )

        # the data is given explicitly
        chunk = ChebyshevSeries( coefficients = [ -23./2., 59./4., -7./2., 1./4. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the coefficient vector is empty
        with self.assertRaises( Exception ) :

            chunk = ChebyshevSeries( coefficients = [] )

if __name__ == '__main__' :

    unittest.main()
