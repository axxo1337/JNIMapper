#ifndef JNIMAPPER_H_
#define JNIMAPPER_H_

#include <map>
#include <cstdint>
#include <string>
#include <memory>
#include <cassert>

#include "JNITypes.h"

#include <json.hpp>
#include <jni.h>

class JNIMapper final
{
public:
	JNIMapper(const uint8_t* memory, JNIEnv* p_env)
	{
		using namespace nlohmann;
		
		parsed_map = nlohmann::json::parse(memory); 
		
		for (json::iterator it_i = parsed_map.begin(); it_i != parsed_map.end(); ++it_i) 
		{
			static bool found_version{ false };

			if (!found_version && it_i.value().is_string())
			{
				found_version = true;
				continue;
			}

			jclass class_ptr = p_env->FindClass(parsed_map[it_i.key()]["name"].get<std::string>().c_str());

			if (class_ptr == nullptr)
			{
				printf("Failed to get class %s ptr\n", it_i.key());
				assert(false);
			}

			auto p_class = std::make_shared<JNIClass>(p_env, class_ptr);
			classes.emplace(std::pair<std::string, std::shared_ptr<JNIClass>>(it_i.key(), std::move(p_class)));

			/* Get field ids */
			for (json::iterator it_j = parsed_map[it_i.key()]["fields"].begin(); it_j != parsed_map[it_i.key()]["fields"].end(); ++it_j)
			{
				jfieldID field{ 0 };

				std::string hash = it_j.value().get<std::string>();
				std::string no_indicator_hash = hash.substr(2, hash.size() - 1);

				size_t delimiter = no_indicator_hash.find("|");
				
				std::string type = no_indicator_hash.substr(0, delimiter);
				std::string name = no_indicator_hash.substr(delimiter+1, no_indicator_hash.size()-1);

				bool is_static{ false };

				/* Check if the field is static or not */
				if (hash[0] == 'S')
				{
					field = p_env->GetStaticFieldID(class_ptr, name.c_str(), type.c_str());
					is_static = true;
				}
				else
					field = p_env->GetFieldID(class_ptr, name.c_str(), type.c_str());

				assert(field != 0);

				std::shared_ptr<JNIField> p_field;

				JNIClass* p_mapped_class = classes[it_i.key()].get();

				switch (type.c_str()[0])
				{
				case 'I':
				{
					p_field = std::make_shared<JNIFieldInt>(p_env, p_mapped_class, field, is_static);
				} break;

				case 'S':
				{
					p_field = std::make_shared<JNIFieldShort>(p_env, p_mapped_class, field, is_static);
				} break;

				case 'J':
				{
					p_field = std::make_shared<JNIFieldLong>(p_env, p_mapped_class, field, is_static);
				} break;

				case 'F':
				{
					p_field = std::make_shared<JNIFieldFloat>(p_env, p_mapped_class, field, is_static);
				} break;

				case 'D':
				{
					p_field = std::make_shared<JNIFieldDouble>(p_env, p_mapped_class, field, is_static);
				} break;

				case 'Z':
				{
					p_field = std::make_shared<JNIFieldBoolean>(p_env, p_mapped_class, field, is_static);
				} break;

				case 'B':
				{
					p_field = std::make_shared<JNIFieldByte>(p_env, p_mapped_class, field, is_static);
				} break;

				case 'C':
				{
					p_field = std::make_shared<JNIFieldChar>(p_env, p_mapped_class, field, is_static);
				} break;

				case 'L':
				{
					p_field = std::make_shared<JNIFieldObject>(p_env, p_mapped_class, field, is_static);
				} break;
				}

				p_mapped_class->fields.emplace(std::pair<std::string, std::shared_ptr<JNIField>>(it_j.key(), std::move(p_field)));
			}
		}

		parsed_map.begin();
	}

	nlohmann::json& GetParsedMap()
	{
		return parsed_map;
	}

public:
	std::map<std::string, std::shared_ptr<JNIClass>> classes;

private:
	nlohmann::json parsed_map;
};

#endif