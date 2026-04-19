//
// Author: Harry Rotheram
//
// used in conjunction with NetworkClient as a means of gaining
// server responses from HTTP requests

#ifndef CURLUTIL_H
#define CURLUTIL_H

#include <cstddef>
#include <string>
namespace sk {
    class CurlUtil{
        public:
            static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* data){
                size_t total = size * nmemb;
                data->append((char*)contents, total);
                return total;
            }
        
    };
}

#endif // !CURLUTIL_H
