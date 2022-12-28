#include "socket_tools.hpp"
#include "Customer.hpp"
/*#include "client.h"*/

std::string to_string(boost::asio::streambuf &buffer)
{
    boost::asio::streambuf::const_buffers_type data = buffer.data();
    return {boost::asio::buffers_begin(data), boost::asio::buffers_end(data)};
}

template <typename _Data_type>
_Data_type get_data_from_string(const char *s)
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
std::string get_string_from_data(const _Data_type& data)
{
        boost::asio::streambuf buf;
        std::ostream os(&buf);
        boost::archive::text_oarchive ar(os);
        ar << data;
        auto s = to_string(buf);
        std::cout << data << std::endl;
        //s += " 01";
        //std::cout << s.substr(s.length() - 2, 2) << std::endl;
        //std::cout << move(s) << std::endl;
        return std::move(s);
}
template
Client get_data_from_string(const char* s);
template
std::string get_string_from_data(const Client& data);

template
Compte get_data_from_string(const char* s);
template
std::string get_string_from_data(const Compte& data);