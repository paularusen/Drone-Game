#include "object3D.h"

#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include <map>

void object3D::CreateDrone(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name) {
        float x = 0.4f;
        float y = 0.02f;
        float z = 0.02f;

        float x2 = 0.02f;
        float z2 = 0.4f;

        glm::vec3 colorDrona = glm::vec3(0.3764705882f, 0.3764705882f, 0.3764705882f);
        std::vector<VertexFormat> vertices = {
            // Prima parte
            VertexFormat(glm::vec3(-x, -y,  z), colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 0
            VertexFormat(glm::vec3(x, -y,  z),  colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 1
            VertexFormat(glm::vec3(-x,  y,  z), colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 2
            VertexFormat(glm::vec3(x,  y,  z),  colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 3
            VertexFormat(glm::vec3(-x, -y, -z), colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 4
            VertexFormat(glm::vec3(x, -y, -z),  colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 5
            VertexFormat(glm::vec3(-x,  y, -z), colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 6
            VertexFormat(glm::vec3(x,  y, -z),  colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 7

            // A doua parte
            VertexFormat(glm::vec3(-x2, -y,  z2), colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 8
            VertexFormat(glm::vec3(x2, -y,  z2),  colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 9
            VertexFormat(glm::vec3(-x2,  y,  z2), colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 10
            VertexFormat(glm::vec3(x2,  y,  z2),  colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 11
            VertexFormat(glm::vec3(-x2, -y, -z2), colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 12
            VertexFormat(glm::vec3(x2, -y, -z2),  colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 13
            VertexFormat(glm::vec3(-x2,  y, -z2), colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 14
            VertexFormat(glm::vec3(x2,  y, -z2),  colorDrona, glm::vec3(0.2f, 0.8f, 0.6f)), // 15
        };

        std::vector<unsigned int> indices = {
            // Prima parte
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,

            // A doua parte
            8, 9, 10,
            9, 11, 10,
            10, 11, 15,
            10, 15, 14,
            9, 15, 11,
            9, 13, 15,
            14, 15, 12,
            15, 13, 12,
            8, 12, 9,
            9, 12, 13,
            10, 14, 12,
            8, 10, 12,
        };

        Mesh* droneMesh = new Mesh(name);
        droneMesh->InitFromData(vertices, indices);
        meshes[name] = droneMesh;
}

void object3D::CreateElice(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name) {
        float x = 0.14f;
        float y = 0.001f;
        float z = 0.01f;
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(x, y, z), glm::vec3(), glm::vec3(0.0f, 0.0f, 0.0f)), // 0
            VertexFormat(glm::vec3(-x, y, z), glm::vec3(), glm::vec3(0.2f, 0.8f, 0.6f)), // 1
            VertexFormat(glm::vec3(x, -y, z), glm::vec3(), glm::vec3(0.2f, 0.8f, 0.6f)), // 2
            VertexFormat(glm::vec3(-x, -y, z), glm::vec3(), glm::vec3(0.2f, 0.8f, 0.6f)), // 3
            VertexFormat(glm::vec3(x, y, -z), glm::vec3(), glm::vec3(0.2f, 0.8f, 0.6f)), // 4
            VertexFormat(glm::vec3(-x, y, -z), glm::vec3(), glm::vec3(0.2f, 0.8f, 0.6f)), // 5
            VertexFormat(glm::vec3(x, -y, -z), glm::vec3(), glm::vec3(0.2f, 0.8f, 0.6f)), // 6
            VertexFormat(glm::vec3(-x, -y, -z), glm::vec3(), glm::vec3(0.2f, 0.8f, 0.6f)), // 7
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,    // First triangle
            1, 3, 2,    // Second triangle
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,
        };

        Mesh* eliceMesh = new Mesh(name);
        eliceMesh->InitFromData(vertices, indices);
        meshes[name] = eliceMesh;
}

void object3D::CreateCube(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name) {
        glm::vec3 color = glm::vec3(0.37f, 0.37f, 0.37f);
        float x1 = 0.037f;
        float y1 = 0.037f;
        float z1 = 0.037f;
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-x1, -y1,   z1),  color, glm::vec3(0.2f, 0.8f, 0.6f)),
            VertexFormat(glm::vec3(-x1, -y1,  -z1), color, glm::vec3(0.2f, 0.8f, 0.6f)),
            VertexFormat(glm::vec3(x1, -y1,  -z1),  color, glm::vec3(0.2f, 0.8f, 0.6f)),
            VertexFormat(glm::vec3(x1, -y1,   z1),   color, glm::vec3(0.2f, 0.8f, 0.6f)),

            VertexFormat(glm::vec3(-x1, y1,   z1),  color,  glm::vec3(0.2f, 0.8f, 0.6f)),
            VertexFormat(glm::vec3(-x1, y1,  -z1), color, glm::vec3(0.2f, 0.8f, 0.6f)),
            VertexFormat(glm::vec3(x1, y1,  -z1),  color, glm::vec3(0.2f, 0.8f, 0.6f)),
            VertexFormat(glm::vec3(x1, y1,   z1),   color, glm::vec3(0.2f, 0.8f, 0.6f)),
        };

        std::vector<unsigned int> indices = {
            // Bottom face
            0, 1, 2,
            0, 2, 3,
            // Top face
            6, 5, 4,
            7, 6, 4,
            // Front face
            6, 2, 1,
            5, 6, 1,
            // Back face
            0, 3, 7,
            0, 7, 4,
            // Left face
            5, 1, 0,
            4, 5, 0,
            // Right face
            7, 3, 2,
            6, 7, 2,
        };

        Mesh* cubeMesh = new Mesh(name);
        cubeMesh->InitFromData(vertices, indices);
        meshes[name] = cubeMesh;
}

void object3D::CreateBuilding(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name) {
        float x = 1.0f;
        float y = 2.0f;
        float z = 1.0f;

        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-x, 0.0f,  z), glm::vec3(0.501f, 0.501f, 0.501f), glm::vec3(0.2f, 0.8f, 0.6f)), // 0
            VertexFormat(glm::vec3(x, 0.0f,  z), glm::vec3(0.501f, 0.501f, 0.501f), glm::vec3(0.2f, 0.8f, 0.6f)),  // 1
            VertexFormat(glm::vec3(-x, 2 * y,  z), glm::vec3(0.501f, 0.501f, 0.501f), glm::vec3(0.2f, 0.8f, 0.6f)), // 2
            VertexFormat(glm::vec3(x, 2 * y,  z), glm::vec3(0.501f, 0.501f, 0.501f), glm::vec3(0.2f, 0.8f, 0.6f)),  // 3
            VertexFormat(glm::vec3(-x, 0.0f, -z), glm::vec3(0.501f, 0.501f, 0.501f), glm::vec3(0.2f, 0.8f, 0.6f)), // 4
            VertexFormat(glm::vec3(x, 0.0f, -z), glm::vec3(0.501f, 0.501f, 0.501f), glm::vec3(0.2f, 0.8f, 0.6f)),  // 5
            VertexFormat(glm::vec3(-x, 2 * y, -z), glm::vec3(0.501f, 0.501f, 0.501f), glm::vec3(0.2f, 0.8f, 0.6f)), // 6
            VertexFormat(glm::vec3(x, 2 * y, -z), glm::vec3(0.501f, 0.501f, 0.501f), glm::vec3(0.2f, 0.8f, 0.6f)),  // 7
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,
        };

        Mesh* buildingMesh = new Mesh(name);
        buildingMesh->InitFromData(vertices, indices);
        meshes[name] = buildingMesh;
}

void object3D::CreateTree(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name) {
        // Parameters for the cylinder (trunk)
        float radiusCyl = 0.15f;
        float heightCyl = 1.6f;
        int numSegmentsCyl = 100;

        // Parameters for the cone (foliage)
        float radiusCone = 0.6f;
        float heightCone = 0.8f;
        int numSegmentsCone = 100;

        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        // Trunk
        int baseIndexCyl = vertices.size();
        vertices.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.157f, 0.078f), glm::vec3(0.2f, 0.8f, 0.6f)); // Center bottom
        for (int i = 0; i <= numSegmentsCyl; ++i) {
            float angle = 2.0f * M_PI * i / numSegmentsCyl;
            float x = radiusCyl * std::cos(angle);
            float z = radiusCyl * std::sin(angle);
            vertices.emplace_back(glm::vec3(x, 0.0f, z), glm::vec3(0.2f, 0.157f, 0.078f), glm::vec3(0.2f, 0.8f, 0.6f));
        }
        vertices.emplace_back(glm::vec3(0.0f, heightCyl, 0.0f), glm::vec3(0.2f, 0.157f, 0.078f), glm::vec3(0.2f, 0.8f, 0.6f)); // Center top
        for (int i = 0; i <= numSegmentsCyl; ++i) {
            float angle = 2.0f * M_PI * i / numSegmentsCyl;
            float x = radiusCyl * std::cos(angle);
            float z = radiusCyl * std::sin(angle);
            vertices.emplace_back(glm::vec3(x, heightCyl, z), glm::vec3(0.2f, 0.157f, 0.078f), glm::vec3(0.2f, 0.8f, 0.6f));
        }

        // Indices for Trunk
        for (int i = 1; i <= numSegmentsCyl; ++i) {
            indices.push_back(baseIndexCyl + 0);
            indices.push_back(baseIndexCyl + i);
            indices.push_back(baseIndexCyl + i + 1);
        }
        int offsetCylTop = baseIndexCyl + numSegmentsCyl + 2;
        for (int i = 1; i <= numSegmentsCyl; ++i) {
            indices.push_back(offsetCylTop);
            indices.push_back(offsetCylTop + i);
            indices.push_back(offsetCylTop + i + 1);
        }

        for (int i = 1; i <= numSegmentsCyl; ++i) {
            int next = (i % numSegmentsCyl) + 1;
            indices.push_back(baseIndexCyl + i);
            indices.push_back(baseIndexCyl + next);
            indices.push_back(offsetCylTop + i);

            indices.push_back(baseIndexCyl + next);
            indices.push_back(offsetCylTop + next);
            indices.push_back(offsetCylTop + i);
        }

        // First Cone (Foliage)
        int baseIndexCone1 = vertices.size();
        vertices.emplace_back(glm::vec3(0.0f, heightCyl, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)); // Base center
        for (int i = 0; i < numSegmentsCone; ++i) {
            float angle = 2.0f * M_PI * i / numSegmentsCone;
            float x = radiusCone * std::cos(angle);
            float z = radiusCone * std::sin(angle);
            vertices.emplace_back(glm::vec3(x, heightCyl, z), glm::vec3(0.0f, 0.4f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f));
        }
        vertices.emplace_back(glm::vec3(0.0f, heightCyl + heightCone, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)); // Tip

        // Indices for First Cone
        for (int i = 1; i < numSegmentsCone; ++i) {
            indices.push_back(baseIndexCone1 + 0);
            indices.push_back(baseIndexCone1 + i);
            indices.push_back(baseIndexCone1 + i + 1);
        }
        indices.push_back(baseIndexCone1 + 0);
        indices.push_back(baseIndexCone1 + numSegmentsCone);
        indices.push_back(baseIndexCone1 + 1);

        int tipIndexCone1 = baseIndexCone1 + numSegmentsCone + 1;
        for (int i = 1; i < numSegmentsCone; ++i) {
            indices.push_back(tipIndexCone1);
            indices.push_back(baseIndexCone1 + i);
            indices.push_back(baseIndexCone1 + i + 1);
        }
        indices.push_back(tipIndexCone1);
        indices.push_back(baseIndexCone1 + numSegmentsCone);
        indices.push_back(baseIndexCone1 + 1);

        // Second Cone (Additional Foliage)
        int baseIndexCone2 = vertices.size();
        float cone2BaseHeight = heightCyl + 0.4f;
        vertices.emplace_back(glm::vec3(0.0f, cone2BaseHeight, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)); // Base center
        for (int i = 0; i < numSegmentsCone; ++i) {
            float angle = 2.0f * M_PI * i / numSegmentsCone;
            float x = radiusCone * std::cos(angle);
            float z = radiusCone * std::sin(angle);
            vertices.emplace_back(glm::vec3(x, cone2BaseHeight, z), glm::vec3(0.0f, 0.4f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f));
        }
        vertices.emplace_back(glm::vec3(0.0f, cone2BaseHeight + heightCone, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)); // Tip

        // Indices for Second Cone
        for (int i = 1; i < numSegmentsCone; ++i) {
            indices.push_back(baseIndexCone2 + 0);
            indices.push_back(baseIndexCone2 + i);
            indices.push_back(baseIndexCone2 + i + 1);
        }
        indices.push_back(baseIndexCone2 + 0);
        indices.push_back(baseIndexCone2 + numSegmentsCone);
        indices.push_back(baseIndexCone2 + 1);

        int tipIndexCone2 = baseIndexCone2 + numSegmentsCone + 1;
        for (int i = 1; i < numSegmentsCone; ++i) {
            indices.push_back(tipIndexCone2);
            indices.push_back(baseIndexCone2 + i);
            indices.push_back(baseIndexCone2 + i + 1);
        }
        indices.push_back(tipIndexCone2);
        indices.push_back(baseIndexCone2 + numSegmentsCone);
        indices.push_back(baseIndexCone2 + 1);

        Mesh* treeMesh = new Mesh(name);
        treeMesh->InitFromData(vertices, indices);
        meshes[name] = treeMesh;
}

void object3D::CreateArrow(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name) {
        float lungime = 0.4f;

        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)), // 0
            VertexFormat(glm::vec3(lungime, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)), // 1
            VertexFormat(glm::vec3(lungime / 2.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)), // 2 (Tipul săgeții)
        };

        std::vector<unsigned int> indices = {
            0, 1, 2
        };

        Mesh* arrowMesh = new Mesh(name);
        arrowMesh->InitFromData(vertices, indices);
        meshes[name] = arrowMesh;
}

void object3D::CreateCheckpoint(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name) {
        float radius = 1.0f;
        int numSegments = 100;
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        vertices.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.2f, 0.8f, 0.6f)); // Center

        for (int i = 0; i <= numSegments; ++i) {
            float angle = 2.0f * M_PI * i / numSegments;
            float x = radius * std::cos(angle);
            float z = radius * std::sin(angle);
            vertices.emplace_back(glm::vec3(x, 1.0f, z), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.2f, 0.8f, 0.6f));
        }

        for (int i = 1; i <= numSegments; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        Mesh* checkpointMesh = new Mesh(name);
        checkpointMesh->InitFromData(vertices, indices);
        meshes[name] = checkpointMesh;
}

void object3D::CreatePackagePosition(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name) {
        float L = 0.5f;
        float l = 0.5f;

        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)), // 0
            VertexFormat(glm::vec3(L, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)), // 1
            VertexFormat(glm::vec3(L, 1.0f,  l), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)), // 2
            VertexFormat(glm::vec3(0.0f, 1.0f,  l), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.8f, 0.6f)), // 3
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 0,
        };

        Mesh* packagePositionMesh = new Mesh(name);
        packagePositionMesh->InitFromData(vertices, indices);
        meshes[name] = packagePositionMesh;
}

void object3D::CreateTerrain(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name) {
    int n = 200;

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // Generare vertec?i
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            vertices.push_back(VertexFormat(glm::vec3(i, 0.0, j), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)));
        }
    }

    // Generare indici
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int start = i * (n + 1) + j;
            indices.push_back(start);
            indices.push_back(start + 1);
            indices.push_back(start + n + 1);

            indices.push_back(start + 1);
            indices.push_back(start + n + 2);
            indices.push_back(start + n + 1);
        }
    }

    Mesh* packagePositionMesh = new Mesh(name);
    packagePositionMesh->InitFromData(vertices, indices);
    meshes[name] = packagePositionMesh;
}
