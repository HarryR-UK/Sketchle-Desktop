#include "NetworkClient.h"
#include <iostream>

using namespace sk;

NetworkClient::NetworkClient(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

NetworkClient::~NetworkClient(){
    curl_global_cleanup();
}


const std::string& NetworkClient::getServerResponse() const{ 
    return mServerResponse;
}


void NetworkClient::addTokenHeader(curl_slist*& headers){
    std::string auth = "Authorization: Bearer " + mToken;
    headers = curl_slist_append(headers, auth.c_str());
}

const std::string NetworkClient::attemptImageSubmit(sf::Image image){
    return "";
}

const std::string& NetworkClient::attemptLogin(std::string username, std::string password){
    mServerResponse.clear();

    std::stringstream ss;
    ss << "{"
        << "\"username\": \"" << username << "\","
        << "\"password\": \"" << password << "\""
        << "}";

    std::string jsonRq = ss.str();

    std::string url = mDomain + "/auth/login";

    mCurl = curl_easy_init();

    if(mCurl){
        curl_easy_setopt(mCurl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(mCurl, CURLOPT_POST, 1L);

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(mCurl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, jsonRq.c_str());

        curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, sk::CurlUtil::writeCallback);
        curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &mServerResponse);

        CURLcode c = curl_easy_perform(mCurl);

        curl_slist_free_all(headers);
        curl_easy_cleanup(mCurl);

        // error checking
        if(c != CURLE_OK){
            std::cerr << "CURL ERROR: " << curl_easy_strerror(c) << '\n';
        }

        if(mServerResponse.find("\"token\"") != std::string::npos){
            // parses token
            auto start = mServerResponse.find("\"token\"");
            start = mServerResponse.find(":", start);
            start = mServerResponse.find("\"", start) + 1;
            auto end = mServerResponse.find("\"", start);

            mToken = mServerResponse.substr(start, end-start);
        }
    }


    return mServerResponse;
}
