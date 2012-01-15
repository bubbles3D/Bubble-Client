#include <cstring>

#include "model.h"

Model* Model::instance = NULL;

Model::Model()
{

}

Model* Model::getInstance()
{
    if (Model::instance == NULL)
    {
        Model::instance = new Model();
    }

    return Model::instance;
}
