#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
    static Model* getInstance();

private:
    Model();
    static Model * instance;
};

#endif // MODEL_H
