#ifndef JNIMAPPER_JNITypes_H_
#define JNIMAPPER_JNITypes_H_

#include <jni.h>

class JNIField;
class JNIMethod;

class JNIClass final
{
public:
	JNIClass(JNIEnv* p_env, jclass class_ptr)
		: p_env(p_env), ptr(class_ptr)
	{
	}

	jclass GetPtr()
	{
		return ptr;
	}

	jobject GetInstance()
	{
		return instance;
	}

	void SetInstance(jobject new_instance)
	{
		instance = new_instance;
	}

public:
	std::map<std::string, std::shared_ptr<JNIField>> fields;
	std::map<std::string, std::shared_ptr<JNIMethod>> method_ids;

private:
	JNIEnv* p_env;
	jclass ptr;
	jobject instance{ nullptr };
};

////////////////////////////////////////////
// JNIField
////////////////////////////////////////////

class JNIField
{
public:
	explicit JNIField(JNIEnv* p_env, JNIClass* parent, jfieldID field_id, bool is_static)
		: p_env(p_env), parent(parent), id(field_id), is_static(is_static)
	{
	}

	JNIClass* GetParent()
	{
		return parent;
	}

	jfieldID GetID()
	{
		return id;
	}

	virtual jint GetValueInt()
	{
		return 0;
	}

	virtual jboolean GetValueBoolean()
	{
		return false;
	}

	virtual jbyte GetValueByte()
	{
		return '\0';
	}

	virtual jchar GetValueChar()
	{
		return '\0';
	}

	virtual jshort GetValueShort()
	{
		return 0;
	}

	virtual jlong GetValueLong()
	{
		return 0;
	}

	virtual jfloat GetValueFloat()
	{
		return 0.f;
	}

	virtual jdouble GetValueDouble()
	{
		return 0;
	}

	virtual jobject GetValueObject()
	{
		return nullptr;
	}

	virtual void SetValueInt(jint new_value)
	{

	}

	virtual void SetValueBoolean(jboolean new_value)
	{

	}

	virtual void SetValueByte(jbyte new_value)
	{

	}

	virtual void SetValueChar(jchar new_value)
	{

	}

	virtual void SetValueShort(jshort new_value)
	{

	}

	virtual void SetValueLong(jlong new_value)
	{

	}

	virtual void SetValueFloat(jfloat new_value)
	{

	}

	virtual void SetValueDouble(jdouble new_value)
	{

	}

	virtual void SetValueObject(jobject new_value)
	{
	}
protected:
	JNIEnv* p_env;
	JNIClass* parent;
	jfieldID id;
	bool is_static;
};

class JNIFieldInt : public JNIField
{
public:
	using JNIField::JNIField;

	jint GetValueInt()
	{
		if (is_static)
			return p_env->GetStaticIntField(parent->GetPtr(), id);

		return p_env->GetIntField(parent->GetInstance(), id);
	}

	void SetValueInt(jint new_value)
	{
		if (is_static)
			return p_env->SetStaticIntField(parent->GetPtr(), id, new_value);

		return p_env->SetIntField(parent->GetInstance(), id, new_value);
	}
};

class JNIFieldBoolean : public JNIField
{
public:
	using JNIField::JNIField;

	jboolean GetValueBoolean()
	{
		if (is_static)
			return p_env->GetStaticBooleanField(parent->GetPtr(), id);

		return p_env->GetBooleanField(parent->GetInstance(), id);
	}

	void SetValueBoolean(jboolean new_value)
	{
		if (is_static)
			return p_env->SetStaticIntField(parent->GetPtr(), id, new_value);

		return p_env->SetIntField(parent->GetInstance(), id, new_value);
	}
};

class JNIFieldByte : public JNIField
{
public:
	using JNIField::JNIField;

	jbyte GetValueByte()
	{
		if (is_static)
			return p_env->GetStaticByteField(parent->GetPtr(), id);

		return p_env->GetByteField(parent->GetInstance(), id);
	}

	void SetValueByte(jchar new_value)
	{
		if (is_static)
			return p_env->SetStaticByteField(parent->GetPtr(), id, new_value);

		return p_env->SetByteField(parent->GetInstance(), id, new_value);
	}
};

class JNIFieldChar : public JNIField
{
public:
	using JNIField::JNIField;

	jchar GetValueChar()
	{
		if (is_static)
			return p_env->GetStaticCharField(parent->GetPtr(), id);

		return p_env->GetCharField(parent->GetInstance(), id);
	}

	void SetValueChar(jchar new_value)
	{
		if (is_static)
			return p_env->SetStaticCharField(parent->GetPtr(), id, new_value);

		return p_env->SetCharField(parent->GetInstance(), id, new_value);
	}
};

class JNIFieldShort : public JNIField
{
public:
	using JNIField::JNIField;

	jshort GetValueShort()
	{
		if (is_static)
			return p_env->GetStaticShortField(parent->GetPtr(), id);

		return p_env->GetShortField(parent->GetInstance(), id);
	}

	void SetValueShort(jshort new_value)
	{
		if (is_static)
			return p_env->SetStaticShortField(parent->GetPtr(), id, new_value);

		return p_env->SetShortField(parent->GetInstance(), id, new_value);
	}
};

class JNIFieldLong : public JNIField
{
public:
	using JNIField::JNIField;

	jlong GetValueLong()
	{
		if (is_static)
			return p_env->GetStaticLongField(parent->GetPtr(), id);

		return p_env->GetLongField(parent->GetInstance(), id);
	}

	void SetValueLong(jlong new_value)
	{
		if (is_static)
			return p_env->SetStaticLongField(parent->GetPtr(), id, new_value);

		return p_env->SetLongField(parent->GetInstance(), id, new_value);
	}
};

class JNIFieldFloat : public JNIField
{
public:
	using JNIField::JNIField;

	jfloat GetValueFloat()
	{
		if (is_static)
			return p_env->GetStaticFloatField(parent->GetPtr(), id);

		return p_env->GetFloatField(parent->GetInstance(), id);
	}

	void SetValueFloat(jfloat new_value)
	{
		printf("TEST\n");

		if (is_static)
			return p_env->SetStaticFloatField(parent->GetPtr(), id, new_value);

		return p_env->SetFloatField(parent->GetInstance(), id, new_value);
	}
};

class JNIFieldDouble : public JNIField
{
public:
	using JNIField::JNIField;

	jdouble GetValueDouble()
	{
		if (is_static)
			return p_env->GetStaticDoubleField(parent->GetPtr(), id);

		return p_env->GetDoubleField(parent->GetInstance(), id);
	}

	void SetValueDouble(jdouble new_value)
	{
		if (is_static)
			return p_env->SetStaticDoubleField(parent->GetPtr(), id, new_value);

		return p_env->SetDoubleField(parent->GetInstance(), id, new_value);
	}
};

class JNIFieldObject : public JNIField
{
public:
	using JNIField::JNIField;

	jobject GetValueObject()
	{
		if (is_static)
			return p_env->GetStaticObjectField(parent->GetPtr(), id);

		return p_env->GetObjectField(parent->GetInstance(), id);
	}

	void SetValueObject(jobject new_value)
	{
		if (is_static)
			return p_env->SetStaticObjectField(parent->GetPtr(), id, new_value);

		return p_env->SetObjectField(parent->GetInstance(), id, new_value);
	}
};

////////////////////////////////////////////
// JNIMethod
////////////////////////////////////////////

class JNIMethod
{

};

#endif