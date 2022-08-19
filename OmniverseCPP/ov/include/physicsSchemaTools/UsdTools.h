// Copyright (c) 2019, NVIDIA CORPORATION.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.
//
#pragma once

#include "pxr/pxr.h"
#include ".//api.h"
#include "pxr/usd/usd/typed.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usdGeom/mesh.h"
#include "pxr/usd/usdGeom/xform.h"

#include "pxr/usd/sdf/path.h"

#include "pxr/base/vt/value.h"

#include "pxr/base/gf/vec3d.h"
#include "pxr/base/gf/vec3f.h"
#include "pxr/base/gf/matrix4d.h"

#include "pxr/base/tf/token.h"
#include "pxr/base/tf/type.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

// Meshes
PHYSICSSCHEMATOOLS_API
UsdGeomMesh createMesh(const UsdStagePtr& stage,
    const SdfPath& path,
    const std::vector<GfVec3f>& points,
    const std::vector<GfVec3f>& normals,
    const std::vector<int>& indices,
    const std::vector<int>& vertexCounts);

PHYSICSSCHEMATOOLS_API
UsdGeomMesh createMeshSquare(const UsdStagePtr& stage, const pxr::SdfPath& path, float halfHeight, float halfWidth);

PHYSICSSCHEMATOOLS_API
UsdGeomMesh createMeshBox(const UsdStagePtr& stage, const pxr::SdfPath& path, const pxr::GfVec3f& halfExtent = { 1, 1, 1 });

PHYSICSSCHEMATOOLS_API
UsdGeomMesh createMeshSphere(const UsdStagePtr& stage,
    const pxr::SdfPath& path,
    float radius,
    int latitudeSegments = 16,
    int longitudeSegments = 32);

PHYSICSSCHEMATOOLS_API
UsdGeomMesh createMeshCapsule(const UsdStagePtr& stage,
    const pxr::SdfPath& path,
    float radius,
    float halfHeight,
    int latitudeSegments = 16,
    int longitudeSegments = 32);

PHYSICSSCHEMATOOLS_API
UsdGeomMesh createMeshCylinder(
    const UsdStagePtr& stage, const pxr::SdfPath& path, float radius, float halfLength, uint32_t tesselation);

// Add USD schema for basic stuffs
PHYSICSSCHEMATOOLS_API
void addPhysicsScene(const UsdStagePtr& stage, const std::string& path);

PHYSICSSCHEMATOOLS_API
UsdGeomXform addActor(const UsdStagePtr& stage, const std::string& path);

PHYSICSSCHEMATOOLS_API
UsdGeomXform addCollisionShape(const UsdStagePtr& stage, const std::string& path);

PHYSICSSCHEMATOOLS_API
void addRigidBody(const UsdStagePtr& stage, const std::string& path);

PHYSICSSCHEMATOOLS_API
void addPosition(UsdGeomXformable& xformable, const pxr::GfVec3f& position);

PHYSICSSCHEMATOOLS_API
void addOrientation(UsdGeomXformable& xformable, const pxr::GfQuatf& orientation);

PHYSICSSCHEMATOOLS_API
void addDisplayColor(pxr::UsdGeomGprim& gprim, const pxr::GfVec3f& color);

PHYSICSSCHEMATOOLS_API
void addVelocity(const UsdStagePtr& stage,
    const std::string& path,
    const pxr::GfVec3f& linearVelocity,
    const pxr::GfVec3f& angularVelocity);

PHYSICSSCHEMATOOLS_API
void addDensity(const UsdStagePtr& stage, const std::string& path, float value);

PHYSICSSCHEMATOOLS_API
void addBoxCollisionShape(const UsdStagePtr& stage,
    const std::string& path,
    float size,
    const pxr::GfVec3f& position,
    const pxr::GfQuatf& orientation,
    const pxr::GfVec3f& color);

