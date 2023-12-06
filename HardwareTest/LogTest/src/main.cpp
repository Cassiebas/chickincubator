#include "Log.hpp"

int main() {
    Log log("", "test.log", "LogTest::", true); //log all levels to test.log
    log(Severity::trace, "Testing trace... done");
    log(Severity::debug, "Testing debug... done");
    log(Severity::info, "Testing info... done");
    log(Severity::warning, "Testing warning... done");
    log(Severity::error, "Testing error... done");
    log(Severity::fatal, "Testing fatal... done");
    return 0;
}