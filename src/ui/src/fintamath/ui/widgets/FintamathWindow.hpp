#pragma once

#include "fintamath/ui/models/CalculatorHandler.hpp"
#include "ui/ui_FintamathMainWindow.h"

namespace fintamath {
  class FintamathMainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit FintamathMainWindow(QWidget *parent = nullptr);
    ~FintamathMainWindow() override;

  private slots:
    void onSolved(const QString &str) const;
    void on_input_textChanged();

  signals:
    void startCalculation(const QString &str);
    void terminateCalculation();

  private:
    QSharedPointer<Ui::FintamathMainWindow> ui = QSharedPointer<Ui::FintamathMainWindow>(new Ui::FintamathMainWindow);
    QSharedPointer<CalculatorHandler> calculatorHandler = QSharedPointer<CalculatorHandler>(new CalculatorHandler);
  };
}