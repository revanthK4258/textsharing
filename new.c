#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Callback function to write the data received from the server into a string
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    size_t total_size = size * nmemb;
    strncat(data, (char *)ptr, total_size);
    return total_size;
}

int main() {
    CURL *curl;
    CURLcode res;
    char url[] = "https://www.youtube.com/";
    char response[1000000] = ""; // Adjust the size of this buffer as needed

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%s\n", response);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
