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
#ifndef FORCEFIELDSCHEMA_GENERATED_PHYSXFORCEFIELDDRAGAPI_H
#define FORCEFIELDSCHEMA_GENERATED_PHYSXFORCEFIELDDRAGAPI_H

/// \file forceFieldSchema/physxForceFieldDragAPI.h

#include "pxr/pxr.h"
#include "forceFieldSchema/api.h"
#include "forceFieldSchema/physxForceFieldAPI.h"
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
// PHYSXFORCEFIELDDRAGAPI                                                     //
// -------------------------------------------------------------------------- //

/// \class ForceFieldSchemaPhysxForceFieldDragAPI
///
/// A force field that slows rigid bodies by generating a force that is opposite to their velocity direction
/// using the forumula f = -linear * v - square * v^2.
///
class ForceFieldSchemaPhysxForceFieldDragAPI : public ForceFieldSchemaPhysxForceFieldAPI
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::MultipleApplyAPI;

    /// Construct a ForceFieldSchemaPhysxForceFieldDragAPI on UsdPrim \p prim with
    /// name \p name . Equivalent to
    /// ForceFieldSchemaPhysxForceFieldDragAPI::Get(
    ///    prim.GetStage(),
    ///    prim.GetPath().AppendProperty(
    ///        "physxForceField:name"));
    ///
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit ForceFieldSchemaPhysxForceFieldDragAPI(
        const UsdPrim& prim=UsdPrim(), const TfToken &name=TfToken())
        : ForceFieldSchemaPhysxForceFieldAPI(prim, /*instanceName*/ name)
    { }

    /// Construct a ForceFieldSchemaPhysxForceFieldDragAPI on the prim held by \p schemaObj with
    /// name \p name.  Should be preferred over
    /// ForceFieldSchemaPhysxForceFieldDragAPI(schemaObj.GetPrim(), name), as it preserves
    /// SchemaBase state.
    explicit ForceFieldSchemaPhysxForceFieldDragAPI(
        const UsdSchemaBase& schemaObj, const TfToken &name)
        : ForceFieldSchemaPhysxForceFieldAPI(schemaObj, /*instanceName*/ name)
    { }

    /// Destructor.
    FORCEFIELDSCHEMA_API
    virtual ~ForceFieldSchemaPhysxForceFieldDragAPI();

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

    /// Return a ForceFieldSchemaPhysxForceFieldDragAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  \p path must be of the format
    /// <path>.physxForceField:name .
    ///
    /// This is shorthand for the following:
    ///
    /// \code
    /// TfToken name = SdfPath::StripNamespace(path.GetToken());
    /// ForceFieldSchemaPhysxForceFieldDragAPI(
    ///     stage->GetPrimAtPath(path.GetPrimPath()), name);
    /// \endcode
    ///
    FORCEFIELDSCHEMA_API
    static ForceFieldSchemaPhysxForceFieldDragAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);

    /// Return a ForceFieldSchemaPhysxForceFieldDragAPI with name \p name holding the
    /// prim \p prim. Shorthand for ForceFieldSchemaPhysxForceFieldDragAPI(prim, name);
    FORCEFIELDSCHEMA_API
    static ForceFieldSchemaPhysxForceFieldDragAPI
    Get(const UsdPrim &prim, const TfToken &name);

    /// Checks if the given name \p baseName is the base name of a property
    /// of PhysxForceFieldDragAPI.
    FORCEFIELDSCHEMA_API
    static bool
    IsSchemaPropertyBaseName(const TfToken &baseName);

    /// Checks if the given path \p path is of an API schema of type
    /// PhysxForceFieldDragAPI. If so, it stores the instance name of
    /// the schema in \p name and returns true. Otherwise, it returns false.
    FORCEFIELDSCHEMA_API
    static bool
    IsPhysxForceFieldDragAPIPath(const SdfPath &path, TfToken *name);

    /// Applies this <b>multiple-apply</b> API schema to the given \p prim 
    /// along with the given instance name, \p name. 
    /// 
    /// This information is stored by adding "PhysxForceFieldDragAPI:<i>name</i>" 
    /// to the token-valued, listOp metadata \em apiSchemas on the prim.
    /// For example, if \p name is 'instance1', the token 
    /// 'PhysxForceFieldDragAPI:instance1' is added to 'apiSchemas'.
    /// 
    /// \return A valid ForceFieldSchemaPhysxForceFieldDragAPI object is returned upon success. 
    /// An invalid (or empty) ForceFieldSchemaPhysxForceFieldDragAPI object is returned upon 
    /// failure. See \ref UsdPrim::ApplyAPI() for 
    /// conditions resulting in failure. 
    /// 
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    FORCEFIELDSCHEMA_API
    static ForceFieldSchemaPhysxForceFieldDragAPI 
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
    // MINIMUMSPEED 
    // --------------------------------------------------------------------- //
    /// Drag forces are not applied below this minimum speed.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxForceFieldDrag:minimumSpeed = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    FORCEFIELDSCHEMA_API
    UsdAttribute GetMinimumSpeedAttr() const;

    /// See GetMinimumSpeedAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    FORCEFIELDSCHEMA_API
    UsdAttribute CreateMinimumSpeedAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // LINEAR 
    // --------------------------------------------------------------------- //
    /// linear sets a force that varies proportionally with the speed of the rigid body.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxForceFieldDrag:linear = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    FORCEFIELDSCHEMA_API
    UsdAttribute GetLinearAttr() const;

    /// See GetLinearAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    FORCEFIELDSCHEMA_API
    UsdAttribute CreateLinearAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // SQUARE 
    // --------------------------------------------------------------------- //
    /// square computes a force the varies with the square of the speed of the rigid body.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxForceFieldDrag:square = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    FORCEFIELDSCHEMA_API
    UsdAttribute GetSquareAttr() const;

    /// See GetSquareAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    FORCEFIELDSCHEMA_API
    UsdAttribute CreateSquareAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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
