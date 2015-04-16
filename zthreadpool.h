#ifndef ZTHREADPOOL_H
#define ZTHREADPOOL_H

#include <QThread>
#include <QMutex>

class ThreadEntry;
class ZThreadPool : public QObject
{
    Q_OBJECT

    QList<ThreadEntry *> tList;
    QMutex tMutex;

public:
    explicit ZThreadPool(QObject *parent = 0);
    ~ZThreadPool();

    void registerThread(QThread *p, const QString &name);
    void addThread(QThread *p, const QString &name);
    void removeThread(QThread *p);
    int size();

public slots:
    void slot_remove(QObject *obj);
    void slot_checkAndRemove();

signals:
    void signal_poolEmpty();

};

#endif // ZTHREADPOOL_H
