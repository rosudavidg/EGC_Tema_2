#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	renderCameraTarget = false;

	camera = new Laborat::Camera();
	camera->Set(glm::vec3(1,1,1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//camera->Set(glm::vec3(1, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple cube
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube", vertices, indices);
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("DavidSimpleShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;

		shader = new Shader("TacSimpleShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/TacVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/TacFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	ballObjects.push_back(new MyBallObject(0, 2, 1, 1, 1)); // Bila alba

	// Rand 1
	ballObjects.push_back(new MyBallObject(0, -1, 1, 0, 0)); // Bila R

	// Rand 2
	ballObjects.push_back(new MyBallObject(-0.1f, -1.2f, 1, 1, 0)); // Bila G
	ballObjects.push_back(new MyBallObject(+0.1f, -1.2f, 1, 0, 0)); // Bila R

	// Rand 3
	ballObjects.push_back(new MyBallObject(-0.2f, -1.4f, 1, 0, 0)); // Bila R
	ballObjects.push_back(new MyBallObject(0,     -1.4f, 0, 0, 0)); // Bila N
	ballObjects.push_back(new MyBallObject(0.2f,  -1.4f, 1, 1, 0)); // Bila G

	// Rand 4
	ballObjects.push_back(new MyBallObject(-0.3f, -1.6f, 1, 1, 0)); // Bila G
	ballObjects.push_back(new MyBallObject(-0.1f, -1.6f, 1, 0, 0)); // Bila R
	ballObjects.push_back(new MyBallObject(0.1f,  -1.6f, 1, 0, 0)); // Bila R
	ballObjects.push_back(new MyBallObject(0.3f,  -1.6f, 1, 1, 0)); // Bila G

	// Rand 5
	ballObjects.push_back(new MyBallObject(-0.4f, -1.8f, 1, 0, 0)); // Bila R
	ballObjects.push_back(new MyBallObject(-0.2f, -1.8f, 1, 1, 0)); // Bila G
	ballObjects.push_back(new MyBallObject(0,     -1.8f, 1, 1, 0)); // Bila G
	ballObjects.push_back(new MyBallObject(0.2f,  -1.8f, 1, 1, 0)); // Bila G
	ballObjects.push_back(new MyBallObject(0.4f,  -1.8f, 1, 0, 0)); // Bila R

	// Buzunare
	holeObjects.push_back(new MyHoleObject(-1.8f, -2.8f)); // nord - stanga
	holeObjects.push_back(new MyHoleObject(+1.8f, -2.8f)); // nord - dreapta

	holeObjects.push_back(new MyHoleObject(-1.8f, 0)); // mijloc - stanga
	holeObjects.push_back(new MyHoleObject(+1.8f, 0)); // mijloc - dreapta

	holeObjects.push_back(new MyHoleObject(-1.8f, +2.8f)); // sud - stanga
	holeObjects.push_back(new MyHoleObject(+1.8f, +2.8f)); // sud - dreapta

	PrintStatus();
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	camera->TranslateUpword(7);
	camera->RotateFirstPerson_OX(-1);
}

Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

// set vertex color attribute
//glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.8f);
//glUniform3fv(location, 1, glm::value_ptr(color));
glEnableVertexAttribArray(3);
glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
// ========================================================================

// Unbind the VAO
glBindVertexArray(0);

// Check for OpenGL errors
CheckOpenGLError();

// Mesh information is saved into a Mesh object
meshes[name] = new Mesh(name);
meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
meshes[name]->vertices = vertices;
meshes[name]->indices = indices;
return meshes[name];
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::RenderTable() {
	// Tabla
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.5, 0));
		//modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 0.5, 3));
		RenderSimpleMesh(meshes["cube"], shaders["DavidSimpleShader"], modelMatrix, glm::vec3(0.3f, 0.74f, 0.3f));
	}

	// Margine nord
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1.1, -2.9));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 0.1, 0.1));
		RenderSimpleMesh(meshes["cube"], shaders["DavidSimpleShader"], modelMatrix, glm::vec3(0.15f, 0.39f, 0.15f));
	}

	// Margine sud
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1.1, +2.9));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 0.1, 0.1));
		RenderSimpleMesh(meshes["cube"], shaders["DavidSimpleShader"], modelMatrix, glm::vec3(0.15f, 0.39f, 0.15f));
	}

	// Margine vest
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.9, 1.1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 3));
		RenderSimpleMesh(meshes["cube"], shaders["DavidSimpleShader"], modelMatrix, glm::vec3(0.15f, 0.39f, 0.15f));
	}

	// Margine est
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(+1.9, 1.1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 3));
		RenderSimpleMesh(meshes["cube"], shaders["DavidSimpleShader"], modelMatrix, glm::vec3(0.15f, 0.39f, 0.15f));
	}
}

