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
#include <vector>
#include <qpushbutton.h>
#include <fstream>
#include <math.h>
class TwixtUI : public QMainWindow
{
    Q_OBJECT

public:
    TwixtUI(QWidget *parent = nullptr);
    ~TwixtUI();

    virtual void paintEvent(QPaintEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);

    virtual void updateGameStatus();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::TwixtUIClass ui;
    IGamePtr m_game;
    std::vector < std::vector<QPoint>> m_coordinateMatrix;

    void initializeCoordinateMatrix();

    QPoint m_selected;
};
