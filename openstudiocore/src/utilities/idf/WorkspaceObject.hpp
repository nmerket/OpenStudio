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

#ifndef UTILITIES_IDF_WORKSPACEOBJECT_HPP
#define UTILITIES_IDF_WORKSPACEOBJECT_HPP

#include "../UtilitiesAPI.hpp"
#include "IdfObject.hpp"

namespace openstudio {

class Workspace;
class WorkspaceExtensibleGroup;

// forward declarations
namespace detail {
  class IdfObject_Impl;
  class WorkspaceObject_Impl;
  class Workspace_Impl;
}

/** WorkspaceObject holds and manipulates data objects in Energyplus IDF format in the context of
 *  a Workspace. Over and above IdfObject, WorkspaceObject maintains ObjectListType fields as
 *  pointers (possibly null) to other WorkspaceObjects in the same Workspace, and only commits 
 *  changes that maintain the validity of its Workspace at the current StrictnessLevel (typically
 *  Draft, moving to Final right before simulation). */
class UTILITIES_API WorkspaceObject : public IdfObject {
 public:
  /** @name Constructors and Destructors */
  //@{

  virtual ~WorkspaceObject() {}

  /** Removes the object from the Workspace. Returns an IdfObjectVector of all removed object(s). */
  // TODO: Replace return type with undo struct including connections.
  std::vector<openstudio::IdfObject> remove();

  //@}
  /** @name Getters */
  //@{

  /** Return the Workspace that contains this WorkspaceObject. */
  Workspace workspace() const;

  /** Returns the object pointed to by field index, if it exists. */
  boost::optional<WorkspaceObject> getTarget(unsigned index) const;

  /** Returns all objects pointed to by this object. */
  std::vector<WorkspaceObject> targets() const;

  /** Returns the index of the field in this object that points to targetHandle, if possible. */
  std::vector<unsigned> getSourceIndices(const Handle& targetHandle) const;

  /** Returns all objects that point to this object, filtering for duplicate objects. */
  std::vector<WorkspaceObject> sources() const;

  /** Returns all objects of type that point to this object, filtering for duplicate objects. */
  std::vector<WorkspaceObject> getSources(IddObjectType type) const;

  //@}
  /** @name Setters */
  //@{

  /** Sets the pointer at field index to targetHandle, if possible. The field must be of object-list
   *  type, and targetHandle must be valid (null or in the containing Workspace, and if the strictness
   *  is greater than enums::None, must correspond to an object of a proper type). */
  bool setPointer(unsigned index, const Handle& targetHandle);

  //@}
  /** @name Queries */
  //@{

  bool operator<(const WorkspaceObject& right) const;

  bool initialized() const;

  /** Returns the number of objects that point to this object. */
  unsigned numSources() const;

  /** Returns true if this object points to another object. To qualify, there must be at least one
   *  pointer field holding a non-null pointer. */
  bool isSource() const;

  /** Returns true if this object can point to another object. To qualify, there must be at least
   *  one object-list field. */
  bool canBeSource() const;

  /** Returns true if field index can be a source field. If no refLists are specified, then
   *  this call is equivalent to iddObject().getField(index)->isObjectListField(). If a
   *  non-empty vector of refLists is specified, then true is only returned if there is a match
   *  between field index's object lists and the referencesLists argument. */
  bool canBeSource(unsigned index,
                   const std::vector<std::string>& refLists=std::vector<std::string>()) const;

  /** Returns true if another object points to this object. */
  bool isTarget() const;

  /** Returns the reference lists of which this object is a member, if this object has a name. */
  std::vector<std::string> canBeTarget() const;

  /** Checks for equality of objectListFields(). Prerequisite: iddObject()s must be 
   *  equal. Looks for object equality of targets if same workspace(), otherwise, looks for data 
   *  field equality of targets. */
  bool objectListFieldsEqual(const WorkspaceObject& other) const;

  /** Returns true if for all objectListFields() that for both objects are non-empty, 
   *  the values are equal (using the same criteria as objectListFieldsEqual). 
   *  Prerequisite: iddObject()s must be equal. */
  bool objectListFieldsNonConflicting(const WorkspaceObject& other) const;

  //@}
  /** @name Serialization */
  //@{

  /** Returns an equivalent IdfObject, naming target objects if necessary. All data is cloned. 
   *  If the objects have handle fields (as in the OpenStudio IDD), pointers to other objects 
   *  are printed as handles; otherwise pointers are printed as names. */
  //DLM@20101010: don't like const overload, just make sure everything is named all the time
  IdfObject idfObject();

  /** Returns an equivalent IdfObject, leaving unnamed target objects unnamed. All data is cloned.
   *  If the objects have handle fields (as in the OpenStudio IDD), pointers to other objects 
   *  are printed as handles; otherwise pointers are printed as names. */
  //DLM@20101010: don't like const overload, just make sure everything is named all the time
  IdfObject idfObject() const;

  //@}

 protected:

  typedef detail::WorkspaceObject_Impl ImplType;

  friend class Workspace;
  friend class detail::Workspace_Impl;
  friend class IdfObject;
  friend class detail::IdfObject_Impl;
  friend class detail::WorkspaceObject_Impl;
  friend class WorkspaceExtensibleGroup;

  WorkspaceObject(std::shared_ptr<detail::WorkspaceObject_Impl> impl);

 private:
 
  std::vector<WorkspaceObject> objects(const std::vector<Handle>& handles,bool sorted) const;

  REGISTER_LOGGER("utilities.idf.WorkspaceObject");
};

/** \relates WorkspaceObject */
UTILITIES_TEMPLATE_EXT template class UTILITIES_API boost::optional<WorkspaceObject>;
typedef boost::optional<WorkspaceObject> OptionalWorkspaceObject;

/** \relates WorkspaceObject */
//UTILITIES_TEMPLATE_EXT template class UTILITIES_API std::vector<WorkspaceObject>;
typedef std::vector<WorkspaceObject> WorkspaceObjectVector;

/** \relates WorkspaceObject
 *  Outputs WorkspaceObject as (IDF) text. */
UTILITIES_API std::ostream& operator<<(std::ostream& os, const WorkspaceObject& workspaceObject);

} // openstudio

#endif // UTILITIES_IDF_WORKSPACEOBJECT_HPP
