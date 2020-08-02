#include "LightEstimator.h"

SpaceColonizationTree::LightSnapShot::LightSnapShot(size_t resolution, float angle, float weight)
{
    _SnapShotTexture = new GLTexture2D(1, GL_RGBA32F, resolution, resolution);
	_SnapShotTexture->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SnapShotTexture->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_SnapShotTexture->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_SnapShotTexture->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    _Angle = angle;
    _Weight = weight;
	_Score = 0;
	_Resolution = resolution;
	_PPBO = new GLPPBO();
	_PPBO->SetData(resolution * resolution * sizeof(float) * 4, nullptr, GL_STREAM_READ);
	_SRC = (float*)malloc(resolution * resolution * sizeof(float) * 4);
}

float SpaceColonizationTree::LightSnapShot::CalculateScore()
{
	size_t amount = 0;
	for (int i = 0; i < _Resolution * _Resolution; i++) {
		if (_SRC[4 * i] != 1.0f) {
			amount++;
		}
	}
	_Score = (float)amount / _Resolution / _Resolution * _Weight;
    return _Score;
}

SpaceColonizationTree::LightSnapShot::~LightSnapShot()
{
	free(_SRC);
	delete(_PPBO);
	delete(_SnapShotTexture);
}

SpaceColonizationTree::LightEstimator::LightEstimator(size_t resolution) : _Resolution(resolution)
{
    _RenderTarget = new RenderTarget(resolution, resolution);
	_DepthBuffer = new GLRenderBuffer();
	_DepthBuffer->AllocateStorage(GL_DEPTH_COMPONENT32, resolution, resolution);
	_RenderTarget->AttachRenderBuffer(_DepthBuffer, GL_DEPTH_ATTACHMENT);
	
	std::string vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/SpaceColonizationTree/LightSnapShot.vert");
	std::string fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/SpaceColonizationTree/LightSnapShot.frag");

	_SnapShotProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode));
	_SnapShots.push_back(new LightSnapShot(resolution, 0, 1.0f));
    _SnapShots.push_back(new LightSnapShot(resolution, 45, 5.0f));
    _SnapShots.push_back(new LightSnapShot(resolution, 90, 10.0f));
    _SnapShots.push_back(new LightSnapShot(resolution, 135, 5.0f));
	_SnapShots.push_back(new LightSnapShot(resolution, 180, 1.0f));
}

void SpaceColonizationTree::LightEstimator::TakeSnapShot(Tree* tree, float shotWidth, bool calculateScore)
{
	if (tree == nullptr || tree->NeedsToGrow()) return;
	
	_SnapShotProgram->Bind();
	auto mesh = tree->GetMesh();
	glm::mat4 model;
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), -(mesh->GetCenter()));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	model = translation * scale;
    for (auto ss : _SnapShots) {
		auto texture = ss->SnapShotTexture();
		_RenderTarget->AttachTexture(texture, GL_COLOR_ATTACHMENT0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		_RenderTarget->Bind();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 view;
		glm::mat4 projection;
		view = glm::lookAt(glm::vec3(0.0f) + shotWidth * glm::vec3(glm::cos(glm::radians(ss->GetAngle())), glm::sin(glm::radians(ss->GetAngle())), 0.0f), glm::vec3(0.0f), glm::vec3(0, 0, 1));
		projection = glm::ortho(-shotWidth, shotWidth, -shotWidth, shotWidth, 0.0f, shotWidth * 2.0f);
		glm::mat4 lsm = projection * view;
		_SnapShotProgram->SetFloat4x4("lightSpaceMatrix", lsm);
		_SnapShotProgram->SetFloat4x4("model", model);
		auto mesh = tree->GetMesh();
		mesh->Enable();
		mesh->VAO()->DisableAttributeArray(12);
		mesh->VAO()->DisableAttributeArray(13);
		mesh->VAO()->DisableAttributeArray(14);
		mesh->VAO()->DisableAttributeArray(15);
		glDrawElements(GL_TRIANGLES, mesh->Size(), GL_UNSIGNED_INT, 0);
		if (calculateScore) {
			glReadBuffer(GL_COLOR_ATTACHMENT0);
			ss->GetPixelBuffer()->Bind();
			glReadPixels(0, 0, _Resolution, _Resolution, GL_RGBA, GL_FLOAT, 0);
			GLubyte* src = nullptr;
			while (src == nullptr) {
				src = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
			}
			memcpy(ss->GetSRC(), src, _Resolution * _Resolution * sizeof(float) * 4);
			glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		}
    }
	RenderTarget::BindDefault();
	if (calculateScore) {
		_LightEstimationScore = CalculateScore();
		Debug::Log("Light Estimation Result:" + std::to_string(_LightEstimationScore));
	}
}

void SpaceColonizationTree::LightEstimator::DrawSnapShots(Camera* camera)
{
	float startX = -0.9f;
	for (auto ss : _SnapShots) {
		if (ss->SnapShotTexture() == nullptr) break;
		RenderManager::DrawTexture2D(ss->SnapShotTexture(), 0, glm::vec2(startX, 0.1f * 16.0 / 9.0f - 1.0f), glm::vec2(0.1f, 0.1f * 16.0 / 9.0f), camera);
		startX += 0.2f;
	}
}

float SpaceColonizationTree::LightEstimator::CalculateScore()
{
	float currentScore, totalScore;
	currentScore = totalScore = 0;
	for (auto ss : _SnapShots) {
		float score = ss->CalculateScore();
		totalScore += score;
	}
    return totalScore;
}
