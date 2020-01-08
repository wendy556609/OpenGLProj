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

	Camera::Type getProjectionType();	// 取得目前的投影型態

	const mat4& getProjectionMatrix(bool &bProj) const;	// 取得投影矩陣
	const mat4& getViewMatrix(bool &bView) const;			// 取得 View Matrix
	const mat4& getViewProjectionMatrix() const;	// 取的 VP 矩陣

	Collider GetCollider() { return _collider; };

	static Camera* create();		// 建立 CCamera 的實體
	static Camera *getInstance();	// 取得  CCamera 的實體

	void destroyInstance();		// 釋放取得資源

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
	mutable bool _bViewDirty;		// View 矩陣內容更新過 必須重新取得
	mutable bool _bProjectionDirty;	// Projection 矩陣內容更新過 必須重新取得

	static Camera* _pCamera;
};

#endif