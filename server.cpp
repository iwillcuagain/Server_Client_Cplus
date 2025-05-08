#include <iostream>
#include <boost/asio/generic/stream_protocol.hpp> //specific #using
#include <boost/asio.hpp> //imports the whole libraru of functions classes etc.
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/basic_stream_file.hpp>


/*namespaces are defined in a block of code to declare varaibles
    you can nest namepsaces in one another
    you can hosts functions in namespaces or variables
    a namespace can look like this

    namespace MyNamespace {
        int value = 42;
        void myFunction() {
            // Function definition
        }
    }

    accessing a namespace would look like:
    std::cout<<MyNamespace::value<<std::endl;

    namespaces are nested in other namespaces for organization purposes


*/

//establish and open socket check if socket is open


//this is our executor that is going to be used to submit functions to an io_context (handles Core I/O functions)


//this constructor creates and opens a stream socket stream
//this socket need to be connected or accepted before data can be sent or received






//this is our executor that is going to be used to submit functions to an io_context (handles Core I/O functions)
//A template class allows function to work with different data types so you dont have to make the same function for each specific data type
//here we are using the basic_executor_type template class
typedef boost::asio::io_context::basic_executor_type< std::allocator< void >, 0 > executor_type;


//you have to create an io_service ( for the server) which is mandatory
boost::asio::io_context io_service_object;


//this is the protocol that we are going to use
typedef boost::asio::ip::tcp protocol_type;

//initiating object of class tcp
// i got an error while runni ghits, find out why
//boost::asio::ip::tcp protocol_object;


// ex is the input and output exeutor that the socket will use
// protocol is an object specifying protocol parameters to be used



/*CONSTRUCTOR*/
// socket(executor_type, protocol_type) is object of the "basic_Stream_socket" class
// The class basic_stream_socket requires (executor, protocol) arguments because its constructor expects them.
// Therefore, when we create a basic_stream_socket object, we must pass ex and protocol immediately.
//boost::asio::basic_stream_socket<protocol_type, executor_type> socket(protocol_type,executor_type);


//creating object of the basic_stream_socket class
//Even when trying to create an object of the class basic_stream_socket, it needs a io_context passed 
//to it so it can associate to which executor for I/O operations
// NOTE: Constructor is explicit — must pass io_context (executor) when creating basic_stream_socket, even for just an object, not another constructor.

// ⚠️ Don't use boost::asio::basic_stream_socket directly — it's a low-level base class.
// ✅ Use derived classes like boost::asio::ip::tcp::socket instead.
//    They simplify usage, expose public destructors, and are intended for real-world use.
//    rather use the class you are getting inheritance from than the low level classes that are (at the end of the day) dependent on the dervied classes
//    it reduces complications

//boost::asio::basic_stream_socket<protocol_type, executor_type> socket_object(io_service_object);


/* Boost.Asio Socket Handling Notes:
 - **Don't use `basic_socket` directly**. It's a generic base class.
 - Always use derived classes like `boost::asio::ip::tcp::socket` or `boost::asio::ip::udp::socket` for TCP/UDP.
 - `basic_socket` has a **protected destructor**, so you cannot instantiate it directly.
 - Use `io_context` (or its executor) to initialize socket objects, e.g.:
     boost::asio::io_context io_context;
     boost::asio::ip::tcp::socket sock(io_context);  // Correct
 - Subclassing `basic_socket`? Ensure a **public destructor** in your derived class.
 - **Summary**: Use concrete classes (`tcp::socket`, `udp::socket`), and always pass an `io_context` or executor.
*/

boost::asio::ip::tcp::socket basic_sock(io_service_object); 

// typedef creates an alias for a type, while declaring an object (like io_service_object) creates an actual instance.


  /// Determine whether the socket is open.
  //bool is_open() const
  //{
   // return impl_.get_service().is_open(impl_.get_implementation());
  //}

//boost::asio::basic_socket sockettest;


