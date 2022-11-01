#include "objectsphere.hpp"
#include <cmath>

ObjectSphere::ObjectSphere() {

}

ObjectSphere::~ObjectSphere() {

}

bool ObjectSphere::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) {
	Ray back_ray = m_transformation_matrix.Apply(castRay, BACKWARDS);

	qbVector<double> vhat = back_ray.m_lab;
	vhat.Normalize();
	
	double b = 2.0 * qbVector<double>::dot(back_ray.m_point1, vhat);
	double c = qbVector<double>::dot(back_ray.m_point1, back_ray.m_point1) - 1.0;
	
	double intTest = (b*b) - 4.0 * c;
	qbVector<double> poi;

	if (intTest > 0.0) {
		double numSQRT = sqrtf(intTest);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;
		
		if ((t1 < 0.0) || (t2 < 0.0)) {
			return false;
		} else {
			if (t1 < t2) {
				poi = back_ray.m_point1 + (vhat * t1);
			} else {
				poi = back_ray.m_point1 + (vhat * t2);
			}

			intPoint = m_transformation_matrix.Apply(poi, FORWARDS);

			qbVector<double> object_origin = qbVector<double> {std::vector<double> {0.0, 0.0, 0.0}};
			qbVector<double> new_object_origin = m_transformation_matrix.Apply(object_origin, FORWARDS);
			localNormal = intPoint - new_object_origin;
			localNormal.Normalize();

			localColor = m_baseColor;
		}
		
		return true;
	} else {
		return false;
	}	
}
