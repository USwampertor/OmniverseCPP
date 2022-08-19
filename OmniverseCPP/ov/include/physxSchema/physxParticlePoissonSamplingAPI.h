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
#ifndef PHYSXSCHEMA_GENERATED_PHYSXPARTICLEPOISSONSAMPLINGAPI_H
#define PHYSXSCHEMA_GENERATED_PHYSXPARTICLEPOISSONSAMPLINGAPI_H

/// \file physxSchema/physxParticlePoissonSamplingAPI.h

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
// PHYSXPARTICLEPOISSONSAMPLINGAPI                                            //
// -------------------------------------------------------------------------- //

/// \class PhysxSchemaPhysxParticlePoissonSamplingAPI
///
/// Applied to a UsdGeomMesh which is Poisson-sampled to generate particles in the particles relationship.
///
class PhysxSchemaPhysxParticlePoissonSamplingAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::SingleApplyAPI;

    /// Construct a PhysxSchemaPhysxParticlePoissonSamplingAPI on UsdPrim \p prim .
    /// Equivalent to PhysxSchemaPhysxParticlePoissonSamplingAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit PhysxSchemaPhysxParticlePoissonSamplingAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a PhysxSchemaPhysxParticlePoissonSamplingAPI on the prim held by \p schemaObj .
    /// Should be preferred over PhysxSchemaPhysxParticlePoissonSamplingAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit PhysxSchemaPhysxParticlePoissonSamplingAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    PHYSXSCHEMA_API
    virtual ~PhysxSchemaPhysxParticlePoissonSamplingAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    PHYSXSCHEMA_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a PhysxSchemaPhysxParticlePoissonSamplingAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// PhysxSchemaPhysxParticlePoissonSamplingAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    PHYSXSCHEMA_API
    static PhysxSchemaPhysxParticlePoissonSamplingAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "PhysxParticlePoissonSamplingAPI" to the 
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    /// 
    /// \return A valid PhysxSchemaPhysxParticlePoissonSamplingAPI object is returned upon success. 
    /// An invalid (or empty) PhysxSchemaPhysxParticlePoissonSamplingAPI object is returned upon 
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions 
    /// resulting in failure. 
    /// 
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    PHYSXSCHEMA_API
    static PhysxSchemaPhysxParticlePoissonSamplingAPI 
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
    // SAMPLINGDISTANCE 
    // --------------------------------------------------------------------- //
    /// The distance between the sampled positions. In general, choose a value larger than the corresponding particle rest offset.
    /// Default value zero means that a suitable value is auto-determined.
    /// Range: [0, inf)
    /// Units: distance
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float physxParticlePoissonSampling:samplingDistance = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetSamplingDistanceAttr() const;

    /// See GetSamplingDistanceAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateSamplingDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // VOLUME 
    // --------------------------------------------------------------------- //
    /// Whether to sample points inside the mesh or not.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool physxParticlePoissonSampling:volume = 0` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    PHYSXSCHEMA_API
    UsdAttribute GetVolumeAttr() const;

    /// See GetVolumeAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateVolumeAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // MAXSAMPLES 
    // --------------------------------------------------------------------- //
    /// Approximate upper bound on the number of samples. Zero means unbounded.
    /// Range: [0, inf)
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int physxParticlePoissonSampling:maxSamples = 50000` |
    /// | C++ Type | int |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Int |
    PHYSXSCHEMA_API
    UsdAttribute GetMaxSamplesAttr() const;

    /// See GetMaxSamplesAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateMaxSamplesAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // PARTICLES 
    // --------------------------------------------------------------------- //
    /// Relationship to the particle set sampled from the mesh.
    ///
    PHYSXSCHEMA_API
    UsdRelationship GetParticlesRel() const;

    /// See GetParticlesRel(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create
    PHYSXSCHEMA_API
    UsdRelationship CreateParticlesRel() const;

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
