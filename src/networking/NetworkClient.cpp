#include "NetworkClient.h"

using namespace sk;

NetworkClient::NetworkClient(){

}

NetworkClient::~NetworkClient(){

}


const std::string& NetworkClient::getServerResponse() const{ 
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
        curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(mCurl, CURLOPT_POST, 1L);

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(mCurl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, jsonRq.c_str());

        curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, sk::CurlUtil::writeCallback);
        curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &mServerResponse);

        curl_easy_perform(mCurl);

        curl_slist_free_all(headers);
        curl_easy_cleanup(mCurl);
    }

    return mServerResponse;
}
