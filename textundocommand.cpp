#include "textundocommand.h"

TextUndoCommand::TextUndoCommand(std::string* str, std::string oldValue, Refreshable* refreshable, QUndoCommand *parent) : QUndoCommand(parent) {
    this->str = str;
    this->oldValue = oldValue;
    this->newValue = *str;
    this->refreshable = refreshable;
}

void TextUndoCommand::undo() {
    *str = oldValue;
    if (refreshable != nullptr) {
        refreshable->refresh();
    }
}

void TextUndoCommand::redo() {
    *str = newValue;
    if (refreshable != nullptr) {
        refreshable->refresh();
    }
}
