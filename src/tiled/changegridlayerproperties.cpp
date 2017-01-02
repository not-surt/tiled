/*
 * changegridlayerproperties.cpp
 * Copyright 2010, Jeff Bland <jksb@member.fsf.org>
 * Copyright 2010, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
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

#include "changegridlayerproperties.h"

#include "mapdocument.h"
#include "gridlayer.h"

#include <QCoreApplication>

using namespace Tiled;
using namespace Tiled::Internal;

ChangeGridLayerProperties::ChangeGridLayerProperties(
        MapDocument *mapDocument,
        GridLayer *gridLayer,
        const QColor &newColor,
        const int newGridWidth,
        const int newGridHeight)
    : QUndoCommand(
          QCoreApplication::translate(
              "Undo Commands", "Change Image Layer Properties"))
    , mMapDocument(mapDocument)
    , mGridLayer(gridLayer)
    , mUndoColor(gridLayer->color())
    , mRedoColor(newColor)
    , mUndoGridWidth(gridLayer->gridWidth())
    , mRedoGridWidth(newGridWidth)
    , mUndoGridHeight(gridLayer->gridHeight())
    , mRedoGridHeight(newGridHeight)
{
}

void ChangeGridLayerProperties::redo()
{
    mGridLayer->setColor(mRedoColor);
    mGridLayer->setGridSize(QSize(mRedoGridWidth, mRedoGridHeight));

    mMapDocument->emitGridLayerChanged(mGridLayer);
}

void ChangeGridLayerProperties::undo()
{
    mGridLayer->setColor(mUndoColor);
    mGridLayer->setGridSize(QSize(mUndoGridWidth, mUndoGridHeight));

    mMapDocument->emitGridLayerChanged(mGridLayer);
}

