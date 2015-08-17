#ifndef __MESSAGEMANAGER__
#define __MESSAGEMANAGER__
#include "SingleInstance.h"
#include <vector>
#include <set>
#include "GameStep.h"
#include "Listener.h"

#define _dispatchMessage DispatchMessage::getInstance()

class MessageManager: public SingleInstance<MessageManager>, public GameStep{
	DEFINE_PRIVATE_INSTANCE(MessageManager);
	//监听者节点模型
	struct ListenerNode{
		int priority;
		Listener* listener;

		ListenerNode();
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
public:
	inline void addEventListener(Listener* listener)
	{
		m_listenerList.insert(ListenerNode(listener));
	};
	void removeEventListener(Listener* listener);

	inline void sendMessage(Event* event){
		m_eventList.push_back(event);
	};

	void clearMessage();

	virtual void loop() override;

	virtual bool init() override;

	virtual void destroy() override; 

};
#endif