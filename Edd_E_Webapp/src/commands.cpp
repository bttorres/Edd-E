#include <functions.h>

// Initialize needed variables
int speed = 152;

// Command handler
esp_err_t cmd_handler(httpd_req_t *req)
{
  char *buf;
  size_t buf_len;
  char variable[32] = {
      0,
  };
  char value[32] = {
      0,
  };

  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1)
  {
    buf = (char *)malloc(buf_len);
    if (!buf)
    {
      httpd_resp_send_500(req);
      return ESP_FAIL;
    }
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
    {
      if (httpd_query_key_value(buf, "var", variable, sizeof(variable)) == ESP_OK &&
          httpd_query_key_value(buf, "val", value, sizeof(value)) == ESP_OK)
      {
      }
      else
      {
        free(buf);
        httpd_resp_send_404(req);
        return ESP_FAIL;
      }
    }
    else
    {
      free(buf);
      httpd_resp_send_404(req);
      return ESP_FAIL;
    }
    free(buf);
  }
  else
  {
    httpd_resp_send_404(req);
    return ESP_FAIL;
  }

  int val = atoi(value);
  int res = 0;
  // Setting the servo wheel speed
  if (!strcmp(variable, "speed"))
  {
    if (val < 50)
      val = 50;
    else if (val > 255)
      val = 255;
    speed = val;
  }
  // Setting Eddie's direction
  else if (!strcmp(variable, "car"))
  {
    if (val == 1)
    {
      // Forward
      sendVal[3] = speed;
      sendVal[4] = speed;
    }
    else if (val == 2)
    {
      // Turn Left
      sendVal[3] = 0 - speed;
      sendVal[4] = speed;
    }
    else if (val == 3)
    {
      // Stop
      sendVal[3] = 0;
      sendVal[4] = 0;
    }
    else if (val == 4)
    {
      // Turn Right
      sendVal[3] = speed;
      sendVal[4] = 0 - speed;
    }
    else if (val == 5)
    {
      // Backward
      sendVal[3] = 0 - speed;
      sendVal[4] = 0 - speed;
    }
  }
  // Sets Neck servo position
  if (!strcmp(variable, "pan"))
  {
    sendVal[0] = val;
  }
  else if (!strcmp(variable, "tilt"))
  {
    sendVal[1] = val;
  }
  else if (!strcmp(variable, "roll"))
  {
    sendVal[2] = val;
  }
  else if (!strcmp(variable, "action"))
  {
    sendVal[5] = val;
  }
  else
  {
    res = -1;
  }

  if (res)
  {
    return httpd_resp_send_500(req);
  }

  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  return httpd_resp_send(req, NULL, 0);
}
