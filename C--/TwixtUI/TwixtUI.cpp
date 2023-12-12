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
    QBrush brush;
    
    pen.setWidth(2);

    p.setPen(pen);

    //draw lines
    //left line
    
    p.drawLine(60, 47, 60, 23 * 27.5 + 47);
    //right line
    p.drawLine(23*27.5+32, 47, 23 * 27.5 + 32, 23 * 27.5 + 45);

    p.setPen(QColor(Qt::red));
    
    //top line - facut bine
    p.drawLine(45, 57, 23*27.5+45, 57);

    //bottom line
    p.drawLine(45, 27.5*23 +35, 27.5 * 23 + 50,27.5*23+35);

    
    p.setPen(QColor(Qt::black));
    for (int i = 0; i < 24; i++)
    {
        
        for (int j = 0; j < 24; j++)
        {
            if ((i == 0 && j == 0) || (i == 0 && j == 23) || (i == 23 && j == 0) || (i == 23 && j == 23))
                continue;
            switch (m_game->GetPiece(i,j)) {
            case EPiece::RedPeg:
                p.setBrush(QColor(Qt::red));
                break;

            case EPiece::BlackPeg:
                p.setBrush(QColor(Qt::black));
                break;

            case EPiece::None:
                p.setBrush(QColor(Qt::white));
                break;
            }
               
            QRect r(i * 27.5 + 40, j * 27.5 + 40, 12, 12);
            p.drawEllipse(r);
        }
    }
}


