/*
 * gridlayeritem.cpp
 * Copyright 2008-2009, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright 2011, Gregory Nickonov <gregory@nickonov.ru>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "gridlayeritem.h"

#include "gridlayer.h"
#include "mapdocument.h"
#include "maprenderer.h"

#include <QtGlobal>
#include <QtMath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

using namespace Tiled;
using namespace Tiled::Internal;

GridLayerItem::GridLayerItem(GridLayer *layer, MapDocument *mapDocument)
    : mLayer(layer)
    , mMapDocument(mapDocument)
{
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption);

    syncWithGridLayer();
    setOpacity(mLayer->opacity());
    setPos(mLayer->offset());
}

void GridLayerItem::syncWithGridLayer()
{
    prepareGeometryChange();
    //mBoundingRect = mMapDocument->renderer()->boundingRect(mLayer);
    mBoundingRect = QRectF(0, 0, 256, 256);
}

QRectF GridLayerItem::boundingRect() const
{
    return mBoundingRect;
}

void GridLayerItem::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *)
{
    // TODO: Display a border around the layer when selected
    //MapRenderer *renderer = mMapDocument->renderer();
    //renderer->drawGridLayer(painter, mLayer, option->exposedRect);

    const int tileWidth = mLayer->gridWidth();
    const int tileHeight = mLayer->gridHeight();

    if (tileWidth <= 0 && tileHeight <= 0)
        return;

    const QRectF &rect = option->exposedRect;

    const int startX = qMax(0, (int) (rect.x() / tileWidth) * tileWidth);
    const int startY = qMax(0, (int) (rect.y() / tileHeight) * tileHeight);
    const int endX = qMin(qCeil(rect.right()),
                          16 * tileWidth + 1);
    const int endY = qMin(qCeil(rect.bottom()),
                          16 * tileHeight + 1);

    QPen gridPen(mLayer->color());
    //QPen gridPen(QColor(255, 0, 0));
    gridPen.setCosmetic(true);
    gridPen.setDashPattern(QVector<qreal>() << 2 << 2);

    if (startY < endY) {
        gridPen.setDashOffset(startY);
        painter->setPen(gridPen);
        for (int x = startX; x < endX; x += tileWidth)
            painter->drawLine(x, startY, x, endY - 1);
    }

    if (startX < endX) {
        gridPen.setDashOffset(startX);
        painter->setPen(gridPen);
        for (int y = startY; y < endY; y += tileHeight)
            painter->drawLine(startX, y, endX - 1, y);
    }

}
