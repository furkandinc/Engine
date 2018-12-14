#include "SnekScene.h"
#include "PoliceScript.h"
#include "ThiefScript.h"
#include "ArtScript.h"
#include <Engine.h>

SnekScene::SnekScene() {
	setName("Snek");
}

void SnekScene::initScene() {
	PerspectiveCamera * camera = new PerspectiveCamera();
	objectHandler->add(camera);

	Object * police = new Object();
	objectHandler->add(police);

	Object * thief = new Object();
	objectHandler->add(thief);

	Object * art = new Object();
	objectHandler->add(art);

	Resource cubeObjectResource = Engine::getInstance()->loadResource(OBJTYPE, "Assets\\cube.obj");

	ObjectGL * cubeObjectGL = new ObjectGL(cubeObjectResource);

	Mesh * cubeMesh = new Mesh();

	cubeMesh->setObjectGL(cubeObjectGL);

	Renderer * cubeRenderer = new Renderer();
	cubeRenderer->setMesh(cubeMesh);
	cubeRenderer->setMaterial(new Material());

	PoliceScript * policeScript = new PoliceScript();
	policeScript->thief = thief;
	policeScript->police = police;
	policeScript->art = art;
	policeScript->boundaryWidth = 1280;
	policeScript->boundaryHeight = 720;

	ThiefScript * thiefScript = new ThiefScript();
	thiefScript->thief = thief;
	thiefScript->art = art;
	thiefScript->boundaryWidth = 1280;
	thiefScript->boundaryHeight = 720;
	
	ArtScript * artScript = new ArtScript();
	artScript->art = art;
	artScript->boundaryWidth = 1280;
	artScript->boundaryHeight = 720;

	Wave * hitWave = new Wave();
	hitWave->readData("Assets\\HitHollow.wav");

	Sound * hitSound = new Sound();
	hitSound->setWave(hitWave);
	hitSound->setVolume(100);

	camera->getComponent<Transform>()->setPosition({ 640, 360, 400 });
	camera->getComponent<Transform>()->setRotation({ -90, 90, 0 });
	camera->setAspect(1280.0 / 720);

	police->addComponent((Renderer *)cubeRenderer->generate());
	police->getComponent<Transform>()->setPosition({ 320, 360, 0 });
	police->getComponent<Transform>()->setScale({ 100, 100, 100 });
	police->getComponent<Renderer>()->getMaterial()->setDiffuseColor({ 0, 1, 0, 1 });
	police->addComponent(new Collider());
	police->getComponent<Collider>()->setCollidable(true);
	police->getComponent<Collider>()->setMesh((Mesh *)cubeMesh->generate());
	police->addComponent(policeScript);
	police->addComponent(hitSound);

	thief->addComponent((Renderer *)cubeRenderer->generate());
	thief->getComponent<Transform>()->setPosition({ 960, 360, 0 });
	thief->getComponent<Transform>()->setScale({ 30, 30, 30 });
	thief->getComponent<Renderer>()->getMaterial()->setDiffuseColor({ 1, 0, 0, 1 });
	thief->addComponent(new Collider());
	thief->getComponent<Collider>()->setCollidable(true);
	thief->getComponent<Collider>()->setMesh((Mesh *)cubeMesh->generate());
	thief->addComponent(thiefScript);

	art->addComponent((Renderer *)cubeRenderer->generate());
	art->getComponent<Transform>()->setPosition({ 720, 360, 0 });
	art->getComponent<Transform>()->setScale({ 50, 50, 50 });
	art->getComponent<Renderer>()->getMaterial()->setDiffuseColor({ 1, 0, 1, 1 });
	art->addComponent(new Collider());
	art->getComponent<Collider>()->setCollidable(true);
	art->getComponent<Collider>()->setMesh((Mesh *)cubeMesh->generate());
	art->addComponent(artScript);
}