#include "Log.hpp"

Log::Log(const std::string path, const std::string filename, const bool showAllSeverities) {
    logger::register_simple_formatter_factory<Severity, char>("Severity");

    logger::add_file_log
    (
        keywords::file_name = path + filename,
        keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
    );
    if (!showAllSeverities) {
        logger::core::get()->set_filter
        (
            logger::trivial::severity >= logger::trivial::info
        );
    }

    logger::add_common_attributes();
}

Log::~Log() {
    
}

void Log::operator()(Severity level, std::string message) {
    switch (level) { //to avoid compiler errors
        case Severity::trace:
                BOOST_LOG_TRIVIAL(severity_level::trace) << message;
            break;
        case Severity::debug:
                BOOST_LOG_TRIVIAL(severity_level::debug) << message;
            break;
        case Severity::info:
                BOOST_LOG_TRIVIAL(severity_level::info) << message;
            break;
        case Severity::warning:
                BOOST_LOG_TRIVIAL(severity_level::warning) << message;
            break;
        case Severity::error:
                BOOST_LOG_TRIVIAL(severity_level::error) << message;
            break;
        case Severity::fatal:
                BOOST_LOG_TRIVIAL(severity_level::fatal) << message;
            break;
        default:
            break;
    }
}