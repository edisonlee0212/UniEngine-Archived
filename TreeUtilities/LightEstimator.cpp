#include "pch.h"
#include "LightEstimator.h"
#include "TreeManager.h"
TreeUtilities::LightSnapShot::LightSnapShot(size_t resolution, glm::vec3 direction, float centerDistance, float width, float weight)
{
	_SnapShotTexture = new GLTexture2D(1, GL_RGBA32F, resolution, resolution);
	_SnapShotTexture->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_SnapShotTexture->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_SnapShotTexture->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_SnapShotTexture->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	_Direction = glm::normalize(direction);
	_CenterDistance = centerDistance;
	_Weight = weight;
	_Width = width;
	_Score = 0;
	_Resolution = resolution;
	_PPBO = new GLPPBO();
	_PPBO->SetData(resolution * resolution * sizeof(float) * 4, nullptr, GL_STREAM_READ);
	_SRC = (float*)malloc(resolution * resolution * sizeof(float) * 4);
}

glm::mat4 TreeUtilities::LightSnapShot::GetViewMatrix(glm::vec3& centerPosition)
{
	glm::mat4 view = glm::lookAt(centerPosition - _CenterDistance * _Direction, centerPosition, glm::vec3(0, 1, 0));
	if (glm::any(glm::isnan(view[3]))) {
		view = glm::lookAt(centerPosition - _CenterDistance * _Direction, centerPosition, glm::vec3(0, 0, 1));
	}
	return view;
}

glm::mat4 TreeUtilities::LightSnapShot::GetLightSpaceMatrix(glm::vec3& centerPosition)
{
	glm::mat4 view = glm::lookAt(centerPosition - _CenterDistance * _Direction, centerPosition, glm::vec3(0, 1, 0));
	if (glm::any(glm::isnan(view[3]))) {
		view = glm::lookAt(centerPosition - _CenterDistance * _Direction, centerPosition, glm::vec3(0, 0, 1));
	}
	glm::mat4 projection;
	projection = glm::ortho(-_Width, _Width, -_Width, _Width, 0.0f, _CenterDistance * 2.0f);
	return projection * view;
}

glm::vec3 TreeUtilities::LightSnapShot::GetDirection()
{
	return _Direction;
}

float TreeUtilities::LightSnapShot::CalculateScore()
{
	size_t amount = 0;
	for (int i = 0; i < _Resolution * _Resolution; i++) {
		if (_SRC[4 * i] != 0.0f) {
			amount++;
		}
	}
	_Score = (float)amount / (float)_Resolution / (float)_Resolution * _Weight;
	return _Score;
}

float TreeUtilities::LightSnapShot::CenterDistance()
{
	return _CenterDistance;
}

float TreeUtilities::LightSnapShot::Width()
{
	return _Width;
}

float TreeUtilities::LightSnapShot::Weight()
{
	return _Weight;
}

float TreeUtilities::LightSnapShot::Resolution()
{
	return _Resolution;
}

float TreeUtilities::LightSnapShot::GetBlockerDistance(glm::vec3& centerPosition, glm::vec3& pos)
{
	glm::mat4 lightSpaceMat = GetLightSpaceMatrix(centerPosition);

	glm::vec3 position = lightSpaceMat * glm::translate(pos) * glm::vec4(0, 0, 0, 1);
	float x = ((position.x + 1.0f) * 0.5f) * _Resolution;
	float y = ((position.y + 1.0f) * 0.5f) * _Resolution;
	glm::vec3 depthVal4 = GetDepth(y, x);
	
	float distance = 0;
	if (distance < 0.0f) distance = 0.0f;
	return distance;
}

unsigned TreeUtilities::LightSnapShot::GetLeafEntityIndex(size_t x, size_t y)
{
	float r = (_SRC[(x * _Resolution + y) * 4] + 0.5f);
	int ru = r;
	return ru;
}

glm::vec3 TreeUtilities::LightSnapShot::GetDepth(size_t x, size_t y)
{
	return glm::vec3(_SRC[(x * _Resolution + y) * 4 + 1], _SRC[(x * _Resolution + y) * 4 + 2], _SRC[(x * _Resolution + y) * 4 + 3]);
}

