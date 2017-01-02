#ifndef GRIDLAYER_H
#define GRIDLAYER_H

#include "tiled_global.h"

#include "layer.h"

namespace Tiled {

class TILEDSHARED_EXPORT GridLayer : public Layer
{
public:
   GridLayer(const QString &name, int x, int y, int width, int height);
   ~GridLayer();

   QSet<SharedTileset> usedTilesets() const override { return QSet<SharedTileset>(); }
   bool referencesTileset(const Tileset *) const override { return false; }
   void replaceReferencesToTileset(Tileset *, Tileset *) override {}

   bool canMergeWith(Layer *) const override { return false; }
   Layer *mergedWith(Layer *) const override { return nullptr; }

   /**
    * Returns the transparent color, or an invalid color if no transparent
    * color is used.
    */
   const QColor &color() const { return mColor; }

   /**
    * Sets the transparent color. Pixels with this color will be masked out
    * when loadFromImage() is called.
    */
   void setColor(const QColor &c) { mColor = c; }

   /**
    * Returns the width of this layer.
    */
   int gridWidth() const { return mGridWidth; }

   /**
    * Returns the height of this layer.
    */
   int gridHeight() const { return mGridHeight; }

   /**
    * Returns the size of this layer.
    */
   QSize gridSize() const { return QSize(mGridWidth, mGridHeight); }

   void setGridSize(const QSize &size);

   bool isEmpty() const override { return false; }

   Layer *clone() const override;

protected:
   GridLayer *initializeClone(GridLayer *clone) const;

private:
    QColor mColor;
    int mGridWidth;
    int mGridHeight;
};

/**
 * Sets the size of this layer.
 */
inline void GridLayer::setGridSize(const QSize &size)
{
    mGridWidth = size.width();
    mGridHeight = size.height();
}

} // namespace Tiled

#endif // GRIDLAYER_H
