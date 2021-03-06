/**
 * @file util/iodevice.cpp
 *
 * Implementation of I/O device type.
 */
#include <memory>
#include "mlearn/util/iodevice.h"



namespace mlearn {



IODevice& IODevice::operator<<(bool val)
{
	write(reinterpret_cast<char *>(&val), sizeof(bool));
	return (*this);
}



IODevice& IODevice::operator<<(float val)
{
	write(reinterpret_cast<char *>(&val), sizeof(float));
	return (*this);
}



IODevice& IODevice::operator<<(int val)
{
	write(reinterpret_cast<char *>(&val), sizeof(int));
	return (*this);
}



IODevice& IODevice::operator<<(const std::string& val)
{
	int len = val.size() + 1;

	(*this) << len;
	write(val.c_str(), len);
	return (*this);
}



IODevice& IODevice::operator>>(bool& val)
{
	read(reinterpret_cast<char *>(&val), sizeof(bool));
	return (*this);
}



IODevice& IODevice::operator>>(float& val)
{
	read(reinterpret_cast<char *>(&val), sizeof(float));
	return (*this);
}



IODevice& IODevice::operator>>(int& val)
{
	read(reinterpret_cast<char *>(&val), sizeof(int));
	return (*this);
}



IODevice& IODevice::operator>>(std::string& val)
{
	int len;
	(*this) >> len;

	std::unique_ptr<char[]> buffer(new char[len]);
	read(buffer.get(), len);

	val = std::string(buffer.get());
	return (*this);
}



}
