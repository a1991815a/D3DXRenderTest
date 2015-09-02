#ifndef __NUMBER__
#define __NUMBER__
#include "Node.h"
#include "Vector.h"
#include "SpriteFrame.h"

class Number: public Node{
public:
	enum NumTypes{
		WHITE,
		BLUE,
		GREEN,
		YELLOW,
		WHITE_SM,
		YELLOW_SM,
		BLUE_SM,
		WHITE_LG,
		RED_VLG,
		RED
	};
	inline NumTypes getType() const {
		return m_type;
	}
	static Number* create(NumTypes type, bool isLv = false);
	void setValue(int val);
	inline int getValue() const {
		return m_num;
	};

	bool getLvTag() const{
		return m_isLv;
	}

	virtual void visit() override;
private:
	int m_num;
	Vector<SpriteFrame*> m_frame;
	NumTypes m_type;
	SpriteFrame* getNumFrame(int num);
	bool m_isLv;
};
#endif