#include "lab_m1/tema2/tema2.h"
#include "lab_m1/tema2/object3D.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/lab4/transform3D.h"

#include "core/gpu/mesh.h"
#include "components/simple_scene.h"

using namespace std;
using namespace m1;
using namespace object3D;

Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

void Tema2::Init()
{
    renderCameraTarget = false;

    InitializeCameras();
    InitializeDrone();
    InitializeText();
    InitializeShaders();
    InitializeMeshes();

}

void Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

    glBindVertexArray(0);

    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}

void Tema2::FrameStart()
{
    glClearColor(0.4, 0.4, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Tema2::generateTreePositions(int nr_Tree, vector<glm::vec3>& poz) {
    for (int i = 0; i < nr_Tree; i++) {
        bool validPosition = false;
        glm::vec3 newPosition;

        while (!validPosition) {
            float x = (rand() % 50) - 20;
            float z = (rand() % 50) - 20;
            newPosition = glm::vec3(x, 0, z);

            validPosition = true;
            if ((newPosition.x >= -2 && newPosition.x <= 2) && (newPosition.z >= -2 && newPosition.z <= 2)) {
                validPosition = false;
                continue;
            }
            for (const auto& pos : poz) {
                if (glm::distance(newPosition, pos) < 2.0f) {
                    validPosition = false;
                    break;
                }
            }
        }

        poz.push_back(newPosition);
    }
    treePositions = poz;
}

void Tema2::genretBlocPositions(int nr_Block, vector<glm::vec3>& poz, const vector<glm::vec3>& treePositions) {
    for (int i = 0; i < nr_Block; i++) {
        bool validPosition = false;
        glm::vec3 newPosition;

        while (!validPosition) {
            float x = (rand() % 50) - 20;
            float z = (rand() % 50) - 20;
            newPosition = glm::vec3(x, 0, z);

            validPosition = true;
            if ((newPosition.x >= -2 && newPosition.x <= 2) && (newPosition.z >= -2 && newPosition.z <= 2)) {
                validPosition = false;
                continue;
            }
            for (const auto& pos : poz) {
                if (glm::distance(newPosition, pos) < 3.0f) {
                    validPosition = false;
                    break;
                }
            }
            for (const auto& pos : treePositions) {
                if (glm::distance(newPosition, pos) < 3.0f) {
                    validPosition = false;
                    break;
                }
            }
        }

        poz.push_back(newPosition);
    }
    positionsCladiri = poz;
}

void Tema2::generareZonaDecolare(glm::vec3& poz, const vector<glm::vec3>& treePositions, const vector<glm::vec3>& positionsCladiri) {
    bool validPosition = false;

    while (!validPosition) {
        float x = (rand() % 50) - 20;
        float z = (rand() % 50) - 20;
        poz = glm::vec3(x, 0, z);

        validPosition = true;
        if (poz == glm::vec3(0, 0, 0)) {
            validPosition = false;
            continue;
        }
        for (const auto& pos : treePositions) {
            if (glm::distance(poz, pos) < 2.0f) {
                validPosition = false;
                break;
            }
        }
        for (const auto& pos : positionsCladiri) {
            if (glm::distance(poz, pos) < 2.0f) {
                validPosition = false;
                break;
            }
        }
    }
}

void Tema2::genrareZonaAterizare(glm::vec3& pozAterizare, const glm::vec3& pozDecolare, const vector<glm::vec3>& treePositions, const vector<glm::vec3>& positionsCladiri) {
    bool validPosition = false;

    while (!validPosition) {
        float x = (rand() % 50) - 20;
        float z = (rand() % 50) - 20;
        pozAterizare = glm::vec3(x, 0, z);

        validPosition = true;
        if (pozAterizare == glm::vec3(0, 0, 0)) {
            validPosition = false;
            continue;
        }
        for (const auto& pos : treePositions) {
            if (glm::distance(pozAterizare, pos) < 2.0f) {
                validPosition = false;
                break;
            }
        }
        for (const auto& pos : positionsCladiri) {
            if (glm::distance(pozAterizare, pos) < 2.0f) {
                validPosition = false;
                break;
            }
        }
        if (glm::distance(pozAterizare, pozDecolare) < 5.0f) {
            validPosition = false;
        }

    }
}

void Tema2::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    RenderScene(true);
    string displayText = "Packages: " + to_string(drona.points);
    text->RenderText(displayText, resolution.x - 250, 10.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    // Mini map
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, resolution.x / 3.f, resolution.y / 3.f);

    RenderScene(false);
}



void Tema2::RenderScene(bool Tip) {

    //Start
    {
        if (susPornire == false) {
            susPornire = true;
            camera->TranslateUpward(1);
        }
    }
    RenderDrone(Tip);
    RenderTrees(Tip);
    RenderBuildings(Tip);
    RenderTerrain(Tip);
    RenderPackage(Tip);
    RenderLandingZone(Tip);
    
}

void Tema2::FrameEnd()
{
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, bool Tip) {
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();

    glm::mat4 viewMatrix = Tip ? camera->GetViewMatrix() : orthoCamera->GetViewMatrix();
    glm::mat4 projMatrix = Tip ? projectionMatrix : projectionMatrixOrto;

    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shader->program, "u_texture_0"), 0);
    glUniform1i(glGetUniformLocation(shader->program, "useTexture"), 1);
    glUniform3fv(glGetUniformLocation(shader->program, "overrideColor"), 1, glm::value_ptr(glm::vec3(2.0f, 2.0f, 2.0f)));

    mesh->Render();
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 7.2;
    float VitezRotatieElici = 1.3;
    float cameraSpeed = 5.5;
    drona.speed = 0;

    glm::vec3 NewPosition;
    if (window->KeyHold(GLFW_KEY_W)) {
        NewPosition = camera->CalculateMoveForward(deltaTime * speed * cameraSpeed);
        if (validMove(glm::vec3(drona.moveX, drona.moveY, drona.moveZ), deltaTime, cameraSpeed))
            camera->MoveForward(deltaTime * cameraSpeed);
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        if (validMove(glm::vec3(drona.moveX, drona.moveY, drona.moveZ), deltaTime, cameraSpeed))
            camera->TranslateRight(-deltaTime * cameraSpeed);
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        if (validMove(glm::vec3(drona.moveX, drona.moveY, drona.moveZ), -deltaTime, cameraSpeed))
            camera->MoveForward(-deltaTime * cameraSpeed);
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        if (validMove(glm::vec3(drona.moveX, drona.moveY, drona.moveZ), deltaTime, cameraSpeed)) {
            camera->TranslateRight(deltaTime * cameraSpeed);
        }
    }
    if (window->KeyHold(GLFW_KEY_UP)) {
        if (validMove(glm::vec3(drona.moveX, drona.moveY, drona.moveZ), deltaTime, cameraSpeed)) {
            camera->TranslateUpward(deltaTime * 1.2 * cameraSpeed);
        }
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        if (validMove(glm::vec3(drona.moveX, drona.moveY, drona.moveZ), deltaTime, cameraSpeed)) {
            camera->TranslateUpward(-deltaTime * 1.2 * cameraSpeed);
        }
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        camera->RotateThirdPerson_OY(0.02);
        drona.RotZ += 0.02;
    }
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        camera->RotateThirdPerson_OY(-0.02);
        drona.RotZ -= 0.02;
    }
}

