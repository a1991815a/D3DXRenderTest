#ifndef __EVENT__
#define __EVENT__
#include "Vec.h"

enum EventTypes{
	ET_UNKNOWN,
	ET_KEY,
	ET_MOUSE,
	ET_CUSTOM
};

enum KeyEventTypes{
	ET_KEY_DOWN,
	ET_KEY_UP
};

enum MouseEventTypes{
	ET_MOUSE_DOWN,
	ET_MOUSE_UP,
	ET_MOUSE_MOVE
};

class Event{
	friend class MessageManager;
private:
	EventTypes m_eventType;
	char m_eventKey;
	Vec2 m_eventLocation;
	unsigned long m_param;
	void* m_data;
public:
	inline EventTypes getType() const { return m_eventType;};
	inline char getKey() const { return m_eventKey;};
	inline const Vec2& getLocation() const { return m_eventLocation;};
	inline void* getData() { return m_data; };
	inline const void* getData() const { return m_data; };
	inline unsigned long getParam() const { return m_param; };
};
#endif