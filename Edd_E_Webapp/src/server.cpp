#include <functions.h>

httpd_handle_t esp_httpd = NULL;
int sendVal[6] = {139, 191, 85, 0, 0, 0};

void startServer()
{
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.max_uri_handlers = 16;
  // Perform corresponding actions when flags are received
  httpd_uri_t index_uri = {
      .uri = "/",
      .method = HTTP_GET,
      .handler = index_handler,
      .user_ctx = NULL};

  httpd_uri_t status_uri = {
      .uri = "/status",
      .method = HTTP_GET,
      .handler = status_handler,
      .user_ctx = NULL};

  httpd_uri_t cmd_uri = {
      .uri = "/control",
      .method = HTTP_GET,
      .handler = cmd_handler,
      .user_ctx = NULL};

  // Starting web server
  if (httpd_start(&esp_httpd, &config) == ESP_OK)
  {
    httpd_register_uri_handler(esp_httpd, &index_uri);
    httpd_register_uri_handler(esp_httpd, &cmd_uri);
    httpd_register_uri_handler(esp_httpd, &status_uri);
  }

  config.server_port += 1;
  config.ctrl_port += 1;
}
