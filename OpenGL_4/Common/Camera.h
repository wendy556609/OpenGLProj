#ifndef CAMERA_H
#define CAMERA_H

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)

#include "../header/Angel.h"
#include "Collider.h"

class Camera
{
public:
	enum class Type
	{
		PERSPECTIVE = 1,
		ORTHOGRAPHIC = 2
	};

	Collider _collider;
	bool isTouch;
	vec4 prePos;

	void updatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	void updateOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
	void updateViewLookAt(vec4 &vp, vec4 &at);
	void updateViewPosition(vec4 &vp);
	void updateLookAt(vec4 &at);

	Camera::Type getProjectionType();	// ���o�ثe����v���A

	const mat4& getProjectionMatrix(bool &bProj) const;	// ���o��v�x�}
	const mat4& getViewMatrix(bool &bView) const;			// ���o View Matrix
	const mat4& getViewProjectionMatrix() const;	// ���� VP �x�}

	Collider GetCollider() { return _collider; };

	static Camera* create();		// �إ� CCamera ������
	static Camera *getInstance();	// ���o  CCamera ������

	void destroyInstance();		// ������o�귽

protected:
	Camera();
	void initDefault();

	vec4 _viewPosition;
	vec4 _lookAt;
	vec4 _upVector;

	mat4 _projection;
	mutable mat4 _view;
	mutable mat4 _viewInv;
	mutable mat4 _viewProjection;
	Camera::Type _type;
	mutable bool _bViewDirty;		// View �x�}���e��s�L �������s���o
	mutable bool _bProjectionDirty;	// Projection �x�}���e��s�L �������s���o

	static Camera* _pCamera;
};

#endif