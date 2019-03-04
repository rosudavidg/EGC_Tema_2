#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <Laboratoare\Tema2\MyBallObject.h>
#include <Laboratoare\Tema2\MyHoleObject.h>
#include "LabCamera.h"

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

	Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	
	void RenderTable();
	void RenderBalls();
	void RenderHoles();
	void RenderTac();
	void MoveBalls(float deltaTime);
	void BallCollisionWithMargins();
	void BallCollisionWithHoles();
	void BallCollisionWithBall();
	void PrintStatus();

	void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));
	void RenderTacMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	float ball_radius = 0.1f;
	float hole_radius = 0.2f;
	
	float table_OX = 4;
	float table_OY = 1;
	float table_OZ = 6;

	float margin_OX = 0.2f;

	std::vector<MyBallObject*> ballObjects;
	std::vector<MyHoleObject*> holeObjects;

	int count = 0;

	int player1Score = 0;
	int player1Fault = 0;
	int player1Color = 0; // 0 - undefined, 1 - red, 2 - galben

	int player2Score = 0;
	int player2Fault = 0;
	int player2Color = 0;

	int winnerPlayer = 0;

	int currentPlayer = 1;

	bool gameRunning = true;

	int gameStep = 0; // 0 - trb sa loveasca tac
					  // 1 - se misca bile (se asteapta)
	                  // 2 - jocul se termina
	                  // 3 - jocul s-a terminat

	float tacX;
	float tacZ;

	bool click_e_apasat = false;

	int pos_x_mouse_la_click;
	int pos_y_mouse_la_click;

protected:
	Laborat::Camera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
};
