
#include "tests/abstract_test.h"

namespace testing {

AbstractTest::~AbstractTest() = default;

bool AbstractTest::skip_class() {
    return false;
}

bool AbstractTest::skip_test(std::string) {
    return false;
}

void AbstractTest::before_class() {}

void AbstractTest::before_test(std::string) {}

void AbstractTest::after_test(std::string) {}

void AbstractTest::after_class() {}

}
