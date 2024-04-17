#pragma once

#include "Walnut/Core/Assert.h"
#include "Walnut/Core/Buffer.h"

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

namespace Walnut
{
  class StreamWriter
  {
  public:
    virtual ~StreamWriter() = default;

    virtual bool IsStreamGood() const = 0;
    virtual uint64_t GetStreamPosition() = 0;
    virtual void SetStreamPosition(uint64_t position) = 0;
    virtual bool WriteData(const char* data, size_t size) = 0;

    operator bool() const { return IsStreamGood(); }

    void WriteBuffer(Buffer buffer, bool writeSize = true);
    void WriteZero(uint64_t size);
    void WriteString(const std::string& string);
    void WriteString(std::string_view string);

    template<typename T>
    void WriteRaw(const T& type)
    {
      bool success = WriteData(reinterpret_cast<const char*>(&type), sizeof(T));
      WL_CORE_ASSERT(success);
    }

    template<typename T>
    void WriteObject(const T& obj)
    {
      T::Serialize(this, obj);
    }

    template<typename Key, typename Value>
    void WriteMap(const std::map<Key, Value>& map, bool writeSize = true);

    template<typename Key, typename Value>
    void WriteMap(const std::unordered_map<Key, Value>& map, bool writeSize = true);

    template<typename Value>
    void WriteMap(const std::unordered_map<std::string, Value>& map, bool writeSize = true);

    template<typename T>
    void WriteArray(const std::vector<T>& array, bool writeSize = true);

  private:
    void WriteArray(const std::vector<std::string>& array, bool writeSize);
  };
} // namespace Walnut

