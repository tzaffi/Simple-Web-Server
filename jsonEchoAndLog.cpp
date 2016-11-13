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

#include "libs/RuleOf72.h"

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

    //my RuleOf72 server:
    server.resource["^/ruleOf72([?].+)"]["GET"]=[&server](shared_ptr<HttpServer::Response> resp, shared_ptr<HttpServer::Request> req)
    {
        RuleOf72 ro72;
        string message = "TBD";
        string path = req->path;
        std::size_t idx = path.find("?");
        try {
            string numStr = path.substr(idx + 1, path.size() - idx - 1);
            message = numStr;
            double num = std::stod(numStr);
            message = ro72.report(num);
            *resp << "HTTP/1.1 200 OK\r\nContent-Length: " << message.length() << "\r\n\r\n" << message;
        } catch(const exception &e) {
            string content= "message: "+message+"\nProblem: "+e.what();
            *resp << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
        }
    };

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
	    chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
	    int suffixNum = ms.count() % 1000;

	    std::stringstream tsBuf;
	    tsBuf << dateCstr << "." << suffixNum << "GMT";
	    std::string timeStamp = tsBuf.str();

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
