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
#ifndef PHYSXSCHEMA_TOKENS_H
#define PHYSXSCHEMA_TOKENS_H

/// \file physxSchema/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// 
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
// 
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "pxr/pxr.h"
#include ".//api.h"
#include "pxr/base/tf/staticData.h"
#include "pxr/base/tf/token.h"
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE


/// \class PhysxSchemaTokensType
///
/// \link PhysxSchemaTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// PhysxSchemaTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use PhysxSchemaTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(PhysxSchemaTokens->acceleration);
/// \endcode
struct PhysxSchemaTokensType {
    PHYSXSCHEMA_API PhysxSchemaTokensType();
    /// \brief "acceleration"
    /// 
    /// Possible value for PhysxSchemaPhysxVehicleContextAPI::GetPhysxVehicleContextUpdateModeAttr()
    const TfToken acceleration;
    /// \brief "actor0"
    /// 
    /// PhysxSchemaPhysxPhysicsAttachment
    const TfToken actor0;
    /// \brief "actor1"
    /// 
    /// PhysxSchemaPhysxPhysicsAttachment
    const TfToken actor1;
    /// \brief "anisotropyMax"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken anisotropyMax;
    /// \brief "anisotropyMin"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken anisotropyMin;
    /// \brief "anisotropyScale"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken anisotropyScale;
    /// \brief "attachmentEnabled"
    /// 
    /// PhysxSchemaPhysxPhysicsAttachment
    const TfToken attachmentEnabled;
    /// \brief "average"
    /// 
    /// Possible value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialFrictionCombineModeAttr(), Default value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialFrictionCombineModeAttr(), Possible value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialRestitutionCombineModeAttr(), Default value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialRestitutionCombineModeAttr()
    const TfToken average;
    /// \brief "axis"
    /// 
    /// PhysxSchemaPlane
    const TfToken axis;
    /// \brief "bounceThreshold"
    /// 
    /// PhysxSchemaPhysxLimitAPI
    const TfToken bounceThreshold;
    /// \brief "buffer"
    /// 
    /// PhysxSchemaPhysxCookedDataAPI
    const TfToken buffer;
    /// \brief "clothConstaint"
    /// 
    ///  This token represents the collection name to use with PhysxCookedDataAPI to represent cooked data of a clothConstaint. 
    const TfToken clothConstaint;
    /// \brief "collisionFilterIndices0"
    /// 
    /// PhysxSchemaPhysxPhysicsAttachment
    const TfToken collisionFilterIndices0;
    /// \brief "collisionFilterIndices1"
    /// 
    /// PhysxSchemaPhysxPhysicsAttachment
    const TfToken collisionFilterIndices1;
    /// \brief "constrained"
    /// 
    /// Possible value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerClimbingModeAttr()
    const TfToken constrained;
    /// \brief "contactDistance"
    /// 
    /// PhysxSchemaPhysxLimitAPI
    const TfToken contactDistance;
    /// \brief "contactOffset"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken contactOffset;
    /// \brief "convexDecomposition"
    /// 
    ///  This token represents the collection name to use with PhysxCookedDataAPI to represent cooked data of a convexDecomposition. 
    const TfToken convexDecomposition;
    /// \brief "convexHull"
    /// 
    ///  This token represents the collection name to use with PhysxCookedDataAPI to represent cooked data of a convexhull. 
    const TfToken convexHull;
    /// \brief "damping"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentRootAPI, PhysxSchemaPhysxTendonAxisRootAPI, PhysxSchemaPhysxLimitAPI
    const TfToken damping;
    /// \brief "easy"
    /// 
    /// Possible value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerClimbingModeAttr(), Default value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerClimbingModeAttr()
    const TfToken easy;
    /// \brief "enableAnisotropy"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken enableAnisotropy;
    /// \brief "enableCCD"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken enableCCD;
    /// \brief "filterType0"
    /// 
    /// PhysxSchemaPhysxPhysicsAttachment
    const TfToken filterType0;
    /// \brief "filterType1"
    /// 
    /// PhysxSchemaPhysxPhysicsAttachment
    const TfToken filterType1;
    /// \brief "fluidRestOffset"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken fluidRestOffset;
    /// \brief "frictionValues"
    /// 
    /// PhysxSchemaPhysxVehicleTireFrictionTable
    const TfToken frictionValues;
    /// \brief "gearing"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentAPI, PhysxSchemaPhysxTendonAxisAPI
    const TfToken gearing;
    /// \brief "Geometry"
    /// 
    /// Possible value for PhysxSchemaPhysxPhysicsAttachment::GetFilterType0Attr(), Possible value for PhysxSchemaPhysxPhysicsAttachment::GetFilterType1Attr()
    const TfToken geometry;
    /// \brief "GINGOLD_XPBD"
    /// 
    /// Possible value for PhysxSchemaPhysxDeformableSurfaceAPI::GetPhysxDeformableSolverAlgorithmAttr()
    const TfToken gINGOLD_XPBD;
    /// \brief "globalSelfCollisionEnabled"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken globalSelfCollisionEnabled;
    /// \brief "GPU"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneBroadphaseTypeAttr(), Default value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneBroadphaseTypeAttr()
    const TfToken gPU;
    /// \brief "groundMaterials"
    /// 
    /// PhysxSchemaPhysxVehicleTireFrictionTable
    const TfToken groundMaterials;
    /// \brief "indices"
    /// 
    /// PhysxSchemaTetrahedralMesh
    const TfToken indices;
    /// \brief "jointAxis"
    /// 
    /// PhysxSchemaPhysxTendonAxisAPI
    const TfToken jointAxis;
    /// \brief "limitStiffness"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentRootAPI, PhysxSchemaPhysxTendonAxisRootAPI
    const TfToken limitStiffness;
    /// \brief "localPos"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentAPI
    const TfToken localPos;
    /// \brief "lowerLimit"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentLeafAPI, PhysxSchemaPhysxTendonAxisRootAPI
    const TfToken lowerLimit;
    /// \brief "max"
    /// 
    /// Possible value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialFrictionCombineModeAttr(), Possible value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialRestitutionCombineModeAttr()
    const TfToken max;
    /// \brief "maxDepenetrationVelocity"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken maxDepenetrationVelocity;
    /// \brief "maxNeighborhood"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken maxNeighborhood;
    /// \brief "maxParticles"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken maxParticles;
    /// \brief "maxVelocity"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken maxVelocity;
    /// \brief "MBP"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneBroadphaseTypeAttr()
    const TfToken mBP;
    /// \brief "min"
    /// 
    /// Possible value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialFrictionCombineModeAttr(), Possible value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialRestitutionCombineModeAttr()
    const TfToken min;
    /// \brief "moveTarget"
    /// 
    /// PhysxSchemaCharacterControllerAPI
    const TfToken moveTarget;
    /// \brief "multiply"
    /// 
    /// Possible value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialFrictionCombineModeAttr(), Possible value for PhysxSchemaPhysxMaterialAPI::GetPhysxMaterialRestitutionCombineModeAttr()
    const TfToken multiply;
    /// \brief "nonParticleCollisionEnabled"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken nonParticleCollisionEnabled;
    /// \brief "offset"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentRootAPI, PhysxSchemaPhysxTendonAxisRootAPI
    const TfToken offset;
    /// \brief "oneDirectional"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneFrictionTypeAttr()
    const TfToken oneDirectional;
    /// \brief "parentAttachment"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentAPI
    const TfToken parentAttachment;
    /// \brief "parentLink"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentAPI
    const TfToken parentLink;
    /// \brief "particleContactOffset"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken particleContactOffset;
    /// \brief "particleSystemEnabled"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken particleSystemEnabled;
    /// \brief "patch"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneFrictionTypeAttr(), Default value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneFrictionTypeAttr()
    const TfToken patch;
    /// \brief "PCM"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneCollisionSystemAttr(), Default value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneCollisionSystemAttr()
    const TfToken pCM;
    /// \brief "PGS"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneSolverTypeAttr()
    const TfToken pGS;
    /// \brief "physics:gearRatio"
    /// 
    /// PhysxSchemaPhysxPhysicsGearJoint
    const TfToken physicsGearRatio;
    /// \brief "physics:hinge"
    /// 
    /// PhysxSchemaPhysxPhysicsRackAndPinionJoint
    const TfToken physicsHinge;
    /// \brief "physics:hinge0"
    /// 
    /// PhysxSchemaPhysxPhysicsGearJoint
    const TfToken physicsHinge0;
    /// \brief "physics:hinge1"
    /// 
    /// PhysxSchemaPhysxPhysicsGearJoint
    const TfToken physicsHinge1;
    /// \brief "physics:prismatic"
    /// 
    /// PhysxSchemaPhysxPhysicsRackAndPinionJoint
    const TfToken physicsPrismatic;
    /// \brief "physics:ratio"
    /// 
    /// PhysxSchemaPhysxPhysicsRackAndPinionJoint
    const TfToken physicsRatio;
    /// \brief "physxArticulation:articulationEnabled"
    /// 
    /// PhysxSchemaPhysxArticulationAPI
    const TfToken physxArticulationArticulationEnabled;
    /// \brief "physxArticulation:enabledSelfCollisions"
    /// 
    /// PhysxSchemaPhysxArticulationAPI
    const TfToken physxArticulationEnabledSelfCollisions;
    /// \brief "physxArticulationForceSensor:constraintSolverForcesEnabled"
    /// 
    /// PhysxSchemaPhysxArticulationForceSensorAPI
    const TfToken physxArticulationForceSensorConstraintSolverForcesEnabled;
    /// \brief "physxArticulationForceSensor:force"
    /// 
    /// PhysxSchemaPhysxArticulationForceSensorAPI
    const TfToken physxArticulationForceSensorForce;
    /// \brief "physxArticulationForceSensor:forwardDynamicsForcesEnabled"
    /// 
    /// PhysxSchemaPhysxArticulationForceSensorAPI
    const TfToken physxArticulationForceSensorForwardDynamicsForcesEnabled;
    /// \brief "physxArticulationForceSensor:sensorEnabled"
    /// 
    /// PhysxSchemaPhysxArticulationForceSensorAPI
    const TfToken physxArticulationForceSensorSensorEnabled;
    /// \brief "physxArticulationForceSensor:torque"
    /// 
    /// PhysxSchemaPhysxArticulationForceSensorAPI
    const TfToken physxArticulationForceSensorTorque;
    /// \brief "physxArticulationForceSensor:worldFrameEnabled"
    /// 
    /// PhysxSchemaPhysxArticulationForceSensorAPI
    const TfToken physxArticulationForceSensorWorldFrameEnabled;
    /// \brief "physxArticulation:sleepThreshold"
    /// 
    /// PhysxSchemaPhysxArticulationAPI
    const TfToken physxArticulationSleepThreshold;
    /// \brief "physxArticulation:solverPositionIterationCount"
    /// 
    /// PhysxSchemaPhysxArticulationAPI
    const TfToken physxArticulationSolverPositionIterationCount;
    /// \brief "physxArticulation:solverVelocityIterationCount"
    /// 
    /// PhysxSchemaPhysxArticulationAPI
    const TfToken physxArticulationSolverVelocityIterationCount;
    /// \brief "physxArticulation:stabilizationThreshold"
    /// 
    /// PhysxSchemaPhysxArticulationAPI
    const TfToken physxArticulationStabilizationThreshold;
    /// \brief "physxAutoAttachment:collisionFilteringOffset"
    /// 
    /// PhysxSchemaPhysxAutoAttachmentAPI
    const TfToken physxAutoAttachmentCollisionFilteringOffset;
    /// \brief "physxAutoAttachment:deformableVertexOverlapOffset"
    /// 
    /// PhysxSchemaPhysxAutoAttachmentAPI
    const TfToken physxAutoAttachmentDeformableVertexOverlapOffset;
    /// \brief "physxAutoAttachment:enableCollisionFiltering"
    /// 
    /// PhysxSchemaPhysxAutoAttachmentAPI
    const TfToken physxAutoAttachmentEnableCollisionFiltering;
    /// \brief "physxAutoAttachment:enableDeformableVertexAttachments"
    /// 
    /// PhysxSchemaPhysxAutoAttachmentAPI
    const TfToken physxAutoAttachmentEnableDeformableVertexAttachments;
    /// \brief "physxAutoAttachment:enableRigidSurfaceAttachments"
    /// 
    /// PhysxSchemaPhysxAutoAttachmentAPI
    const TfToken physxAutoAttachmentEnableRigidSurfaceAttachments;
    /// \brief "physxAutoAttachment:rigidSurfaceSamplingDistance"
    /// 
    /// PhysxSchemaPhysxAutoAttachmentAPI
    const TfToken physxAutoAttachmentRigidSurfaceSamplingDistance;
    /// \brief "physxAutoParticleCloth:springBendStiffness"
    /// 
    /// PhysxSchemaPhysxAutoParticleClothAPI
    const TfToken physxAutoParticleClothSpringBendStiffness;
    /// \brief "physxAutoParticleCloth:springDamping"
    /// 
    /// PhysxSchemaPhysxAutoParticleClothAPI
    const TfToken physxAutoParticleClothSpringDamping;
    /// \brief "physxAutoParticleCloth:springShearStiffness"
    /// 
    /// PhysxSchemaPhysxAutoParticleClothAPI
    const TfToken physxAutoParticleClothSpringShearStiffness;
    /// \brief "physxAutoParticleCloth:springStretchStiffness"
    /// 
    /// PhysxSchemaPhysxAutoParticleClothAPI
    const TfToken physxAutoParticleClothSpringStretchStiffness;
    /// \brief "physxCamera:subject"
    /// 
    /// PhysxSchemaPhysxCameraAPI
    const TfToken physxCameraSubject;
    /// \brief "physxCharacterController:climbingMode"
    /// 
    /// PhysxSchemaPhysxCharacterControllerAPI
    const TfToken physxCharacterControllerClimbingMode;
    /// \brief "physxCharacterController:contactOffset"
    /// 
    /// PhysxSchemaPhysxCharacterControllerAPI
    const TfToken physxCharacterControllerContactOffset;
    /// \brief "physxCharacterController:invisibleWallHeight"
    /// 
    /// PhysxSchemaPhysxCharacterControllerAPI
    const TfToken physxCharacterControllerInvisibleWallHeight;
    /// \brief "physxCharacterController:maxJumpHeight"
    /// 
    /// PhysxSchemaPhysxCharacterControllerAPI
    const TfToken physxCharacterControllerMaxJumpHeight;
    /// \brief "physxCharacterController:nonWalkableMode"
    /// 
    /// PhysxSchemaPhysxCharacterControllerAPI
    const TfToken physxCharacterControllerNonWalkableMode;
    /// \brief "physxCharacterController:scaleCoeff"
    /// 
    /// PhysxSchemaPhysxCharacterControllerAPI
    const TfToken physxCharacterControllerScaleCoeff;
    /// \brief "physxCharacterController:stepOffset"
    /// 
    /// PhysxSchemaPhysxCharacterControllerAPI
    const TfToken physxCharacterControllerStepOffset;
    /// \brief "physxCharacterController:upAxis"
    /// 
    /// PhysxSchemaPhysxCharacterControllerAPI
    const TfToken physxCharacterControllerUpAxis;
    /// \brief "physxCharacterController:volumeGrowth"
    /// 
    /// PhysxSchemaPhysxCharacterControllerAPI
    const TfToken physxCharacterControllerVolumeGrowth;
    /// \brief "physxCollision:contactOffset"
    /// 
    /// PhysxSchemaPhysxCollisionAPI
    const TfToken physxCollisionContactOffset;
    /// \brief "physxCollisionCustomGeometry"
    /// 
    ///  This token represents the custom geometry option for cones and cylinders. The simulation will not use a convex approximation but a custom geometry instead. 
    const TfToken physxCollisionCustomGeometry;
    /// \brief "physxCollision:minTorsionalPatchRadius"
    /// 
    /// PhysxSchemaPhysxCollisionAPI
    const TfToken physxCollisionMinTorsionalPatchRadius;
    /// \brief "physxCollision:restOffset"
    /// 
    /// PhysxSchemaPhysxCollisionAPI
    const TfToken physxCollisionRestOffset;
    /// \brief "physxCollision:torsionalPatchRadius"
    /// 
    /// PhysxSchemaPhysxCollisionAPI
    const TfToken physxCollisionTorsionalPatchRadius;
    /// \brief "physxContactReport:reportPairs"
    /// 
    /// PhysxSchemaPhysxContactReportAPI
    const TfToken physxContactReportReportPairs;
    /// \brief "physxContactReport:threshold"
    /// 
    /// PhysxSchemaPhysxContactReportAPI
    const TfToken physxContactReportThreshold;
    /// \brief "physxConvexDecompositionCollision:errorPercentage"
    /// 
    /// PhysxSchemaPhysxConvexDecompositionCollisionAPI
    const TfToken physxConvexDecompositionCollisionErrorPercentage;
    /// \brief "physxConvexDecompositionCollision:hullVertexLimit"
    /// 
    /// PhysxSchemaPhysxConvexDecompositionCollisionAPI
    const TfToken physxConvexDecompositionCollisionHullVertexLimit;
    /// \brief "physxConvexDecompositionCollision:maxConvexHulls"
    /// 
    /// PhysxSchemaPhysxConvexDecompositionCollisionAPI
    const TfToken physxConvexDecompositionCollisionMaxConvexHulls;
    /// \brief "physxConvexDecompositionCollision:minThickness"
    /// 
    /// PhysxSchemaPhysxConvexDecompositionCollisionAPI
    const TfToken physxConvexDecompositionCollisionMinThickness;
    /// \brief "physxConvexDecompositionCollision:shrinkWrap"
    /// 
    /// PhysxSchemaPhysxConvexDecompositionCollisionAPI
    const TfToken physxConvexDecompositionCollisionShrinkWrap;
    /// \brief "physxConvexDecompositionCollision:voxelResolution"
    /// 
    /// PhysxSchemaPhysxConvexDecompositionCollisionAPI
    const TfToken physxConvexDecompositionCollisionVoxelResolution;
    /// \brief "physxConvexHullCollision:hullVertexLimit"
    /// 
    /// PhysxSchemaPhysxConvexHullCollisionAPI
    const TfToken physxConvexHullCollisionHullVertexLimit;
    /// \brief "physxConvexHullCollision:minThickness"
    /// 
    /// PhysxSchemaPhysxConvexHullCollisionAPI
    const TfToken physxConvexHullCollisionMinThickness;
    /// \brief "physxCookedData"
    /// 
    /// Property namespace prefix for the PhysxSchemaPhysxCookedDataAPI schema.
    const TfToken physxCookedData;
    /// \brief "physxDeformable:areaLossTolerance"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceAPI
    const TfToken physxDeformableAreaLossTolerance;
    /// \brief "physxDeformable:bendingStiffnessScale"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceAPI
    const TfToken physxDeformableBendingStiffnessScale;
    /// \brief "physxDeformableBodyMaterial:dampingScale"
    /// 
    /// PhysxSchemaPhysxDeformableBodyMaterialAPI
    const TfToken physxDeformableBodyMaterialDampingScale;
    /// \brief "physxDeformableBodyMaterial:density"
    /// 
    /// PhysxSchemaPhysxDeformableBodyMaterialAPI
    const TfToken physxDeformableBodyMaterialDensity;
    /// \brief "physxDeformableBodyMaterial:dynamicFriction"
    /// 
    /// PhysxSchemaPhysxDeformableBodyMaterialAPI
    const TfToken physxDeformableBodyMaterialDynamicFriction;
    /// \brief "physxDeformableBodyMaterial:elasticityDamping"
    /// 
    /// PhysxSchemaPhysxDeformableBodyMaterialAPI
    const TfToken physxDeformableBodyMaterialElasticityDamping;
    /// \brief "physxDeformableBodyMaterial:poissonsRatio"
    /// 
    /// PhysxSchemaPhysxDeformableBodyMaterialAPI
    const TfToken physxDeformableBodyMaterialPoissonsRatio;
    /// \brief "physxDeformableBodyMaterial:youngsModulus"
    /// 
    /// PhysxSchemaPhysxDeformableBodyMaterialAPI
    const TfToken physxDeformableBodyMaterialYoungsModulus;
    /// \brief "physxDeformable:collisionIndices"
    /// 
    /// PhysxSchemaPhysxDeformableBodyAPI
    const TfToken physxDeformableCollisionIndices;
    /// \brief "physxDeformable:collisionPoints"
    /// 
    /// PhysxSchemaPhysxDeformableBodyAPI
    const TfToken physxDeformableCollisionPoints;
    /// \brief "physxDeformable:collisionRestPoints"
    /// 
    /// PhysxSchemaPhysxDeformableBodyAPI
    const TfToken physxDeformableCollisionRestPoints;
    /// \brief "physxDeformable:deformableEnabled"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableDeformableEnabled;
    /// \brief "physxDeformable:disableGravity"
    /// 
    /// PhysxSchemaPhysxDeformableBodyAPI
    const TfToken physxDeformableDisableGravity;
    /// \brief "physxDeformable:drag"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceAPI
    const TfToken physxDeformableDrag;
    /// \brief "physxDeformable:enableCCD"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableEnableCCD;
    /// \brief "physxDeformable:lift"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceAPI
    const TfToken physxDeformableLift;
    /// \brief "physxDeformable:restPoints"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableRestPoints;
    /// \brief "physxDeformable:selfCollision"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableSelfCollision;
    /// \brief "physxDeformable:selfCollisionFilterDistance"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableSelfCollisionFilterDistance;
    /// \brief "physxDeformable:settlingThreshold"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableSettlingThreshold;
    /// \brief "physxDeformable:simulationIndices"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableSimulationIndices;
    /// \brief "physxDeformable:simulationPoints"
    /// 
    /// PhysxSchemaPhysxDeformableBodyAPI
    const TfToken physxDeformableSimulationPoints;
    /// \brief "physxDeformable:simulationRestPoints"
    /// 
    /// PhysxSchemaPhysxDeformableBodyAPI
    const TfToken physxDeformableSimulationRestPoints;
    /// \brief "physxDeformable:simulationVelocities"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableSimulationVelocities;
    /// \brief "physxDeformable:sleepDamping"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableSleepDamping;
    /// \brief "physxDeformable:sleepThreshold"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableSleepThreshold;
    /// \brief "physxDeformable:solverAlgorithm"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceAPI
    const TfToken physxDeformableSolverAlgorithm;
    /// \brief "physxDeformable:solverPositionIterationCount"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableSolverPositionIterationCount;
    /// \brief "physxDeformableSurfaceMaterial:bendingDamping"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceMaterialAPI
    const TfToken physxDeformableSurfaceMaterialBendingDamping;
    /// \brief "physxDeformableSurfaceMaterial:density"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceMaterialAPI
    const TfToken physxDeformableSurfaceMaterialDensity;
    /// \brief "physxDeformableSurfaceMaterial:dynamicFriction"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceMaterialAPI
    const TfToken physxDeformableSurfaceMaterialDynamicFriction;
    /// \brief "physxDeformableSurfaceMaterial:elasticityDamping"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceMaterialAPI
    const TfToken physxDeformableSurfaceMaterialElasticityDamping;
    /// \brief "physxDeformableSurfaceMaterial:poissonsRatio"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceMaterialAPI
    const TfToken physxDeformableSurfaceMaterialPoissonsRatio;
    /// \brief "physxDeformableSurfaceMaterial:thickness"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceMaterialAPI
    const TfToken physxDeformableSurfaceMaterialThickness;
    /// \brief "physxDeformableSurfaceMaterial:youngsModulus"
    /// 
    /// PhysxSchemaPhysxDeformableSurfaceMaterialAPI
    const TfToken physxDeformableSurfaceMaterialYoungsModulus;
    /// \brief "physxDeformable:vertexVelocityDamping"
    /// 
    /// PhysxSchemaPhysxDeformableAPI
    const TfToken physxDeformableVertexVelocityDamping;
    /// \brief "physxDiffuseParticles:airDrag"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesAirDrag;
    /// \brief "physxDiffuseParticles:bubbleDrag"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesBubbleDrag;
    /// \brief "physxDiffuseParticles:buoyancy"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesBuoyancy;
    /// \brief "physxDiffuseParticles:collisionDecay"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesCollisionDecay;
    /// \brief "physxDiffuseParticles:diffuseParticlesEnabled"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesDiffuseParticlesEnabled;
    /// \brief "physxDiffuseParticles:divergenceWeight"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesDivergenceWeight;
    /// \brief "physxDiffuseParticles:kineticEnergyWeight"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesKineticEnergyWeight;
    /// \brief "physxDiffuseParticles:lifetime"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesLifetime;
    /// \brief "physxDiffuseParticles:maxDiffuseParticles"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesMaxDiffuseParticles;
    /// \brief "physxDiffuseParticles:pressureWeight"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesPressureWeight;
    /// \brief "physxDiffuseParticles:threshold"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesThreshold;
    /// \brief "physxDiffuseParticles:useAccurateVelocity"
    /// 
    /// PhysxSchemaPhysxDiffuseParticlesAPI
    const TfToken physxDiffuseParticlesUseAccurateVelocity;
    /// \brief "physxDroneCamera:feedForwardVelocityGain"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraFeedForwardVelocityGain;
    /// \brief "physxDroneCamera:followDistance"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraFollowDistance;
    /// \brief "physxDroneCamera:followHeight"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraFollowHeight;
    /// \brief "physxDroneCamera:horizontalVelocityGain"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraHorizontalVelocityGain;
    /// \brief "physxDroneCamera:maxDistance"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraMaxDistance;
    /// \brief "physxDroneCamera:maxSpeed"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraMaxSpeed;
    /// \brief "physxDroneCamera:positionOffset"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraPositionOffset;
    /// \brief "physxDroneCamera:rotationFilterTimeConstant"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraRotationFilterTimeConstant;
    /// \brief "physxDroneCamera:velocityFilterTimeConstant"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraVelocityFilterTimeConstant;
    /// \brief "physxDroneCamera:verticalVelocityGain"
    /// 
    /// PhysxSchemaPhysxCameraDroneAPI
    const TfToken physxDroneCameraVerticalVelocityGain;
    /// \brief "physxFollowCamera:cameraPositionTimeConstant"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraCameraPositionTimeConstant;
    /// \brief "physxFollowCamera:followMaxDistance"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraFollowMaxDistance;
    /// \brief "physxFollowCamera:followMaxSpeed"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraFollowMaxSpeed;
    /// \brief "physxFollowCamera:followMinDistance"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraFollowMinDistance;
    /// \brief "physxFollowCamera:followMinSpeed"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraFollowMinSpeed;
    /// \brief "physxFollowCamera:followTurnRateGain"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraFollowTurnRateGain;
    /// \brief "physxFollowCamera:lookAheadMaxSpeed"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraLookAheadMaxSpeed;
    /// \brief "physxFollowCamera:lookAheadMinDistance"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraLookAheadMinDistance;
    /// \brief "physxFollowCamera:lookAheadMinSpeed"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraLookAheadMinSpeed;
    /// \brief "physxFollowCamera:lookAheadTurnRateGain"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraLookAheadTurnRateGain;
    /// \brief "physxFollowCamera:lookPositionHeight"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraLookPositionHeight;
    /// \brief "physxFollowCamera:lookPositionTimeConstant"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraLookPositionTimeConstant;
    /// \brief "physxFollowCamera:pitchAngle"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraPitchAngle;
    /// \brief "physxFollowCamera:pitchAngleTimeConstant"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraPitchAngleTimeConstant;
    /// \brief "physxFollowCamera:positionOffset"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraPositionOffset;
    /// \brief "physxFollowCamera:slowPitchAngleSpeed"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraSlowPitchAngleSpeed;
    /// \brief "physxFollowCamera:slowSpeedPitchAngleScale"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraSlowSpeedPitchAngleScale;
    /// \brief "physxFollowCamera:velocityNormalMinSpeed"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraVelocityNormalMinSpeed;
    /// \brief "physxFollowCamera:yawAngle"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraYawAngle;
    /// \brief "physxFollowCamera:yawRateTimeConstant"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowCameraYawRateTimeConstant;
    /// \brief "physxFollowFollowCamera:lookAheadMaxDistance"
    /// 
    /// PhysxSchemaPhysxCameraFollowAPI
    const TfToken physxFollowFollowCameraLookAheadMaxDistance;
    /// \brief "physxFollowLookCamera:downHillGroundAngle"
    /// 
    /// PhysxSchemaPhysxCameraFollowLookAPI
    const TfToken physxFollowLookCameraDownHillGroundAngle;
    /// \brief "physxFollowLookCamera:downHillGroundPitch"
    /// 
    /// PhysxSchemaPhysxCameraFollowLookAPI
    const TfToken physxFollowLookCameraDownHillGroundPitch;
    /// \brief "physxFollowLookCamera:followReverseDistance"
    /// 
    /// PhysxSchemaPhysxCameraFollowLookAPI
    const TfToken physxFollowLookCameraFollowReverseDistance;
    /// \brief "physxFollowLookCamera:followReverseSpeed"
    /// 
    /// PhysxSchemaPhysxCameraFollowLookAPI
    const TfToken physxFollowLookCameraFollowReverseSpeed;
    /// \brief "physxFollowLookCamera:upHillGroundAngle"
    /// 
    /// PhysxSchemaPhysxCameraFollowLookAPI
    const TfToken physxFollowLookCameraUpHillGroundAngle;
    /// \brief "physxFollowLookCamera:upHillGroundPitch"
    /// 
    /// PhysxSchemaPhysxCameraFollowLookAPI
    const TfToken physxFollowLookCameraUpHillGroundPitch;
    /// \brief "physxFollowLookCamera:velocityBlendTimeConstant"
    /// 
    /// PhysxSchemaPhysxCameraFollowLookAPI
    const TfToken physxFollowLookCameraVelocityBlendTimeConstant;
    /// \brief "physxIsosurface:anisotropyMax"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceAnisotropyMax;
    /// \brief "physxIsosurface:anisotropyMin"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceAnisotropyMin;
    /// \brief "physxIsosurface:anisotropyRadius"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceAnisotropyRadius;
    /// \brief "physxIsosurface:enableAnisotropy"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceEnableAnisotropy;
    /// \brief "physxIsosurface:gridFilteringFlags"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceGridFilteringFlags;
    /// \brief "physxIsosurface:gridSmoothingRadiusRelativeToCellSize"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceGridSmoothingRadiusRelativeToCellSize;
    /// \brief "physxIsosurface:gridSpacing"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceGridSpacing;
    /// \brief "physxIsosurface:isoSurfaceEnabled"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceIsoSurfaceEnabled;
    /// \brief "physxIsosurface:isosurfaceLevel"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceIsosurfaceLevel;
    /// \brief "physxIsosurface:kernelRadius"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceKernelRadius;
    /// \brief "physxIsosurface:maxSubgrids"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceMaxSubgrids;
    /// \brief "physxIsosurface:maxTriangles"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceMaxTriangles;
    /// \brief "physxIsosurface:maxVertices"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceMaxVertices;
    /// \brief "physxIsosurface:numMeshNormalSmoothingPasses"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceNumMeshNormalSmoothingPasses;
    /// \brief "physxIsosurface:numMeshSmoothingPasses"
    /// 
    /// PhysxSchemaPhysxIsosurfaceAPI
    const TfToken physxIsosurfaceNumMeshSmoothingPasses;
    /// \brief "physxJoint:enableProjection"
    /// 
    /// PhysxSchemaPhysxJointAPI
    const TfToken physxJointEnableProjection;
    /// \brief "physxJoint:jointFriction"
    /// 
    /// PhysxSchemaPhysxJointAPI
    const TfToken physxJointJointFriction;
    /// \brief "physxJoint:maxJointVelocity"
    /// 
    /// PhysxSchemaPhysxJointAPI
    const TfToken physxJointMaxJointVelocity;
    /// \brief "physxLimit"
    /// 
    /// Property namespace prefix for the PhysxSchemaPhysxLimitAPI schema.
    const TfToken physxLimit;
    /// \brief "physxMaterial:frictionCombineMode"
    /// 
    /// PhysxSchemaPhysxMaterialAPI
    const TfToken physxMaterialFrictionCombineMode;
    /// \brief "physxMaterial:improvePatchFriction"
    /// 
    /// PhysxSchemaPhysxMaterialAPI
    const TfToken physxMaterialImprovePatchFriction;
    /// \brief "physxMaterial:restitutionCombineMode"
    /// 
    /// PhysxSchemaPhysxMaterialAPI
    const TfToken physxMaterialRestitutionCombineMode;
    /// \brief "physxParticle:fluid"
    /// 
    /// PhysxSchemaPhysxParticleSetAPI
    const TfToken physxParticleFluid;
    /// \brief "physxParticle:particleEnabled"
    /// 
    /// PhysxSchemaPhysxParticleAPI
    const TfToken physxParticleParticleEnabled;
    /// \brief "physxParticle:particleGroup"
    /// 
    /// PhysxSchemaPhysxParticleAPI
    const TfToken physxParticleParticleGroup;
    /// \brief "physxParticle:particleSystem"
    /// 
    /// PhysxSchemaPhysxParticleAPI
    const TfToken physxParticleParticleSystem;
    /// \brief "physxParticlePoissonSampling:maxSamples"
    /// 
    /// PhysxSchemaPhysxParticlePoissonSamplingAPI
    const TfToken physxParticlePoissonSamplingMaxSamples;
    /// \brief "physxParticlePoissonSampling:particles"
    /// 
    /// PhysxSchemaPhysxParticlePoissonSamplingAPI
    const TfToken physxParticlePoissonSamplingParticles;
    /// \brief "physxParticlePoissonSampling:samplingDistance"
    /// 
    /// PhysxSchemaPhysxParticlePoissonSamplingAPI
    const TfToken physxParticlePoissonSamplingSamplingDistance;
    /// \brief "physxParticlePoissonSampling:volume"
    /// 
    /// PhysxSchemaPhysxParticlePoissonSamplingAPI
    const TfToken physxParticlePoissonSamplingVolume;
    /// \brief "physxParticle:pressure"
    /// 
    /// PhysxSchemaPhysxParticleClothAPI
    const TfToken physxParticlePressure;
    /// \brief "physxParticle:restPoints"
    /// 
    /// PhysxSchemaPhysxParticleClothAPI
    const TfToken physxParticleRestPoints;
    /// \brief "physxParticle:selfCollision"
    /// 
    /// PhysxSchemaPhysxParticleAPI
    const TfToken physxParticleSelfCollision;
    /// \brief "physxParticle:selfCollisionFilter"
    /// 
    /// PhysxSchemaPhysxParticleClothAPI
    const TfToken physxParticleSelfCollisionFilter;
    /// \brief "physxParticle:simulationPoints"
    /// 
    /// PhysxSchemaPhysxParticleSetAPI
    const TfToken physxParticleSimulationPoints;
    /// \brief "physxParticle:springDampings"
    /// 
    /// PhysxSchemaPhysxParticleClothAPI
    const TfToken physxParticleSpringDampings;
    /// \brief "physxParticle:springIndices"
    /// 
    /// PhysxSchemaPhysxParticleClothAPI
    const TfToken physxParticleSpringIndices;
    /// \brief "physxParticle:springRestLengths"
    /// 
    /// PhysxSchemaPhysxParticleClothAPI
    const TfToken physxParticleSpringRestLengths;
    /// \brief "physxParticle:springStiffnesses"
    /// 
    /// PhysxSchemaPhysxParticleClothAPI
    const TfToken physxParticleSpringStiffnesses;
    /// \brief "physxPBDMaterial:cflCoefficient"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialCflCoefficient;
    /// \brief "physxPBDMaterial:cohesion"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialCohesion;
    /// \brief "physxPBDMaterial:density"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialDensity;
    /// \brief "physxPBDMaterial:drag"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialDrag;
    /// \brief "physxPBDMaterial:gravityScale"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialGravityScale;
    /// \brief "physxPBDMaterial:lift"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialLift;
    /// \brief "physxPBDMaterial:particleDamping"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialParticleDamping;
    /// \brief "physxPBDMaterial:particleFriction"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialParticleFriction;
    /// \brief "physxPBDMaterial:surfaceTension"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialSurfaceTension;
    /// \brief "physxPBDMaterial:viscosity"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialViscosity;
    /// \brief "physxPBDMaterial:vorticityConfinement"
    /// 
    /// PhysxSchemaPhysxPBDMaterialAPI
    const TfToken physxPBDMaterialVorticityConfinement;
    /// \brief "physxPhysicsDistanceJoint:springDamping"
    /// 
    /// PhysxSchemaPhysxPhysicsDistanceJointAPI
    const TfToken physxPhysicsDistanceJointSpringDamping;
    /// \brief "physxPhysicsDistanceJoint:springEnabled"
    /// 
    /// PhysxSchemaPhysxPhysicsDistanceJointAPI
    const TfToken physxPhysicsDistanceJointSpringEnabled;
    /// \brief "physxPhysicsDistanceJoint:springStiffness"
    /// 
    /// PhysxSchemaPhysxPhysicsDistanceJointAPI
    const TfToken physxPhysicsDistanceJointSpringStiffness;
    /// \brief "physxRigidBody:angularDamping"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyAngularDamping;
    /// \brief "physxRigidBody:disableGravity"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyDisableGravity;
    /// \brief "physxRigidBody:enableCCD"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyEnableCCD;
    /// \brief "physxRigidBody:enableGyroscopicForces"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyEnableGyroscopicForces;
    /// \brief "physxRigidBody:enableSpeculativeCCD"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyEnableSpeculativeCCD;
    /// \brief "physxRigidBody:linearDamping"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyLinearDamping;
    /// \brief "physxRigidBody:lockedPosAxis"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyLockedPosAxis;
    /// \brief "physxRigidBody:lockedRotAxis"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyLockedRotAxis;
    /// \brief "physxRigidBody:maxAngularVelocity"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyMaxAngularVelocity;
    /// \brief "physxRigidBody:maxContactImpulse"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyMaxContactImpulse;
    /// \brief "physxRigidBody:maxDepenetrationVelocity"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyMaxDepenetrationVelocity;
    /// \brief "physxRigidBody:maxLinearVelocity"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyMaxLinearVelocity;
    /// \brief "physxRigidBody:retainAccelerations"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyRetainAccelerations;
    /// \brief "physxRigidBody:sleepThreshold"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodySleepThreshold;
    /// \brief "physxRigidBody:solverPositionIterationCount"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodySolverPositionIterationCount;
    /// \brief "physxRigidBody:solverVelocityIterationCount"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodySolverVelocityIterationCount;
    /// \brief "physxRigidBody:stabilizationThreshold"
    /// 
    /// PhysxSchemaPhysxRigidBodyAPI
    const TfToken physxRigidBodyStabilizationThreshold;
    /// \brief "physxScene:bounceThreshold"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneBounceThreshold;
    /// \brief "physxScene:broadphaseType"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneBroadphaseType;
    /// \brief "physxScene:collisionSystem"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneCollisionSystem;
    /// \brief "physxScene:enableCCD"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneEnableCCD;
    /// \brief "physxScene:enableEnhancedDeterminism"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneEnableEnhancedDeterminism;
    /// \brief "physxScene:enableGPUDynamics"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneEnableGPUDynamics;
    /// \brief "physxScene:enableStabilization"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneEnableStabilization;
    /// \brief "physxScene:frictionCorrelationDistance"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneFrictionCorrelationDistance;
    /// \brief "physxScene:frictionOffsetThreshold"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneFrictionOffsetThreshold;
    /// \brief "physxScene:frictionType"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneFrictionType;
    /// \brief "physxScene:gpuCollisionStackSize"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuCollisionStackSize;
    /// \brief "physxScene:gpuFoundLostAggregatePairsCapacity"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuFoundLostAggregatePairsCapacity;
    /// \brief "physxScene:gpuFoundLostPairsCapacity"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuFoundLostPairsCapacity;
    /// \brief "physxScene:gpuHeapCapacity"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuHeapCapacity;
    /// \brief "physxScene:gpuMaxNumPartitions"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuMaxNumPartitions;
    /// \brief "physxScene:gpuMaxParticleContacts"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuMaxParticleContacts;
    /// \brief "physxScene:gpuMaxRigidContactCount"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuMaxRigidContactCount;
    /// \brief "physxScene:gpuMaxRigidPatchCount"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuMaxRigidPatchCount;
    /// \brief "physxScene:gpuMaxSoftBodyContacts"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuMaxSoftBodyContacts;
    /// \brief "physxScene:gpuTempBufferCapacity"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuTempBufferCapacity;
    /// \brief "physxScene:gpuTotalAggregatePairsCapacity"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneGpuTotalAggregatePairsCapacity;
    /// \brief "physxScene:invertCollisionGroupFilter"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneInvertCollisionGroupFilter;
    /// \brief "physxScene:maxBiasCoefficient"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneMaxBiasCoefficient;
    /// \brief "physxScene:maxIterationCount"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneMaxIterationCount;
    /// \brief "physxScene:minIterationCount"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneMinIterationCount;
    /// \brief "physxScene:reportKinematicKinematicPairs"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneReportKinematicKinematicPairs;
    /// \brief "physxScene:reportKinematicStaticPairs"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneReportKinematicStaticPairs;
    /// \brief "physxScene:solverType"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneSolverType;
    /// \brief "physxScene:timeStepsPerSecond"
    /// 
    /// PhysxSchemaPhysxSceneAPI
    const TfToken physxSceneTimeStepsPerSecond;
    /// \brief "physxTendon"
    /// 
    /// Property namespace prefix for the PhysxSchemaPhysxTendonAttachmentLeafAPI schema., Property namespace prefix for the PhysxSchemaPhysxTendonAttachmentRootAPI schema., Property namespace prefix for the PhysxSchemaPhysxTendonAttachmentAPI schema., Property namespace prefix for the PhysxSchemaPhysxTendonAxisRootAPI schema., Property namespace prefix for the PhysxSchemaPhysxTendonAxisAPI schema.
    const TfToken physxTendon;
    /// \brief "physxTriangleMeshCollision:weldTolerance"
    /// 
    /// PhysxSchemaPhysxTriangleMeshCollisionAPI
    const TfToken physxTriangleMeshCollisionWeldTolerance;
    /// \brief "physxTriangleMeshSimplificationCollision:metric"
    /// 
    /// PhysxSchemaPhysxTriangleMeshSimplificationCollisionAPI
    const TfToken physxTriangleMeshSimplificationCollisionMetric;
    /// \brief "physxTriangleMeshSimplificationCollision:weldTolerance"
    /// 
    /// PhysxSchemaPhysxTriangleMeshSimplificationCollisionAPI
    const TfToken physxTriangleMeshSimplificationCollisionWeldTolerance;
    /// \brief "physxTrigger:enterScriptType"
    /// 
    /// PhysxSchemaPhysxTriggerAPI
    const TfToken physxTriggerEnterScriptType;
    /// \brief "physxTrigger:leaveScriptType"
    /// 
    /// PhysxSchemaPhysxTriggerAPI
    const TfToken physxTriggerLeaveScriptType;
    /// \brief "physxTrigger:onEnterScript"
    /// 
    /// PhysxSchemaPhysxTriggerAPI
    const TfToken physxTriggerOnEnterScript;
    /// \brief "physxTrigger:onLeaveScript"
    /// 
    /// PhysxSchemaPhysxTriggerAPI
    const TfToken physxTriggerOnLeaveScript;
    /// \brief "physxVehicleAutoGearBox:downRatios"
    /// 
    /// PhysxSchemaPhysxVehicleAutoGearBoxAPI
    const TfToken physxVehicleAutoGearBoxDownRatios;
    /// \brief "physxVehicleAutoGearBox:latency"
    /// 
    /// PhysxSchemaPhysxVehicleAutoGearBoxAPI
    const TfToken physxVehicleAutoGearBoxLatency;
    /// \brief "physxVehicleAutoGearBox:upRatios"
    /// 
    /// PhysxSchemaPhysxVehicleAutoGearBoxAPI
    const TfToken physxVehicleAutoGearBoxUpRatios;
    /// \brief "physxVehicleClutch:strength"
    /// 
    /// PhysxSchemaPhysxVehicleClutchAPI
    const TfToken physxVehicleClutchStrength;
    /// \brief "physxVehicleContext:forwardAxis"
    /// 
    /// PhysxSchemaPhysxVehicleContextAPI
    const TfToken physxVehicleContextForwardAxis;
    /// \brief "physxVehicleContext:sweepRadiusScale"
    /// 
    /// PhysxSchemaPhysxVehicleContextAPI
    const TfToken physxVehicleContextSweepRadiusScale;
    /// \brief "physxVehicleContext:sweepWidthScale"
    /// 
    /// PhysxSchemaPhysxVehicleContextAPI
    const TfToken physxVehicleContextSweepWidthScale;
    /// \brief "physxVehicleContext:upAxis"
    /// 
    /// PhysxSchemaPhysxVehicleContextAPI
    const TfToken physxVehicleContextUpAxis;
    /// \brief "physxVehicleContext:updateMode"
    /// 
    /// PhysxSchemaPhysxVehicleContextAPI
    const TfToken physxVehicleContextUpdateMode;
    /// \brief "physxVehicleController:accelerator"
    /// 
    /// PhysxSchemaPhysxVehicleControllerAPI
    const TfToken physxVehicleControllerAccelerator;
    /// \brief "physxVehicleController:automatic"
    /// 
    /// PhysxSchemaPhysxVehicleControllerAPI
    const TfToken physxVehicleControllerAutomatic;
    /// \brief "physxVehicleController:brake"
    /// 
    /// PhysxSchemaPhysxVehicleControllerAPI
    const TfToken physxVehicleControllerBrake;
    /// \brief "physxVehicleController:handbrake"
    /// 
    /// PhysxSchemaPhysxVehicleControllerAPI
    const TfToken physxVehicleControllerHandbrake;
    /// \brief "physxVehicleController:steerLeft"
    /// 
    /// PhysxSchemaPhysxVehicleControllerAPI
    const TfToken physxVehicleControllerSteerLeft;
    /// \brief "physxVehicleController:steerRight"
    /// 
    /// PhysxSchemaPhysxVehicleControllerAPI
    const TfToken physxVehicleControllerSteerRight;
    /// \brief "physxVehicleController:targetGear"
    /// 
    /// PhysxSchemaPhysxVehicleControllerAPI
    const TfToken physxVehicleControllerTargetGear;
    /// \brief "physxVehicle:drive"
    /// 
    /// PhysxSchemaPhysxVehicleAPI
    const TfToken physxVehicleDrive;
    /// \brief "physxVehicleDriveBasic:peakTorque"
    /// 
    /// PhysxSchemaPhysxVehicleDriveBasicAPI
    const TfToken physxVehicleDriveBasicPeakTorque;
    /// \brief "physxVehicleDriveStandard:autoGearBox"
    /// 
    /// PhysxSchemaPhysxVehicleDriveStandardAPI
    const TfToken physxVehicleDriveStandardAutoGearBox;
    /// \brief "physxVehicleDriveStandard:clutch"
    /// 
    /// PhysxSchemaPhysxVehicleDriveStandardAPI
    const TfToken physxVehicleDriveStandardClutch;
    /// \brief "physxVehicleDriveStandard:engine"
    /// 
    /// PhysxSchemaPhysxVehicleDriveStandardAPI
    const TfToken physxVehicleDriveStandardEngine;
    /// \brief "physxVehicleDriveStandard:gears"
    /// 
    /// PhysxSchemaPhysxVehicleDriveStandardAPI
    const TfToken physxVehicleDriveStandardGears;
    /// \brief "physxVehicleEngine:dampingRateFullThrottle"
    /// 
    /// PhysxSchemaPhysxVehicleEngineAPI
    const TfToken physxVehicleEngineDampingRateFullThrottle;
    /// \brief "physxVehicleEngine:dampingRateZeroThrottleClutchDisengaged"
    /// 
    /// PhysxSchemaPhysxVehicleEngineAPI
    const TfToken physxVehicleEngineDampingRateZeroThrottleClutchDisengaged;
    /// \brief "physxVehicleEngine:dampingRateZeroThrottleClutchEngaged"
    /// 
    /// PhysxSchemaPhysxVehicleEngineAPI
    const TfToken physxVehicleEngineDampingRateZeroThrottleClutchEngaged;
    /// \brief "physxVehicleEngine:maxRotationSpeed"
    /// 
    /// PhysxSchemaPhysxVehicleEngineAPI
    const TfToken physxVehicleEngineMaxRotationSpeed;
    /// \brief "physxVehicleEngine:moi"
    /// 
    /// PhysxSchemaPhysxVehicleEngineAPI
    const TfToken physxVehicleEngineMoi;
    /// \brief "physxVehicleEngine:peakTorque"
    /// 
    /// PhysxSchemaPhysxVehicleEngineAPI
    const TfToken physxVehicleEnginePeakTorque;
    /// \brief "physxVehicleEngine:torqueCurve"
    /// 
    /// PhysxSchemaPhysxVehicleEngineAPI
    const TfToken physxVehicleEngineTorqueCurve;
    /// \brief "physxVehicleGears:ratios"
    /// 
    /// PhysxSchemaPhysxVehicleGearsAPI
    const TfToken physxVehicleGearsRatios;
    /// \brief "physxVehicleGears:ratioScale"
    /// 
    /// PhysxSchemaPhysxVehicleGearsAPI
    const TfToken physxVehicleGearsRatioScale;
    /// \brief "physxVehicleGears:switchTime"
    /// 
    /// PhysxSchemaPhysxVehicleGearsAPI
    const TfToken physxVehicleGearsSwitchTime;
    /// \brief "physxVehicle:highForwardSpeedSubStepCount"
    /// 
    /// PhysxSchemaPhysxVehicleAPI
    const TfToken physxVehicleHighForwardSpeedSubStepCount;
    /// \brief "physxVehicle:lowForwardSpeedSubStepCount"
    /// 
    /// PhysxSchemaPhysxVehicleAPI
    const TfToken physxVehicleLowForwardSpeedSubStepCount;
    /// \brief "physxVehicle:minLongitudinalSlipDenominator"
    /// 
    /// PhysxSchemaPhysxVehicleAPI
    const TfToken physxVehicleMinLongitudinalSlipDenominator;
    /// \brief "physxVehicle:subStepThresholdLongitudinalSpeed"
    /// 
    /// PhysxSchemaPhysxVehicleAPI
    const TfToken physxVehicleSubStepThresholdLongitudinalSpeed;
    /// \brief "physxVehicleSuspension:camberAtMaxCompression"
    /// 
    /// PhysxSchemaPhysxVehicleSuspensionAPI
    const TfToken physxVehicleSuspensionCamberAtMaxCompression;
    /// \brief "physxVehicleSuspension:camberAtMaxDroop"
    /// 
    /// PhysxSchemaPhysxVehicleSuspensionAPI
    const TfToken physxVehicleSuspensionCamberAtMaxDroop;
    /// \brief "physxVehicleSuspension:camberAtRest"
    /// 
    /// PhysxSchemaPhysxVehicleSuspensionAPI
    const TfToken physxVehicleSuspensionCamberAtRest;
    /// \brief "physxVehicle:suspensionLineQueryType"
    /// 
    /// PhysxSchemaPhysxVehicleAPI
    const TfToken physxVehicleSuspensionLineQueryType;
    /// \brief "physxVehicleSuspension:maxCompression"
    /// 
    /// PhysxSchemaPhysxVehicleSuspensionAPI
    const TfToken physxVehicleSuspensionMaxCompression;
    /// \brief "physxVehicleSuspension:maxDroop"
    /// 
    /// PhysxSchemaPhysxVehicleSuspensionAPI
    const TfToken physxVehicleSuspensionMaxDroop;
    /// \brief "physxVehicleSuspension:springDamperRate"
    /// 
    /// PhysxSchemaPhysxVehicleSuspensionAPI
    const TfToken physxVehicleSuspensionSpringDamperRate;
    /// \brief "physxVehicleSuspension:springStrength"
    /// 
    /// PhysxSchemaPhysxVehicleSuspensionAPI
    const TfToken physxVehicleSuspensionSpringStrength;
    /// \brief "physxVehicleSuspension:sprungMass"
    /// 
    /// PhysxSchemaPhysxVehicleSuspensionAPI
    const TfToken physxVehicleSuspensionSprungMass;
    /// \brief "physxVehicleTire:camberStiffnessPerUnitGravity"
    /// 
    /// PhysxSchemaPhysxVehicleTireAPI
    const TfToken physxVehicleTireCamberStiffnessPerUnitGravity;
    /// \brief "physxVehicleTire:frictionTable"
    /// 
    /// PhysxSchemaPhysxVehicleTireAPI
    const TfToken physxVehicleTireFrictionTable;
    /// \brief "physxVehicleTire:frictionVsSlipGraph"
    /// 
    /// PhysxSchemaPhysxVehicleTireAPI
    const TfToken physxVehicleTireFrictionVsSlipGraph;
    /// \brief "physxVehicleTire:latStiffX"
    /// 
    /// PhysxSchemaPhysxVehicleTireAPI
    const TfToken physxVehicleTireLatStiffX;
    /// \brief "physxVehicleTire:latStiffY"
    /// 
    /// PhysxSchemaPhysxVehicleTireAPI
    const TfToken physxVehicleTireLatStiffY;
    /// \brief "physxVehicleTire:longitudinalStiffnessPerUnitGravity"
    /// 
    /// PhysxSchemaPhysxVehicleTireAPI
    const TfToken physxVehicleTireLongitudinalStiffnessPerUnitGravity;
    /// \brief "physxVehicle:vehicleEnabled"
    /// 
    /// PhysxSchemaPhysxVehicleAPI
    const TfToken physxVehicleVehicleEnabled;
    /// \brief "physxVehicleWheelAttachment:collisionGroup"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAttachmentAPI
    const TfToken physxVehicleWheelAttachmentCollisionGroup;
    /// \brief "physxVehicleWheelAttachment:driven"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAttachmentAPI
    const TfToken physxVehicleWheelAttachmentDriven;
    /// \brief "physxVehicleWheelAttachment:suspension"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAttachmentAPI
    const TfToken physxVehicleWheelAttachmentSuspension;
    /// \brief "physxVehicleWheelAttachment:suspensionForceAppPointOffset"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAttachmentAPI
    const TfToken physxVehicleWheelAttachmentSuspensionForceAppPointOffset;
    /// \brief "physxVehicleWheelAttachment:suspensionTravelDirection"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAttachmentAPI
    const TfToken physxVehicleWheelAttachmentSuspensionTravelDirection;
    /// \brief "physxVehicleWheelAttachment:tire"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAttachmentAPI
    const TfToken physxVehicleWheelAttachmentTire;
    /// \brief "physxVehicleWheelAttachment:tireForceAppPointOffset"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAttachmentAPI
    const TfToken physxVehicleWheelAttachmentTireForceAppPointOffset;
    /// \brief "physxVehicleWheelAttachment:wheel"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAttachmentAPI
    const TfToken physxVehicleWheelAttachmentWheel;
    /// \brief "physxVehicleWheelAttachment:wheelCenterOfMassOffset"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAttachmentAPI
    const TfToken physxVehicleWheelAttachmentWheelCenterOfMassOffset;
    /// \brief "physxVehicleWheelController:brakeTorque"
    /// 
    /// PhysxSchemaPhysxVehicleWheelControllerAPI
    const TfToken physxVehicleWheelControllerBrakeTorque;
    /// \brief "physxVehicleWheelController:driveTorque"
    /// 
    /// PhysxSchemaPhysxVehicleWheelControllerAPI
    const TfToken physxVehicleWheelControllerDriveTorque;
    /// \brief "physxVehicleWheelController:steerAngle"
    /// 
    /// PhysxSchemaPhysxVehicleWheelControllerAPI
    const TfToken physxVehicleWheelControllerSteerAngle;
    /// \brief "physxVehicleWheel:dampingRate"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAPI
    const TfToken physxVehicleWheelDampingRate;
    /// \brief "physxVehicleWheel:mass"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAPI
    const TfToken physxVehicleWheelMass;
    /// \brief "physxVehicleWheel:maxBrakeTorque"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAPI
    const TfToken physxVehicleWheelMaxBrakeTorque;
    /// \brief "physxVehicleWheel:maxHandBrakeTorque"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAPI
    const TfToken physxVehicleWheelMaxHandBrakeTorque;
    /// \brief "physxVehicleWheel:maxSteerAngle"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAPI
    const TfToken physxVehicleWheelMaxSteerAngle;
    /// \brief "physxVehicleWheel:moi"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAPI
    const TfToken physxVehicleWheelMoi;
    /// \brief "physxVehicleWheel:radius"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAPI
    const TfToken physxVehicleWheelRadius;
    /// \brief "physxVehicleWheel:toeAngle"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAPI
    const TfToken physxVehicleWheelToeAngle;
    /// \brief "physxVehicleWheel:width"
    /// 
    /// PhysxSchemaPhysxVehicleWheelAPI
    const TfToken physxVehicleWheelWidth;
    /// \brief "points0"
    /// 
    /// PhysxSchemaPhysxPhysicsAttachment
    const TfToken points0;
    /// \brief "points1"
    /// 
    /// PhysxSchemaPhysxPhysicsAttachment
    const TfToken points1;
    /// \brief "preventClimbing"
    /// 
    /// Possible value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerNonWalkableModeAttr(), Default value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerNonWalkableModeAttr()
    const TfToken preventClimbing;
    /// \brief "preventClimbingForceSliding"
    /// 
    /// Possible value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerNonWalkableModeAttr()
    const TfToken preventClimbingForceSliding;
    /// \brief "raycast"
    /// 
    /// Possible value for PhysxSchemaPhysxVehicleAPI::GetPhysxVehicleSuspensionLineQueryTypeAttr(), Default value for PhysxSchemaPhysxVehicleAPI::GetPhysxVehicleSuspensionLineQueryTypeAttr()
    const TfToken raycast;
    /// \brief "restitution"
    /// 
    /// PhysxSchemaPhysxLimitAPI
    const TfToken restitution;
    /// \brief "restLength"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentLeafAPI, PhysxSchemaPhysxTendonAxisRootAPI
    const TfToken restLength;
    /// \brief "restOffset"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken restOffset;
    /// \brief "rotX"
    /// 
    /// Possible value for PhysxSchemaPhysxTendonAxisAPI::GetJointAxisAttr()
    const TfToken rotX;
    /// \brief "rotY"
    /// 
    /// Possible value for PhysxSchemaPhysxTendonAxisAPI::GetJointAxisAttr()
    const TfToken rotY;
    /// \brief "rotZ"
    /// 
    /// Possible value for PhysxSchemaPhysxTendonAxisAPI::GetJointAxisAttr()
    const TfToken rotZ;
    /// \brief "SAP"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneBroadphaseTypeAttr()
    const TfToken sAP;
    /// \brief "SAT"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneCollisionSystemAttr()
    const TfToken sAT;
    /// \brief "scriptBuffer"
    /// 
    /// Possible value for PhysxSchemaPhysxTriggerAPI::GetPhysxTriggerEnterScriptTypeAttr(), Possible value for PhysxSchemaPhysxTriggerAPI::GetPhysxTriggerLeaveScriptTypeAttr()
    const TfToken scriptBuffer;
    /// \brief "scriptFile"
    /// 
    /// Possible value for PhysxSchemaPhysxTriggerAPI::GetPhysxTriggerEnterScriptTypeAttr(), Default value for PhysxSchemaPhysxTriggerAPI::GetPhysxTriggerEnterScriptTypeAttr(), Possible value for PhysxSchemaPhysxTriggerAPI::GetPhysxTriggerLeaveScriptTypeAttr(), Default value for PhysxSchemaPhysxTriggerAPI::GetPhysxTriggerLeaveScriptTypeAttr()
    const TfToken scriptFile;
    /// \brief "SIMPLIFIED_NEOHOOKEAN_ENERGY_CONSTRAINT"
    /// 
    /// Possible value for PhysxSchemaPhysxDeformableSurfaceAPI::GetPhysxDeformableSolverAlgorithmAttr(), Default value for PhysxSchemaPhysxDeformableSurfaceAPI::GetPhysxDeformableSolverAlgorithmAttr()
    const TfToken sIMPLIFIED_NEOHOOKEAN_ENERGY_CONSTRAINT;
    /// \brief "simulationOwner"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken simulationOwner;
    /// \brief "slopeLimit"
    /// 
    /// PhysxSchemaCharacterControllerAPI
    const TfToken slopeLimit;
    /// \brief "smoothing"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken smoothing;
    /// \brief "solidRestOffset"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken solidRestOffset;
    /// \brief "solverPositionIterationCount"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken solverPositionIterationCount;
    /// \brief "stiffness"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentRootAPI, PhysxSchemaPhysxTendonAxisRootAPI, PhysxSchemaPhysxLimitAPI
    const TfToken stiffness;
    /// \brief "sweep"
    /// 
    /// Possible value for PhysxSchemaPhysxVehicleAPI::GetPhysxVehicleSuspensionLineQueryTypeAttr()
    const TfToken sweep;
    /// \brief "tendonEnabled"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentRootAPI, PhysxSchemaPhysxTendonAxisRootAPI
    const TfToken tendonEnabled;
    /// \brief "TGS"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneSolverTypeAttr(), Default value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneSolverTypeAttr()
    const TfToken tGS;
    /// \brief "transX"
    /// 
    /// Possible value for PhysxSchemaPhysxTendonAxisAPI::GetJointAxisAttr()
    const TfToken transX;
    /// \brief "transY"
    /// 
    /// Possible value for PhysxSchemaPhysxTendonAxisAPI::GetJointAxisAttr()
    const TfToken transY;
    /// \brief "transZ"
    /// 
    /// Possible value for PhysxSchemaPhysxTendonAxisAPI::GetJointAxisAttr()
    const TfToken transZ;
    /// \brief "triangleMesh"
    /// 
    ///  This token represents the collection name to use with PhysxCookedDataAPI to represent cooked data of a TriangleMesh. 
    const TfToken triangleMesh;
    /// \brief "twoDirectional"
    /// 
    /// Possible value for PhysxSchemaPhysxSceneAPI::GetPhysxSceneFrictionTypeAttr()
    const TfToken twoDirectional;
    /// \brief "upperLimit"
    /// 
    /// PhysxSchemaPhysxTendonAttachmentLeafAPI, PhysxSchemaPhysxTendonAxisRootAPI
    const TfToken upperLimit;
    /// \brief "velocityChange"
    /// 
    /// Possible value for PhysxSchemaPhysxVehicleContextAPI::GetPhysxVehicleContextUpdateModeAttr(), Default value for PhysxSchemaPhysxVehicleContextAPI::GetPhysxVehicleContextUpdateModeAttr()
    const TfToken velocityChange;
    /// \brief "Vertices"
    /// 
    /// Possible value for PhysxSchemaPhysxPhysicsAttachment::GetFilterType0Attr(), Possible value for PhysxSchemaPhysxPhysicsAttachment::GetFilterType1Attr()
    const TfToken vertices;
    /// \brief "wind"
    /// 
    /// PhysxSchemaPhysxParticleSystem
    const TfToken wind;
    /// \brief "X"
    /// 
    /// Possible value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerUpAxisAttr(), Possible value for PhysxSchemaPlane::GetAxisAttr()
    const TfToken x;
    /// \brief "Y"
    /// 
    /// Possible value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerUpAxisAttr(), Possible value for PhysxSchemaPlane::GetAxisAttr()
    const TfToken y;
    /// \brief "Z"
    /// 
    /// Possible value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerUpAxisAttr(), Default value for PhysxSchemaPhysxCharacterControllerAPI::GetPhysxCharacterControllerUpAxisAttr(), Possible value for PhysxSchemaPlane::GetAxisAttr(), Default value for PhysxSchemaPlane::GetAxisAttr()
    const TfToken z;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var PhysxSchemaTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa PhysxSchemaTokensType
extern PHYSXSCHEMA_API TfStaticData<PhysxSchemaTokensType> PhysxSchemaTokens;

PXR_NAMESPACE_CLOSE_SCOPE

#endif
