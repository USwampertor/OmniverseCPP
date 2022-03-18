// Copyright (c) 2020, NVIDIA CORPORATION.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.
//

#pragma once

#include "OmniClientAbi.h"
#include "OmniClientContent.h"
#include "OmniClientTypes.h"

typedef void(OMNICLIENT_ABI* OmniClientExportCallback)(void* userData,
                                                       char const* path,
                                                       OmniClientContent const& content) OMNICLIENT_CALLBACK_NOEXCEPT;

OMNICLIENT_EXPORT(bool)
omniClientExportToOmniObject(const char* srcUrl, const char* dstPath, void* userData, OmniClientExportCallback callback)
    OMNICLIENT_NOEXCEPT;
