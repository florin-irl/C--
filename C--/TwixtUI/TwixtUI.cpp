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

    //draw lines
    //left line
    p.setPen(pen);
    p.drawLine(93, 82, 93, 23 * 25 + 82);
    //right line
    p.drawLine(69 + 23 * 25, 82, 69 + 23 * 25, 23 * 25 + 82);
    

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
               
            QRect r(i * 25 + 75, j * 25 + 75, 12, 12);
            p.drawEllipse(r);
        }
    }
}


