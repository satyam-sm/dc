// hello_server.cpp
#include <iostream>
#include <omniORB4/CORBA.h>
#include "hello.hh"

class Hello_impl : public POA_HelloApp::Hello {
public:
    Hello_impl() {}
    virtual ~Hello_impl() {}

    // Implement the sayHello method
    virtual char* sayHello() {
        std::cout << "sayHello() method called." << std::endl;
        return CORBA::string_dup("Hello from CORBA Server!");
    }
};

int main(int argc, char* argv[]) {
    try {
        // Initialize the ORB
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        // Get reference to root POA
        CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

        // Create the Hello_impl object
        Hello_impl* helloImpl = new Hello_impl();

        // Activate the object
        PortableServer::ObjectId_var helloId = poa->activate_object(helloImpl);

        // Obtain the CORBA object reference
        CORBA::Object_var helloRef = helloImpl->_this();

        // Print the IOR
        CORBA::String_var ior = orb->object_to_string(helloRef);
        std::cout << "Server IOR: " << ior << std::endl;

        // Activate the POA manager
        PortableServer::POAManager_var manager = poa->the_POAManager();
        manager->activate();

        // Run the ORB's event loop
        std::cout << "CORBA Server is running..." << std::endl;
        orb->run();
    } catch (CORBA::Exception& e) {
        std::cerr << "CORBA Exception: " << e._name() << std::endl;
    }
    return 0;
}
