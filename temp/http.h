void sendValue(HTTPClient &http, String sensor, int value) {
  http.begin(ENV_SERVER_ADDRESS, 3000);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String payload = "device=NodeMCU";
  payload += "&sensor=" + sensor;
  payload += "&value=" + String(value);

  int httpCode = http.POST(String(payload));

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println(http.errorToString(httpCode).c_str());
  }

  http.end();
}
