//
// Copyright 2020 Pixar
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
#ifndef PXR_IMAGING_HGI_TYPES_H
#define PXR_IMAGING_HGI_TYPES_H

#include "pxr/pxr.h"
#include "pxr/imaging/hgi/api.h"
#include <stdlib.h>


PXR_NAMESPACE_OPEN_SCOPE

/// \enum HgiFormat
///
/// HgiFormat describes the memory format of image buffers used in Hgi.
/// These formats are closely aligned with HdFormat and allow us to keep Hgi
/// independent of Hd.
///
/// For reference, see:
///   https://www.khronos.org/registry/vulkan/specs/1.1/html/vkspec.html#VkFormat
enum HgiFormat
{
    HgiFormatInvalid = -1,

    // UNorm8 - a 1-byte value representing a float between 0 and 1.
    // float value = (unorm / 255.0f);
    HgiFormatUNorm8 = 0,
    HgiFormatUNorm8Vec2,
    /* HgiFormatUNorm8Vec3 */ // Unsupported Metal (MTLPixelFormat)
    HgiFormatUNorm8Vec4,

    // SNorm8 - a 1-byte value representing a float between -1 and 1.
    // float value = max(snorm / 127.0f, -1.0f);
    HgiFormatSNorm8,
    HgiFormatSNorm8Vec2,
    /* HgiFormatSNorm8Vec3 */ // Unsupported Metal (MTLPixelFormat)
    HgiFormatSNorm8Vec4,

    // Float16 - a 2-byte IEEE half-precision float.
    HgiFormatFloat16,
    HgiFormatFloat16Vec2,
    HgiFormatFloat16Vec3,
    HgiFormatFloat16Vec4,

    // Float32 - a 4-byte IEEE float.
    HgiFormatFloat32,
    HgiFormatFloat32Vec2,
    HgiFormatFloat32Vec3,
    HgiFormatFloat32Vec4,

    // Int32 - a 4-byte signed integer
    HgiFormatInt32,
    HgiFormatInt32Vec2,
    HgiFormatInt32Vec3,
    HgiFormatInt32Vec4,

    // UNorm8 SRGB - a 1-byte value representing a float between 0 and 1.
    // Gamma compression/decompression happens during read/write.
    // Alpha component is linear.
    /* HgiFormatUNorm8srgb */     // Unsupported by OpenGL
    /* HgiFormatUNorm8Vec2srgb */ // Unsupported by OpenGL
    /* HgiFormatUNorm8Vec3srgb */ // Unsupported Metal (MTLPixelFormat)
    HgiFormatUNorm8Vec4srgb,

    // BPTC compressed. 3-component, 4x4 blocks, signed floating-point
    HgiFormatBC6FloatVec3,

    // BPTC compressed. 3-component, 4x4 blocks, unsigned floating-point
    HgiFormatBC6UFloatVec3,

    // Depth stencil format (Float32 can be used for just depth)
    HgiFormatFloat32UInt8,

    HgiFormatCount
};

/// Return the count of components in the given format.
HGI_API
size_t HgiGetComponentCount(HgiFormat f);

/// Return the size of a single element of the given format.
///
/// Returns the bytes-per-pixel even for blocked formats such as
/// BC6 since - luckily - the number still happens to be integral for supported
/// compression formats.
HGI_API
size_t HgiDataSizeOfFormat(HgiFormat f);

/// Return whether the given format uses compression.
HGI_API
bool HgiIsCompressed(HgiFormat f);

PXR_NAMESPACE_CLOSE_SCOPE

#endif
