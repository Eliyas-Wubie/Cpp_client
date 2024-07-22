#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;

int main() {
    try {
        io_context io_context;
        tcp::socket socket(io_context);

        // Connect to the server
        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 3000));

        while (true) {
            // Read user input
            cout << "Enter message to send (type 'exit' to quit): ";
            string message;
            getline(cin, message);

            if (message == "exit")
                break;

            // Send data to the server
            boost::system::error_code error;
            write(socket, buffer(message + "\n"), error);
            if (error) {
                throw boost::system::system_error(error);
            }

            // Receive response from the server
            char response[1024];
            size_t length = socket.read_some(buffer(response), error);
            if (error) {
                throw boost::system::system_error(error);
            }

            cout << "Received from server: ";
            cout.write(response, length);
            cout << endl;
        }

    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}