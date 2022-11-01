#include "pointlight.hpp"

#define PI 3.141592653589793238

PointLight::PointLight() {
    m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
    m_intensity = 1.0;
}

PointLight::~PointLight() {

}

bool PointLight::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                         const std::vector<std::shared_ptr<ObjectAbstract>> &objectList,
                                         const std::shared_ptr<ObjectAbstract> &currentObject,
                                         qbVector<double> &color, double &intensity) {
	qbVector<double> lightDirection = (m_location - intPoint).Normalized();
	double lightDistance = (m_location - intPoint).norm();

    qbVector<double> startPoint = intPoint;

	Ray lightRay (startPoint, startPoint + lightDirection);
    
	qbVector<double> poi {3};
	qbVector<double> poiNormal {3};
	qbVector<double> poiColor{3};
	bool validInt = false;
	for (auto sceneObject : objectList) {
		if (sceneObject != currentObject) {
			validInt = sceneObject-> TestIntersection(lightRay, poi, poiNormal, poiColor);
            if (validInt) {
                double dist = (poi - startPoint).norm();
                if (dist > lightDistance) {
                    validInt = false;
                }
            }
		}
        
		if (validInt) {
			break;
        }
	}
    
	if (!validInt) {
		double angle = acos(qbVector<double>::dot(localNormal, lightDirection));
		
		if (angle > PI / 2) {
			color = m_color;
			intensity = 0.0;
			return false;
		} else {
			color = m_color;
			intensity = m_intensity * (1.0 - (angle / (PI / 2)));
			return true;
		}
	} else {
		color = m_color;
		intensity = 0.0;
		return false;
	}
}