void Tema2::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_SPACE) {
        if (drona.amPachet == false) {
            drona.amPachet = true;
        }
        else {
            drona.amPachet = false;
        }
    }
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = true;
            camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
            camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
        }
    }
}

bool Tema2::validMove(glm::vec3 PozDrona, float deltaTime, float cameraSpeed) {
    float razaColiziuneCladire = 1.7f;
    float razaColiziuneCopac = 0.8f;

    glm::vec3 PozDronaXZ = glm::vec3(PozDrona.x, 0, PozDrona.z);

    if (PozDrona.y <= 4.2f) {
        for (const auto& pos : positionsCladiri) {
            glm::vec3 posXZ = glm::vec3(pos.x, 0, pos.z);
            if (glm::distance(PozDronaXZ, posXZ) < razaColiziuneCladire) {
                camera->MoveForward(-deltaTime * 4 * cameraSpeed);
                return false;
            }
        }
    }

    if (PozDrona.y <= 2.7f) {
        if (PozDrona.y <= 1.4f) {
            razaColiziuneCopac = 0.5f;
        }
        for (const auto& pos : treePositions) {
            glm::vec3 posXZ = glm::vec3(pos.x, 0, pos.z);
            if (glm::distance(PozDronaXZ, posXZ) < razaColiziuneCopac) {
                camera->MoveForward(-deltaTime * 4 * cameraSpeed);
                return false;
            }
        }
    }

    if (PozDrona.y < 1.0f) {
        camera->TranslateUpward(deltaTime * 1.2f * cameraSpeed);
        return false;
    }
    return true;
}

bool Tema2::checkColiziunePachet(glm::vec3 pozPachet) {
    float razaColiziune = 1.f;
    float distanta = glm::distance(glm::vec3(drona.moveX, drona.moveY, drona.moveZ), pozPachet);
    return distanta < razaColiziune;
}

