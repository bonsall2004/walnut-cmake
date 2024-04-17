#pragma once

#include "Walnut/Core/Assert.h"
#include "Walnut/Core/Buffer.h"

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

namespace Walnut
{
  class StreamReader
  {
  public:
    virtual ~StreamReader() = default;

    virtual bool IsStreamGood() const = 0;
    virtual uint64_t GetStreamPosition() = 0;
    virtual void SetStreamPosition(uint64_t position) = 0;
    virtual bool ReadData(char* destination, size_t size) = 0;

    operator bool() const { return IsStreamGood(); }

    bool ReadBuffer(Buffer& buffer, uint32_t size = 0);
    bool ReadString(std::string& string);

    template<typename Key, typename Value>
    void ReadMap(std::map<Key, Value>& map, uint32_t size = 0);

    template<typename Key, typename Value>
    void ReadMap(std::unordered_map<Key, Value>& map, uint32_t size = 0);

    template<typename Value>
    void ReadMap(std::unordered_map<std::string, Value>& map, uint32_t size = 0);

    template<typename T>
    void ReadArray(std::vector<T>& array, uint32_t size = 0);

    // Move this to the source file
    void ReadArray(std::vector<std::string>& array, uint32_t size);

    // Move this to the source file
    template<typename T>
    bool ReadRaw(T& type)
    {
      bool success = ReadData((char*)&type, sizeof(T));
      WL_CORE_ASSERT(success);
      return success;
    }

    // Move this to the source file
    template<typename T>
    void ReadObject(T& obj)
    {
      T::Deserialize(this, obj);
    }
  };
}
