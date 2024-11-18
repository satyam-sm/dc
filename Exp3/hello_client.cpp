#include <iostream>
#include <omniORB4/CORBA.h>
#include "hello.hh"

int main(int argc, char* argv[]) {
    try {
        // Initialize the ORB
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        // Convert the server IOR into a CORBA object
        CORBA::Object_var obj = orb->string_to_object(argv[1]);

        // Narrow the object reference to the Hello interface
        HelloApp::Hello_var hello = HelloApp::Hello::_narrow(obj);

        if (CORBA::is_nil(hello)) {
            std::cerr << "Failed to narrow reference." << std::endl;
            return 1;
        }

        // Call the sayHello() method on the server
        CORBA::String_var message = hello->sayHello();
        std::cout << "Server says: " << message << std::endl;

        // Clean up
        orb->destroy();
    } catch (CORBA::Exception& e) {
        std::cerr << "CORBA Exception: " << e._name() << std::endl;
    }
    return 0;
}
