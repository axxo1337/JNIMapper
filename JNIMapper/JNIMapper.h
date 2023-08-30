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

    for (json::iterator it_i{ parsed_map.begin() }; it_i != mappings.end(); ++it_i)
		{
      jclass p_class{ p_env->FindClass(mappings[it_i.key()]["name"].get<std::string>().c_str()) };

      if (p_class == nullptr)
      {
        // TODO ADD LOGGING
        continue;    
      }

      JNIClass* p_jniclass{ classes.insert(std::pair{ it_i.key(), std::make_shared<JNIClass>(p_env, class_ptr) }).first.second };
      
      for (json::iterator it_j{ parsed_map[it_i.key()]["fields"].begin() }; it_j != mappings[it_i.key()]["fields"].end(); ++it_j)
      {
        jfieldID field_id{};
        std::string hash{ mappings[it_j.key()].get<std::string>() };
        char hash_indicator{ hash[0] };
        size_t delimiter_end_pos{ hash.find_last_of('|') };
        std::string hash_signature{ hash.substr(2, delimiter_end_pos - 2) };
        std::string hash_name{ hash.substr(delimiter_end_pos + 1, hash_name.size() - delimiter_end_pos - 1) };
        bool is_static{};

        if (hash_indicator == 'S')
        {
          is_static = true;
          field_id = p_env->GetStaticFieldID(p_class, hash_name.c_str(), hash_signature.c_str());
        }
        else
        {
          field_id = p_env->GetFieldID(p_class, hash_name.c_str(), hash_signature.c_str());
          if (field_id == 0 && hash_indicator == 'U')
          {
            field_id = p_env->GetStaticFieldID(p_class, hash_name.c_str(), hash_signature.c_str());
            is_static = field_id != 0;
          }
        }

         
      }
    }

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
  std::map<std::string, std::shared_ptr<JNIClass>> classes;
};

#endif
