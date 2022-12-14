#pragma once

#include "../maths/vec/vec2.h"
#include "../maths/vec/vec3.h"
#include "../maths/mat/mat4.h"

struct ProjectionBounds
{
	float left, right, top, bottom, zNear, zFar;
	ProjectionBounds();
	ProjectionBounds(float left, float right, float top, float bottom, float zNear, float zFar);
};
class OrthographicCamera
{
private:
	// Camera's transform
	static vec2 pCameraPosition;
	static ProjectionBounds pCameraBounds;
	static float pCameraSpeed;
	static float pCameraRotationSpeed;
	static float pZoomFactor;
	static float pZoomIncrement;
	static float pRotationAngle;

	// Camera's transform matrices
	static mat4 pProjectionMatrix;
	static mat4 pCameraTranslation;
	static mat4 pCameraRotation;

	static bool IsInitialized;

private:
	static void CreateViewMatrix();

public:
	
	OrthographicCamera(float left, float right, float top, float bottom, float zNear, float zFar);

	// Setters
	static void SetPosition(const vec2& pos);
	static void Rotate(float angle);

	static void SetCameraSpeed(float cameraSpeed);
	static void SetRotationSpeed(float rotationSpeed);
	static void SetZoomSpeed(float zoomIncrement);
	
	static void ZoomIn();
	static void ZoomOut();

	static void UpdateControls();  

	// Getters
	inline static vec2 GetCameraPosition() { return pCameraPosition; }
	inline static mat4 GetProjectionMatrix() { return pProjectionMatrix; }
	inline static mat4 GetCameraTranslationMatrix() { return pCameraTranslation; }
	inline static mat4 GetCameraRotationMatrix() { return pCameraRotation; }
	inline static bool IsCameraInitialized() { return IsInitialized; }
};

