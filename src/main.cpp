//
// Author: Harry Rotheram
//
//

#include <cstdlib>
#include <stdio.h>

#include "Application.h"
#include "networking/NetworkClient.h"

int main(void)
{

    //sk::Application app;
    //app.run();
    
    sk::NetworkClient net;

    std::cout << net.attemptLogin("darren123", "HelloDarren123*") << '\n';


    return EXIT_SUCCESS;
}
