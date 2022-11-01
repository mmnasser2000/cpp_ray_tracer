#include "objectabst.hpp"
#include <math.h>

#define EPSILON 1e-21f;

ObjectAbstract::ObjectAbstract() {
	
}
ObjectAbstract::~ObjectAbstract() {

}

bool ObjectAbstract::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) {
	return false;
}

bool ObjectAbstract::close(const double f1, const double f2) {
	return fabs(f1-f2) < EPSILON;
}

void ObjectAbstract::SetTransformMatrix(const GeoTransformation &transformation) {
	m_transformation_matrix = transformation;
}