#include "allhiveform.h"

AllHiveForm::AllHiveForm(QWidget *parent) : QWidget(parent) {

    setStyleSheet("QWidget { background-color: #000000; }"
                  "QLineEdit { background-color: #000000; color: #FFA500; }"
                  "QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }"
                  "QPushButton:hover { background-color: #FFD700; }");

    mainLayout = new QVBoxLayout(this);

    welcomeLabel = new QLabel("Hives", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFA500;");

    tableView = new QTableView(this);
    model = new QSqlTableModel(this);
    tableView->setModel(model);
    tableView->setStyleSheet("QTableView { background-color: #000000; color: #FFA500; }"
                             "QTableView::item { background-color: #000000; color: #FFA500; }"
                             "QHeaderView::section { background-color: #FFA500; color: #000000; }");

    buttonLayout = new QVBoxLayout();

    editDataButton = new QPushButton("Save Data", this);
    editDataButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    editDataButton->setFixedWidth(200);

    addDataButton = new QPushButton("Add Data", this);
    addDataButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    addDataButton->setFixedWidth(200);

    deleteDataButton = new QPushButton("Delete Data", this);
    deleteDataButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    deleteDataButton->setFixedWidth(200);

    backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("background-color: #FFA500; color: #000000; border: 1px solid #000000;");
    backButton->setFixedWidth(200);

    buttonLayout->addWidget(editDataButton);
    buttonLayout->addWidget(addDataButton);
    buttonLayout->addWidget(deleteDataButton);
    buttonLayout->addWidget(backButton);

    mainLayout->addWidget(welcomeLabel);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    connect(editDataButton, &QPushButton::clicked, this, &AllHiveForm::onEditButtonClicked);
    connect(addDataButton, &QPushButton::clicked, this, &AllHiveForm::onAddButtonClicked);
    connect(deleteDataButton, &QPushButton::clicked, this, &AllHiveForm::onDeleteButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &AllHiveForm::onBackButtonClicked);

    loadHivesData();

    setLayout(mainLayout);
    setWindowTitle("Hives");
    resize(800, 600);
}

void AllHiveForm::closeEvent(QCloseEvent *event) {
    event->accept();
}

AllHiveForm::~AllHiveForm() {
    delete backButton;
    delete editDataButton;
    delete addDataButton;
    delete deleteDataButton;
    delete buttonLayout;
    delete welcomeLabel;
    delete tableView;
    delete mainLayout;
    delete model;
}

void AllHiveForm::onEditButtonClicked() {
    if (model->isDirty()) {
        if (model->submitAll()) {
            showMessageBox("Success", "Data saved successfully!", QMessageBox::Information);
        } else {
            showMessageBox("Error", "Failed to save data!", QMessageBox::Warning);
        }
    } else {
        showMessageBox("Info", "No changes to save.", QMessageBox::Information);
    }
}

void AllHiveForm::onBackButtonClicked() {
    this->close();
}

void AllHiveForm::onAddButtonClicked() {
    QSqlQuery query = DatabaseManager::getInstance().executeQuery("SELECT MAX(ID_Hive) FROM Hives");
    if (query.next()) {
        int maxId = query.value(0).toInt();
        int newId = maxId + 1;

        int row = model->rowCount();
        model->insertRow(row);
        model->setData(model->index(row, 0), newId);
        tableView->setCurrentIndex(model->index(row, 0));
    } else {
        showMessageBox("Error", "Failed to get the maximum ID_Hive!", QMessageBox::Warning);
    }
}

void AllHiveForm::onDeleteButtonClicked() {
    QModelIndex index = tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
        model->submitAll();
    } else {
        showMessageBox("Error", "No row selected!", QMessageBox::Warning);
    }
}

void AllHiveForm::loadHivesData() {
    model->setTable("Hives");
    model->select();

    if (model->rowCount() == 0) {
        showMessageBox("Error", "No hives found!", QMessageBox::Warning);
    }
}

void AllHiveForm::showMessageBox(const QString &title, const QString &message, QMessageBox::Icon icon) {
    QMessageBox messageBox;
    messageBox.setIcon(icon);
    messageBox.setText(message);
    messageBox.setWindowTitle(title);
    messageBox.setStyleSheet("QMessageBox { background-color: #000000; color: #FFA500; }"
                             "QMessageBox QLabel { color: #FFA500; }"
                             "QMessageBox QPushButton { background-color: #FFA500; color: #000000; border: 1px solid #000000; }");
    messageBox.exec();
}
