#ifndef __MESSAGEMANAGER__
#define __MESSAGEMANAGER__
#include "SingleInstance.h"
#include <vector>
#include <set>
#include "GameStep.h"
#include "Listener.h"

#define _dispatchMessage MessageManager::getInstance()

class MessageManager: public SingleInstance<MessageManager>, public GameStep{
	DEFINE_PRIVATE_INSTANCE(MessageManager);
	//监听者节点模型
	struct ListenerNode{
		int priority;
		Listener* listener;

		ListenerNode() 
			:priority(0), listener(nullptr)
		{};
		ListenerNode(Listener* listener){
			this->priority = listener->m_priority;
			this->listener = listener;
		};
		inline bool operator<(const ListenerNode& node) const{
			return priority < node.priority;
		};
		inline bool operator==(const ListenerNode& node) const{
			return (priority == node.priority) && (listener == node.listener);
		}
	};
private:
	std::vector<Event*> m_eventList;						//消息队列
	std::multiset<ListenerNode> m_listenerList;				//监听者队列
	std::vector<char> m_keyList;
	Vec2 m_location;
public:

	inline void pushKey(char key) {
		m_keyList.push_back(key);
	};
	void setLocation(float x, float y) {
		m_location.x = x;
		m_location.y = y;
	};
	
	inline void addEventListener(Listener* listener){
		m_listenerList.insert(ListenerNode(listener));
	};
	void removeEventListener(Listener* listener);

	inline void sendMessage(Event* event){
		m_eventList.push_back(event);
	};

	void sendMessage(
		EventTypes m_eventType,
		unsigned long m_param,
		void* m_data = nullptr
		);

	void sendKeyMessage(char key, KeyEventTypes key_type);
	void sendMouseMessage(float x, float y, MouseEventTypes mouse_type);

	void clearMessage();

	virtual void loop() override;

	virtual bool init() override;

	virtual void destroy() override; 
};
#endif