TreeUtilities::LightSnapShot::~LightSnapShot()
{
	free(_SRC);
	delete(_PPBO);
	delete(_SnapShotTexture);
}

TreeUtilities::LightEstimator::LightEstimator(size_t resolution, float centerDistance) : _Resolution(resolution)
{
	_RenderTarget = new RenderTarget(resolution, resolution);
	_DepthBuffer = new GLRenderBuffer();
	_DepthBuffer->AllocateStorage(GL_DEPTH_COMPONENT32, resolution, resolution);
	_RenderTarget->AttachRenderBuffer(_DepthBuffer, GL_DEPTH_ATTACHMENT);

	std::string vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/TreeUtilities/LightSnapShot.vert");
	std::string fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/TreeUtilities/LightSnapShot.frag");

	_SnapShotProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode));

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/TexturePassThrough.vert");
	fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/TreeUtilities/LightSnapShotVBlur.frag");

	_SnapShotVBlurProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode));

	vertShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/Vertex/TexturePassThrough.vert");
	fragShaderCode = std::string("#version 460 core\n") +
		FileIO::LoadFileAsString("Shaders/TreeUtilities/LightSnapShotHBlur.frag");

	_SnapShotHBlurProgram = new GLProgram(
		new GLShader(ShaderType::Vertex, &vertShaderCode),
		new GLShader(ShaderType::Fragment, &fragShaderCode));

	_BlurFilter = new GLTexture2D(1, GL_RGBA32F, resolution, resolution);
	_BlurFilter->SetInt(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_BlurFilter->SetInt(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_BlurFilter->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	_BlurFilter->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	_BlurFilterRenderTarget = new RenderTarget(resolution, resolution);
	_BlurFilterRenderTarget->AttachTexture(_BlurFilter, GL_COLOR_ATTACHMENT0);
}

void TreeUtilities::LightEstimator::ResetCenterDistance(float distance)
{
	_CenterDistance = distance;
}

void TreeUtilities::LightEstimator::ResetSnapShotWidth(float width)
{
	_SnapShotWidth = width;
}

void TreeUtilities::LightEstimator::PushSnapShot(glm::vec3 direction, float weight)
{
	_SnapShots.push_back(new LightSnapShot(_Resolution, direction, _CenterDistance, _SnapShotWidth, weight));
}

void TreeUtilities::LightEstimator::Clear()
{
	for (int i = 0; i < _SnapShots.size(); i++) {
		delete _SnapShots[i];
	}
	_SnapShots.clear();
}

void TreeUtilities::LightEstimator::TakeSnapShot(Entity treeEntity, bool calculateScore, bool storeSnapshot)
{
	if (treeEntity.IsDeleted() || treeEntity.IsNull()) return;

	
	std::vector<LocalToWorld> matrices = std::vector<LocalToWorld>();
	std::vector<Entity> leafEntities = std::vector<Entity>();
	TreeManager::GetLeafQuery().ToComponentDataArray(EntityManager::GetComponentData<TreeIndex>(treeEntity), &matrices);
	TreeManager::GetLeafQuery().ToEntityArray(EntityManager::GetComponentData<TreeIndex>(treeEntity), &leafEntities);
	
	auto mesh = TreeManager::GetLeafSystem()->GetLeafMesh();
	
	GLVBO indicesBuffer;
	size_t count = matrices.size();
	if (count == 0) return;
	mesh->Enable();

	indicesBuffer.SetData((GLsizei)count * sizeof(Entity), leafEntities.data(), GL_STATIC_DRAW);
	mesh->VAO()->EnableAttributeArray(11);
	mesh->VAO()->SetAttributeIntPointer(11, 1, GL_UNSIGNED_INT, sizeof(Entity), (void*)0);
	mesh->VAO()->SetAttributeDivisor(11, 1);

	GLVBO matricesBuffer;
	matricesBuffer.SetData((GLsizei)count * sizeof(glm::mat4), matrices.data(), GL_STATIC_DRAW);

	
	

	
	mesh->VAO()->EnableAttributeArray(12);
	mesh->VAO()->SetAttributePointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	mesh->VAO()->EnableAttributeArray(13);
	mesh->VAO()->SetAttributePointer(13, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(14);
	mesh->VAO()->SetAttributePointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	mesh->VAO()->EnableAttributeArray(15);
	mesh->VAO()->SetAttributePointer(15, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	mesh->VAO()->SetAttributeDivisor(12, 1);
	mesh->VAO()->SetAttributeDivisor(13, 1);
	mesh->VAO()->SetAttributeDivisor(14, 1);
	mesh->VAO()->SetAttributeDivisor(15, 1);

	glm::mat4 model;
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	model = translation * scale;
	for (auto ss : _SnapShots) {
		auto texture = ss->SnapShotTexture();
		_RenderTarget->AttachTexture(texture, GL_COLOR_ATTACHMENT0);
		_SnapShotProgram->Bind();
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		_RenderTarget->Bind();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		glm::vec3 treePosition = glm::vec3(EntityManager::GetComponentData<LocalToWorld>(treeEntity).Value[3]);
		_SnapShotProgram->SetFloat4x4("lightSpaceMatrix", ss->GetLightSpaceMatrix(treePosition));
		_SnapShotProgram->SetFloat4x4("model", model);
		
		if (matrices.size() != 0) glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)mesh->Size(), GL_UNSIGNED_INT, 0, (GLsizei)count);
	}
	
	mesh->VAO()->DisableAttributeArray(11);

	Default::GLPrograms::ScreenVAO->Bind();
	for (auto ss : _SnapShots) {
		auto texture = ss->SnapShotTexture();
		texture->Bind(0);
		//Blur depth value here.
		_BlurFilterRenderTarget->Bind();
		_BlurFilterRenderTarget->AttachTexture(_BlurFilter, GL_COLOR_ATTACHMENT0);
		_BlurFilterRenderTarget->AttachTexture(texture, GL_COLOR_ATTACHMENT1);
		glDisable(GL_DEPTH_TEST);
		
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		_SnapShotVBlurProgram->Bind();
		_SnapShotVBlurProgram->SetInt("textureInput", 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		_BlurFilter->Bind(1);
		glDrawBuffer(GL_COLOR_ATTACHMENT1);
		_SnapShotHBlurProgram->Bind();
		_SnapShotHBlurProgram->SetInt("textureInput", 1);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		if (calculateScore || storeSnapshot) {
			glReadBuffer(GL_COLOR_ATTACHMENT1);
			ss->GetPixelBuffer()->Bind();
			glReadPixels(0, 0, _Resolution, _Resolution, GL_RGBA, GL_FLOAT, 0);
			GLubyte* src = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
			memcpy(ss->GetSRC(), src, _Resolution * _Resolution * sizeof(float) * 4);
			glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		}
	}
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	RenderTarget::BindDefault();
	if (calculateScore) {
		_LightEstimationScore = CalculateScore();
		Debug::Log("Light Estimation Result:" + std::to_string(_LightEstimationScore));
	}
}

void TreeUtilities::LightEstimator::DrawSnapShots(Camera* camera)
{
	float startX = -0.9f;
	for (auto ss : _SnapShots) {
		if (ss->SnapShotTexture() == nullptr) break;
		RenderManager::DrawTexture2D(ss->SnapShotTexture(), 0, glm::vec2(startX, 0.1f * 16.0 / 9.0f - 1.0f), glm::vec2(0.1f, 0.1f * 16.0 / 9.0f), camera);
		startX += 0.2f;
	}
}

float TreeUtilities::LightEstimator::CalculateScore()
{
	float currentScore, totalScore;
	currentScore = totalScore = 0;
	for (auto ss : _SnapShots) {
		float score = ss->CalculateScore();
		totalScore += score;
	}
	return totalScore;
}

float TreeUtilities::LightEstimator::GetScore()
{
	return _LightEstimationScore;
}

std::vector<TreeUtilities::LightSnapShot*>* TreeUtilities::LightEstimator::GetSnapShots()
{
	return &_SnapShots;
}