void Tema2::RenderBalls() {
	for (int i = 0; i < ballObjects.size(); i++) {
		MyBallObject* ball = ballObjects.at(i);

		if (ball->visible == true) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(ball->posx, table_OY + ball_radius, ball->posz));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
			RenderSimpleMesh(meshes["sphere"], shaders["DavidSimpleShader"], modelMatrix, glm::vec3(ball->R, ball->G, ball->B));
		}
	}
}

void Tema2::RenderHoles() {
	for (int i = 0; i < holeObjects.size(); i++) {
		MyHoleObject* hole = holeObjects.at(i);

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(hole->posx, table_OY, hole->posz));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.4, 0.4));
		RenderSimpleMesh(meshes["sphere"], shaders["DavidSimpleShader"], modelMatrix, glm::vec3(0, 0, 0));
	}
}

void Tema2::RenderTac() {
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02, 0.02, 1));
		RenderTacMesh(meshes["cube"], shaders["TacSimpleShader"], modelMatrix, glm::vec3(0.2f, 0.1f, 0));
	}
}

void Tema2::MoveBalls(float deltaTime) {
	for (int i = 0; i < ballObjects.size(); i++) {
		MyBallObject* ball = ballObjects.at(i);

		if (ball->moving == true) {
			ball->posx += ball->speedx * deltaTime;
			ball->posz += ball->speedz * deltaTime;

			if (ball->speedx > 0) {
				ball->speedx -= 1 * deltaTime;
			}

			if (ball->speedx < 0) {
				ball->speedx += 1 * deltaTime;
			}

			if (ball->speedz > 0) {
				ball->speedz -= 1 * deltaTime;
			}

			if (ball->speedz < 0) {
				ball->speedz += 1 * deltaTime;
			}

			if (-0.2 < ball->speedz && ball->speedz < 0.2) {
				ball->speedz = 0;
			}

			if (-0.2 < ball->speedx && ball->speedx < 0.2) {
				ball->speedx = 0;
			}

			if (ball->speedx == 0 && ball->speedz == 0) {
				ball->moving = false;
			}

		}

	}
}

void Tema2::BallCollisionWithMargins() {
	for (int i = 0; i < ballObjects.size(); i++) {
		MyBallObject *ball = ballObjects.at(i);

		if (ball->visible == true) {
			// Margine sus
			if (ball->posz - ball_radius < -2.8) {
				ball->speedz *= -1;
				ball->posz = -2.8 + ball_radius + 0.01;
			}

			// Margine jos
			if (ball->posz + ball_radius > 2.8) {
				ball->speedz *= -1;
				ball->posz = 2.8 - ball_radius - 0.01;
			}

			// Margine stanga
			if (ball->posx - ball_radius < -1.8) {
				ball->speedx *= -1;
				ball->posx = -1.8 + ball_radius + 0.01;
			}

			// Margine dreapta
			if (ball->posx + ball_radius > 1.8) {
				ball->speedx *= -1;
				ball->posx = 1.8 - ball_radius - 0.01;
			}
		}
	}
}

