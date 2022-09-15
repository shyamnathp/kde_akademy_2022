from PySide6.QtCore import Slot, Qt, QRect, QSize
from PySide6.QtGui import QColor, QPainter, QTextFormat
from PySide6.QtWidgets import QPlainTextEdit, QWidget, QTextEdit

@Slot()
def highlight_current_line(text_edit: QPlainTextEdit):
    extra_selections = []

    if not text_edit.isReadOnly():
        selection = QTextEdit.ExtraSelection()

        line_color = QColor(Qt.yellow).lighter(160)
        selection.format.setBackground(line_color)

        selection.format.setProperty(QTextFormat.FullWidthSelection, True)

        selection.cursor = text_edit.textCursor()
        selection.cursor.clearSelection()

        extra_selections.append(selection)

    text_edit.setExtraSelections(extra_selections)

text_edit = mainWindow.getTextEdit()
text_edit.cursorPositionChanged.connect(lambda: highlight_current_line(text_edit))