/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**
 * @file 	main.cpp
 * @author 	Marco "Swampy" Millan
 * @date 	2022/08/16
 * @brief This only is to make things callable from C++ to javascript
 * 
 */
/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/


#include "ovFunctions.h"

extern "C"
{
//   EXPORTABLE bool 
//   c_initialize(bool doLiveEdit) {
//     return initialize(doLiveEdit);
//   }
// 
//   EXPORTABLE void
//   c_shutdown() {
//     return shutdown();
//   }
// 
//   EXPORTABLE const char*
//   c_createStage(const char* path, const char* name) {
//     const char* toReturn = createStage(std::string(path), std::string(name)).c_str();
//     return toReturn;
//   }

  EXPORTABLE int
  c_ping() {
    return 5;
  }
  
}