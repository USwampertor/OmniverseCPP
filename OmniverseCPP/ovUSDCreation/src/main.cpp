/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**
 * @file 	main.cpp
 * @author 	Marco "Swampy" Millan
 * @date 	2022/03/02
 * @brief This example will show in a detailed way how does Omniverse
 *        works by using the USD system and create a USD object.
 *        It is strongly based on the Nvidia example given in 
 *        the Omniverse connector example, but tried to simplify it
 *        and make it more explainable
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
  std::string destinationPath = "omniverse://localhost/Projects/OmniverseCPP/";
  
  // So we can have a control of errors, we will use a try catch that englobes the whole
  // project
  try
  {
    // First check if Omniverse can be reached or is started
    // If the user has not logged it, a prompt will appear asking for the user to
    // connect
    // If there is a problem, either by the credentials or reaching the server,
    // This will return false
    if (!initialize(true)) {
        throw std::exception(Utils::format("Error thrown at: %s", g_error.c_str()).c_str());
    }

    // After reaching the servers, we create a stage just to confirm the connection
    // and print the username to show also that we can access information of the user
    const std::string stageURL = createStage(destinationPath);
    std::cout << Utils::format("Connected user: %s", getUserName(stageURL).c_str()) << std::endl;
    
    // We stop the connection with Omniverse
    shutdown();
  }

  // Oh no! Something happened, we will try to fetch the error
  catch (const std::exception& e)
  {
     std::cout << std::string("There was a problem with Omniverse \n") << e.what() << std::endl;
     return -1;
  }

  // Everything went a-okay
  return 0;
}