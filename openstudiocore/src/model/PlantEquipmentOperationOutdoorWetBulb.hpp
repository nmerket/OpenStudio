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

#ifndef MODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULB_HPP
#define MODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULB_HPP

#include "ModelAPI.hpp"
#include "PlantEquipmentOperationRangeBasedScheme.hpp"

namespace openstudio {
namespace model {

namespace detail {

  class PlantEquipmentOperationOutdoorWetBulb_Impl;

} // detail

/** PlantEquipmentOperationOutdoorWetBulb is a PlantEquipmentOperationRangeBasedScheme that wraps the OpenStudio IDD object 'OS:PlantEquipmentOperation:OutdoorWetBulb'. */
class MODEL_API PlantEquipmentOperationOutdoorWetBulb : public PlantEquipmentOperationRangeBasedScheme {
 public:
  /** @name Constructors and Destructors */
  //@{

  explicit PlantEquipmentOperationOutdoorWetBulb(const Model& model);

  virtual ~PlantEquipmentOperationOutdoorWetBulb() {}

  //@}

  static IddObjectType iddObjectType();

  /** @name Getters */
  //@{


  //@}
  /** @name Setters */
  //@{


  //@}
  /** @name Other */
  //@{


  //@}
 protected:
  /// @cond
  typedef detail::PlantEquipmentOperationOutdoorWetBulb_Impl ImplType;

  explicit PlantEquipmentOperationOutdoorWetBulb(std::shared_ptr<detail::PlantEquipmentOperationOutdoorWetBulb_Impl> impl);

  friend class detail::PlantEquipmentOperationOutdoorWetBulb_Impl;
  friend class Model;
  friend class IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.model.PlantEquipmentOperationOutdoorWetBulb");
};

/** \relates PlantEquipmentOperationOutdoorWetBulb*/
typedef boost::optional<PlantEquipmentOperationOutdoorWetBulb> OptionalPlantEquipmentOperationOutdoorWetBulb;

/** \relates PlantEquipmentOperationOutdoorWetBulb*/
typedef std::vector<PlantEquipmentOperationOutdoorWetBulb> PlantEquipmentOperationOutdoorWetBulbVector;

} // model
} // openstudio

#endif // MODEL_PLANTEQUIPMENTOPERATIONOUTDOORWETBULB_HPP

