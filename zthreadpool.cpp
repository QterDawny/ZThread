#include "zthreadpool.h"

class ThreadEntry {
public:
    QString name;
    QThread *p;
};

ZThreadPool::ZThreadPool(QObject *parent) :
    QObject(parent)
{
}

ZThreadPool::~ZThreadPool() {
    while(!tList.isEmpty()) {
        delete tList.takeFirst();
    }
}

void ZThreadPool::registerThread(QThread *p, const QString &name) {
    addThread(p, name);
    connect(p, SIGNAL(finished()), SLOT(slot_checkAndRemove()));
}

void ZThreadPool::addThread(QThread *p, const QString &name) {
    ThreadEntry *t = new ThreadEntry();
    t->name = name;
    t->p = p;
    tMutex.lock();
    tList.append(t);
    tMutex.unlock();
}

void ZThreadPool::removeThread(QThread *p) {
    tMutex.lock();
    foreach(ThreadEntry *t, tList) {
        if(t->p == p) {
            tList.removeOne(t);
            delete t;
            break;
        }
    }
    if(tList.size() == 0) {
        emit signal_poolEmpty();
    }
    tMutex.unlock();
}

int ZThreadPool::size() {
    int n = 0;
    tMutex.lock();
    n = tList.size();
    tMutex.unlock();
    return n;
}

void ZThreadPool::slot_remove(QObject *obj) {
    removeThread((QThread *)obj);
}

void ZThreadPool::slot_checkAndRemove() {
    QThread *p = static_cast<QThread*>(sender());
    removeThread(p);
}