/*
We need to establish an endpoint that will have subsequent information attached to it such as:
Port address, Loopback address, etc.
*/

//the address type of a Address
typedef uint_least32_t uint_type;

//constructor for address_v4 objects used later
//this line initializes the "address_v4" object
//you dont need this line because it already has a default constructor
//boost::asio::ip::address_v4 address_v4();

//object for adress_v4 class
boost::asio::ip::address_v4 addy;

/*
IMPORTANT:
- Defining a constructor (like address_v4()) only tells the compiler *how* to initialize an object.
- To actually create an object, you must declare it WITHOUT parentheses, like:
    boost::asio::ip::address_v4 addy;
- Writing boost::asio::ip::address_v4 address_v4(); 
  would DECLARE a function, NOT create an object. (This is called the "most vexing parse" problem.)



IMPORTNAT:
    C++ sees what parameters you are passing at creation time — 
    and matches them to the correct constructor automatically.
    You dont need to declare a constructor again in your code.


  */

//constructs the ipv4 address
boost::asio::ip::address address(addy);

//127.0.0.1
//uint_type addr = 16777343;
int port_num = 5000;

//constructor for endpoint
//If you construct an object with arguments, that object is ready to use
// — no need for a second empty declaration.
boost::asio::ip::tcp::endpoint endpoint(address,port_num);

//If you construct an object with arguments, that object is ready to use
// — no need for a second empty declaration.
//boost::asio::ip::detail::endpoint endpoint_object;


//basic socket acceptor
boost::asio::ip::tcp::acceptor acceptor(io_service_object);
//<protocol_type, executor_type> acceptor_construct(io_service_object);



/*
Write code for leaving the terminals running after connection is established
     -set the client and server in a wait state, waiting for data that is potentially sent
*/
//defines the types of errors you can get regarding a connection


char data_ptr[1024];
char *ptr_array = data_ptr;
std::size_t buffer_size = 1024; //maybe adjust later to match data_ptr array size
boost::asio::mutable_buffer buffer(ptr_array, buffer_size);

/*
Write code for sending data through the socket

*/
int main() {

    enum boost::asio::error::basic_errors aborted = boost::asio::error::basic_errors::connection_aborted;
    
    //you have to call static methods with "::" instead "."
    protocol_type protocol = boost::asio::ip::tcp::v4();
    
    executor_type ex = io_service_object.get_executor();

    //using object "socket(ex,protocol)" of the basic_stream_scoket class
    // To call a constructor, we must create an object at the same time by providing the arguments; we cannot call the object like a function afterward.
    //socket( ex,protocol);
    
    /*
    Summary:
    - The socket (tcp::socket) is just the data pipe for communication once a connection is established.
    - The acceptor (tcp::acceptor) is the server's "door" that listens for incoming connection requests.
    - You open, bind, and listen on the acceptor — NOT the socket.
    - Once a client connects, the acceptor assigns the connection to a socket via acceptor.accept(socket).
    - That socket is then used to send and receive data.

    Think of it like this:
        Acceptor = front door
        Socket = phone line you give a client to talk
    */

    acceptor.open(protocol);


    acceptor.bind(endpoint);

    if (acceptor.is_open()){
        std::cout<<"This socket is open. Endpoint Address is "<< endpoint.address()<<" Operating on port "<<endpoint.port()<<std::endl;
    }
    else{
        std::cout<<"socket is not open"<<std::endl;
    }

    acceptor.listen();
    //when you use accept(), you have to put the socket you want to speak on
    acceptor.accept(basic_sock);
    std::cout<<"Connection established"<<std::endl;

    do{
    
        basic_sock.receive( buffer);
        std::cout << "Received: " << std::string(data_ptr, buffer_size) << std::endl;


    }while(true);

    std::cout<<"Conneciton has ended."<<std::endl;
    

    

    return 0;
}


//void basic_stream_socket(const executor_type & ex, const protocol_type & protocol){};