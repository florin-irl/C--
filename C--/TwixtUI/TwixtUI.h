#pragma once

#include <QMouseEvent>
#include <QPaintEvent>
#include <qpainter.h>
#include <QApplication>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QtWidgets/QMainWindow>
#include "ui_TwixtUI.h"
#include "IGame.h"
class TwixtUI : public QMainWindow
{
    Q_OBJECT

public:
    TwixtUI(QWidget *parent = nullptr);
    ~TwixtUI();

    virtual void paintEvent(QPaintEvent* e);

private:
    Ui::TwixtUIClass ui;
    IGamePtr m_game;
};
