#include <download.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <errno.h>

// callback function to write the data received from curl to a file, used by curl
size_t writeData(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int downloadFile(const char* url, const char* file_path) {
    CURL* curl = curl_easy_init();
    if (curl) {
        FILE* file = fopen(file_path, "wb"); // write binary
        if (!file) {
            perror("snbox: download failed: couldn't open file");
            return 1;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        CURLcode code = curl_easy_perform(curl);

        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        if (http_code != 200) {
            fprintf(stderr, "snbox: download failed: web server returned %ld\n", http_code);
            fclose(file);
            remove(file_path);
            curl_easy_cleanup(curl);
            return 1;
        }

        if (code != CURLE_OK) {
            fprintf(stderr, "snbox: download failed: curl error: %s\n", curl_easy_strerror(code));
            fclose(file);
            curl_easy_cleanup(curl);
            return 1;
        }
        fclose(file);
        curl_easy_cleanup(curl);
        return 0;
    }
    perror("snbox: download failed: curl didn't init");
    return 1;
}