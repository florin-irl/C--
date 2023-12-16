#include "TwixtUI.h"


TwixtUI::TwixtUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("Twixt With a Twist! by Team C--");
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
  
    for (int i = 0; i < m_game->GetBoardSize(); i++)
    {
        
        for (int j = 0; j < m_game->GetBoardSize(); j++)
        {
            if ((i == 0 && j == 0) || (i == 0 && j == m_game->GetBoardSize() - 1)
                || (i == m_game->GetBoardSize() - 1 && j == 0) 
                || (i == m_game->GetBoardSize() - 1 && j == m_game->GetBoardSize() - 1))
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

    //update piece counters
    ui.label_5->setText(QString::number(m_game->GetNrRedPegsRemaining()));
    ui.label_6->setText(QString::number(m_game->GetNrRedBridgesRemaining()));
    ui.label_7->setText(QString::number(m_game->GetNrBlackPegsRemaining()));
    ui.label_8->setText(QString::number(m_game->GetNrBlackBridgesRemaining()));

    //update who is playing display
    switch (m_game->GetTurn())
    {
    case EPiece::RedPeg:
        ui.label_11->setText("RED");
        ui.label_11->setStyleSheet("color: red; font-family: Bahnschrift;");
        break;
    case EPiece::BlackPeg:
        ui.label_11->setText("BLACK");
        ui.label_11->setStyleSheet("color: black; font-family: Bahnschrift;");
        break;
    }

    //update game status
    updateGameStatus();
}

void TwixtUI::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
       for(int i=0;i< m_game->GetBoardSize();i++)
           for(int j=0;j< m_game->GetBoardSize();j++)
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
        for (int i = 0; i < m_game->GetBoardSize(); i++)
            for (int j = 0; j < m_game->GetBoardSize(); j++)
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
                        //daca deja exista bridge-ul cu nodurile selectate, il sterg
                        try
                        {
                            float xselected = (m_selected.x() - 40) / 27.5;
                            float yselected = (m_selected.y() - 40) / 27.5;

                            int ceilingxselected = static_cast<int>(std::ceil(xselected));
                            int ceilingyselected = static_cast<int>(std::ceil(yselected));

                            float x = (m_coordinateMatrix[i][j].x() - 40) / 27.5;
                            float y = (m_coordinateMatrix[i][j].y() - 40) / 27.5;

                            int ceilingx = static_cast<int>(std::ceil(x));
                            int ceilingy = static_cast<int>(std::ceil(y));
                           /* if(m_game->)*/
                            m_game->RemoveBridge(ceilingyselected, ceilingxselected, ceilingy, ceilingx);
                            m_selected.setX(-1);
                            m_selected.setY(-1);
                        }
                        catch (std::exception)
                        {

                        }


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

void TwixtUI::updateGameStatus()
{
    switch (m_game->GetGameState())
    {
    case EGameState::Draw:
        ui.label_17->setText("DRAW!");
        ui.label_17->setStyleSheet("color: green; font-family: Bahnschrift;");
        break;
    case EGameState::Playing:
        ui.label_17->setText("PLAYING");
        ui.label_17->setStyleSheet("color: gray; font-family: Bahnschrift;");
        break;
    case EGameState::WonByBlack:
        ui.label_17->setText("WON BY BLACK!");
        ui.label_17->setStyleSheet("color: black; font-family: Bahnschrift;");
        break;
    case EGameState::WonByRed:
        ui.label_17->setText("WON BY RED!");
        ui.label_17->setStyleSheet("color: red; font-family: Bahnschrift;");
        break;
    }
   
}

void TwixtUI::on_pushButton_2_clicked()
{
    m_game->RestartGame();
    update();
}

void TwixtUI::on_pushButton_3_clicked()
{
    try
    {
        m_game->SaveGame("data.out");
        
    }
    catch (std::exception)
    {

    }
}

void TwixtUI::on_pushButton_4_clicked()
{
    try
    {
        m_game->LoadGame("data.out");
        update();
    }
    catch (std::exception)
    {

    }
}

void TwixtUI::on_pushButton_5_clicked()
{
    QString text = ui.lineEdit->text();
    bool conversionOk;
    int boardSize = text.toInt(&conversionOk);
    if (!conversionOk)
    {
        qDebug() << "Conversion to int failed.";
    }
    
    text = ui.lineEdit_2->text();
    int nrPegs = text.toInt(&conversionOk);
    if (!conversionOk)
    {
        qDebug() << "Conversion to int failed.";
    }

    text = ui.lineEdit_3->text();
    int nrBridges = text.toInt(&conversionOk);
    if (!conversionOk)
    {
        qDebug() << "Conversion to int failed.";
    }
    

    m_game->SetUpGame(boardSize, nrPegs, nrBridges);
    update();

}



void TwixtUI::initializeCoordinateMatrix()
{
    QPainter p(this);
    QPen pen;
    p.setPen(pen);
    m_coordinateMatrix.resize(m_game->GetBoardSize());
    for (int i = 0; i < m_game->GetBoardSize(); i++)
    {
        m_coordinateMatrix[i].resize(m_game->GetBoardSize());
        for (int j = 0; j < m_game->GetBoardSize(); j++)
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
    try {
        m_game->SwitchTurn();
        m_selected.setX(-1);
        m_selected.setY(-1);
        update();
    }
    catch (std::exception)
    {

    }
}


