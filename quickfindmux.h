/*
 * Copyright (C) 2013 Nicolas Bonnefon and other contributors
 *
 * This file is part of glogg.
 *
 * glogg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * glogg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with glogg.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QUICKFINDMUX_H
#define QUICKFINDMUX_H

#include <QString>

// Interface representing a widget searchable in both direction.
class SearchableWidgetInterface {
  public:
    virtual void searchForward() = 0;
    virtual void searchBackward() = 0;
};

// Interface representing the selector. It will be called and asked
// who the search have to be forwarded to.
class QuickFindMuxSelectorInterface {
  public:
    virtual SearchableWidgetInterface* getActiveSearchable() const = 0;
};

// Represents a multiplexer (unique application wise) dispatching the
// Quick Find search from the UI to the relevant view.
// It owns the QuickFindPattern.
class QuickFindMux
{
  public:

    enum QFDirection {
        Forward,
        Backward,
    };

    // Construct the multiplexer, the selector class will be called
    // and ask who the search have to be forwarded to.
    QuickFindMux( const QuickFindMuxSelectorInterface* selector );

    // Register the mux with this searchable widget for messages
    // to be forwarded back to the client.
    // The client should call this for each possible searchable widget.
    void registerSearchable( const SearchableWidgetInterface* searchable );

    // Set the direction that will be used by the search when searching
    // forward.
    void setDirection( QFDirection direction );

    // Signal the current pattern must be altered (will start an incremental
    // search if the options are configured in such a way).
    void setNewPattern( const QString& new_pattern );

    // Starts a search in the specified direction
    void searchNext();
    void searchPrevious();

    // Idem but ignore the direction and always search in the
    // specified direction
    void searchForward();
    void searchBackward();

  private:
    const QuickFindMuxSelectorInterface* selector_;

    QFDirection currentDirection_;
};

#endif
