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
#include <qmessagebox.h>
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
    virtual void mouseMoveEvent(QMouseEvent* e);

    
    virtual void drawPegs(QPainter& painter,QPen& pen);
    virtual void drawBridges(QPainter& painter, QPen& pen);
    virtual void drawBoardLines(QPainter& painter, QPen& pen);

    virtual void updateGameStatus();
    virtual void updatePlayingDisplay();
    virtual void updatePieceCounters();

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
    bool m_turnSwitched;

    const float pegSpacing = 27.5;
    const float padding = 40;
    const float pegDiameter = 12;

    const float leftPadding = 60;
    const float topPadding = 47;
    const float rightPadding = 32;
    const float bottomPadding = 45;
    const float redTopPadding = 57;
    const float redBottomPadding = 35;
    const float redRightPadding = 50;
};