void Tema2::InitializeDrone() {
    drona.moveX = 0.0f;
    drona.moveY = 0.0f;
    drona.moveZ = 0.0f;
    drona.amPachet = false;
    drona.amAvutPachet = false;
    drona.timeAckPachet = 0.1f;
    drona.points = 0;
    drona.RotX = 0.0f;
    drona.RotY = 0.0f;
    drona.RotZ = 0.0f;
    drona.speed = 7.0f;
}

void Tema2::InitializeText() {
    text = new gfxc::TextRenderer(window->props.selfDir, 
                                 window->props.resolution.x, 
                                 window->props.resolution.y);
    text->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 24);
}

void Tema2::InitializeShaders() {
    Shader* shader = new Shader("LabShader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
}

void Tema2::InitializeMeshes() {
    // Load predefined meshes
    Mesh* mesh = new Mesh("pachet");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Initialize other meshes using factory functions
    CreateTerrain(meshes, "teren");
    CreateDrone(meshes, "Drona");
    CreateElice(meshes, "elice");
    CreateCube(meshes, "CUB");
    CreateBuilding(meshes, "Cladire");
    CreateTree(meshes, "copac");
    CreateArrow(meshes, "sageata");
    CreateCheckpoint(meshes, "Checkpoint");
    CreatePackagePosition(meshes, "pachetPos");
}

void Tema2::InitializeCameras() {
    camera = new implemented::Camera();
    camera->Set(glm::vec3(-1.154f, 1.154f, -1.154f), 
               glm::vec3(0.0f, 0.0f, 0.0f), 
               glm::vec3(0.0f, 1.0f, 0.0f));

    // Mini Map
    orthoCamera = new implemented::Camera();
    orthoCamera->Set(glm::vec3(0.0f, 10.0f, 0.0f), 
                    glm::vec3(0.0f, 0.0f, 0.0f), 
                    glm::vec3(0.0f, 0.0f, -1.0f));
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    projectionMatrixOrto = glm::ortho(-36.0f, 36.0f, -36.0f, 36.0f, 0.01f, 200.0f);

    fov = 50;
    ortoD = 10;
}

void Tema2::RenderDrone(bool Tip) {
    glm::mat4 modelMatrix = glm::mat4(1);
        glm::mat4 save;

        glm::vec3 cameraTargetPosition = camera->GetTargetPosition();
        float x = cameraTargetPosition.x;
        float y = cameraTargetPosition.y;
        float z = cameraTargetPosition.z;
        drona.moveX = x;
        drona.moveY = y;
        drona.moveZ = z;

        modelMatrix = glm::translate(modelMatrix, cameraTargetPosition);
        modelMatrix = glm::rotate(modelMatrix, (drona.RotZ), glm::vec3(0, 1, 0));

        drona.RotX = 2;

        RenderMesh(meshes["Drona"], shaders["VertexColor"], modelMatrix, Tip);
        if (drona.amAvutPachet) {
            if (drona.timeAckPachet < 1) {
                drona.timeAckPachet += 0.002f;
                glm::ivec2 resolution = window->GetResolution();
                string displayText = "Package delivered";
                text->RenderText(displayText, 10.0f, 10.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.5f));
            } else {
                drona.amAvutPachet = false;
                drona.timeAckPachet = 0.0f;
            }
        }

        if (drona.speed > 0) {
            eliceRotation += eliceRotationSpeed * 2;
        }

        save = modelMatrix;

        float hy = 0.04f;

        modelMatrix = glm::translate(save, glm::vec3(0, hy, 0.4));
        RenderMesh(meshes["CUB"], shaders["VertexColor"], modelMatrix, Tip);

        modelMatrix = glm::translate(save, glm::vec3(0, hy + 0.04, 0.4));
        modelMatrix = glm::rotate(modelMatrix, eliceRotation, glm::vec3(0, 1, 0));
        RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix, Tip);

        modelMatrix = glm::translate(save, glm::vec3(0, hy, -0.4));
        RenderMesh(meshes["CUB"], shaders["VertexColor"], modelMatrix, Tip);

        modelMatrix = glm::translate(save, glm::vec3(0, hy + 0.04, -0.4));
        modelMatrix = glm::rotate(modelMatrix, eliceRotation, glm::vec3(0, 1, 0));
        RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix, Tip);

        modelMatrix = glm::translate(save, glm::vec3(0.4, hy, 0));
        RenderMesh(meshes["CUB"], shaders["VertexColor"], modelMatrix, Tip);

        modelMatrix = glm::translate(save, glm::vec3(0.4, hy + 0.04, 0));
        modelMatrix = glm::rotate(modelMatrix, eliceRotation, glm::vec3(0, 1, 0));
        RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix, Tip);

        modelMatrix = glm::translate(save, glm::vec3(-0.4, hy, 0));
        RenderMesh(meshes["CUB"], shaders["VertexColor"], modelMatrix, Tip);

        modelMatrix = glm::translate(save, glm::vec3(-0.4, hy + 0.04, 0));
        modelMatrix = glm::rotate(modelMatrix, eliceRotation, glm::vec3(0, 1, 0));
        RenderMesh(meshes["elice"], shaders["VertexColor"], modelMatrix, Tip);

        eliceRotation += eliceRotationSpeed;

        if (eliceRotation > 2 * M_PI) {
            eliceRotation = 0;
        }
}
void Tema2::RenderTrees(bool Tip) {
    if (firstTime) {
            generateTreePositions(50, treePositions);
            firstTime = false;
        }
        for (const auto& pos : treePositions) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pos);
            RenderMesh(meshes["copac"], shaders["VertexColor"], modelMatrix, Tip);
        }
}

