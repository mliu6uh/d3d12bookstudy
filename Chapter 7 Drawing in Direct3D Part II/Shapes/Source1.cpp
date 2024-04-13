#include <d3d12.h>
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT3 normal;
};

std::vector<Vertex> CreateInclinedCylinderVertices(float radius, float height, float inclinationAngle, UINT numSegments)
{
    std::vector<Vertex> vertices;

    float angleIncrement = XM_2PI / numSegments;
    float angle = 0.0f;

    // Calculate the height component of each vertex
    float halfHeight = height * 0.5f;
    float yTop = halfHeight;
    float yBottom = -halfHeight;

    for (UINT i = 0; i < numSegments; ++i)
    {
        // Calculate positions for top and bottom rings of vertices
        XMFLOAT3 topVertexPos(radius * cos(angle), yTop, radius * sin(angle));
        XMFLOAT3 bottomVertexPos(radius * cos(angle), yBottom, radius * sin(angle));

        // Apply inclination angle to the top and bottom positions
        float inclinationRadians = XMConvertToRadians(inclinationAngle);
        topVertexPos.y *= cos(inclinationRadians);
        bottomVertexPos.y *= cos(inclinationRadians);

        // Calculate normals
        XMFLOAT3 topNormal = XMFLOAT3(topVertexPos.x, 0.0f, topVertexPos.z);
        XMFLOAT3 bottomNormal = XMFLOAT3(bottomVertexPos.x, 0.0f, bottomVertexPos.z);

        // Normalize normals
        XMVECTOR topNormalVec = XMVector3Normalize(XMLoadFloat3(&topNormal));
        XMVECTOR bottomNormalVec = XMVector3Normalize(XMLoadFloat3(&bottomNormal));

        // Add vertices to the vector
        vertices.push_back({ topVertexPos, XMFLOAT3(XMVectorGetX(topNormalVec), XMVectorGetY(topNormalVec), XMVectorGetZ(topNormalVec)) });
        vertices.push_back({ bottomVertexPos, XMFLOAT3(XMVectorGetX(bottomNormalVec), XMVectorGetY(bottomNormalVec), XMVectorGetZ(bottomNormalVec)) });

        // Increment angle for the next set of vertices
        angle += angleIncrement;
    }

    return vertices;
}

int main()
{
    // Example usage
    float radius = 1.0f;
    float height = 2.0f;
    float inclinationAngle = 45.0f; // In degrees
    UINT numSegments = 32;

    std::vector<Vertex> vertices = CreateInclinedCylinderVertices(radius, height, inclinationAngle, numSegments);

    // Now 'vertices' contains the positions and normals of the vertices for the inclined cylinder
    return 0;
}

//#include <DirectXMath.h>
//
//using namespace DirectX;
//
//void TransformVertices(const XMMATRIX& matrix, XMVECTOR* vertices, size_t numVertices)
//{
//    // Transform each vertex by the given matrix
//    for (size_t i = 0; i < numVertices; ++i)
//    {
//        vertices[i] = XMVector3Transform(vertices[i], matrix);
//    }
//}
//
//int main()
//{
//    // Example usage
//    XMVECTOR vertices[] = {
//        XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),  // Vertex 1
//        XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f),  // Vertex 2
//        XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)   // Vertex 3
//    };
//
//    XMMATRIX transformationMatrix = XMMatrixTranslation(1.0f, 2.0f, 3.0f);
//
//    // Apply transformation to vertices
//    TransformVertices(transformationMatrix, vertices, 3);
//
//    // Now the vertices are transformed
//    return 0;
//}
