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
#ifndef FORCEFIELDSCHEMA_GENERATED_PHYSXFORCEFIELDAPI_H
#define FORCEFIELDSCHEMA_GENERATED_PHYSXFORCEFIELDAPI_H

/// \file forceFieldSchema/physxForceFieldAPI.h

#include "pxr/pxr.h"
#include "forceFieldSchema/api.h"
#include "pxr/usd/usd/apiSchemaBase.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/stage.h"
#include "forceFieldSchema/tokens.h"

#include "pxr/base/vt/value.h"

#include "pxr/base/gf/vec3d.h"
#include "pxr/base/gf/vec3f.h"
#include "pxr/base/gf/matrix4d.h"

#include "pxr/base/tf/token.h"
#include "pxr/base/tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// PHYSXFORCEFIELDAPI                                                         //
// -------------------------------------------------------------------------- //

/// \class ForceFieldSchemaPhysxForceFieldAPI
///
/// Force field base class that simply specifies the position and enables or disables the ForceField.
///
class ForceFieldSchemaPhysxForceFieldAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::MultipleApplyAPI;

    /// Construct a ForceFieldSchemaPhysxForceFieldAPI on UsdPrim \p prim with
    /// name \p name . Equivalent to
    /// ForceFieldSchemaPhysxForceFieldAPI::Get(
    ///    prim.GetStage(),
    ///    prim.GetPath().AppendProperty(
    ///        "physxForceField:name"));
    ///
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit ForceFieldSchemaPhysxForceFieldAPI(
        const UsdPrim& prim=UsdPrim(), const TfToken &name=TfToken())
        : UsdAPISchemaBase(prim, /*instanceName*/ name)
    { }

    /// Construct a ForceFieldSchemaPhysxForceFieldAPI on the prim held by \p schemaObj with
    /// name \p name.  Should be preferred over
    /// ForceFieldSchemaPhysxForceFieldAPI(schemaObj.GetPrim(), name), as it preserves
    /// SchemaBase state.
    explicit ForceFieldSchemaPhysxForceFieldAPI(
        const UsdSchemaBase& schemaObj, const TfToken &name)
        : UsdAPISchemaBase(schemaObj, /*instanceName*/ name)
    { }

    /// Destructor.
    FORCEFIELDSCHEMA_API
    virtual ~ForceFieldSchemaPhysxForceFieldAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes for a given instance name.  Does not
    /// include attributes that may be authored by custom/extended methods of
    /// the schemas involved. The names returned will have the proper namespace
    /// prefix.
    FORCEFIELDSCHEMA_API
    static const TfTokenVector &
    GetSchemaAttributeNames(
        bool includeInherited=true, const TfToken instanceName=TfToken());

    /// Returns the name of this multiple-apply schema instance
    TfToken GetName() const {
        return _GetInstanceName();
    }

    /// Return a ForceFieldSchemaPhysxForceFieldAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  \p path must be of the format
    /// <path>.physxForceField:name .
    ///
    /// This is shorthand for the following:
    ///
    /// \code
    /// TfToken name = SdfPath::StripNamespace(path.GetToken());
    /// ForceFieldSchemaPhysxForceFieldAPI(
    ///     stage->GetPrimAtPath(path.GetPrimPath()), name);
    /// \endcode
    ///
    FORCEFIELDSCHEMA_API
    static ForceFieldSchemaPhysxForceFieldAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);

    /// Return a ForceFieldSchemaPhysxForceFieldAPI with name \p name holding the
    /// prim \p prim. Shorthand for ForceFieldSchemaPhysxForceFieldAPI(prim, name);
    FORCEFIELDSCHEMA_API
    static ForceFieldSchemaPhysxForceFieldAPI
    Get(const UsdPrim &prim, const TfToken &name);

    /// Checks if the given name \p baseName is the base name of a property
    /// of PhysxForceFieldAPI.
    FORCEFIELDSCHEMA_API
    static bool
    IsSchemaPropertyBaseName(const TfToken &baseName);

    /// Checks if the given path \p path is of an API schema of type
    /// PhysxForceFieldAPI. If so, it stores the instance name of
    /// the schema in \p name and returns true. Otherwise, it returns false.
    FORCEFIELDSCHEMA_API
    static bool
    IsPhysxForceFieldAPIPath(const SdfPath &path, TfToken *name);

    /// Applies this <b>multiple-apply</b> API schema to the given \p prim 
    /// along with the given instance name, \p name. 
    /// 
    /// This information is stored by adding "PhysxForceFieldAPI:<i>name</i>" 
    /// to the token-valued, listOp metadata \em apiSchemas on the prim.
    /// For example, if \p name is 'instance1', the token 
    /// 'PhysxForceFieldAPI:instance1' is added to 'apiSchemas'.
    /// 
    /// \return A valid ForceFieldSchemaPhysxForceFieldAPI object is returned upon success. 
    /// An invalid (or empty) ForceFieldSchemaPhysxForceFieldAPI object is returned upon 
    /// failure. See \ref UsdPrim::ApplyAPI() for 
    /// conditions resulting in failure. 
    /// 
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    FORCEFIELDSCHEMA_API
    static ForceFieldSchemaPhysxForceFieldAPI 
    Apply(const UsdPrim &prim, const TfToken &name);

protected:
    /// Returns the type of schema this class belongs to.
    ///
    /// \sa UsdSchemaType
    FORCEFIELDSCHEMA_API
    UsdSchemaType _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    FORCEFIELDSCHEMA_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    FORCEFIELDSCHEMA_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // ENABLED 
    // --------------------------------------------------------------------- //
    /// Enable or disable this ForceField. Overrides all other settings.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool physxForceField:enabled = 1` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    FORCEFIELDSCHEMA_API
    UsdAttribute GetEnabledAttr() const;

    /// See GetEnabledAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    FORCEFIELDSCHEMA_API
    UsdAttribute CreateEnabledAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // POSITION 
    // --------------------------------------------------------------------- //
    /// The location of the force field. Set to (0, 0, 0) to obtain the position
    /// from the prim and continuously update it if it is animated.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float3 physxForceField:position = (0, 0, 0)` |
    /// | C++ Type | GfVec3f |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float3 |
    FORCEFIELDSCHEMA_API
    UsdAttribute GetPositionAttr() const;

    /// See GetPositionAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    FORCEFIELDSCHEMA_API
    UsdAttribute CreatePositionAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // RANGE 
    // --------------------------------------------------------------------- //
    /// Forces are not applied when the distance to the force field is outside
    /// of this (minimum, maximum) range. Each force field can have a different 
    /// definition of distance, e.g. for a spherical fore field, the distance is 
    /// to the center, for a plane, the distance is to the closest point on the 
    /// surface, for a line, it is to the closest point on the line. The minimum
    /// or maximum range is ignored if the value is negative.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float2 physxForceField:range = (-1, -1)` |
    /// | C++ Type | GfVec2f |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float2 |
    FORCEFIELDSCHEMA_API
    UsdAttribute GetRangeAttr() const;

    /// See GetRangeAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    FORCEFIELDSCHEMA_API
    UsdAttribute CreateRangeAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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
