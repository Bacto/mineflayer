#ifndef CHUNK_H
#define CHUNK_H

#include <QtGlobal>

#include <OpenEXR/ImathVec.h>
using namespace Imath;

uint qHash(const Vec3<int> & coord);

#include <QVector>
#include <QSharedPointer>
#include <QHash>

#include "Drawable.h"
#include "Texture.h"
#include "Mesh.h"
#include "MeshInstance.h"

class Chunk : public Drawable {
public:
    typedef Vec3<int> Coord;

    struct Block {
        int type;
        int metadata;
        int light;
        int sky_light;
        QSharedPointer<MeshInstance> mesh_instance;
    };

public:
    Chunk(const Coord & pos);

    // use to set or retrieve Block data. Call updateBlock when done.
    QSharedPointer<Block> getBlock(const Coord & coord) const;
    // call this if you edit the data from a block.
    void updateBlock(const Coord & coord);

    // debug method to generate random blocks
    void randomize();

protected:
    void render();

private:
    Coord m_pos;
    Vec3<int> m_size;
    QVector<QSharedPointer<Block> > m_blocks;

    static bool s_initialized;
    static QHash<QString, Texture *> s_textures;
    static QVector<Mesh *> s_meshes;

private:
    int indexOf(const Coord & coord) const;

    static void initialize();

    void updateEntireChunkMesh();
};

#endif // CHUNK_H
