// Author: Harry Rotheram

#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <cstddef>

#include <curl/curl.h>

namespace sk {
    class NetworkClient{
        private:
            CURL* mCurl;

        private:

        public:

        public:
            NetworkClient();
            ~NetworkClient();

    };
}

#endif // !NETWORKCLIENT_H
