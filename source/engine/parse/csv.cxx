#include "../../../include/blood/parse/csv.hxx"
#include "../../../include/blood/common/encoding.hxx"

#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace blood::parse;
    
CSV::CSV(const char* _path, const bool _has_header)
{
    std::ifstream fin(_path, std::ios::in);
    if (fin.is_open())
    {
        std::stringstream ss;
        std::copy(std::istreambuf_iterator<char>(fin)
            , std::istreambuf_iterator<char>()
            , std::ostreambuf_iterator<char>(ss));

        parse_string_stream(ss);
        fin.close();
    }
    else
    {
        printf("config file not open\n");
    }
}

CSV::CSV(const std::string& _data_string, const bool _has_header)
: m_path(_data_string)
{
    std::stringstream ss; ss << _data_string;
    parse_string_stream(ss);
}

void CSV::parse_string_stream(std::stringstream& _ss)
{
    bool is_firstline = true;
    int count = 0;
    std::string line;
    while (!_ss.eof())
    {
        std::getline(_ss, line);
            
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        if (!line.empty())
        {
            auto row = convert_line_to_values(line);
            count += row.size();

            if (is_firstline)
            {
                m_header = row;
                is_firstline = false;
            }
            m_table.emplace_back(row);
        }
    }
    printf("Table configuration complete, %n values. ", count);
}

CSV::values CSV::convert_line_to_values(const std::string& _line)
{
    std::vector<std::string> row;
    std::string line = _line;
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
    if (!line.empty())
    {
        row = blood::fn::text::split_string(line, ',');
    }
    return row;
}

std::string CSV::get_cell(int i, int j) const
{
    return m_table[i][j];
}