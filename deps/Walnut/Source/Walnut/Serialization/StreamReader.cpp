#include "StreamReader.h"

namespace Walnut
{
  bool StreamReader::ReadBuffer(Buffer& buffer, uint32_t size)
  {
    buffer.Size = size;
    if (size == 0)
    {
      if (!ReadData((char*)&buffer.Size, sizeof(uint32_t)))
        return false;
    }

    buffer.Allocate(buffer.Size);
    return ReadData((char*)buffer.Data, buffer.Size);
  }

  bool StreamReader::ReadString(std::string& string)
  {
    size_t size;
    if (!ReadData((char*)&size, sizeof(size_t)))
      return false;

    string.resize(size);
    return ReadData((char*)string.data(), sizeof(char) * size);
  }

  template<typename Key, typename Value>
  void StreamReader::ReadMap(std::map<Key, Value>& map, uint32_t size)
  {
    if (size == 0)
      ReadRaw<uint32_t>(size);

    for (uint32_t i = 0; i < size; i++)
    {
      Key key;
      if constexpr (std::is_trivial<Key>())
        ReadRaw<Key>(key);
      else
        ReadObject<Key>(key);

      if constexpr (std::is_trivial<Value>())
        ReadRaw<Value>(map[key]);
      else
        ReadObject<Value>(map[key]);
    }
  }

  template<typename Key, typename Value>
  void StreamReader::ReadMap(std::unordered_map<Key, Value>& map, uint32_t size)
  {
    if (size == 0)
      ReadRaw<uint32_t>(size);

    for (uint32_t i = 0; i < size; i++)
    {
      Key key;
      if constexpr (std::is_trivial<Key>())
        ReadRaw<Key>(key);
      else
        ReadObject<Key>(key);

      if constexpr (std::is_trivial<Value>())
        ReadRaw<Value>(map[key]);
      else
        ReadObject<Value>(map[key]);
    }
  }

  template<typename Value>
  void StreamReader::ReadMap(std::unordered_map<std::string, Value>& map, uint32_t size)
  {
    if (size == 0)
      ReadRaw<uint32_t>(size);

    for (uint32_t i = 0; i < size; i++)
    {
      std::string key;
      ReadString(key);

      if constexpr (std::is_trivial<Value>())
        ReadRaw<Value>(map[key]);
      else
        ReadObject<Value>(map[key]);
    }
  }

  // Explicit specialization for ReadArray<std::string>
  void StreamReader::ReadArray(std::vector<std::string>& array, uint32_t size)
  {
    if (size == 0)
      ReadRaw<uint32_t>(size);

    array.resize(size);

    for (uint32_t i = 0; i < size; i++)
      ReadString(array[i]);
  }
}
