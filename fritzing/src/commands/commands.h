/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2013 Fachhochschule Potsdam - http://fh-potsdam.de

Fritzing is free software: you can redistribute it and/or modify\
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fritzing is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fritzing.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************

$Revision: 6954 $:
$Author: irascibl@gmail.com $:
$Date: 2013-04-05 10:22:00 +0200 (Fr, 05. Apr 2013) $

********************************************************************/

#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include <QHash>
#include <QPainterPath>


#include "utils/misc.h"
#include "items/itembase.h"

/////////////////////////////////////////////

class CommandProgress : public QObject {
    Q_OBJECT

public:
    CommandProgress();

    void setActive(bool);
    bool active();
    void emitUndo();
    void emitRedo();

signals:
    void incUndo();
    void incRedo();

protected:
    bool m_active;
};

/////////////////////////////////////////////

class BaseCommand : public QUndoCommand
{
public:
	enum CrossViewType {
		SingleView,
		CrossView
	};

public:
    BaseCommand(BaseCommand::CrossViewType, class InfoGraphicsView*, QUndoCommand* parent);
	~BaseCommand();

	BaseCommand::CrossViewType crossViewType() const;
	void setCrossViewType(BaseCommand::CrossViewType);
    class InfoGraphicsView* infoGraphicsView() const;
	int subCommandCount() const;
	const BaseCommand * subCommand(int index) const;
	virtual QString getDebugString() const;
	const QUndoCommand * parentCommand() const;
	void addSubCommand(BaseCommand * subCommand);
	void subUndo();
	void subRedo();
	void subUndo(int index);
	void subRedo(int index);
	int index() const;
	void setUndoOnly();
	void setRedoOnly();
    void setSkipFirstRedo();
    void undo();
    void redo();

    static int totalChildCount(const QUndoCommand *);
    static CommandProgress * initProgress();
    static void clearProgress();

protected:
	virtual QString getParamString() const;

	static int nextIndex;

protected:
	BaseCommand::CrossViewType m_crossViewType;
    class InfoGraphicsView * m_infoGraphicsView;
	QList<BaseCommand *> m_commands;
	QUndoCommand * m_parentCommand;
	int m_index;
	bool m_undoOnly;
	bool m_redoOnly;
    bool m_skipFirstRedo;

    static CommandProgress m_commandProgress;
};

/////////////////////////////////////////////

class TemporaryCommand : public QUndoCommand
{

public:
	TemporaryCommand(const QString & text);
	~TemporaryCommand();

    void setEnabled(bool);

    void redo();

protected:
    bool m_enabled;
};


/////////////////////////////////////////////

#endif // COMMANDS_H
