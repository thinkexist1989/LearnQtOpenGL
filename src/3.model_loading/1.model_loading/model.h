#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <mesh.h>

#include <string>
#include <vector>

#include <QOpenGLFunctions>

class Model: protected QOpenGLFunctions
{
public:
    // model data
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;

    Model(std::string const &path, bool gamma = false);
    void Draw(QOpenGLShaderProgram* psp);

    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

private:
    void loadModel(const std::string &path);

    void processNode(aiNode *node, const aiScene* scene);
    Mesh processMesh(aiMesh *mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

};

#endif // MODEL_H
