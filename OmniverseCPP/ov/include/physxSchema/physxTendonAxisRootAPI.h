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
#ifndef PHYSXSCHEMA_GENERATED_PHYSXTENDONAXISROOTAPI_H
#define PHYSXSCHEMA_GENERATED_PHYSXTENDONAXISROOTAPI_H

/// \file physxSchema/physxTendonAxisRootAPI.h

#include "pxr/pxr.h"
#include ".//api.h"
#include ".//physxTendonAxisAPI.h"
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
// PHYSXTENDONAXISROOTAPI                                                     //
// -------------------------------------------------------------------------- //

/// \class PhysxSchemaPhysxTendonAxisRootAPI
///
/// WARNING: Draft API, this design is not fixed and may change in the future. At this point, we don't support
/// multi-axis joints (e.g. spherical, D6) or 0-DOF joints (fixed joints) yet.
/// 
/// Applied to a Physics Joint that must be part of an articulation, e.g. PhysicsRevoluteJoint or PhysicsPrismaticJoint.
/// 
/// In addition to creating a regular axis of the fixed tendon, the root API provides attributes that apply to the
/// entire tendon. The root API must be applied to the joint that is the common ancestor of all joint axes in the tendon.
/// 
/// For restrictions on tendon structure and grouping of axes into tendons, see PhysxTendonAxisAPI.
/// 
/// Details on dynamics:
/// 
/// Fixed tendons create an abstract coupling between degrees of freedom of an articulation. Each tendon axis is
/// associated with an articulation joint and a specific joint axis, i.e. degree of freedom. Since
/// the joint axes in the tendon must follow the articulation with the root axis as the common ancestor, the tendon
/// mirrors the articulation's tree structure. This tree structure is key for the computation of the constraint forces
/// applied by the tendon on the articulation links.
/// 
/// The length of the fixed tendon at a given axis is evaluated recursively as
/// 
/// tendonLength[i] = tendonLength[i - 1] + gearing[i] * jointPosition[i]
/// 
/// where gearing[i] and jointPosition[i] refer to the i-th tendon axis gearing and corresponding joint axis position in
/// degrees (rotational) or distance units (translational), and tendonLength[i - 1] is the length at the parent tendon
/// axis in the tendon tree. Note that since the tendon length is an abstract construct as a weighted sum of joint
/// positions, negative 'lengths' are possible.
/// 
/// For the root axis, we define the tendon length to be
/// 
/// tendonLength[0] = offset + gearing[0] * jointPosition[0]
/// 
/// i.e. the parent length for the root is set to the offset attribute.
/// 
/// Before we can define the fixed-tendon constraint forces, we define the tendon-axis velocity v[i] that damping is
/// acting on. The velocity v[i] is the velocity of the virtual joint between the child link of the tendon axis'
/// articulation joint and the articulation parent link of the tendon's root-axis joint:
/// 
/// v[i] = vChild[i] - vRoot
/// 
/// where vChild[i] is the velocity of the child link projected onto the tendon-joint axis, and, analogously, vRoot is the
/// root-axis' parent link's velocity projected onto the root axis. For example, consider an articulation with three links
/// connected by two revolute joints, and the first link is a fixed base. The first revolute joint is the root axis of the
/// tendon, and the second axis is between the two moving links. Then, the root-tendon-axis velocity v[0] is equal to the
/// velocity of its joint, and the second tendon-axis velocity is equal to the angular velocity of the third link, since
/// the parent link of the root axis is fixed and has angular velocity zero (i.e. vRoot = 0).
/// 
/// Now we can define the constraint force (or torque) applied at the i-th axis
/// 
/// f[i] = sgn(gearing[i]) * (stiffness * (restLength - tendonLength[i]) + limitForce[i]) - damping * v[i]
/// 
/// where the signum on the gearing ensures that the force or torque is in the deviation-reducing direction, and the
/// limitForce[i] is an additional force from user-set limits on the tendon length. In particular, it is
/// 
/// limitForce[i] = limitStiffness * (upperLimit - tendonLength[i])  *if*  tendonLength[i] > upperLimit
/// limitForce[i] = limitStiffness * (lowerLimit - tendonLength[i])  *if*  tendonLength[i] < lowerLimit
/// limitForce[i] = 0  *otherwise*.
/// 
/// Setting stiffness to zero allows implementing one-sided constraints using the limit parameters.
/// 
/// Finally, a reaction force/torque equal and opposing f[i] is applied to the tendon root axis' parent link according to
/// the type of the root-joint axis.
/// 
/// 
///
class PhysxSchemaPhysxTendonAxisRootAPI : public PhysxSchemaPhysxTendonAxisAPI
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::MultipleApplyAPI;

    /// Construct a PhysxSchemaPhysxTendonAxisRootAPI on UsdPrim \p prim with
    /// name \p name . Equivalent to
    /// PhysxSchemaPhysxTendonAxisRootAPI::Get(
    ///    prim.GetStage(),
    ///    prim.GetPath().AppendProperty(
    ///        "physxTendon:name"));
    ///
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit PhysxSchemaPhysxTendonAxisRootAPI(
        const UsdPrim& prim=UsdPrim(), const TfToken &name=TfToken())
        : PhysxSchemaPhysxTendonAxisAPI(prim, /*instanceName*/ name)
    { }

    /// Construct a PhysxSchemaPhysxTendonAxisRootAPI on the prim held by \p schemaObj with
    /// name \p name.  Should be preferred over
    /// PhysxSchemaPhysxTendonAxisRootAPI(schemaObj.GetPrim(), name), as it preserves
    /// SchemaBase state.
    explicit PhysxSchemaPhysxTendonAxisRootAPI(
        const UsdSchemaBase& schemaObj, const TfToken &name)
        : PhysxSchemaPhysxTendonAxisAPI(schemaObj, /*instanceName*/ name)
    { }

    /// Destructor.
    PHYSXSCHEMA_API
    virtual ~PhysxSchemaPhysxTendonAxisRootAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes for a given instance name.  Does not
    /// include attributes that may be authored by custom/extended methods of
    /// the schemas involved. The names returned will have the proper namespace
    /// prefix.
    PHYSXSCHEMA_API
    static const TfTokenVector &
    GetSchemaAttributeNames(
        bool includeInherited=true, const TfToken instanceName=TfToken());

    /// Returns the name of this multiple-apply schema instance
    TfToken GetName() const {
        return _GetInstanceName();
    }

    /// Return a PhysxSchemaPhysxTendonAxisRootAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  \p path must be of the format
    /// <path>.physxTendon:name .
    ///
    /// This is shorthand for the following:
    ///
    /// \code
    /// TfToken name = SdfPath::StripNamespace(path.GetToken());
    /// PhysxSchemaPhysxTendonAxisRootAPI(
    ///     stage->GetPrimAtPath(path.GetPrimPath()), name);
    /// \endcode
    ///
    PHYSXSCHEMA_API
    static PhysxSchemaPhysxTendonAxisRootAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);

    /// Return a PhysxSchemaPhysxTendonAxisRootAPI with name \p name holding the
    /// prim \p prim. Shorthand for PhysxSchemaPhysxTendonAxisRootAPI(prim, name);
    PHYSXSCHEMA_API
    static PhysxSchemaPhysxTendonAxisRootAPI
    Get(const UsdPrim &prim, const TfToken &name);

    /// Checks if the given name \p baseName is the base name of a property
    /// of PhysxTendonAxisRootAPI.
    PHYSXSCHEMA_API
    static bool
    IsSchemaPropertyBaseName(const TfToken &baseName);

    /// Checks if the given path \p path is of an API schema of type
    /// PhysxTendonAxisRootAPI. If so, it stores the instance name of
    /// the schema in \p name and returns true. Otherwise, it returns false.
    PHYSXSCHEMA_API
    static bool
    IsPhysxTendonAxisRootAPIPath(const SdfPath &path, TfToken *name);

    /// Applies this <b>multiple-apply</b> API schema to the given \p prim 
    /// along with the given instance name, \p name. 
    /// 
    /// This information is stored by adding "PhysxTendonAxisRootAPI:<i>name</i>" 
    /// to the token-valued, listOp metadata \em apiSchemas on the prim.
    /// For example, if \p name is 'instance1', the token 
    /// 'PhysxTendonAxisRootAPI:instance1' is added to 'apiSchemas'.
    /// 
    /// \return A valid PhysxSchemaPhysxTendonAxisRootAPI object is returned upon success. 
    /// An invalid (or empty) PhysxSchemaPhysxTendonAxisRootAPI object is returned upon 
    /// failure. See \ref UsdPrim::ApplyAPI() for 
    /// conditions resulting in failure. 
    /// 
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    PHYSXSCHEMA_API
    static PhysxSchemaPhysxTendonAxisRootAPI 
    Apply(const UsdPrim &prim, const TfToken &name);

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
    // STIFFNESS 
    // --------------------------------------------------------------------- //
    /// Tendon length spring stiffness. Range [0, inf).
    /// Units: force / distance = mass / time / time
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float stiffness = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetStiffnessAttr() const;

    /// See GetStiffnessAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateStiffnessAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // DAMPING 
    // --------------------------------------------------------------------- //
    /// Tendon length damping.  Range [0, inf).
    /// Units: force / distance * time = mass / time
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float damping = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetDampingAttr() const;

    /// See GetDampingAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateDampingAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // LIMITSTIFFNESS 
    // --------------------------------------------------------------------- //
    /// Tendon length-limit spring stiffness. Range [0, inf).
    /// Units: force / distance = mass / time / time
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float limitStiffness = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetLimitStiffnessAttr() const;

    /// See GetLimitStiffnessAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateLimitStiffnessAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // OFFSET 
    // --------------------------------------------------------------------- //
    /// Tendon length offset. Range (-inf, inf).
    /// Units: distance
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float offset = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetOffsetAttr() const;

    /// See GetOffsetAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateOffsetAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // RESTLENGTH 
    // --------------------------------------------------------------------- //
    /// Tendon rest length. Range (-inf, inf).
    /// Units: distance
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float restLength = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetRestLengthAttr() const;

    /// See GetRestLengthAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateRestLengthAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // LOWERLIMIT 
    // --------------------------------------------------------------------- //
    /// Tendon length lower limit. Range (-inf, upperLimit].
    /// Units: distance
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float lowerLimit = -inf` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetLowerLimitAttr() const;

    /// See GetLowerLimitAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateLowerLimitAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // UPPERLIMIT 
    // --------------------------------------------------------------------- //
    /// Tendon length upper limit. Range [lowerLimit, inf).
    /// Units: distance
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float upperLimit = inf` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    PHYSXSCHEMA_API
    UsdAttribute GetUpperLimitAttr() const;

    /// See GetUpperLimitAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateUpperLimitAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TENDONENABLED 
    // --------------------------------------------------------------------- //
    /// Enables/disables the tendon from contributing to the articulation dynamics.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool tendonEnabled = 1` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    PHYSXSCHEMA_API
    UsdAttribute GetTendonEnabledAttr() const;

    /// See GetTendonEnabledAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    PHYSXSCHEMA_API
    UsdAttribute CreateTendonEnabledAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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
