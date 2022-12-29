#include "socket_tools.hpp"
#include "client.hpp"
/*#include "client.h"*/

std::string to_string(boost::asio::streambuf &buffer)
{
    boost::asio::streambuf::const_buffers_type data = buffer.data();
    return {boost::asio::buffers_begin(data), boost::asio::buffers_end(data)};
}

template <typename _Data_type>
_Data_type get_data_from_string(const char* s)
{
    _Data_type data; //Client data
    boost::asio::streambuf buf; 
    std::ostream output(&buf);
    output << s;
    std::istream is(&buf);
    boost::archive::text_iarchive ia(is);
    ia >> data;
    return std::move(data);
}

template <typename _Data_type>
std::string get_string_from_data(const _Data_type& data,int demande_type)
{
        boost::asio::streambuf buf;
        std::ostream os(&buf);
        boost::archive::text_oarchive ar(os);
        ar << data;
        auto s = to_string(buf);
        s += " ";
        s+= std::to_string(demande_type);
        return std::move(s);
}

std::string get_data_from_string0(std::string s) {
    int tmp = s.length();
    while (s[tmp - 1] != '1' && s[tmp - 1] != '2' && s[tmp - 1] != '3' && s[tmp - 1] != '4' && s[tmp - 1] != '5' && s[tmp - 1] != '6' && s[tmp - 1] != '7' && s[tmp - 1] != '8' && s[tmp - 1] != '9') {
        tmp -= 1;
    }
    std::string tmp2 = s.substr(tmp - 2, 2);
    return tmp2;

}
template
Client get_data_from_string(const char* s);
template
std::string get_string_from_data(const Client& data,int demande_type);

template
Compte get_data_from_string(const char* s);
template
std::string get_string_from_data(const Compte& data,int demande_type);