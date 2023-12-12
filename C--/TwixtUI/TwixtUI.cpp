#include "TwixtUI.h"


TwixtUI::TwixtUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("Twixt With a Twist! - C--");
    m_game = IGame::CreateGame();
}

TwixtUI::~TwixtUI()
{}

void TwixtUI::paintEvent(QPaintEvent * e)
{
    QPainter p(this);
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(5);
    for (int i = 0; i < 24; i++)
    {
        if (i == 0 || i == 23)
        {
            p.drawLine(95, 80, 95, 23 * 25 + 80);
        }
        for (int j = 0; j < 24; j++)
        {
            if ((i == 0 && j == 0) || (i == 0 && j == 23) || (i == 23 && j == 0) || (i == 23 && j == 23))
                continue;
            QRect r(i * 25 + 75, j * 25 + 75, 15, 15);
            p.drawEllipse(r);
        }
    }
}


