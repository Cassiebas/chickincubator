#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <boost/log/sinks.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

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
using backend_type = logger::sinks::text_file_backend;
using sink_type = logger::sinks::synchronous_sink<backend_type>;
namespace kw = logger::keywords;

using logger_type = logger::sources::severity_logger<Severity>;
BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string);

class Log { //Wrapper class for boost::log
    private: 
        const std::string g_format = "[%TimeStamp%] (%LineID%) [%Severity%] [%Tag%]: %Message%";
        logger_type g_logger;
        std::string logtag;
    
        void Init(const std::string path = "", const std::string filename = "output.log", const std::string tag = "Log", const bool showAllSeverities = false);
    public:
        // Log(); 
        Log(const std::string path = "", const std::string filename = "output.log", const std::string tag = "Log", const bool showAllSeverities = false);
        ~Log();
        void operator()(Severity level, std::string message);
};

#endif