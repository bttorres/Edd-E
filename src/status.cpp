#include <functions.h>

// Set up web app
esp_err_t status_handler(httpd_req_t *req)
{
  static char json_response[1024];
  httpd_resp_set_type(req, "application/json");
  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  return httpd_resp_send(req, json_response, strlen(json_response));
}
