#include "model3D.hpp"

Model3D::Model3D(sf::Vector3f n_coo,std::string geo,float coeff_size):
    coo(n_coo),
    file(geo),
    size(coeff_size)
{
    std::ifstream goe_file(file);

    std::string line;

    std::vector<std::vector<int>> vectorNormalIndex;

    while(std::getline(goe_file, line))
    {   
        
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v")
        {
            //def points
            sf::Vector3f nv;
            ss >> nv.x >> nv.z >> nv.y;
            nv.y = -nv.y;
            points.push_back(nv);
        }
        if (type == "vn")
        {
            //def points
            sf::Vector3f vectorNormal;
            ss >> vectorNormal.x >> vectorNormal.z >> vectorNormal.y;
            vectorNormal.y = -vectorNormal.y;
            vn.push_back(vectorNormal);
        }
        if (type == "f")
        {
            //def faces

            std::vector<int> index_vertex;

            std::vector<int> v_i;

            std::string vert;
            while (ss >> vert)
            {
                std::stringstream vs(vert);
                std::string indexStr;

                //vertex index
                std::getline(vs, indexStr, '/');
                index_vertex.push_back(std::stoi(indexStr) - 1);

                //texture index
                std::getline(vs, indexStr, '/');

                //normal index
                std::getline(vs, indexStr, '/');
                v_i.push_back(std::stoi(indexStr) - 1);

            }

            vectorNormalIndex.push_back(v_i);

            faces.push_back(index_vertex);
        }
    
    }

    v = points;

    for (int z = 0; z < vectorNormalIndex.size(); z++)
    {
        
        sf::Vector3f nv;

        for (int y = 0; y < vectorNormalIndex[z].size(); y++)
        {
            nv += vn[vectorNormalIndex[z][y]];
        }

        float no = std::sqrt(nv.x*nv.x + nv.y*nv.y + nv.z*nv.z);

        nv = nv/no;

        vn_by_face.push_back(nv);
    }

    std::vector<sf::Vector3f> vertex_in_space;

    for (int i = 0; i < points.size(); i++)
    {
        vertex_in_space.push_back((points[i]*size)+coo);
    }

    points = vertex_in_space;

    vn = vn_by_face;

}

std::vector<sf::Vector3f> Model3D::getVertexs()
{
    return points;
}

std::vector<std::vector<int>> Model3D::getFaces()
{
    return faces;
}

std::vector<sf::Vector3f> Model3D::getVectorNormal()
{
    return vn_by_face;
}

sf::Vector3f Model3D::getCoo()
{
    return coo;
}

void Model3D::turn_model(sf::Vector3f rotation)
{
    std::vector<sf::Vector3f> n_points;
    for (int i = 0; i < v.size(); i++)
    {
        n_points.push_back((rotate_model(v[i],rotation)*size)+coo);
    }
    points = n_points;

    std::vector<sf::Vector3f> n_vn;
    for (int i = 0; i < vn.size(); i++)
    {
        sf::Vector3f n = rotate_model(vn[i], rotation);

        float len = std::sqrt(n.x*n.x + n.y*n.y + n.z*n.z)+0.0001;
        n = n / len;

        n_vn.push_back(n);
    }
    vn_by_face = n_vn;
}