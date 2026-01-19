#include "applicgaragewindow.h"
#include "ui_applicgaragewindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <sstream>
#include <iostream>
#include "unistd.h"

#include "Garage.h"
#include "Model.h"
#include "Option.h"
#include "OptionException.h"
#include "PasswordException.h"


#define IMAGES_DIR "../../images/"

using namespace carconfig;

ApplicGarageWindow::ApplicGarageWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::ApplicGarageWindow)
{
    ui->setupUi(this);
    ::close(2);


    // Configuration de la table des options (projet en cours)
    ui->tableWidgetOptions->setColumnCount(3);
    ui->tableWidgetOptions->setRowCount(5);
    for (int i=0 ; i<5 ; i++) ui->tableWidgetOptions->setRowHeight(i,10);
    QStringList labelsTableOptions;
    labelsTableOptions << "Code" << "Prix" << "Intitulé";
    ui->tableWidgetOptions->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetOptions->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetOptions->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetOptions->horizontalHeader()->setVisible(true);
    ui->tableWidgetOptions->horizontalHeader()->setDefaultSectionSize(60);
    ui->tableWidgetOptions->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetOptions->verticalHeader()->setVisible(false);
    ui->tableWidgetOptions->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des employes (Personnel Garage)
    ui->tableWidgetEmployees->setColumnCount(4);
    ui->tableWidgetEmployees->setRowCount(0);
    QStringList labelsTableEmployes;
    labelsTableEmployes << "Numéro" << "Nom" << "Prénom" << "Fonction";
    ui->tableWidgetEmployees->setHorizontalHeaderLabels(labelsTableEmployes);
    ui->tableWidgetEmployees->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetEmployees->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetEmployees->horizontalHeader()->setVisible(true);
    ui->tableWidgetEmployees->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetEmployees->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetEmployees->verticalHeader()->setVisible(false);
    ui->tableWidgetEmployees->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des clients
    ui->tableWidgetClients->setColumnCount(4);
    ui->tableWidgetClients->setRowCount(0);
    QStringList labelsTableClients;
    labelsTableClients << "Numéro" << "Nom" << "Prénom" << "GSM";
    ui->tableWidgetClients->setHorizontalHeaderLabels(labelsTableClients);
    ui->tableWidgetClients->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetClients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetClients->horizontalHeader()->setVisible(true);
    ui->tableWidgetClients->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetClients->verticalHeader()->setVisible(false);
    ui->tableWidgetClients->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des contrats
    ui->tableWidgetContracts->setColumnCount(4);
    ui->tableWidgetContracts->setRowCount(0);
    QStringList labelsTableContrats;
    labelsTableContrats << "Numéro" << "Vendeur" << "Client" << "Voiture";
    ui->tableWidgetContracts->setHorizontalHeaderLabels(labelsTableContrats);
    ui->tableWidgetContracts->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetContracts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetContracts->horizontalHeader()->setVisible(true);
    ui->tableWidgetContracts->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetContracts->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetContracts->verticalHeader()->setVisible(false);
    ui->tableWidgetContracts->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Importation des modeles (étape 10)
    int i;

    Garage &g=Garage::getInstance();

    g.importModelsFromCsv("../../CSVs/models.csv");

    for(i=0; i<g.getNbModels(); i++){
        Model m=g.getModel(i);
        addAvailableModel(m.getName(), m.getBasePrice());
    }

    // Importation des options (étape 10)
    g.importOptionsFromCsv("../../CSVs/options.csv");

    for(i=0; i<g.getNbOptions(); i++){
        Option o=g.getOption(i);

        addAvailableOption(o.getLabel(), o.getPrice());
    }

    setRole();
    MAJtableEmployes();
    // Lecture de config.dat, des employees, clients et contrats (étape 12)
    Garage::getInstance().load();

    

    // ***** TESTS de l'interfac graphique (à supprimer) *****
    //this->addTupleTableEmployees("12;Coptere;Eli;Vendeur");
    //this->addTupleTableEmployees("17;Issier;Paul;Administratif");
    //this->addTupleTableClients("4;Wagner;Jean-Marc;0498.25.36.69");
    //this->addTupleTableContracts("7;Coptere Eli;Wagner Jean-Marc;Projet 208 Wagner");

    this->clearTableOption();
    //this->setTableOption(2,"EMM0","Toit ouvrant panoramique",750.00);
    //this->setTableOption(4);

    //this->setCurrentProjectName("Projet308_Mr_Dugenou");
    //this->setModel("308 Gti Fusee Hybr",120,2,17500.0f,"308");

    //this->addAvailableOption("Peinture metallisee",450.0f);
    //this->addAvailableOption("Jante alliage leger 15 pouces",450.0f);

    //this->addAvailableModel("308 Gti Fusee Hybr",21500.0f);
}

