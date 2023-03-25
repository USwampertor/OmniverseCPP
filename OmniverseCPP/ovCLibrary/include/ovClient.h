#pragma once

#include <OmniClient.h>

/**
 * This is a ONLY C wrapper for exporting objects to other languages
 */
extern "C"
{
  typedef void(OMNICLIENT_ABI* cOmniClientLogCallback)
    (char const* threadName, char const* component, OmniClientLogLevel level, char const* message)
    OMNICLIENT_CALLBACK_NOEXCEPT;

  OMNICLIENT_EXPORT(void)
    cOmniClientSetLogCallback(cOmniClientLogCallback callback)
    OMNICLIENT_NOEXCEPT;

  OMNICLIENT_EXPORT(void)
    cOmniClientSetLogLevel(OmniClientLogLevel level)
    OMNICLIENT_NOEXCEPT;

  OMNICLIENT_EXPORT(char const*)
    cOmniClientGetLogLevelString(OmniClientLogLevel level)
    OMNICLIENT_NOEXCEPT;

  OMNICLIENT_EXPORT(char)
    cOmniClientGetLogLevelChar(OmniClientLogLevel level)
    OMNICLIENT_NOEXCEPT;
}