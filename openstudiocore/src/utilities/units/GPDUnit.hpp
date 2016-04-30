/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef UTILITIES_UNITS_GPDUNIT_HPP
#define UTILITIES_UNITS_GPDUNIT_HPP

#include "../UtilitiesAPI.hpp"
#include "Unit.hpp"

namespace openstudio {
namespace detail {

  class GPDUnit_Impl;

} // detail

/** Structure to hold GPDUnit exponents needed for GPDUnit construction. For purposes of
 *  conversion we need a length base unit. Therefore, gal cannot be a base unit. For convenience
 *  of construction, GPDExpnt takes a gal argument, but subsequently this is stored as a power of
 *  cube root of gallons (crgal). \relates GPDUnit */
struct UTILITIES_API GPDExpnt {
 public:
  GPDExpnt(int inH2O=0,
           int gal=0,
           int day=0,
           int R=0,
           int A=0,
           int cd=0,
           int lbmol=0,
           int deg=0,
           int sr=0,
           int people=0,
           int cycle=0,
           int dollar=0)
    : m_inH2O(inH2O),
      m_crgal(3*gal),
      m_day(day),
      m_R(R),
      m_A(A),
      m_cd(cd),
      m_lbmol(lbmol),
      m_deg(deg),
      m_sr(sr),
      m_people(people),
      m_cycle(cycle),
      m_dollar(dollar)
  {}
 private:
  int m_inH2O;
  int m_crgal;
  int m_day;
  int m_R;
  int m_A;
  int m_cd;
  int m_lbmol;
  int m_deg;
  int m_sr;
  int m_people;
  int m_cycle;
  int m_dollar;

  friend class detail::GPDUnit_Impl;
};

/** GPDUnit is a Unit with baseUnits fixed by its constructors, see GPDExpnt. setBaseUnitExponent
 *  throws an exception if any other string is passed in as a baseUnit. GPDUnit.hpp declares
 *  related operators and UnitFactory callback functions. */
class UTILITIES_API GPDUnit : public Unit {
 public:
  /** @name Constructors and Destructors */
  //@{

  /** Default constructor.
   *
   *  \param[in] exponents holds the exponents for each base unit.
   *  \param[in] scaleExponent exponent for scale. For instance 3 for kilo.
   *  \param[in] prettyString optional string to use in place of standardString. */
  GPDUnit(const GPDExpnt& exponents=GPDExpnt(),
         int scaleExponent=0,
         const std::string& prettyString="");

  /** Alternate constructor. Specify the abbreviation of the scale, rather than its
   *  exponent.
   *
   *  \param[in] scaleAbbreviation is string equal to a scale abbreviation. For instance
   *    "k" for kilo.
   *  \param[in] exponents holds the exponents for each base unit.
   *  \param[in] prettyString optional string to use in place of standardString. */
  GPDUnit(const std::string& scaleAbbreviation,
         const GPDExpnt& exponents=GPDExpnt(),
         const std::string& prettyString="");

  virtual ~GPDUnit() {}

  //@}
 protected:
  /// @cond
  typedef detail::GPDUnit_Impl ImplType;

  explicit GPDUnit(std::shared_ptr<detail::GPDUnit_Impl> impl);

  friend class detail::GPDUnit_Impl;
  friend class Unit;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.units.GPDUnit");
};

/** \relates GPDUnit*/
UTILITIES_TEMPLATE_EXT template class UTILITIES_API boost::optional<GPDUnit>;
typedef boost::optional<GPDUnit> OptionalGPDUnit;

/** \relates GPDUnit*/
UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::vector<GPDUnit>;
typedef std::vector<GPDUnit> GPDUnitVector;

/** @name Create Functions Used by UnitFactory */
//@{

// base units

/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDPressure();
/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDLength();
/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDTime();
/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDTemperature();
/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDElectricCurrent();
/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDLuminousIntensity();
/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDAmountOfSubstance();
/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDAngle();
/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDSolidAngle();
/** \relates GPDUnit */
UTILITIES_API GPDUnit createGPDPeople();
/** relates GPDUnit */
UTILITIES_API GPDUnit createGPDCycle();
/** relates GPDUnit */
UTILITIES_API GPDUnit createGPDCurrency();

// first order derived units

/** Gallons (gal). \relates GPDUnit */
UTILITIES_API GPDUnit createGPDVolume();
/** Gallons per day (gpd) = gal/day. \relates GPDUnit */
UTILITIES_API GPDUnit createGPDVolumetricFlowrate();
/** Lumen (lm) = cd*sr. \relates GPDUnit */
UTILITIES_API GPDUnit createGPDLuminousFlux();

//@}

} // openstudio

#endif // UTILITIES_UNITS_GPDUNIT_HPP
