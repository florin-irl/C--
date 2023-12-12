#include "TwixtUI.h"


TwixtUI::TwixtUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("Twixt With a Twist! - C--");
    m_game = IGame::CreateGame();
    initializeCoordinateMatrix();
    m_selected.setX(-1);
    m_selected.setY(-1);
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
               
            QRect r(j * 27.5 + 40, i * 27.5 + 40, 12, 12);
            p.drawEllipse(r);

          
            
        }
    }
    for (const auto& bridge : m_game->GetBridges())
    {
        float x1, x2, y1, y2;
        x1 = bridge.GetFirstPegPos().GetCol()*27.5+40;
        y1 = bridge.GetFirstPegPos().GetRow()*27.5+40;
        x2 = bridge.GetSecondPegPos().GetCol() * 27.5 + 40;
        y2 = bridge.GetSecondPegPos().GetRow() * 27.5 + 40;
        p.drawLine(40, 40, 50, 50);
        
    }
}

void TwixtUI::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
       for(int i=0;i<24;i++)
           for(int j=0;j<24;j++)
        {
            if (sqrt(pow(m_coordinateMatrix[i][j].x() - e->pos().x(), 2) +
                pow(m_coordinateMatrix[i][j].y() - e->pos().y(), 2)) < 12)
               /*if (fabs(m_coordinateMatrix[i][j].x() - e->pos().x()) < 10 && fabs(m_coordinateMatrix[i][j].y()
                   - e->pos().y() < 10))*/
            {
                
                if (m_selected.x() == -1)
                {
                    try {
                        m_game->PlacePeg(i, j);
                        m_selected = m_coordinateMatrix[i][j];
                    }
                    catch (std::exception)
                    {
                        m_selected.setX(-1);
                        m_selected.setY(-1);
                    }
                }
                else
                {
                    try {
                        int x = (m_selected.x() - 40) / 27.5;
                        int y = (m_selected.y() - 40) / 27.5;
                        m_game->PlaceBridge(y, x, j, i);
                        update();
                        m_selected.setX(-1);
                        m_selected.setY(-1);
                    }
                    catch (std::exception)
                    {
                        m_selected.setX(-1);
                        m_selected.setY(-1);
                    }

                }
                update();
                break;
            }
        }
    }
}

void TwixtUI::initializeCoordinateMatrix()
{
    QPainter p(this);
    QPen pen;
    p.setPen(pen);
    m_coordinateMatrix.resize(24);
    for (int i = 0; i < 24; i++)
    {
        m_coordinateMatrix[i].resize(24);
        for (int j = 0; j < 24; j++)
        {
            double x= i * 27.5 + 40;
            double y= j * 27.5 + 40;
            m_coordinateMatrix[i][j].setX(y);
            m_coordinateMatrix[i][j].setY(x);
            
        }
    }


}


void TwixtUI::on_pushButton_clicked()
{
    m_game->SwitchTurn();
    m_selected.setX(-1);
    m_selected.setY(-1);
}
