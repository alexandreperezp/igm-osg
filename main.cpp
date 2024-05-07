#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/AnimationPath>
#include <osg/ShapeDrawable>
#include "osg/Material"

int main() {
    osg::ref_ptr<osg::Group> root = new osg::Group;

    // Crear un cubo
    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3(0, 0, 0), 1.0f);
    osg::ref_ptr<osg::ShapeDrawable> boxDrawable = new osg::ShapeDrawable(box);

    // Crear un Geode y añadir el boxDrawable a él
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(boxDrawable);

    // Crear un segundo cubo
    osg::ref_ptr<osg::Box> box2 = new osg::Box(osg::Vec3(0, 0, 0),0.5f);
    osg::ref_ptr<osg::ShapeDrawable> boxDrawable2 = new osg::ShapeDrawable(box2);

    // Crear un segundo Geode y añadir el boxDrawable a él
    osg::ref_ptr<osg::Geode> geode2 = new osg::Geode;
    geode2->addDrawable(boxDrawable2);

    // Crear un material y configurar sus propiedades
    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2f, 0.2f, 0.2f, 0.5f));
    material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8f, 0.8f, 0.8f, 0.5f));
    material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0f, 1.0f, 1.0f, 0.5f));
    material->setShininess(osg::Material::FRONT_AND_BACK, 128.0f); // Brillo

    // Aplicar el material al nodo que contiene el cubo
    geode->getOrCreateStateSet()->setAttribute(material);
    geode2->getOrCreateStateSet()->setAttribute(material);

    // Crear una transformación de matriz para la rotación
    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
    transform->addChild(geode);
    // Crear una transformación de matriz para la rotación
    osg::ref_ptr<osg::MatrixTransform> transform2 = new osg::MatrixTransform;
    transform2->addChild(geode2);

    // Crear un camino de animación para la rotación
    osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
    path->setLoopMode(osg::AnimationPath::LOOP);
    // Crear un camino de animación para la rotación
    osg::ref_ptr<osg::AnimationPath> path2 = new osg::AnimationPath;
    path2->setLoopMode(osg::AnimationPath::LOOP);

    // Agregar puntos de control para la rotación
    for (unsigned int i = 0; i <= 360; ++i)
    {
        osg::Quat rotation(osg::DegreesToRadians((float)i), osg::Vec3(0, 0, 1));
        path->insert((float)i / 360.0f, osg::AnimationPath::ControlPoint(osg::Vec3(0, 0, 0), rotation));
    }

    // Agregar puntos de control para la rotación
    for (unsigned int i = 0; i <= 360; ++i)
    {
        osg::Quat rotation(osg::DegreesToRadians((float)i), osg::Vec3(0, 0, 1));
        path2->insert((float)i / 360.0f, osg::AnimationPath::ControlPoint(osg::Vec3(1.5, 0, 0), rotation));
    }

    // Crear un callback de animación y agregarlo a la transformación
    osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback(path, 0.0, 0.5);
    osg::ref_ptr<osg::AnimationPathCallback> apcb2 = new osg::AnimationPathCallback(path2, 0.0, 0.5);
    transform->setUpdateCallback(apcb);
    transform2->setUpdateCallback(apcb2);

    root->addChild(transform);
    root->addChild(transform2);

    // Crear un visor y ejecutar
    osgViewer::Viewer viewer;
    viewer.setSceneData(root);
    viewer.run();

    return 0;
}
