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
#ifndef DESTRUCTIONSCHEMA_TOKENS_H
#define DESTRUCTIONSCHEMA_TOKENS_H

/// \file destructionSchema/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// 
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
// 
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "pxr/pxr.h"
#include "destructionSchema/api.h"
#include "pxr/base/tf/staticData.h"
#include "pxr/base/tf/token.h"
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE


/// \class DestructionSchemaTokensType
///
/// \link DestructionSchemaTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// DestructionSchemaTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use DestructionSchemaTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(DestructionSchemaTokens->destructArea);
/// \endcode
struct DestructionSchemaTokensType {
    DESTRUCTIONSCHEMA_API DestructionSchemaTokensType();
    /// \brief "destruct:area"
    /// 
    /// DestructionSchemaDestructibleBondAPI
    const TfToken destructArea;
    /// \brief "destruct:attached"
    /// 
    /// DestructionSchemaDestructibleBondAPI
    const TfToken destructAttached;
    /// \brief "destruct:base"
    /// 
    /// DestructionSchemaDestructibleInstAPI
    const TfToken destructBase;
    /// \brief "destruct:centroid"
    /// 
    /// DestructionSchemaDestructibleBondAPI, DestructionSchemaDestructibleChunkAPI
    const TfToken destructCentroid;
    /// \brief "destruct:defaultBondStrength"
    /// 
    /// DestructionSchemaDestructibleBaseAPI
    const TfToken destructDefaultBondStrength;
    /// \brief "destruct:defaultChunkStrength"
    /// 
    /// DestructionSchemaDestructibleBaseAPI
    const TfToken destructDefaultChunkStrength;
    /// \brief "destruct:normal"
    /// 
    /// DestructionSchemaDestructibleBondAPI
    const TfToken destructNormal;
    /// \brief "destruct:parentChunk"
    /// 
    /// DestructionSchemaDestructibleChunkAPI
    const TfToken destructParentChunk;
    /// \brief "destruct:strength"
    /// 
    /// DestructionSchemaDestructibleBondAPI, DestructionSchemaDestructibleChunkAPI
    const TfToken destructStrength;
    /// \brief "destruct:supportDepth"
    /// 
    /// DestructionSchemaDestructibleBaseAPI
    const TfToken destructSupportDepth;
    /// \brief "destruct:unbreakable"
    /// 
    /// DestructionSchemaDestructibleBondAPI
    const TfToken destructUnbreakable;
    /// \brief "destruct:volume"
    /// 
    /// DestructionSchemaDestructibleChunkAPI
    const TfToken destructVolume;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var DestructionSchemaTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa DestructionSchemaTokensType
extern DESTRUCTIONSCHEMA_API TfStaticData<DestructionSchemaTokensType> DestructionSchemaTokens;

PXR_NAMESPACE_CLOSE_SCOPE

#endif
