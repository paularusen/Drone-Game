#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/camera.h"
#include "lab_m1/tema2/object3D.h"

#include "components/text_renderer.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        struct Object
        {
            Mesh* mesh;
            glm::mat4 modelMatrix;
        };

        void Init() override;

    private:
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;


        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void RenderScene(bool Tip);
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, bool Tip);
        bool validMove(glm::vec3 PozDrona, float deltaTime, float cameraSpeed);
        bool checkColiziunePachet(glm::vec3 pozPachet);
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void RenderDrone(bool Tip);
        void RenderTrees(bool Tip);
        void RenderBuildings(bool Tip);
        void RenderTerrain(bool Tip);
        void RenderPackage(bool Tip);
        void RenderLandingZone(bool Tip);
        void InitializeDrone();
        void InitializeText();
        void InitializeShaders();
        void InitializeMeshes();
        void InitializeCameras();
    protected:
        implemented::Camera* camera;
        implemented::Camera* orthoCamera;

        glm::mat4 projectionMatrix;
        glm::mat4 projectionMatrixOrto;

        bool renderCameraTarget;

        float fov;
        float ortoD;

        struct dronaData
        {
            float moveX;
            float moveY;
            float moveZ;

            float RotX;
            float RotY;
            float RotZ;

            bool amPachet;
            bool amAvutPachet;
            float timeAckPachet;

            int points;

            short speed;

        } drona;

        float left;
        float right;
        float bottom;
        float top;

        float eliceRotation = 0;
        float eliceRotationSpeed = 0.1f;
        std::vector<glm::vec3> treePositions;
        std::vector<glm::vec3> positionsCladiri;
        glm::vec3 zonaDecolarePos;
        glm::vec3 zonaAterizarePos;
        glm::vec3 DirSageata;

        bool susPornire = false;
        bool firstTime = true;
        bool firstBloc = true;
        bool zonaDecolare = false;
        bool zonaAterizare = false;

        gfxc::TextRenderer* text;

        void generateTreePositions(int nr_Tree, std::vector<glm::vec3>& poz);
        void genretBlocPositions(int nr_Block, std::vector<glm::vec3>& poz, const std::vector<glm::vec3>& treePositions);
        void generareZonaDecolare(glm::vec3& poz, const std::vector<glm::vec3>& treePositions, const std::vector<glm::vec3>& positionsCladiri);
        void genrareZonaAterizare(glm::vec3& pozAterizare, const glm::vec3& pozDecolare, const std::vector<glm::vec3>& treePositions, const std::vector<glm::vec3>& positionsCladiri);

    };
}   // namespace m1