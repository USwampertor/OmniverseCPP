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
#include "OmniClientTypes.h"

OMNICLIENT_EXPORT(OmniClientContent) omniClientAllocContent(size_t size) OMNICLIENT_NOEXCEPT;
OMNICLIENT_EXPORT(OmniClientContent) omniClientReferenceContent(void* buffer, size_t size) OMNICLIENT_NOEXCEPT;
OMNICLIENT_EXPORT(OmniClientContent) omniClientMoveContent(OmniClientContent& content) OMNICLIENT_NOEXCEPT;
OMNICLIENT_EXPORT(OmniClientContent) omniClientCopyContent(OmniClientContent const& content) OMNICLIENT_NOEXCEPT;
OMNICLIENT_EXPORT(void) omniClientFreeContent(OmniClientContent& content) OMNICLIENT_NOEXCEPT;
