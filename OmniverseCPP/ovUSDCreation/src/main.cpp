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

/*
 *	@brief		The main entry of the executable
 *	@param    argc the entry code
 *	@param    argv the parameters passed in the executable
 *	@return   the exit code
 */
int 
main(int argc, char* argv[]) {
  // This will be the path where we will write our own first USD
  String destinationPath = "omniverse://localhost/OmniverseCPP/";
  
  // So we can have a control of errors, we will use a try catch that englobes the whole
  // project
  try
  {


  }
  catch (Exception* e)
  {
    cout << String("Error found at: ") << e->what() << endl;
  }
}