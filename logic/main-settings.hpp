/* Copyright (c) 2015, Stanislaw Halik <sthalik@misaki.pl>

 * Permission to use, copy, modify, and/or distribute this
 * software for any purpose with or without fee is hereby granted,
 * provided that the above copyright notice and this permission
 * notice appear in all copies.
 */

#pragma once

#include <QString>
#include "options/options.hpp"
#include "api/plugin-api.hpp"

using namespace options;

#include "export.hpp"

namespace axis_clamp_opts
{

} // ns axis-clamp-opts

struct axis_opts final
{
    enum max_clamp
    {
        r180 = 180,
        r90 = 90,
        r60 = 60,
        r45 = 45,
        r30 = 30,
        r25 = 25,
        r20 = 20,
        r15 = 15,
        r10 = 10,

        t30 = 30,
        t20 = 20,
        t15 = 15,
        t10 = 10,
    };

    // note, these two bundles can be the same value with no issues
    bundle b_settings_window, b_mapping_window;
    value<double> zero;
    value<int> src;
    value<bool> invert, altp;
    value<max_clamp> clamp;
    axis_opts(bundle b_settings_window, bundle b_mapping_window, QString pfx, Axis idx) :
        b_settings_window(b_settings_window),
        b_mapping_window(b_mapping_window),
        zero(b_settings_window, n(pfx, "zero-pos"), 0),
        src(b_settings_window, n(pfx, "source-index"), idx),
        invert(b_settings_window, n(pfx, "invert-sign"), false),
        altp(b_mapping_window, n(pfx, "alt-axis-sign"), false),
        clamp(b_mapping_window, n(pfx, "max-value"), idx >= Yaw ? r180 : t30)
    {}
private:
    static inline QString n(QString pfx, QString name)
    {
        return QString("%1-%2").arg(pfx, name);
    }
};

struct key_opts
{
    value<QString> keycode, guid;
    value<int> button;

    key_opts(bundle b, const QString& name) :
        keycode(b, QString("keycode-%1").arg(name), ""),
        guid(b, QString("guid-%1").arg(name), ""),
        button(b, QString("button-%1").arg(name), -1)
    {}
};

struct module_settings
{
    bundle b;
    value<QString> tracker_dll, filter_dll, protocol_dll;
    module_settings() :
        b(make_bundle("modules")),
        tracker_dll(b, "tracker-dll", "PointTracker 1.1"),
        filter_dll(b, "filter-dll", "Accela"),
        protocol_dll(b, "protocol-dll", "freetrack 2.0 Enhanced")
    {
    }
};

struct main_settings
{
    bundle b, b_map;
    axis_opts a_x, a_y, a_z;
    axis_opts a_yaw, a_pitch, a_roll;
    value<bool> tcomp_p, tcomp_disable_tx, tcomp_disable_ty, tcomp_disable_tz;
    value<bool> tcomp_disable_src_yaw, tcomp_disable_src_pitch, tcomp_disable_src_roll;
    value<bool> tray_enabled, tray_start;
    value<int> camera_yaw, camera_pitch, camera_roll;
    value<bool> use_camera_offset_from_centering;
    value<bool> center_at_startup;
    value<int> center_method;
    value<int> neck_y, neck_z;
    value<bool> neck_enable;
    key_opts key_start_tracking1, key_start_tracking2;
    key_opts key_stop_tracking1, key_stop_tracking2;
    key_opts key_toggle_tracking1, key_toggle_tracking2;
    key_opts key_restart_tracking1, key_restart_tracking2;
    key_opts key_center1, key_center2;
    key_opts key_toggle1, key_toggle2;
    key_opts key_zero1, key_zero2;
    key_opts key_toggle_press1, key_toggle_press2;
    key_opts key_zero_press1, key_zero_press2;
    value<bool> tracklogging_enabled;
    value<QString> tracklogging_filename;
    main_settings() :
        b(make_bundle("opentrack-ui")),
        b_map(make_bundle("opentrack-mappings")),
        a_x(b, b_map, "x", TX),
        a_y(b, b_map, "y", TY),
        a_z(b, b_map, "z", TZ),
        a_yaw(b, b_map, "yaw", Yaw),
        a_pitch(b, b_map, "pitch", Pitch),
        a_roll(b, b_map, "roll", Roll),
        tcomp_p(b, "compensate-translation", false),
        tcomp_disable_tx(b, "compensate-translation-disable-x-axis", false),
        tcomp_disable_ty(b, "compensate-translation-disable-y-axis", false),
        tcomp_disable_tz(b, "compensate-translation-disable-z-axis", false),
        tcomp_disable_src_yaw(b, "compensate-translation-disable-source-yaw", false),
        tcomp_disable_src_pitch(b, "compensate-translation-disable-source-pitch", false),
        tcomp_disable_src_roll(b, "compensate-translation-disable-source-roll", false),
        tray_enabled(b, "use-system-tray", false),
        tray_start(b, "start-in-tray", false),
        camera_yaw(b, "camera-yaw", 0),
        camera_pitch(b, "camera-pitch", 0),
        camera_roll(b, "camera-roll", 0),
        use_camera_offset_from_centering(b, "use-camera-offset-from-centering", false),
        center_at_startup(b, "center-at-startup", true),
        center_method(b, "centering-method", 1),
        neck_y(b, "neck-height", 0),
        neck_z(b, "neck-depth", 0),
        neck_enable(b, "neck-enable", false),
        key_start_tracking1(b, "start-tracking"),
        key_start_tracking2(b, "start-tracking-alt"),
        key_stop_tracking1(b, "stop-tracking"),
        key_stop_tracking2(b, "stop-tracking-alt"),
        key_toggle_tracking1(b, "toggle-tracking"),
        key_toggle_tracking2(b, "toggle-tracking-alt"),
        key_restart_tracking1(b, "restart-tracking"),
        key_restart_tracking2(b, "restart-tracking-alt"),
        key_center1(b, "center"),
        key_center2(b, "center-alt"),
        key_toggle1(b, "toggle"),
        key_toggle2(b, "toggle-alt"),
        key_zero1(b, "zero"),
        key_zero2(b, "zero-alt"),
        key_toggle_press1(b, "toggle-press"),
        key_toggle_press2(b, "toggle-press-alt"),
        key_zero_press1(b, "zero-press"),
        key_zero_press2(b, "zero-press-alt"),
        tracklogging_enabled(b, "tracklogging-enabled", false),
        tracklogging_filename(b, "tracklogging-filename", QString())
    {
    }
};
