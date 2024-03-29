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
#ifndef DESTRUCTIONSCHEMA_GENERATED_DESTRUCTIBLEINSTAPI_H
#define DESTRUCTIONSCHEMA_GENERATED_DESTRUCTIBLEINSTAPI_H

/// \file destructionSchema/destructibleInstAPI.h

#include "pxr/pxr.h"
#include "destructionSchema/api.h"
#include "pxr/usd/usd/apiSchemaBase.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/stage.h"
#include "destructionSchema/tokens.h"

#include "pxr/base/vt/value.h"

#include "pxr/base/gf/vec3d.h"
#include "pxr/base/gf/vec3f.h"
#include "pxr/base/gf/matrix4d.h"

#include "pxr/base/tf/token.h"
#include "pxr/base/tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// DESTRUCTIBLEINSTAPI                                                        //
// -------------------------------------------------------------------------- //

/// \class DestructionSchemaDestructibleInstAPI
///
/// When applied to a UsdGeomXformable, it creates a destructible
/// instance based off of the geometry and attributes defined by a referenced
/// DestructibleBaseAPI.
///
class DestructionSchemaDestructibleInstAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::SingleApplyAPI;

    /// Construct a DestructionSchemaDestructibleInstAPI on UsdPrim \p prim .
    /// Equivalent to DestructionSchemaDestructibleInstAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit DestructionSchemaDestructibleInstAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a DestructionSchemaDestructibleInstAPI on the prim held by \p schemaObj .
    /// Should be preferred over DestructionSchemaDestructibleInstAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit DestructionSchemaDestructibleInstAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    DESTRUCTIONSCHEMA_API
    virtual ~DestructionSchemaDestructibleInstAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    DESTRUCTIONSCHEMA_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a DestructionSchemaDestructibleInstAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// DestructionSchemaDestructibleInstAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    DESTRUCTIONSCHEMA_API
    static DestructionSchemaDestructibleInstAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "DestructibleInstAPI" to the 
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    /// 
    /// \return A valid DestructionSchemaDestructibleInstAPI object is returned upon success. 
    /// An invalid (or empty) DestructionSchemaDestructibleInstAPI object is returned upon 
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions 
    /// resulting in failure. 
    /// 
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    DESTRUCTIONSCHEMA_API
    static DestructionSchemaDestructibleInstAPI 
    Apply(const UsdPrim &prim);

protected:
    /// Returns the type of schema this class belongs to.
    ///
    /// \sa UsdSchemaType
    DESTRUCTIONSCHEMA_API
    UsdSchemaType _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    DESTRUCTIONSCHEMA_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    DESTRUCTIONSCHEMA_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // BASE 
    // --------------------------------------------------------------------- //
    /// The referenced destructible base
    /// (see DestructibleBaseAPI).
    ///
    DESTRUCTIONSCHEMA_API
    UsdRelationship GetBaseRel() const;

    /// See GetBaseRel(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create
    DESTRUCTIONSCHEMA_API
    UsdRelationship CreateBaseRel() const;

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
