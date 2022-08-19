//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PHYSXSCHEMA_GENERATED_PHYSXVEHICLEAPI_H
#define PHYSXSCHEMA_GENERATED_PHYSXVEHICLEAPI_H

/// \file physxSchema/physxVehicleAPI.h

#include "pxr/pxr.h"
#include ".//api.h"
#include "pxr/usd/usd/apiSchemaBase.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/stage.h"
#include ".//tokens.h"

#include "pxr/base/vt/value.h"

#include "pxr/base/gf/vec3d.h"
#include "pxr/base/gf/vec3f.h"
#include "pxr/base/gf/matrix4d.h"

#include "pxr/base/tf/token.h"
#include "pxr/base/tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// PHYSXVEHICLEAPI                                                            //
// -------------------------------------------------------------------------- //

/// \class PhysxSchemaPhysxVehicleAPI
///
/// PhysX vehicle. Has to be applied to a prim with PhysicsRigidBodyAPI applied. Wheels can be added by applying PhysxVehicleWheelAttachmentAPI to a prim that is a descendant of the "vehicle" prim.
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref PhysxSchemaTokens.
/// So to set an attribute to the value "rightHanded", use PhysxSchemaTokens->rightHanded
/// as the value.
///
class PhysxSchemaPhysxVehicleAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::SingleApplyAPI;

    /// Construct a PhysxSchemaPhysxVehicleAPI on UsdPrim \p prim .
    /// Equivalent to PhysxSchemaPhysxVehicleAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit PhysxSchemaPhysxVehicleAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a PhysxSchemaPhysxVehicleAPI on the prim held by \p schemaObj .
    /// Should be preferred over PhysxSchemaPhysxVehicleAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit PhysxSchemaPhysxVehicleAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    PHYSXSCHEMA_API
    virtual ~PhysxSchemaPhysxVehicleAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    PHYSXSCHEMA_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a PhysxSchemaPhysxVehicleAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// PhysxSchemaPhysxVehicleAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    PHYSXSCHEMA_API
    static PhysxSchemaPhysxVehicleAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "PhysxVehicleAPI" to the 
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    /// 
    /// \return A valid PhysxSchemaPhysxVehicleAPI object is returned upon success. 
    /// An invalid (or empty) PhysxSchemaPhysxVehicleAPI object is returned upon 
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions 
    /// resulting in failure. 
    /// 
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    PHYSXSCHEMA_API
    static PhysxSchemaPhysxVehicleAPI 
    Apply(const UsdPrim &prim);