void Tema2::RenderBuildings(bool Tip) {
    if (firstBloc) {
            genretBlocPositions(5, positionsCladiri, treePositions);
            firstBloc = false;
        }
        for (const auto& pos : positionsCladiri) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, pos);
            RenderMesh(meshes["Cladire"], shaders["VertexColor"], modelMatrix, Tip);
        }
}

void Tema2::RenderTerrain(bool Tip) {
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, -100.0f));
    RenderMesh(meshes["teren"], shaders["LabShader"], modelMatrix, Tip);
}

void Tema2::RenderPackage(bool Tip) {
    if (zonaDecolare == false && drona.amPachet == false) {
        generareZonaDecolare(zonaDecolarePos, treePositions, positionsCladiri);
        zonaDecolare = true;
    }
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, zonaDecolarePos);

    if (drona.amPachet == false) {
        RenderMesh(meshes["pachetPos"], shaders["VertexColor"], modelMatrix, Tip);
    }

    glm::mat4 pachetModelMatrix = glm::mat4(1);

    if (!drona.amPachet) {
        if (checkColiziunePachet(zonaDecolarePos + glm::vec3(0.25, 1.1, 0.25))) {
            drona.amPachet = true;
        }
        pachetModelMatrix = glm::translate(pachetModelMatrix, zonaDecolarePos + glm::vec3(0.25, 1.1, 0.25));
    }
    else {
        glm::vec3 cameraTargetPosition = camera->GetTargetPosition();
        float x = cameraTargetPosition.x;
        float y = cameraTargetPosition.y - 0.12;
        float z = cameraTargetPosition.z;
        pachetModelMatrix = glm::translate(pachetModelMatrix, glm::vec3(x, y, z));
        zonaDecolare = false;

        glm::vec3 dir = glm::normalize(DirSageata - glm::vec3(drona.moveX, drona.moveY, drona.moveZ));
        float angle = atan2(dir.x, dir.z);

        glm::mat4 sageataModelMatrix = glm::mat4(1);
        sageataModelMatrix = glm::translate(sageataModelMatrix, glm::vec3(drona.moveX, 1.f, drona.moveZ));
        sageataModelMatrix = glm::rotate(sageataModelMatrix, angle, glm::vec3(0, 1, 0));
        sageataModelMatrix = glm::scale(sageataModelMatrix, glm::vec3(1.5f));

        RenderMesh(meshes["sageata"], shaders["VertexColor"], sageataModelMatrix, Tip);
    }
    
    pachetModelMatrix = glm::scale(pachetModelMatrix, glm::vec3(0.25));
    if (Tip) RenderMesh(meshes["pachet"], shaders["VertexNormal"], pachetModelMatrix, Tip);
    else {
        glm::mat4 ScalePachet = pachetModelMatrix;
        ScalePachet = glm::scale(ScalePachet, glm::vec3(5.25));

        RenderMesh(meshes["pachet"], shaders["VertexNormal"], ScalePachet, Tip);
    }
}

void Tema2::RenderLandingZone(bool Tip) {
    if (!zonaAterizare) {
        genrareZonaAterizare(zonaAterizarePos, zonaDecolarePos, treePositions, positionsCladiri);
        zonaAterizare = true;
        DirSageata = zonaAterizarePos;
    }

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), zonaAterizarePos);
    if (drona.amPachet) {
        RenderMesh(meshes["Checkpoint"], shaders["VertexColor"], modelMatrix, Tip);
    }

    float distanceToLanding = glm::distance(glm::vec3(drona.moveX, 0.0f, drona.moveZ), zonaAterizarePos);
    if (distanceToLanding < 1.0f && drona.amPachet) {
        drona.amPachet = false;
        drona.points += 1;
        drona.amAvutPachet = true;
        zonaAterizare = false;
    }
}