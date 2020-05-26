#pragma once
#include "SharedComponent.h"
#include "Misc.h"
#include "Math.h"
namespace UniEngine {

    struct Vertex {
        // position
        float3 Position;
        // normal
        float3 Normal;
        // texCoords
        float2 TexCoords;
        // tangent
        float3 Tangent;
        // bitangent
        float3 Bitangent;
    };

    class OMesh : SharedComponent {
    public:
        /*  Mesh Data  */
        std::vector<Vertex>* vertices;
        std::vector<unsigned>* triangles;
        std::size_t hash_code() { return _VAO; }

        /*  Functions  */

        unsigned VAO();

        OMesh();

        ~OMesh();

        void Clear();

        void Set(std::vector<Vertex>* vertices, std::vector<unsigned>* triangles, int offset = 0);

        void RecalculateNormal();

    private:
        /*  Render data  */
        unsigned _VBO, _EBO, _VAO;
        /*  Functions    */
        // initializes all the buffer objects/arrays
        void SetupMesh();
    };
}