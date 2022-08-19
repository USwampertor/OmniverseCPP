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
#ifndef DESTRUCTIONSCHEMA_GENERATED_DESTRUCTIBLEBASEAPI_H
#define DESTRUCTIONSCHEMA_GENERATED_DESTRUCTIBLEBASEAPI_H

/// \file destructionSchema/destructibleBaseAPI.h

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
// DESTRUCTIBLEBASEAPI                                                        //
// -------------------------------------------------------------------------- //

/// \class DestructionSchemaDestructibleBaseAPI
///
/// Applies destructible attributes to any UsdGeomXformable prim
/// and allows mesh descendants to be used to author destruction.
///
class DestructionSchemaDestructibleBaseAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::SingleApplyAPI;

    /// Construct a DestructionSchemaDestructibleBaseAPI on UsdPrim \p prim .
    /// Equivalent to DestructionSchemaDestructibleBaseAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit DestructionSchemaDestructibleBaseAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a DestructionSchemaDestructibleBaseAPI on the prim held by \p schemaObj .
    /// Should be preferred over DestructionSchemaDestructibleBaseAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit DestructionSchemaDestructibleBaseAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    DESTRUCTIONSCHEMA_API
    virtual ~DestructionSchemaDestructibleBaseAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    DESTRUCTIONSCHEMA_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a DestructionSchemaDestructibleBaseAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// DestructionSchemaDestructibleBaseAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    DESTRUCTIONSCHEMA_API
    static DestructionSchemaDestructibleBaseAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "DestructibleBaseAPI" to the 
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    /// 
    /// \return A valid DestructionSchemaDestructibleBaseAPI object is returned upon success. 
    /// An invalid (or empty) DestructionSchemaDestructibleBaseAPI object is returned upon 
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions 
    /// resulting in failure. 
    /// 
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    DESTRUCTIONSCHEMA_API
    static DestructionSchemaDestructibleBaseAPI 
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
    // SUPPORTDEPTH 
    // --------------------------------------------------------------------- //
    /// Desired chunk depth for support graph representation.
    /// Leaves that are shallower than this depth and non-leaves at this depth
    /// will be support chunks and may be bonded together using bonds.  The
    /// setting will make leaf chunks the support chunks.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int destruct:supportDepth = 2147483647` |
    /// | C++ Type | int |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Int |
    DESTRUCTIONSCHEMA_API
    UsdAttribute GetSupportDepthAttr() const;

    /// See GetSupportDepthAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    DESTRUCTIONSCHEMA_API
    UsdAttribute CreateSupportDepthAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // DEFAULTBONDSTRENGTH 
    // --------------------------------------------------------------------- //
    /// Default value to use for all bonds in the destructible.
    /// If not authored, use individual bond strength values.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float destruct:defaultBondStrength = -1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    DESTRUCTIONSCHEMA_API
    UsdAttribute GetDefaultBondStrengthAttr() const;

    /// See GetDefaultBondStrengthAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    DESTRUCTIONSCHEMA_API
    UsdAttribute CreateDefaultBondStrengthAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // DEFAULTCHUNKSTRENGTH 
    // --------------------------------------------------------------------- //
    /// Default value to use for all chunks in the destructible.
    /// If not authored, use individual chunk strength values.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float destruct:defaultChunkStrength = -1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    DESTRUCTIONSCHEMA_API
    UsdAttribute GetDefaultChunkStrengthAttr() const;

    /// See GetDefaultChunkStrengthAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    DESTRUCTIONSCHEMA_API
    UsdAttribute CreateDefaultChunkStrengthAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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
