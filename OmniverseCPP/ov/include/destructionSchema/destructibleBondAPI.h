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
#ifndef DESTRUCTIONSCHEMA_GENERATED_DESTRUCTIBLEBONDAPI_H
#define DESTRUCTIONSCHEMA_GENERATED_DESTRUCTIBLEBONDAPI_H

/// \file destructionSchema/destructibleBondAPI.h

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
// DESTRUCTIBLEBONDAPI                                                        //
// -------------------------------------------------------------------------- //

/// \class DestructionSchemaDestructibleBondAPI
///
/// When applied to a UsdGeomXformable descendant of a prim with the
/// DestructibleBaseAPI, this prim may be used to override, delete, or define
/// bonds between chunks.
///
class DestructionSchemaDestructibleBondAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::SingleApplyAPI;

    /// Construct a DestructionSchemaDestructibleBondAPI on UsdPrim \p prim .
    /// Equivalent to DestructionSchemaDestructibleBondAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit DestructionSchemaDestructibleBondAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a DestructionSchemaDestructibleBondAPI on the prim held by \p schemaObj .
    /// Should be preferred over DestructionSchemaDestructibleBondAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit DestructionSchemaDestructibleBondAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    DESTRUCTIONSCHEMA_API
    virtual ~DestructionSchemaDestructibleBondAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    DESTRUCTIONSCHEMA_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a DestructionSchemaDestructibleBondAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// DestructionSchemaDestructibleBondAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    DESTRUCTIONSCHEMA_API
    static DestructionSchemaDestructibleBondAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "DestructibleBondAPI" to the 
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    /// 
    /// \return A valid DestructionSchemaDestructibleBondAPI object is returned upon success. 
    /// An invalid (or empty) DestructionSchemaDestructibleBondAPI object is returned upon 
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions 
    /// resulting in failure. 
    /// 
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    DESTRUCTIONSCHEMA_API
    static DestructionSchemaDestructibleBondAPI 
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
    // CENTROID 
    // --------------------------------------------------------------------- //
    /// Optional bond centroid.  If not authored, the translation
    /// component of this prim's transform will be used as the centroid.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `point3f destruct:centroid = (-inf, -inf, -inf)` |
    /// | C++ Type | GfVec3f |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Point3f |
    DESTRUCTIONSCHEMA_API
    UsdAttribute GetCentroidAttr() const;

    /// See GetCentroidAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    DESTRUCTIONSCHEMA_API
    UsdAttribute CreateCentroidAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // NORMAL 
    // --------------------------------------------------------------------- //
    /// Optional bond normal.  If not authored, the Z-axis of the
    /// local frame defined by this prim's transform will be used as the
    /// normal.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `normal3f destruct:normal = (0, 0, 0)` |
    /// | C++ Type | GfVec3f |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Normal3f |
    DESTRUCTIONSCHEMA_API
    UsdAttribute GetNormalAttr() const;

    /// See GetNormalAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    DESTRUCTIONSCHEMA_API
    UsdAttribute CreateNormalAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // AREA 
    // --------------------------------------------------------------------- //
    /// Optional bond area.  If not authored, it will be calculated
    /// from the adjoining chunks.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float destruct:area = -inf` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    DESTRUCTIONSCHEMA_API
    UsdAttribute GetAreaAttr() const;

    /// See GetAreaAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    DESTRUCTIONSCHEMA_API
    UsdAttribute CreateAreaAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // STRENGTH 
    // --------------------------------------------------------------------- //
    /// The bond's strength.  Default value = -1.0.  If negative, the
    /// bond's area will be used.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float destruct:strength = -1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    DESTRUCTIONSCHEMA_API
    UsdAttribute GetStrengthAttr() const;

    /// See GetStrengthAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    DESTRUCTIONSCHEMA_API
    UsdAttribute CreateStrengthAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // UNBREAKABLE 
    // --------------------------------------------------------------------- //
    /// Whether or not the bond is unbreakable.
    /// Default value = false.  If true, the bond has effectively infinite
    /// strength.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool destruct:unbreakable = 0` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    DESTRUCTIONSCHEMA_API
    UsdAttribute GetUnbreakableAttr() const;

    /// See GetUnbreakableAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    DESTRUCTIONSCHEMA_API
    UsdAttribute CreateUnbreakableAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ATTACHED 
    // --------------------------------------------------------------------- //
    /// If two paths are given, at least one must be a chunk.  If the
    /// second path is also a chunk, the bond is internal.  Otherwise the
    /// second prim must be a rigid body collider and the bond is external.
    /// If only one path is given, the bond is external, attaching to the
    /// static world.
    ///
    DESTRUCTIONSCHEMA_API
    UsdRelationship GetAttachedRel() const;

    /// See GetAttachedRel(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create
    DESTRUCTIONSCHEMA_API
    UsdRelationship CreateAttachedRel() const;

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
