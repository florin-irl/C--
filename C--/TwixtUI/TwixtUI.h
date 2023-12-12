#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TwixtUI.h"

class TwixtUI : public QMainWindow
{
    Q_OBJECT

public:
    TwixtUI(QWidget *parent = nullptr);
    ~TwixtUI();

private:
    Ui::TwixtUIClass ui;
};
