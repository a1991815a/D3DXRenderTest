#ifndef __NODE__
#define __NODE__
#include "D3DXHeader.h"
#include "RenderRef.h"
#include "Ref.h"
#include "Rect.h"

class Node: public Ref, public RenderRef{
private:
	Vec2 m_position;							//位置
	Vec2 m_scale;								//缩放
	Vec3 m_rotate;								//旋转
	Vec2 m_contentSize;							//大小
	bool m_enable;								//是否可用
	bool m_visiable;							//是否可见
	bool m_updateFlag;							//是否需要更新矩阵
public:
	Node()
		:m_enable(true), m_visiable(true), m_updateFlag(true)
	{};
	~Node() {};

/*
	setter , getter
*/
	const Vec2& getPosition() const {
		return m_position;
	}
	void setPosition(const Vec2& pos) {
		m_position = pos;
		setUpdate(true);
	}
	void setPositionX(real x) {
		m_position.x = x;
		setUpdate(true);
	};
	void setPositionY(real y) {
		m_position.y = y;
		setUpdate(true);
	}
	const Vec2& getScale() const {
		return m_scale;
	}
	void setScale(const Vec2& scale) {
		m_scale = scale;
		setUpdate(true);
	}
	void setScaleX(real x) {
		m_scale.x = x;
		setUpdate(true);
	}
	void setScaleY(real y) {
		m_scale.y = y;
		setUpdate(true);
	};
	const Vec3& getRotate() const {
		return m_rotate;
	}
	void setRotate(const Vec3& rotate) {
		m_rotate = rotate;
		setUpdate(true);
	}
	void setRotateX(real x) {
		m_rotate.x = x;
		setUpdate(true);
	}
	void setRotateY(real y) {
		m_rotate.y = y;
		setUpdate(true);
	}
	void setRotateZ(real z) {
		m_rotate.z = z;
		setUpdate(true);
	}
	const Vec2& getContentSize() {
		return m_contentSize;
	}
	void setContentSize(const Vec2& size) {
		m_contentSize = size;
		setUpdate(true);
	}
	void setContentSizeWidth(real width) {
		m_contentSize.x = width;
		setUpdate(true);
	}
	void setContentSizeHeight(real height) {
		m_contentSize.y = height;
		setUpdate(true);
	}
	bool isEnable() const {
		return m_enable;
	}
	void setEnable(bool enable) {
		m_enable = enable;
	}
	bool isVisiable() const {
		return m_visiable;
	}
	void setVisiable(bool visiable) {
		m_visiable = visiable;
	}
	void update() {
		//如果无需更新矩阵
		if (!m_updateFlag)
			return;	
		D3DXMATRIX* mMatrix = getTransformMatrix();
		D3DXMATRIX matrix;
		D3DXMatrixIdentity(mMatrix);
		D3DXMatrixRotationX(&matrix, m_rotate.x);
		*mMatrix = *mMatrix * matrix;
		D3DXMatrixRotationY(&matrix, m_rotate.y);
		*mMatrix = *mMatrix * matrix;
		D3DXMatrixRotationZ(&matrix, m_rotate.z);
		*mMatrix = *mMatrix * matrix;
		D3DXMatrixScaling(&matrix, m_rotate.x, m_rotate.y, 1);
		*mMatrix = *mMatrix * matrix;
		D3DXMatrixTranslation(&matrix, m_position.x, m_position.y, 0);
		*mMatrix = *mMatrix * matrix;
		setUpdate(false);
	}																	//更新变换矩阵
	bool getUpdate() const {
		return m_updateFlag;
	}
private:
	void setUpdate(bool flag) {
		m_updateFlag = flag;
	}
};
#endif