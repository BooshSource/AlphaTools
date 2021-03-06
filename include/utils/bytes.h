#pragma once

#include "types.h"

/**
 * \file bytes.h
 * \brief Byte manipulation utilities
 */

namespace util {

/**
 * Gets a singular bit from a byte array, at the given index
 *
 * \param data Byte array to get from
 * \param pos Index to retrieve
 * \return Value of bit at that index
 */
bool get_bit(const uchar* data, const ulong pos);

/**
 * Get the value of a range in a byte array, as a ulong. Gets [start, end]
 *
 * \param data Byte array to get from
 * \param start Index to start at
 * \param end Index to end at
 * \return Value of the range
 */
ulong get_range(const uchar* data, const ulong start, const ulong end);

/**
 * Get the value of a range in a byte array, as a long. Gets [start, end]
 *
 * \param data Byte array to get from
 * \param start Index to start at
 * \param end Index to end at
 * \return Value of the range
 */
long get_signed_range(const uchar* data, const ulong start, const ulong end);

// Bytes to...

/**
 * Convert an array of bytes to an unsigned long, with start/end indices
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a ulong
 */
template<Endian E = Endian::BIG>
ulong btol(const uchar* bytes, const ulong start, const ulong end);

/**
 * Specialization of btol for big endian
 *
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a ulong
 */
template<>
ulong btol<Endian::BIG>(const uchar* bytes, const ulong start, const ulong end);

/**
 * Specialization of btol for little endian
 *
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a ulong
 */
template<>
ulong btol<Endian::LITTLE>(const uchar* bytes, const ulong start, const ulong end);

/**
 * Convert an array of bytes to a signed long, with start/end indices
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a long
 */
template<Endian E = Endian::BIG>
slong btol(const char* bytes, const ulong start, const ulong end);

/**
 * Specialization of btol for big endian
 *
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a long
 */
template<>
slong btol<Endian::BIG>(const char* bytes, const ulong start, const ulong end);

/**
 * Specialization of btol for little endian
 *
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a long
 */
template<>
slong btol<Endian::LITTLE>(const char* bytes, const ulong start, const ulong end);

/**
 * Convert an array of bytes to an unsigned long, with optional length of the array
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param length Length of array
 * \return Bytes interpreted as a ulong
 */
template<Endian E = Endian::BIG>
ulong btol(const uchar* bytes, const ulong length = 8);

/**
 * Convert an array of bytes to a signed long, with optional length of the array
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param length Length of array
 * \return Bytes interpreted as a long
 */
template<Endian E = Endian::BIG>
slong btol(const char* bytes, const ulong length = 8);

/**
 * Convert an array of bytes to an unsigned int, with start/end indices
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a uint
 */
template<Endian E = Endian::BIG>
uint btoi(const uchar* bytes, const ulong start, const ulong end);

/**
 * Convert an array of bytes to a signed int, with start/end indices
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as an int
 */
template<Endian E = Endian::BIG>
int btoi(const char* bytes, const ulong start, const ulong end);

/**
 * Convert an array of bytes to an unsigned int, with optional length of the array
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param length Length of array
 * \return Bytes interpreted as a uint
 */
template<Endian E = Endian::BIG>
uint btoi(const uchar* bytes, const ulong length = 4);

/**
 * Convert an array of bytes to a signed int, with optional length of the array
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param length Length of array
 * \return Bytes interpreted as an int
 */
template<Endian E = Endian::BIG>
int btoi(const char* bytes, const ulong length = 4);

/**
 * Convert an array of bytes to an unsigned short, with start/end indices
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a ushort
 */
template<Endian E = Endian::BIG>
ushort btos(const uchar* bytes, const ulong start, const ulong end);

/**
 * Convert an array of bytes to a signed short, with start/end indices
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a short
 */
template<Endian E = Endian::BIG>
short btos(const char* bytes, const ulong start, const ulong end);

/**
 * Convert an array of bytes to an unsigned short, with optional length of the array
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param length Length of array
 * \return Bytes interpreted as a ushort
 */
template<Endian E = Endian::BIG>
ushort btos(const uchar* bytes, const ulong length = 2);

/**
 * Convert an array of bytes to a signed short, with optional length of the array
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param length Length of array
 * \return Bytes interpreted as a short
 */
template<Endian E = Endian::BIG>
short btos(const char* bytes, const ulong length = 2);

/**
 * Convert an array of bytes to an unsigned char, with start/end indices
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a uchar
 */
template<Endian E = Endian::BIG>
uchar btoc(const uchar* bytes, const ulong start, const ulong end);

/**
 * Convert an array of bytes to a signed char, with start/end indices
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param start Byte index to start at
 * \param end Byte index to end at
 * \return Bytes interpreted as a char
 */
template<Endian E = Endian::BIG>
char btoc(const char* bytes, const ulong start, const ulong end);

/**
 * Convert an array of bytes to an unsigned char, with optional length of the array
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param length Length of array
 * \return Bytes interpreted as a uchar
 */
template<Endian E = Endian::BIG>
uchar btoc(const uchar* bytes, const ulong length = 1);

/**
 * Convert an array of bytes to a signed char, with optional length of the array
 *
 * \tparam E What Endianness to use
 * \param bytes Array of bytes
 * \param length Length of array
 * \return Bytes interpreted as a char
 */
template<Endian E = Endian::BIG>
char btoc(const char* bytes, const ulong length = 1);

// ...to Bytes

/**
 * Convert an unsigned long to a bytes array, with optional length of the result array
 *
 * \tparam E What Endianness to use
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<Endian E = Endian::BIG>
uchar* ltob(const ulong val, const ulong length = 8);

/**
 * Specialization of ltob for big endian
 *
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<>
uchar* ltob<Endian::BIG>(const ulong val, const ulong length);

/**
 * Specialization of ltob for big endian
 *
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<>
uchar* ltob<Endian::LITTLE>(const ulong val, const ulong length);

/**
 * Convert a signed long to a bytes array, with optional length of the result array
 *
 * \tparam E What Endianness to use
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<Endian E = Endian::BIG>
char* ltob(const slong val, const ulong length = 8);

/**
 * Specialization of ltob for big endian
 *
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<>
char* ltob<Endian::BIG>(const slong val, const ulong length);

/**
 * Specialization of ltob for big endian
 *
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<>
char* ltob<Endian::LITTLE>(const slong val, const ulong length);

/**
 * Convert an unsigned int to a bytes array, with optional length of the result array
 *
 * \tparam E What Endianness to use
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<Endian E = Endian::BIG>
uchar* itob(const uint val, const ulong length = 4);

/**
 * Convert a signed int to a bytes array, with optional length of the result array
 *
 * \tparam E What Endianness to use
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<Endian E = Endian::BIG>
char* itob(const int val, const ulong length = 4);

/**
 * Convert an unsigned short to a bytes array, with optional length of the result array
 *
 * \tparam E What Endianness to use
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<Endian E = Endian::BIG>
uchar* stob(const ushort val, const ulong length = 2);

/**
 * Convert a signed short to a bytes array, with optional length of the result array
 *
 * \tparam E What Endianness to use
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<Endian E = Endian::BIG>
char* stob(const short val, const ulong length = 2);

/**
 * Convert an unsigned char to a bytes array, with optional length of the result array
 *
 * \tparam E What Endianness to use
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<Endian E = Endian::BIG>
uchar* ctob(const uchar val, const ulong length = 1);

/**
 * Convert a signed char to a bytes array, with optional length of the result array
 *
 * \tparam E What Endianness to use
 * \param val Value to convert
 * \param length Length of the result array
 * \return New byte array
 */
template<Endian E = Endian::BIG>
char* ctob(const char val, const ulong length = 1);

}

#include "bytes.tpp"
