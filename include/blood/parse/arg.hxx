#pragma once
#ifndef blood_parse_arg_hxx_
#define blood_parse_arg_hxx_

#include <list>
#include <vector>
#include <string>
#include <unordered_map>

namespace blood { namespace parse { 

class Argument
{
    friend class CommandLineParser;
    
private:
    /* Return true value if you don't want stopping the program */
    typedef bool(*RunFn)(std::string,void*);
    typedef std::string String;

    Argument();
public:
    Argument(String name);
    bool runFunction();

    void setFunction(RunFn);
    void setPrefix(bool is_prefix);
    void setTitle(String);
    void setData(void*);

    Argument& operator=(const Argument& _r); // The Argument class implements the = operator, but lacks a copy constructor. It is dangerous to use such a class

private:
    String m_name;
    String m_title;
    String m_next_value;
    RunFn  m_fn;
    bool   m_is_prefix;
    void*  m_data;
};


class CommandLineParser
{
    CommandLineParser();
public:
    CommandLineParser(int _count, char* _array[]);
    CommandLineParser(const std::vector<std::string> _args);

    void addArgument(Argument arg);
    void useEmptyListBlock(bool _block);
    void useEmptyListHelp(bool _help);

    /* Function returned true value if the program can continue*/
    bool processing();
    void help() const;

    std::string get_path() const { return m_path; };
    unsigned int getArgumentsCount() const { return m_args.size(); };

private:
    bool                                      m_use_block;
    bool                                      m_use_help;

    std::string                               m_path;
    std::list<std::string>                    m_args;
    std::unordered_map<std::string, Argument> m_keys;
};

}} // end blood::parse

#endif // blood_parse_arg_hxx_
