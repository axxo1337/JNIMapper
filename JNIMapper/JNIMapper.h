#ifndef JNIMAPPER_JNIMAPPER_H_
#define JNIMAPPER_JNIMAPPER_H_

#include <memory>
#include <map>
#include <cstdint>

#include <json.hpp> // https://github.com/nlohmann/json
#include <jni.h> // JDK17

//
// JNIHelper class
//

class JNIHelper
{
};

//
// JNITypes classes
//

class JNIField final
{
};

class JNIMethod final
{
};

class JNIClass final
{
};

//
// JNIMapper class
//

class JNIMapper final
{
public:
  JNIMapper()
  {
  }

  bool init(const std::uint8_t* p_mappings_buffer, JNIEnv* p_env)
  {
    using namespace nlohmann;

    if (is_init)
      return false;

    json mappings{ json::parse(p_mappings_buffer) };

    is_init = true;
  }

  void shutdown()
  {
    if (!is_init)
        return;

    is_init = false;
  }

private:
  bool is_init{};
};

#endif
