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
    setMouseTracking(true);
    ui.label_18->setText("");
}

TwixtUI::~TwixtUI()
{}




void TwixtUI::paintEvent(QPaintEvent * e)
{
    
    QPainter p(this);
    QPen pen;
    
    //draw border lines
    drawBoardLines(p, pen);
    //draw the pegs
    drawPegs(p,pen);
    //draw the bridges
    drawBridges(p, pen);

    //update piece counters
    updatePieceCounters();

    //update who is playing display
    updatePlayingDisplay();

    //update game status
    updateGameStatus();
}

void TwixtUI::mouseReleaseEvent(QMouseEvent* e)
{
    std::unordered_set<Bridge> bridges = m_game->GetBridges();
    if (e->button() == Qt::LeftButton)
    {
        for (int i = 0; i < m_game->GetBoardSize(); i++)
            for (int j = 0; j < m_game->GetBoardSize(); j++)
            {
                if (sqrt(pow(m_coordinateMatrix[i][j].x() - e->pos().x(), 2) +
                    pow(m_coordinateMatrix[i][j].y() - e->pos().y(), 2)) < 12)
                    /*if (fabs(m_coordinateMatrix[i][j].x() - e->pos().x()) < 10 && fabs(m_coordinateMatrix[i][j].y()
                        - e->pos().y() < 10))*/
                {


                    try {
                        m_game->PlacePeg(i, j);

                    }
                    catch (std::exception excep)
                    {
                        m_selected.setX(-1);
                        m_selected.setY(-1);
                        ui.label_18->setText(excep.what());
                    }


                    update();
                    break;
                }
            }
    }
    if (e->button() == Qt::RightButton && m_game->GetGameState()==EGameState::Playing)
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
                        float xselected = (m_selected.x() - 40) / 27.5;
                        float yselected = (m_selected.y() - 40) / 27.5;

                        int ceilingxselected = static_cast<int>(std::ceil(xselected));
                        int ceilingyselected = static_cast<int>(std::ceil(yselected));

                        float x = (m_coordinateMatrix[i][j].x() - 40) / 27.5;
                        float y = (m_coordinateMatrix[i][j].y() - 40) / 27.5;

                        int ceilingx = static_cast<int>(std::ceil(x));
                        int ceilingy = static_cast<int>(std::ceil(y));
                        // de aplicat find


                        //daca deja exista bridge-ul cu nodurile selectate, il sterg
                        if (std::find(bridges.begin(), bridges.end(), Bridge{ Position{ceilingyselected,
                            ceilingxselected},Position{ceilingy,ceilingx} }) != bridges.end())
                        {
                            try
                            {

                                /* if(m_game->)*/
                                m_game->RemoveBridge(ceilingyselected, ceilingxselected, ceilingy, ceilingx);
                                m_selected.setX(-1);
                                m_selected.setY(-1);
                            }
                            catch (std::exception excep)
                            {
                                ui.label_18->setText(excep.what());
                            }
                            float xselected = (m_selected.x() - 40) / 27.5;
                            float yselected = (m_selected.y() - 40) / 27.5;

                            int ceilingxselected = static_cast<int>(std::ceil(xselected));
                            int ceilingyselected = static_cast<int>(std::ceil(yselected));

                            float x = (m_coordinateMatrix[i][j].x() - 40) / 27.5;
                            float y = (m_coordinateMatrix[i][j].y() - 40) / 27.5;

                            int ceilingx = static_cast<int>(std::ceil(x));
                            int ceilingy = static_cast<int>(std::ceil(y));
                        }
                        else
                        {

                            try {
                                //creez un bridge de la nodul selectat pana in punctul nou determinat;


                                m_selected.setX(-1);
                                m_selected.setY(-1);
                                m_game->PlaceBridge(ceilingyselected, ceilingxselected, ceilingy, ceilingx);
                            }
                            catch (std::exception excep)
                            {
                                ui.label_18->setText(excep.what());
                            }
                        }
                        update();
                        break;
                    }
                }
            }
    }
}

