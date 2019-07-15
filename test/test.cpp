#include <iostream>
#include <yunikEngine/camera.hpp>
#include <yunikEngine/manager.hpp>
#include <yunikEngine/mesh.hpp>
#include <yunikEngine/scene.hpp>
#include <yunikEngine/shader.hpp>
#include <yunikEngine/window.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>

class testScene : public yunikEngine::Scene {
    public:
    testScene (void) {
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        glm::vec3 vertices[3];
        vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
        vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
        vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

        glGenVertexArrays(1, &VAO);
	    glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        sp = new yunikEngine::ShaderProgram();
        sp->init();

        yunikEngine::Shader vs;
        if (!vs.load(yunikEngine::Shader::Type::VERTEX_SHADER, "shader.vert")){
            printf("vs load failed\n");
        }
        sp->attachShader(vs);

        yunikEngine::Shader fs;
        if (!fs.load(yunikEngine::Shader::Type::FRAGMENT_SHADER, "shader.frag")) {
            printf("fs load failed\n");
        }
        sp->attachShader(fs);

        sp->link();

        cam = new yunikEngine::Camera();
        cam->setPos(glm::vec3(4.0f, 3.0f, 10.0f));
/* 
        m = new yunikEngine::Mesh();
        m->load("bunny.obj");*/
    }

    ~testScene (void) {}

    yunikEngine::Scene* update (void) {
        //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        //m->render();
        sp->use();
        sp->setMat4("Projection", cam->getProjectionMatrix(getWindow()));
        sp->setMat4("View", cam->getViewMatrix());
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        return this;
    }

    void setWindow (yunikEngine::Window* newWindow) {
        yunikEngine::Scene::setWindow(newWindow);
    }

    yunikEngine::Window* getWindow (void) {
        return yunikEngine::Scene::getWindow();
    }
    
    private:
    GLuint VAO;
    GLuint VBO;

    yunikEngine::ShaderProgram* sp;
    yunikEngine::Camera* cam;
    //yunikEngine::Mesh* m;
};

int main (void) {
    if (!yunikEngine::Manager::init()) {
        return -1;
    }

    yunikEngine::Window w;
    w.createWindow(1064, 768, "Hello world!");

    testScene* ts = new testScene();
    ts->setWindow(&w);

    w.setScene(static_cast<yunikEngine::Scene*>(ts));

    w.render();

    yunikEngine::Manager::deinit();
    return 0;
}
