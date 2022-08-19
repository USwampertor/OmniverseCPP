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
#ifndef PHYSXSCHEMA_GENERATED_PHYSXCAMERAFOLLOWLOOKAPI_H
#define PHYSXSCHEMA_GENERATED_PHYSXCAMERAFOLLOWLOOKAPI_H

/// \file physxSchema/physxCameraFollowLookAPI.h

#include "pxr/pxr.h"
#include ".//api.h"
#include ".//physxCameraFollowAPI.h"
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
// PHYSXCAMERAFOLLOWLOOKAPI                                                   //
// -------------------------------------------------------------------------- //

/// \class PhysxSchemaPhysxCameraFollowLookAPI
///
/// PhysX camera that follows behind the subject's forward vector as it moves. Assumes the subject is always upright and does not roll.
///
class PhysxSchemaPhysxCameraFollowLookAPI : public PhysxSchemaPhysxCameraFollowAPI
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::SingleApplyAPI;

    /// Construct a PhysxSchemaPhysxCameraFollowLookAPI on UsdPrim \p prim .
    /// Equivalent to PhysxSchemaPhysxCameraFollowLookAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit PhysxSchemaPhysxCameraFollowLookAPI(const UsdPrim& prim=UsdPrim())
        : PhysxSchemaPhysxCameraFollowAPI(prim)
    {
    }

    /// Construct a PhysxSchemaPhysxCameraFollowLookAPI on the prim held by \p schemaObj .
    /// Should be preferred over PhysxSchemaPhysxCameraFollowLookAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit PhysxSchemaPhysxCameraFollowLookAPI(const UsdSchemaBase& schemaObj)
        : PhysxSchemaPhysxCameraFollowAPI(schemaObj)
    {
    }

    /// Destructor.
    PHYSXSCHEMA_API
    virtual ~PhysxSchemaPhysxCameraFollowLookAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    PHYSXSCHEMA_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a PhysxSchemaPhysxCameraFollowLookAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// PhysxSchemaPhysxCameraFollowLookAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    PHYSXSCHEMA_API
    static PhysxSchemaPhysxCameraFollowLookAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "PhysxCameraFollowLookAPI" to the 
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    /// 
    /// \return A valid PhysxSchemaPhysxCameraFollowLookAPI object is returned upon success. 
    /// An invalid (or empty) PhysxSchemaPhysxCameraFollowLookAPI object is returned upon 
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions 
    /// resulting in failure. 
    /// 
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    PHYSXSCHEMA_API
    static PhysxSchemaPhysxCameraFollowLookAPI 
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
    // DOWNHILLGROUNDANGLE 
    // --------------------------------------------------------------------- //
    /// The minimum pitch angle of the terrain used for a linear interpolation to adjust the pitch of the camera. e.g. -45.0 degrees
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxFollowLookCamera:downHillGroundAngle` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetDownHillGroundAngleAttr() const;

    /// See GetDownHillGroundAngleAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateDownHillGroundAngleAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // DOWNHILLGROUNDPITCH 
    // --------------------------------------------------------------------- //
    /// The minimum pitch angle of the camera used for a linear interpolation to adjust the pitch of the camera. e.g. 10.0 degrees
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxFollowLookCamera:downHillGroundPitch` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetDownHillGroundPitchAttr() const;

    /// See GetDownHillGroundPitchAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateDownHillGroundPitchAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // UPHILLGROUNDANGLE 
    // --------------------------------------------------------------------- //
    /// The maximum pitch angle of the terrain used for a linear interpolation to adjust the pitch of the camera. e.g. 45.0 degrees
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxFollowLookCamera:upHillGroundAngle` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetUpHillGroundAngleAttr() const;

    /// See GetUpHillGroundAngleAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateUpHillGroundAngleAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // UPHILLGROUNDPITCH 
    // --------------------------------------------------------------------- //
    /// The maximum pitch angle of the camera used for a linear interpolation to adjust the pitch of the camera. e.g. 10.0 degrees
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxFollowLookCamera:upHillGroundPitch` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetUpHillGroundPitchAttr() const;

    /// See GetUpHillGroundPitchAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateUpHillGroundPitchAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // VELOCITYBLENDTIMECONSTANT 
    // --------------------------------------------------------------------- //
    /// Filter time constant to blend between the look and velocity vectors, in seconds. e.g. 0.1 seconds
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxFollowLookCamera:velocityBlendTimeConstant` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetVelocityBlendTimeConstantAttr() const;

    /// See GetVelocityBlendTimeConstantAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateVelocityBlendTimeConstantAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FOLLOWREVERSESPEED 
    // --------------------------------------------------------------------- //
    /// The positive, maximum speed, when driving in reverse, used for a linear interpolation to compute the follow distance of the camera. e.g. 1500.0 cm/sec
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxFollowLookCamera:followReverseSpeed` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetFollowReverseSpeedAttr() const;

    /// See GetFollowReverseSpeedAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateFollowReverseSpeedAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FOLLOWREVERSEDISTANCE 
    // --------------------------------------------------------------------- //
    /// The maximum distance, when driving in reverse, used for a linear interpolation to compute the follow distance of the camera. e.g. 3000.0 cm
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxFollowLookCamera:followReverseDistance` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetFollowReverseDistanceAttr() const;

    /// See GetFollowReverseDistanceAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateFollowReverseDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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
