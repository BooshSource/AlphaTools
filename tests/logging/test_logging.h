#pragma once

#include <streambuf>
#include <sstream>
#include "at_tests"

class TestLogger : public testing::AbstractTest {
    
    std::streambuf* old_cout;
    std::streambuf* old_cerr;
    std::ostringstream new_cout;
    std::ostringstream new_cerr;
    
    void clear_logs();
    
    void test_root();
    void test_default_level();
    void test_normal();
    void test_format();
    void test_saving();
	void test_auto_parent();
    
public:
    
    void before_class() override;
    void before_test(std::string name) override;
    void run() override;
    void after_test(std::string name) override;
    void after_class() override;
    
};

void run_logging_tests();
