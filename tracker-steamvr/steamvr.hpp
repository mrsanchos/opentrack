#pragma once
#include "api/plugin-api.hpp"
#include "ui_dialog.h"
#include "compat/util.hpp"
#include "options/options.hpp"

#include "compat/euler.hpp"

#include <openvr.h>

#include <atomic>
#include <cmath>
#include <memory>

#include <QString>
#include <QMutex>
#include <QMutexLocker>

using namespace options;

struct settings : opts
{
    value<int> order;
    settings() :
        opts("valve-steamvr"),
        order(b, "rotation-order", 0)
    {}
};

class steamvr : public ITracker
{
public:
    steamvr();
    ~steamvr() override;
    void start_tracker(QFrame *) override;
    void data(double *data) override;
private:

    using error_t = vr::EVRInitError;
    using vr_t = vr::IVRSystem*;

    vr_t vr;

    settings s;

    using rmat = euler::rmat;
    using euler_t = euler::euler_t;

    static void vr_deleter();
    static vr_t vr_init(error_t& error);
    static QString strerror(error_t error);
};

class steamvr_dialog : public ITrackerDialog
{
    Q_OBJECT
public:
    steamvr_dialog();

    void register_tracker(ITracker *) override;
    void unregister_tracker() override;
private:
    Ui::dialog ui;
    settings s;
    vr::IVRSystem* vr;
private slots:
    void doOK();
    void doCancel();
};

class steamvr_metadata : public Metadata
{
public:
    QString name() { return QString(QCoreApplication::translate("steamvr_metadata", "Valve SteamVR")); }
    QIcon icon() { return QIcon(":/images/rift_tiny.png"); }
};

