/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**
 * @file 	ovUtils.h
 * @author 	Marco "Swampy" Millan
 * @date 	2022/03/03
 * @brief 	
 * 
 */
/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
#pragma once

#include "ovPrerequisites.h"

struct Utils {
  static void
  runCommand(const String& commandLine) {
    system(commandLine.c_str());
  }

  template<typename ... Args>
  static String 
  format(const String& format, Args ... args) {
    int32 size_s = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { ThrowRuntimeError("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return String(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
  }

  template<typename T>
  static String 
  toString(const T& number) {
    return std::to_string(number);
  }

  static void 
  ThrowException(const String& message) {
    throw::std::exception(message.c_str());
  }

  static void 
  ThrowRuntimeError(const String& message) {
    throw::std::runtime_error(message.c_str());
  }

  static const String BLANK;

};
