#include "server_http.hpp"
#include "client_http.hpp"

//Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

//Added for the default_resource example
#include <fstream>
#include <boost/filesystem.hpp>
#include <vector>
#include <algorithm>

using namespace std;
//Added for the json-example:
using namespace boost::property_tree;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

int main() {
    //HTTP-server at port 8080 using 1 thread
    //Unless you do more heavy non-threaded processing in the resources,
    //1 thread is usually faster than several threads
    HttpServer server(8080, 1);

    //Default GET/POST/PUT-example. If no other matches, this anonymous function will be called.
    //Will respond with content in the web/-directory, and its subdirectories.
    //Default file: index.html
    //Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server
    server.default_resource["GET"]=[&server](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        try {
            time_t now;
            const size_t tsLength = 25;
            char dateCstr[tsLength];
            dateCstr[0] = '\0';
            now = time(NULL);
            strftime(dateCstr, tsLength, "%Y-%m-%d_%H-%M-%S", gmtime(&now));
            std::string timeStamp = dateCstr;
            timeStamp += "GMT";

            std::stringstream jsonBuf;
            jsonBuf << "{"
                 << "\"method\": \"" << request->method
                 << "\", \"path\": \"" << request->path
                 << "\", \"remote_endpoint_address\": \"" << request->remote_endpoint_address
                 << "\", \"time\": \"" << timeStamp
                 << "\"}";
            std::string json = jsonBuf.str();
            auto length = json.length();

            boost::filesystem::path dir("path");

            std::string logDir = "/Users/zeph/ClionProjects/Simple-Web-Server/log/";
            std::ofstream ofs(logDir + timeStamp + ".log", std::ofstream::out);
            ofs << json << std::endl;
            ofs.close();

            *response << "HTTP/1.1 200 OK\r\nContent-Length: " << length << "\r\n\r\n" << json;
        }
        catch(const exception &e) {
            string content="Could not open path "+request->path+": "+e.what();
            *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
        }
    };

    server.default_resource["POST"]=server.default_resource["PUT"]=server.default_resource["GET"];

    thread server_thread([&server](){
        //Start server
        server.start();
    });
    
    //Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));
    
    //Client examples
    HttpClient client("localhost:8080");
    auto r1=client.request("GET", "/match/123");
    cout << r1->content.rdbuf() << endl;

    string json_string="{\"firstName\": \"John\",\"lastName\": \"Smith\",\"age\": 25}";
    auto r2=client.request("POST", "/string", json_string);
    cout << r2->content.rdbuf() << endl;
    
    auto r3=client.request("POST", "/json", json_string);
    cout << r3->content.rdbuf() << endl;
        
    server_thread.join();
    
    return 0;
}