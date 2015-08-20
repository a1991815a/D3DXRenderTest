#ifndef __NODE__
#define __NODE__
#include "D3DXHeader.h"
#include "RenderObject.h"
#include "Ref.h"
#include "Rect.h"
#include "Vector.h"

#define CREATE_FUNC(RET)		\
static RET* create(){			\
	RET* ret = nullptr;			\
	gbAlloc(ret);				\
	if(ret && ret->init()){		\
		return ret;				\
	}							\
	gbDealloc(ret);				\
	return nullptr;				\
}

class Node: public Ref, public RenderObject{
private:
	Vec3				m_anchontPoint;						//锚点
	Vec2				m_position;							//位置
	Vec2				m_scale;							//缩放
	Vec3				m_rotate;							//旋转
	Vec2				m_contentSize;						//大小
	bool				m_enable;							//是否可用
	bool				m_visiable;							//是否可见
	bool				m_updateFlag;						//是否需要更新矩阵

	Node*				m_parent;							//父亲
	Vector<Node*>		m_childs;							//孩子

	int					m_tag;								//标记
	std::string			m_name;								//名字

	int					m_local;							//本地顺序
	int					m_global;							//全局顺序

	D3DXMATRIX			mMatrix;							//模型矩阵
protected:
	inline Vector<Node*>& getChilds(){
		return m_childs;
	}
public:
	Node()
		:m_anchontPoint(0, 0, 0), m_position(), m_scale(1, 1), m_rotate(),
		m_contentSize(),
		m_enable(true), m_visiable(true), m_updateFlag(true),
		m_parent(nullptr), m_childs(),m_tag(INT_MIN), m_name(),
		m_local(0), m_global(0)
	{
		D3DXMatrixIdentity(&mMatrix);
	};
	~Node() {
		m_childs.clear();
	};
	virtual void pushQuadCommand();							//发送渲染数据
/*
	父子操作
*/
	inline void addChild(Node* node){
		m_childs.push_back(node);
		node->m_parent = this;
	}

	inline Node* searchChild(int tag){
		auto itor = m_childs.begin();
		for (; itor != m_childs.end(); ++itor)
			if((*itor)->m_tag == tag)
				return *itor;
	}
	inline Node* searchChild(const std::string& name){
		auto itor = m_childs.begin();
		for (; itor != m_childs.end(); ++itor)
			if((*itor)->m_name == name)
				return *itor;
	}
	inline const Node* searchChild(int tag) const{
		auto itor = m_childs.begin();
		for (; itor != m_childs.end(); ++itor)
			if((*itor)->m_tag == tag)
				return *itor;
	}
	inline const Node* searchChild(const std::string& name) const{
		auto itor = m_childs.begin();
		for (; itor != m_childs.end(); ++itor)
			if((*itor)->m_name == name)
				return *itor;
	}
	inline void delChild(int tag){
		auto itor = m_childs.begin();
		for (; itor != m_childs.end(); ++itor)
		{
			if((*itor)->m_tag == tag)
			{
				m_childs.erase(itor);
				break;
			}
		}
	}
	inline void delChild(const std::string& name){
		auto itor = m_childs.begin();
		for (; itor != m_childs.end(); ++itor)
		{
			if((*itor)->m_name == name)
			{
				m_childs.erase(itor);
				break;
			}
		}
	}
	inline void delChild(const Node* node){
		auto itor = m_childs.begin();
		for (; itor != m_childs.end(); ++itor)
		{
			if((*itor) == node)
			{
				m_childs.erase(itor);
				break;
			}
		}
	}
/*
	setter , getter
*/
	inline void setLocalZ(int z){
		m_local = z;
	}
	inline void setGlobalZ(int z){
		m_global = z;
	}
	inline int getLocal() const{
		return m_local;
	}
	inline int getGlobal() const{
		return m_global;
	}

	inline const std::string& getName() const{
		return m_name;
	}
	inline void setName(const std::string& name){
		m_name = name;
	}
	inline int getTag() const{
		return m_tag;
	}
	inline void setTag(int tag){
		m_tag = tag;
	}

	const Vec3& getAnchontPoint() const{
		return m_anchontPoint;
	}
	void setAnchontPoint(real x, real y){
		m_anchontPoint.x = x;
		m_anchontPoint.y = y;
	};

	void setAnchontPoint(const Vec2& point){
		m_anchontPoint.x = point.x;
		m_anchontPoint.y = point.y;
	}
	void setAnchontPointX(real x){
		m_anchontPoint.x = x;
	}
	void setAnchontPointY(real y){
		m_anchontPoint.y = y;
	}

	const Vec2& getPosition() const {
		return m_position;
	}
	void setPosition(const Vec2& pos) {
		m_position = pos;
		setUpdate(true);
	}
	void setPosition(real x, real y){
		m_position.x = x;
		m_position.y = y;
		setUpdate(true);
	};

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
	void setContentSize(real width, real height){
		m_contentSize.x = width;
		m_contentSize.y = height;
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
	inline const D3DXMATRIX* getTransformMatrix() const {
		return &mMatrix;
	}
	void update();															//更新变换矩阵
	bool getUpdate() const {
		return m_updateFlag;
	}
private:
	void setUpdate(bool flag) {
		m_updateFlag = flag;
	}
};
#endif