#ifndef MALLA_H
#define MALLA_H

using namespace std;

class malla{
    private:
        GLuint vao, vbo, tbo, ebo;
        int numVertices;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::mat4 modelMatrix;
        char* filename;
        float angle;

        GLuint nfaces;
        GLuint matloc;

    protected:
        GLuint tex;
        GLuint shaderprog;

    public:
        malla(char *filename);

        // gets
        GLuint getVao();
        int getNumVertices();
        glm::vec3 getPosition();
        glm::vec3 getRotation();
        char* getFilename();

        // sets
        void setVao(GLuint vao);
        void setNumVertices(int num);
        void setPosition(glm::vec3 pos);
        void setRotation(float ang, glm::vec3 rot);
        void setFilename(char *f);
        void setModelMatrix(glm::mat4 model);
        void draw(int matloc);

        bool load_texture(const char* file_name);
        void render_indices();
};

#endif
