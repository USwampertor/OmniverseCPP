/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**
 * @file 	main.cpp
 * @author 	Marco "Swampy" Millan
 * @date 	2022/03/02
 * @brief This example will show in a detailed way how does Omniverse
 *        works by using the USD system and create a USD object
 * 
 */
/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/

#include "ovOmniverseFunctions.h"
#include "ovUtils.h"

/*
 *	@brief		The main entry of the executable
 *	@param    argc the entry code
 *	@param    argv the parameters passed in the executable
 *	@return   the exit code
 */
int 
main(int argc, char* argv[]) {
  // This will be the path where we will write our own first USD
  String destinationPath = "omniverse://localhost/Projects/OmniverseCPP/";
  
  // So we can have a control of errors, we will use a try catch that englobes the whole
  // project
  try
  {
     if (!initialize(true)) {
        throw Exception(Utils::format("Error thrown at: %s", g_error.c_str()).c_str());
     }
     const String stageURL = createStage(destinationPath);
     printf("Connected user: %s", getUserName(stageURL).c_str());
     shutdown();
  }
  catch (const Exception& e)
  {
     cout << String("There was a problem with Omniverse \n") << e.what() << endl;
     return -1;
  }

  return 0;
}