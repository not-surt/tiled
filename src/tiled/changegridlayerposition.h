/*
 * changegridlayerproperties.h
 * Copyright 2014, Michael Aquilina <michaelaquilina@gmail.com>
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

#ifndef CHANGEGRIDLAYERPOSITION_H
#define CHANGEGRIDLAYERPOSITION_H

#include <QPoint>
#include <QUndoCommand>

namespace Tiled {

class GridLayer;

namespace Internal {

class MapDocument;

class ChangeGridLayerPosition : public QUndoCommand
{
public:
    /**
     * Constructs a new 'Change Image Layer Position' command.
     *
     * @param mapDocument   the map document of the layer's map
     * @param gridLayer    the image layer to modify
     * @param newPos        the new position of the image layer
     */
    ChangeGridLayerPosition(MapDocument *mapDocument,
                             GridLayer *gridLayer,
                             const QPoint &newPos);

    void undo() override;
    void redo() override;

private:
    MapDocument *mMapDocument;
    GridLayer *mGridLayer;
    const QPoint mUndoPos;
    const QPoint mRedoPos;
};

} // namespace Internal
} // namespace Tiled

#endif // CHANGEGRIDLAYERPOSITION_H
