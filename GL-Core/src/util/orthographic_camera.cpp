#include "orthographic_camera.h"
#include "../maths/constants.h"
#include <cassert>

#include "../util/input.h"

vec2 OrthographicCamera::pCameraPosition;
ProjectionBounds OrthographicCamera::pCameraBounds;
float OrthographicCamera::pCameraSpeed = 4.0f;
float OrthographicCamera::pCameraRotationSpeed = 1.0f;
float OrthographicCamera::pZoomFactor = 1.0f;
float OrthographicCamera::pZoomIncrement = 0.1f;
float OrthographicCamera::pRotationAngle = 0.0f;
 
mat4 OrthographicCamera::pProjectionMatrix;
mat4 OrthographicCamera::pCameraTranslation;
mat4 OrthographicCamera::pCameraRotation;
bool OrthographicCamera::IsInitialized = false;

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, float zNear, float zFar)
{
	IsInitialized = true;
	
	pProjectionMatrix = orthographic(left, right, top, bottom, zNear, zFar);
	pCameraBounds = { left, right, top, bottom, zNear, zFar };

	CreateViewMatrix();
}

void OrthographicCamera::SetPosition(const vec2& pos)
{
	pCameraPosition = pos;

	CreateViewMatrix();
}

void OrthographicCamera::SetZoomSpeed(float zoomIncrement)
{
	if (zoomIncrement > 500.0f || zoomIncrement < 0.0f)
	{
		std::cout << "Use a value between 1 and 500" << std::endl;
		assert(false);
		return;
	}
	pZoomIncrement = zoomIncrement / 1000.0f;
}
void OrthographicCamera::SetCameraSpeed(float cameraSpeed)
{
	pCameraSpeed = cameraSpeed;
}
void OrthographicCamera::SetRotationSpeed(float rotationSpeed)
{
	pCameraRotationSpeed = rotationSpeed;
}

void OrthographicCamera::ZoomIn()
{
	pZoomFactor -= pZoomIncrement;
	if (pZoomFactor <= 0.05f)
		pZoomFactor = 0.05f;
	else
		pProjectionMatrix = orthographic(pCameraBounds.left * pZoomFactor, pCameraBounds.right * pZoomFactor, pCameraBounds.top * pZoomFactor, pCameraBounds.bottom * pZoomFactor, pCameraBounds.zNear, pCameraBounds.zFar);
}

void OrthographicCamera::ZoomOut()
{
	pZoomFactor += pZoomIncrement;
	if (pZoomFactor >= 5.0f)
		pZoomFactor = 5.0f;
	else
		pProjectionMatrix = orthographic(pCameraBounds.left * pZoomFactor, pCameraBounds.right * pZoomFactor, pCameraBounds.top * pZoomFactor, pCameraBounds.bottom * pZoomFactor, pCameraBounds.zNear, pCameraBounds.zFar);
}
void OrthographicCamera::Rotate(float angle)
{
	pRotationAngle = angle;

	CreateViewMatrix();
}

void OrthographicCamera::CreateViewMatrix()
{
	pCameraTranslation = translate(vec3(-pCameraPosition.x, -pCameraPosition.y, 0.0f));
	pCameraRotation = rotate(TO_RADIANS(pRotationAngle), vec3(0.0f, 0.0f, 1.0f));
}

void OrthographicCamera::UpdateControls()
{
	// Camera controls
	if (Input::IsKeyHold(KEY_A))
		pCameraPosition.x -= pCameraSpeed;
	if (Input::IsKeyHold(KEY_D))
		pCameraPosition.x += pCameraSpeed;
	if (Input::IsKeyHold(KEY_W))
		pCameraPosition.y += pCameraSpeed;
	if (Input::IsKeyHold(KEY_S))
		pCameraPosition.y -= pCameraSpeed;

	if (Input::IsKeyHold(KEY_LEFT))
	{
		pRotationAngle -= pCameraRotationSpeed;
		Rotate(pRotationAngle);
	}
	if (Input::IsKeyHold(KEY_RIGHT))
	{
		pRotationAngle += pCameraRotationSpeed;
		Rotate(pRotationAngle);
	}
	if (Input::IsMouseScrollUp())
		ZoomIn();
	if (Input::IsMouseScrollDown())
		ZoomOut();

	// Reset's the camera's transform
	if (Input::IsKeyHold(KEY_R))
	{
		pCameraPosition = { 0.0f, 0.0f };
		pRotationAngle = 0.0f;
		pZoomFactor = 1.0f;

		pProjectionMatrix = orthographic(pCameraBounds.left * pZoomFactor, pCameraBounds.right * pZoomFactor, pCameraBounds.top * pZoomFactor, pCameraBounds.bottom * pZoomFactor, pCameraBounds.zNear, pCameraBounds.zFar);
	}
	CreateViewMatrix();
}

ProjectionBounds::ProjectionBounds()
	:left(-1), right(1), top(1), bottom(-1), zNear(1.0f), zFar(-1.0f)
{
}

ProjectionBounds::ProjectionBounds(float left, float right, float top, float bottom, float zNear, float zFar)
	:left(left), right(right), top(top), bottom(bottom), zNear(zNear), zFar(zFar)
{
}
