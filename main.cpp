#include <iostream>
#include <deque>
#include <thread>
#include <boost/asio.hpp>
#include <QApplication>
#include <QWidget>

using boost::asio::ip::tcp;

class chat_client {
public:
    chat_client(boost::asio::io_service &io_service,
                tcp::resolver::iterator endpoint_iterator)
            : io_service_(io_service),
              socket_(io_service) {
    }

    void close() {
        io_service_.post([this]() { socket_.close(); });
    }

private:
    boost::asio::io_service &io_service_;
    tcp::socket socket_;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.exec();

    try {
        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({argv[1], argv[2]});
        chat_client c(io_service, endpoint_iterator);

        std::thread t([&io_service]() { io_service.run(); });

        c.close();
        t.join();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    std::cout << "Vsyo ok ;)" << "\n";

    return 0;
}