void TwixtUI::mouseMoveEvent(QMouseEvent* e)
{
   /* QPainter painter;
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    switch (m_game->GetTurn())
    {
    case EPiece::BlackPeg:
        painter.setBrush(QColor(Qt::black));
        break;
    case EPiece::RedPeg:
        painter.setBrush(QColor(Qt::red));
        break;

    }
    for (int i = 0; i < m_game->GetBoardSize(); i++)
    {

        for (int j = 0; j < m_game->GetBoardSize(); j++)
        {
            if (sqrt(pow(m_coordinateMatrix[i][j].x() - e->pos().x(), 2) +
                pow(m_coordinateMatrix[i][j].y() - e->pos().y(), 2)) < 12)
            {
                QRect r(j * 27.5 + 40, i * 27.5 + 40, 12, 12);
                painter.drawEllipse(r);
                update();
                break;
            }
        }
    }*/
    QPainter painter;
    QPen pen;
    pen.setWidth(10);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QRect r(e->pos().x(), e->pos().y(), 12, 12);
    painter.drawEllipse(r);
    update();
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

void TwixtUI::drawPegs(QPainter& painter, QPen& pen)
{
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    for (int i = 0; i < m_game->GetBoardSize(); i++)
    {

        for (int j = 0; j < m_game->GetBoardSize(); j++)
        {
            if ((i == 0 && j == 0) || (i == 0 && j == m_game->GetBoardSize() - 1)
                || (i == m_game->GetBoardSize() - 1 && j == 0)
                || (i == m_game->GetBoardSize() - 1 && j == m_game->GetBoardSize() - 1))
                continue;
            switch (m_game->GetPiece(i, j)) {
            case EPiece::RedPeg:
                painter.setBrush(QColor(Qt::red));
                break;

            case EPiece::BlackPeg:
                painter.setBrush(QColor(Qt::black));
                break;

            case EPiece::None:
                painter.setBrush(QColor(Qt::white));
                break;
            }

            if (m_coordinateMatrix[i][j].x() == m_selected.x() &&
                m_coordinateMatrix[i][j].y() == m_selected.y())
            {
                pen.setColor(Qt::green);
                pen.setWidth(3);
                painter.setPen(pen);
            }
            QRect r(j * pegSpacing + padding, i * pegSpacing + padding, pegDiameter, pegDiameter);
            painter.drawEllipse(r);
            pen.setColor(Qt::black);
            pen.setWidth(2);
            painter.setPen(pen);

        }
    }
}

void TwixtUI::drawBridges(QPainter& painter, QPen& pen)
{
    float firstPegX, firstPegY,
        secondPegX, secondPegY;
    for (const auto& bridge : m_game->GetBridges())
    {
        firstPegX = bridge.GetFirstPegPos().GetCol() * pegSpacing + padding;
        firstPegY = bridge.GetFirstPegPos().GetRow() * pegSpacing + padding;
        secondPegX = bridge.GetSecondPegPos().GetCol() * pegSpacing + padding;
        secondPegY = bridge.GetSecondPegPos().GetRow() * pegSpacing + padding;
        switch (m_game->GetPiece(bridge.GetFirstPegPos().GetRow(), bridge.GetFirstPegPos().GetCol()))
        {
        case EPiece::BlackPeg:
            pen.setColor(Qt::black);
            painter.setPen(pen);
            break;
        case EPiece::RedPeg:
            pen.setColor(Qt::red);
            painter.setPen(pen);
            break;
        }
        painter.drawLine(firstPegX + pegDiameter/2, firstPegY + pegDiameter/2, secondPegX + pegDiameter/2, secondPegY + pegDiameter/2);

    }
}

void TwixtUI::drawBoardLines(QPainter& painter, QPen& pen)
{
    pen.setWidth(5);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    //left line
    painter.drawLine(leftPadding, topPadding, leftPadding, (m_game->GetBoardSize()-1) * pegSpacing + topPadding);
    //right line
    painter.drawLine((m_game->GetBoardSize() - 1) * pegSpacing + rightPadding, topPadding, (m_game->GetBoardSize() - 1)
        * pegSpacing + rightPadding, (m_game->GetBoardSize() - 1) * pegSpacing + bottomPadding);

    pen.setColor(Qt::red);
    painter.setPen(pen);

    //top line - facut bine
    painter.drawLine(bottomPadding, redTopPadding, (m_game->GetBoardSize() - 1) * pegSpacing + bottomPadding, redTopPadding);

    //bottom line
    painter.drawLine(bottomPadding, pegSpacing * (m_game->GetBoardSize() - 1) + redBottomPadding, pegSpacing
        * (m_game->GetBoardSize() - 1) + redRightPadding, pegSpacing * (m_game->GetBoardSize() - 1) + redBottomPadding);


}

void TwixtUI::updatePlayingDisplay()
{
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
}

void TwixtUI::updatePieceCounters()
{
    ui.label_5->setText(QString::number(m_game->GetNrRedPegsRemaining()));
    ui.label_6->setText(QString::number(m_game->GetNrRedBridgesRemaining()));
    ui.label_7->setText(QString::number(m_game->GetNrBlackPegsRemaining()));
    ui.label_8->setText(QString::number(m_game->GetNrBlackBridgesRemaining()));
}

void TwixtUI::on_pushButton_2_clicked()
{
    m_game->RestartGame();
    ui.label_18->setText("");
    update();
}

void TwixtUI::on_pushButton_3_clicked()
{
    try
    {
        m_game->SaveGame("data.out");
        
    }
    catch (std::exception excep)
    {
        ui.label_18->setText(excep.what());
    }
}

void TwixtUI::on_pushButton_4_clicked()
{
    try
    {
        m_game->LoadGame("data.out");
        ui.label_18->setText("");
        update();
    }
    catch (std::exception excep)
    {
        ui.label_18->setText(excep.what());
    }
}

void TwixtUI::on_pushButton_5_clicked()
{
    QString text = ui.lineEdit->text();
    bool conversionOk;
    int boardSize = text.toInt(&conversionOk);
    if (!conversionOk)
    {
        QMessageBox::critical(this, "Error", "Input must be a number!", QMessageBox::Ok);
        return;

    }
    if (boardSize < 5 || boardSize>24)
    {
        QMessageBox::critical(this, "Error", "Boardsize must be at least 5 and at most 24!", QMessageBox::Ok);
        return;
    }
    
    text = ui.lineEdit_2->text();
    int nrPegs = text.toInt(&conversionOk);
    if (!conversionOk)
    {
        QMessageBox::critical(this, "Error", "Input must be a number!", QMessageBox::Ok);
        return;
    }
    if (nrPegs < 3)
    {
        QMessageBox::critical(this, "Error", "Nr of pegs should be at least 3!", QMessageBox::Ok);
        return;
    }

    text = ui.lineEdit_3->text();
    int nrBridges = text.toInt(&conversionOk);
    if (!conversionOk)
    {
        QMessageBox::critical(this, "Error", "Input must be a number!", QMessageBox::Ok);
        return;
    }
    if (nrBridges < 2)
    {
        QMessageBox::critical(this, "Error", "Nr of bridges should be at least 2!", QMessageBox::Ok);
        return;
    }
    
    m_game->SetUpGame(boardSize, nrPegs, nrBridges);
    ui.label_18->setText("");
    update();
}

void TwixtUI::initializeCoordinateMatrix()
{
    double x, y;
    m_coordinateMatrix.resize(m_game->GetBoardSize());
    for (int i = 0; i < m_game->GetBoardSize(); i++)
    {
        m_coordinateMatrix[i].resize(m_game->GetBoardSize());
        for (int j = 0; j < m_game->GetBoardSize(); j++)
        {
             y= i * pegSpacing + padding;
             x= j * pegSpacing + padding;
            m_coordinateMatrix[i][j].setX(x);
            m_coordinateMatrix[i][j].setY(y);
            
        }
    }


}


void TwixtUI::on_pushButton_clicked()
{
    try {
        m_game->SwitchTurn();
        m_selected.setX(-1);
        m_selected.setY(-1);
        ui.label_18->setText("");
        update();
    }
    catch (std::exception excep)
    {
        ui.label_18->setText(excep.what());
    }
}


