//
// Created by lim on 20. 9. 10.
//

#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <curl.h>

struct memory {
    char *response;
    size_t size;
};
struct memory chunk;

static size_t cb(void *data, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *) userp;

    char *ptr = (char *) realloc(mem->response, mem->size + realsize + 1);
    if (ptr == NULL)
        return 0;  /* out of memory! */

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}


char *baz() {
    CURL *curl;
    CURLcode res;
    char *postthis = NULL;

    curl = curl_easy_init();
    printf("curl : %s", curl);
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        postthis = (char *) "{\"test\":\"test\"}";
        struct curl_slist *header = NULL;
        header = curl_slist_append(header, "Content-Type: application/json");
        header = curl_slist_append(header, "Accept-Charset: UTF-8");
        header = curl_slist_append(header, "User-Agent: MCW/v1/TheCryptoAssetsCo.");
        header = curl_slist_append(header, "TestHeader: test");

        syslog(LOG_CRIT, "%s .......\n%s", (char *) header, (char *) postthis);

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
        curl_easy_setopt(curl, CURLOPT_URL, "https://devapi.mycoldwallet.io/v1/TestAPI");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_POST, true);

        /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);

        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

        res = curl_easy_perform(curl);

        /* always cleanup */
        //curl_easy_cleanup(curl);

        /* free the custom headers */
        //curl_slist_free_all(header);
        if (res != CURLE_OK) {
            //fprintf(stderr, "curl_easy_perform() failed : %s\n", curl_easy_strerror(res));
            return (char *) "failed";
        } else {
            syslog(LOG_CRIT, "chunk.size : %lu", (long) chunk.size);

        }
        return (chunk.response);
    }
    return (char *) "failed";
}


extern "C" JNIEXPORT jstring
Java_com_example_curl_1ex5_MainActivity_foo(JNIEnv *env, jobject thiz) {
    jstring msg = env->NewStringUTF(baz());
    return msg;
}