void Tema2::BallCollisionWithHoles() {
	for (int i = 0; i < ballObjects.size(); i++) {
		MyBallObject *ball = ballObjects.at(i);

		for (int j = 0; j < holeObjects.size(); j++) {
			MyHoleObject *hole = holeObjects.at(j);

			if (ball->visible && ball->B != 1 && (ball->posx - hole->posx) * (ball->posx - hole->posx) + (ball->posz - hole->posz) * (ball->posz - hole->posz) <= 0.04f) {
				ball->visible = false;
				ball->speedx = 0;
				ball->speedz = 0;

				if (player1Color == 1 && ball->G == 0 && ball->R == 1 && ball->B == 0) {
					player1Score++;
					PrintStatus();
				}

				if (player2Color == 1 && ball->G == 0 && ball->R == 1 && ball->B == 0) {
					player2Score++;
					PrintStatus();
				}

				if (player1Color == 2 && ball->G == 1 && ball->R == 1 && ball->B == 0) {
					player1Score++;
					PrintStatus();
				}

				if (player2Color == 2 && ball->G == 1 && ball->R == 1 && ball->B == 0) {
					player2Score++;
					PrintStatus();
				}

				if (currentPlayer == 1) {
					if (player1Color == 0) {
						if (ball->G == 0 && ball->R == 1 && ball->B == 0) {
							player1Color = 1;
							player2Color = 2;
							player1Score++;
							PrintStatus();
						}
					}
				}

				if (currentPlayer == 2) {
					if (player2Color == 0) {
						if (ball->G == 0 && ball->R == 1 && ball->B == 0) {
							player2Score++; 
							player2Color = 1;
							player1Color = 2;
							PrintStatus();
						}
					}
				}

				if (currentPlayer == 1) {
					if (player1Color == 0) {
						if (ball->G == 1 && ball->R == 1 && ball->B == 0) {
							player1Score++;
							player1Color = 2;
							player2Color = 1;
							PrintStatus();
						}
					}
				}

				if (currentPlayer == 2) {
					if (player2Color == 0) {
						if (ball->G == 1 && ball->R == 1 && ball->B == 0) {
							player2Score++;
							player2Color = 2;
							player1Color = 1;
							PrintStatus();
						}
					}
				}

			}
		}
	}
}

void Tema2::BallCollisionWithBall() {
	for (int i = 0; i < ballObjects.size(); i++) {
		MyBallObject *ball1 = ballObjects.at(i);
	
		if (ball1->visible == true) {
			for (int j = i + 1; j < ballObjects.size() && i != j; j++) {
				MyBallObject *ball2 = ballObjects.at(j);

				if (ball2->visible == true) {
					float dist = pow((ball1->posx - ball2->posx), 2) + pow((ball1->posz - ball2->posz), 2);
					
					if (dist <= pow(0.2, 2) && (ball1->moving == true || ball2->moving == true)) {

						//printf("COLLISION\n");
						float cx1 = ball1->posx;
						float cy1 = ball1->posz;

						float cx2 = ball2->posx;
						float cy2 = ball2->posz;

						float circle1VX = ball1->speedx;
						float circle1VY = ball1->speedz;
						float circle2VX = ball2->speedx;
						float circle2VY = ball2->speedz;

						float d = sqrt(pow(cx1 - cx2, 2) + pow(cy1 - cy2, 2));
						float n_x = (cx2 - cx1) / d;
						float n_y = (cy2 - cy1) / d;
						float p = circle1VX * n_x + circle1VY * n_y - circle2VX * n_x - circle2VY * n_y;
						
						ball1->speedx = circle1VX - p * n_x;
						ball1->speedz = circle1VY - p * n_y;
						ball2->speedx = circle2VX + p * n_x;
						ball2->speedz = circle2VY + p * n_y;

						ball2->moving = true;
						ball1->moving = true;

					}
				}
			}
		}
	}
}

void Tema2::PrintStatus() {
	if (winnerPlayer == 0) {
		printf("PLAYER 1: SCORE: %d FAULTS %d ", player1Score, player1Fault);

		printf("COLOR: ");
		if (player1Color == 0) {
			printf("UNK\n");
		}
		else if (player1Color == 1) {
			printf("RED\n");
		}
		else {
			printf("YELLOW\n");
		}

		printf("PLAYER 2: SCORE: %d FAULTS %d ", player2Score, player2Fault);

		printf("COLOR: ");
		if (player2Color == 0) {
			printf("UNK\n");
		}
		else if (player2Color == 1) {
			printf("RED\n");
		}
		else {
			printf("YELLOW\n");
		}

		printf("\n");

	}
	else {
		printf("WINNER: PLAYER %d\n", winnerPlayer);
	}
}

