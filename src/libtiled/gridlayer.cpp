#include "gridlayer.h"

using namespace Tiled;

GridLayer::GridLayer(const QString &name, int x, int y, int width, int height)
    : Layer(GridLayerType, name, x, y, width, height),
    mColor(),
    mGridWidth(16),
    mGridHeight(16)
{
}

GridLayer::~GridLayer()
{
}

Layer *GridLayer::clone() const
{
    return initializeClone(new GridLayer(mName, mX, mY, mWidth, mHeight));
}

GridLayer *GridLayer::initializeClone(GridLayer *clone) const
{
    Layer::initializeClone(clone);

    clone->mColor = mColor;
    clone->mGridWidth = mGridWidth;
    clone->mGridHeight = mGridHeight;

    return clone;
}

