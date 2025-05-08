#include <iostream>
#include <boost/asio/generic/stream_protocol.hpp> //specific #using
#include <boost/asio.hpp> //imports the whole libraru of functions classes etc.
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/basic_stream_file.hpp>



//this is our executor that is going to be used to submit functions to an io_context (handles Core I/O functions)
typedef boost::asio::io_context::basic_executor_type< std::allocator< void >, 0 > executor_type;


//you have to create an io_service ( for the server) which is mandatory
boost::asio::io_context io_service_object;


//this is the protocol that we are going to use
typedef boost::asio::ip::tcp protocol_type;


boost::asio::ip::tcp::socket basic_sock(io_service_object); 

boost::system::error_code e;

//the address type of a Address
typedef uint_least32_t uint_type;


//object for adress_v4 class
boost::asio::ip::address_v4 addy;


//constructs the ipv4 address
boost::asio::ip::address address(addy);

//127.0.0.1
//uint_type addr = 16777343;
int port_num = 5000;

//constructor for endpoint

boost::asio::ip::tcp::endpoint endpoint(address,port_num);


//basic socket acceptor
boost::asio::ip::tcp::acceptor acceptor(io_service_object);

char data_ptr[1024];
char *ptr_array = data_ptr;
std::size_t buffer_size = 1024; //maybe adjust later to match data_ptr array size
boost::asio::mutable_buffer buffer(ptr_array, buffer_size);

int main() {

    enum boost::asio::error::basic_errors aborted = boost::asio::error::basic_errors::connection_aborted;
    
    //you have to call static methods with "::" instead "."
    protocol_type protocol = boost::asio::ip::tcp::v4();
    
    executor_type ex = io_service_object.get_executor();
    // To call a constructor, we must create an object at the same time by providing the arguments; we cannot call the object like a function afterward.

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

        
    try{

        while(true){
        basic_sock.receive( buffer);
        std::cout << "Received: " << std::string(data_ptr, buffer_size) << std::endl;
        }
    }
    catch (boost::system::system_error){
        std::cout<<"Error occurred. Verify data transfer"<<std::endl;
    }

    

    std::cout<<"Conneciton has ended."<<std::endl;
    

    

    return 0;
}
