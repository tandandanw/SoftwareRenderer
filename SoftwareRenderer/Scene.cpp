#include "Scene.h"

namespace Tan
{
	Scene::Scene()
	{
		renderObject = nullptr;
		lightSource  = nullptr;
		camera		 = nullptr;
	}

	void Scene::Initialize()
	{
		renderObject = new RenderObject;
		renderState = TEXTURE;

		// can be initialized.
		lightSource = new Light;
		camera      = new Camera;

		view = RenderMath::GetViewMatrix
		(
			camera->pos,
			camera->at,
			camera->up
		);
		projection = RenderMath::GetPerspectiveMatrix
		(
			static_cast<float>(PI * 0.5f),
			static_cast<float>(WND_WIDTH / WND_HEIGHT),
			NEAR,
			FAR
		);
	}

	void Scene::Update()
	{
		renderObject->Rotate();
	}

	void Scene::Delete()
	{
		if (renderObject)
		{
			renderObject->Delete();
			delete renderObject;
		}
		renderObject = nullptr;

		if (lightSource)
			delete lightSource;
		lightSource = nullptr;

		if (camera)
			delete camera;
		camera = nullptr;
	}

	void Scene::CreateBox()
	{
		renderObject->GenerateBox();
	}
}