protected:
    /// Returns the type of schema this class belongs to.
    ///
    /// \sa UsdSchemaType
    PHYSXSCHEMA_API
    UsdSchemaType _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    PHYSXSCHEMA_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    PHYSXSCHEMA_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // VEHICLEENABLED 
    // --------------------------------------------------------------------- //
    /// Defines whether the vehicle simulation update loop will run for the vehicle or not.
    /// 
    /// Note: if set to false, the prim's rigid body will still get simulated (the PhysicsRigidBodyAPI API schema
    /// can be used to turn the body into a kinematic or set velocities to zero at that point).
    /// 
    /// Note: it is an illegal setup to have a vehicle enabled, while the prim's rigid body is disabled or kinematic.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool physxVehicle:vehicleEnabled = 1` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    PHYSXSCHEMA_API
    UsdAttribute GetVehicleEnabledAttr() const;

    /// See GetVehicleEnabledAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateVehicleEnabledAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // SUSPENSIONLINEQUERYTYPE 
    // --------------------------------------------------------------------- //
    /// Collision of the wheels with the ground surface is detected through scene queries along the suspension direction. 
    /// This attribute defines whether a raycast or a sweep should be used as the query type. Raycasts are faster while sweeps
    /// can represent the wheel shape better and thus react earlier to ground surface changes.
    /// 
    /// Note: to use sweeps, all wheels need to have collision geometry defined (either a convex mesh that was generated from
    /// a mesh, a capsule or a sphere).
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `uniform token physxVehicle:suspensionLineQueryType = "raycast"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
    /// | \ref PhysxSchemaTokens "Allowed Values" | raycast, sweep |
    PHYSXSCHEMA_API
    UsdAttribute GetSuspensionLineQueryTypeAttr() const;

    /// See GetSuspensionLineQueryTypeAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateSuspensionLineQueryTypeAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // SUBSTEPTHRESHOLDLONGITUDINALSPEED 
    // --------------------------------------------------------------------- //
    /// Threshold speed that is used to categorize vehicle speed as low speed or high speed for
    /// choosing the sub-step count.
    /// 
    /// Note: if not defined, the value 5.0 will be used. This default value is in meter length scale 
    /// and will get adjusted if another unit is used.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxVehicle:subStepThresholdLongitudinalSpeed` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetSubStepThresholdLongitudinalSpeedAttr() const;

    /// See GetSubStepThresholdLongitudinalSpeedAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateSubStepThresholdLongitudinalSpeedAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // LOWFORWARDSPEEDSUBSTEPCOUNT 
    // --------------------------------------------------------------------- //
    /// Number of sub-steps performed in the vehicle dynamics update for vehicles that have
    /// longitudinal speed lower than subStepThresholdLongitudinalSpeed.
    /// 
    /// Note: if not defined, the value 3 will be used.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int physxVehicle:lowForwardSpeedSubStepCount` |
    /// | C++ Type | int |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Int |
    PHYSXSCHEMA_API
    UsdAttribute GetLowForwardSpeedSubStepCountAttr() const;

    /// See GetLowForwardSpeedSubStepCountAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateLowForwardSpeedSubStepCountAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // HIGHFORWARDSPEEDSUBSTEPCOUNT 
    // --------------------------------------------------------------------- //
    /// Number of sub-steps performed in the vehicle dynamics update for vehicles that have
    /// longitudinal speed greater than subStepThresholdLongitudinalSpeed.
    /// 
    /// Note: if not defined, the value 1 will be used.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int physxVehicle:highForwardSpeedSubStepCount` |
    /// | C++ Type | int |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Int |
    PHYSXSCHEMA_API
    UsdAttribute GetHighForwardSpeedSubStepCountAttr() const;

    /// See GetHighForwardSpeedSubStepCountAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateHighForwardSpeedSubStepCountAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // MINLONGITUDINALSLIPDENOMINATOR 
    // --------------------------------------------------------------------- //
    /// The minimum denominator used in the longitudinal slip calculation. For low longitudinal
    /// velocities, the computation of the longitudinal slip can become unstable. This value defines
    /// the minimum velocity to use when computing the longitudinal slip.
    /// 
    /// Note: if not defined, the value 4.0 will be used. This default value is in meter length scale 
    /// and will get adjusted if another unit is used.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxVehicle:minLongitudinalSlipDenominator` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetMinLongitudinalSlipDenominatorAttr() const;

    /// See GetMinLongitudinalSlipDenominatorAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateMinLongitudinalSlipDenominatorAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // DRIVE 
    // --------------------------------------------------------------------- //
    /// A relationship to a PhysxVehicleDriveBasicAPI or PhysxVehicleDriveStandardAPI prim that describes the 
    /// drive model. If none is specified, it is up to the user to apply torque to the wheels. It is also
    /// possible to apply PhysxVehicleDriveBasicAPI or PhysxVehicleDriveStandardAPI to the prim directly. In 
    /// that case the relationship must not be defined.
    ///
    PHYSXSCHEMA_API
    UsdRelationship GetDriveRel() const;

    /// See GetDriveRel(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create
    PHYSXSCHEMA_API
    UsdRelationship CreateDriveRel() const;

public:
    // ===================================================================== //
    // Feel free to add custom code below this line, it will be preserved by 
    // the code generator. 
    //
    // Just remember to: 
    //  - Close the class declaration with }; 
    //  - Close the namespace with PXR_NAMESPACE_CLOSE_SCOPE
    //  - Close the include guard with #endif
    // ===================================================================== //
    // --(BEGIN CUSTOM CODE)--
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
