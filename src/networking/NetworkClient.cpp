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
    mServerResponse.clear();
    image.saveToFile("drawing.png");
    std::string url = mDomain + "/drawings/submit";

    mCurl = curl_easy_init();

    if(mCurl){
        curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(mCurl, CURLOPT_POST, 1L);

        struct curl_slist* headers = nullptr;
        addTokenHeader(headers);

        curl_easy_setopt(mCurl, CURLOPT_HTTPHEADER, headers);

        curl_mime* mime = curl_mime_init(mCurl);

        curl_mimepart* part = curl_mime_addpart(mime);
        curl_mime_name(part, "file");
        curl_mime_filedata(part, "drawing.png");

        curl_easy_setopt(mCurl, CURLOPT_MIMEPOST, mime);

        curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, sk::CurlUtil::writeCallback);
        curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &mServerResponse);
        CURLcode res = curl_easy_perform(mCurl);

        if (res != CURLE_OK) {
            std::cerr << "CURL ERROR: " << curl_easy_strerror(res) << std::endl;
        }

        curl_mime_free(mime);
        curl_slist_free_all(headers);
        curl_easy_cleanup(mCurl);

    }

    return mServerResponse;


}

const std::string NetworkClient::attemptGetDailyTheme(){
    mServerResponse.clear();

    std::string url = mDomain + "/theme/daily";

    mCurl = curl_easy_init();

    if(mCurl){
        curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, sk::CurlUtil::writeCallback);
        curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &mServerResponse);

        CURLcode c = curl_easy_perform(mCurl);
        curl_easy_cleanup(mCurl);


        // error checking
        if(c != CURLE_OK){
            std::cerr << "CURL ERROR: " << curl_easy_strerror(c) << '\n';
        }

    }

    return mServerResponse;
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
