/*
 * changegridlayerproperties.h
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

#ifndef CHANGEGRIDLAYERPROPERTIES_H
#define CHANGEGRIDLAYERPROPERTIES_H

#include <QColor>
#include <QString>
#include <QUndoCommand>

namespace Tiled {

class GridLayer;

namespace Internal {

class MapDocument;

class ChangeGridLayerProperties : public QUndoCommand
{
public:
    /**
     * Constructs a new 'Change Image Layer Properties' command.
     *
     * @param mapDocument   the map document of the layer's map
     * @param gridLayer    the grid layer to modify
     * @param newColor      the new transparent color to apply
     */
    ChangeGridLayerProperties(MapDocument *mapDocument,
                              GridLayer *gridLayer,
                              const QColor &newColor,
                              const int newGridWidth,
                              const int newGridHeight);

    void undo() override;
    void redo() override;

private:
    MapDocument *mMapDocument;
    GridLayer *mGridLayer;
    const QColor mUndoColor;
    const QColor mRedoColor;
    const int mUndoGridWidth;
    const int mRedoGridWidth;
    const int mUndoGridHeight;
    const int mRedoGridHeight;
};

} // namespace Internal
} // namespace Tiled

#endif // CHANGEGRIDLAYERPROPERTIES_H
