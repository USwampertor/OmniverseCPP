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
#ifndef FORCEFIELDSCHEMA_TOKENS_H
#define FORCEFIELDSCHEMA_TOKENS_H

/// \file forceFieldSchema/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// 
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
// 
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "pxr/pxr.h"
#include "forceFieldSchema/api.h"
#include "pxr/base/tf/staticData.h"
#include "pxr/base/tf/token.h"
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE


/// \class ForceFieldSchemaTokensType
///
/// \link ForceFieldSchemaTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// ForceFieldSchemaTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use ForceFieldSchemaTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(ForceFieldSchemaTokens->forceFieldBodies);
/// \endcode
struct ForceFieldSchemaTokensType {
    FORCEFIELDSCHEMA_API ForceFieldSchemaTokensType();
    /// \brief "forceFieldBodies"
    /// 
    /// This token is the instance name used to label all of the PhysxForceField collecitonAPI's.
    const TfToken forceFieldBodies;
    /// \brief "physxForceField"
    /// 
    /// Property namespace prefix for the ForceFieldSchemaPhysxForceFieldSpinAPI schema., Property namespace prefix for the ForceFieldSchemaPhysxForceFieldWindAPI schema., Property namespace prefix for the ForceFieldSchemaPhysxForceFieldNoiseAPI schema., Property namespace prefix for the ForceFieldSchemaPhysxForceFieldDragAPI schema., Property namespace prefix for the ForceFieldSchemaPhysxForceFieldLinearAPI schema., Property namespace prefix for the ForceFieldSchemaPhysxForceFieldPlanarAPI schema., Property namespace prefix for the ForceFieldSchemaPhysxForceFieldSphericalAPI schema., Property namespace prefix for the ForceFieldSchemaPhysxForceFieldAPI schema.
    const TfToken physxForceField;
    /// \brief "physxForceFieldDrag:linear"
    /// 
    /// ForceFieldSchemaPhysxForceFieldDragAPI
    const TfToken physxForceFieldDragLinear;
    /// \brief "physxForceFieldDrag:minimumSpeed"
    /// 
    /// ForceFieldSchemaPhysxForceFieldDragAPI
    const TfToken physxForceFieldDragMinimumSpeed;
    /// \brief "physxForceFieldDrag:square"
    /// 
    /// ForceFieldSchemaPhysxForceFieldDragAPI
    const TfToken physxForceFieldDragSquare;
    /// \brief "physxForceField:enabled"
    /// 
    /// ForceFieldSchemaPhysxForceFieldAPI
    const TfToken physxForceFieldEnabled;
    /// \brief "physxForceFieldLinear:constant"
    /// 
    /// ForceFieldSchemaPhysxForceFieldLinearAPI
    const TfToken physxForceFieldLinearConstant;
    /// \brief "physxForceFieldLinear:direction"
    /// 
    /// ForceFieldSchemaPhysxForceFieldLinearAPI
    const TfToken physxForceFieldLinearDirection;
    /// \brief "physxForceFieldLinear:inverseSquare"
    /// 
    /// ForceFieldSchemaPhysxForceFieldLinearAPI
    const TfToken physxForceFieldLinearInverseSquare;
    /// \brief "physxForceFieldLinear:linear"
    /// 
    /// ForceFieldSchemaPhysxForceFieldLinearAPI
    const TfToken physxForceFieldLinearLinear;
    /// \brief "physxForceFieldNoise:amplitude"
    /// 
    /// ForceFieldSchemaPhysxForceFieldNoiseAPI
    const TfToken physxForceFieldNoiseAmplitude;
    /// \brief "physxForceFieldNoise:drag"
    /// 
    /// ForceFieldSchemaPhysxForceFieldNoiseAPI
    const TfToken physxForceFieldNoiseDrag;
    /// \brief "physxForceFieldNoise:frequency"
    /// 
    /// ForceFieldSchemaPhysxForceFieldNoiseAPI
    const TfToken physxForceFieldNoiseFrequency;
    /// \brief "physxForceFieldPlanar:constant"
    /// 
    /// ForceFieldSchemaPhysxForceFieldPlanarAPI
    const TfToken physxForceFieldPlanarConstant;
    /// \brief "physxForceFieldPlanar:inverseSquare"
    /// 
    /// ForceFieldSchemaPhysxForceFieldPlanarAPI
    const TfToken physxForceFieldPlanarInverseSquare;
    /// \brief "physxForceFieldPlanar:linear"
    /// 
    /// ForceFieldSchemaPhysxForceFieldPlanarAPI
    const TfToken physxForceFieldPlanarLinear;
    /// \brief "physxForceFieldPlanar:normal"
    /// 
    /// ForceFieldSchemaPhysxForceFieldPlanarAPI
    const TfToken physxForceFieldPlanarNormal;
    /// \brief "physxForceField:position"
    /// 
    /// ForceFieldSchemaPhysxForceFieldAPI
    const TfToken physxForceFieldPosition;
    /// \brief "physxForceField:range"
    /// 
    /// ForceFieldSchemaPhysxForceFieldAPI
    const TfToken physxForceFieldRange;
    /// \brief "physxForceFieldSpherical:constant"
    /// 
    /// ForceFieldSchemaPhysxForceFieldSphericalAPI
    const TfToken physxForceFieldSphericalConstant;
    /// \brief "physxForceFieldSpherical:inverseSquare"
    /// 
    /// ForceFieldSchemaPhysxForceFieldSphericalAPI
    const TfToken physxForceFieldSphericalInverseSquare;
    /// \brief "physxForceFieldSpherical:linear"
    /// 
    /// ForceFieldSchemaPhysxForceFieldSphericalAPI
    const TfToken physxForceFieldSphericalLinear;
    /// \brief "physxForceFieldSpin:constant"
    /// 
    /// ForceFieldSchemaPhysxForceFieldSpinAPI
    const TfToken physxForceFieldSpinConstant;
    /// \brief "physxForceFieldSpin:inverseSquare"
    /// 
    /// ForceFieldSchemaPhysxForceFieldSpinAPI
    const TfToken physxForceFieldSpinInverseSquare;
    /// \brief "physxForceFieldSpin:linear"
    /// 
    /// ForceFieldSchemaPhysxForceFieldSpinAPI
    const TfToken physxForceFieldSpinLinear;
    /// \brief "physxForceFieldSpin:spinAxis"
    /// 
    /// ForceFieldSchemaPhysxForceFieldSpinAPI
    const TfToken physxForceFieldSpinSpinAxis;
    /// \brief "physxForceFieldWind:averageDirection"
    /// 
    /// ForceFieldSchemaPhysxForceFieldWindAPI
    const TfToken physxForceFieldWindAverageDirection;
    /// \brief "physxForceFieldWind:averageSpeed"
    /// 
    /// ForceFieldSchemaPhysxForceFieldWindAPI
    const TfToken physxForceFieldWindAverageSpeed;
    /// \brief "physxForceFieldWind:directionVariation"
    /// 
    /// ForceFieldSchemaPhysxForceFieldWindAPI
    const TfToken physxForceFieldWindDirectionVariation;
    /// \brief "physxForceFieldWind:directionVariationFrequency"
    /// 
    /// ForceFieldSchemaPhysxForceFieldWindAPI
    const TfToken physxForceFieldWindDirectionVariationFrequency;
    /// \brief "physxForceFieldWind:drag"
    /// 
    /// ForceFieldSchemaPhysxForceFieldWindAPI
    const TfToken physxForceFieldWindDrag;
    /// \brief "physxForceFieldWind:speedVariation"
    /// 
    /// ForceFieldSchemaPhysxForceFieldWindAPI
    const TfToken physxForceFieldWindSpeedVariation;
    /// \brief "physxForceFieldWind:speedVariationFrequency"
    /// 
    /// ForceFieldSchemaPhysxForceFieldWindAPI
    const TfToken physxForceFieldWindSpeedVariationFrequency;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var ForceFieldSchemaTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa ForceFieldSchemaTokensType
extern FORCEFIELDSCHEMA_API TfStaticData<ForceFieldSchemaTokensType> ForceFieldSchemaTokens;

PXR_NAMESPACE_CLOSE_SCOPE

#endif
