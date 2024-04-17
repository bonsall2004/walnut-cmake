#include "StreamWriter.h"

namespace Walnut
{
  void StreamWriter::WriteBuffer(Buffer buffer, bool writeSize)
  {
    if (writeSize)
      WriteData(reinterpret_cast<const char*>(&buffer.Size), sizeof(uint32_t));

    WriteData(reinterpret_cast<const char*>(buffer.Data), buffer.Size);
  }

  void StreamWriter::WriteZero(uint64_t size)
  {
    char zero = 0;
    for (uint64_t i = 0; i < size; i++)
      WriteData(&zero, 1);
  }

  void StreamWriter::WriteString(const std::string& string)
  {
    size_t size = string.size();
    WriteData(reinterpret_cast<const char*>(&size), sizeof(size_t));
    WriteData(string.data(), sizeof(char) * string.size());
  }

  void StreamWriter::WriteString(std::string_view string)
  {
    size_t size = string.size();
    WriteData(reinterpret_cast<const char*>(&size), sizeof(size_t));
    WriteData(string.data(), sizeof(char) * string.size());
  }

  // Implementation of other member functions...

  template<typename Key, typename Value>
  void StreamWriter::WriteMap(const std::map<Key, Value>& map, bool writeSize)
  {
    if (writeSize)
      WriteRaw<uint32_t>(static_cast<uint32_t>(map.size()));

    for (const auto& [key, value] : map)
    {
      if constexpr (std::is_trivial<Key>::value)
        WriteRaw<Key>(key);
      else
        WriteObject<Key>(key);

      if constexpr (std::is_trivial<Value>::value)
        WriteRaw<Value>(value);
      else
        WriteObject<Value>(value);
    }
  }

  template<typename Key, typename Value>
  void StreamWriter::WriteMap(const std::unordered_map<Key, Value>& map, bool writeSize)
  {
    if (writeSize)
      WriteRaw<uint32_t>(static_cast<uint32_t>(map.size()));

    for (const auto& [key, value] : map)
    {
      if constexpr (std::is_trivial<Key>::value)
        WriteRaw<Key>(key);
      else
        WriteObject<Key>(key);

      if constexpr (std::is_trivial<Value>::value)
        WriteRaw<Value>(value);
      else
        WriteObject<Value>(value);
    }
  }

  template<typename Value>
  void StreamWriter::WriteMap(const std::unordered_map<std::string, Value>& map, bool writeSize)
  {
    if (writeSize)
      WriteRaw<uint32_t>(static_cast<uint32_t>(map.size()));

    for (const auto& [key, value] : map)
    {
      WriteString(key);

      if constexpr (std::is_trivial<Value>::value)
        WriteRaw<Value>(value);
      else
        WriteObject<Value>(value);
    }
  }

  template<typename T>
  void StreamWriter::WriteArray(const std::vector<T>& array, bool writeSize)
  {
    if (writeSize)
      WriteRaw<uint32_t>(static_cast<uint32_t>(array.size()));

    for (const auto& element : array)
    {
      if constexpr (std::is_trivial<T>::value)
        WriteRaw<T>(element);
      else
        WriteObject<T>(element);
    }
  }

  // Explicit specialization for WriteArray<std::string>
  void StreamWriter::WriteArray(const std::vector<std::string>& array, bool writeSize)
  {
    if (writeSize)
      WriteRaw<uint32_t>(static_cast<uint32_t>(array.size()));

    for (const auto& element : array)
      WriteString(element);
  }
} // namespace Walnut