ApplicGarageWindow::~ApplicGarageWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Méthodes de la fenêtre /////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTitle(string title)
{
    this->setWindowTitle(title.c_str());
}

void ApplicGarageWindow::setRole(int val)
{
    // val = 0 --> personne n'est loggé
    // val = 1 --> un administratif est loggé
    // val = 2 --> un vendeur loggé
    // val = 3 --> on a accès à tout

    if (val == 0)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(false);
        ui->actionResetPassword->setEnabled(false);

        ui->menuEmployees->setEnabled(false);

        ui->menuClients->setEnabled(false);

        ui->menuCar->setEnabled(false);
        ui->comboBoxAvailableModels->setEnabled(false);
        ui->comboBoxAvailableOptions->setEnabled(false);
        ui->pushButtonOpenProject->setEnabled(false);
        ui->pushButtonNewProject->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonSaveProject->setEnabled(false);
        ui->pushButtonAddOption->setEnabled(false);
        ui->pushButtonRemoveOption->setEnabled(false);
        ui->pushButtonSelectModel->setEnabled(false);

        ui->pushButtonShowCar->setEnabled(false);
        ui->pushButtonNewContract->setEnabled(false);
        ui->pushButtonDeleteContract->setEnabled(false);
    }

    if (val == 1)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionResetPassword->setEnabled(true);

        ui->menuEmployees->setEnabled(true);

        ui->menuClients->setEnabled(false);

        ui->menuCar->setEnabled(false);
        ui->comboBoxAvailableModels->setEnabled(false);
        ui->comboBoxAvailableOptions->setEnabled(false);
        ui->pushButtonOpenProject->setEnabled(false);
        ui->pushButtonNewProject->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonSaveProject->setEnabled(false);
        ui->pushButtonAddOption->setEnabled(false);
        ui->pushButtonRemoveOption->setEnabled(false);
        ui->pushButtonSelectModel->setEnabled(false);

        ui->pushButtonShowCar->setEnabled(true);
        ui->pushButtonNewContract->setEnabled(false);
        ui->pushButtonDeleteContract->setEnabled(true);
    }

    if (val == 2)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionResetPassword->setEnabled(true);

        ui->menuEmployees->setEnabled(false);

        ui->menuClients->setEnabled(true);

        ui->menuCar->setEnabled(true);
        ui->comboBoxAvailableModels->setEnabled(true);
        ui->comboBoxAvailableOptions->setEnabled(true);
        ui->pushButtonOpenProject->setEnabled(true);
        ui->pushButtonNewProject->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonSaveProject->setEnabled(true);
        ui->pushButtonAddOption->setEnabled(true);
        ui->pushButtonRemoveOption->setEnabled(true);
        ui->pushButtonSelectModel->setEnabled(true);

        ui->pushButtonShowCar->setEnabled(true);
        ui->pushButtonNewContract->setEnabled(true);
        ui->pushButtonDeleteContract->setEnabled(true);
    }

    if (val == 3)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(true);
        ui->actionResetPassword->setEnabled(true);

        ui->menuEmployees->setEnabled(true);

        ui->menuClients->setEnabled(true);

        ui->menuCar->setEnabled(true);
        ui->comboBoxAvailableModels->setEnabled(true);
        ui->comboBoxAvailableOptions->setEnabled(true);
        ui->pushButtonOpenProject->setEnabled(true);
        ui->pushButtonNewProject->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonSaveProject->setEnabled(true);
        ui->pushButtonAddOption->setEnabled(true);
        ui->pushButtonRemoveOption->setEnabled(true);
        ui->pushButtonSelectModel->setEnabled(true);

        ui->pushButtonShowCar->setEnabled(true);
        ui->pushButtonNewContract->setEnabled(true);
        ui->pushButtonDeleteContract->setEnabled(true);
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Table des options du projet en cours (ne pas modifier) /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTableOption(int index,string code,string label,float price)
{
    // Modifie l'option de la ligne correspondant à l'indice fourni dans la table des options de l'interface graphique
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(code.c_str());
    ui->tableWidgetOptions->setItem(index,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    char tmp[20];
    sprintf(tmp,"%.2f",price);
    if (price < 0.0) item->setText("");
    else item->setText(tmp);
    ui->tableWidgetOptions->setItem(index,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(label.c_str());
    ui->tableWidgetOptions->setItem(index,2,item);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearTableOption()
{
    for (int i=0 ; i<5 ; i++) setTableOption(i);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexOptionSelectionTable() const
{
    // retourne l'indice de l'option selectionnee dans la table des options
    QModelIndexList list = ui->tableWidgetOptions->selectionModel()->selectedRows();
    if (list.size() == 0) return -1;
    QModelIndex index = list.at(0);
    int ind = index.row();
    return ind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combobox des modèles disponibles (ne pas modifier) /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addAvailableModel(string name,float basePrice)
{
    // ajoute un modèle dans le combobox correspondant (juste le nom et le prix)
    stringstream ss;
    char temp[20];
    sprintf(temp,"%.2f",basePrice);
    ss << name.c_str() << " (" << temp << ")";
    ui->comboBoxAvailableModels->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearComboBoxAvailableModels()
{
    ui->comboBoxAvailableModels->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexModelSelectionCombobox() const
{
    // retourne l'indice du modèle selectionné dans le combobox des modèles
    return ui->comboBoxAvailableModels->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des options disponibles (ne pas modifier) ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addAvailableOption(string label,float price)
{
    // ajoute une option dans le combobox correspondant
    stringstream ss;
    char temp[20];
    sprintf(temp,"%.2f",price);
    ss << label << " (" << temp << ")";
    ui->comboBoxAvailableOptions->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearComboBoxAvailableOptions()
{
    ui->comboBoxAvailableOptions->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexOptionSelectionCombobox() const
{
    // retourne l'indice de l'option selectionnée dans le combobox des options
    return ui->comboBoxAvailableOptions->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Gestion I/O Projet en cours (ne pas modifier) //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setCurrentProjectName(string name)
{
    // Remplit le champ nom de l'interface graphique avec le nom reçu
    ui->lineEditProjectName->setText(name.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::getCurrentProjectName() const
{
    return ui->lineEditProjectName->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setModel(string name,int power,int engine,float basePrice,string modelImage)
{
    // Remplit les champs correspondants dans l'interface graphique
    // pour le moteur (int) : 0=Essence, 1=Diesel, 2=Electrique, 3=Hybride
    ui->lineEditModelName->setText(name.c_str());
    ui->lineEditPower->setText(to_string(power).c_str());
    char tmp[20];
    sprintf(tmp,"%.2f",basePrice);
    ui->lineEditBasePrice->setText(tmp);

    ui->radioButtonPetrol->setChecked(false);
    ui->radioButtonDiesel->setChecked(false);
    ui->radioButtonElectric->setChecked(false);
    ui->radioButtonHybrid->setChecked(false);

    if (engine == 0) ui->radioButtonPetrol->setChecked(true);
    if (engine == 1) ui->radioButtonDiesel->setChecked(true);
    if (engine == 2) ui->radioButtonElectric->setChecked(true);
    if (engine == 3) ui->radioButtonHybrid->setChecked(true);

    // Met à jour l'image du modèle
    string cheminComplet = IMAGES_DIR + modelImage;
    QLabel* label = new QLabel();
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setScaledContents(true);
    QPixmap *pixmap_img = new QPixmap(cheminComplet.c_str());
    label->setPixmap(*pixmap_img);
    label->resize(label->pixmap()->size());
    ui->scrollArea->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setPrice(float price)
{
  char tmp[20];
  sprintf(tmp,"%.2f",price);
  ui->lineEditPrice->setText(tmp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Employes (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addTupleTableEmployees(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char name[40];
    strcpy(name,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char firstName[40];
    strcpy(firstName,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char fonction[40];
    strcpy(fonction,tmp);

    // Ajout possible
    int nbLines = ui->tableWidgetEmployees->rowCount();
    nbLines++;
    ui->tableWidgetEmployees->setRowCount(nbLines);
    ui->tableWidgetEmployees->setRowHeight(nbLines-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetEmployees->setItem(nbLines-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(name);
    ui->tableWidgetEmployees->setItem(nbLines-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(firstName);
    ui->tableWidgetEmployees->setItem(nbLines-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(fonction);
    ui->tableWidgetEmployees->setItem(nbLines-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearTableEmployees()
{
    ui->tableWidgetEmployees->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexEmployeeSelectionTable()
{
    QModelIndexList liste = ui->tableWidgetEmployees->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int ind = index.row();
    return ind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Clients (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addTupleTableClients(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char lastName[40];
    strcpy(lastName,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char firstName[40];
    strcpy(firstName,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char gsm[40];
    strcpy(gsm,tmp);

    // Ajout possible
    int nbLines = ui->tableWidgetClients->rowCount();
    nbLines++;
    ui->tableWidgetClients->setRowCount(nbLines);
    ui->tableWidgetClients->setRowHeight(nbLines-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetClients->setItem(nbLines-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(lastName);
    ui->tableWidgetClients->setItem(nbLines-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(firstName);
    ui->tableWidgetClients->setItem(nbLines-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(gsm);
    ui->tableWidgetClients->setItem(nbLines-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearTableClients()
{
    ui->tableWidgetClients->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexClientSelectionTable()
{
    QModelIndexList liste = ui->tableWidgetClients->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int ind = index.row();
    return ind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Contrats (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::addTupleTableContracts(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char seller[40];
    strcpy(seller,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char client[40];
    strcpy(client,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char car[40];
    strcpy(car,tmp);

    // Ajout possible
    int nbLines = ui->tableWidgetContracts->rowCount();
    nbLines++;
    ui->tableWidgetContracts->setRowCount(nbLines);
    ui->tableWidgetContracts->setRowHeight(nbLines-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetContracts->setItem(nbLines-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(seller);
    ui->tableWidgetContracts->setItem(nbLines-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(client);
    ui->tableWidgetContracts->setItem(nbLines-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(car);
    ui->tableWidgetContracts->setItem(nbLines-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::clearTableContracts()
{
    ui->tableWidgetContracts->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndexContractSelectionTable()
{
    QModelIndexList liste = ui->tableWidgetContracts->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int ind = index.row();
    return ind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogMessage(const char* title,const char* message)
{
   QMessageBox::information(this,title,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogError(const char* title,const char* message)
{
   QMessageBox::critical(this,title,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::dialogPromptText(const char* title,const char* question)
{
    QString chaine = QInputDialog::getText(this,title,question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::dialogPromptInt(const char* title,const char* question)
{
    return QInputDialog::getInt(this,title,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ApplicGarageWindow::dialogPromptFloat(const char* title,const char* question)
{
    return QInputDialog::getDouble(this,title,question);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionQuit_triggered()
{
    // TO DO (étape 12)

    cout << ">>> Clic sur item Quitter <<<" << endl;
    Garage::getInstance().save();

    QApplication::exit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::closeEvent(QCloseEvent *event)
{
    // TO DO (étape 12)
    Garage::getInstance().save();

    cout << ">>> Clic sur croix de fenetre <<<" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNewModel_triggered()
{
    // TO DO (étape 9)
    Engine e;

    string modelName = this->dialogPromptText("Nouveau modèle","Nom :");
    if(modelName==""){
        dialogError("Erreur", "Nom invalide");
        return;
    }

    int power = this->dialogPromptInt("Nouveau modèle","Puissance :");
    if(power<=0){
        dialogError("Erreur", "Puissance invalide");
        return;
    }

    int engine = this->dialogPromptInt("Nouveau modèle :","Moteur (0=essence,1=diesel,2=électrique,3=hybride) :");
    switch(engine)
    {
        case 0: 
            e = Petrol;
            break;
        case 1:
            e = Diesel;
            break;
        case 2:
            e = Electric;
            break;
        case 3:
            e = Hybrid;
            break;
        default:
            dialogError("Erreur", "Num moteur invalide");
            return;
    }


    float basePrice = this->dialogPromptFloat("Nouveau modèle","Prix de base :");
    if(basePrice<=0.0){
        dialogError("Erreur", "Prix de base invalide");
        return;
    }

    string image = this->dialogPromptText("Nouveau modèle","Nom du fichier de l'image :");
    if(image==""){
        dialogError("Erreur", "Image invalide");
        return;
    }


    cout << ">>> Clic sur item NewModel <<<" << endl;
    cout << "modelName = " << modelName << endl;
    cout << "power = " << power << endl;
    cout << "engine = " << engine << endl;
    cout << "basePrice = " << basePrice << endl;
    cout << "image = " << image << endl;

    Model m(modelName.c_str(), power, e, basePrice);
    m.setImage(image);
    Garage::getInstance().addModel(m);

    addAvailableModel(modelName, basePrice);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNewOption_triggered()
{
    // TO DO (étape 9)
    int i;
    string code = this->dialogPromptText("Nouvelle option","Code :");
    if(code==""){
        dialogError("Erreur", "Code invalide");
        return;
    }

    string label = this->dialogPromptText("Nouvelle option","Intitule :");
    if(label==""){
        dialogError("Erreur", "Intitulé invalide");
        return;
    }
    float price = this->dialogPromptFloat("Nouvelle option","Prix :");
    if(price<=0.0){
        dialogError("Erreur", "Prix invalide");
        return;
    }

    cout << ">>> Clic sur item NewOption <<<" << endl;
    cout << "code = " << code << endl;
    cout << "label = " << label << endl;
    cout << "price = " << price << endl;

    Car& currentProject=Garage::getCurrentProject(); 
    
    for(i=0; i<5; i++){
        Option *o=currentProject[i]; 
        if(o!=nullptr && o->getCode()==code){
            dialogError("Erreur", "Option avec ce code existe déjà");
            return;
        }
    }

    try{
        Option o(code, label, price);
        Garage::getInstance().addOption(o);

        addAvailableOption(label, price);

    }catch(const OptionException &e){
        dialogError("Erreur", e.getMessage().c_str());
        return;
    }
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAddEmployee_triggered()
{
    // TO DO (étape 11)
    int i;
    std::string role;

    string lastName = this->dialogPromptText("Nouvel employé","Nom :");
    if(lastName==""){
        dialogError("Erreur", "Nom invalide");
        return;
    }

    string firstName = this->dialogPromptText("Nouvel employé","Prénom :");
    if(firstName==""){
        dialogError("Erreur", "Prénom invalide");
        return;
    }

    string login = this->dialogPromptText("Nouvel employé","Login :");
    if(login==""){
        dialogError("Erreur", "Login invalide");
        return;
    }

    int type = this->dialogPromptInt("Nouvel employé","Fonction (0=administratif,1=vendeur) :");

    switch (type) {
    case 0:
        role="administratif";
        break;
    case 1:
        role="vendeur";
        break;
    default:
        dialogError("Erreur", "Fonction invalide (0=administratif, 1=vendeur)");
        return;
    }

    cout << ">>> Clic sur item AddEmployee <<<" << endl;
    cout << "lastName = " << lastName << endl;
    cout << "firstName = " << firstName << endl;
    cout << "login = " << login << endl;
    cout << "type = " << type << endl;


    Garage &g=Garage::getInstance();
    g.addEmployee(lastName, firstName, login, role);

    MAJtableEmployes();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionDeleteEmployeeById_triggered()
{
    // TO DO (étape 11)
    cout << ">>> Clic sur item DeleteEmployeeById <<<" << endl;

    int id = dialogPromptInt("Supprimer employé","Id :");


    Garage&g=Garage::getInstance();
    g.deleteEmployeeById(id);

    MAJtableEmployes();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionDeleteEmployeeByIndex_triggered()
{
    // TO DO (étape 11)
    int indice;

    cout << ">>> Clic sur item DeleteEmployeeByIndex <<<" << endl;
    indice=getIndexEmployeeSelectionTable();

    if(indice==-1){
        dialogError("Erreur", "Aucun employé sélectionné");
        return;
    }

    Garage &g=Garage::getInstance();
    g.deleteEmployeeByIndex(indice);

    MAJtableEmployes();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAddClient_triggered()
{
    // TO DO (étape 11)
    cout << ">>> Clic sur item AddClient <<<" << endl;
    int i;

    string lastName = this->dialogPromptText("Nouveau client","Nom :");
    if(lastName==""){
        dialogError("Erreur", "Nom invalide");
        return;
    }

    string firstName = this->dialogPromptText("Nouveau client","Prénom :");
    if(firstName==""){
        dialogError("Erreur", "Prénom invalide");
        return;
    }

    string gsm = this->dialogPromptText("Nouveau client","Gsm :");
    if(gsm==""){
        dialogError("Erreur", "GSM invalide");
        return;
    }


    cout << ">>> Clic sur item AddEmployee <<<" << endl;
    cout << "lastName = " << lastName << endl;
    cout << "firstName = " << firstName << endl;


    Garage &g=Garage::getInstance();
    g.addClient(lastName, firstName, gsm);

    MAJtableClients();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionDeleteClientById_triggered()
{
    // TO DO (étape 11)
    cout << ">>> Clic sur item DeleteClientById <<<" << endl;

    int id = this->dialogPromptInt("Supprimer client","Id :");


    Garage&g=Garage::getInstance();
    g.deleteClientById(id);

    MAJtableClients();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionDeleteClientByIndex_triggered()
{
    // TO DO (étape 11)
    int indice;
    cout << ">>> Clic sur item DeleteClientByIndex <<<" << endl;

    indice=getIndexClientSelectionTable();

    if(indice==-1){
        dialogError("Erreur", "Aucun client selectionné");
        return;
    }

    Garage &g=Garage::getInstance();
    g.deleteClientByIndex(indice);

    MAJtableClients();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogin_triggered()
{
    // TO DO (étape 11)
    
    cout << ">>> Clic sur item Login <<<" << endl;
    string login = this->dialogPromptText("Entrer en session","Login :");

    if(login==""){
        dialogError("Erreur", "Login invalide");
        return;
    }

    Garage &g=Garage::getInstance();
    Employee e=g.findEmployeeLogin(login);
   

    if(e.getLogin()=="")
    {
        dialogError("Erreur", "Login inexistant");
        return;
    }
    
    try{
        string trouvemdp=e.getPassword();

        string mdp=dialogPromptText("Entrer en session", "Mot de passe :");
        if(mdp==""){
            dialogError("Erreur", "Mot de passe invalide");
            return;
        }


        if(mdp!=trouvemdp){
            dialogError("Erreur", "Mot de passe incorrect");
            return;
        }
    }catch(const PasswordException &pe){
        dialogError("Erreur", "Aucun mot de passe enregistré. Encodez un nouveau");
        string mdp2=dialogPromptText("Entrer en session", "Nouveau mot de passe :");

        if(mdp2=="") return;

        try{
            e.setPassword(mdp2);
        }catch(const PasswordException &pe2){
            pe2.display();
            dialogError("Erreur", pe2.getMessage().c_str());
            return;
        }

        g.updateEmployee(e);
        dialogMessage("Information", "Mot de passe enregistré. Veuillez vous reconnecter.");
        return;

    
    }

    Garage::idLoggedEmployee=e.getId();
    if(e.getRole()=="administratif"){
        setRole(1);
    }else{
        setRole(2);
    }

    setTitle(e.getLastName());
    MAJtableEmployes();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogout_triggered()
{
    // TO DO (étape 11)
    cout << ">>> Clic sur item Logout <<<" << endl;
    setTitle("Application Garage");
    setRole(0);
    clearTableEmployees();   
    clearTableClients(); 
    clearTableOption();
    clearTableContracts();
    setPrice(0.0);
    Garage::resetCurrentProject();
    MAJprojetEnCours();



    Garage::idLoggedEmployee=-1;


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionResetPassword_triggered()
{
    // TO DO (étape 11)
    cout << ">>> clic sur item ResetPassword <<<" << endl;

    if(Garage::idLoggedEmployee==-1){
        dialogError("Erreur", "Aucun employé connecté");
        return;
    }

    Garage &g=Garage::getInstance();

    Employee e=g.findEmployeeById(Garage::idLoggedEmployee);
    if(e.getLogin()==""){
        dialogError("Erreur", "Employé introuvable");
        return;
    }

    e.resetPassword();
    g.updateEmployee(e);
    dialogMessage("Information", "Mot de passe réinitialisé");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSelectModel_clicked()
{
    // TO DO (étape 9)
    cout << ">>> Clic sur bouton SelectModel <<<" << endl;


    int indice, engine=0, i, ligne;

    indice=this->getIndexModelSelectionCombobox();

    if(indice==-1){
        dialogError("Erreur", "Aucun modèle selectionné");
        return;
    }

    Model m=Garage::getInstance().getModel(indice); 
    Garage::getCurrentProject().setModel(m);

    MAJprojetEnCours();
   


    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonAddOption_clicked()
{
    // TO DO (étape 9)
    cout << ">>> Clic sur bouton AddOption <<<" << endl;

    int indice, i=0;
    indice=getIndexOptionSelectionCombobox();

    if(indice==-1){
        dialogError("Erreur", "Aucune option selectionnée");
        return;
    }
    
    try{
        Option o=Garage::getInstance().getOption(indice);
     
        Garage::getCurrentProject().addOption(o);

        MAJtableOptions();

        setPrice(Garage::getCurrentProject().getPrice());

    }catch(const OptionException &e){
        dialogError("Erreur", e.getMessage().c_str());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonRemoveOption_clicked()
{
    // TO DO (étape 9)
    cout << ">>> Clic sur bouton RemoveOption <<<" << endl;
    int indice, i;
    indice=getIndexOptionSelectionTable();

    if(indice==-1){
        dialogError("Erreur", "Aucune option selectionnée");
        return;
    }

    try{
        Car &currentProject=Garage::getCurrentProject();

        Option *o=currentProject[indice];
        currentProject.removeOption(o->getCode());

        MAJprojetEnCours();

        

    }catch(const OptionException &e){
        dialogError("Erreur", e.getMessage().c_str());
    }
   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonReduction_clicked()
{
    // TO DO (étape 9()
    cout << ">>> Clic sur bouton Reduction <<<" << endl;
    int indice, i;

    indice=getIndexOptionSelectionTable();

    if(indice==-1){
        dialogError("Erreur", "Aucune option sélectionnée");
        return;
    }

    try{
        Car &currentProject=Garage::getCurrentProject();
        Option *o=currentProject[indice];
        (*o)--;

        MAJtableOptions();
        MAJprojetEnCours();
    }catch(const OptionException &e){
        dialogError("Erreur", e.getMessage().c_str());
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSaveProject_clicked()
{
    // TO DO (étape 9)
    cout << ">>> Clic sur bouton SaveProject <<<" << endl;

    std::string projectName;

    projectName=getCurrentProjectName();

    Car &currentProject=Garage::getCurrentProject();
    currentProject.setName(projectName);

    currentProject.save();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonOpenProject_clicked()
{
    // TO DO (étape 9)
    int i;
    int engine = 0;

    cout << ">>> Clic sur bouton OpenProject <<<" << endl;

    std::string projectName;

    projectName=getCurrentProjectName();

    Car &currentProject=Garage::getCurrentProject();

    
    currentProject.load(projectName);
    currentProject.setName(projectName); 


    MAJprojetEnCours();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNewProject_clicked()
{
    // TO DO (étape 9)
    cout << ">>> Clic sur bouton NewProject <<<" << endl;

    Garage::resetCurrentProject();


    MAJprojetEnCours();
    
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNewContract_clicked()
{
    // TO DO (étape 13)
    cout << ">>> Clic sur bouton NewContract <<<" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonDeleteContract_clicked()
{
    // TO DO (étape 13)
    cout << ">>> Clic sur bouton DeleteContract <<<" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonShowCar_clicked()
{
    // TO DO (étape 13)
    cout << ">>> Clic sur bouton ShowCar <<<" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Mes méthodes à moi /////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::MAJtableOptions()
{
    int i;
    Car &c=Garage::getCurrentProject();

    for(i=0;i<5;i++)
    {
        Option *o=c[i];
        if (o != NULL){
            setTableOption(i, o->getCode(), o->getLabel(), o->getPrice());
        }
        else{
            setTableOption(i);
        } 
    }
}

void ApplicGarageWindow::MAJprojetEnCours(){

    int engine=0;

    Car &c=Garage::getCurrentProject();
    Model m=c.getModel();

    switch(m.getEngine()){
        case Petrol:
            engine=0;
            break;
        case Diesel:
            engine=1;
            break;
        case Electric:
            engine=2;
            break;
        case Hybrid:
            engine=3;
            break;
    }

    setCurrentProjectName(c.getName());

    setModel(m.getName(), m.getPower(), engine, m.getBasePrice(), m.getImage());
 
    MAJtableOptions();
    setPrice(c.getPrice());
}

void ApplicGarageWindow::MAJtableEmployes()
{
    int i;
    clearTableEmployees();
    Garage&g=Garage::getInstance();

    for(i=0; i<g.getNbEmployees(); i++){
        Employee e=g.findEmployeeByIndex(i);
        addTupleTableEmployees(e.tuple());
    }

}

void ApplicGarageWindow::MAJtableClients()
{
    int i;
    clearTableClients();
    Garage&g=Garage::getInstance();

    for(i=0; i<g.getNbClients(); i++){
        Client c=g.findClientByIndex(i);
        addTupleTableClients(c.tuple());
    }
}
/*
void ApplicGarageWindow::MAJtableContrats()
{
    videTableContrats();
    Vecteur<Contrat> contrats = Garage::getInstance().getContrats();
    Iterateur<Contrat> it(contrats);
    while (!it.end())
    {
        ajouteTupleTableContrats(((Contrat)it).Tuple());
        it++;
    }
}*/


