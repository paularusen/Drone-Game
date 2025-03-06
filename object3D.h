#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include <glm/glm.hpp>
#include "core/gpu/mesh.h"
#include "components/simple_scene.h"

namespace object3D
{
    void CreateDrone(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name);
    void CreateElice(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name);
    void CreateCube(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name);
    void CreateBuilding(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name);
    void CreateTree(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name);
    void CreateArrow(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name);
    void CreateCheckpoint(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name);
    void CreatePackagePosition(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name);
    void CreateTerrain(std::unordered_map<std::string, Mesh*>& meshes, const std::string& name);

}
