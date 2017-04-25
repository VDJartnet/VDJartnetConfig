//This file is part of VDJartnetConfig.
//
//VDJartnetConfig is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//VDJartnetConfig is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with VDJartnetConfig.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TEXTUNDOCOMMAND_H
#define TEXTUNDOCOMMAND_H

#include <QUndoCommand>
#include <string>
#include <functional>

class Refreshable {
public:
    virtual void refresh() = 0;
};

class TextUndoCommand : public QUndoCommand {
public:
    enum { Id = -1 };

    TextUndoCommand(std::string* str, std::string oldValue, Refreshable* refreshable = nullptr, QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;
    //bool mergeWith(const QUndoCommand *command) override;
    int id() const override { return Id; }

private:
    std::string* str;
    std::string newValue;
    std::string oldValue;

    Refreshable* refreshable;
};
#endif // TEXTUNDOCOMMAND_H