PHYSICSSCHEMATOOLS_API
void addGroundPlane(const UsdStagePtr& stage,
    const std::string& path,
	const pxr::TfToken& axis = TfToken("Z"),
    float size = 100.0f,
    const pxr::GfVec3f& position = pxr::GfVec3f(0.0f),
    const pxr::GfVec3f& color = pxr::GfVec3f(0.5f));

PHYSICSSCHEMATOOLS_API
void addGroundTriMesh(const UsdStagePtr& stage,
    const std::string& path,
    float size = 100.0f,
    const pxr::GfVec3f& position = pxr::GfVec3f(0.0f),
    const pxr::GfVec3f& color = pxr::GfVec3f(0.5f));

PHYSICSSCHEMATOOLS_API
void addRigidBox(const UsdStagePtr& stage,
    const std::string& path,
    const pxr::GfVec3f& size,
    const pxr::GfVec3f& position,
    const pxr::GfQuatf& orientation,
    const pxr::GfVec3f& color,
    float density,
    const pxr::GfVec3f& linVelocity = pxr::GfVec3f(0.0f),
    const pxr::GfVec3f& angularVelocity = pxr::GfVec3f(0.0f));

PHYSICSSCHEMATOOLS_API
void addRigidSphere(const UsdStagePtr& stage,
    const std::string& path,
    float radius,
    const pxr::GfVec3f& position,
    const pxr::GfQuatf& orientation,
    const pxr::GfVec3f& color,
    float density,
    const pxr::GfVec3f& linVelocity = pxr::GfVec3f(0.0f),
    const pxr::GfVec3f& angularVelocity = pxr::GfVec3f(0.0f));

PHYSICSSCHEMATOOLS_API
void addRigidCapsule(const UsdStagePtr& stage,
    const std::string& path,
    float radius,
    float halfHeight,
	const pxr::TfToken& axis,
    const pxr::GfVec3f& position,
    const pxr::GfQuatf& orientation,
    const pxr::GfVec3f& color,
    float density,
    const pxr::GfVec3f& linVelocity = pxr::GfVec3f(0.0f),
    const pxr::GfVec3f& angularVelocity = pxr::GfVec3f(0.0f));

PHYSICSSCHEMATOOLS_API
void addRigidCylinder(const UsdStagePtr& stage,
    const std::string& path,
    float radius,
    float halfHeight,
	const pxr::TfToken& axis,
    const pxr::GfVec3f& position,
    const pxr::GfQuatf& orientation,
    const pxr::GfVec3f& color,
    float density,
    const pxr::GfVec3f& linVelocity = pxr::GfVec3f(0.0f),
    const pxr::GfVec3f& angularVelocity = pxr::GfVec3f(0.0f));

PHYSICSSCHEMATOOLS_API
void addRigidCone(const UsdStagePtr& stage,
	const std::string& path,
	float radius,
	float halfHeight,
	const pxr::TfToken& axis,
	const pxr::GfVec3f& position,
	const pxr::GfQuatf& orientation,
	const pxr::GfVec3f& color,
	float density,
	const pxr::GfVec3f& linVelocity = pxr::GfVec3f(0.0f),
	const pxr::GfVec3f& angularVelocity = pxr::GfVec3f(0.0f));

PHYSICSSCHEMATOOLS_API
void addRigidBoxForInstancing(const UsdStagePtr& stage,
    const std::string& path,
    const pxr::GfVec3f& size,
    const pxr::GfVec3f& color,
    float density);

PHYSICSSCHEMATOOLS_API
void encodeSdfPath(const SdfPath& path, uint32_t& ePart0, uint32_t& ePart1);

PHYSICSSCHEMATOOLS_API
SdfPath decodeSdfPath(const uint32_t ePart0, const uint32_t ePart1);

PHYSICSSCHEMATOOLS_API
uint64_t sdfPathToInt(const SdfPath& path);

PHYSICSSCHEMATOOLS_API
SdfPath intToSdfPath(const uint64_t intPath);

PXR_NAMESPACE_CLOSE_SCOPE