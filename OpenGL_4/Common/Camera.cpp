#include "Camera.h"

Camera* Camera::_pCamera = nullptr;

Camera::Camera() {
	_type = Type::PERSPECTIVE;
	_bViewDirty = true;
	_bProjectionDirty = true;
	isTouch = false;
	_collider.Init(1.0f, 1.0f, 1.0f, vec4(0.0f));
}

void Camera::destroyInstance()
{
	CC_SAFE_DELETE(_pCamera);
}

Camera* Camera::create()
{
	if (_pCamera == nullptr) {
		_pCamera = new (std::nothrow) Camera;
		_pCamera->initDefault();
	}
	return _pCamera;
}

void  Camera::initDefault()
{
	// 設定預設鏡頭的位置
	_viewPosition = vec4(0, 0, 0, 1.0f);
	_lookAt = vec4(0, 0, -1.0f, 1.0f);
	_upVector = vec4(0, 1.0f, 0, 1.0f);
	// 產生 View Matrix
	_view = LookAt(_viewPosition, _lookAt, _upVector);

	// 以常用的大小開啟透視投影作為預設的鏡頭投影方式
	_projection = Perspective(60.0, 1.0f, 1.0, 1000.0);
	_bViewDirty = true;
	_bProjectionDirty = true;
	_viewProjection = _projection * _view;	// 可以先不用計算
}

Camera* Camera::getInstance()
{
	if (_pCamera == nullptr) {
		_pCamera = new (std::nothrow) Camera;
		_pCamera->initDefault();
	}
	return _pCamera;
}

void Camera::updatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	_projection = Perspective(60.0, 1.0f, 1.0, 1000.0);
	_bProjectionDirty = true;
	_type = Type::PERSPECTIVE;
	_viewProjection = _projection * _view; // 同時更新  viewProjection matrix (可以先不用計算)
}

void Camera::updateOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	_projection = Ortho(left, right, bottom, top, nearPlane, farPlane);
	_bProjectionDirty = true;
	_type = Type::ORTHOGRAPHIC;
	_viewProjection = _projection * _view; // 同時更新  viewProjection matrix (可以先不用計算)
}

void Camera::updateViewPosition(vec4 &vp)
{
	// 產生 View Matrix
	_viewPosition = vp;
	_view = LookAt(_viewPosition, _lookAt, _upVector);
	_bViewDirty = true;
	_viewProjection = _projection * _view; // 可以先不用計算
	_collider.SetCubeCollider(vp);
}
void Camera::updateLookAt(vec4 &at)
{
	// 產生 View Matrix
	_lookAt = at;
	_view = LookAt(_viewPosition, _lookAt, _upVector);
	_bViewDirty = true;
	_viewProjection = _projection * _view;  // 可以先不用計算
}

void Camera::updateViewLookAt(vec4 &vp, vec4 &at)
{
	// 產生 View Matrix
	_viewPosition = vp;
	_lookAt = at;
	_view = LookAt(_viewPosition, _lookAt, _upVector);
	_bViewDirty = true;
	_viewProjection = _projection * _view; // 可以先不用計算
	_collider.SetCubeCollider(vp);
}

const mat4& Camera::getProjectionMatrix(bool &bProj) const
{
	bProj = _bProjectionDirty;
	if (_bProjectionDirty) _bProjectionDirty = false; // 重新取得 就設定成 false
	return _projection;
}

const mat4& Camera::getViewMatrix(bool &bView) const
{
	bView = _bViewDirty;
	if (_bViewDirty) _bViewDirty = false; // 重新取得 就設定成 false
	return _view;
}

const mat4& Camera::getViewProjectionMatrix() const
{
	return _viewProjection;
}

Camera::Type Camera::getProjectionType()
{
	return _type;
}

const vec4& Camera::getViewPosition() const	// 取的 VP 矩陣
{
	return _viewPosition;
}