void Tema2::Update(float deltaTimeSeconds)
{
	RenderTable();
	RenderHoles();
	RenderBalls();

	switch (gameStep) {
	case 0:
		RenderTac();
		break;
	case 1:
		MoveBalls(deltaTimeSeconds);
		BallCollisionWithMargins();
		BallCollisionWithHoles();
		BallCollisionWithBall();
		break;
	}

	MyBallObject *whiteBall = NULL;

	for (int i = 0; i < ballObjects.size(); i++) {
		if (ballObjects.at(i)->R == 1 && ballObjects.at(i)->G == 1 && ballObjects.at(i)->B == 1) {
			whiteBall = ballObjects.at(i);
		}
	}

	if (click_e_apasat == true) {
		tacZ += 1 * deltaTimeSeconds;

		if (tacZ >= whiteBall->posz + 1) {
			tacZ = whiteBall->posz;
		}
	}
	else {
		tacX = whiteBall->posx;
		tacZ = whiteBall->posz + 0.2;
	}

	if (gameStep == 1) {
		camera->Set(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0));
		bool moving = false;

		for (int i = 0; i < ballObjects.size(); i++) {
			if (ballObjects.at(i)->moving == true) {
				moving = true;
				break;
			}
		}

		if (moving == false) {
			gameStep = 0;

			if (currentPlayer == 0) {
				currentPlayer = 1;
			}
			else {
				currentPlayer = 0;
			}

		}
	}
	else {
		camera->Set(glm::vec3(whiteBall->posx, 5, whiteBall->posz), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem();
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	location = glGetUniformLocation(shader->program, "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	location = glGetUniformLocation(shader->program, "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	//glm::mat4 projectionMatrix = camera->GetProjectionMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->program, "Color");
	glUniform3fv(location, 1, glm::value_ptr(color));


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::RenderTacMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	location = glGetUniformLocation(shader->program, "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	location = glGetUniformLocation(shader->program, "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	//glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->program, "Color");
	glUniform3fv(location, 1, glm::value_ptr(color));

	glm::vec3 parametrii = glm::vec3(tacX, 1.1, tacZ + 1);
	location = glGetUniformLocation(shader->program, "Parametrii");
	glUniform3fv(location, 1, glm::value_ptr(parametrii));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event

	if (key == GLFW_KEY_J) {
		for (int i = 0; i < ballObjects.size(); i++) {
			if (ballObjects.at(i)->B == 1) {
				ballObjects.at(i)->speedz = 5;
				ballObjects.at(i)->moving = true;
			}
		}
	}

	if (key == GLFW_KEY_U) {
		for (int i = 0; i < ballObjects.size(); i++) {
			if (ballObjects.at(i)->B == 1) {
				ballObjects.at(i)->speedz = -5;
				ballObjects.at(i)->moving = true;
			}
		}
	}

	if (key == GLFW_KEY_H) {
		for (int i = 0; i < ballObjects.size(); i++) {
			if (ballObjects.at(i)->B == 1) {
				ballObjects.at(i)->speedx = -5;
				ballObjects.at(i)->moving = true;
			}
		}
	}

	if (key == GLFW_KEY_K) {
		for (int i = 0; i < ballObjects.size(); i++) {
			if (ballObjects.at(i)->B == 1) {
				ballObjects.at(i)->speedx = 5;
				ballObjects.at(i)->moving = true;
			}
		}
	}

	if (key == GLFW_KEY_P) {
		for (int i = 0; i < ballObjects.size(); i++) {
			if (ballObjects.at(i)->B == 1) {
				ballObjects.at(i)->posz -= 0.01;
			}
		}
	}


}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event

}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
			//camera->TranslateRight(-deltaX * sensivityOX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
			camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
		}

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (button == GLFW_MOUSE_BUTTON_RIGHT && gameStep == 0) {
		click_e_apasat = true;
		pos_x_mouse_la_click = mouseX;
		pos_y_mouse_la_click = mouseY;
	}
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (button == GLFW_MOUSE_BUTTON_RIGHT && gameStep == 0 && click_e_apasat) {
		gameStep = 1;
		click_e_apasat = false;

		for (int i = 0; i < ballObjects.size(); i++) {
			if (ballObjects.at(i)->B == 1) {
				ballObjects.at(i)->speedz = -6 * (tacZ - ballObjects.at(i)->posz);
				ballObjects.at(i)->moving = true;
			}
		}
	}
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}

void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}
