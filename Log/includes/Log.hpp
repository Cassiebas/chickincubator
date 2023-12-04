#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logger = boost::log;
namespace keywords = boost::log::keywords;
using Severity = logger::trivial::severity_level;
    // {
    //     trace,
    //     debug,
    //     info,
    //     warning,
    //     error,
    //     fatal
    // }


class Log { //Wrapper class for boost::log
    private: 
        
    public: 
        Log(const std::string path = "", const std::string filename = "output.log", const bool showAllSeverities = false);
        ~Log();
        void operator()(Severity level, std::string message);
};

#endif