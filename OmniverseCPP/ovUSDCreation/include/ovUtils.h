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
  runCommand(const std::string& commandLine) {
    system(commandLine.c_str());
  }

  template<typename ... Args>
  static std::string 
  format(const std::string& format, Args ... args) {
    int size_s = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { throwRuntimeError("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
  }

  template<typename T>
  static std::string 
  toString(const T& number) {
    return std::to_string(number);
  }

  static void 
  throwException(const std::string& message) {
    throw::std::exception(message.c_str());
  }

  static void 
  throwRuntimeError(const std::string& message) {
    throw::std::runtime_error(message.c_str());
  }

  static const std::string BLANK;

};
