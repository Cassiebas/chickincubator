#include "Log.hpp"

Log::Log(const std::string path, const std::string filename, const std::string tag, const bool showAllSeverities) 
{
    Init(path, filename, tag, showAllSeverities);
}

// Log::Log() {

// }

Log::~Log() {
    
}

void Log::Init(const std::string path, const std::string filename, const std::string tag, const bool showAllSeverities) {    
    logtag = tag;
    logger::register_simple_formatter_factory<logger::trivial::severity_level, char>("Severity");
    logger::add_common_attributes();
    auto backend = boost::make_shared<backend_type>(
        kw::file_name = path + filename,
        kw::rotation_size = 10 * 1024 * 1024,
        kw::time_based_rotation = logger::sinks::file::rotation_at_time_point(0, 0, 0),
        kw::auto_flush = true);

    auto sink = boost::make_shared<sink_type>(backend);
    sink->set_formatter(logger::parse_formatter(g_format));
    sink->set_filter(tag_attr == logtag);

    logger::core::get()->add_sink(sink);

}

void Log::operator()(Severity level, std::string message) {
    BOOST_LOG_SCOPED_THREAD_TAG("Tag", logtag);
    switch (level) { //to avoid compiler errors
        case Severity::trace:
                // BOOST_LOG_TRIVIAL(severity_level::trace) << message;
                BOOST_LOG_SEV(g_logger, logger::trivial::trace) << message;
            break;
        case Severity::debug:
                // BOOST_LOG_TRIVIAL(severity_level::debug) << message;
                BOOST_LOG_SEV(g_logger, logger::trivial::debug) << message;
            break;
        case Severity::info:
                // BOOST_LOG_TRIVIAL(severity_level::info) << message;
                BOOST_LOG_SEV(g_logger, logger::trivial::info) << message;
            break;
        case Severity::warning:
                // BOOST_LOG_TRIVIAL(severity_level::warning) << message;
                BOOST_LOG_SEV(g_logger, logger::trivial::warning) << message;
            break;
        case Severity::error:
                // BOOST_LOG_TRIVIAL(severity_level::error) << message;
                BOOST_LOG_SEV(g_logger, logger::trivial::error) << message;
            break;
        case Severity::fatal:
                // BOOST_LOG_TRIVIAL(severity_level::fatal) << message;
                BOOST_LOG_SEV(g_logger, logger::trivial::fatal) << message;
            break;
        default:
            break;
    }
}