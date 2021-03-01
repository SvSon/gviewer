#pragma once

#include <QWidget>
#include <QColor>

namespace Ui {
class ColorPicker;
}

namespace gviewer {

/// Виждет выбора цвета
class ColorPicker : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPicker(QWidget *parent = nullptr);
    explicit ColorPicker(const QString& title, QWidget *parent = nullptr);
    ~ColorPicker();

    /// Установить заголовок цвета
    void setTitle(const QString& title);
    /// Установить цвет
    void setColor(const QColor& color);

private slots:
    /// Выбрыть цвет из диалогового окна
    void chooseColor();

signals:
    /// Сигнал изменения цвета
    void colorChanged(const QColor& color);

private:
    Ui::ColorPicker *ui;
};

}
