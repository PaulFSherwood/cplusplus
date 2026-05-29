#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>

QFrame* makeCard(const QString& title, const QString& value, const QString& change)
{
   QFrame* card = new QFrame;
   card->setObjectName("card");

   auto* layout = new QVBoxLayout(card);

   QLabel* titleLabel = new QLabel(title);
   titleLabel->setObjectName("cardTitle");

   QLabel* valueLabel = new QLabel(value);
   valueLabel->setObjectName("cardValue");

   QLabel* changeLabel = new QLabel(change);
   changeLabel->setObjectName("positiveText");

   layout->addWidget(titleLabel);
   layout->addWidget(valueLabel);
   layout->addWidget(changeLabel);
   layout->addStretch();

   return card;
}

QFrame* makePanel(const QString& title)
{
   QFrame* panel = new QFrame;
   panel->setObjectName("panel");

   auto* layout = new QVBoxLayout(panel);

   auto* topRow = new QHBoxLayout;

   QLabel* titleLabel = new QLabel(title);
   titleLabel->setObjectName("panelTitle");

   QPushButton* button = new QPushButton("View Report");
   button->setObjectName("smallButton");

   topRow->addWidget(titleLabel);
   topRow-> addStretch();
   topRow->addWidget(button);

   QLabel* subtitle = new QLabel("Data from 1-12 Apr, 2025");
   subtitle->setObjectName("subtitle");

   QLabel* fakeChart = new QLabel("Chart Area");
   fakeChart->setObjectName("chartPlaceholder");
   fakeChart->setMinimumHeight(180);

   layout->addLayout(topRow);
   layout->addWidget(subtitle);
   layout->addWidget(fakeChart);

   return panel;
}

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QWidget window;
   window.setWindowTitle("Personal Finance Dashboard");
   window.resize(1200, 750);

   auto* root = new QVBoxLayout(&window);
   root->setContentsMargins(24, 24, 24, 24);
   root->setSpacing(18);

   QLabel* title = new QLabel("Personal Finance");
   title->setObjectName("appTitle");
   root->addWidget(title);

   auto* topGrid = new QGridLayout;
   topGrid->setSpacing(18);

   QFrame* expenses = makePanel("Daily Expenses");
   QFrame* summary = makePanel("Summary");

   topGrid->addWidget(expenses, 0, 0, 1, 2);
   topGrid->addWidget(summary, 0, 2, 1, 1);

   root->addLayout(topGrid);

   auto* cardRow = new QHBoxLayout;
   cardRow->setSpacing(18);

   cardRow->addWidget(makeCard("Portfolio value", "$10,284", "^ 26%"));
   cardRow->addWidget(makeCard("Portfolio growth", "$2,500", "^ 12%"));
   cardRow->addWidget(makeCard("Dividends", "$1,200", "^ 5%"));
   cardRow->addWidget(makeCard("Net deposits", "$3,000", "^ 8%"));

   root->addLayout(cardRow);

   auto* bottomGrid = new QGridLayout;
   bottomGrid->setSpacing(18);

   QFrame* tablePanel = new QFrame;
   tablePanel->setObjectName("panel");

   auto* tableLayout = new QVBoxLayout(tablePanel);

   QLabel* tableTitle = new QLabel("Daily Expenses");
   tableTitle->setObjectName("panelTitle");

   QTableWidget* table = new QTableWidget(5, 5);
   table->setHorizontalHeaderLabels({"Name", "Company", "Location", "Domain", "Status"});

   QStringList names = {"James Anderson", "Mia White", "William Brown", "Emma Davis", "Ethan Harris"};
   QStringList companies = {"Acme Corp", "Globex Inc" "Soylent Corp", "Initech", "Umbrella Corp"};
   QStringList locations = {"New York, USA", "London, UK", "Berlin, Germany", "Paris, France", "Toykyo, Japan"};
   QStringList domains = {"finance", "healthcare", "education", "retail", "finance"};
   QStringList statuses = {"Active", "Inactive", "Pending", "Active", "Inactive"};

   for (int row = 0; row < 5; ++row)
   {
      table->setItem(row, 0, new QTableWidgetItem(names[row]));
      table->setItem(row, 0, new QTableWidgetItem(companies[row]));
      table->setItem(row, 0, new QTableWidgetItem(locations[row]));
      table->setItem(row, 0, new QTableWidgetItem(domains[row]));
      table->setItem(row, 0, new QTableWidgetItem(statuses[row]));
   }

   table->horizontalHeader()->setStretchLastSection(true);
   table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   table->verticalHeader()->setVisible(false);
   table->setShowGrid(false);

   tableLayout->addWidget(tableTitle);
   tableLayout->addWidget(table);

   bottomGrid->addWidget(tablePanel, 0, 0, 1, 2);
   bottomGrid->addWidget(makePanel("Daily Expenses"), 0, 2, 1, 1);

   root->addLayout(bottomGrid);

   window.setStyleSheet(R"(
      QWidget {
         background-color: #171a1f;
         color: #e8e8e8;
         font-family: Segoe UI;
         font-size: 14px;
      }
      
      QLabel#appTitle {
         font-size: 18px;
         font-weight: bold;
         color: #ffffff;
      }
      
      QFrame#panel,
      QFrame#card {
         background-color: #20242b;
         border: 1px solid #323844;
         border-radius: 14px;
      }
      
      QFrame#card {
         min-height: 90px;
      }
         
      QLabel#panelTitle {
         font-size: 18px;
         font-weight: bold;
         color: #ffffff;
         background: transparent;
      }
         
      QLabel#subtitle {
         color: #aab0bb;
         background: transparent;
      }
         
      QLabel#cardTitle {
         color: #b6bbc5;
         font-weight: bold;
         color: #ffffff;
         background: transparent;
      }
         
      QLable#cardValue {
         font-size: 26px;
         font-weight: bold;
         color: #ffffff;
         background: transparent;
      }
         
      QLabel#positiveText {
         color: #39e58c;
         background-color: rgba(57, 229, 140, 35);
         border-radius: 8px;
         padding: 3px 8px;
         max-width: 60px;
      }
         
      QLabel#chartPlaceholder {
         background-color: #181c322;
         border: 1px dashed #3c4350;
         border-radius: 6px;
         color: #626a78;
      }
         
      QPushButton#smallButton {
         background-color: #252b34;
         color: #ffffff;
         border: 1px solid #4a5260;
         border-radius: 8px;
         padding: 6px 12px;
         font-weight: bold;
      }
         
      QPushButton#smallButton:hover {
         background-color: #303846;
         border: 1px solid #5ef0a0;
      }
         
      QPushButton#smallButton:pressed {
         background-color: #1d222a;
      }
         
      QTabelWidget {
         background-color: #20242b;
         border: none;
         gridline-color: #323844;
         selection-background-color: #2f8664;
         selection-color: white;
      }
         
      QTableWidget::item {
         padding: 8px;
         border-bottom: 1px solid #323844;
      }
         
      QTableWidget::item:selected {
         background-color: #20242b;
         color: #cbd0d8;
         border: none;
         border-bottom: 1px solid #3a414d;
         padding: 8px;
         font-weight: bold;
      }
         
      QScrollBar:vertical {
         background: #171a1f;
         width: 10px;
      }
         
      QScrollBar::handle:vertical {
         background: ##3b4350;
         border-radius: 5px;
      }
         
      QScrollBar:handle:vertical:hover {
         background: #4d5667;
      }
   )");

   window.show();
   return app.exec();
}