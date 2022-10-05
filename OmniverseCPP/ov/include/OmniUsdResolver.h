// Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.
//
// clang-format off
#pragma once

#include "Defines.h"

/**
 * Sets the message that will be used by all atomic checkpoints created when saving USD files in Nucleus. By default
 * the message will be an empty string (""). The provided message will apply all to all 'Save' and 'Export' calls made
 * after the call to this function.
 * 
 * @param message Checkpoint message.
 */
OMNIUSDRESOLVER_EXPORT(void) omniUsdResolverSetCheckpointMessage(const char* message) OMNIUSDRESOLVER_NOEXCEPT;
