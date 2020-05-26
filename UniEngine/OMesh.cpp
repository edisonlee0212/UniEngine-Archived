#include "OMesh.h"

using namespace UniEngine;

unsigned OMesh::VAO() {
    if (_VAO == 0) SetupMesh();
    return _VAO;
}

OMesh::OMesh() {
    _VAO = 0;
    _EBO = 0;
    _VBO = 0;
    vertices = new std::vector<Vertex>();
    triangles = new std::vector<unsigned>();
}

OMesh::~OMesh() {
    Clear();
    delete vertices;
    delete triangles;
}

void OMesh::Set(std::vector<Vertex>* vertices, std::vector<unsigned>* triangles, int offset) {
    this->vertices->clear();
    this->triangles->clear();
    size_t size = triangles->size() / 3;
    for (size_t i = 0; i < size; i++) {
        this->vertices->push_back(vertices->at(offset + triangles->at(3 * i)));
        this->vertices->push_back(vertices->at(offset + triangles->at(3 * i + 1)));
        this->vertices->push_back(vertices->at(offset + triangles->at(3 * i + 2)));
        this->triangles->push_back(3 * i);
        this->triangles->push_back(3 * i + 1);
        this->triangles->push_back(3 * i + 2);
    }
    SetupMesh();
}

void OMesh::RecalculateNormal() {
    if (_VAO == 0) return;
    size_t size = vertices->size();
    for (size_t i = 0; i < size / 3; i++) {
        auto v1 = vertices->at(3 * i);
        auto v2 = vertices->at(3 * i + 1);
        auto v3 = vertices->at(3 * i + 2);
        v1.Normal = v2.Normal = v3.Normal = Cross(v1.Position - v2.Position, v1.Position - v3.Position);
        vertices->at(3 * i) = v1;
        vertices->at(3 * i + 1) = v2;
        vertices->at(3 * i + 2) = v3;
    }
    SetupMesh();
}

void OMesh::Clear() {
    if (_VAO != 0) {
        glDeleteVertexArrays(1, &_VAO);
        glDeleteBuffers(1, &_VBO);
        glDeleteBuffers(1, &_EBO);
    }
    _VAO = _VBO = _EBO = 0;
}

void OMesh::SetupMesh()
{
    Clear();
    // create buffers/arrays
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vertex), &vertices->at(0), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles->size() * sizeof(unsigned), &triangles->at(0), GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}