#pragma once

#include <string>
#include "types.h"

namespace util {

std::string reverse(const std::string& str);

bool starts_with(const std::string& val, const std::string& start);

bool ends_with(const std::string& val, const std::string& end);

std::string to_uppercase(const std::string& str);

std::string to_lowercase(const std::string& str);

template<Endian E = BIG>
std::string btoh(const uchar* val, const ulong length, const bool prefix = true, const bool pad = false);

template<Endian E = BIG>
std::string btoh(const char* val, const ulong length, const bool prefix = true, const bool pad = false);

template<Endian E = BIG>
std::string ltoh(const ulong val, bool prefix = true, bool pad = false);

template<Endian E = BIG>
std::string ltoh(const slong val, bool prefix = true, bool pad = false);

template<Endian E = BIG>
std::string itoh(const uint val, bool prefix = true, bool pad = false);

template<Endian E = BIG>
std::string itoh(const int val, bool prefix = true, bool pad = false);

template<Endian E = BIG>
std::string stoh(const ushort val, bool prefix = true, bool pad = false);

template<Endian E = BIG>
std::string stoh(const short val, bool prefix = true, bool pad = false);

template<Endian E = BIG>
std::string ctoh(const uchar val, bool prefix = true, bool pad = false);

template<Endian E = BIG>
std::string ctoh(const char val, bool prefix = true, bool pad = false);

}

#include "strmanip.tpp"
