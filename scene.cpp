#include "scene.h"

Scene::Scene() {
	const int PI = 3.141592653589793238;
	m_camera.SetPosition(qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetLookAt(qbVector<double>{std::vector<double> {0.0, 0.0, -1.0}} );
	m_camera.SetUp(qbVector<double>{std::vector<double> {0.0, 1.0, 0.0}} );
	m_camera.SetHorzSize(1.0);
	m_camera.SetAspect(1280.0 / 720.0);
	m_camera.UpdateCameraGeometry();
	
	int sphere1_idx = 0;
	int sphere2_idx = 1;
	int cone1_idx = 2;
	int plane1_idx = 3;
	m_objects.push_back(std::make_shared<ObjectSphere> (ObjectSphere()));
	m_objects.push_back(std::make_shared<ObjectSphere> (ObjectSphere()));
	m_objects.push_back(std::make_shared<ObjectCone> (ObjectCone()));
	m_objects.push_back(std::make_shared<ObjectPlane> (ObjectPlane()));
	

	GeoTransformation m_sphere1, m_sphere2, m_cone1,  m_plane1;
	m_sphere1.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, -5.0}},
					qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});
														
	m_sphere2.SetTransform(qbVector<double>{std::vector<double>{-1.0, 0.0, -3.0}},
					qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
													
	m_cone1.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, -3.0}},
					qbVector<double>{std::vector<double>{PI/2, PI, 0.0}},
					qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
	m_plane1.SetTransform(qbVector<double>{std::vector<double>{0.0, -1.4, 0.0}},
					qbVector<double>{std::vector<double>{PI/2, PI/2, 0.0}},
					qbVector<double>{std::vector<double>{50.0, 50.0, 50.0}});
														
	m_objects.at(sphere1_idx) -> SetTransformMatrix(m_sphere1);
	m_objects.at(sphere2_idx) -> SetTransformMatrix(m_sphere2);
	m_objects.at(cone1_idx) -> SetTransformMatrix(m_cone1);
	m_objects.at(plane1_idx) -> SetTransformMatrix(m_plane1);
	
	m_objects.at(sphere1_idx) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}};
	m_objects.at(sphere2_idx) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 1.0, 0.0}};
	m_objects.at(cone1_idx) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}};
	m_objects.at(plane1_idx)-> m_baseColor = qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}};


	m_lights.push_back(std::make_shared<PointLight> (PointLight()));
	m_lights.at(0)-> m_location = qbVector<double> {std:: vector<double> {0.0, 5.0, 0.0}};
	m_lights.at(0) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
}

bool Scene::Render(Image &outputImage) {
	int xSize = outputImage.getXSize();
	int ySize = outputImage.getYSize();
	
	Ray cameraRay;
	qbVector<double> intPoint {3};
	qbVector<double> localNormal {3};
	qbVector<double> localColor {3};

	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);

	for (int x=0; x<xSize; ++x) {
		for (int y=0; y<ySize; ++y) {
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			
			m_camera.GenerateRay(normX, normY, cameraRay);

			std:: shared_ptr<ObjectAbstract> closest_object;
			qbVector<double> closest_int_point {3};
			qbVector<double> closest_local_normal {3};
			qbVector<double> closest_local_color {3};
			bool intersected = false;
			double minDist = 1e6;
			double maxDist = 0.0;

			for (auto curr_object : m_objects) {
				bool validInt = curr_object-> TestIntersection(cameraRay, intPoint, localNormal, localColor);

				if (validInt) {
					intersected = true;

					double dist = (intPoint - cameraRay.m_point1).norm();
					if (dist < minDist) {
						minDist = dist;
						closest_object = curr_object;
						closest_int_point = intPoint;
						closest_local_normal = localNormal;
						closest_local_color = localColor;
					}

				}
			}
			
			if (intersected) {
				double intensity;
				qbVector<double> color {3};
				double red = 0.0;
				double green = 0.0;
				double blue = 0.0;
				bool valid_illumination = false;
				bool illuminated = false;
				for (auto curr_light : m_lights) {
					valid_illumination = curr_light-> ComputeIllumination(closest_int_point, closest_local_normal, m_objects, closest_object, color, intensity);
					
					if (valid_illumination) {
						illuminated = true;
						red += intensity*KA + color.GetElement(0) * intensity * KD;
						green += intensity*KA + color.GetElement(1) * intensity * KD;
						blue += intensity*KA + color.GetElement(2) * intensity * KD;
					}
				}
				
				if (illuminated) {
					red *= closest_local_color.GetElement(0);
					green *= closest_local_color.GetElement(1);
					blue *= closest_local_color.GetElement(2);
					outputImage.SetPixel(x, y, red, green, blue);
				}
			}
		}
	}
	
	return true;
}