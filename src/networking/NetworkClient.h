// Author: Harry Rotheram

#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "../utils/CurlUtil.h"
#include <cstddef>
#include <SFML/Graphics.hpp>
#include <curl/curl.h>
#include <string>
#include <sstream>

namespace sk {
    class NetworkClient{
        private:
            CURL* mCurl;
            const std::string mDomain = "https://sketchle.up.railway.app/api";
            std::string mToken = "";

            std::string mServerResponse;

        private:
            void addTokenHeader(curl_slist*& headers);

        public:

        public:
            NetworkClient();
            ~NetworkClient();
            const std::string& getServerResponse() const;
            const std::string& attemptLogin(std::string username, std::string password);
            const std::string attemptImageSubmit(sf::Image image);


    };
}

#endif // !NETWORKCLIENT_H
