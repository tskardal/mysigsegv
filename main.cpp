#include <QCoreApplication>
#include <QDebug>
#include <QtSql>

void connect(const QString &connectionName) {
  auto host = "192.168.137.42";
  auto user = "testusr";
  auto pwd = "testusr";
  auto dbName = "testdb";

  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
  db.setHostName(host);
  db.setPort(3306);
  db.setUserName(user);
  db.setPassword(pwd);
  db.setDatabaseName(dbName);
  bool open = db.open();
  if (!open) {
    qDebug() << "Failed to open connection";
    return;
  }

  QSqlQuery q("SHOW VARIABLES LIKE '%version%';", db);
  while (q.next()) {
    qDebug() << q.value(0).toString() << " = " << q.value(1).toString();
  }
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  connect("test");
  QSqlDatabase::removeDatabase("test");
  connect("test");
  QSqlDatabase::removeDatabase("test");

  qDebug() << "Done";

  return a.exec();
}
