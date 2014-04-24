/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2013 Fachhochschule Potsdam - http://fh-potsdam.de

Fritzing is free software: you can redistribute it and/or modify
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

#include "commands.h"
#include "debugdialog.h"
#include "sketch/infographicsview.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CommandProgress::CommandProgress() {
    m_active = false;
}

void CommandProgress::setActive(bool active) {
    m_active = active;
}

bool CommandProgress::active() {
    return m_active;
}

void CommandProgress::emitUndo() {
    emit incUndo();
}

void CommandProgress::emitRedo() {
    emit incRedo();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int BaseCommand::nextIndex = 0;
CommandProgress BaseCommand::m_commandProgress;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BaseCommand::BaseCommand(BaseCommand::CrossViewType crossViewType, InfoGraphicsView * infoGraphicsView, QUndoCommand *parent)
	: QUndoCommand(parent)
{
	m_skipFirstRedo = m_undoOnly = m_redoOnly = false;
	m_crossViewType = crossViewType;
    m_infoGraphicsView = infoGraphicsView;
	m_parentCommand = parent;
	m_index = BaseCommand::nextIndex++;
}

BaseCommand::~BaseCommand() {
	foreach (BaseCommand * baseCommand, m_commands) {
		delete baseCommand;
	}
	m_commands.clear();
}

BaseCommand::CrossViewType BaseCommand::crossViewType() const {
	return m_crossViewType;
}

void BaseCommand::setCrossViewType(BaseCommand::CrossViewType crossViewType) {
	m_crossViewType = crossViewType;
}

InfoGraphicsView* BaseCommand::infoGraphicsView() const {
    return m_infoGraphicsView;
}

QString BaseCommand::getDebugString() const {
	return QString("%1 %2").arg(getParamString()).arg(text());
}

void BaseCommand::setUndoOnly() {
	m_undoOnly = true;
}

void BaseCommand::setRedoOnly()
{
	m_redoOnly = true;
}

void BaseCommand::setSkipFirstRedo() {
    m_skipFirstRedo = true;
}

QString BaseCommand::getParamString() const {
	return QString("%1 %2")
        .arg(m_infoGraphicsView->viewName())
		.arg((m_crossViewType == BaseCommand::SingleView) ? "single-view" : "cross-view");
}

int BaseCommand::subCommandCount() const {
	return m_commands.count();
}

const BaseCommand * BaseCommand::subCommand(int ix) const {
	if (ix < 0) return NULL;
	if (ix >= m_commands.count()) return NULL;

	return m_commands.at(ix);
}

void BaseCommand::addSubCommand(BaseCommand * subCommand) {
	m_commands.append(subCommand);
#ifndef QT_NO_DEBUG
    if (m_infoGraphicsView != NULL) {
        m_infoGraphicsView->writeUndo(subCommand, 4, this);
	}
#endif
}

const QUndoCommand * BaseCommand::parentCommand() const {
	return m_parentCommand;
}

void BaseCommand::subUndo() {
	for (int i = m_commands.count() - 1; i >= 0; i--) { 
		m_commands[i]->undo();
	}
}

void BaseCommand::subRedo() {
	foreach (BaseCommand * command, m_commands) {
		command->redo();
	}
}

void BaseCommand::subUndo(int index) {
	if (index < 0 || index >= m_commands.count()) return;

	m_commands[index]->undo();

}

void BaseCommand::subRedo(int index) {
	if (index < 0 || index >= m_commands.count()) return;

	m_commands[index]->redo();
}

int BaseCommand::index() const {
	return m_index;
}

void BaseCommand::undo() {
    if (m_commandProgress.active()) m_commandProgress.emitUndo();
}

void BaseCommand::redo() {
    if (m_commandProgress.active()) m_commandProgress.emitRedo();
}

CommandProgress * BaseCommand::initProgress() {
    m_commandProgress.setActive(true);
    return &m_commandProgress;
}

void BaseCommand::clearProgress() {
    m_commandProgress.setActive(false);
}

int BaseCommand::totalChildCount(const QUndoCommand * command) {
    int cc = command->childCount();
    int tcc = cc;
    for (int i = 0; i < cc; i++) {
        tcc += totalChildCount(command->child(i));
    }
    return tcc;
}

////////////////////////////////////

TemporaryCommand::TemporaryCommand(const QString & text) : QUndoCommand(text) {
    m_enabled = true;
}

TemporaryCommand::~TemporaryCommand() {
}

void TemporaryCommand::setEnabled(bool enabled) {
    m_enabled = enabled;
}

 void TemporaryCommand::redo() {
     if (m_enabled) {
         QUndoCommand::redo();
     }
}

