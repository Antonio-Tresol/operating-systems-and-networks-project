#include "../../include/net/ProxyHttpsServer.hpp"

#include <regex>
#include <utility>

using std::exception;
using std::invalid_argument;
using std::istringstream;
using std::map;
using std::regex;
using std::regex_match;
using std::regex_search;
using std::runtime_error;
using std::shared_ptr;
using std::smatch;
using std::sregex_iterator;
using std::string;
using std::to_string;
using std::vector;
using Row = std::pair<std::string, int>;
using std::string;

void ProxyHttpsServer::handleClient(const std::shared_ptr<IPv4SslSocket> &client) {
    try {
        string request{client->sslRead()};
        Logger::info("HttpsServer: Received request on socket " + std::to_string(client->getSocketFD()));
        serveFigure(client, request);
    } catch (const std::exception &e) {
        Logger::error(
                "HttpsServer: Error reading from client on socket "
                + std::to_string(client->getSocketFD())
                + ": " + string{e.what()});
    }
}

// Client interaction
map<string, map<string, string>> ProxyHttpsServer::parseHttpRequest(
        const string &request) {
    istringstream requestStream(request);
    string method, url, version;
    requestStream >> method >> url >> version;

    map<string, map<string, string>> result{
            {"Request-Line",
                        {{"Method", method}, {"URL", url}, {"Version", version}}},
            {"Headers", parseHeaders(requestStream)}};

    return result;
}

map<string, string> ProxyHttpsServer::parseHeaders(istringstream &stream) {
    map<string, string> headers;
    string line;
    while (getline(stream, line, '\n')) {  // Specify '\n' as the delimiter
        // Check if line is not just '\r'
        if (line.size() > 1) {
            // Remove the trailing '\r' if it exists
            if (line.back() == '\r') {
                line.pop_back();
            }
            auto colonPos = line.find(':');
            if (colonPos != string::npos) {
                string name = line.substr(0, colonPos);
                string value =
                        line.substr(colonPos + 2);  // Skip the colon and the space after it
                headers[name] = value;
            }
        }
    }
    return headers;
}

bool ProxyHttpsServer::validateUrlFormat(const string &url) {
    regex pathFormat{R"(/lego/\w+$)"};
    return std::regex_match(url, pathFormat);
}

string ProxyHttpsServer::getLastPath(const string &url) {
    size_t pos = url.find_last_of('/');
    if (pos != string::npos) {
        return url.substr(pos + 1);  // Return the part after the last '/'
    }
    return url;  // Return the whole URL if there is no '/'
}

string ProxyHttpsServer::generateHttpResponse(int statusCode,
                                              const string &body) {
    string statusMessage;
    switch (statusCode) {
        case 200:
            statusMessage = "OK";
            break;
        case 404:
            statusMessage = "Not Found";
            break;
        case 500:
            statusMessage = "Internal Error";
            break;
        default:
            throw invalid_argument("Unknown HTTP status code");
    }

    string response =
            "HTTP/1.1 " + to_string(statusCode) + " " + statusMessage + "\r\n";
    response += "Content-Type: text/html\r\n";
    response += "Content-Length: " + to_string(body.size()) + "\r\n";
    response += "Connection: close\r\n";
    response += "\r\n" + body;

    return response;
}

void ProxyHttpsServer::sendHttpResponse(const shared_ptr<IPv4SslSocket> &client,
                                        int statusCode, const string &body) {
    string response = ProxyHttpsServer::generateHttpResponse(statusCode, body);
    client->write(response);
}

void ProxyHttpsServer::sendHttpsResponse(
        const shared_ptr<IPv4SslSocket> &client, int statusCode,
        const string &body) {
    string response = ProxyHttpsServer::generateHttpResponse(statusCode, body);
    client->sslWrite(response);
}

void ProxyHttpsServer::serveFigure(const shared_ptr<IPv4SslSocket> &client,
                                   const string &request) {
    string socketNum{std::to_string(client->getSocketFD())};

    try {
        // for a normal request: parse the request
        map<string, map<string, string>> parsedRequest{parseHttpRequest(request)};
        string url{parsedRequest["Request-Line"]["URL"]};

        Logger::info("HttpsServer: Client request on socket " + socketNum + ": " + request);

        // check if the url is valid
        if (!validateUrlFormat(url)) {
            Logger::info(
                    "HttpsServer: Sending 404 response to client (caused by invalid URL Format) on socket "
                    + socketNum);
            sendHttpsResponse(client, 404, "");
            return;
        }

        string figureName{getLastPath(url)};

        // get the body of the figure
        string body{proxyHttpsController.getFigureByName(figureName)};
        // prepare the headers
        map<string, string> headers{parsedRequest["Headers"]};
        if (body.empty()) {  // if the body is empty, send a 404 response
            Logger::info(
                    "HttpsServer: Sending 404 response to client (caused by FigureNotFound) on socket "
                    + socketNum);
            sendHttpsResponse(client, 404, body);
        } else {  // if the body is not empty, send the figure and 200 response
            Logger::info("HttpsServer: Sending response to client on socket " + socketNum);
            sendHttpsResponse(client, 200, body);
        }
    } catch (exception &e) {
        Logger::error("HttpsServer: Client error on socket " + socketNum + ": ", e);
        Logger::error("HttpsServer: Dropping client on socket " + socketNum);
    }
    Logger::info("HttpsServer: Handled connection on socket " + socketNum);
    return;
}
