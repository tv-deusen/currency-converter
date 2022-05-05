#include <stdio.h>
#include <curl/curl.h>

struct data {
  char trace_ascii; /* 1 or 0 */
};

int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp);