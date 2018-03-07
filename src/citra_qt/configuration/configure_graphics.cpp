// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "citra_qt/configuration/configure_graphics.h"
#include "core/core.h"
#include "core/settings.h"
#include "ui_configure_graphics.h"

ConfigureGraphics::ConfigureGraphics(QWidget* parent)
    : QWidget(parent), ui(new Ui::ConfigureGraphics) {

    ui->setupUi(this);
    this->setConfiguration();

    ui->toggle_vsync->setEnabled(!Core::System::GetInstance().IsPoweredOn());
    ui->frame_limit->setEnabled(Settings::values.use_frame_limit);
    connect(ui->toggle_frame_limit, &QCheckBox::stateChanged, ui->frame_limit,
            &QSpinBox::setEnabled);

    ui->layoutBox->setEnabled(!Settings::values.custom_layout);

    ui->tex_cache_size->setEnabled(!Core::System::GetInstance().IsPoweredOn());
    ui->tex_scale_mode->setEnabled(!Core::System::GetInstance().IsPoweredOn());
    ui->tex_scale_factor->setEnabled(!Core::System::GetInstance().IsPoweredOn());
    ui->tex_scale_depos->setEnabled(!Core::System::GetInstance().IsPoweredOn());
}

ConfigureGraphics::~ConfigureGraphics() {}

void ConfigureGraphics::setConfiguration() {
    ui->toggle_hw_renderer->setChecked(Settings::values.use_hw_renderer);
    ui->resolution_factor_combobox->setEnabled(Settings::values.use_hw_renderer);
    ui->toggle_shader_jit->setChecked(Settings::values.use_shader_jit);
    ui->resolution_factor_combobox->setCurrentIndex(Settings::values.resolution_factor);
    ui->toggle_vsync->setChecked(Settings::values.use_vsync);
    ui->toggle_frame_limit->setChecked(Settings::values.use_frame_limit);
    ui->frame_limit->setValue(Settings::values.frame_limit);
    ui->layout_combobox->setCurrentIndex(static_cast<int>(Settings::values.layout_option));
    ui->swap_screen->setChecked(Settings::values.swap_screen);

    ui->tex_cache_size->setValue(Settings::values.tex_cache_size);
    ui->tex_scale_mode->setCurrentIndex(Settings::values.tex_scale_mode);
    ui->tex_scale_factor->setValue(Settings::values.tex_scale_factor);
    ui->tex_scale_depos->setChecked(Settings::values.tex_scale_depos);
    ui->tex_dump->setChecked(Settings::values.tex_dump);
    ui->tex_dump_dir->setText(QString::fromStdString(Settings::values.tex_dump_dir));
    ui->tex_load->setChecked(Settings::values.tex_load);
    ui->tex_load_dir->setText(QString::fromStdString(Settings::values.tex_load_dir));
}

void ConfigureGraphics::applyConfiguration() {
    Settings::values.use_hw_renderer = ui->toggle_hw_renderer->isChecked();
    Settings::values.use_shader_jit = ui->toggle_shader_jit->isChecked();
    Settings::values.resolution_factor =
        static_cast<u16>(ui->resolution_factor_combobox->currentIndex());
    Settings::values.use_vsync = ui->toggle_vsync->isChecked();
    Settings::values.use_frame_limit = ui->toggle_frame_limit->isChecked();
    Settings::values.frame_limit = ui->frame_limit->value();
    Settings::values.layout_option =
        static_cast<Settings::LayoutOption>(ui->layout_combobox->currentIndex());
    Settings::values.swap_screen = ui->swap_screen->isChecked();

    Settings::values.tex_cache_size = ui->tex_cache_size->value();
    Settings::values.tex_scale_mode = ui->tex_scale_mode->currentIndex();
    Settings::values.tex_scale_factor = ui->tex_scale_factor->value();
    Settings::values.tex_scale_depos = ui->tex_scale_depos->isChecked();
    Settings::values.tex_dump = ui->tex_dump->isChecked();
    Settings::values.tex_dump_dir = ui->tex_dump_dir->text().toStdString();
    Settings::values.tex_load = ui->tex_load->isChecked();
    Settings::values.tex_load_dir = ui->tex_load_dir->text().toStdString();
    Settings::Apply();
}

void ConfigureGraphics::retranslateUi() {
    ui->retranslateUi(this);
}
