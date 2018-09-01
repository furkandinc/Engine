#include "SnekScene.h"
#include "SnekScript.h"

#include <Object\Camera\PerpectiveCamera.h>
#include <Component\Transform.h>
#include <Component\Renderer.h>
#include <Component\Collider.h>
#include <Asset\CubeMesh.h>
#include <Component\Control.h>

SnekScene::SnekScene() {
	setName("Snek");
}

void SnekScene::initScene() {
	
	PerspectiveCamera * camera = new PerspectiveCamera();
	objectHandler->add(camera);

	Object * snek = new Object();
	objectHandler->add(snek);

	Object * target = new Object();
	objectHandler->add(target);

	SnekScript * snekScript = new SnekScript();
	snekScript->target = target;
	snekScript->player = snek;

	Control * snekControl = new Control();
	snekControl->setScript(snekScript);
	
	camera->getComponent<Transform>()->setPosition({ 640, 360, 400 });
	camera->getComponent<Transform>()->setRotation({ -90, 90, 0 });
	camera->setAspect(1280.0 / 720);

	snek->getComponent<Transform>()->setPosition({ 320, 360, 0 });
	snek->getComponent<Transform>()->setScale({ 100, 100, 100 });
	snek->getComponent<Renderer>()->getMaterial()->setDiffuseColor({ 0, 1, 0, 1 });
	snek->addComponent(new Collider());
	snek->getComponent<Collider>()->setCollidable(true);
	snek->getComponent<Collider>()->setMesh(new CubeMesh());
	snek->addComponent(snekControl);

	target->getComponent<Transform>()->setPosition({ 960, 360, 0 });
	target->getComponent<Transform>()->setScale({ 30, 30, 30 });
	target->getComponent<Renderer>()->getMaterial()->setDiffuseColor({ 1, 0, 0, 1 });
	target->addComponent(new Collider());
	target->getComponent<Collider>()->setCollidable(true);
	target->getComponent<Collider>()->setMesh(new CubeMesh());
}