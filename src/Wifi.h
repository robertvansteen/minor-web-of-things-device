class Wifi
{
  public:
    Wifi(char const* ssid, char const* password);
    void connect();
  private:
    const char* _ssid;
    const char* _password;
};
