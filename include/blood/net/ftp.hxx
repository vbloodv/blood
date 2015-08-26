#pragma once
#if defined(USE_CURL)

#include <curl/curl.h>
#include <string>

namespace blood { namespace net {

class FTP
{
    FTP();
public:
    FTP(std::string ftp_addr, std::string ftp_user, std::string ftp_pass);

    bool downloadFile(const std::string from_ftp, const std::string to_local);
    bool uploadFile(const std::string from_local, const std::string to_ftp);
    bool getFileToString(const std::string from_ftp_file, std::string& to_str);

    void downloadoruploadarray();

    void reconnect(std::string ftp_addr, std::string ftp_user, std::string ftp_pass);

    void enableFTPS();
    
private:
    void initialize();
    void initializeProtocol();
    void processing(CURL* _curl);

private:
    std::string m_address;
    std::string m_user;
    std::string m_pass;
private:
    CURL*       m_curl;
    CURLcode    m_code;
    FILE*       m_file;
private:
    bool        m_enable_ftps;
};

} } // end blood::net

#endif // end USE_CURL
