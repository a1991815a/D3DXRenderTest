#ifndef __SINGLEINSTANCE__
#define __SINGLEINSTANCE__

#define DEFINE_PRIVATE_INSTANCE(STY)		\
private:									\
	STY();									\
	~STY();									\
	friend class SingleInstance<STY>		\


template<typename _sTy>
class SingleInstance{
private:
	static _sTy* m_instance;
public:
	static _sTy* getInstance();
	static void destroyInstance();
};

template<typename _sTy>
_sTy* SingleInstance<_sTy>::m_instance = nullptr;

template<typename _sTy>
_sTy* SingleInstance<_sTy>::getInstance()
{
	if(m_instance == nullptr)
		m_instance = new _sTy();
	return m_instance;
}

template<typename _sTy>
void SingleInstance<_sTy>::destroyInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

#endif