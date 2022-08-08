/********************************************************************************
** Form generated from reading UI file 'conceptCAbATE.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CONCEPTCABATE_H
#define CONCEPTCABATE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cpu6502_mainwindow
{
public:
    QAction *actionLoad_asm;
    QAction *actionReset_program;
    QAction *actionDebug_mode;
    QAction *actionClear_file;
    QAction *actionRefresh_program;
    QAction *actionHex_mode;
    QWidget *centralwidget;
    QPushButton *ExecuteButton;
    QPlainTextEdit *CpuCommandLine;
    QLabel *label_error_message;
    QGroupBox *DebugModeBox;
    QLabel *label_debug_where_i_am;
    QToolButton *CommandGoRight;
    QLabel *label_2;
    QSpinBox *spinCommandToRemember;
    QToolButton *CommandGoLeft;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QGroupBox *PC_group;
    QLineEdit *PC_value;
    QGroupBox *SP_group;
    QLineEdit *SP_value;
    QGroupBox *ACU_group;
    QLineEdit *ACU_value;
    QGroupBox *IRX_group;
    QLineEdit *IRX_value;
    QGroupBox *IRY_group;
    QLineEdit *IRY_value;
    QGroupBox *PS_group;
    QGroupBox *CarryFlag_Group;
    QLineEdit *CF_value;
    QGroupBox *OverflowFlag_group;
    QLineEdit *OF_value;
    QGroupBox *DecimalMode_group;
    QLineEdit *DM_value;
    QGroupBox *BreakCommand_group;
    QLineEdit *BC_value;
    QGroupBox *ZeroFlag_group;
    QLineEdit *ZF_value;
    QGroupBox *NegativeFlag_group;
    QLineEdit *NF_value;
    QGroupBox *InterruptDisable_group;
    QLineEdit *ID_value;
    QGroupBox *memory_group;
    QGroupBox *MemorySP0;
    QLineEdit *MemorySPEdit0;
    QGroupBox *MemorySP1;
    QLineEdit *MemorySPEdit1;
    QGroupBox *MemorySP2;
    QLineEdit *MemorySPEdit2;
    QGroupBox *MemorySP3;
    QLineEdit *MemorySPEdit3;
    QGroupBox *MemorySP4;
    QLineEdit *MemorySPEdit4;
    QGroupBox *MemorySP5;
    QLineEdit *MemorySPEdit5;
    QGroupBox *MemoryStart0;
    QLineEdit *MemoryStartEdit0;
    QGroupBox *MemoryStart1;
    QLineEdit *MemoryStartEdit1;
    QGroupBox *MemoryStart5;
    QLineEdit *MemoryStartEdit5;
    QGroupBox *MemoryStart3;
    QLineEdit *MemoryStartEdit3;
    QGroupBox *MemoryStart4;
    QLineEdit *MemoryStartEdit4;
    QGroupBox *MemoryStart2;
    QLineEdit *MemoryStartEdit2;
    QLabel *label_5;
    QLineEdit *ShowMemoryStartAt;
    QGroupBox *LoadASM_group;
    QPushButton *ScanASM;
    QPushButton *LoadASM;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *cpu6502_mainwindow)
    {
        if (cpu6502_mainwindow->objectName().isEmpty())
            cpu6502_mainwindow->setObjectName(QString::fromUtf8("cpu6502_mainwindow"));
        cpu6502_mainwindow->setWindowModality(Qt::ApplicationModal);
        cpu6502_mainwindow->setEnabled(true);
        cpu6502_mainwindow->resize(850, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(cpu6502_mainwindow->sizePolicy().hasHeightForWidth());
        cpu6502_mainwindow->setSizePolicy(sizePolicy);
        cpu6502_mainwindow->setMinimumSize(QSize(850, 600));
        cpu6502_mainwindow->setMaximumSize(QSize(850, 600));
        cpu6502_mainwindow->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8("images/cpu-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        cpu6502_mainwindow->setWindowIcon(icon);
        actionLoad_asm = new QAction(cpu6502_mainwindow);
        actionLoad_asm->setObjectName(QString::fromUtf8("actionLoad_asm"));
        actionReset_program = new QAction(cpu6502_mainwindow);
        actionReset_program->setObjectName(QString::fromUtf8("actionReset_program"));
        actionDebug_mode = new QAction(cpu6502_mainwindow);
        actionDebug_mode->setObjectName(QString::fromUtf8("actionDebug_mode"));
        actionDebug_mode->setCheckable(true);
        actionClear_file = new QAction(cpu6502_mainwindow);
        actionClear_file->setObjectName(QString::fromUtf8("actionClear_file"));
        actionRefresh_program = new QAction(cpu6502_mainwindow);
        actionRefresh_program->setObjectName(QString::fromUtf8("actionRefresh_program"));
        actionHex_mode = new QAction(cpu6502_mainwindow);
        actionHex_mode->setObjectName(QString::fromUtf8("actionHex_mode"));
        actionHex_mode->setCheckable(true);
        centralwidget = new QWidget(cpu6502_mainwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        ExecuteButton = new QPushButton(centralwidget);
        ExecuteButton->setObjectName(QString::fromUtf8("ExecuteButton"));
        ExecuteButton->setGeometry(QRect(10, 510, 831, 41));
        CpuCommandLine = new QPlainTextEdit(centralwidget);
        CpuCommandLine->setObjectName(QString::fromUtf8("CpuCommandLine"));
        CpuCommandLine->setGeometry(QRect(10, 450, 831, 41));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(CpuCommandLine->sizePolicy().hasHeightForWidth());
        CpuCommandLine->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        CpuCommandLine->setFont(font);
        CpuCommandLine->setInputMethodHints(Qt::ImhNone);
        CpuCommandLine->setMaximumBlockCount(1);
        label_error_message = new QLabel(centralwidget);
        label_error_message->setObjectName(QString::fromUtf8("label_error_message"));
        label_error_message->setGeometry(QRect(20, 490, 811, 18));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setKerning(true);
        font1.setStyleStrategy(QFont::PreferDefault);
        label_error_message->setFont(font1);
        label_error_message->setStyleSheet(QString::fromUtf8("color: rgb(165, 29, 45);"));
        DebugModeBox = new QGroupBox(centralwidget);
        DebugModeBox->setObjectName(QString::fromUtf8("DebugModeBox"));
        DebugModeBox->setGeometry(QRect(530, 0, 311, 141));
        label_debug_where_i_am = new QLabel(DebugModeBox);
        label_debug_where_i_am->setObjectName(QString::fromUtf8("label_debug_where_i_am"));
        label_debug_where_i_am->setGeometry(QRect(140, 100, 41, 20));
        label_debug_where_i_am->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        CommandGoRight = new QToolButton(DebugModeBox);
        CommandGoRight->setObjectName(QString::fromUtf8("CommandGoRight"));
        CommandGoRight->setGeometry(QRect(220, 80, 32, 34));
        CommandGoRight->setArrowType(Qt::RightArrow);
        label_2 = new QLabel(DebugModeBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 60, 61, 20));
        spinCommandToRemember = new QSpinBox(DebugModeBox);
        spinCommandToRemember->setObjectName(QString::fromUtf8("spinCommandToRemember"));
        spinCommandToRemember->setGeometry(QRect(230, 20, 51, 31));
        CommandGoLeft = new QToolButton(DebugModeBox);
        CommandGoLeft->setObjectName(QString::fromUtf8("CommandGoLeft"));
        CommandGoLeft->setGeometry(QRect(100, 80, 32, 34));
        CommandGoLeft->setArrowType(Qt::LeftArrow);
        label = new QLabel(DebugModeBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 231, 20));
        label_3 = new QLabel(DebugModeBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 60, 71, 18));
        label_4 = new QLabel(DebugModeBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(150, 80, 61, 18));
        PC_group = new QGroupBox(centralwidget);
        PC_group->setObjectName(QString::fromUtf8("PC_group"));
        PC_group->setGeometry(QRect(10, 0, 151, 61));
        PC_value = new QLineEdit(PC_group);
        PC_value->setObjectName(QString::fromUtf8("PC_value"));
        PC_value->setGeometry(QRect(40, 20, 81, 31));
        PC_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        SP_group = new QGroupBox(centralwidget);
        SP_group->setObjectName(QString::fromUtf8("SP_group"));
        SP_group->setGeometry(QRect(30, 70, 121, 61));
        SP_value = new QLineEdit(SP_group);
        SP_value->setObjectName(QString::fromUtf8("SP_value"));
        SP_value->setGeometry(QRect(20, 20, 81, 31));
        SP_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        ACU_group = new QGroupBox(centralwidget);
        ACU_group->setObjectName(QString::fromUtf8("ACU_group"));
        ACU_group->setGeometry(QRect(180, 70, 121, 61));
        ACU_value = new QLineEdit(ACU_group);
        ACU_value->setObjectName(QString::fromUtf8("ACU_value"));
        ACU_value->setGeometry(QRect(30, 20, 81, 31));
        ACU_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        IRX_group = new QGroupBox(centralwidget);
        IRX_group->setObjectName(QString::fromUtf8("IRX_group"));
        IRX_group->setGeometry(QRect(340, 0, 161, 61));
        IRX_value = new QLineEdit(IRX_group);
        IRX_value->setObjectName(QString::fromUtf8("IRX_value"));
        IRX_value->setGeometry(QRect(40, 20, 81, 31));
        IRX_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        IRY_group = new QGroupBox(centralwidget);
        IRY_group->setObjectName(QString::fromUtf8("IRY_group"));
        IRY_group->setGeometry(QRect(170, 0, 161, 61));
        IRY_value = new QLineEdit(IRY_group);
        IRY_value->setObjectName(QString::fromUtf8("IRY_value"));
        IRY_value->setGeometry(QRect(40, 20, 81, 31));
        IRY_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        PS_group = new QGroupBox(centralwidget);
        PS_group->setObjectName(QString::fromUtf8("PS_group"));
        PS_group->setGeometry(QRect(530, 150, 311, 281));
        CarryFlag_Group = new QGroupBox(PS_group);
        CarryFlag_Group->setObjectName(QString::fromUtf8("CarryFlag_Group"));
        CarryFlag_Group->setGeometry(QRect(10, 20, 131, 61));
        CF_value = new QLineEdit(CarryFlag_Group);
        CF_value->setObjectName(QString::fromUtf8("CF_value"));
        CF_value->setGeometry(QRect(20, 20, 71, 31));
        CF_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        OverflowFlag_group = new QGroupBox(PS_group);
        OverflowFlag_group->setObjectName(QString::fromUtf8("OverflowFlag_group"));
        OverflowFlag_group->setGeometry(QRect(10, 80, 131, 61));
        OF_value = new QLineEdit(OverflowFlag_group);
        OF_value->setObjectName(QString::fromUtf8("OF_value"));
        OF_value->setGeometry(QRect(20, 20, 71, 31));
        OF_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        DecimalMode_group = new QGroupBox(PS_group);
        DecimalMode_group->setObjectName(QString::fromUtf8("DecimalMode_group"));
        DecimalMode_group->setGeometry(QRect(160, 20, 131, 61));
        DM_value = new QLineEdit(DecimalMode_group);
        DM_value->setObjectName(QString::fromUtf8("DM_value"));
        DM_value->setGeometry(QRect(20, 20, 71, 31));
        DM_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        BreakCommand_group = new QGroupBox(PS_group);
        BreakCommand_group->setObjectName(QString::fromUtf8("BreakCommand_group"));
        BreakCommand_group->setGeometry(QRect(160, 80, 131, 61));
        BC_value = new QLineEdit(BreakCommand_group);
        BC_value->setObjectName(QString::fromUtf8("BC_value"));
        BC_value->setGeometry(QRect(20, 20, 71, 31));
        BC_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        ZeroFlag_group = new QGroupBox(PS_group);
        ZeroFlag_group->setObjectName(QString::fromUtf8("ZeroFlag_group"));
        ZeroFlag_group->setGeometry(QRect(160, 150, 131, 61));
        ZF_value = new QLineEdit(ZeroFlag_group);
        ZF_value->setObjectName(QString::fromUtf8("ZF_value"));
        ZF_value->setGeometry(QRect(20, 20, 71, 31));
        ZF_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        NegativeFlag_group = new QGroupBox(PS_group);
        NegativeFlag_group->setObjectName(QString::fromUtf8("NegativeFlag_group"));
        NegativeFlag_group->setGeometry(QRect(10, 150, 131, 61));
        NF_value = new QLineEdit(NegativeFlag_group);
        NF_value->setObjectName(QString::fromUtf8("NF_value"));
        NF_value->setGeometry(QRect(20, 20, 71, 31));
        NF_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        InterruptDisable_group = new QGroupBox(PS_group);
        InterruptDisable_group->setObjectName(QString::fromUtf8("InterruptDisable_group"));
        InterruptDisable_group->setGeometry(QRect(10, 210, 281, 61));
        ID_value = new QLineEdit(InterruptDisable_group);
        ID_value->setObjectName(QString::fromUtf8("ID_value"));
        ID_value->setGeometry(QRect(20, 20, 71, 31));
        ID_value->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        memory_group = new QGroupBox(centralwidget);
        memory_group->setObjectName(QString::fromUtf8("memory_group"));
        memory_group->setGeometry(QRect(10, 130, 511, 211));
        MemorySP0 = new QGroupBox(memory_group);
        MemorySP0->setObjectName(QString::fromUtf8("MemorySP0"));
        MemorySP0->setGeometry(QRect(10, 30, 71, 61));
        MemorySPEdit0 = new QLineEdit(MemorySP0);
        MemorySPEdit0->setObjectName(QString::fromUtf8("MemorySPEdit0"));
        MemorySPEdit0->setGeometry(QRect(10, 20, 51, 31));
        MemorySPEdit0->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemorySP1 = new QGroupBox(memory_group);
        MemorySP1->setObjectName(QString::fromUtf8("MemorySP1"));
        MemorySP1->setGeometry(QRect(90, 30, 71, 61));
        MemorySPEdit1 = new QLineEdit(MemorySP1);
        MemorySPEdit1->setObjectName(QString::fromUtf8("MemorySPEdit1"));
        MemorySPEdit1->setGeometry(QRect(10, 20, 51, 31));
        MemorySPEdit1->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemorySP2 = new QGroupBox(memory_group);
        MemorySP2->setObjectName(QString::fromUtf8("MemorySP2"));
        MemorySP2->setGeometry(QRect(170, 30, 71, 61));
        MemorySPEdit2 = new QLineEdit(MemorySP2);
        MemorySPEdit2->setObjectName(QString::fromUtf8("MemorySPEdit2"));
        MemorySPEdit2->setGeometry(QRect(10, 20, 51, 31));
        MemorySPEdit2->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemorySP3 = new QGroupBox(memory_group);
        MemorySP3->setObjectName(QString::fromUtf8("MemorySP3"));
        MemorySP3->setGeometry(QRect(250, 30, 71, 61));
        MemorySPEdit3 = new QLineEdit(MemorySP3);
        MemorySPEdit3->setObjectName(QString::fromUtf8("MemorySPEdit3"));
        MemorySPEdit3->setGeometry(QRect(10, 20, 51, 31));
        MemorySPEdit3->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemorySP4 = new QGroupBox(memory_group);
        MemorySP4->setObjectName(QString::fromUtf8("MemorySP4"));
        MemorySP4->setGeometry(QRect(330, 30, 71, 61));
        MemorySPEdit4 = new QLineEdit(MemorySP4);
        MemorySPEdit4->setObjectName(QString::fromUtf8("MemorySPEdit4"));
        MemorySPEdit4->setGeometry(QRect(10, 20, 51, 31));
        MemorySPEdit4->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemorySP5 = new QGroupBox(memory_group);
        MemorySP5->setObjectName(QString::fromUtf8("MemorySP5"));
        MemorySP5->setGeometry(QRect(410, 30, 71, 61));
        MemorySPEdit5 = new QLineEdit(MemorySP5);
        MemorySPEdit5->setObjectName(QString::fromUtf8("MemorySPEdit5"));
        MemorySPEdit5->setGeometry(QRect(10, 20, 51, 31));
        MemorySPEdit5->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemoryStart0 = new QGroupBox(memory_group);
        MemoryStart0->setObjectName(QString::fromUtf8("MemoryStart0"));
        MemoryStart0->setGeometry(QRect(10, 138, 71, 61));
        MemoryStartEdit0 = new QLineEdit(MemoryStart0);
        MemoryStartEdit0->setObjectName(QString::fromUtf8("MemoryStartEdit0"));
        MemoryStartEdit0->setGeometry(QRect(10, 20, 51, 31));
        MemoryStartEdit0->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemoryStart1 = new QGroupBox(memory_group);
        MemoryStart1->setObjectName(QString::fromUtf8("MemoryStart1"));
        MemoryStart1->setGeometry(QRect(90, 138, 71, 61));
        MemoryStartEdit1 = new QLineEdit(MemoryStart1);
        MemoryStartEdit1->setObjectName(QString::fromUtf8("MemoryStartEdit1"));
        MemoryStartEdit1->setGeometry(QRect(10, 20, 51, 31));
        MemoryStartEdit1->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemoryStart5 = new QGroupBox(memory_group);
        MemoryStart5->setObjectName(QString::fromUtf8("MemoryStart5"));
        MemoryStart5->setGeometry(QRect(410, 138, 71, 61));
        MemoryStartEdit5 = new QLineEdit(MemoryStart5);
        MemoryStartEdit5->setObjectName(QString::fromUtf8("MemoryStartEdit5"));
        MemoryStartEdit5->setGeometry(QRect(10, 20, 51, 31));
        MemoryStartEdit5->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemoryStart3 = new QGroupBox(memory_group);
        MemoryStart3->setObjectName(QString::fromUtf8("MemoryStart3"));
        MemoryStart3->setGeometry(QRect(250, 138, 71, 61));
        MemoryStartEdit3 = new QLineEdit(MemoryStart3);
        MemoryStartEdit3->setObjectName(QString::fromUtf8("MemoryStartEdit3"));
        MemoryStartEdit3->setGeometry(QRect(10, 20, 51, 31));
        MemoryStartEdit3->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemoryStart4 = new QGroupBox(memory_group);
        MemoryStart4->setObjectName(QString::fromUtf8("MemoryStart4"));
        MemoryStart4->setGeometry(QRect(330, 138, 71, 61));
        MemoryStartEdit4 = new QLineEdit(MemoryStart4);
        MemoryStartEdit4->setObjectName(QString::fromUtf8("MemoryStartEdit4"));
        MemoryStartEdit4->setGeometry(QRect(10, 20, 51, 31));
        MemoryStartEdit4->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        MemoryStart2 = new QGroupBox(memory_group);
        MemoryStart2->setObjectName(QString::fromUtf8("MemoryStart2"));
        MemoryStart2->setGeometry(QRect(170, 138, 71, 61));
        MemoryStartEdit2 = new QLineEdit(MemoryStart2);
        MemoryStartEdit2->setObjectName(QString::fromUtf8("MemoryStartEdit2"));
        MemoryStartEdit2->setGeometry(QRect(10, 20, 51, 31));
        MemoryStartEdit2->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        label_5 = new QLabel(memory_group);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 108, 101, 18));
        ShowMemoryStartAt = new QLineEdit(memory_group);
        ShowMemoryStartAt->setObjectName(QString::fromUtf8("ShowMemoryStartAt"));
        ShowMemoryStartAt->setGeometry(QRect(100, 100, 113, 31));
        LoadASM_group = new QGroupBox(centralwidget);
        LoadASM_group->setObjectName(QString::fromUtf8("LoadASM_group"));
        LoadASM_group->setGeometry(QRect(10, 350, 511, 91));
        ScanASM = new QPushButton(LoadASM_group);
        ScanASM->setObjectName(QString::fromUtf8("ScanASM"));
        ScanASM->setGeometry(QRect(400, 20, 88, 28));
        LoadASM = new QPushButton(LoadASM_group);
        LoadASM->setObjectName(QString::fromUtf8("LoadASM"));
        LoadASM->setGeometry(QRect(400, 50, 88, 28));
        listWidget = new QListWidget(LoadASM_group);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 20, 371, 60));
        cpu6502_mainwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(cpu6502_mainwindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 850, 23));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        cpu6502_mainwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(cpu6502_mainwindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        cpu6502_mainwindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionDebug_mode);
        menuMenu->addAction(actionHex_mode);
        menuMenu->addAction(actionRefresh_program);
        menuMenu->addSeparator();
        menuMenu->addAction(actionReset_program);
        menuMenu->addSeparator();

        retranslateUi(cpu6502_mainwindow);

        QMetaObject::connectSlotsByName(cpu6502_mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *cpu6502_mainwindow)
    {
        cpu6502_mainwindow->setWindowTitle(QCoreApplication::translate("cpu6502_mainwindow", "Cpu6502 - Interpreter", nullptr));
        actionLoad_asm->setText(QCoreApplication::translate("cpu6502_mainwindow", "Load .asm", nullptr));
        actionReset_program->setText(QCoreApplication::translate("cpu6502_mainwindow", "Reset program", nullptr));
        actionDebug_mode->setText(QCoreApplication::translate("cpu6502_mainwindow", "Debug mode", nullptr));
        actionClear_file->setText(QCoreApplication::translate("cpu6502_mainwindow", "Clear file", nullptr));
        actionRefresh_program->setText(QCoreApplication::translate("cpu6502_mainwindow", "Refresh program", nullptr));
        actionHex_mode->setText(QCoreApplication::translate("cpu6502_mainwindow", "Hex mode", nullptr));
        ExecuteButton->setText(QCoreApplication::translate("cpu6502_mainwindow", "Execute", nullptr));
#if QT_CONFIG(tooltip)
        CpuCommandLine->setToolTip(QCoreApplication::translate("cpu6502_mainwindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        CpuCommandLine->setWhatsThis(QCoreApplication::translate("cpu6502_mainwindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        CpuCommandLine->setDocumentTitle(QString());
        CpuCommandLine->setPlainText(QString());
        CpuCommandLine->setPlaceholderText(QCoreApplication::translate("cpu6502_mainwindow", "Type your command here!", nullptr));
        label_error_message->setText(QCoreApplication::translate("cpu6502_mainwindow", "Error message here!", nullptr));
#if QT_CONFIG(tooltip)
        DebugModeBox->setToolTip(QCoreApplication::translate("cpu6502_mainwindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        DebugModeBox->setWhatsThis(QCoreApplication::translate("cpu6502_mainwindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        DebugModeBox->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Debug Mode", nullptr));
        label_debug_where_i_am->setText(QCoreApplication::translate("cpu6502_mainwindow", "0", nullptr));
        CommandGoRight->setText(QCoreApplication::translate("cpu6502_mainwindow", "...", nullptr));
        label_2->setText(QCoreApplication::translate("cpu6502_mainwindow", "Go left", nullptr));
        CommandGoLeft->setText(QCoreApplication::translate("cpu6502_mainwindow", "...", nullptr));
        label->setText(QCoreApplication::translate("cpu6502_mainwindow", "Debug command to remember:", nullptr));
        label_3->setText(QCoreApplication::translate("cpu6502_mainwindow", "Go right", nullptr));
        label_4->setText(QCoreApplication::translate("cpu6502_mainwindow", "You are at", nullptr));
        PC_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Program Counter", nullptr));
        SP_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Stack Pointer", nullptr));
        ACU_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Accumulator", nullptr));
        IRX_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Index Register X", nullptr));
        IRY_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Index Register Y", nullptr));
        PS_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Processor Status", nullptr));
        CarryFlag_Group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Carry Flag", nullptr));
        OverflowFlag_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Overflow Flag", nullptr));
        DecimalMode_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Decimal Mode", nullptr));
        BreakCommand_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Break Command", nullptr));
        ZeroFlag_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Zero Flag", nullptr));
        NegativeFlag_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Negative Flag", nullptr));
        InterruptDisable_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Interrupt Disable", nullptr));
        memory_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Memory", nullptr));
        MemorySP0->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemorySP1->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemorySP2->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemorySP3->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemorySP4->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemorySP5->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemoryStart0->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemoryStart1->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemoryStart5->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemoryStart3->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemoryStart4->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        MemoryStart2->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "0xFFFF", nullptr));
        label_5->setText(QCoreApplication::translate("cpu6502_mainwindow", "Start from:", nullptr));
        LoadASM_group->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Load .asm", nullptr));
        ScanASM->setText(QCoreApplication::translate("cpu6502_mainwindow", "Scan", nullptr));
        LoadASM->setText(QCoreApplication::translate("cpu6502_mainwindow", "Load", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("cpu6502_mainwindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cpu6502_mainwindow: public Ui_cpu6502_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CONCEPTCABATE_H
