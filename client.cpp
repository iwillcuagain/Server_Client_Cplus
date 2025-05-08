#include <iostream>
#include <boost/asio/generic/stream_protocol.hpp> //specific #using
#include <boost/asio.hpp> //imports the whole libraru of functions classes etc.
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/basic_stream_file.hpp>
#include <fstream>
#include <iostream>


typedef boost::asio::io_context::basic_executor_type< std::allocator< void >, 0 > executor_type;

 
boost::asio::io_context io_service_object;

boost::asio::ip::tcp::socket basic_sock(io_service_object);

executor_type ex = io_service_object.get_executor();

typedef boost::asio::ip::tcp protocol_type;

//the address type of a Address
typedef uint_least32_t uint_type;

//adress_1 initiation
uint_type address_1 = 2130706434;

//initialize socket

//instantiate constructor
boost::asio::ip::address_v4 address_v4(address_1);

//constructs the ipv4 address
boost::asio::ip::address address(address_v4);

int port_num = 5001;

boost::asio::ip::tcp::endpoint endpoint(address,port_num);


//peer endpoint initialization
int peer_port = 5000;
boost::asio::ip::address_v4 peer_address;
boost::asio::ip::address address2(peer_address);
boost::asio::ip::tcp::endpoint peer_endpoint(address2,peer_port);

//checking for condition for "connection-aborted error" which will use to close conneciton or keep alive
enum boost::asio::error::basic_errors aborted = boost::asio::error::basic_errors::connection_aborted;


//creates the default constructor | set teh data and size variables
//the data is a pointer to the stack for the buffer | pointer to array[0]
//buffer_size is how large the buffer is in bytes

char data_ptr[1024] = "Hello server";
char *ptr_array = data_ptr;
std::size_t buffer_size = 1024; //maybe adjust later to match data_ptr array size
boost::asio::mutable_buffer buffer(ptr_array, buffer_size);

//const std::string path = "C:\\Users\\levai\\OneDrive\\Desktop\\exchange.txt";

//auto flags = boost::asio::file_base::flags::read_write;


//you can query the socket to see how much data is available then allocate your buffer accordingly
//socket::available

//initatiate the stream file
//boost::asio::basic_stream_file<executor_type> my_stream_file(ex, path, flags );


//look up iostream file operations and try initation a fstream file and pass that instead.
//or look up how to do it then try and look at the notation of boost.asio


//uses the "write function" (1 of overload x)



int main(){

    protocol_type protocol = boost::asio::ip::tcp::v4();
    
    executor_type ex = io_service_object.get_executor();

    std::cout<<" The address for this endpoint is "<<endpoint.address()<<std::endl;
    std::cout<<" The port for this endpoint is "<<endpoint.port()<<std::endl;

    
    
    basic_sock.connect(peer_endpoint);
    std::cout<<"Connection is running. "<<std::endl;

    boost::asio::write(basic_sock, buffer);
    std::cout<<"Message sent"<<std::endl;


    


    std::cout<<"Conneciton has ended."<<std::endl;



    

    return 0;
}