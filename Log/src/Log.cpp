#include "Log.hpp"

Log::Log(const std::string path, const std::string filename, const std::string tag, const bool showAllSeverities) {
    auto backend = boost::make_shared<backend_type>(
        kw::file_name = path + file + "_%N.log",
        kw::rotation_size = 10 * 1024 * 1024,
        kw::time_based_rotation = logger::sinks::file::rotation_at_time_point(0, 0, 0),
        kw::auto_flush = true);

    auto sink = boost::make_shared<sink_type>(backend);
    sink->set_formatter(logger::parse_formatter(g_format));
    sink->set_filter(tag_attr == tag_);

    logger::core::get()->add_sink(sink);
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