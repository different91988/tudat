/*! \file sphericalHarmonicsGravityField.cpp
 *    Source file that defines the spherical harmonics gravity field model
 *    included in Tudat.
 *
 *    Path              : /Astrodynamics/EnvironmentModels/
 *    Version           : 8
 *    Check status      : Checked
 *
 *    Author            : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Checker           : J.C.P Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Date created      : 17 November, 2010
 *    Last modified     : 10 March, 2011
 *
 *    References
 *
 *    Notes
 *
 *    Copyright (c) 2010 Delft University of Technology.
 *
 *    This software is protected by national and international copyright.
 *    Any unauthorized use, reproduction or modification is unlawful and
 *    will be prosecuted. Commercial and non-private application of the
 *    software in any form is strictly prohibited unless otherwise granted
 *    by the authors.
 *
 *    The code is provided without any warranty; without even the implied
 *    warranty of merchantibility or fitness for a particular purpose.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      101117    K. Kumar          File created.
 *      101214    K. Kumar          Updated getGradientOfPotential() and
 *                                  getLaplacianOfPotential().
 *      101215    K. Kumar          Simplified getGradientOfPotential() and
 *                                  getLaplacianOfPotential().
 *      101216    K. Kumar          Updated functions to use position
 *                                  of origin for relative position.
 *      110106    K. Kumar          Added set/get functions for degree and
 *                                  order of expansion.
 *      110202    K. Kumar          Updated code to make use of the
 *                                  CartesianPositionElements class.
 *      110204    K. Kumar          Removed "vector" from naming.
 *      110310    K. Kumar          Changed naming from Laplacian to gradient
 *                                  tensor.
 */

// Include statements.
#include "sphericalHarmonicsGravityField.h"

// Using declarations.
using mathematics::raiseToIntegerPower;
using std::endl;

//! Default constructor.
SphericalHarmonicsGravityField::SphericalHarmonicsGravityField( )
    : degreeOfExpansion_( -0 ),
      orderOfExpansion_( -0 ),
      referenceRadius_( -0.0 )
{  
}

//! Default destructor.
SphericalHarmonicsGravityField::~SphericalHarmonicsGravityField( )
{
}

//! Set the reference radius.
void SphericalHarmonicsGravityField::setReferenceRadius(
        const double& referenceRadius )
{
    referenceRadius_ = referenceRadius;
}

//! Set degree of spherical harmonics gravity field expansion.
void SphericalHarmonicsGravityField::setDegreeOfExpansion(
        const unsigned int& degreeOfExpansion )
{
    degreeOfExpansion_ = degreeOfExpansion;
}

//! Set order of spherical harmonics gravity field expansion.
void SphericalHarmonicsGravityField::setOrderOfExpansion(
        const unsigned int& orderOfExpansion )
{
    orderOfExpansion_ = orderOfExpansion;
}

//! Get the reference radius.
double SphericalHarmonicsGravityField::getReferenceRadius( )
{
    return referenceRadius_;
}

//! Get degree of spherical harmonics gravity field expansion.
double SphericalHarmonicsGravityField::getDegreeOfExpansion( )
{
    return degreeOfExpansion_;
}

//! Get order of spherical harmonics gravity field expansion.
double SphericalHarmonicsGravityField::getOrderOfExpansion( )
{
    return orderOfExpansion_;
}

//! Get the gravitational potential.
double SphericalHarmonicsGravityField::getPotential(
        CartesianPositionElements* pointerToPosition )
{
    // Compute relative position.
    relativePosition_.state = pointerToPosition->state
                              - positionOfOrigin_.state;

    // Return the gravitational potential for a point mass.
    return gravitationalParameter_ / relativePosition_.state.norm( );
}

//! Get the gradient of the gravitational potential.
Vector3d SphericalHarmonicsGravityField::getGradientOfPotential(
        CartesianPositionElements* pointerToPosition )
{
    // Compute relative position.
    relativePosition_.state = pointerToPosition->state
                              - positionOfOrigin_.state;

    // Compute and return gradient of potential.
    return -gravitationalParameter_ * relativePosition_.state
            / raiseToIntegerPower( relativePosition_.state.norm(), 3 );
}

//! Get gradient tensor of the gravitational potential.
Matrix3d SphericalHarmonicsGravityField::
        getGradientTensorOfPotential( CartesianPositionElements*
                                      pointerToPosition )
{

    // Declare local variables.
    // Declare identity matrix for computations.
    Matrix3d identityMatrix_;

    // Compute relative position.
    relativePosition_.state = pointerToPosition->state
                              - positionOfOrigin_.state;
    // Set identity matrix to square size of state.
    identityMatrix_.setIdentity( 3, 3 );

    // Compute and return gradient tensor of potential.
    return gravitationalParameter_
            / raiseToIntegerPower( relativePosition_.state.norm( ), 5 )
            * ( ( 3.0 * relativePosition_.state
                  * relativePosition_.state.transpose( ) )
                - ( relativePosition_.state.squaredNorm( )
                    * identityMatrix_ ) );
}

//! Overload ostream to print class information.
std::ostream& operator<<( std::ostream& stream,
                          SphericalHarmonicsGravityField&
                          sphericalHarmonicsGravityField )
{
    stream << "This is a SphericalHarmonicsGravityField object." << endl;
    stream << "The gravitational parameter is set to: "
           << sphericalHarmonicsGravityField.getGravitationalParameter( )
           << endl;
    stream << "The origin of the gravity field is set to: "
           << sphericalHarmonicsGravityField.getOrigin( ) << endl;
    stream << "The degree of expansion of the spherical harmonics series is "
           << "set to : "
           << sphericalHarmonicsGravityField.getDegreeOfExpansion( ) << endl;
    stream << "The order of expansion of the spherical harmonics series is "
           << "set to: "
           << sphericalHarmonicsGravityField.getOrderOfExpansion( ) << endl;
    stream << "The reference radius is set to: "
           << sphericalHarmonicsGravityField.getReferenceRadius( ) << endl;

    // Return stream.
    return stream;
}

// End of file.
