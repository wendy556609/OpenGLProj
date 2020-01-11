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
	// �]�w�w�]���Y����m
	_viewPosition = vec4(0, 0, 0, 1.0f);
	_lookAt = vec4(0, 0, -1.0f, 1.0f);
	_upVector = vec4(0, 1.0f, 0, 1.0f);
	// ���� View Matrix
	_view = LookAt(_viewPosition, _lookAt, _upVector);

	// �H�`�Ϊ��j�p�}�ҳz����v�@���w�]�����Y��v�覡
	_projection = Perspective(60.0, 1.0f, 1.0, 1000.0);
	_bViewDirty = true;
	_bProjectionDirty = true;
	_viewProjection = _projection * _view;	// �i�H�����έp��
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
	_viewProjection = _projection * _view; // �P�ɧ�s  viewProjection matrix (�i�H�����έp��)
}

void Camera::updateOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	_projection = Ortho(left, right, bottom, top, nearPlane, farPlane);
	_bProjectionDirty = true;
	_type = Type::ORTHOGRAPHIC;
	_viewProjection = _projection * _view; // �P�ɧ�s  viewProjection matrix (�i�H�����έp��)
}

void Camera::updateViewPosition(vec4 &vp)
{
	// ���� View Matrix
	_viewPosition = vp;
	_view = LookAt(_viewPosition, _lookAt, _upVector);
	_bViewDirty = true;
	_viewProjection = _projection * _view; // �i�H�����έp��
	_collider.SetCubeCollider(vp);
}
void Camera::updateLookAt(vec4 &at)
{
	// ���� View Matrix
	_lookAt = at;
	_view = LookAt(_viewPosition, _lookAt, _upVector);
	_bViewDirty = true;
	_viewProjection = _projection * _view;  // �i�H�����έp��
}

void Camera::updateViewLookAt(vec4 &vp, vec4 &at)
{
	// ���� View Matrix
	_viewPosition = vp;
	_lookAt = at;
	_view = LookAt(_viewPosition, _lookAt, _upVector);
	_bViewDirty = true;
	_viewProjection = _projection * _view; // �i�H�����έp��
	_collider.SetCubeCollider(vp);
}

const mat4& Camera::getProjectionMatrix(bool &bProj) const
{
	bProj = _bProjectionDirty;
	if (_bProjectionDirty) _bProjectionDirty = false; // ���s���o �N�]�w�� false
	return _projection;
}

const mat4& Camera::getViewMatrix(bool &bView) const
{
	bView = _bViewDirty;
	if (_bViewDirty) _bViewDirty = false; // ���s���o �N�]�w�� false
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

const vec4& Camera::getViewPosition() const	// ���� VP �x�}
{
	return _viewPosition;
}