#include "objectplane.hpp"
#include <cmath>

ObjectPlane::ObjectPlane() {

}

ObjectPlane::~ObjectPlane() {

}

bool ObjectPlane::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) {
	Ray back_ray = m_transformation_matrix.Apply(castRay, BACKWARDS);

	qbVector<double> k = back_ray.m_lab;
	k.Normalize();

	
	if (!close(k.GetElement(2), 0.0)) {
		double t = back_ray.m_point1.GetElement(2) / -k.GetElement(2);
		if (t > 0.0) {
			double u = back_ray.m_point1.GetElement(0) + t * k.GetElement(0);
			double v = back_ray.m_point1.GetElement(1) + t * k.GetElement(1);

			if (abs(u) < 1.0 && abs(v) < 1.0) {
				qbVector<double> poi = back_ray.m_point1 + t*k;

				intPoint = m_transformation_matrix.Apply(poi, FORWARDS);

				qbVector<double> local_origin = {std:: vector<double>{0.0, 0.0, 0.0}};
				qbVector<double> normal_vector = {std:: vector<double>{0.0, 0.0, -1.0}};
				qbVector<double> global_origin = m_transformation_matrix.Apply(local_origin, FORWARDS);
				localNormal = m_transformation_matrix.Apply(normal_vector, FORWARDS) - global_origin;
				localNormal.Normalize();

				localColor = m_baseColor;

				return true;
			}
		}
	}
	return false;
}
