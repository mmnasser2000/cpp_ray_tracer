#include "camera.hpp"
#include "ray.h"
#include <math.h>

Camera::Camera() {
	m_cameraPosition = qbVector<double>	{std::vector<double> {0.0, 0.0, 1.0}};
	m_cameraLookAt = qbVector<double> {std::vector<double> {0.0, 0.0, -1.0}};
	m_cameraUp = qbVector<double> {std::vector<double> {1.0, 0.0, 0.0}};
	m_cameraLength = 1.0;
	m_cameraHorzSize = 1.0;
	m_cameraAspectRatio = 1.0;
}

void Camera::SetPosition(const qbVector<double> &newPosition) {
	m_cameraPosition = newPosition;
}
void Camera::SetLookAt(const qbVector<double> &newLookAt) {
	m_cameraLookAt = newLookAt;
}
void Camera::SetUp(const qbVector<double> &upVector) {
	m_cameraUp = upVector;
}
void Camera::SetLength(double newLength) {
	m_cameraLength = newLength;
}
void Camera::SetHorzSize(double newHorzSize) {
	m_cameraHorzSize = newHorzSize;
}
void Camera::SetAspect(double newAspect) {
	m_cameraAspectRatio = newAspect;
}

qbVector<double> Camera::GetPosition() {
	return m_cameraPosition;
}
qbVector<double> Camera::GetLookAt() {
	return m_cameraLookAt;
}
qbVector<double> Camera::GetUp() {
	return m_cameraUp;
}
double Camera::GetLength() {
	return m_cameraLength;
}
double Camera::GetHorzSize() {
	return m_cameraHorzSize;
}
double Camera::GetAspect() {
	return m_cameraAspectRatio;
}
qbVector<double> Camera::GetU() {
	return m_projectionScreenU;
}
qbVector<double> Camera::GetV() {
	return m_projectionScreenV;
}
qbVector<double> Camera::GetScreenCenter() {
	return m_projectionScreenCenter;
}

void Camera::UpdateCameraGeometry() {
	m_alignmentVector = m_cameraLookAt - m_cameraPosition;
	m_alignmentVector.Normalize();
	
	m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
	m_projectionScreenU.Normalize();
	m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
	m_projectionScreenV.Normalize();
	
	m_projectionScreenCenter = m_cameraPosition + (m_cameraLength * m_alignmentVector);
	
	m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
}

bool Camera::GenerateRay(float proScreenX, float proScreenY, Ray &cameraRay) {
	qbVector<double> screenWorldPart1 = m_projectionScreenCenter + (m_projectionScreenU * proScreenX);
	qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);
	
	cameraRay.m_point1 = m_cameraPosition;
	cameraRay.m_point2 = screenWorldCoordinate;
	cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;
	
	return true;
}

