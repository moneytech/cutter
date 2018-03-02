#ifndef JUPYTERCONNECTION_H
#define JUPYTERCONNECTION_H

#ifdef CUTTER_ENABLE_JUPYTER

#include <QProcess>
#include <QMap>

class NestedIPyKernel;

struct _object;
typedef _object PyObject;

struct _ts;
typedef _ts PyThreadState;

class JupyterConnection : public QObject
{
    Q_OBJECT

public:
    static JupyterConnection* getInstance();

    JupyterConnection(QObject *parent = nullptr);
    ~JupyterConnection();

    void start();
    QString getUrl();

    long startNestedIPyKernel(const QStringList &argv);
    NestedIPyKernel *getNestedIPyKernel(long id);
    QVariant pollNestedIPyKernel(long id);

signals:
    void urlReceived(const QString &url);
    void creationFailed();

private:
    PyObject *cutterJupyterModule = nullptr;
    PyObject *cutterNotebookAppInstance = nullptr;

    PyThreadState *pyThreadState = nullptr;

    QMap<long, NestedIPyKernel *> kernels;
    long nextKernelId = 1;

    void initPython();
    void createCutterJupyterModule();
};


#define Jupyter() (JupyterConnection::getInstance())

#endif

#endif //JUPYTERCONNECTION_H
