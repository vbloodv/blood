#pragma once
#include <vector>
#include <string>
namespace blood { namespace fn { namespace text {
            std::string               convert_unicode_to_multy(std::wstring in);
            std::wstring              convert_multy_to_unicode(std::string  in);
            std::wstring              convert_string_to_unicode(std::string in);

            std::string               replace(std::string& in, const std::string& from, const std::string& to);
            std::wstring              replace(std::wstring& in, const std::wstring& from, const std::wstring& to);

            std::vector<std::string>  split_string(std::string in, const char symbol);
            std::vector<std::wstring> split_wstring(std::wstring in, const wchar_t symbol);

            bool is_number(std::string in);

}}} // end blood::fn::text;