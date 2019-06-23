#include "SpacyShootyScene.h"
#include "PlayerControllerScript.h"
#include "GameControllerScript.h"
#include "ForwardScript.h"
#include "ExplosionScript.h"

SpacyShootyScene::SpacyShootyScene() {
	setName("Spacy Shooty");
}

void SpacyShootyScene::initScene() {

	// Resources
	Resource rscObjCube = Engine::getInstance()->loadResource(OBJTYPE, "Assets\\Default\\Shape\\cube.obj");
	Resource rscObjShip = Engine::getInstance()->loadResource(OBJTYPE, "Assets\\SpacyShooty\\DaShip2.obj");
	Resource rscObjShipCollider = Engine::getInstance()->loadResource(OBJTYPE, "Assets\\SpacyShooty\\DaShip2Collider.obj");
	Resource rscObjAsteroid = Engine::getInstance()->loadResource(OBJTYPE, "Assets\\spacyShooty\\DaAsteroid.obj");
	Resource rscObjAsteroidCollider = Engine::getInstance()->loadResource(OBJTYPE, "Assets\\SpacyShooty\\DaAsteroidCollider.obj");
	Resource rscBmpShip = Engine::getInstance()->loadResource(BMPTYPE, "Assets\\SpacyShooty\\DaShip2.bmp");
	Resource rscBmpSpace = Engine::getInstance()->loadResource(BMPTYPE, "Assets\\SpacyShooty\\DaSpace.bmp");
	Resource rscBmpAsteroid = Engine::getInstance()->loadResource(BMPTYPE, "Assets\\SpacyShooty\\DaAsteroid.bmp");
	Resource rscPngAsteroid = Engine::getInstance()->loadResource(PNGTYPE, "Assets\\SpacyShooty\\DaAsteroid.png");
	Resource rscPngShip = Engine::getInstance()->loadResource(PNGTYPE, "Assets\\SpacyShooty\\DaShip2.png");

	ObjectGL * oglCube = new ObjectGL(rscObjCube);
	ObjectGL * oglShip = new ObjectGL(rscObjShip);
	ObjectGL * oglAsteroid = new ObjectGL(rscObjAsteroid);
	ObjectGL * oglShipCollider = new ObjectGL(rscObjShipCollider);
	ObjectGL * obglAsteroidCollider = new ObjectGL(rscObjAsteroidCollider);

	TextureGL * texSpace = new TextureGL(rscBmpSpace);
	TextureGL * texShip = new TextureGL(rscPngShip);
	TextureGL * texAsteroid = new TextureGL(rscPngAsteroid);
	TextureGL * texShipBmp = new TextureGL(rscBmpShip);
	//Resources end

	// Assets Start

	Wave * waveShoot = new Wave();
	waveShoot->readData("Assets\\SpacyShooty\\DaLazer.wav");

	Wave * waveBgm = new Wave();
	waveBgm->readData("Assets\\SpacyShooty\\DaBgm.wav");

	Wave * waveExplosion = new Wave();
	waveExplosion->readData("Assets\\SpacyShooty\\DaExplosion.wav");

	Mesh * meshShip = new Mesh();
	meshShip->setObjectGL(oglShip);

	Mesh * meshHazard = new Mesh();
	meshHazard->setObjectGL(oglAsteroid);

	Mesh * meshCube = new Mesh();
	meshCube->setObjectGL(oglCube);

	Mesh * meshShipCollider = new Mesh();
	meshShipCollider->setObjectGL(oglShipCollider);

	Mesh * meshHazardCollider = new Mesh();
	meshHazardCollider->setObjectGL(obglAsteroidCollider);
	//Assets end

	// Components

	PlayerControllerScript * scriptPlayerController = new PlayerControllerScript();

	GameControllerScript * scriptGameController = new GameControllerScript();

	ForwardScript * scriptForwardScript = new ForwardScript();

	Sound * soundShoot = new Sound();
	soundShoot->setWave(waveShoot);
	soundShoot->setVolume(100);

	Sound * soundExplosion = new Sound();
	soundExplosion->setWave(waveExplosion);
	soundExplosion->setVolume(10);

	Sound * soundBgm = new Sound();
	soundBgm->setWave(waveBgm);
	soundBgm->setVolume(30);
	// Components end

	//Prefabs
	Object * explosionPrefab = new Object();
	explosionPrefab->addComponent(new ExplosionScript());
	explosionPrefab->addComponent(soundExplosion);

	Object * bulletPrefab = new Object();
	bulletPrefab->setTag("bullet");
	bulletPrefab->addComponent(new Renderer());
	bulletPrefab->addComponent(new Collider());
	bulletPrefab->addComponent(new ForwardScript());
	bulletPrefab->addComponent(soundShoot);
	bulletPrefab->getComponent<Collider>()->setCollidable(true);
	bulletPrefab->getComponent<Collider>()->setMesh((Mesh *)meshCube->generate());
	bulletPrefab->getComponent<Transform>()->setScale({ 30, 5, 5 });
	bulletPrefab->getComponent<Renderer>()->setMesh((Mesh *)meshCube->generate());
	bulletPrefab->getComponent<Renderer>()->setMaterial(new Material());
	bulletPrefab->getComponent<Renderer>()->getMaterial()->setDiffuseColor({1, 1, 0});
	bulletPrefab->getComponent<Sound>()->setVolume(20);

	Object * hazardPrefab = new Object();
	hazardPrefab->setTag("hazard");
	hazardPrefab->addComponent(new Renderer());
	hazardPrefab->addComponent(new Collider());
	hazardPrefab->addComponent(scriptForwardScript);
	hazardPrefab->getComponent<Collider>()->setMesh(meshHazardCollider);
	hazardPrefab->getComponent<Collider>()->setCollidable(true);
	hazardPrefab->getComponent<Renderer>()->setMesh((Mesh *)meshHazard->generate());
	hazardPrefab->getComponent<Renderer>()->setMaterial(new Material());
	hazardPrefab->getComponent<Renderer>()->getMaterial()->setColorTexture(texAsteroid);
	hazardPrefab->getComponent<Renderer>()->getMaterial()->setShininess(0);

	//Prefabs end
	//PerspectiveCamera * camera = new PerspectiveCamera();
	//objectHandler->add(camera);

	OrthographicCamera * camera = new OrthographicCamera();
	objectHandler->add(camera);

	Object * space = new Object();
	objectHandler->add(space);

	Object * objShip = new Object();
	objectHandler->add(objShip);

	Object * objText = new Object();
	objectHandler->add(objText);

	Object * objPlayerController = new Object();
	objectHandler->add(objPlayerController);

	Object * objGameController = new Object();
	objectHandler->add(objGameController);

	Object * objBackgroundMusic = new Object();
	objectHandler->add(objBackgroundMusic);

	camera->getComponent<Transform>()->setPosition({ 640, 360, 1000 });
	camera->getComponent<Transform>()->setRotation({ -90, 90, 0 });
	camera->setWidth(1280);
	camera->setHeight(720);

	//camera->getComponent<Transform>()->setPosition({ -300, 0, 150 });
	//camera->getComponent<Transform>()->setRotation({ 0, 20, 0 });
	//camera->setAspect(1280.0 / 720.0);
	//camera->setFov(60.0);

	space->addComponent(new Renderer());
	space->getComponent<Transform>()->setPosition({ 640, 360, 0 });
	space->getComponent<Transform>()->setScale({ 1500, 1500, 1 });
	space->getComponent<Transform>()->setRotation({ 0, 0, 0 });
	space->getComponent<Renderer>()->setMesh((Mesh *)meshCube->generate());
	space->getComponent<Renderer>()->setMaterial(new Material());
	space->getComponent<Renderer>()->getMaterial()->setColorTexture(texSpace);
	space->getComponent<Renderer>()->getMaterial()->setSpecularColor({ 0, 0, 0});
	space->getComponent<Renderer>()->getMaterial()->setDiffuseColor({ 0, 0, 0});
	space->getComponent<Renderer>()->getMaterial()->setAmbientColor({ 0.5, 0.5, 0.5});
	
	objShip->setTag("ship");
	objShip->addComponent(new Renderer());
	objShip->addComponent(new Collider());
	objShip->getComponent<Transform>()->setPosition({ 320, 360, 500 });
	objShip->getComponent<Transform>()->setScale({ 200, 200, 200 });
	objShip->getComponent<Transform>()->setRotation({ 90, 0, 0 });
	objShip->getComponent<Renderer>()->setMesh(meshShip);
	objShip->getComponent<Renderer>()->setMaterial(new Material());
	objShip->getComponent<Renderer>()->getMaterial()->setColorTexture(texShip);
	objShip->getComponent<Renderer>()->getMaterial()->setShininess(10);
	objShip->getComponent<Renderer>()->getMaterial()->setAmbientColor({ 0.5f, 0.5f, 0.5f });
	objShip->getComponent<Renderer>()->getMaterial()->setDiffuseColor({0.5f, 0.5f, 0.5f});
	objShip->getComponent<Collider>()->setMesh(meshShipCollider);
	objShip->getComponent<Collider>()->setCollidable(true);
	
	objPlayerController->addComponent(scriptPlayerController);

	objGameController->addComponent(scriptGameController);

	objBackgroundMusic->addComponent(soundBgm);
	objBackgroundMusic->getComponent<Sound>()->play();

	//objShip->addChild(camera);
	//objShip->addChild(objCube);

	objText->addComponent(new UIText());
	objText->getComponent<Transform>()->setPosition({ 50, 500, 100 });
	objText->getComponent<Transform>()->setScale({ 50, 50, 50 });
	objText->getComponent<Transform>()->setRotation({ -90, 0, 0 });
	objText->getComponent<UIText>()->setMaterial(new Material());
	objText->getComponent<UIText>()->getMaterial()->setSpecularColor({ 1, 1, 1 });
	objText->getComponent<UIText>()->getMaterial()->setDiffuseColor({ 1, 1, 1 });
	objText->getComponent<UIText>()->getMaterial()->setAmbientColor({ 0.5, 0.5, 0.5 });
	objText->getComponent<UIText>()->setText("Initial Text");
	objText->setTag("text");

	// Script references

	scriptPlayerController->player = objShip;

	scriptForwardScript->hazardPrefab = hazardPrefab;
	scriptForwardScript->explosionPrefab = explosionPrefab;

	scriptGameController->player = objShip;
	scriptGameController->bulletPrefab = bulletPrefab;
	scriptGameController->hazardPrefab = hazardPrefab;
	scriptGameController->explosionPrefab = explosionPrefab;
	scriptGameController->camera = camera;
	scriptGameController->uitext = objText;
}