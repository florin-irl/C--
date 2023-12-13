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
    
    pen.setWidth(5);
    pen.setColor(Qt::black);

    p.setPen(pen);

    //draw lines
    //left line
    
    p.drawLine(60, 47, 60, 23 * 27.5 + 47);
    //right line
    p.drawLine(23*27.5+32, 47, 23 * 27.5 + 32, 23 * 27.5 + 45);

    pen.setColor(Qt::red);
    p.setPen(pen);
    
    //top line - facut bine
    p.drawLine(45, 57, 23*27.5+45, 57);

    //bottom line
    p.drawLine(45, 27.5*23 +35, 27.5 * 23 + 50,27.5*23+35);

    pen.setWidth(2);
    pen.setColor(Qt::black);
    p.setPen(pen);
  
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
               
            if (m_coordinateMatrix[i][j].x() == m_selected.x() &&
                m_coordinateMatrix[i][j].y() == m_selected.y())
            {
                pen.setColor(Qt::green);
                pen.setWidth(3);
                p.setPen(pen);
            }
            QRect r(j * 27.5 + 40, i * 27.5 + 40, 12, 12);
            p.drawEllipse(r);
            pen.setColor(Qt::black);
            pen.setWidth(2);
            p.setPen(pen);
          
            
        }
    }
    for (const auto& bridge : m_game->GetBridges())
    {
        float x1, x2, y1, y2;
        x1 = bridge.GetFirstPegPos().GetCol()*27.5+40;
        y1 = bridge.GetFirstPegPos().GetRow()*27.5+40;
        x2 = bridge.GetSecondPegPos().GetCol() * 27.5 + 40;
        y2 = bridge.GetSecondPegPos().GetRow() * 27.5 + 40;
        switch (m_game->GetPiece(bridge.GetFirstPegPos().GetRow(), bridge.GetFirstPegPos().GetCol()))
        {
        case EPiece::BlackPeg:
            pen.setColor(Qt::black);
            p.setPen(pen);
            break;
        case EPiece::RedPeg:
            pen.setColor(Qt::red);
            p.setPen(pen);
            break;
        }
        p.drawLine(x1+6, y1+6, x2+6, y2+6);
        
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
                
               
                    try {
                        m_game->PlacePeg(i, j);
                       
                    }
                    catch (std::exception)
                    {
                        m_selected.setX(-1);
                        m_selected.setY(-1);
                    }
                
              
                update();
                break;
            }
        }
    }
    if (e->button() == Qt::RightButton)
    {
        for (int i = 0; i < 24; i++)
            for (int j = 0; j < 24; j++)
            {
                
                if (sqrt(pow(m_coordinateMatrix[i][j].x() - e->pos().x(), 2) +
                    pow(m_coordinateMatrix[i][j].y() - e->pos().y(), 2)) < 12)
                {
                    //deselectez nodul daca apas din nou pe el
                    if (m_selected.x() == m_coordinateMatrix[i][j].x() && m_selected.y() == m_coordinateMatrix[i][j].y())
                    {
                        m_selected.setX(-1);
                        m_selected.setY(-1);
                        update();
                        break;
                    }
                    //setez nodul selectat daca nu este deja unul selectat
                    if (m_selected.x() == -1)
                    {
                        if (m_game->GetPiece(i, j) != EPiece::None && m_game->GetPiece(i, j) == m_game->GetTurn())
                        {
                            m_selected.setX(m_coordinateMatrix[i][j].x());
                            m_selected.setY(m_coordinateMatrix[i][j].y());
                            update();
                            break;
                        }
                    }
                    else
                    {
                        try {
                            //creez un bridge de la nodul selectat pana in punctul nou determinat;
                            float xselected = (m_selected.x() - 40) / 27.5;
                            float yselected = (m_selected.y() - 40) / 27.5;

                            int ceilingxselected = static_cast<int>(std::ceil(xselected));
                            int ceilingyselected = static_cast<int>(std::ceil(yselected));

                            float x = (m_coordinateMatrix[i][j].x() - 40) / 27.5;
                            float y = (m_coordinateMatrix[i][j].y() - 40) / 27.5;

                            int ceilingx = static_cast<int>(std::ceil(x));
                            int ceilingy = static_cast<int>(std::ceil(y));

                            std::ofstream fout("data.out");
                            fout << ceilingxselected << ' ' << ceilingyselected;
                            fout << std::endl;
                            fout << x << ' ' << y;
                            m_selected.setX(-1);
                            m_selected.setY(-1);
                            m_game->PlaceBridge(ceilingyselected, ceilingxselected, ceilingy, ceilingx);
                        }
                        catch(std::exception)
                        {

                        }
                        update();
                        break;
                    }
                    
                   
                    
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
    update();
}
