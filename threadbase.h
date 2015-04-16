#ifndef THREADBASE_H
#define THREADBASE_H

#include <QThread>

template <class T>
class ThreadBase : public QThread {
    typedef int (T::*Func) (void *p, void *q);
    T *parent;
    Func func;  // Func 里不能直接更新UI，需要发信号SINGAL，与对应线程槽连接

public:
    int *ret;
    void *p;
    void *q;

    // p q ??
    ThreadBase(T* parent, Func func)
        : ret(NULL), p(NULL), q(NULL) {
        this->parent = parent;
        this->func = func;
        connect(this, SIGNAL(finished()), SLOT(deleteLater()));
    }

    void start(void *p, void *q, int *ret) {
        this->p = p;
        this->q = q;
        this->ret = ret;
        QThread::start();
    }

    void run() {
        int r = (parent->*func) (p, q);
        if(ret != NULL) {
            *ret = r;
        }
    }
};

#endif // THREADBASE_H
